#pragma once

#include <iostream>
#include <vector>
#include <map>

#include <boost/property_tree/json_parser.hpp>

#include "boost/asio.hpp"
#include <boost/bind.hpp>
#include "boost/system/error_code.hpp"
#include "boost/thread.hpp"
#include "boost/shared_ptr.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

#define BOOST_ASIO_DISABLE_THREADS