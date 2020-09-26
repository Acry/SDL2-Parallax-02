#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region HEAD
#pragma region DESCRIPTION
#pragma endregion DESCRIPTION

#pragma region INCLUDES
//local headers
#include "helper.h"
#pragma endregion INCLUDES

#pragma region CPP DEFINITIONS
#define W 800
#pragma endregion CPP DEFINITIONS

#pragma region DATASTRUCTURES
#pragma endregion DATASTRUCTURES

#pragma region GLOBALS
int WW = W;
int WH = W / 16 * 9;

SDL_Surface *temp_surface;

SDL_Texture *gradient;
SDL_Rect gradient_dst;

SDL_Texture *mountains;
SDL_Rect mountains_dst;
SDL_Rect mountains_src;

SDL_Texture *sky;
SDL_Rect sky_src;
SDL_Rect sky_dst;

SDL_Texture *bg_l;
SDL_Rect bg_l_src;
SDL_Rect bg_l_dst;

SDL_Texture *bg_r;
SDL_Rect bg_r_src;
SDL_Rect bg_r_sky_dst;

SDL_Texture *middleground;
SDL_Rect middleground_src;
SDL_Rect middleground_dst;

SDL_Texture *foreground;
SDL_Rect foreground_src;
SDL_Rect foreground_dst;
#pragma endregion GLOBALS

#pragma region FUNCTION PROTOTYPES
void assets_in(void);
void assets_out(void);
void move_right(void);
void move_left(void);
#pragma endregion FUNCTION PROTOTYPES

/* DEFINED PROGRESS GOALS
 * 
 * Nothing right now
 * n'joy
 * 
 * 
 */
#pragma endregion HEAD

#pragma region MAIN FUNCTION
int main(int argc, char *argv[])
{

	(void)argc;
	(void)argv;

#pragma region INIT
	init();
	assets_in();

	SDL_SetWindowSize(Window, WW, WH);
	SDL_SetWindowPosition(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_SetWindowTitle(Window, "Parallax Scrolling");
	SDL_ShowWindow(Window);
	SDL_Event event;
	int running = 1;
#pragma endregion INIT

#pragma region MAIN LOOP
	while (running)
	{
#pragma region EVENT LOOP
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_RIGHT)
				{
					running = 0;
				}
			}
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = 0;
					break;
				case SDLK_LEFT:
					move_left();
					break;
				case SDLK_RIGHT:
					move_right();
					break;

				case SDLK_SPACE:
					break;

				default:
					break;
				}
			}
		}
#pragma endregion EVENT LOOP

#pragma region RENDERING
		SDL_SetRenderDrawColor(Renderer, 111, 111, 111, 255);
		SDL_RenderClear(Renderer);
		SDL_RenderCopy(Renderer, gradient, NULL, &gradient_dst);
		SDL_RenderCopy(Renderer, mountains, NULL, &mountains_dst);
		SDL_RenderCopy(Renderer, sky, &sky_src, &sky_dst);
		SDL_RenderCopy(Renderer, bg_l, &bg_l_src, &bg_l_dst);
		SDL_RenderCopy(Renderer, middleground, &middleground_src, &middleground_dst);
		SDL_RenderCopy(Renderer, foreground, &foreground_src, &foreground_dst);
		SDL_RenderPresent(Renderer);
#pragma endregion RENDERING
	}
#pragma endregion MAIN LOOP
	assets_out();
	exit_();
	return EXIT_SUCCESS;
}
#pragma endregion MAIN FUNCTION

#pragma region FUNCTIONS
void move_right(void)
{
	if (foreground_src.x + foreground_src.w < 5252)
	{
		mountains_src.x += 2;
		sky_src.x += 4;
		bg_l_src.x += 8;
		middleground_src.x += 12;
		foreground_src.x += 18;
	}
}

void move_left(void)
{
	if (foreground_src.x > 0)
	{
		mountains_src.x -= 2;
		sky_src.x -= 4;
		bg_l_src.x -= 8;
		middleground_src.x -= 12;
		foreground_src.x -= 18;
	}
}

void assets_in(void)
{
	int w, h; //query tex
	float fh;

#pragma region GRADIENT
	temp_surface = IMG_Load("./assets/graphics/gradient.png");
	gradient = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(mountains, NULL, NULL, &w, &h);
	fh = (float)h;
	gradient_dst.w = WW;
	gradient_dst.h = WH * 0.75;
	gradient_dst.x = 0;
	gradient_dst.y = 0;
#pragma endregion GRADIENT

#pragma region MOUNTAINS
	temp_surface = IMG_Load("./assets/graphics/mountains.png");
	mountains = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(mountains, NULL, NULL, &w, &h);
	fh = (float)h;

	mountains_dst.w = WW;
	mountains_dst.h = WH;
	mountains_dst.x = 0;
	mountains_dst.y = 130;

	mountains_src.w = roundf((float)WW * ((fh / (float)mountains_dst.h)));
	mountains_src.h = h;
	mountains_src.x = 200;
	mountains_src.y = 0;
#pragma endregion MOUNTAINS

#pragma region SKY
	temp_surface = IMG_Load("./assets/graphics/sky.png");
	sky = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(sky, NULL, NULL, &w, &h);
	fh = (float)h;

	sky_dst.w = WW;
	sky_dst.h = WH / 2;
	sky_dst.x = 0;
	sky_dst.y = 160;

	sky_src.w = roundf((float)WW * ((fh / (float)sky_dst.h)));
	sky_src.h = h;
	sky_src.x = WW;
	sky_src.y = 0;
#pragma endregion SKY

#pragma region BG_LEFT
	temp_surface = IMG_Load("./assets/graphics/bg_l.png");
	bg_l = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(bg_l, NULL, NULL, &w, &h);
	fh = (float)h;

	bg_l_dst.w = WW;
	bg_l_dst.h = WH * 1.25;
	bg_l_dst.x = 0;
	bg_l_dst.y = -140;

	bg_l_src.h = h;
	bg_l_src.w = roundf((float)WW * ((fh / (float)bg_l_dst.h)));
	bg_l_src.x = 300;
	bg_l_src.y = 0;
#pragma endregion BG_LEFT

#pragma region BG_RIGHT
#pragma endregion BG_RIGHT

#pragma region MITTLE
	temp_surface = IMG_Load("./assets/graphics/middleground.png");
	middleground = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(middleground, NULL, NULL, &w, &h);
	fh = (float)h;

	middleground_dst.w = WW;
	middleground_dst.h = WH * 1.50;
	middleground_dst.x = 0;
	middleground_dst.y = -181;

	middleground_src.h = h;
	middleground_src.w = roundf((float)WW * ((fh / (float)middleground_dst.h)));
	middleground_src.x = 300;
	middleground_src.y = 0;
#pragma endregion MIDDLE

#pragma region FOREGROUND
	temp_surface = IMG_Load("./assets/graphics/foreground.png");
	foreground = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(foreground, NULL, NULL, &w, &h);
	fh = (float)h;

	foreground_dst.w = WW;
	foreground_dst.h = WH * 1.75;
	foreground_dst.x = 0;
	foreground_dst.y = -280;

	foreground_src.h = h;
	foreground_src.w = roundf((float)WW * ((fh / (float)foreground_dst.h)));
	foreground_src.x = 0;
	foreground_src.y = 0;
#pragma endregion FOREGROUND

	SDL_FreeSurface(temp_surface);
}

void assets_out(void)
{
	SDL_DestroyTexture(gradient);
	SDL_DestroyTexture(mountains);
	SDL_DestroyTexture(sky);
	SDL_DestroyTexture(bg_l);
	SDL_DestroyTexture(bg_r);
	SDL_DestroyTexture(middleground);
	SDL_DestroyTexture(foreground);
}
#pragma endregion FUNCTIONS
