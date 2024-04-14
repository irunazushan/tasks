#include "invertor.h"

int main() {
  std::cout << "\nTest 0:" << std::endl;
  {
    uint16_t data[10] = {0};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInUnits = 4;
    size_t startPtrIndex = 2;
    invertUnit((data + startPtrIndex), lengthInUnits, startPtrIndex,
               sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';

    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 1:" << std::endl;
  {
    uint8_t data[8] = {0};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInUnits = 3;
    size_t startPtrIndex = 5;
    invertUnit((data + startPtrIndex), lengthInUnits, startPtrIndex,
               sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';

    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 2:" << std::endl;
  {
    uint64_t data[5] = {12, 1235, 55555, 6816, 505};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInBytes = 8;
    size_t startPtrIndex = 0;
    invertBytes((data + startPtrIndex), lengthInBytes, startPtrIndex,
                sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 3:" << std::endl;
  {
    char data[10] = {'A', 'B', 'C', 'D', 'E'};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInBytes = 4;
    size_t startPtrIndex = 3;
    invertBytes((data + startPtrIndex), lengthInBytes, startPtrIndex,
                sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 4:" << std::endl;
  {
    uint32_t data[7] = {0};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInBytes = 9;
    size_t startPtrIndex = 3;
    invertBytes((data + startPtrIndex), lengthInBytes, startPtrIndex,
                sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 5: Проверка на выход из границ массива" << std::endl;
  {
    uint32_t data[7] = {0};
    size_t lengthInUnits = 9;
    size_t startPtrIndex = 3;
    invertUnit((data + startPtrIndex), lengthInUnits, startPtrIndex,
               sizeof(data) / sizeof(data[0]));
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 6: Проверка на выход из границ массива" << std::endl;
  {
    uint64_t data[5] = {0};
    size_t lengthInBytes = 1;
    size_t startPtrIndex = 10;
    invertBytes((data + startPtrIndex), lengthInBytes, startPtrIndex,
                sizeof(data) / sizeof(data[0]));
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 7: Проверка на выход из границ массива" << std::endl;
  {
    uint64_t data[5] = {0};
    size_t lengthInBytes = 9;
    size_t startPtrIndex = 9;
    invertBytes((data + startPtrIndex), lengthInBytes, startPtrIndex,
                sizeof(data) / sizeof(data[0]));
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 8: Вставка битов" << std::endl;
  {
    uint64_t data[] = {15, 15};
    size_t bitIndexes[] = {3, 4, 9, 100, 101, 102, 103};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInBytes = 15;
    size_t startPtrIndex = 0;
    invertBits((data + startPtrIndex),
               sizeof(bitIndexes) / sizeof(bitIndexes[0]), bitIndexes,
               lengthInBytes, startPtrIndex, sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 9: Вставка битов" << std::endl;
  {
    char data[5] = {'F', 'T', 'T'};
    size_t bitIndexes[] = {0, 1, 2, 5, 6, 9, 20, 21, 22, 24, 25};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInBytes = 4;
    size_t startPtrIndex = 1;
    invertBits((data + startPtrIndex),
               sizeof(bitIndexes) / sizeof(bitIndexes[0]), bitIndexes,
               lengthInBytes, startPtrIndex, sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 10: Вставка битов" << std::endl;
  {
    uint64_t data[3] = {0};
    size_t bitIndexes[] = {5, 6, 7, 8, 9, 10, 50, 51, 52, 100, 101};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInBytes = 15;
    size_t startPtrIndex = 1;
    invertBits((data + startPtrIndex),
               sizeof(bitIndexes) / sizeof(bitIndexes[0]), bitIndexes,
               lengthInBytes, startPtrIndex, sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 11: Вставка битов" << std::endl;
  {
    uint8_t data[10] = {0};
    size_t bitIndexes[] = {0, 1, 5, 6, 7, 23, 24, 25, 35, 36, 37, 38};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInBytes = 6;
    size_t startPtrIndex = 4;
    invertBits((data + startPtrIndex),
               sizeof(bitIndexes) / sizeof(bitIndexes[0]), bitIndexes,
               lengthInBytes, startPtrIndex, sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';
    showBits(data, sizeof(data));
  }

  std::cout << "\nTest 12: Вставка битов за выделенной памятью" << std::endl;
  {
    uint8_t data[10] = {0};
    size_t bitIndexes[] = {2, 4, 21};
    std::cout << "Биты до инвертирования:" << '\n';
    showBits(data, sizeof(data));
    size_t lengthInBytes = 2;
    size_t startPtrIndex = 8;
    invertBits((data + startPtrIndex),
               sizeof(bitIndexes) / sizeof(bitIndexes[0]), bitIndexes,
               lengthInBytes, startPtrIndex, sizeof(data) / sizeof(data[0]));
    std::cout << "Биты после инвертирования:" << '\n';
    showBits(data, sizeof(data));
  }
  return 0;
}