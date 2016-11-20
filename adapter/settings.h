#pragma once
#include <string>
#include <vector>

class Settings
{
public:
	Settings(int argc, char **argv);
	std::string GetType(int i);
	int GetInputPort(int i);
	int GetOutputPort(int i);
	unsigned int GetAmount();

private:
	unsigned int m_amount;
	std::vector<std::string> m_type;
	std::vector<int> m_inputPorts;
	std::vector<int> m_outputPorts;
};