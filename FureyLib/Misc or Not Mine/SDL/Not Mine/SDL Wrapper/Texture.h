
// SDL Texture Wrapper Class Script
// by Allen Cantin

#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Texture {
public:
	Texture() {
		srf = NULL;
		texture = NULL;
		area = { 0, 0, 0, 0};
		font = NULL;
	}
	Texture(const char* path, SDL_Renderer* renderer) {
		SetTexture(path, renderer);
		area = { 0, 0, 0, 0 };
	}
	~Texture() {
		SDL_FreeSurface(srf);
		SDL_DestroyTexture(texture);
		if (font) {
			TTF_CloseFont(font);
		}
	}
	void SetFont(const char* path, int size) {
		font = TTF_OpenFont(path, size);
	}
	void SetText(SDL_Renderer* renderer, const char* text, int r, int g, int b) {
		srf = TTF_RenderText_Solid(font, text, { unsigned char(r), unsigned char(g), unsigned char(b), 255 });
		texture = SDL_CreateTextureFromSurface(renderer, srf);
	}
	void SetCoordinates(int x, int y) {
		area.x = x;
		area.y = y;
	}
	void SetDimensions(int w, int h) {
		area.w = w;
		area.h = h;
	}
	void SetTexture(const char* path, SDL_Renderer* renderer) {
		srf = SDL_LoadBMP(path);
		texture = SDL_CreateTextureFromSurface(renderer, srf);
	}
	SDL_Texture* GetTexture() {
		return texture;
	}
	SDL_Rect* GetArea() {
		return &area;
	}

private:
	SDL_Surface* srf;
	SDL_Texture* texture;
	SDL_Rect area;
	TTF_Font* font;
};