#include "pch.h"
#include "listener.h"
#include <iostream>


listener::listener(boost::asio::io_context & ioc, boost::asio::ip::tcp::endpoint endpoint)
	: acceptor_(ioc), socket_(ioc)
{
	boost::system::error_code ec;

	// îòêðûâàåì àêöåïòîð
	acceptor_.open(endpoint.protocol(), ec);
	if (ec)
	{
		std::cerr << "Acceptor open : " << ec.message() << "\n";
		return;
	}

	// настраиваем на повторное использование адреса
	acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
	if (ec)
	{
		std::cerr << "Acceptor set reuse address : " << ec.message() << "\n";
		return;
	}

	// ïðèâÿçûâàåì 
	acceptor_.bind(endpoint, ec);
	if (ec)
	{
		std::cerr << "Acceptor bind : " << ec.message() << "\n";
		return;
	}

	// ïåðåâîäèì àêöåïòîð â ðåæèì ïðîñëóøêè
	acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
	if (ec)
	{
		std::cerr << "Acceptor listen : " << ec.message() << "\n";
		return;
	}
}

listener::~listener()
{
}

void listener::run()
{
	if (!acceptor_.is_open())
		return;
	do_accept();
}

void listener::do_accept()
{
	acceptor_.async_accept
	(
		socket_,
		std::bind
		(
			&listener::on_accept,
			shared_from_this(),
			std::placeholders::_1
		)
	);
}

void listener::on_accept(boost::system::error_code ec)
{
}
