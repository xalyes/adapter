#include <utility>

#include <iostream>
#include <vector>
#include <map>

#include <boost/property_tree/json_parser.hpp>

#include "boost/asio.hpp"
#include <boost/bind.hpp>
#include "boost/system/error_code.hpp"
#include "boost/thread.hpp"
#include "boost/shared_ptr.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

#define BOOST_ASIO_DISABLE_THREADS

using namespace boost::asio;

static boost::asio::io_service g_service;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

void Client(int port, std::string msg = "hello beatch!")
{
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), port);
	ip::tcp::socket sock(g_service);
	boost::system::error_code err;
	sock.connect(ep, err);
	sock.write_some(buffer(msg.c_str(), 1024), err);
	if (msg == "GET")
	{
		char buff[1024];
		sock.read_some(buffer(buff, 1024), err);
		std::cout << buff;
	}

	sock.close();
	std::cout << "good" << std::endl;
}

int main()
{
	std::string request;
	int port;
	std::cin >> request >> port;
	while (true)
	{
		Client(port, request);
		std::cin >> request >> port;
	}
	return 0;
}