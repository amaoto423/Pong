#include<SDL.h>
#include"game.h"

const float thickness = 15;
const float ballsize = 15;
const float paddleheight = 100;
const float paddlewidth = 15;
Game::Game() :mIsRunning(1) {

}

bool Game::Initialize() {
	bool a = SDL_Init(SDL_INIT_EVERYTHING);
	if (a != 0) {
		SDL_Log("SDL cant be initialized %s", SDL_GetError());
		return false;
	}
	mWindow=SDL_CreateWindow(
		"Pong",
		100,
		100,
		1024,
		768,
		0
		);
	if (!mWindow) {
		SDL_Log("Window cant be created %s", SDL_GetError());
		return false;

	}
	mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Renderer cant be initialized %s", SDL_GetError());
		return false;
	}

	return true;

}

void Game::ProcessInput() {
	
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			mIsRunning = false;
		}
	}
	auto key_count = 0;
	auto key_state = SDL_GetKeyboardState(&key_count);

	if (key_state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
	float speed=0;
	if(key_state[SDL_SCANCODE_W]){
		speed -= 200.0f;
	}
	if (key_state[SDL_SCANCODE_S]) {
		speed += 200.0f;
	}
	PaddleSpeed.y = speed;
}

void Game::Runloop() {
	while (mIsRunning) {
		ProcessInput();
		GenerateOutput();
		UpdateGame();
	}
}

void Game::ShutDown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
	SDL_RenderClear(mRenderer);
	SDL_Rect RightWall = { 1024-thickness,0,thickness,768 };
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(mRenderer, &RightWall);
	SDL_Rect UpWall = { 0,0,1024,thickness };
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(mRenderer, &UpWall);
	SDL_Rect DownWall = { 0,768 - thickness,1024,thickness };
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	SDL_RenderFillRect(mRenderer, &DownWall);
	
	SDL_Rect Ball = { BallPos.x, BallPos.y, ballsize, ballsize };
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderFillRect(mRenderer, &Ball);
	
	SDL_Rect Paddle = { PaddlePos.x,PaddlePos.y,paddlewidth,paddleheight};
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(mRenderer, &Paddle);




	SDL_RenderPresent(mRenderer);

}

void Game::UpdateGame() {
	float deltatime=(SDL_GetTicks() - thickcount)/1000.0f;
	thickcount = SDL_GetTicks();

	PaddlePos.y += PaddleSpeed.y * deltatime;
	if (PaddlePos.y < thickness) {
		PaddlePos.y = thickness;
	}
	if (PaddlePos.y > 768 - thickness-paddleheight) {
		PaddlePos.y = 768 - thickness-paddleheight;
	}
	
	
	if (BallPos.x > 1024 - thickness-ballsize && BallSpeed.x > 0) {
		BallSpeed.x *= -1;
	}
	if (BallPos.y < thickness && BallSpeed.y < 0) {
		BallSpeed.y *= -1;
	}
	if (BallPos.y >768- thickness-ballsize && BallSpeed.y > 0) {
		BallSpeed.y *= -1;
	}
	if (BallPos.y < PaddlePos.y + paddleheight && BallPos.y > PaddlePos.y && BallPos.x < 10 + thickness && BallSpeed.x < 0) {
		BallSpeed.x *= -1;
	}




	BallPos.x += BallSpeed.x * deltatime;
	BallPos.y += BallSpeed.y * deltatime;



}