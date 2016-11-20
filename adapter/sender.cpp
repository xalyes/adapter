#include "stdafx.h"
#include "sender.h"
#include "network_helpers.h"

using namespace boost::asio;

void Sender::Acceptor(int port, unsigned int module)
{
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), port);
	ip::tcp::acceptor acc(g_service, ep);
	boost::thread_group threads;

	while (m_exitStatus != true)
	{
		ip::tcp::socket sock(g_service);
		std::cout << "socket is open: " << port << std::endl;
		acc.accept(sock);
		std::cout << "accept" << std::endl;
		boost::asio::streambuf response;
		size_t bytes = read_until(sock, response, '\0');
		boost::asio::streambuf::const_buffers_type bufs = response.data();
		std::string msg(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes - 1);
		std::cout << "get it: " << msg << std::endl;
		if (msg == "GET")
		{
			sock.write_some(buffer(Sender::m_data[module]));
			std::cout << "write it: " << Sender::m_data[module] << std::endl;
		}
		sock.close();
		std::cout << "close it" << std::endl;
	}
	threads.join_all();
}

void Sender::Start()
{
	m_exitStatus = false;
	for (unsigned int i = 0; i < m_settings.GetAmount(); ++i)
	{
		m_threads.create_thread(boost::bind(&Sender::Acceptor, this, m_settings.GetOutputPort(i), i));
	}
	std::cout << "sender started" << std::endl;
}

void Sender::Stop()
{
	m_exitStatus = true;
	m_threads.join_all();
}

std::vector<std::string> Sender::m_data = { "null", "null", "null", "null", "null", "null", "null", "null" };