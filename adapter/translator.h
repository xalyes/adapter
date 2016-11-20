#pragma once

void TranslateMessage(const std::string& msg, unsigned int module, const std::string& type);

class Translator
{
public:
	Translator(const std::string& msg, unsigned int module, const std::string& type);
	void ToJson();

private:
	const std::string m_message;
	const int m_module;
	boost::property_tree::ptree m_jsonTree;
	const std::string m_type;
};