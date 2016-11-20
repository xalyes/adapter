#include "stdafx.h"
#include "translator.h"
#include "sender.h"
#include <sstream>

void TranslateMessage(const std::string& msg, int port)
{
	Translator translator(msg, port);
	translator.ToJson();
}

Translator::Translator(const std::string & msg, int port) : m_message(msg), m_port(port)
{
}

void Translator::ToJson()
{
	m_jsonTree.put<int>("module", m_port);
	m_jsonTree.put<std::string>("type", "words");
	m_jsonTree.put<std::string>("data", m_message);
	std::stringstream s;
	boost::property_tree::write_json(s, m_jsonTree);
	GetData().at(0) = s.str();
	std::cout << GetData().at(0) << std::endl;
}
