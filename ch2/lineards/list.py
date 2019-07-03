from collections import deque 

def main():
    s = []
    print("{:d}".format(len(s) == 0))            # s is empty, true (1)
    print("==================")
    s.append('a')
    s.append('b')
    s.append('c')
    # stack is LIFO, thus the content of s is currently like this:
    # c <- top
    # b
    # a
    print("{:s}".format(s[-1]))                  # output 'c'
    s.pop();                                     # pop topmost
    print("{:s}".format(s[-1]))                  # output 'b'
    print("{:d}".format(len(s) == 0))            # s is not empty, false
    print("==================")

    q = deque([])
    print("{:d}".format(len(q) == 0))            # q is empty, true (1)
    print("==================")
    while len(s) != 0:                           # s has 2 more items
        q.append(s[-1]);                         # enqueue 'b' and 'a'
        s.pop();
    q.append('z')                                # add one more item
    print("{:s}".format(q[0]))                   # prints 'b'
    print("{:s}".format(q[-1]))                  # prints 'z'

    # output 'b', 'a', then 'z' (until queue is empty), according to the insertion order above
    print("==================")
    while len(q) != 0: 
        print("{:s}".format(q[0]))               # take the front first
        q.popleft();                             # before popping it


    print("==================")
    d = deque([])
    d.append('a')
    d.append('b')
    d.append('c')
    print("{:s} - {:s}".format(d[0], d[-1]))     # prints 'a - c'
    d.appendleft('d')
    print("{:s} - {:s}".format(d[0], d[-1]))     # prints 'd - c'
    d.pop()
    print("{:s} - {:s}".format(d[0], d[-1]))     # prints 'd - b'
    d.popleft()
    print("{:s} - {:s}".format(d[0], d[-1]))     # prints 'a - b'

if __name__ == "__main__":
    main()
