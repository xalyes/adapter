#pragma once

#include "boost/asio.hpp"
#include <string>

static boost::asio::io_service g_service;

size_t ReadCompletion(char * buf, const boost::system::error_code & err, size_t bytes);
void WriteMsg(std::string msg, int port);