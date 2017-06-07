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
		virtual void start(void);
		virtual void stop(void);
		virtual void pause(void);
		virtual void unpause(void);

		/**
		 * Get the timer's time.
		 */
		virtual Uint32 getTicks(void) const;

		/**
		 * Get the timer's status;
		 */
		virtual bool isStarted(void) const;
		virtual bool isPaused(void) const;
};

#endif /* PTIMER_H */


