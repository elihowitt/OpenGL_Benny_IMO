#include "inputManager.h"

InputManager* InputManager::sInstance = NULL;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

InputManager * InputManager::Instace()
{
	if (sInstance == NULL)
		sInstance = new InputManager();

	return sInstance;
}

void InputManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

bool InputManager::KeyDown(SDL_Scancode scancode)
{
	return m_keyboardStates[scancode];
}

void InputManager::Update()
{
	m_keyboardStates = SDL_GetKeyboardState(NULL);
}
