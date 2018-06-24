#ifdef WIN32
#define _WIN_WINNT 0x0501
#include<stdio.h>
#endif

#include <string>
#include "cocos2d.h"
#include <vector>
#include <iostream>  
#include <boost/bind.hpp>  
#include <boost/asio.hpp>  
#include <boost/shared_ptr.hpp>  
#include <boost/thread.hpp>  
#include <boost/enable_shared_from_this.hpp>
#include "chat.hpp"


using boost::asio::ip::tcp;
using namespace boost::asio;
using namespace std;
io_service service;
vector <string> vec;
ip::tcp::socket sock(service);//����socket
ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 1000);//����Ҫ���ӵ�Ƕ����
float a__;
float b__;
float a_;
float b_;
float c_;
float d_;
float j;
float k;
char p;
char msg[10];
char ch_[1];
bool whether_read = false;


void connect()
{
	sock.connect(ep);//����
}

void write(char c,float a, float b)//��������
{
	char write_message[100];
	chat_message msg;
	sprintf_s(write_message, "1%c%.2f %.2f",c, a, b);
	msg.body_length(strlen(write_message));
	memcpy(msg.body(), write_message, msg.body_length());
	msg.encode_header();
	sock.send(buffer(msg.data(), msg.length()));//ͬ����������
}

void write(char e,float a, float b, float c, float d)
{
	char write_message[100];
	chat_message msg;
	sprintf_s(write_message, "2%c%.2f %.2f %.2f %.2f",e, a, b, c, d);
	msg.body_length(strlen(write_message));
	memcpy(msg.body(), write_message, msg.body_length());
	msg.encode_header();
	sock.send(buffer(msg.data(), msg.length()));//ͬ����������
}

void write(char c,char ch[12], float a, float b)
{
	char write_message[100];
	chat_message msg;
	sprintf_s(write_message, "3%c%s %.2f %.2f", c,ch, a, b);
	msg.body_length(strlen(write_message));
	memcpy(msg.body(), write_message, msg.body_length());
	msg.encode_header();
	sock.send(buffer(msg.data(), msg.length()));//ͬ����������

	//cocos2d::log(" send   3  %c %s %.2f %.2f", c, ch, a, b);
}

void read()//��ȡ����
{
	while (true)
	{
		chat_message read_message;
		
		read(sock, buffer(read_message.data(), 3));//���´����������ݴ���ʱ���ᱻִ��
		read_message.decode_header();
		read(sock, buffer(ch_, 1));

		whether_read = true;

		if (ch_[0] == '1')//�ƶ���Ϣ��������Ϣ
		{
			read(sock, buffer(read_message.body(), read_message.body_length() - 1));
			sscanf_s(read_message.body(), "%c %f %f",&p,sizeof(p), &a__, &b__);
			cocos2d::log("clinet read  1 ");
		}
		else if (ch_[0] == '2')//��ѡ
		{
			read(sock, buffer(read_message.body(), read_message.body_length() - 1));
			sscanf_s(read_message.body(), "%c %f %f %f %f", &p,sizeof(p),&a_, &b_, &c_, &d_);
		}
		else if(ch_[0] == '3')//����������Ϣ
		{
			read(sock, buffer(read_message.body(), read_message.body_length() - 1));
			sscanf_s(read_message.body(), "%c %s %f %f", &p,sizeof(p),msg, sizeof(msg), &j, &k);
			cocos2d::log("clinet read 3 %c %s %f %f", p, msg, j, k);
		}
		else;
	}
}

void thread_()
{
	boost::thread thread__(read);
}



