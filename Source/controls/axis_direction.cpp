#include "axis_direction.h"

#ifdef USE_SDL3
#include <SDL3/SDL_timer.h>
#else
#include <SDL.h>
#endif

namespace devilution {

namespace {
bool AllowDirectionRepeat(int now, int minDelayMs, int minIntervalMs, int &pressTime, int &lastRepeatTime)
{
	if (pressTime == 0) {
		pressTime = now;
		lastRepeatTime = 0;
		return true;
	}
	if (lastRepeatTime == 0) {
		if (now - pressTime < minDelayMs)
			return false;
		lastRepeatTime = now;
		return true;
	}
	if (now - lastRepeatTime < minIntervalMs)
		return false;
	lastRepeatTime = now;
	return true;
}
} // namespace

AxisDirection AxisDirectionRepeater::Get(AxisDirection axisDirection)
{
	const int now = SDL_GetTicks();

	switch (axisDirection.x) {
	case AxisDirectionX_LEFT:
		last_press_right_ = 0;
		last_repeat_right_ = 0;
		if (!AllowDirectionRepeat(now, min_delay_ms_, min_interval_ms_, last_press_left_, last_repeat_left_))
			axisDirection.x = AxisDirectionX_NONE;
		break;
	case AxisDirectionX_RIGHT:
		last_press_left_ = 0;
		last_repeat_left_ = 0;
		if (!AllowDirectionRepeat(now, min_delay_ms_, min_interval_ms_, last_press_right_, last_repeat_right_))
			axisDirection.x = AxisDirectionX_NONE;
		break;
	case AxisDirectionX_NONE:
		last_press_left_ = 0;
		last_repeat_left_ = 0;
		last_press_right_ = 0;
		last_repeat_right_ = 0;
		break;
	}

	switch (axisDirection.y) {
	case AxisDirectionY_UP:
		last_press_down_ = 0;
		last_repeat_down_ = 0;
		if (!AllowDirectionRepeat(now, min_delay_ms_, min_interval_ms_, last_press_up_, last_repeat_up_))
			axisDirection.y = AxisDirectionY_NONE;
		break;
	case AxisDirectionY_DOWN:
		last_press_up_ = 0;
		last_repeat_up_ = 0;
		if (!AllowDirectionRepeat(now, min_delay_ms_, min_interval_ms_, last_press_down_, last_repeat_down_))
			axisDirection.y = AxisDirectionY_NONE;
		break;
	case AxisDirectionY_NONE:
		last_press_up_ = 0;
		last_repeat_up_ = 0;
		last_press_down_ = 0;
		last_repeat_down_ = 0;
		break;
	}

	return axisDirection;
}

} // namespace devilution
