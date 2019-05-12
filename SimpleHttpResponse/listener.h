#pragma once
#include <memory>
#include <boost/asio.hpp>

class listener : std::enable_shared_from_this<listener>
{
	boost::asio::ip::tcp::acceptor	acceptor_;
	boost::asio::ip::tcp::socket	socket_;
public:
	listener
	(
		boost::asio::io_context&		ioc,		//
		boost::asio::ip::tcp::endpoint	endpoint
	);
	
	~listener();
	// Добавлен комментарий для возможности проверки на GitHub
	void run();
protected:
	void do_accept();
	void on_accept(boost::system::error_code ec);

};

