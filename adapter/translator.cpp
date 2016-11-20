#include "stdafx.h"
#include "translator.h"
#include "sender.h"
#include <sstream>

void TranslateMessage(const std::string& msg, unsigned int module, const std::string& type)
{
	Translator translator(msg, module, type);
	translator.ToJson();
}

Translator::Translator(const std::string & msg, unsigned int module, const std::string& type)
	: m_message(msg),
	m_module(module),
	m_type(type)
{
}

void Translator::ToJson()
{
	m_jsonTree.put<int>("module", m_module);
	m_jsonTree.put<std::string>("type", m_type);
	m_jsonTree.put<std::string>("data", m_message);
	std::stringstream s;
	boost::property_tree::write_json(s, m_jsonTree);
	Sender::m_data[m_module] = s.str();
	std::cout << Sender::m_data.at(m_module) << std::endl;
}
