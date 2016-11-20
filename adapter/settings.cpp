#include "stdafx.h"
#include "settings.h"
#include "boost/program_options.hpp"
#include <boost/algorithm/string.hpp>

Settings::Settings(int argc, char ** argv)
{
	namespace po = boost::program_options;
	po::options_description desc("General options");

	desc.add_options()
		("ports", po::value<std::vector<std::string> >()->multitoken(), "Connection ports");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	std::vector<std::string> ports;
	ports = vm["ports"].as<std::vector<std::string> >();
	m_amount = ports.size();
	for (size_t i = 0; i < m_amount; ++i)
	{
		std::vector<std::string> strings;
		boost::split(strings, ports[i], boost::is_any_of(":-"));
		m_type.push_back(strings[0]);
		m_inputPorts.push_back(std::stoi(strings[1]));
		m_outputPorts.push_back(std::stoi(strings[2]));
	}
}

std::string Settings::GetType(int i)
{
	return m_type[i];
}

int Settings::GetInputPort(int i)
{
	return m_inputPorts[i];
}

int Settings::GetOutputPort(int i)
{
	return m_outputPorts[i];
}

unsigned int Settings::GetAmount()
{
	return m_amount;
}
