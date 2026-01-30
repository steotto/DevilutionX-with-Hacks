#include "axis_direction.h"

#ifdef USE_SDL3
#include <SDL3/SDL_timer.h>
#else
#include <SDL.h>
#endif

namespace devilution {

namespace {
bool AllowRepeat(int &lastPrimary, int &lastOpposite, int now, int minDelayMs, int minIntervalMs)
{
	lastOpposite = 0;
	if (lastPrimary == 0) {
		// Negative value marks the initial press timestamp for the first-repeat delay.
		lastPrimary = -now;
		return true;
	}
	if (lastPrimary < 0) {
		if (now + lastPrimary < minDelayMs)
			return false;
		lastPrimary = now;
		return true;
	}
	if (now - lastPrimary < minIntervalMs)
		return false;
	lastPrimary = now;
	return true;
}
} // namespace

AxisDirection AxisDirectionRepeater::Get(AxisDirection axisDirection)
{
	const int now = SDL_GetTicks();

	switch (axisDirection.x) {
	case AxisDirectionX_LEFT:
		if (!AllowRepeat(last_left_, last_right_, now, min_delay_ms_, min_interval_ms_))
			axisDirection.x = AxisDirectionX_NONE;
		break;
	case AxisDirectionX_RIGHT:
		if (!AllowRepeat(last_right_, last_left_, now, min_delay_ms_, min_interval_ms_))
			axisDirection.x = AxisDirectionX_NONE;
		break;
	case AxisDirectionX_NONE:
		last_left_ = last_right_ = 0;
		break;
	}

	switch (axisDirection.y) {
	case AxisDirectionY_UP:
		if (!AllowRepeat(last_up_, last_down_, now, min_delay_ms_, min_interval_ms_))
			axisDirection.y = AxisDirectionY_NONE;
		break;
	case AxisDirectionY_DOWN:
		if (!AllowRepeat(last_down_, last_up_, now, min_delay_ms_, min_interval_ms_))
			axisDirection.y = AxisDirectionY_NONE;
		break;
	case AxisDirectionY_NONE:
		last_up_ = last_down_ = 0;
		break;
	}

	return axisDirection;
}

} // namespace devilution
