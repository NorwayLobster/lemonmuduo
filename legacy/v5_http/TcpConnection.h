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
#include "Buffer.h"

#include <string>
#include <memory>
#include <functional>

namespace wd
{

class EpollPoller;

class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection : Noncopyable,
	public std::enable_shared_from_this<TcpConnection>
{
public:
	typedef std::function<void(const TcpConnectionPtr &)> ConnectionCallback;
	typedef std::function<void(const TcpConnectionPtr &)> CloseCallback;
	typedef std::function<void(const TcpConnectionPtr &, Buffer *)> MessageCallback;

	TcpConnection(int sockfd, EpollPoller * loop);
	~TcpConnection();

	std::string receive();
	void send(const std::string & msg);
	void send(Buffer * buf);
	void sendAndClose(const std::string & msg);
	void sendInLoop(const std::string & msg);
	void shutdown();

	std::string toString();

	void setConnectionCallback(const ConnectionCallback & cb);
	void setMessageCallback(const MessageCallback & cb);
	void setCloseCallback(const CloseCallback & cb);

	void setContext(void * context){ _context = context; }
	void * getContext(){ return _context; }

	void handleConnectionCallback();
	void handleRead();
	void handleCloseCallback();

private:
	Socket sockfd_;
	SocketIO sockIO_;
	const InetAddress localAddr_;
	const InetAddress peerAddr_;
	bool isShutdownWrite_;
	EpollPoller * loop_;

	Buffer _inputBuffer;
	Buffer _outputBuffer;
	void * _context;

	ConnectionCallback onConnectionCb_;
	MessageCallback onMessageCb_;
	CloseCallback onCloseCb_;
};

}//end of namespace wd

#endif
