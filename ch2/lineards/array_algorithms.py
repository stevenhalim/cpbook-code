import bisect

# we will gradually convert the C++17 version to Python 3 soon

# typedef struct {
#   int id;
#   int solved;
#   int penalty;
# } team;

# bool icpc_cmp(team a, team b) {
#   if (a.solved != b.solved) // can use this primary field to decide sorted order
#     return a.solved > b.solved;   // ICPC rule: sort by number of problem solved
#   else if (a.penalty != b.penalty)       // a.solved == b.solved, but we can use
#                                        // secondary field to decide sorted order
#     return a.penalty < b.penalty;       // ICPC rule: sort by descending penalty
#   else                        // a.solved == b.solved AND a.penalty == b.penalty
#     return a.id < b.id;                      // sort based on increasing team ID
# }

def main():
    arr = [10, 7, 2, 15, 4]
    # sort descending with list
    arr.sort()
    arr.reverse()
    for val in arr:
      print(val, end=' ')                        # access the values
    print()
    print("==================")

  # shuffle(v.begin(), v.end(), default_random_engine()); // shuffle the content
  # for (auto &val : v)
  #   printf("%d ", val);
  # printf("\n");
  # printf("==================\n");
  # partial_sort(v.begin(), v.begin()+2, v.end()); // partial_sort demo
  # for (auto &val : v)
  #   printf("%d ", val);
  # printf("\n");
  # printf("==================\n");


  # // multi-field sorting example, suppose we have 4 ICPC teams
  # team nus[4] = { {1, 1, 10}, 
  #                 {2, 3, 60},
  #                 {3, 1, 20},
  #                 {4, 3, 60} };

  # // without sorting, they will be ranked like this:
  # for (int i = 0; i < 4; ++i)
  #   printf("id: %d, solved: %d, penalty: %d\n",
  #          nus[i].id, nus[i].solved, nus[i].penalty);

  # sort(nus, nus+4, icpc_cmp);           // sort using a comparison function
  # printf("==================\n");
  # // after sorting using ICPC rule, they will be ranked like this:
  # for (int i = 0; i < 4; ++i)
  #   printf("id: %d, solved: %d, penalty: %d\n",
  #          nus[i].id, nus[i].solved, nus[i].penalty);
  # printf("==================\n");

  # // there is a technique for multi-field sorting if the sort order is "standard"
  # // use pair (for 2 fields) or tuple (for >= 3 fields) in C++ and put the highest priority in front
  # typedef tuple<int, string, string> state;
  # state a = make_tuple(10, "steven", "grace");   // old way
  # state b = {7, "steven", "halim"};              // C++17 way
  # state c = {7, "steven", "felix"};
  # state d = {9, "a", "b"};
  # vector<state> test;
  # test.push_back(a);
  # test.push_back(b);
  # test.push_back(c);
  # test.push_back(d);
  # for (auto &[value, name1, name2] : test)
  #   printf("value: %d, name1 = %s, name2 = %s\n", value, name1.c_str(), name2.c_str());
  # printf("==================\n");
  # sort(test.begin(), test.end());                // use built-in comparator
  # // sorted ascending based on value, then based on name1,
  # // then based on name2, in that order!
  # for (auto &[value, name1, name2] : test)
  #   printf("value: %d, name1 = %s, name2 = %s\n", value, name1.c_str(), name2.c_str());
  # printf("==================\n");

    # binary search using lower bound
    arr.sort()                                    # sort ascending again
    i = bisect.bisect_left(arr, 7)                # found
    print("{}".format(i))

    j = bisect.bisect_left(arr, 77)               # not found
    if j == len(arr):
        # arr is of size 5 -> arr[0], arr[1], arr[2], arr[3], arr[4]
        # if lower_bound cannot find the required value,
        # it will return len(arr)
        # thus, testing whether j == len(arr)
        # can detect this "not found" issue
        print("77 not found")
    print("==================")

    # sometimes these two useful simple macros are used
    print("min(10, 7) = {}".format(min(10, 7)))
    print("max(10, 7) = {}".format(max(10, 7)))

main()
