#include "Display.h"

Display::Display()
{
	_window = nullptr; 
	_screenHeight = 768;
	_screenWidth = 1024;
}

Display::~Display()
{
	SDL_GL_DeleteContext(_glcontext); //Destroys everything on desconstruct
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Display::NukeDisplay(float r, float g, float b, float a)
{
	glClearColor(r,g,b,a); //Clears colour buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::GiveError(std::string errorString) //If there is an error, this is what is sent to the consol
{
	std::cout << errorString << std::endl;
	std::cout << "Press any key to exit";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void Display::swapBuff()
{
	SDL_GL_SwapWindow(_window); //Swaps the buffer for displaying content on the screen
}

void Display::MakeDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initialise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);  //Red colour buffer, bit size
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); //Green colour buffer, bit size
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); //Blue colour buffer, bit size
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Output is single or double buffered. True or false 

	_window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)_screenWidth, (int)_screenHeight, SDL_WINDOW_OPENGL); //Creates the window

	if (_window == nullptr) //If no window is found. Handle error
	{
		
		GiveError("error, Window did not create!");
	}
	
	_glcontext = SDL_GL_CreateContext(_window);
	if (_glcontext == nullptr)  //If no glcontext is found. Handle error
	{
		GiveError("Error! glcontext did not create!");
	}
	
	error = glewInit();
	if (error != GLEW_OK)  //If no glenum is found. Handle error
	{
		GiveError("Error! Glenum didn not create");
	}
	
	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);//Clears the colour
}
