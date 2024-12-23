#pragma once

#include <algorithm>
#include <cassert>
#include <deque>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "geo.h"

namespace catalogue {
namespace structures {
/**
 * Структура остановки.
 * @param name string - имя остановки
 * @param latitude double - широта остановки
 * @param longitude double - долгота остановки
 * @note Сущность предназначена для хранения параметров одной остановки
 */
struct Stop {
  std::string name;
  Coordinates coordinates;

  Stop(const std::string &_name, const Coordinates &_coordinates)
      : name(_name), coordinates(_coordinates) {}
  Stop(const Stop &other) : name(other.name), coordinates(other.coordinates) {}
  Stop(Stop &&other)
      : name(std::move(other.name)),
        coordinates(std::move(other.coordinates)) {}
  Stop &operator=(Stop &&other) {
    name = std::move(other.name);
    coordinates = std::move(other.coordinates);
    return *this;
  }
  bool operator==(const Stop &rhs) const {
    return this->name == rhs.name && this->coordinates == rhs.coordinates;
  }
};

struct Bus {
  std::string name;
  std::vector<Stop *> stops;

  Bus() = default;
  Bus(const std::string &_name, const std::vector<Stop *> &_stops)
      : name(move(_name)),
        stops(std::move_iterator(_stops.begin()),
              std::move_iterator(_stops.end())) {}
};
/**
 * Хэшер для контейнера дистанций остановок.
 * @param stops pair<Stop*, Stop*> - Указатели на остановки, между которыми
 * будет сохранено значение дистанции
 */
struct DistanceHasher {
  size_t operator()(const std::pair<Stop *, Stop *> &stops) const {
    return hasher(stops.first) + hasher(stops.second) * 42;
  }

 private:
  std::hash<const void *> hasher;
};

struct DistanceStatistics {
  double distance;
  double curvature;
};

/**
 * Структура передачи информации о маршруте, запрашиваемой в
 * TransportCatalogue::GetBusStatistics
 * @param stops size_t - Общее количество остановок
 * @param unique_stops size_t - Количество уникальных остановок
 * @param distance double - Расстояние маршрута
 */
struct BusStatistics {
  size_t stops;
  size_t unique_stops;
  DistanceStatistics distance_statistics;
};

};  // namespace structures

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
