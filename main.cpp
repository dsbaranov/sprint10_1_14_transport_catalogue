#include "json_reader.h"
#include "request_handler.h"
#include "transport_catalogue.h"
#include "map_renderer.h"
#include "svg.h"
// #include <fstream>
int main()
{
  // {
  //   TransportCatalogue catalogue;
  //   RequestHandler request_handler(catalogue);
  //   JsonReader reader(request_handler);

  //   std::ifstream f_input("../input.json");
  //   if (f_input.is_open())
  //     reader.ReadStreamAndWriteStream(f_input, std::cout);
  // }
  {
    TransportCatalogue catalogue;
    RequestHandler request_handler(catalogue);
    MapRenderer renderer;
    JsonReader reader(request_handler, renderer);

    reader.ReadStreamAndWriteStream(std::cin, std::cout);
  }
}