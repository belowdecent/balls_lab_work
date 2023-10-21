#include <iostream>
#include <SDL.h>
#include "Ball.hpp"
#include "Limiter.hpp"
#include "SDL_image.h"
#include "SDL_video.h"

#define PROJECT_NAME "Lab2"

static inline int init_error(const char* message_fmt) {
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, message_fmt, SDL_GetError());
	return 1;
} 

static int initialize(
	SDL_Window** win,
	SDL_Renderer** renderer
) {
	if (SDL_Init(SDL_INIT_VIDEO)) 
		return init_error("Couldn't initialize SDL: %s");
	IMG_Init(IMG_INIT_PNG);


	*win = SDL_CreateWindow(
		"Balling", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		640, 480,
		SDL_WINDOW_RESIZABLE
	);

	if (*win == NULL)
		return init_error("Couldn't create window: %s");

	*renderer = SDL_CreateRenderer(*win, -1, SDL_RENDERER_PRESENTVSYNC);

	if (*renderer == NULL) {
		return init_error("Couldn't create renderer: %s");
	}

	return 0;
}

int main(int argc, char **argv) {
	if(argc != 1) {
	std::cout << argv[0] <<  "takes no arguments.\n";
	return 1;
	}

	SDL_Window* win;
	SDL_Renderer* renderer;

	if (initialize(&win, &renderer)) {
		SDL_Quit();
		return 3;
	}

	Ball ball = create_ball(10, 10, 30, -20, -40, renderer);
	Limiter lim = {
		.rect = {
			.x = 250,
			.y = 250,
			.w = 200,
			.h = 1,
		}
	};

	Limiter lim2 = {
		.rect = {
			.x = 500,
			.y = 250,
			.w = 1,
			.h = 200,
		}
	};
	SDL_GetWindowSize(win, &ball.window_w, &ball.window_h);

	SDL_Event e;

	while (1) {
		SDL_PollEvent(&e);
		int lim_dx = 0;
		int lim_dy = 0;

		if (e.type == SDL_QUIT) {
			break;
		} else if (e.type == SDL_WINDOWEVENT) {
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				SDL_GetWindowSize(win, &ball.window_w, &ball.window_h);
			}
		} else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_UP:
					lim_dy = -10;
					break;
				case SDLK_DOWN:
					lim_dy = 10;
					break;
				case SDLK_LEFT:
					lim_dx = -10;
					break;
				case SDLK_RIGHT:
					lim_dx = 10;
					break;
			}
		}

		move_limiter(&lim, lim_dx, lim_dy);

		

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		ball_collision(&ball, &lim);
		ball_collision(&ball, &lim2);
		move_ball(&ball, 0.033);
		draw_ball(&ball, renderer);
		draw_limiter(&lim, renderer);
		draw_limiter(&lim2, renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	IMG_Quit();
}
