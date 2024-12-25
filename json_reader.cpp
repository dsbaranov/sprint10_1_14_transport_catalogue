#include "json_reader.h"

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из
 * JSON, а также код обработки запросов к базе и формирование массива ответов в
 * формате JSON
 */
JsonReader::JsonReader(const RequestHandler &handler) : handler_(handler) {}

void JsonReader::ReadStream(std::istream &input)
{
    auto request_map = json::Load(input).GetRoot().AsMap();
    std::vector<BusRequest> bus_requests;
    std::vector<StopRequest> stop_requests;
    std::vector<StopRequestDistance> stop_distances;
    std::vector<StatRequest> stat_requests;
    if (request_map.count("base_requests"s) != 0)
    {
        const auto &json_base_requests = request_map.at("base_requests").AsArray();
        for (const auto &json_base_request : json_base_requests)
        {
            assert(json_base_request.IsMap());
            const auto &json_request = json_base_request.AsMap();
            const auto &request_name = json_request.at("name").AsString();
            if (json_request.at("type").AsString() == "Stop"sv)
            {
                stop_requests.push_back({json_request.at("name").AsString(),
                                         json_request.at("latitude").AsDouble(),
                                         json_request.at("longitude").AsDouble()});
                if (json_request.count("road_distances") != 0)
                {
                    const auto &relative_distances = json_request.at("road_distances").AsMap();
                    for (const auto &[rel_name, json_rel_distance] : relative_distances)
                    {
                        stop_distances.push_back({request_name,
                                                  rel_name,
                                                  json_rel_distance.AsDouble()});
                    }
                }
            }
            else if (
                json_request.at("type").AsString() == "Bus"sv)
            {
                const auto &json_bus_stops = json_request.at("stops").AsArray();
                std::vector<std::string> bus_stops;
                bus_stops.reserve(json_bus_stops.size());
                for (const auto &json_stop : json_bus_stops)
                {
                    bus_stops.push_back(json_stop.AsString());
                }
                bus_requests.push_back({request_name,
                                        bus_stops,
                                        json_request.at("is_roundtrip").AsBool()});
            }
        }
    }
    if (request_map.count("stat_requests"s) != 0)
    {
        auto &json_stat_requests = request_map["stat_requests"s].AsArray();
        for (const auto &json_stat_request : json_stat_requests)
        {
            assert(json_stat_request.IsMap());
            const auto &json_request = json_stat_request.AsMap();
            stat_requests.push_back({json_request.at("id"s).AsInt(), json_request.at("type"s).AsString(), json_request.at("name").AsString()});
        }
    }
    assert(bus_requests.size() == 1 && stop_requests.size() == 2 && stop_distances.size() == 2 && stat_requests.size() == 2);
}