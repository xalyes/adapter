#pragma once

#include "boost/asio.hpp"
#include <string>

static boost::asio::io_service g_service;

const int numberOfPorts = 2;
const int PortsToListen[numberOfPorts] = { 2001, 2002 };
const int PortsToSend[numberOfPorts] = { 8001, 8002 };

size_t ReadCompletion(char * buf, const boost::system::error_code & err, size_t bytes);
void WriteMsg(std::string msg, int port);