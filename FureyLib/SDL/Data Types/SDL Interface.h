
// SDL Asset Interface Script
// by Kyle Furey

#pragma once
#include "SDL.h"

// Include this heading to use the class
#include "SDL Interface.h"

// Inherited interface of new SDL assets.
class SDL_Interface
{
public:

	// DATA

	// The rectangle transform of this asset
	SDL_Rect* transform = nullptr;


	// CONSTRUCTOR AND DECONSTRUCTOR

	// Default constructor
	SDL_Interface() { }

	// Deconstructor
	~SDL_Interface()
	{
		Destroy();
	}


	// FUNCTIONS

	// Function used to render an asset to the screen
	virtual void Render() { }

	// Function used to safely deallocate an asset's memory
	virtual void Destroy()
	{
		delete transform;
		transform = nullptr;
	}
};


// OTHER FUNCTIONS

// Creates a new SDL_Rect (must be freed)
static SDL_Rect* NewRect(int x, int y, int w, int h)
{
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return rect;
}

// Creates a new SDL_Color
static SDL_Color NewColor(int r, int g, int b, int a = 255)
{
	SDL_Color color = SDL_Color();
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}
