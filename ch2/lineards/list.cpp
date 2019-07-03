#include <bits/stdc++.h>
using namespace std;

int main() {
  stack<char> s;
  printf("%d\n", s.empty());                   // currently s is empty, true (1)
  printf("==================\n");
  s.push('a');
  s.push('b');
  s.push('c');
  // stack is LIFO, thus the content of s is currently like this:
  // c <- top
  // b
  // a
  printf("%c\n", s.top());                       // output 'c'
  s.pop();                                       // pop topmost
  printf("%c\n", s.top());                       // output 'b'
  printf("%d\n", s.empty());                     // output false (0)
  printf("==================\n");

  queue<char> q;
  printf("%d\n", q.empty());                     // output true (1)
  printf("==================\n");
  while (!s.empty()) {                           // s has 2 more items
    q.push(s.top());                             // enqueue 'b' and 'a'
    s.pop();
  }
  q.push('z');                                   // add one more item
  printf("%c\n", q.front());                     // prints 'b'
  printf("%c\n", q.back());                      // prints 'z'

  // output 'b', 'a', then 'z' (until queue is empty), according to the insertion order above
  printf("==================\n");
  while (!q.empty()) {
    printf("%c\n", q.front());                   // take the front first
    q.pop();                                     // before popping it
  }

  printf("==================\n");
  deque<char> d;
  d.push_back('a');
  d.push_back('b');
  d.push_back('c');
  printf("%c - %c\n", d.front(), d.back());      // prints 'a - c'
  d.push_front('d');
  printf("%c%c%c%c\n", d[0], d[1], d[2], d[3]);  // only in C++, 'dabc'
  printf("%c - %c\n", d.front(), d.back());      // prints 'd - c'
  d.pop_back();
  printf("%c - %c\n", d.front(), d.back());      // prints 'd - b'
  d.pop_front();
  printf("%c - %c\n", d.front(), d.back());      // prints 'a - b'

  return 0;
}
