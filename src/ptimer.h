/**
 * Timer Class.
 * Alex Striff.
 */

#ifndef PTIMER_H
#define PTIMER_H

#include "pob.h"

class PTimer
{
	private:
		bool   started, paused;
		Uint32 start_ticks, paused_ticks;

	public:
		/**
		 * Initializes the timer.
		 */
		PTimer():
			started(false),
			paused(false),
			start_ticks(0),
			paused_ticks(0) {}

		/**
		 * Timer actions.
		 */
		void start(void);
		void stop(void);
		void pause(void);
		void unpause(void);

		/**
		 * Get the timer's time.
		 */
		Uint32 getTicks(void) const;

		/**
		 * Get the timer's status;
		 */
		bool isStarted(void) const;
		bool isPaused(void) const;
};

#endif /* PTIMER_H */


