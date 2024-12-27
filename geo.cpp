#include "geo.h"
namespace catalogue::geo {
double ComputeDistance(const Coordinates &from, const Coordinates &to) {
  using namespace std;
  if (from == to) {
    return 0;
  }
  static const double dr = 3.1415926535 / 180.;
  return acos(sin(from.lat * dr) * sin(to.lat * dr) +
              cos(from.lat * dr) * cos(to.lat * dr) *
                  cos(abs(from.lng - to.lng) * dr)) *
         EARTH_RADIUS;
}

double ComputeCurvature(const double actual_distance,
                        const double geographical_distance) {
  if (geographical_distance == 0.) {
    return 1.;
  }
  return actual_distance / geographical_distance;
}
}  // namespace catalogue::geo
