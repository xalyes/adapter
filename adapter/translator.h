#pragma once

void TranslateMessage(const std::string& msg, int port);

class Translator
{
public:
	Translator(const std::string& msg, int port);
	void ToJson();

private:
	const std::string m_message;
	const int m_port;
	boost::property_tree::ptree m_jsonTree;
};