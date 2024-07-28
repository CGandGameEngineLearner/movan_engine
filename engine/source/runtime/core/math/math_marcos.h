#pragma once

#define MOVAN_MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MOVAN_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MOVAN_PIN(a, min_value, max_value) MOVAN_MIN(max_value, MOVAN_MAX(a, min_value))

#define MOVAN_VALID_INDEX(idx, range) (((idx) >= 0) && ((idx) < (range)))
#define MOVAN_PIN_INDEX(idx, range) MOVAN_PIN(idx, 0, (range)-1)

#define MOVAN_SIGN(x) ((((x) > 0.0f) ? 1.0f : 0.0f) + (((x) < 0.0f) ? -1.0f : 0.0f))
