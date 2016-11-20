#pragma once
#include "network_helpers.h"

static std::vector<std::string> data;
std::vector<std::string>& GetData();

class Sender
{
public:
	void Acceptor(int port);
	void Start();
	void Stop();

private:
	boost::thread_group m_threads;
	bool m_exitStatus;
};