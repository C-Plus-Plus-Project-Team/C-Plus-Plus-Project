#ifdef WIN32
#define _WIN_WINNT 0x0501
#include<stdio.h>
#endif

#include <algorithm>  
#include <cstdlib>  
#include <deque>  
#include <iostream>  
#include <list>  
#include <set>  
#include <boost/bind.hpp>  
#include <boost/shared_ptr.hpp>  
#include <boost/enable_shared_from_this.hpp>  
#include <boost/asio.hpp>  
#include "chat.hpp"  

using boost::asio::ip::tcp;
using namespace boost::asio;
using namespace std;

typedef std::deque<chat_message> chat_message_queue;//ʹ��typedefʹ��ʼ����

class chat_participant//����Ŀͻ���
{
public:
	virtual ~chat_participant() {}//��������
	virtual void deliver(const chat_message& msg) = 0; //ʹ���麯��
};

typedef boost::shared_ptr<chat_participant> chat_participant_ptr;//ָ��Clients�������ָ��

class chat_room
{
public:
	void join(chat_participant_ptr participant)
	{
		cout << "join" << endl;
		participants_.insert(participant);//��Ҽ���
	}

	void leave(chat_participant_ptr participant)
	{
		cout << "leave" << endl;
		participants_.erase(participant);//����˳�
	}

	void deliver(const chat_message& msg) //�����ݴ��뻺��������
	{
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > max_recent_msgs)
		{
			recent_msgs_.pop_front();//����ʱ�����������������
		}
		for_each(participants_.begin(), participants_.end(), boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));//��ÿ����ҷ�������
	}

private:
	set<chat_participant_ptr> participants_; //��ǰ�����
	enum { max_recent_msgs = 100 }; //�������е������Ϣ
	chat_message_queue recent_msgs_; //���ݶ��У��ȵ��ȳ���
};

class chat_session//ÿһ����ҵ���
	: public chat_participant, // �̳�  
	public boost::enable_shared_from_this<chat_session> // ����ʹ��shared_from_this()(��shared_ptr<chat_session>)  
{
public:
	typedef const boost::system::error_code& error_code;

	chat_session(io_service& io_service, chat_room& room)//���캯��
		: socket_(io_service),
		room_(room)
	{}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		room_.join(shared_from_this());
		cout << "read_header" << endl;
		boost::asio::async_read(socket_, buffer(read_msg_.data(), chat_message::header_length), boost::bind(&chat_session::handle_read_header, shared_from_this(), boost::asio::placeholders::error));//����:shared_from_this()->handle_read_header(boost::asio::placeholders::error);
	}

	// ��buffer�е����ݵ�read_msg_��header����  
	void handle_read_header(const error_code& err)
	{
		if (!err && read_msg_.decode_header())
		{
			cout << "read_body" << endl;
			boost::asio::async_read(socket_, buffer(read_msg_.body(), read_msg_.body_length()), boost::bind(&chat_session::handle_read_body, shared_from_this(), boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

	// ��buffer�е����ݵ�read_msg_��body����  
	void handle_read_body(const error_code& err)
	{
		if (!err)
		{
			cout << "read_header" << endl;
			room_.deliver(read_msg_);
			boost::asio::async_read(socket_, buffer(read_msg_.data(), chat_message::header_length), boost::bind(&chat_session::handle_read_header, shared_from_this(), boost::asio::placeholders::error));
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

	//�������ݵ�write_msgs_���Ͷ��е��ʼһ�����Ե�buffer  
	void deliver(const chat_message& msg) // 12,�м����ͻ��˵��ü���  
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress) // ���ݶ��е��ʼһ�����ݴ��뵽buffer  
		{
			cout << "deliver" << endl;
			cout << write_msgs_.front().data() << endl;
			boost::asio::async_write(socket_, buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&chat_session::handle_write, shared_from_this(), boost::asio::placeholders::error));
		}
	}

	// ��write_msgs_������buffer��ʹ�ͻ��˿��Եõ����ݹ��������ֵ��write_msgs_Ϊ��  
	void handle_write(const error_code& err)
	{
		if (!err)
		{
			write_msgs_.pop_front();//����ѷ��͵�����
			if (!write_msgs_.empty())
			{
				cout << "write" << endl;
				boost::asio::async_write(socket_, buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&chat_session::handle_write, shared_from_this(), boost::asio::placeholders::error));
			}
		}
		else
		{
			room_.leave(shared_from_this());
		}
	}

private:
	tcp::socket socket_;//�˿�
	chat_room& room_;
	chat_message read_msg_; // �ӻ���������������  
	chat_message_queue write_msgs_; // ���͵������������ݶ���
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;

class chat_server//�Կͻ��˵Ĵ���
{
public:
	chat_server(io_service& io_service, const tcp::endpoint& endpoint)
		: io_service_(io_service),
		acceptor_(io_service, endpoint)
	{
		chat_session_ptr new_session(new chat_session(io_service_, room_));
		acceptor_.async_accept(new_session->socket(), boost::bind(&chat_server::handle_accept, this, new_session, boost::asio::placeholders::error));
	}
	//����������ӣ�Ȼ��ȴ���һ������
	void handle_accept(chat_session_ptr session, const error_code& err)
	{
		if (!err)
		{
			session->start();
			chat_session_ptr new_session(new chat_session(io_service_, room_));
			acceptor_.async_accept(new_session->socket(), boost::bind(&chat_server::handle_accept, this, new_session, boost::asio::placeholders::error));
		}
	}

private:
	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
	chat_room room_;
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

int main()
{

	try
	{
		boost::asio::io_service io_service;

		chat_server_list servers;

		tcp::endpoint endpoint(/*boost::asio::ip::address_v4::from_string("127.0.0.1")*/tcp::v4(), 1000);
		chat_server_ptr server(new chat_server(io_service, endpoint)); // 1  
		servers.push_back(server);

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}