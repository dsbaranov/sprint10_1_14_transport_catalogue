#include "domain.h"

using namespace std::literals;
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

  // Coordinates
  bool Coordinates::operator==(const Coordinates &other) const
  {
    return lat == other.lat && lng == other.lng;
  }
  bool Coordinates::operator!=(const Coordinates &other) const
  {
    return !(*this == other);
  }

} // namespace catalogue::structures

ErrorResponse::ErrorResponse(int id) : request_id(id), error_message("not found"s) {}

Response::Response(std::nullptr_t) : value_(nullptr) {}
Response::Response(const StopResponse &value) : value_(value) {}
Response::Response(const BusResponse &value) : value_(value) {}
Response::Response(const ErrorResponse &value) : value_(value) {}

ResponseValue Response::GetValue() const
{
  return value_;
}

bool Response::IsBusResponse() const
{
  return Is<BusResponse>();
}
bool Response::IsStopResponse() const
{
  return Is<StopResponse>();
}
bool Response::IsErrorResponse() const
{
  return Is<ErrorResponse>();
}

const StopResponse &Response::AsStop() const
{
  return ExtractValue<StopResponse>();
}
const BusResponse &Response::AsBus() const
{
  return ExtractValue<BusResponse>();
}
const ErrorResponse &Response::AsError() const
{
  return ExtractValue<ErrorResponse>();
}