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

typedef std::deque<chat_message> chat_message_queue;//使用typedef使初始化简单

class chat_participant//加入的客户端
{
public:
	virtual ~chat_participant() {}//析构函数
	virtual void deliver(const chat_message& msg) = 0; //使用虚函数
};

typedef boost::shared_ptr<chat_participant> chat_participant_ptr;//指向Clients类的智能指针

class chat_room
{
public:
	void join(chat_participant_ptr participant)
	{
		cout << "join" << endl;
		participants_.insert(participant);//玩家加入
	}

	void leave(chat_participant_ptr participant)
	{
		cout << "leave" << endl;
		participants_.erase(participant);//玩家退出
	}

	void deliver(const chat_message& msg) //将数据存入缓冲区队列
	{
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > max_recent_msgs)
		{
			recent_msgs_.pop_front();//将过时的数据清理出缓存区
		}
		for_each(participants_.begin(), participants_.end(), boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));//给每个玩家发送数据
	}

private:
	set<chat_participant_ptr> participants_; //当前的玩家
	enum { max_recent_msgs = 100 }; //缓冲区中的最大消息
	chat_message_queue recent_msgs_; //数据队列（先到先出）
};

class chat_session//每一个玩家的类
	: public chat_participant, // 继承  
	public boost::enable_shared_from_this<chat_session> // 可以使用shared_from_this()(即shared_ptr<chat_session>)  
{
public:
	typedef const boost::system::error_code& error_code;

	chat_session(io_service& io_service, chat_room& room)//构造函数
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
		boost::asio::async_read(socket_, buffer(read_msg_.data(), chat_message::header_length), boost::bind(&chat_session::handle_read_header, shared_from_this(), boost::asio::placeholders::error));//调用:shared_from_this()->handle_read_header(boost::asio::placeholders::error);
	}

	// 存buffer中的数据到read_msg_：header部分  
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

	// 存buffer中的数据到read_msg_：body部分  
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

	//存入数据到write_msgs_，送队列的最开始一条发言到buffer  
	void deliver(const chat_message& msg) // 12,有几个客户端调用几次  
	{
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress) // 数据队列的最开始一条数据存入到buffer  
		{
			cout << "deliver" << endl;
			cout << write_msgs_.front().data() << endl;
			boost::asio::async_write(socket_, buffer(write_msgs_.front().data(), write_msgs_.front().length()), boost::bind(&chat_session::handle_write, shared_from_this(), boost::asio::placeholders::error));
		}
	}

	// 把write_msgs_数据送buffer，使客户端可以得到，递归调用自身值到write_msgs_为空  
	void handle_write(const error_code& err)
	{
		if (!err)
		{
			write_msgs_.pop_front();//清除已发送的数据
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
	tcp::socket socket_;//端口
	chat_room& room_;
	chat_message read_msg_; // 从缓存区读到的数据  
	chat_message_queue write_msgs_; // 发送到缓存区的数据队列
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;

class chat_server//对客户端的处理
{
public:
	chat_server(io_service& io_service, const tcp::endpoint& endpoint)
		: io_service_(io_service),
		acceptor_(io_service, endpoint)
	{
		chat_session_ptr new_session(new chat_session(io_service_, room_));
		acceptor_.async_accept(new_session->socket(), boost::bind(&chat_server::handle_accept, this, new_session, boost::asio::placeholders::error));
	}
	//处理玩家连接，然后等待下一个连接
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