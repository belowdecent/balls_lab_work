#pragma once

#include <SDL.h>
#include <SDL_image.h>

struct Ball {
	double x;
	double y;
	double r;
	SDL_Texture* texture;

	double vx;
	double vy;
	SDL_Rect dest;
	int window_w;
	int window_h;
};

Ball create_ball(double x, double y, double r, double vx, double vy, SDL_Renderer* renderer);
void draw_ball(Ball* ball, SDL_Renderer* renderer);
void move_ball(Ball* ball, double dt);
