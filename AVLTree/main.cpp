#include "AVL.h"
#include <iostream>

int main() {
  avl_tree avl;

  for (int i = 0; i <= 1000; i++) {
    avl.add(i);
  }

  std::cout << "\n";

  avl.bshow();

  return 0;
}