 ///
 /// @file    TcpServer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2015-11-07 10:23:57
 ///

#include "TcpServer.h"
#include "SocketUtil.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
TcpServer::TcpServer(unsigned short port)
	: acceptor_(createSocketFd(), InetAddress(port)),
	  epollfd_(acceptor_)
{
	acceptor_.ready();
}

TcpServer::TcpServer(const string & ip, unsigned short port)
	: acceptor_(createSocketFd(), InetAddress(ip.c_str(), port)),
	  epollfd_(acceptor_)
{
	acceptor_.ready();
}

void TcpServer::start()
{
	epollfd_.loop();
}

void TcpServer::stop()
{
	epollfd_.unloop();
}

void TcpServer::setConnectionCallback(const ConnectionCallback &cb)
{
	epollfd_.setConnectionCallback(cb);
}

void TcpServer::setMessageCallback(const MessageCallback & cb)
{
	epollfd_.setMessageCallback(cb);
}

void TcpServer::setCloseCallback(const CloseCallback & cb)
{
	epollfd_.setCloseCallback(cb);
}

string TcpServer::ipPort()const
{
	return acceptor_.ipPort();
}

}//end of namespace wd
