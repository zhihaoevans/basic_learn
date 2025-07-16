#include <grpcpp/grpcpp.h>
#include "math.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using math::Request;
using math::Response;
using math::Calculator;

class CalculatorServiceImpl final : public Calculator::Service {
  Status Add(ServerContext* context, const Request* request, Response* reply) override {
    reply->set_result(request->a() + request->b());
    return Status::OK;
  }

  Status Multiply(ServerContext* context, const Request* request, Response* reply) override {
    reply->set_result(request->a() * request->b());
    return Status::OK;
  }
};

int main() {
  std::string server_address("localhost:50051");
  CalculatorServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
  return 0;
}
