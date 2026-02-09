#include <glog/logging.h>

#include <filesystem>
#include <string>
#include <thread>
#include <vector>

static void setup_logging(const std::string& dir) {
  std::filesystem::create_directories(dir);
  FLAGS_logtostderr = false;
  FLAGS_log_dir = dir;
  FLAGS_max_log_size = 1;
  google::InitGoogleLogging("logging_example");
}

int main(int argc, char** argv) {
  std::string log_dir = "logs";
  if (argc > 1) log_dir = argv[1];
  setup_logging(log_dir);

  LOG(INFO) << "info message";
  LOG(WARNING) << "warning message";
  LOG(ERROR) << "error message";

  int x = 5;
  LOG_IF(INFO, x > 3) << "conditional info when x>3";
  LOG_IF(WARNING, x % 2 == 1) << "conditional warning when x is odd";

  for (int i = 0; i < 50000; ++i) {
    LOG(INFO) << "rolling " << i;
  }

  google::ShutdownGoogleLogging();
  return 0;
}
