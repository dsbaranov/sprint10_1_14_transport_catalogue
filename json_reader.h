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
    JsonReader(RequestHandler &handler);

    void ReadStreamAndWriteStream(std::istream &input, std::ostream &out);

private:
    RequestHandler &handler_;
};