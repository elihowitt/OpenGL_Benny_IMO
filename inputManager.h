#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include<SDL2\SDL.h>

class InputManager
{
private:
	InputManager();
	~InputManager();
protected:
private:
	static InputManager* sInstance;
	
	const Uint8* m_keyboardStates;
public:
	static InputManager* Instace();
	static void Release();

	bool KeyDown(SDL_Scancode scancode);

	void Update();
};

#endif // !INPUTMANAGER_H
