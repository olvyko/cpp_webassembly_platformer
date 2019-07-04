#include "IOManager.h"

#include <fstream>

IOManager* IOManager::m_instance;

IOManager::IOManager()
{
}

IOManager::~IOManager()
{
}

IOManager* IOManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new IOManager();
		return m_instance;
	}

	// Point to same object (singleton pattern)
	return m_instance;
}

bool IOManager::readFileToBuffer(std::string t_filePath, std::vector<unsigned char>& t_buffer)
{
	std::ifstream file(t_filePath, std::ios::binary);
	if (file.fail()) 
	{
		perror(t_filePath.c_str());
		return false;
	}

	//seek to the end
	file.seekg(0, std::ios::end);

	//Get the file size
	unsigned int fileSize = (unsigned int)file.tellg();
	file.seekg(0, std::ios::beg);

	//Reduce the file size by any header bytes that might be present
	fileSize -= (unsigned int)file.tellg();

	t_buffer.resize(fileSize);
	file.read((char *)&(t_buffer[0]), fileSize);
	file.close();

	return true;
}

bool IOManager::readFileToBuffer(std::string t_filePath, std::string& t_buffer)
{
	std::ifstream file(t_filePath, std::ios::binary);
	if (file.fail()) 
	{
		perror(t_filePath.c_str());
		return false;
	}

	//seek to the end
	file.seekg(0, std::ios::end);

	//Get the file size
	unsigned int fileSize = (unsigned int)file.tellg();
	file.seekg(0, std::ios::beg);

	//Reduce the file size by any header bytes that might be present
	fileSize -= (unsigned int)file.tellg();

	t_buffer.resize(fileSize);
	file.read((char *)&(t_buffer[0]), fileSize);
	file.close();

	return true;
}