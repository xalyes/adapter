#include "stdafx.h"
#include <utility>
#include "reciever.h"
#include "sender.h"
#include "network_helpers.h"
#include "boost/program_options.hpp"
using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

void Client(int port, std::string msg = "hello beatch!")
{
	io_service service;
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), port);
	ip::tcp::socket sock(service);
	sock.connect(ep);
	sock.write_some(buffer(msg));
	sock.close();
	if (msg == "get")
	{
		char buff[1024];
		sock.connect(ep);
		sock.read_some(buffer(buff, 1024));
		std::cout << buff;
	}
	
	sock.close();
	std::cout << "good" << std::endl;
}

int main(int argc, char **argv)
{
	namespace po = boost::program_options;
	po::options_description desc("General options");

	desc.add_options()
		("ports", po::value<std::vector<std::string> >()->multitoken(), "Connection ports");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	std::vector<std::string> ports;
	ports = vm["ports"].as<std::vector<std::string> >();
	std::cout << ports[0];
	if (!vm["ports"].empty() && (ports = vm["ports"].as<std::vector<std::string> >()).size() == 2) {
		
	}

	Reciever reciever;
	Sender sender;
	reciever.Start();
	sender.Start();
	while (true)
	{
	}
	boost::this_thread::sleep(boost::posix_time::millisec(1000000));
	//Client(2001);
	//Client(2002);
	//Client(2001);
	boost::this_thread::sleep(boost::posix_time::millisec(1000));
	//Client(8001);


	//reciever.Stop();
	//sender.Stop();
	return 0;
}