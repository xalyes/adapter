#include "stdafx.h"
#include "network_helpers.h"

void WriteMsg(std::string msg, int port)
{
	std::cout << msg << ":" << port << std::endl;
}

size_t ReadCompletion(char * buf, const boost::system::error_code & err, size_t bytes)
{
	if (err) return 0;
	bool found = std::find(buf, buf + bytes, '\0') < buf + bytes;
	// we read one-by-one until we get to enter, no buffering
	return found ? 0 : 1;
}