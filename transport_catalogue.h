#pragma once

#include <algorithm>
#include <cassert>
#include <deque>
#include <set>
#include <stdexcept>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "geo.h"

namespace catalogue {

class TransportCatalogue {
 public:
  void AddStop(const structures::Stop &stop);

  structures::Stop *FindStop(std::string_view name) const;

  void AddBus(const structures::Bus &bus);

  structures::Bus *FindBus(std::string_view name) const;

  const std::set<std::string_view> &FindBusesByStop(
      structures::Stop *stop) const;

  const structures::BusStatistics GetBusStatistics(structures::Bus *bus) const;

  void SetDistance(
      const std::pair<structures::Stop *, structures::Stop *> &stops,
      double distance);

  double GetDistance(
      const std::pair<structures::Stop *, structures::Stop *> &stops) const;

 private:
  structures::DistanceStatistics CalculateBusDistance(
      structures::Bus *bus) const;

  std::set<std::string_view> empty_set_;
  std::deque<structures::Stop> stops_;
  std::deque<structures::Bus> busses_;
  std::unordered_map<std::string_view, structures::Stop *> stopname_to_stop_;
  std::unordered_map<std::string_view, structures::Bus *> busname_to_bus_;
  std::unordered_map<structures::Stop *, std::set<std::string_view>>
      stop_to_busses_;
  std::unordered_map<std::pair<structures::Stop *, structures::Stop *>, double,
                     structures::DistanceHasher>
      stops_to_distance_;
};
};  // namespace catalogue
