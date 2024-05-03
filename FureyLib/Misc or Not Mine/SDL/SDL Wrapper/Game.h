
// SDL Game Wrapper Class
// by Allen Cantin

#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Texture.h"
#include <functional>
#include <vector>
class Game {
	
public:
	Game(const char* title) {
		//initialize libraries
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		//Initialize renderer color
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
	~Game() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);

		for (int i = 0; i < staticGameTextures.size(); i++) {
			SDL_DestroyTexture(staticGameTextures[i]->GetTexture());
		}
		for (int i = 0; i < dynamicGameTextures.size(); i++) {
			SDL_DestroyTexture(dynamicGameTextures[i]->GetTexture());
		}

		TTF_Quit();
		SDL_Quit();
	}
	void SubscribeInputEvent(std::function<void(SDL_Event*)> f) {
		inputEventHandler.push_back(f);
	}
	void SubscribeTick(std::function<void()> f) {
		tickHandler.push_back(f);
	}
	void StartGame() {
		//apply static textures
		for (int i = 0; i < staticGameTextures.size(); i++) {
			const SDL_Rect rect = *staticGameTextures[i]->GetArea();
			SDL_RenderCopy(renderer, staticGameTextures[i]->GetTexture(), NULL, &rect);
		}

		SDL_UpdateWindowSurface(window);
		RunGame();
	}
	SDL_Renderer* GetRenderer() {
		return renderer;
	}
	SDL_Window* GetWindow() {
		return window;
	}
	void AddStaticGameTexture(Texture* texture) {
		staticGameTextures.push_back(texture);
	}
	void AddDynamicGameTexture(Texture* texture) {
		dynamicGameTextures.push_back(texture);
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	const int width = 800;
	const int height = 600;
	std::vector<std::function<void(SDL_Event*)>> inputEventHandler;
	std::vector<std::function<void()>> tickHandler;
	std::vector<Texture*> staticGameTextures; //for textures that never move or change
	std::vector<Texture*> dynamicGameTextures; //for textures that move and/or change

	void ProcessEvents(SDL_Event* e, bool* exit) {
		if (e->type == SDL_QUIT) {
			*exit = true;
			return;
		}
		for (int i = 0; i < inputEventHandler.size(); i++) {
			inputEventHandler[i](e);
		}
	}

	void Tick() {
		for (int i = 0; i < tickHandler.size(); i++) {
			tickHandler[i]();
		}
		SDL_RenderPresent(renderer);
	}

	void RunGame() {
		SDL_Event e;
		bool quit = false;
		while (quit == false) {
			while (SDL_PollEvent(&e)) {
				ProcessEvents(&e, &quit);
			}
			Tick();
		}
	}
};