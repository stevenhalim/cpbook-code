#include <bits/stdc++.h>
using namespace std;

typedef pair<int, string> is;

int main() {
  // suppose we enter these 7 money-name pairs below
  /*
  100 john
  10 billy
  20 andy
  100 steven
  70 felix
  2000 grace
  70 martin
  */
  priority_queue<is> pq;
  pq.push(make_pair(100, "john"));               // insertion in O(log n)
  pq.push({10, "billy"});                        // alternative way with {}
  pq.push({20, "andy"});
  pq.push({100, "steven"});
  pq.push({70, "felix"});
  pq.push({2000, "grace"});
  pq.push({70, "martin"});
  // priority queue will arrange items in 'heap' based
  // on the first key in pair, which is money (integer), largest first
  // if first keys tie, use second key, which is name, largest first
  
  // the internal content of pq heap MAY be something like this:
  // re-read (max) heap concept if you do not understand this diagram
  // the primary keys are money (integer), secondary keys are names (string)!
  //                        (2000,grace)
  //           (100,steven)               (70,martin)   
  //     (100,john)   (10,billy)     (20,andy)  (70,felix)

  // let's print out the top 3 person with most money
  // O(1) to access the top / max element
  auto &[score, name] = pq.top();                // C++17 style
  printf("%s has %d $\n", name.c_str(), score);

  pq.pop(); // O(log n) to delete the top and repair the structure
  // [score, name] still binded to pq.top() as we use `&' above
  // be careful not to overuse & to avoid accidental by reference bug
  printf("%s has %d $\n", name.c_str(), score);

  pq.pop();
  printf("%s has %d $\n", name.c_str(), score);

  return 0;
}
