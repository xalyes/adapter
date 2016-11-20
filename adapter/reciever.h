#pragma once

class Reciever
{
public:
	void Acceptor(int port);
	void Start();
	void Stop();

private:
	boost::thread_group m_threads;
	bool m_exitStatus;
};