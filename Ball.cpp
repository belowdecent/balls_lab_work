#include "Ball.hpp"

Ball create_ball(double x, double y, double r, double vx, double vy, SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load("ball.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return {
		.x = x,
		.y = y,
		.r = r,
		.texture = texture,
		.vx = vx,
		.vy = vy,
		.dest = {
			.x = int(x),
			.y = int(y),
			.w = int(2 * r),
			.h = int(2 * r),
		}
	};
}

void draw_ball(Ball* ball, SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, ball->texture, nullptr, &ball->dest);
}

void move_ball(Ball* ball, double dt) {
	ball->x += ball->vx * dt;
	ball->y += ball->vy * dt;

	ball->dest.x = (int)ball->x;
	ball->dest.y = (int)ball->y;

	if (ball->dest.x < 0 && ball->vx < 0) {
		ball->vx = -ball->vx;
	} else if ((ball->dest.x + ball->dest.w) > ball->window_w && ball->vx > 0) {
		ball->vx = -ball->vx;
	}

	if (ball->y < 0 && ball->vy < 0) {
		ball->vy = -ball->vy;
	} else if ((ball->dest.y + ball->dest.h) > ball->window_h && ball->vy > 0) {
		ball->vy = -ball->vy;
	}
}
