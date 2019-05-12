#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;

/// Управление подключением
class session : public std::enable_shared_from_this<session>
{
	boost::beast::tcp_stream	stream_;
	boost::beast::flat_buffer	buffer_;
public:
	session
	(
		boost::asio::ip::tcp::socket&&	socket
	);

	// Запуск асинхронной обработки 
	void run();

protected:
	void do_read();
	void do_close();
	void handle_request(http::request<http::string_body>&& req);
	
	~session();
};

