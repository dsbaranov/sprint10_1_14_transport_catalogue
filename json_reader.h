#include "request_handler.h"

#pragma once

/*
 * Здесь можно разместить код наполнения транспортного справочника данными из
 * JSON, а также код обработки запросов к базе и формирование массива ответов в
 * формате JSON
 */

class JsonReader
{
public:
    JsonReader(const RequestHandler &handler);

private:
    const RequestHandler &handler_;
};