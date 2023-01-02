#pragma once
#include<SDL.h>
struct Vector2 {
	float x;
	float y;
};
class Game {
public:
	Game();
	bool Initialize();
	void Runloop();
	void ShutDown();
private:
	void UpdateGame();
	void ProcessInput();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	Vector2 BallPos={300,300};
	Vector2 PaddlePos={10,360};
	Vector2 BallSpeed={200,200};
	Vector2 PaddleSpeed={0,0};
	float thickcount = SDL_GetTicks();
};