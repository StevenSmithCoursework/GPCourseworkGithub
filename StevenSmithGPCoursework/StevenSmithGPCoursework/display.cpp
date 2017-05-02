#include "display.h"
#include <GL\glew.h>
#include <iostream>


Display::Display(int windowWidth, int windowHeight, const std::string& windowName)
{
	//Initialises everything for SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Sets attributes to help with displaying colours etc
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Creates the window and context and binds the information to the relevant variable
	m_Window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_Window);

	//Initialises glew and an error check is performed
	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialise" << std::endl;
	}

	//Sets closed to false
	m_isClosed = false;

	//Enables a depth test and face culling to help with drawing objects within the window
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display()
{
	//Clears any information that was created within the constructor
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	//Clears the display screen
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed()
{
	//Used to check the status of m_isClosed
	return m_isClosed;
}

void Display::SwapBuffers()
{
	//Swaps the buffers and checks if the window has been closed
	SDL_GL_SwapWindow(m_Window);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			m_isClosed = true;
		}
	}
}