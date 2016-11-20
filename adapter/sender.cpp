#include "stdafx.h"
#include "sender.h"
#include "network_helpers.h"

using namespace boost::asio;

std::vector<std::string>& GetData()
{
	if (data.empty())
	{
		for (int i = 0; i < numberOfPorts; ++i)
			data.push_back("null data");
	}
	return data;
}

void Sender::Acceptor(int port)
{
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), port);
	ip::tcp::acceptor acc(g_service, ep);
	boost::thread_group threads;
	char buff[1024];

	while (m_exitStatus != true)
	{
		ip::tcp::socket sock(g_service);
		std::cout << "socket is open: " << port << std::endl;
		acc.accept(sock);
		std::cout << "accept" << std::endl;
		boost::asio::streambuf response;
		size_t bytes = read_until(sock, response, '\0');
		//sock.close();
		boost::asio::streambuf::const_buffers_type bufs = response.data();
		std::string msg(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes - 1);
		std::cout << "get it: " << msg << std::endl;
		//std::string msg(buff, bytes - 1);
		if (msg == "GET")
		{
			sock.write_some(buffer(GetData()[0]));
			std::cout << "write it: " << GetData()[0] << std::endl;
		}
		sock.close();
		std::cout << "close it" << std::endl;
	}
	threads.join_all();
}

void Sender::Start()
{
	m_exitStatus = false;
	for (int i = 0; i < numberOfPorts; ++i)
	{
		m_threads.create_thread(boost::bind(&Sender::Acceptor, this, PortsToSend[i]));
	}
	std::cout << "sender started" << std::endl;
}

void Sender::Stop()
{
	m_exitStatus = true;
	m_threads.join_all();
}