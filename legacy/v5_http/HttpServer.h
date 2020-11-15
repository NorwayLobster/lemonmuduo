
#ifndef WD_HTTP_HTTPSERVER_H
#define WD_HTTP_HTTPSERVER_H

#include "Noncopyable.h"
#include "TcpServer.h"
#include <functional>

namespace wd 
{

class Buffer;
class HttpRequest;
class HttpResponse;

class HttpServer : Noncopyable
{
public:
	typedef std::function<void (const HttpRequest&, HttpResponse*)> HttpCallback;

	HttpServer(const string & ip, unsigned short port);

	~HttpServer();  // force out-line dtor, for scoped_ptr members.

	void setHttpCallback(const HttpCallback& cb)
	{
		httpCallback_ = cb;
	}

	void start();

private:
	void onConnection(const TcpConnectionPtr& conn);
	void onMessage(const TcpConnectionPtr& conn, Buffer* buf);
	void onRequest(const TcpConnectionPtr&, const HttpRequest&);

	TcpServer server_;
	HttpCallback httpCallback_;
};

}//end of namespace wd

#endif  // WD_HTTP_HTTPSERVER_H
