#include "stdafx.h"
#include "reciever.h"
#include "sender.h"
#include "network_helpers.h"
#include "settings.h"
using namespace boost::asio;

int main(int argc, char **argv)
{
	Settings settings(argc, argv);
	Reciever reciever(settings);
	Sender sender(settings);
	reciever.Start();
	sender.Start();

	while (true)
	{
	}

	return 0;
}