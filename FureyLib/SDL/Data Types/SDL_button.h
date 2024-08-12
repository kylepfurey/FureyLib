
// SDL Button Script
// by Kyle Furey

// REQUIREMENTS: SDL_interface.h

#pragma once
#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_interface.h"

// Include this heading to use the class
#include "SDL_button.h"

// Image and text that can detect overlapping used for SDL programs.
class SDL_Button : public SDL_Interface
{
private:

	// PRIVATE DATA

	// The stored renderer (not freed on deconstruction, just a copy)
	SDL_Renderer* renderer = nullptr;

	// The texture for the button
	SDL_Texture* image = nullptr;

	// Whether we are drawing a rectangle instead of an image
	SDL_Color rect_color = SDL_Color();
	bool outline_rect = false;
	bool created_rect = false;

	// The font for the text on the button
	TTF_Font* font = nullptr;
	bool created_font = false;

	// The texture for the text on the button
	SDL_Texture* text = nullptr;
	SDL_Rect* text_transform = nullptr;
	bool created_text = false;

	// Image string and text string
	std::string image_string = "";
	std::string text_string = "";
	SDL_Color text_SDL_color = SDL_Color();

public:

	// CONSTRUCTORS AND DECONSTRUCTOR

	// Default constructor
	SDL_Button() { }

	// Rect constructor
	SDL_Button(SDL_Renderer* window_renderer, SDL_Color color, bool outline, int x, int y, int w, int h)
	{
		// Store renderer
		renderer = window_renderer;


		// Create image
		created_rect = true;

		outline_rect = outline;

		rect_color = color;


		// Create transform
		transform = NewRect(x, y, w, h);
	}

	// Rect, font, and text constructor
	SDL_Button(SDL_Renderer* window_renderer, SDL_Color color, bool outline, int x, int y, int w, int h, std::string font_file_name, int font_size, std::string displayed_text, SDL_Color text_color)
	{
		// Store renderer
		renderer = window_renderer;


		// Create image
		created_rect = true;

		outline_rect = outline;

		rect_color = color;


		// Create transform
		transform = NewRect(x, y, w, h);


		// Create font
		created_font = true;

		font = TTF_OpenFont(font_file_name.c_str(), font_size);


		// Create text
		created_text = true;

		text_transform = NewRect(transform->x, transform->y, transform->w, transform->h);

		text_string = displayed_text;

		text_SDL_color = text_color;

		SDL_Surface* temp_surface = TTF_RenderText_Solid(font, displayed_text.c_str(), NewColor(text_color.r, text_color.g, text_color.b, text_color.a));

		text = SDL_CreateTextureFromSurface(renderer, temp_surface);

		SDL_FreeSurface(temp_surface);
	}

	// Rect and text constructor
	SDL_Button(SDL_Renderer* window_renderer, SDL_Color color, bool outline, int x, int y, int w, int h, TTF_Font* existing_font, std::string displayed_text, SDL_Color text_color)
	{
		// Store renderer
		renderer = window_renderer;


		// Create image
		created_rect = true;

		outline_rect = outline;

		rect_color = color;


		// Create transform
		transform = NewRect(x, y, w, h);


		// Load font
		font = existing_font;


		// Create text
		created_text = true;

		text_transform = NewRect(transform->x, transform->y, transform->w, transform->h);

		text_string = displayed_text;

		text_SDL_color = text_color;

		SDL_Surface* temp_surface = TTF_RenderText_Solid(font, displayed_text.c_str(), NewColor(text_color.r, text_color.g, text_color.b, text_color.a));

		text = SDL_CreateTextureFromSurface(renderer, temp_surface);

		SDL_FreeSurface(temp_surface);
	}

	// Image constructor
	SDL_Button(SDL_Renderer* window_renderer, std::string image_file_name, int x, int y, int scaleX, int scaleY)
	{
		// Store renderer
		renderer = window_renderer;


		// Create image
		image_string = image_file_name;

		SDL_Surface* temp_surface = SDL_LoadBMP_RW(SDL_RWFromFile(image_file_name.c_str(), "rb"), 1);

		image = SDL_CreateTextureFromSurface(renderer, temp_surface);


		// Create transform
		transform = NewRect(x, y, temp_surface->w * scaleX, temp_surface->h * scaleY);

		SDL_FreeSurface(temp_surface);
	}

	// Image, font, and text constructor
	SDL_Button(SDL_Renderer* window_renderer, std::string image_file_name, int x, int y, int scaleX, int scaleY, std::string font_file_name, int font_size, std::string displayed_text, SDL_Color text_color)
	{
		// Store renderer
		renderer = window_renderer;


		// Create image
		image_string = image_file_name;

		SDL_Surface* temp_surface = SDL_LoadBMP_RW(SDL_RWFromFile(image_file_name.c_str(), "rb"), 1);

		image = SDL_CreateTextureFromSurface(renderer, temp_surface);


		// Create transform
		transform = NewRect(x, y, temp_surface->w * scaleX, temp_surface->h * scaleY);

		SDL_FreeSurface(temp_surface);


		// Create font
		created_font = true;

		font = TTF_OpenFont(font_file_name.c_str(), font_size);


		// Create text
		created_text = true;

		text_transform = NewRect(transform->x, transform->y, transform->w, transform->h);

		text_string = displayed_text;

		text_SDL_color = text_color;

		temp_surface = TTF_RenderText_Solid(font, displayed_text.c_str(), NewColor(text_color.r, text_color.g, text_color.b, text_color.a));

		text = SDL_CreateTextureFromSurface(renderer, temp_surface);

		SDL_FreeSurface(temp_surface);
	}

	// Image and text constructor
	SDL_Button(SDL_Renderer* window_renderer, std::string image_file_name, int x, int y, int scaleX, int scaleY, TTF_Font* existing_font, std::string displayed_text, SDL_Color text_color)
	{
		// Store renderer
		renderer = window_renderer;


		// Create image
		image_string = image_file_name;

		SDL_Surface* temp_surface = SDL_LoadBMP_RW(SDL_RWFromFile(image_file_name.c_str(), "rb"), 1);

		image = SDL_CreateTextureFromSurface(renderer, temp_surface);


		// Create transform
		transform = NewRect(x, y, temp_surface->w * scaleX, temp_surface->h * scaleY);

		SDL_FreeSurface(temp_surface);


		// Load font
		font = existing_font;


		// Create text
		created_text = true;

		text_transform = NewRect(transform->x, transform->y, transform->w, transform->h);

		text_string = displayed_text;

		text_SDL_color = text_color;

		temp_surface = TTF_RenderText_Solid(font, displayed_text.c_str(), NewColor(text_color.r, text_color.g, text_color.b, text_color.a));

		text = SDL_CreateTextureFromSurface(renderer, temp_surface);

		SDL_FreeSurface(temp_surface);
	}

	// Deconstructor (MUST BE CALLED BEFORE SDL_QUIT AND TTF_QUIT)
	~SDL_Button()
	{
		Destroy();
	}


	// FUNCTIONS

	// Prepares to render all elements of this button
	void Render() override
	{
		// Render image
		if (!created_rect)
		{
			SDL_RenderCopy(renderer, image, NULL, transform);
		}
		else
		{
			SDL_Color* previous_color = new SDL_Color();

			SDL_GetRenderDrawColor(renderer, &previous_color->r, &previous_color->g, &previous_color->b, &previous_color->a);

			SDL_SetRenderDrawColor(renderer, rect_color.r, rect_color.g, rect_color.b, rect_color.a);

			if (!outline_rect)
			{
				SDL_RenderFillRect(renderer, transform);
			}
			else
			{
				SDL_RenderDrawRect(renderer, transform);
			}

			SDL_SetRenderDrawColor(renderer, previous_color->r, previous_color->g, previous_color->b, previous_color->a);

			delete previous_color;

			previous_color = nullptr;
		}

		// Render text
		if (created_text)
		{
			SDL_RenderCopy(renderer, text, NULL, text_transform);
		}
	}

	// Check if this button is overlapped by the given coordinates
	bool IsOverlapped(int x, int y)
	{
		return x >= transform->x && x <= transform->x + transform->w && y >= transform->y && y <= transform->y + transform->h;
	}

	// Get the index of the first overlapped button in a vector of buttons, or -1 if none are overlapped
	static int GetOverlapped(std::vector<SDL_Button*> buttons, int x, int y)
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			if (buttons[i]->IsOverlapped(x, y))
			{
				return i;
			}
		}

		return -1;
	}

	// Gets the current color of this button if it was constructed using a fill constructor
	SDL_Color GetColor()
	{
		if (created_rect)
		{
			return rect_color;
		}

		return SDL_Color();
	}

	// Gets whether the this button is outlined if it was constructed using a fill constructor
	bool GetOutlined()
	{
		if (created_rect)
		{
			return outline_rect;
		}

		return false;
	}

	// Sets a new color for this button if it was constructed using a fill constructor
	void SetColor(SDL_Color color, bool outline)
	{
		if (created_rect)
		{
			rect_color = color;

			outline_rect = outline;
		}
	}

	// Gets the current image directory string for this button if it was constructed using an image constructor
	std::string GetImage()
	{
		if (!created_rect)
		{
			return image_string;
		}

		return "";
	}

	// Sets a new image for this button if it was constructed using an image constructor
	void SetImage(std::string image_file_name)
	{
		if (!created_rect)
		{
			SDL_DestroyTexture(image);

			image_string = image_file_name;

			SDL_Surface* temp_surface = SDL_LoadBMP_RW(SDL_RWFromFile(image_file_name.c_str(), "rb"), 1);

			image = SDL_CreateTextureFromSurface(renderer, temp_surface);

			SDL_FreeSurface(temp_surface);
		}
	}

	// Gets the current text string for this button if it was constructed using a text constructor
	std::string GetText()
	{
		if (created_text)
		{
			return text_string;
		}

		return "";
	}

	// Gets the current text color for this button if it was constructed using a text constructor
	SDL_Color GetTextColor()
	{
		if (created_text)
		{
			return text_SDL_color;
		}

		return SDL_Color();
	}

	// Sets new text for this button if it was constructed using a text constructor
	void SetText(std::string displayed_text, SDL_Color text_color)
	{
		if (created_text)
		{
			text_transform = NewRect(transform->x, transform->y, transform->w, transform->h);

			text_string = displayed_text;

			text_SDL_color = text_color;

			SDL_Surface* temp_surface = TTF_RenderText_Solid(font, displayed_text.c_str(), NewColor(text_color.r, text_color.g, text_color.b, text_color.a));

			text = SDL_CreateTextureFromSurface(renderer, temp_surface);

			SDL_FreeSurface(temp_surface);
		}
	}

	// Sets a new font and text for this button if it was constructed using a text and font constructor
	void SetText(std::string displayed_text, SDL_Color text_color, std::string font_file_name, int font_size)
	{
		if (created_text && created_font)
		{
			TTF_CloseFont(font);

			font = TTF_OpenFont(font_file_name.c_str(), font_size);

			text_transform = NewRect(transform->x, transform->y, transform->w, transform->h);

			text_string = displayed_text;

			text_SDL_color = text_color;

			SDL_Surface* temp_surface = TTF_RenderText_Solid(font, displayed_text.c_str(), NewColor(text_color.r, text_color.g, text_color.b, text_color.a));

			text = SDL_CreateTextureFromSurface(renderer, temp_surface);

			SDL_FreeSurface(temp_surface);
		}
	}

	// Sets a new font and text for this button if it was constructed using a text constructor
	void SetText(std::string displayed_text, SDL_Color text_color, TTF_Font* existing_font)
	{
		if (created_text && !created_font)
		{
			font = existing_font;

			text_transform = NewRect(transform->x, transform->y, transform->w, transform->h);

			text_string = displayed_text;

			text_SDL_color = text_color;

			SDL_Surface* temp_surface = TTF_RenderText_Solid(font, displayed_text.c_str(), NewColor(text_color.r, text_color.g, text_color.b, text_color.a));

			text = SDL_CreateTextureFromSurface(renderer, temp_surface);

			SDL_FreeSurface(temp_surface);
		}
	}

	// Deallocates this button (MUST BE CALLED BEFORE SDL_QUIT AND TTF_QUIT)
	void Destroy() override
	{
		// Deallocate transform
		delete transform;

		// Deallocate image
		SDL_DestroyTexture(image);

		// Deallocate font
		if (created_font)
		{
			TTF_CloseFont(font);
		}

		// Deallocate text
		if (created_text)
		{
			delete text_transform;

			SDL_DestroyTexture(text);
		}

		// Mark pointers as null
		renderer = nullptr;
		image = nullptr;
		font = nullptr;
		text = nullptr;
		text_transform = nullptr;
	}

	// Resets the button to another button
	SDL_Button& Reset(SDL_Button new_button)
	{
		Destroy();

		*this = new_button;
	}
};
