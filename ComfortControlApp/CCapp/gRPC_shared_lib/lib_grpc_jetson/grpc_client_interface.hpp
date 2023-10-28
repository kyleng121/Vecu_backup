#ifndef GRPC_CLIENT_INTERFACE_HPP
#define GRPC_CLIENT_INTERFACE_HPP

#include <stdint.h>
#include <string>
#include <memory>

class GrpcClientInterface
{
public:
  ~GrpcClientInterface() = default;
  
  virtual uint32_t GetDatapoint(std::string& data_point) = 0;
  virtual int32_t SetDatapoint(std::string& data_point, int32_t value) = 0;
  virtual int32_t SetDatapoint(std::string& data_point, uint32_t value) = 0;
};

class ClientBuilder
{
public:
  ClientBuilder() = default;
  ~ClientBuilder() = default;

  std::shared_ptr<GrpcClientInterface> CreateClient(std::string ip_and_port);
};

#endif // GRPC_CLIENT_INTERFACE_HPP
