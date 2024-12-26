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
RequestHandler::RequestHandler(TransportCatalogue &catalogue)
    : catalogue_(catalogue) {}

void RequestHandler::AddStops(const std::vector<StopRequest> &requests) {
  for (const StopRequest &request : requests) {
    catalogue_.AddStop({request.name, {request.latitude, request.longitude}});
  }
}
void RequestHandler::AddDistances(
    const std::vector<StopRequestDistance> &requests) {
  for (const StopRequestDistance &request : requests) {
    Stop *from_ptr = catalogue_.FindStop(request.from);
    assert(from_ptr != nullptr);
    Stop *to_ptr = catalogue_.FindStop(request.to);
    assert(to_ptr != nullptr);
    catalogue_.SetDistance(std::make_pair(from_ptr, to_ptr), request.distance);
  }
}
void RequestHandler::AddBusses(const std::vector<BusRequest> &requests) {
  for (const BusRequest &request : requests) {
    std::vector<Stop *> bus_stops;
    bus_stops.reserve(request.stops.size());
    for (const std::string &stop_name : request.stops) {
      Stop *stop = catalogue_.FindStop(stop_name);
      assert(stop != nullptr);
      bus_stops.push_back(stop);
    }

    Bus new_bus{request.name, bus_stops};
  }
}