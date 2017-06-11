/**
 * Timer Class.
 * Alex Striff.
 */

#ifndef PTIMER_H
#define PTIMER_H

#include "common.h"

class PTimer
{
	bool   started,     paused;
	Uint32 start_ticks, paused_ticks;

	public:
		PTimer():
			started(false),
			paused(false),
			start_ticks(0ul),
			paused_ticks(0ul) {}

		virtual void start(void);
		virtual void stop(void);
		virtual void pause(void);
		virtual void unpause(void);

		virtual Uint32 ticks(void) const;

		virtual bool isStarted(void) const;
		virtual bool isPaused(void) const;
};
COMMON_VERIFY(PTimer);

#endif /* PTIMER_H */


