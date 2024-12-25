#include "json_reader.h"
#include "request_handler.h"
#include "transport_catalogue.h"

#include <fstream>
int main()
{

  {
    TransportCatalogue catalogue;
    RequestHandler request_handler(catalogue);
    JsonReader reader(request_handler);

    std::ifstream f_input("../input.json");
    if (f_input.is_open())
      reader.ReadStream(f_input);
  }
  /*
   * Примерная структура программы:
   *
   * Считать JSON из stdin
   * Построить на его основе JSON базу данных транспортного справочника
   * Выполнить запросы к справочнику, находящиеся в массива "stat_requests",
   * построив JSON-массив с ответами Вывести в stdout ответы в виде JSON
   */
}