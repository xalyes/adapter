#include "stdafx.h"
#include "network_helpers.h"
#include "translator.h"
#include "reciever.h"
#include <sstream>

using namespace boost::asio;

void Reciever::Acceptor(int port, unsigned int module)
{
	ip::tcp::endpoint ep(ip::tcp::v4(), port);
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
		
		sock.close();

		boost::asio::streambuf::const_buffers_type bufs = response.data();
		std::string msg(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes - 1);
		std::cout << "get it: " << msg << std::endl;
		//std::string msg(response_stream.str(), bytes - 1);
		threads.create_thread(boost::bind(TranslateMessage, msg, module, m_settings.GetType(module)));
	}
	threads.join_all();
}

void Reciever::Start()
{
	m_exitStatus = false;
	for (unsigned int i = 0; i < m_settings.GetAmount(); ++i)
	{
		m_threads.create_thread(boost::bind(&Reciever::Acceptor, this, m_settings.GetInputPort(i), i));
	}
	std::cout << "reciever started" << std::endl;
}

void Reciever::Stop()
{
	m_exitStatus = true;
	m_threads.join_all();
}


