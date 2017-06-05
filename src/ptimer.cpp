#include "ptimer.h"

void PTimer::start(void)
{
	paused       = false;
	started      = true;
	paused_ticks = 0;
	start_ticks  = SDL_GetTicks();
}

void PTimer::stop(void)
{
	paused       = false;
	started      = false;
	paused_ticks = 0;
	start_ticks  = 0;
}

void PTimer::pause(void)
{
	if (started && !paused) {
		paused       = true;
		paused_ticks = SDL_GetTicks() - start_ticks;
		start_ticks  = 0;
	}
}

void PTimer::unpause(void)
{
	if (started && paused) {
		paused       = false;
		start_ticks  = SDL_GetTicks() - paused_ticks;
		paused_ticks = 0;
	}
}

Uint32 PTimer::getTicks(void) const
{
	if (started) {
		return paused ? paused_ticks : (SDL_GetTicks() - start_ticks);
	} else {
		return 0;
	}
}

bool PTimer::isStarted(void) const
{
	return started;
}

bool PTimer::isPaused(void) const
{
	return (started && paused);
}

