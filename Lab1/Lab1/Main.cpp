#include <iostream>
#include "Mainloop.h"

int main(int argc, char** argv) //arguments used to call SDL main
{
	Mainloop mainloop; //Main constructor
	mainloop.run(); //calls the "run()" function to begin the game

	return 0;

}
