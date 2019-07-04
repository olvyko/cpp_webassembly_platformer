
#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <vector>

class IOManager
{
public:
	static IOManager* getInstance();
	bool readFileToBuffer(std::string t_filePath, std::vector<unsigned char>& t_buffer);
	bool readFileToBuffer(std::string t_filePath, std::string& t_buffer);

private:
	IOManager();
	~IOManager();

	IOManager(IOManager const&) = delete;
	IOManager& operator=(IOManager const&) = delete;

	static IOManager* m_instance;
};

#endif // IO_MANAGER_H