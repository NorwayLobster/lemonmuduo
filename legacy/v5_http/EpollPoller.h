 ///
 /// @file    EpollPoller.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2015-11-06 16:12:11
 ///


#ifndef __WD_EPOLLPOLLER_H
#define __WD_EPOLLPOLLER_H

#include "Noncopyable.h"
#include "TcpConnection.h"
#include "MutexLock.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <functional>

namespace wd
{

class Acceptor;
class EpollPoller : Noncopyable
{
public:
	typedef std::function<void(const TcpConnectionPtr &)> ConnectionCallback;
	typedef std::function<void(const TcpConnectionPtr &)> CloseCallback;
	typedef std::function<void(const TcpConnectionPtr &, Buffer *)> MessageCallback;
	typedef std::function<void()> Functor;

	EpollPoller(Acceptor & acceptor);
	~EpollPoller();

	void loop();
	void unloop();
	void runInLoop(const Functor & cb);
	void doPendingFunctors();

	void wakeup();
	void handleRead();

	void setConnectionCallback(const ConnectionCallback & cb);
	void setMessageCallback(const MessageCallback & cb);
	void setCloseCallback(const CloseCallback & cb);

private:
	void waitEpollfd();
	void handleConnection();
	void handleMessage(int peerfd);
	
private:
	Acceptor & acceptor_;
	int epollfd_;
	int listenfd_;
	int wakeupfd_;
	bool isLooping_;

	MutexLock mutex_;
	std::vector<Functor> pendingFunctors_;

	typedef std::vector<struct epoll_event> EventList;
	EventList eventsList_;

	typedef std::map<int, TcpConnectionPtr> ConnectionMap;
	ConnectionMap connMap_;

	ConnectionCallback onConnectionCb_;
	MessageCallback onMessageCb_;
	CloseCallback onCloseCb_;
};


}//end of namespace wd

#endif
