#pragma once

#include <string>
#include <SDL2\SDL.h>

class Display
{
public:
	Display(int windowWidth, int windowHeight, const std::string& windowName);
	void Clear(float r, float g, float b, float a);
	void SwapBuffers();
	bool IsClosed();
	~Display();

private:
	SDL_Window* m_Window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

