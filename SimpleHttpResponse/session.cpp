#include "pch.h"
#include "session.h"
#include <iostream>


session::session(boost::asio::ip::tcp::socket && socket)
	:stream_(std::move(socket))
{
}

void session::run()
{
	do_read();
}

void session::do_read ()
{
	http::request<http::string_body> req;
	stream_.expires_after(std::chrono::seconds(30));

	http::async_read
	(
		stream_,
		buffer_,
		req,
		[this, &req] (beast::error_code ec, std::size_t bytes_transferred)
		{
			boost::ignore_unused(bytes_transferred);

			if (ec == http::error::end_of_stream)
				return do_close();

			if (ec)
			{
				std::cerr << "Read error : " << ec.message() << "\n";
				return;
			}

			handle_request(std::move(req));

			do_read();
		}
	);
}

void session::do_close()
{
	beast::error_code ec;
	stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
}

void session::handle_request(http::request<http::string_body>&& req)
{
}

session::~session()
{
}
