
#include "InputManager.h"

InputManager* InputManager::m_instance;

InputManager::InputManager() 
    : m_mouseCoords(0.0f)
{

}

InputManager::~InputManager()
{

}

InputManager* InputManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new InputManager();
		return m_instance;
	}

	// Point to same object (singleton pattern)
	return m_instance;
}

void InputManager::update() 
{
    // Loop through _keyMap using a for each loop, and copy it over to _previousKeyMap
    for (auto& it : m_keyMap) 
    {
        m_previousKeyMap[it.first] = it.second;
    }
}

void InputManager::pressKey(unsigned int t_keyID)
{
    // Here we are treating _keyMap as an associative array.
    // if keyID doesn't already exist in _keyMap, it will get added
    m_keyMap[t_keyID] = true;
}

void InputManager::releaseKey(unsigned int t_keyID)
{
    m_keyMap[t_keyID] = false;
}

bool InputManager::isKeyDown(unsigned int t_keyID)
{
    // We dont want to use the associative array approach here
    // because we don't want to create a key if it doesnt exist.
    // So we do it manually
    auto it = m_keyMap.find(t_keyID);
    if (it != m_keyMap.end()) 
    {
        // Found the key
        return it->second;
    } 
    else 
    {
        // Didn't find the key
        return false;
    }
}

bool InputManager::isKeyPressed(unsigned int t_keyID)
{
    // Check if it is pressed this frame, and wasn't pressed last frame
    if (isKeyDown(t_keyID) == true && wasKeyDown(t_keyID) == false)
    {
        return true;
    }
    return false;
}

bool InputManager::wasKeyDown(unsigned int t_keyID)
{
    // We dont want to use the associative array approach here
    // because we don't want to create a key if it doesnt exist.
    // So we do it manually
    auto it = m_previousKeyMap.find(t_keyID);
    if (it != m_previousKeyMap.end()) 
    {
        // Found the key
        return it->second;
    } 
    else 
    {
        // Didn't find the key
        return false;
    }
}
