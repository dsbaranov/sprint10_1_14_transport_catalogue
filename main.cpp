#include "json_reader.h"
#include "request_handler.h"
#include "transport_catalogue.h"

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
    JsonReader reader(request_handler);
    reader.ReadStreamAndWriteStream(std::cin, std::cout);
  }
}