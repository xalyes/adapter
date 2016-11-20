#pragma once
#include "settings.h"

class Reciever
{
public:
	Reciever(Settings& settings) : m_settings(settings) {}
	void Acceptor(int port, unsigned int module);
	void Start();
	void Stop();

private:
	boost::thread_group m_threads;
	bool m_exitStatus;
	Settings m_settings;
};