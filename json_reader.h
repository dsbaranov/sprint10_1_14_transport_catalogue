#include "request_handler.h"
#include "json.h"
#include "domain.h"
#pragma once
/*
 * Здесь можно разместить код наполнения транспортного справочника данными из
 * JSON, а также код обработки запросов к базе и формирование массива ответов в
 * формате JSON
 */
using namespace json;
using namespace std::literals;

class JsonReader
{
public:
    JsonReader(const RequestHandler &handler);

    void ReadStream(std::istream &input);

private:
    const RequestHandler &handler_;
};