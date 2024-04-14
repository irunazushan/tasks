#ifndef __INVERTOR__H
#define __INVERTOR__H

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
void invertBits(T* startBit, size_t amountEl, size_t* bitIndexes,
                size_t lengthInBytes, size_t startPtrIndex,
                size_t lengthOfArray) {
  if (lengthInBytes != 0 &&
      !isIndexInBounds(startPtrIndex,
                       std::max((lengthInBytes / sizeof(T)), (size_t)1),
                       lengthOfArray)) {
    std::cerr << "Error: invertion is out of range" << std::endl;
    return;
  }
  size_t used = 0;
  size_t i = 0;
  size_t nextCell = 0;
  size_t iterationUnit = sizeof(T) * 8;
  while (used < amountEl) {
    if (!isIndexInBounds(startPtrIndex * iterationUnit, bitIndexes[used],
                         lengthOfArray * iterationUnit)) {
      std::cerr << "Error: Bit " << bitIndexes[used]
                << " for invertion is out of range" << std::endl;
      break;
    }
    if (bitIndexes[used] - nextCell < iterationUnit) {
      startBit[i] ^= static_cast<T>(1) << (bitIndexes[used] - nextCell);
      ++used;
    } else {
      i++;
      nextCell += iterationUnit;
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

#endif