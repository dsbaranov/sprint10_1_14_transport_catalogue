#pragma once
#include <string>
#include <vector>
#include <unordered_map>
/*
 * В этом файле вы можете разместить классы/структуры, которые являются частью
 * предметной области (domain) вашего приложения и не зависят от транспортного
 * справочника. Например Автобусные маршруты и Остановки.
 *
 * Их можно было бы разместить и в transport_catalogue.h, однако вынесение их в
 * отдельный заголовочный файл может оказаться полезным, когда дело дойдёт до
 * визуализации карты маршрутов: визуализатор карты (map_renderer) можно будет
 * сделать независящим от транспортного справочника.
 *
 * Если структура вашего приложения не позволяет так сделать, просто оставьте
 * этот файл пустым.
 *
 */
namespace catalogue::structures
{

  struct Coordinates
  {
    double lat;
    double lng;
    bool operator==(const Coordinates &other) const;
    bool operator!=(const Coordinates &other) const;
    Coordinates(double _lat, double _lng) : lat(_lat), lng(_lng) {}
  };

  /**
   * Структура остановки.
   * @param name string - имя остановки
   * @param latitude double - широта остановки
   * @param longitude double - долгота остановки
   * @note Сущность предназначена для хранения параметров одной остановки
   */
  struct Stop
  {
    std::string name;
    Coordinates coordinates;

    Stop(const std::string &_name, const Coordinates &_coordinates)
        : name(_name), coordinates(_coordinates) {}
    Stop(const Stop &other) : name(other.name), coordinates(other.coordinates) {}
    Stop(Stop &&other)
        : name(std::move(other.name)),
          coordinates(std::move(other.coordinates)) {}
    Stop &operator=(Stop &&other)
    {
      name = std::move(other.name);
      coordinates = std::move(other.coordinates);
      return *this;
    }
    bool operator==(const Stop &rhs) const
    {
      return this->name == rhs.name && this->coordinates == rhs.coordinates;
    }
  };

  struct Bus
  {
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
  struct DistanceHasher
  {
    size_t operator()(const std::pair<Stop *, Stop *> &stops) const
    {
      return hasher(stops.first) + hasher(stops.second) * 42;
    }

  private:
    std::hash<const void *> hasher;
  };

  struct DistanceStatistics
  {
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
  struct BusStatistics
  {
    size_t stops;
    size_t unique_stops;
    DistanceStatistics distance_statistics;
  };

} // namespace catalogue::structures

struct StopRequest
{
  std::string name;
  double latitude;
  double longitude;
};

struct StopRequestDistance
{
  std::string from;
  std::string to;
  double distance;
};

struct BusRequest
{
  std::string name;
  std::vector<std::string> stops;
  bool is_roundtrip;
};

struct StatRequest
{
  int id;
  std::string type;
  std::string name;
};
