//-*-c++-*-

#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <ostream>
#include <utility>



namespace AprilTags {

std::ostream& operator<<(std::ostream &os, const std::pair<float,float> &pt);

//! Miscellaneous math utilities and fast exp functions.
class MathUtil {
public:
	
	//! Returns the square of a value.
	static inline float square(float x) { return x*x; }
	
	static inline float distance2D(const std::pair<float,float> &p0, const std::pair<float,float> &p1) {
		float dx = p0.first - p1.first;
		float dy = p0.second - p1.second;
		return std::sqrt(dx*dx + dy*dy);
	}
	
	//! Returns a result in [-Pi, Pi]
	static inline float mod2pi(float vin) {
		const float twopi = 2.0f * (float)M_PI;
		const float twopi_inv = 1.f / twopi;
		float absv = fabsf(vin);
		float q = absv*twopi_inv + 0.5f;
		int qi = (int) q;
		float r = absv - qi*twopi;
		return (vin<0) ? -r : r;
	}
	
	//! Returns a value of v wrapped such that ref and v differ by no more than +/- Pi
	static inline float mod2pi(const float &ref, const float &v) { return ref + mod2pi(v-ref); }

// lousy approximation of arctan function, but good enough for our purposes (about 4 degrees)
  static inline float fast_atan2(const float &y, const float &x) {
    float coeff_1 = M_PI*0.25f;
    float coeff_2 = 3.0f*coeff_1;
    float abs_y = fabs(y)+1e-10;      // kludge to prevent 0/0 condition

    float angle;

    if (x >= 0) {
      float r = (x - abs_y) / (x + abs_y);
      angle = coeff_1 - coeff_1 * r;
    } else {
      float r = (x + abs_y) / (abs_y - x);
      angle = coeff_2 - coeff_1 * r;
    }

    if (y < 0)
      return -angle;     // negate if in quad III or IV
    else
      return angle;
  }
	
};

} // namespace

#endif
