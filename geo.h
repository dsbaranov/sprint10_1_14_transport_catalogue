#pragma once

#include <cmath>
#include <utility>

#include "domain.h"

namespace catalogue::geo {

static const size_t EARTH_RADIUS = 6371000;

using namespace catalogue::structures;
double ComputeDistance(const Coordinates &from, const Coordinates &to);
double ComputeCurvature(const double actual_distance,
                        const double geographical_distance);
};  // namespace catalogue::geo
