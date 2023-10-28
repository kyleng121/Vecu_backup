#include <iostream>
#include <string>

#include "lib_grpc_linux_pc/grpc_client_interface.hpp"

int main()
{
  std::cout << "this is testing grpc linux pc main" << std::endl;
  
  ClientBuilder myBuilder;
  std::shared_ptr<GrpcClientInterface> myClient = myBuilder.CreateClient("127.0.0.1:55555");

  std::string hierarchy("Vehicle.Cabin.Seat.Row1.DriverSide.Backrest.Lumbar.Height");
  myClient->SetDatapoint(hierarchy, uint32_t(40));

  std::string hierarchy2("Vehicle.Cabin.Button");
  uint32_t readValue = myClient->GetDatapoint(hierarchy2);
  std::cout << "Got value from " << hierarchy2 << " : " << readValue << std::endl;

  return 0;
}