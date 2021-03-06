/**
 * Range Structure.
 * Alex Striff.
 */

#ifndef RANGE_H
#define RANGE_H

#include <limits>
#include "commont.h"

using coord = double;

struct Range
{
	coord min;
	coord max;

	// Range(coord min = std::numeric_limits<coord>::max(),
	// 		coord max = std::numeric_limits<coord>::min()):
	// 	min(min), max(max) {};

	Range(coord min = std::numeric_limits<coord>::max(),
			coord max = std::numeric_limits<coord>::min()):
		min(std::min(min, max)), max(std::max(min, max)) {};

	bool overlaps(const Range& r) const
	{
		return (min < r.min && r.min < max) || (min < r.max && r.max < max);
	}
	bool overlaps(Range&& r) const
	{
		return (min < r.min && r.min < max) || (min < r.max && r.max < max);
	}
	bool overlaps(coord r) const
	{
		return (min < r && r < max) || (min < r && r < max);
	}

	void update(coord v)
	{
		if (v > max) {
			max = v;
		}
		if (v < min) {
			min = v;
		}
	}
	void update(const Range& r)
	{
		if (r.max > max) {
			max = r.max;
		} else if (r.min > max) {
			max = r.min;
		}
		if (r.min < min) {
			min = r.min;
		} else if (r.max < min) {
			min = r.max;
		}
	}
};
COMMON_VERIFY(Range);

const auto inverse_range = Range(
		std::numeric_limits<coord>::max(),
		std::numeric_limits<coord>::min());

#endif /* RANGE_H */

