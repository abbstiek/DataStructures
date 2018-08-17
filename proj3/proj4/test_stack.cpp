#include <iostream>
#include <string>
#include "stack.h"

using namespace std;
using namespace cop4530;

int main() {
  Stack<int> istack;
  Stack<string> sstack;

  cout << "Are the stacks empty?" << endl;
  cout << istack.empty() << endl;
  cout << sstack.empty() << endl << endl;

  istack.push(3);
  istack.push(4);
  istack.push(5);

  cout << istack << endl;

  sstack.push("hello");
  sstack.push("world");

  cout << sstack << endl << endl;

  Stack<int> istack2;

  cout << "istack != istack2 right now" << endl;
  cout << (istack == istack2) << endl << endl;

  istack2 = istack;

  cout << "istack == istack2 right now" << endl;
  cout << (istack == istack2) << endl << endl;

  return 0;
}