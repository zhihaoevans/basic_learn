#include <grpcpp/grpcpp.h>
#include "math.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using math::Request;
using math::Response;
using math::Calculator;

class MathClient {
public:
  MathClient(std::shared_ptr<Channel> channel) 
    : stub_(Calculator::NewStub(channel)) {}

  int Add(int a, int b) {
    Request request;
    request.set_a(a);
    request.set_b(b);

    Response response;
    ClientContext context;

    Status status = stub_->Add(&context, request, &response);
    return status.ok() ? response.result() : -1;
  }

  int Multiply(int a, int b) {
    Request request;
    request.set_a(a);
    request.set_b(b);

    Response response;
    ClientContext context;

    Status status = stub_->Multiply(&context, request, &response);
    return status.ok() ? response.result() : -1;
  }

private:
  std::unique_ptr<Calculator::Stub> stub_;
};

int main() {
  MathClient client(grpc::CreateChannel(
    "localhost:50051", grpc::InsecureChannelCredentials()));

  std::cout << "3 + 5 = " << client.Add(3, 5) << std::endl;
  std::cout << "3 * 5 = " << client.Multiply(3, 5) << std::endl;
  return 0;
}
