#pragma once

#include <cstdint>

namespace devilution {

enum AxisDirectionX : uint8_t {
	AxisDirectionX_NONE,
	AxisDirectionX_LEFT,
	AxisDirectionX_RIGHT
};
enum AxisDirectionY : uint8_t {
	AxisDirectionY_NONE,
	AxisDirectionY_UP,
	AxisDirectionY_DOWN
};

/**
 * @brief 8-way direction of a D-Pad or a thumb stick.
 */
struct AxisDirection {
	AxisDirectionX x;
	AxisDirectionY y;
};

/**
 * @brief Returns a non-empty AxisDirection at most once per the given time interval.
 */
class AxisDirectionRepeater {
public:
	AxisDirectionRepeater(int min_delay_ms_ = 300, int min_interval_ms_ = 150)
	    : last_press_left_(0)
	    , last_repeat_left_(0)
	    , last_press_right_(0)
	    , last_repeat_right_(0)
	    , last_press_up_(0)
	    , last_repeat_up_(0)
	    , last_press_down_(0)
	    , last_repeat_down_(0)
	    , min_delay_ms_(min_delay_ms_)
	    , min_interval_ms_(min_interval_ms_)
	{
	}

	AxisDirection Get(AxisDirection axisDirection);

private:
	int last_press_left_;
	int last_repeat_left_;
	int last_press_right_;
	int last_repeat_right_;
	int last_press_up_;
	int last_repeat_up_;
	int last_press_down_;
	int last_repeat_down_;
	int min_delay_ms_;
	int min_interval_ms_;
};

} // namespace devilution
