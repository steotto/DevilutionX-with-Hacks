#include "axis_direction.h"

#ifdef USE_SDL3
#include <SDL3/SDL_timer.h>
#else
#include <SDL.h>
#endif

namespace devilution {

bool AxisDirectionRepeater::AllowRepeat(int &lastPrimary, int &lastOpposite, int now)
{
	lastOpposite = 0;
	if (lastPrimary == 0) {
		// Negative value marks the initial press timestamp for the first-repeat delay
		lastPrimary = -now;
		return true;
	}
	if (lastPrimary < 0) {
		if (now + lastPrimary < min_delay_ms_)
			return false;
		lastPrimary = now;
		return true;
	}
	if (now - lastPrimary < min_interval_ms_)
		return false;
	lastPrimary = now;
	return true;
}

AxisDirection AxisDirectionRepeater::Get(AxisDirection axisDirection)
{
	const int now = SDL_GetTicks();

	switch (axisDirection.x) {
	case AxisDirectionX_LEFT:
		if (!AllowRepeat(last_left_, last_right_, now))
			axisDirection.x = AxisDirectionX_NONE;
		break;
	case AxisDirectionX_RIGHT:
		if (!AllowRepeat(last_right_, last_left_, now))
			axisDirection.x = AxisDirectionX_NONE;
		break;
	case AxisDirectionX_NONE:
		last_left_ = last_right_ = 0;
		break;
	}

	switch (axisDirection.y) {
	case AxisDirectionY_UP:
		if (!AllowRepeat(last_up_, last_down_, now))
			axisDirection.y = AxisDirectionY_NONE;
		break;
	case AxisDirectionY_DOWN:
		if (!AllowRepeat(last_down_, last_up_, now))
			axisDirection.y = AxisDirectionY_NONE;
		break;
	case AxisDirectionY_NONE:
		last_up_ = last_down_ = 0;
		break;
	}

	return axisDirection;
}

} // namespace devilution
