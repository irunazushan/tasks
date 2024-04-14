#include <bitset>
#include <iostream>

bool isIndexInBounds(size_t startPtrIndex, size_t lengthForInvertion,
                     size_t lengthData) {
  return (startPtrIndex + lengthForInvertion <= lengthData);
}

template <class T>
void invertUnit(T* startBit, size_t lengthInUnits, size_t startPtrIndex,
                size_t lengthOfArray) {
  if (!isIndexInBounds(startPtrIndex, lengthInUnits, lengthOfArray)) {
    std::cerr << "Error: invertion is out of range" << std::endl;
    return;
  }
  T mask = ~0;
  for (size_t i = 0; i < lengthInUnits; i++) {
    startBit[i] ^= mask;
  }
}

template <class T>
void invertBytes(T* startBit, size_t lengthInBytes, size_t startPtrIndex,
                 size_t lengthOfArray) {
  if (lengthInBytes != 0 &&
      !isIndexInBounds(startPtrIndex,
                       std::max((lengthInBytes / sizeof(T)), (size_t)1),
                       lengthOfArray)) {
    std::cerr << "Error: invertion is out of range" << std::endl;
    return;
  }
  T mask = (uint8_t)~0;
  size_t iterationPerUnit = sizeof(startBit[0]);
  size_t i = 0;
  size_t j = 1;
  while (lengthInBytes) {
    startBit[i] ^= mask;
    --lengthInBytes;
    if (lengthInBytes && j < iterationPerUnit) {
      mask <<= 8;
      j++;
    } else {
      mask = (uint8_t)~0;
      j = 1;
      i++;
    }
  }
}

template <class T>
void showBits(const T* data, size_t size) {
  size_t amountOfUnits = size / sizeof(data[0]);
  for (int i = amountOfUnits - 1; i >= 0; i--) {
    std::cout << std::bitset<(sizeof(T) * 8)>(static_cast<T>(data[i])) << ' ';
  }
  std::cout << '\n';
}

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
  return 0;
}