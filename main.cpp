#include "json_reader.h"
#include "request_handler.h"
#include "transport_catalogue.h"
int main()
{
  TransportCatalogue catalogue;
  RequestHandler request_handler(catalogue);
  JsonReader reader(request_handler);
  /*
   * Примерная структура программы:
   *
   * Считать JSON из stdin
   * Построить на его основе JSON базу данных транспортного справочника
   * Выполнить запросы к справочнику, находящиеся в массива "stat_requests",
   * построив JSON-массив с ответами Вывести в stdout ответы в виде JSON
   */
}