#pragma once
#include "network_helpers.h"
#include "settings.h"

class Sender
{
public:
	Sender(Settings& settings) : m_settings(settings)
	{}
	void Acceptor(int port, unsigned int module);
	void Start();
	void Stop();

	static std::vector<std::string> m_data;

private:
	boost::thread_group m_threads;
	bool m_exitStatus;
	Settings m_settings;
};