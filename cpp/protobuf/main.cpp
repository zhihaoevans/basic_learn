#include <iostream>
#include <fstream>
#include "person.pb.h"

int main() {
  // 创建并填充 Person 对象
  example::Person person;
  person.set_name("Alice");
  person.set_id(1234);
  person.set_email("alice@example.com");
  person.add_phone_numbers("+86-123456789");
  person.add_phone_numbers("+86-987654321");

  // 序列化到字符串
  std::string serialized_str;
  if (!person.SerializeToString(&serialized_str)) {
    std::cerr << "序列化失败!" << std::endl;
    return -1;
  }

  // 反序列化
  example::Person new_person;
  if (!new_person.ParseFromString(serialized_str)) {
    std::cerr << "反序列化失败!" << std::endl;
    return -1;
  }

  // 打印反序列化结果
  std::cout << "Name: " << new_person.name() << std::endl;
  std::cout << "ID: " << new_person.id() << std::endl;
  std::cout << "Email: " << new_person.email() << std::endl;
  std::cout << "Phone Numbers: ";
  for (const auto& num : new_person.phone_numbers()) {
    std::cout << num << ", ";
  }
  std::cout << std::endl;

  return 0;
}
