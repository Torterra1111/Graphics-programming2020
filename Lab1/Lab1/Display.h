#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	Display();  //Constructior
	~Display(); //destructor 
	void MakeDisplay();  //Creating the accualy display
	void swapBuff(); //Swap the buffer to displan on screen
	void NukeDisplay(float r, float g, float b, float a); //Clear display

	float getWidth() const { return _screenWidth; } //Getter for width
	float getHeight() const { return _screenHeight; } //Getter for Hight

private:

	void GiveError(std::string errorString); //Error handling
	
	GLenum error; //GLEnum error handling
	SDL_Window* _window; //holds pointer to out window
	SDL_GLContext _glcontext; //GLContext error handling
	float _screenWidth; //Stores screenwidth
	float _screenHeight; //Stores screen Height
};


