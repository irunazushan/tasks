#include <iostream>

#include "linked_list.h"

int main() {
  {
    std::cout << "TEST 0" << std::endl;
    LinkedList<int> ls{2, 3, 4, 5, 6, 7};
    std::cout << "Expecting output: 2,3,4,5,6,7\n";
    for (auto it = ls.begin(); it != ls.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "\nTEST 1" << std::endl;
    LinkedList<int> ls;
    ls.push_front(3);
    ls.push_front(4);
    ls.push_front(5);
    ls.push_front(6);
    ls.push_front(7);
    for (auto it = ls.begin(); it != ls.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    auto it = ls.begin();
    ++it;
    ++it;
    ls.erase_after(it);
    ls.erase_after(it);
    std::cout << "Expecting 4 and 3 will be deleted\n";
    for (auto it = ls.begin(); it != ls.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }

  {
    std::cout << "\nTEST 2" << std::endl;
    LinkedList<int> ls;
    ls.push_front(3);
    ls.push_front(4);
    ls.push_front(5);
    ls.push_front(6);
    ls.push_front(7);
    auto it = ls.find(5);
    ++it;
    std::cout << "Expecting next of the 5 node -> node 4\n";
    std::cout << *it << std::endl;
  }

  {
    std::cout << "\nTEST 3" << std::endl;
    LinkedList<int> ls{3, 4, 5, 6, 7};
    for (auto it = ls.begin(); it != ls.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "size before deleting: " << ls.size() << std::endl;
    ls.erase(4);
    ls.erase(6);
    ls.erase(7);
    std::cout << "size after deleting: " << ls.size() << std::endl;
    std::cout << "Expecting the list contains 3 and 5 \n";
    for (auto it = ls.begin(); it != ls.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}