#include "darts.h"

namespace darts {
	int score(double x, double y) {
		//distance squared from the center
		double distance_squared = x * x + y * y;

		//scoring based on distance squared
		if (distance_squared > 100.0)
		{
			return 0;
			//outside of the outer circle
		}
		else if (distance_squared > 25.0) {
			return 1;
			//within the outer circle
		}
		else if (distance_squared > 1.0)
		{
			return 5;  
			// Within the middle circle
		}
		else {
			return 10;  
			// Within the inner circle (including the center)
		}
	}

} // namespace darts