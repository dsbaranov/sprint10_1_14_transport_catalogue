#include "request_handler.h"
/*
 * Здесь можно было бы разместить код обработчика запросов к базе, содержащего
 * логику, которую не хотелось бы помещать ни в transport_catalogue, ни в json
 * reader.
 *
 * Если вы затрудняетесь выбрать, что можно было бы поместить в этот файл,
 * можете оставить его пустым.
 */
using namespace catalogue::structures;
using namespace std::literals;
RequestHandler::RequestHandler(TransportCatalogue &catalogue)
    : catalogue_(catalogue) {}

void RequestHandler::AddStops(const std::vector<StopRequest> &requests)
{
  if (requests.empty())
  {
    return;
  }
  for (const StopRequest &request : requests)
  {
    catalogue_.AddStop({request.name, {request.latitude, request.longitude}});
  }
}
void RequestHandler::AddDistances(
    const std::vector<StopRequestDistance> &requests)
{
  if (requests.empty())
  {
    return;
  }
  for (const StopRequestDistance &request : requests)
  {
    Stop *from_ptr = catalogue_.FindStop(request.from);
    assert(from_ptr != nullptr);
    Stop *to_ptr = catalogue_.FindStop(request.to);
    assert(to_ptr != nullptr);
    catalogue_.SetDistance(std::make_pair(from_ptr, to_ptr), request.distance);
  }
}
void RequestHandler::AddBusses(const std::vector<BusRequest> &requests)
{
  if (requests.empty())
  {
    return;
  }
  for (const BusRequest &request : requests)
  {
    std::vector<Stop *> bus_stops;
    bus_stops.reserve(request.stops.size());
    for (const std::string &stop_name : request.stops)
    {
      Stop *stop_ptr = catalogue_.FindStop(stop_name);
      assert(stop_ptr != nullptr);
      bus_stops.push_back(stop_ptr);
    }
    std::vector<Stop *> stops(bus_stops.begin(), bus_stops.end());
    if (request.is_roundtrip)
    {
      stops.insert(stops.end(), *stops.begin());
    }
    else
    {
      stops.insert(stops.end(), std::next(bus_stops.rbegin()), bus_stops.rend());
    }

    Bus new_bus{
        request.name, stops};
    catalogue_.AddBus(new_bus);
  }
}

Response RequestHandler::GetStatistics(const StatRequest &request) const
{
  if (request.type == "Stop"s)
  {
    Stop *stop_ptr = catalogue_.FindStop(request.name);
    if (!stop_ptr)
    {
      return ErrorResponse(request.id);
    }
    const std::set<std::string_view> &buses = catalogue_.FindBusesByStop(stop_ptr);
    return StopResponse{request.id, buses};
  }
  else if (request.type == "Bus"s)
  {
    Bus *bus_ptr = catalogue_.FindBus(request.name);
    if (!bus_ptr)
    {
      return ErrorResponse(request.id);
    }
    [[maybe_unused]] BusStatistics statistics = catalogue_.GetBusStatistics(bus_ptr);
    // int request_id;
    // size_t stop_count;
    // size_t unique_stop_count;
    // double route_length;
    // double curvature;
    return BusResponse{request.id, static_cast<int>(statistics.stops), static_cast<int>(statistics.unique_stops), statistics.distance_statistics.distance, statistics.distance_statistics.curvature};
  }
  return ErrorResponse(request.id);
}