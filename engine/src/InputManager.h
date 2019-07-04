
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>

class InputManager
{
public:
	static InputManager* getInstance();

	void update();

	void pressKey(unsigned int t_keyID);
	void releaseKey(unsigned int t_keyID);
	bool isKeyDown(unsigned int t_keyID);
	bool isKeyPressed(unsigned int t_keyID);

	void setMouseCoords(glm::vec2 t_mouseCoords) { m_mouseCoords = t_mouseCoords; };
	glm::vec2 getMouseCoords() const { return m_mouseCoords; }
private:
	InputManager();
	~InputManager();
	InputManager(InputManager const&) = delete;
	InputManager& operator=(InputManager const&) = delete;

	static InputManager* m_instance;

	bool wasKeyDown(unsigned int t_keyID);

	std::unordered_map<unsigned int, bool> m_keyMap;
	std::unordered_map<unsigned int, bool> m_previousKeyMap;
	glm::vec2 m_mouseCoords;
};
#endif
