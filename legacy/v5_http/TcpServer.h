 ///
 /// @file    TcpServer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2015-11-07 10:19:27
 ///

#ifndef _WD_TCPSERVER_H
#define _WD_TCPSERVER_H

#include "InetAddress.h"
#include "Acceptor.h"
#include "EpollPoller.h"

#include <string>
using std::string;

namespace wd
{

class TcpServer
{
public:
	typedef std::function<void(const TcpConnectionPtr &)> ConnectionCallback;
	typedef std::function<void(const TcpConnectionPtr &)> CloseCallback;
	typedef std::function<void(const TcpConnectionPtr &, Buffer *)> MessageCallback;

	TcpServer(unsigned short port);
	TcpServer(const string & ip, unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(const ConnectionCallback & cb);
	void setMessageCallback(const MessageCallback & cb);
	void setCloseCallback(const CloseCallback & cb);

	string ipPort() const;

private:
	Acceptor acceptor_;
	EpollPoller epollfd_;

	ConnectionCallback onConnectionCb_;
	MessageCallback onMessageCb_;
	CloseCallback onCloseCb_;
};

}// end of namespace wd

#endif
