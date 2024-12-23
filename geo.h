#pragma once

#include <cmath>
#include <utility>

namespace catalogue {
namespace structures {

struct Coordinates {
  double lat;
  double lng;
  bool operator==(const Coordinates &other) const {
    return lat == other.lat && lng == other.lng;
  }
  bool operator!=(const Coordinates &other) const { return !(*this == other); }

  Coordinates(double _lat, double _lng) : lat(_lat), lng(_lng) {}
};

};  // namespace structures

namespace geo {
static const size_t EARTH_RADIUS = 6371000;

using namespace catalogue::structures;
inline double ComputeDistance(const Coordinates &from, const Coordinates &to) {
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
inline double ComputeCurvature(const double actual_distance,
                               const double geographical_distance) {
  if (geographical_distance == 0.) {
    return 1.;
  }
  return actual_distance / geographical_distance;
}
};  // namespace geo
};  // namespace catalogue
