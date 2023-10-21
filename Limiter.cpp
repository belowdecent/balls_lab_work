#include "Limiter.hpp"

void draw_limiter(Limiter* limiter, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &limiter->rect);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

int magnitude_sq(int ax, int ay) {
	return ax * ax + ay * ay;
}

void ball_collision(Ball* ball, Limiter* limiter) {
	// AABB check
	bool is_to_left = ball->dest.x + ball->dest.w < limiter->rect.x;
	bool is_to_right = limiter->rect.x + limiter->rect.w < ball->dest.x;
	bool is_to_top = ball->dest.y + ball->dest.h < limiter->rect.y;
	bool is_to_bottom = limiter->rect.y + limiter->rect.h < ball->dest.y;

	if (is_to_left || is_to_right || is_to_top || is_to_bottom)
		return;

	double lim_left_x   = static_cast<double>(limiter->rect.x);
	double lim_right_x  = static_cast<double>(limiter->rect.x + limiter->rect.w);
	double lim_top_y    = static_cast<double>(limiter->rect.y);
	double lim_bottom_y = static_cast<double>(limiter->rect.y + limiter->rect.h);

	double ball_left_x   = ball->x;
	double ball_center_x = ball->x + ball->r;
	double ball_right_x  = ball->x + ball->r * 2;

	double ball_top_y    = ball->y;
	double ball_center_y = ball->y + ball->r;
	double ball_bottom_y = ball->y + ball->r * 2.0;

	bool ball_right_collision  = ball_center_x <= lim_left_x   && ball_right_x  >= lim_left_x   && ball->vx > 0;
	bool ball_left_collision   = ball_left_x   <= lim_right_x  && ball_center_x >= lim_right_x  && ball->vx < 0;
	bool ball_bottom_collision = ball_center_y <= lim_top_y    && ball_bottom_y >= lim_top_y    && ball->vy > 0;
	bool ball_top_collision    = ball_top_y    <= lim_bottom_y && ball_center_y >= lim_bottom_y && ball->vy < 0;

	if (ball_left_collision || ball_right_collision) {
		ball->vx = -ball->vx;
	}

	if (ball_top_collision || ball_bottom_collision) {
		ball->vy = -ball->vy;
	}
}

void move_limiter(Limiter* limiter, int dx, int dy) {
	limiter->rect.x += dx;
	limiter->rect.y += dy;
}
