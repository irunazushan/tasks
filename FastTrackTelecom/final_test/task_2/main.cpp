#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::vector<int> sharedVector;
std::mutex mtx;

void writeToVector() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::lock_guard<std::mutex> lock(mtx);
    sharedVector.push_back(sharedVector.size());
    std::cout << "Записано: " << sharedVector.back() << std::endl;
  }
}

void readFromVector() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::lock_guard<std::mutex> lock(mtx);
    if (!sharedVector.empty()) {
      std::cout << "Чтение: " << sharedVector.back() << std::endl;
      sharedVector.pop_back();
    }
  }
}

int main() {
  std::thread writer(writeToVector);
  std::thread reader(readFromVector);
  std::thread reader2(readFromVector);

  writer.join();
  reader.join();
  reader2.join();

  return 0;
}