#pragma once

#include <string>

using namespace std;

namespace space_age {
	class space_age {
		public:
			space_age(double age_in_seconds);

			int seconds() const;

			double on_earth() const;

			double on_mercury() const;

			double on_venus() const;

			double on_mars() const;

			double on_jupiter() const;

			double on_saturn() const;

			double on_uranus() const;

			double on_neptune() const;

		private:
			double age;
			double earth_seconds = 31557600;
			double mercury_ratio = 0.2408467;
			double venus_ratio = 0.61519726;
			double mars_ratio = 1.8808158;
			double jupiter_ratio = 11.862615;
			double saturn_ratio = 29.447498;
			double uranus_ratio = 84.016846;
			double neptune_ratio = 164.79132;
	};
}  // namespace space_age
