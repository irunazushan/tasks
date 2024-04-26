#include <iostream>

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* ptr = arr;
    int fourthElement = *(ptr + 3);

    std::cout << "Потерянный найден: " << fourthElement << std::endl;

    return 0;
}