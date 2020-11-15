 ///
 /// @file    TcpConnection.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2015-11-05 16:59:04
 ///

#ifndef _WD_TCPCONNCETION_H
#define _WD_TCPCONNCETION_H

#include "Noncopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <memory>
#include <functional>

namespace wd
{

class TcpConnection : Noncopyable
{
public:
	TcpConnection(int sockfd);
	~TcpConnection();

	std::string receive();
	void send(const std::string & msg);
	void shutdown();

	std::string toString();

private:
	Socket sockfd_;
	SocketIO sockIO_;
	const InetAddress localAddr_;
	const InetAddress peerAddr_;
	bool isShutdownWrite_;
};

}//end of namespace wd

#endif
