#include <SDL.h>
Uint32 timerTicks = 0;

void reset_timer(Uint32 timeout) {
	timerTicks = SDL_GetTicks() + timeout;
}
bool get_timer_status() {
	return SDL_TICKS_PASSED(SDL_GetTicks(), timerTicks);
}
Uint32 get_timer_difference() {
	return timerTicks - SDL_GetTicks();
}