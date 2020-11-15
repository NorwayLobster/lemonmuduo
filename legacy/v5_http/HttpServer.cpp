#include "HttpServer.h"

#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Buffer.h"

#include <iostream>
using std::cout;
using std::endl;

using namespace wd;

namespace wd 
{
namespace detail
{

void defaultHttpCallback(const HttpRequest&, HttpResponse* resp)
{
	resp->setStatusCode(HttpResponse::k404NotFound);
	resp->setStatusMessage("Not Found");
	resp->setCloseConnection(true);
}
}
}//end of namespace wd

HttpServer::HttpServer(const string & ip,
		unsigned short port)
: server_(ip, port)
, httpCallback_(detail::defaultHttpCallback)
{
	using namespace std::placeholders;
	server_.setConnectionCallback(
			std::bind(&HttpServer::onConnection, this, _1));
	server_.setMessageCallback(
			std::bind(&HttpServer::onMessage, this, _1, _2));

	cout << "> HttpSever listening on " << server_.ipPort() << endl;
}

HttpServer::~HttpServer()
{
}

void HttpServer::start()
{
	server_.start();
}

void HttpServer::onConnection(const TcpConnectionPtr& conn)
{
	cout << conn->toString() << " has connected!\n";
	conn->setContext(new HttpContext());//谁来析构?
}

void HttpServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf)
{
	HttpContext* context = static_cast<HttpContext * >(conn->getContext());

	if (!context->parseRequest(buf))//完整的数据还没到达怎么办？
	{
		conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
		conn->shutdown();
	}

	if (context->gotAll())
	{
		onRequest(conn, context->request());
		context->reset();
	}
}

void HttpServer::onRequest(const TcpConnectionPtr& conn, const HttpRequest& req)
{
	const string& connection = req.getHeader("Connection");
	bool close = connection == "close" ||
		(req.getVersion() == HttpRequest::kHttp10 && connection != "Keep-Alive");
	HttpResponse response(close);
	httpCallback_(req, &response);
	Buffer buf;
	response.appendToBuffer(&buf);
	conn->send(&buf);
	if (response.closeConnection())
	{
		conn->shutdown();
	}
}

