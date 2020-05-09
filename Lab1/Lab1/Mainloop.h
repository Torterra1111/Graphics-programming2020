#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"


enum class GameState { PLAY, EXIT }; //Game states for controling when to exit/play

class Mainloop
{
public:
	Mainloop(); //CONSTRUCTOR
	~Mainloop(); //DESTRUCTOR
	 
	void run();
	bool Collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);

private:

	void MakeSystems(); //Initilise everything
	void gameLoop();  //Main loop of play
	void TakeInput(); //Taking input from the player
	void update();  //Updating positions and such
	void drawGame(); //Draw everything
	void Playmusic(unsigned int source, glm::vec3 pos);

	void CreateToonLighting();
	void CreateExplodeShader();
	void CreateReflectShader();
	void CreatePhongLighting();

	glm::mat4 modelView; //ModelView
	
	Display _gameDisplay; //Holding the gamedisplay
	GameState _gameState; //Holding the state of the game (exit,play)
	Camera myCamera; //Holding the camera
	Audio AudioSource; //Holding the audio
	ALint state; //Holding the validation of openGL

	//Meshes for the models
	Mesh meshMonkey;
	Mesh meshArrow;
	Mesh meshShield;
	
	//Transforms to move models
	Transform Monkey;
	Transform Arrow;
	Transform Shield;

	//Textures for the models
	Texture BrickTex;
	Texture WaterTex;
	Texture SpongeTex;
	
	Shader shader; //Shader 
	Shader ToonShade; //Toonshader
	Shader ExplodeShade; //ExplodingShader
	Shader ReflectShade; //EviromentShader
	Shader PhongShade; //Phong Shader

	string input; //Input detection
	SDL_Event evnt; //input

	float playerturn = 0.0; //Controls where the player/shield is looking
	float playerRotx = 0.0; //Controls where the player/shield is rotated in X
	float playerRoty = 0.0; //Controls where the player/shield is rotated in Y
	float playerx = 0.0;    //Controls the X co-ordinate of the player
	float playery = 0.0;    //Controls the Y co-ordinate of the player

	float shieldPosx = 0.0; //Controls where the shield is placed in the X position
	float shieldpoxY = 0.0; //Controls where the shield in placed in the Y position
	float shieldRotx= 0.0;
	float shieldRoty= 0.0;
	float shieldRotz= 0.0;

	float arrowx = 3.0f;
	float arrowy = 3.0f;
	float arrowrot = 0.0f;

	float arrowmvx = 0.0f; //Movespeed in the X position
	float arrowmvy = 0.0f; //Movespeed in the Y position
	float Movespeed = 0.0f; //Movepseed extra
	int score = 0;
	bool dospawn;

	//Moneky go die die
	float explodie = 0.0;
	bool iskill = false;

	//Skybox
	void Skybox();
    GLuint skyboxVAO, skyboxVBO, cubemapTexture;
	vector<std::string> faces;
	Texture skybox;
	Shader shaderSkybox;


	unsigned int whistle; //Colision
	unsigned int backGroundMusic; //background
	unsigned int hitsound; //Hitsound
};

