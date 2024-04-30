
// SDL Macro Library Script
// by Kyle Furey

#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <vector>
#include <chrono>
#include <ctime>  

// Include this heading to use the library
#include "SDL Macros.h"


// I===========================================================================================================================================================================I
//
//																					WINDOWS
// 
// I===========================================================================================================================================================================I



// I==============================================================================I
//  Creates an SDL window with a name, a width and height, and a background color.
//  You must CLOSE_WINDOW before the program ends!
//  EXAMPLE:  CREATE_WINDOW("SDL Program", 1920, 1080, 255, 255, 255);
// I==============================================================================I
#define CREATE_WINDOW(name, width, height, red, green, blue) \
\
SDL_Window* window; \
\
SDL_Renderer* renderer; \
\
SDL_Surface* temp_surface; \
\
vector<SDL_Texture*> textures = vector<SDL_Texture*>(); \
\
vector<SDL_Rect*> transforms = vector<SDL_Rect*>(); \
\
SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); \
\
window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_ENABLE); \
\
renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); \
\
SDL_SetRenderDrawColor(renderer, red, green, blue, 255); \
\
SDL_Surface* window_surface = SDL_GetWindowSurface(window); \
\
const int window_width = window_surface->w; \
\
const int window_height = window_surface->h;


// I============================================I
//  Renders all created textures.
//  Automatically called at the end of the loop.
// I============================================I
#define RENDER_ALL \
\
for (int i = 0; i < textures.size(); i++) \
{ \
	SDL_RenderCopy(renderer, textures[i], NULL, transforms[i]); \
}


// I=======================I
//  Updates the SDL window.
// I=======================I
#define UPDATE_WINDOW \
\
RENDER_ALL; \
\
SDL_RenderPresent(renderer); \
\
SDL_RenderClear(renderer);


// I====================================================I
//  Frees the SDL window's memory and closes the window.
// I====================================================I
#define CLOSE_WINDOW \
\
SDL_DestroyRenderer(renderer); \
\
SDL_DestroyWindow(window); \
\
SDL_Quit();



// I===========================================================================================================================================================================I
//
//																				DELTA TIME
// 
// I===========================================================================================================================================================================I



// I================================I
// Initialize delta time variables.
// I================================I
#define INIT_DELTA_TIME \
\
/* The current elapsed time in clock time (not in seconds) */ \
std::clock_t clock_time = std::clock(); \
\
/* The time in seconds since the last time the loop was called */ \
double delta_time = 0; \
\
/* The number of loops that has occured since delta time was initialized */ \
int loop_count = 0;


// I========================================I
//  Updates the delta time variable.
//  Call this at the start of the main loop.
//  Requires delta time to be initialized.
//  Access delta time by using delta_time.
// I========================================I
#define UPDATE_DELTA_TIME \
\
delta_time = (std::clock() - clock_time) / (double)CLOCKS_PER_SEC;\
\
clock_time = std::clock(); \
\
loop_count++;


// I======================================I
//  Gets the elapsed time of a loop.
//  Requires delta time to be initialized.
// I======================================I
#define elapsed_time (clock_time / (double)CLOCKS_PER_SEC)


// I========================================I
//  Gets the frame rate of a loop.
//  Requires delta time to be initialized.
// I========================================I
#define frame_rate (loop_count / elapsed_time)



// I===========================================================================================================================================================================I
//
//																					LOOPING
// 
// I===========================================================================================================================================================================I



// I========================================================================I
//  Begins an SDL loop that will continue forever until LOOP_EXIT is called.
//  You need to mark the end of the loop with LOOP_END.
//  You need to have logic to exit the loop with LOOP_EXIT.
//  It is recommended to use curly braces to mark the scope of the loop.
// I========================================================================I
#define LOOP_BEGIN \
\
INIT_DELTA_TIME; \
\
SDL_Event SDL_event; \
\
bool quit = false; \
\
while (!quit) \
{ \
	while (SDL_PollEvent(&SDL_event)) \
	{ \
		UPDATE_DELTA_TIME; \
		if (SDL_event.type == SDL_QUIT) \
		{ \
			quit = true; \
			break; \
		}


// I=====================================================================I
//  Marks the end of an SDL loop created with LOOP_BEGIN.
//  Automatically updates the window when the end of the loop is reached.
// I=====================================================================I
#define LOOP_END \
\
		UPDATE_WINDOW; \
	} \
}


// I==============================================I
//  Immediately exits an SDL loop.
//  Must be placed within LOOP_BEGIN and LOOP_END.
// I==============================================I
#define LOOP_QUIT \
\
quit = true; \
\
break; \


// I==============================================I
//  Restarts an SDL loop.
//  Must be placed within LOOP_BEGIN and LOOP_END.
// I==============================================I
#define LOOP_RESTART continue;



// I===========================================================================================================================================================================I
//
//																					IMAGES
// 
// I===========================================================================================================================================================================I



// Creates a new SDL_Rect (must be freed)
SDL_Rect* new_rect(int x, int y, int w, int h)
{
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	return rect;
}


// I=========================================================================================================================I
//  Creates an image from the given bitmap image file name and creates a variable for it named the given image variable name.
//  Sets its starting position and scale to the given X and Y parameters and creates a variable for its transform.
//  You must REMOVE_IMAGE(image_variable_name) before the program ends!
//  EXAMPLE:  INSERT_MAGE("Image.bmp", image, image_transform, 500, 500, 1, 1);
// I=========================================================================================================================I
#define INSERT_IMAGE(image_file_name, image_variable_name, transform_variable_name, x, y, scaleX, scaleY) \
\
temp_surface = SDL_LoadBMP(image_file_name); \
\
SDL_Rect* transform_variable_name = new_rect(x, y, temp_surface->w * scaleX, temp_surface->h * scaleY); \
\
SDL_Texture* image_variable_name = SDL_CreateTextureFromSurface(renderer, temp_surface); \
\
textures.push_back(image_variable_name); \
\
transforms.push_back(transform_variable_name); \
\
SDL_FreeSurface(temp_surface); \
\
SDL_RenderCopy(renderer, image_variable_name, NULL, transform_variable_name);


// I===========================================================================================================================I
//  Recreates an image from the given bitmap image file name and creates a variable for it named the given image variable name.
//  EXAMPLE:  REPLACE_IMAGE("Image.bmp", image, image_transform);
// I===========================================================================================================================I
#define REPLACE_IMAGE(image_file_name, image_variable_name, transform_variable_name) \
\
SDL_DestroyTexture(image_variable_name); \
\
temp_surface = SDL_LoadBMP(image_file_name); \
\
image_variable_name = SDL_CreateTextureFromSurface(renderer, temp_surface); \
\
SDL_FreeSurface(temp_surface); \
\
SDL_RenderCopy(renderer, image_variable_name, NULL, transform_variable_name);


// I===============================================I
//  Frees the given image variable's memory.
//  EXAMPLE:  REMOVE_IMAGE(image, image_transform);
// I===============================================I
#define REMOVE_IMAGE(image_variable_name, transform_variable_name) \
\
SDL_DestroyTexture(image_variable_name); \
\
delete transform_variable_name; \



// I===========================================================================================================================================================================I
//
//																				WIDTH AND HEIGHT
// 
// I===========================================================================================================================================================================I



// I========================I
//  Gets the window's width.
// I========================I
#define WINDOW_WIDTH (window_surface->w)


// I=========================I
//  Gets the window's height.
// I=========================I
#define WINDOW_HEIGHT (window_surface->h)


// I=======================I
//  Gets an image's width.
//  EXAMPLE:  WIDTH(image);
// I=======================I
#define WIDTH(transform_variable_name) (transform_variable_name->w)


// I========================I
//  Gets an image's height.
//  EXAMPLE:  HEIGHT(image);
// I========================I
#define HEIGHT(transform_variable_name) (transform_variable_name->h)


// I===================================================I
//  Gets a image's width while it is being constructed.
// I===================================================I
#define GET_WIDTH (temp_surface->w)


// I====================================================I
//  Gets a image's height while it is being constructed.
// I====================================================I
#define GET_HEIGHT (temp_surface->h)



// I===========================================================================================================================================================================I
//
//																				KEYBOARD INPUT
// 
// I===========================================================================================================================================================================I



// I=====================================================================I
//  Checks for the given keyboard input.
//  Uses the SDLK_KEYTYPE enum as the first parameter.
//  The second parameter is a bool to check when the key is released.
//  You need to mark the end of the input check with INPUT_END_KEY.
//  It is recommended to use curly braces to mark the scope of the input.
//  EXAMPLE:  INPUT_KEY(SDLK_SPACE, false); {
// I=====================================================================I
#define INPUT_KEY(SDLK_KEYTYPE, on_key_up) \
\
if (SDL_event.type == on_key_up ? SDL_KEYUP : SDL_KEYDOWN) \
{ \
	if (SDL_event.key.keysym.sym == SDLK_KEYTYPE) \
	{


// I=====================================================================I
//  Checks for when the given keyboard input is pressed down.
//  Uses the SDLK_KEYTYPE enum as the parameter.
//  You need to mark the end of the input check with INPUT_END_KEY.
//  It is recommended to use curly braces to mark the scope of the input.
//  EXAMPLE:  INPUT_KEY_DOWN(SDLK_SPACE); {
// I=====================================================================I
#define INPUT_KEY_DOWN(SDLK_KEYTYPE) \
\
if (SDL_event.type == SDL_KEYDOWN) \
{ \
	if (SDL_event.key.keysym.sym == SDLK_KEYTYPE) \
	{


// I================================================================================================================================================I
//  Checks for when the given keyboard input is pressed down following other keyboard checks.
//  Uses the SDLK_KEYTYPE enum as the first parameter.
//  You need to mark the start and end of the input check with INPUT_KEY(SDLK_KEYTYPE) or INPUT_KEY(SDLK_KEYTYPE, on_key_up) and then INPUT_END_KEY.
//  It is recommended to use curly braces to mark the scope of the input.
//  EXAMPLE:  INPUT_ELSE_KEY(SDLK_W); {
// I================================================================================================================================================I
#define INPUT_ELSE_KEY(SDLK_KEYTYPE) \
\
} \
else if (SDL_event.key.keysym.sym == SDLK_KEYTYPE) \
{


// I========================================I
//  Marks the end of a keyboard input check.
// I========================================I
#define INPUT_END_KEY \
\
	} \
}



// I===========================================================================================================================================================================I
//
//																				MOUSE INPUT
// 
// I===========================================================================================================================================================================I



// I======================================================================I
//  Checks for mouse movement input.
//  You need to mark the end of the input check with INPUT_END_MOUSE_MOVE.
//  You can access the mouse movement data with the mouse variable.
//  It is recommended to use curly braces to mark the scope of the input.
// I======================================================================I
#define INPUT_MOUSE_MOVE \
\
if (SDL_event.type == SDL_MOUSEMOTION) \
{ \
/* Stores the recent data of mouse movement */ \
	SDL_MouseMotionEvent mouse = SDL_event.motion;


// I==========================================================================================================I
//  Checks for mouse movement input following other input checks.
//  You need to mark the start and end of the input check with INPUT_MOUSE_MOVE and then INPUT_END_MOUSE_MOVE.
//  You can access the mouse movement data with the mouse variable.
//  It is recommended to use curly braces to mark the scope of the input.
// I==========================================================================================================I
#define INPUT_ELSE_MOUSE_MOVE \
\
} \
if (SDL_event.type == SDL_MOUSEMOTION) \
{ \
/* Stores the recent data of mouse movement */ \
	SDL_MouseMotionEvent mouse = SDL_event.motion;


// I==============================================I
//  Marks the end of a mouse movement input check.
// I==============================================I
#define INPUT_END_MOUSE_MOVE \
\
	}


// I========================================================================I
//  Checks for mouse button input.
//  The parameter is a bool to check when the button is released.
//  You need to mark the end of the input check with INPUT_END_MOUSE_BUTTON.
//  You can access the mouse button data with the mouse variable.
//  It is recommended to use curly braces to mark the scope of the input.
//  EXAMPLE:  INPUT_MOUSE_BUTTON(true); {
// I========================================================================I
#define INPUT_MOUSE_BUTTON(on_button_up) \
\
if (SDL_event.type == on_button_up ? SDL_MOUSEBUTTONUP : SDL_MOUSEBUTTONDOWN) \
{ \
/* Stores the recent data of a mouse button press */ \
	SDL_MouseButtonEvent mouse = SDL_event.button;


// I========================================================================I
//  Checks for mouse button input being pressed down.
//  You need to mark the end of the input check with INPUT_END_MOUSE_BUTTON.
//  You can access the mouse button data with the mouse variable.
//  It is recommended to use curly braces to mark the scope of the input.
// I========================================================================I
#define INPUT_MOUSE_BUTTON_DOWN \
\
if (SDL_event.type == SDL_MOUSEBUTTONDOWN) \
{ \
/* Stores the recent data of a mouse button press */ \
	SDL_MouseButtonEvent mouse = SDL_event.button;


// I==================================================================================================================================================I
//  Checks for mouse button input following other input checks.
//  The parameter is a bool to check when the button is released.
//  You need to mark the start and end of the input check with INPUT_MOUSE_BUTTON or INPUT_MOUSE_BUTTON(on_button_up) and then INPUT_END_MOUSE_BUTTON.
//  It is recommended to use curly braces to mark the scope of the input.
//  EXAMPLE:  INPUT_ELSE_MOUSE_BUTTON(true); {
// I==================================================================================================================================================I
#define INPUT_ELSE_MOUSE_BUTTON(on_button_up) \
\
} \
else if (SDL_event.type == on_button_up ? SDL_MOUSEBUTTONUP : SDL_MOUSEBUTTONDOWN) \
{ \
/* Stores the recent data of a mouse button press */ \
	SDL_MouseButtonEvent mouse = SDL_event.button;


// I==================================================================================================================================================I
//  Checks for mouse button input being pressed down following other input checks.
//  You need to mark the start and end of the input check with INPUT_MOUSE_BUTTON or INPUT_MOUSE_BUTTON(on_button_up) and then INPUT_END_MOUSE_BUTTON.
//  It is recommended to use curly braces to mark the scope of the input.
// I==================================================================================================================================================I
#define INPUT_ELSE_MOUSE_BUTTON_DOWN \
\
} \
else if (SDL_event.type == SDL_MOUSEBUTTONDOWN) \
{ \
/* Stores the recent data of a mouse button press */ \
	SDL_MouseButtonEvent mouse = SDL_event.button;


// I============================================I
//  Marks the end of a mouse button input check.
// I============================================I
#define INPUT_END_MOUSE_BUTTON \
\
	}


// I=================================================================================I
//  Used to default to a different branch of input logic if no input criteria is met.
// I=================================================================================I
#define INPUT_ELSE \
\
} \
else \
{


// I=======================================I
//  Marks the end of a general input check.
// I=======================================I
#define INPUT_END \
\
	} \
}



// I===========================================================================================================================================================================I
//
//																					TEXT
// 
// I===========================================================================================================================================================================I



// I=================================================I
//  Allows TTF text to be rendered to the screen.
//	You must call CLOSE_TEXT before the program ends!
// I=================================================I
#define START_TEXT TTF_Init();


// I=====================I
//  Frees the TTF memory.
// I=====================I
#define CLOSE_TEXT TTF_Quit();


// I===========================================================================I
//  Creates a TTF font by the given ttf font file and assigns it to a variable.
//  The third file name is the default size of the font.
//  You must CLOSE_FONT before the program ends!
//  EXAMPLE:  CREATE_FONT("Sans.ttf", font, 24);
// I===========================================================================I
#define CREATE_FONT(font_file_name, font_variable_name, font_size) TTF_Font* font_variable_name = TTF_OpenFont(font_file_name, font_size);


// I==========================================I
//  Frees the TTF font's memory.
//  EXAMPLE:  CLOSE_FONT(font);
// I==========================================I
#define CLOSE_FONT(font_variable_name) TTF_CloseFont(font_variable_name);


// Creates a new SDL_Color
SDL_Color new_color(int r, int g, int b, int a = 255)
{
	SDL_Color color = SDL_Color();
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}


// I===================================================================================================================I
//  Creates text from the given font, text, and color and creates a variable for it named the given text variable name.
//  Sets its starting position to the given X and Y parameters and creates a variable for its transform.
//  Must have already created a font with CREATE_FONT(font_file_name, font_variable_name, font_size).
//  You must call REMOVE_TEXT(text_variable_name) and CLOSE_TEXT before the program ends!
//  EXAMPLE:  INSERT_TEXT(font, text, "Hello, Dinner!", 255, 255, 255, text_transform, 500, 500, 1, 1);
// I===================================================================================================================I
#define INSERT_TEXT(font_variable, text_variable_name, text, red, green, blue, transform_variable_name, x, y, scaleX, scaleY) \
\
temp_surface = TTF_RenderText_Solid(font_variable, text, new_color(red, green, blue)); \
\
SDL_Rect* transform_variable_name = new_rect(x, y, temp_surface->w * scaleX, temp_surface->h * scaleY); \
\
SDL_Texture* text_variable_name = SDL_CreateTextureFromSurface(renderer, temp_surface); \
\
textures.push_back(text_variable_name); \
\
transforms.push_back(transform_variable_name); \
\
SDL_RenderCopy(renderer, text_variable_name, NULL, transform_variable_name);


// I=====================================================================================================================I
//  Recreates text from the given font, text, and color and creates a variable for it named the given text variable name.
//  EXAMPLE:  REPLACE_TEXT(font, text, "Hello, Dinner!", 255, 255, 255, text_transform);
// I=====================================================================================================================I
#define REPLACE_TEXT(font_variable, text_variable_name, text, red, green, blue, transform_variable_name) \
\
SDL_DestroyTexture(text_variable_name); \
\
temp_surface = TTF_RenderText_Solid(font_variable, text, new_color(red, green, blue)); \
\
text_variable_name = SDL_CreateTextureFromSurface(renderer, temp_surface); \
\
SDL_RenderCopy(renderer, text_variable_name, NULL, transform_variable_name);


// I============================================I
//  Frees the given text variable's memory.
//  EXAMPLE:  REMOVE_TEXT(text, text_transform);
// I============================================I
#define REMOVE_TEXT(text_variable_name, transform_variable_name) \
\
SDL_DestroyTexture(text_variable_name); \
\
delete transform_variable_name;



// I===========================================================================================================================================================================I
//
//																					AUDIO
// 
// I===========================================================================================================================================================================I



// I==============================================================================I
//  Allows Mixer sounds and music to the played with the given number of channels.
//	You must call CLOSE_AUDIO before the program ends!
//  EXAMPLE:  START_AUDIO(1);
// I==============================================================================I
#define START_AUDIO(number_of_channels) \
\
Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, number_of_channels, 2048 ); \
\
Mix_Init(MIX_INIT_WAVPACK | MIX_INIT_MP3 | MIX_INIT_OGG);


// I=======================I
//  Frees the Mixer memory.
// I=======================I
#define CLOSE_AUDIO Mix_Quit();


// I========================================================================================I
//  Creates a sound to be played.
//  You must call REMOVE_SOUND(sound_variable_name) and CLOSE_AUDIO before the program ends!
//  EXAMPLE:  CREATE_SOUND("Sound.wav", sound);
// I========================================================================================I
#define LOAD_SOUND(sound_file_name, sound_variable_name) Mix_Chunk* sound_variable_name = Mix_LoadWAV(sound_file_name);


// I========================================I
//  Frees the given sound variable's memory.
//  EXAMPLE:  REMOVE_SOUND(sound);
// I========================================I
#define REMOVE_SOUND(sound_variable_name) Mix_FreeChunk(sound_variable_name);


// I======================================================================================================================================================================================I
//  Plays an instance of the given sound variable.
//  The second parameter is the number of times the sound will loop. -1 is used for infinite loops.
//  The third parameter is an int for which channel the sound is being played on. Playing on the same channel will overwrite that channel's sound. -1 is used for finding an open channel.
//  EXAMPLE:  PLAY_SOUND(sound, false, -1);
// I======================================================================================================================================================================================I
#define PLAY_SOUND(sound_variable_name, number_of_loops, channel) Mix_PlayChannel(channel, sound_variable_name, number_of_loops);


// I======================================================================I
//  Pauses the sound of a given channel. -1 is used to pause all channels.
//  EXAMPLE:  PAUSE_SOUNDS(-1);
// I======================================================================I
#define PAUSE_SOUNDS(channel) Mix_Pause(channel);


// I========================================================================I
//  Resumes the sound of a given channel. -1 is used to resume all channels.
//  EXAMPLE:  RESUME_SOUNDS(-1);
// I==========================----==========================================I
#define RESUME_SOUNDS(channel) Mix_Resume(channel);


// I====================================================================I
//  Stops the sound of a given channel. -1 is used to stop all channels.
//  EXAMPLE:  STOP_SOUNDS(-1);
// I==========================----======================================I
#define STOP_SOUNDS(channel) Mix_HaltChannel(channel);


// I==============================================================================I
//  Sets the volume of a channel. -1 is used to modify the volume of all channels.
//  EXAMPLE:  SET_VOLUME(-1, 10);
// I==============================================================================I
#define SET_SOUND_VOLUME(channel, new_volume) Mix_Volume(channel, new_volume);


// I========================================================================================I
//  Creates music to be played.
//  You must call REMOVE_MUSIC(music_variable_name) and CLOSE_AUDIO before the program ends!
//  EXAMPLE:  CREATE_MUSIC("Music.wav", music);
// I========================================================================================I
#define LOAD_MUSIC(music_file_name, music_variable_name) Mix_Music* music_variable_name = Mix_LoadMUS(music_file_name);


// I==================================I
//  Frees the music variable's memory.
//  EXAMPLE:  REMOVE_MUSIC(music);
// I==================================I
#define REMOVE_MUSIC(music_variable_name) Mix_FreeMusic(music_variable_name);


// I===============================================================================================I
//  Plays the given music variable.
//  The second parameter is the number of times the music will loop. -1 is used for infinite loops.
//  EXAMPLE:  PLAY_MUSIC(music, false);
// I===============================================================================================I
#define PLAY_MUSIC(music_variable_name, number_of_loops) Mix_PlayMusic(music_variable_name, number_of_loops);


// I=================I
//  Pauses all music.
// I=================I
#define PAUSE_MUSIC Mix_PauseMusic();


// I==================I
//  Resumes all music.
// I==================I
#define RESUME_MUSIC Mix_ResumeMusic();


// I================I
//  Stops all music.
// I================I
#define STOP_MUSIC Mix_HaltMusic();


// I==============================I
//  Sets the volume of music.
//  EXAMPLE:  SET_MUSIC_VOLUME(10);
// I==============================I
#define SET_MUSIC_VOLUME(new_volume) Mix_VolumeMusic(new_volume);


// I========================I
//  Sets the global volume.
//  EXAMPLE:  SET_VOLUME(10);
// I========================I
#define SET_VOLUME(new_volume) Mix_MasterVolume(new_volume);
