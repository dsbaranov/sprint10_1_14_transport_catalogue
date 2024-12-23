#include "transport_catalogue.h"

namespace catalogue {
using namespace structures;

void TransportCatalogue::AddStop(const Stop &stop) {
  stops_.push_back(stop);
  Stop *target = &stops_.back();
  stopname_to_stop_[target->name] = target;
}

Stop *TransportCatalogue::FindStop(std::string_view name) const {
  const auto stop_it = stopname_to_stop_.find(name);
  if (stop_it == stopname_to_stop_.end()) {
    return nullptr;
  }
  return stop_it->second;
}

void TransportCatalogue::AddBus(const Bus &bus) {
  busses_.push_back(std::move(bus));
  Bus *target = &busses_.back();
  busname_to_bus_[target->name] = target;
  for (Stop *stop : target->stops) {
    stop_to_busses_[stop].insert(target->name);
  }
}
Bus *TransportCatalogue::FindBus(std::string_view name) const {
  auto bus_it = busname_to_bus_.find(name);
  if (bus_it == busname_to_bus_.end()) {
    return nullptr;
  }
  return bus_it->second;
}

const std::set<std::string_view> &TransportCatalogue::FindBusesByStop(
    Stop *stop) const {
  auto busses_it = stop_to_busses_.find(stop);
  if (busses_it == stop_to_busses_.end()) {
    return empty_set_;
  }
  return busses_it->second;
};

const BusStatistics TransportCatalogue::GetBusStatistics(
    structures::Bus *bus) const {
  std::unordered_set<Stop *> unique_stops(bus->stops.begin(), bus->stops.end());
  return {bus->stops.size(), unique_stops.size(), CalculateBusDistance(bus)};
}

DistanceStatistics TransportCatalogue::CalculateBusDistance(
    structures::Bus *bus) const {
  double actual_distance = 0., geo_distance = 0.;
  for (auto it = bus->stops.begin(); it < bus->stops.end(); ++it) {
    auto next = std::next(it);
    if (next != bus->stops.end()) {
      actual_distance += GetDistance(std::make_pair(*it, *next));
      geo_distance +=
          geo::ComputeDistance((*it)->coordinates, (*next)->coordinates);
    }
  }
  double curvature = geo::ComputeCurvature(actual_distance, geo_distance);
  return {actual_distance, curvature};
}

void TransportCatalogue::SetDistance(const std::pair<Stop *, Stop *> &stops,
                                     double distance) {
  assert(stops.first && stops.second);
  stops_to_distance_[stops] = distance;
}

double TransportCatalogue::GetDistance(
    const std::pair<Stop *, Stop *> &stops) const {
  assert(stops.first && stops.second);
  auto distance_it = stops_to_distance_.find(stops);
  if (distance_it == stops_to_distance_.end() && stops.first != stops.second) {
    distance_it =
        stops_to_distance_.find(std::make_pair(stops.second, stops.first));
  };
  if (distance_it != stops_to_distance_.end()) {
    return distance_it->second;
  }
  return geo::ComputeDistance(stops.first->coordinates,
                              stops.second->coordinates);
}
};  // namespace catalogue
