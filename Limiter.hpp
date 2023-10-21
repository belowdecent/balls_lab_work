#pragma once

#include <SDL.h>
#include "Ball.hpp"

struct Limiter {
	SDL_Rect rect;
};

void draw_limiter(Limiter* limiter, SDL_Renderer* renderer);
void ball_collision(Ball* ball, Limiter* limiter);
void move_limiter(Limiter* limiter, int dx, int dy);
