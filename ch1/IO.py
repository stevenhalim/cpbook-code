# comment all lines and only uncomment demo code that you are interested with

# IO_in1.txt
import sys
inputs = iter(sys.stdin.readlines())
TC = int(next(inputs))
for _ in range(TC):
    print(sum(map(int, next(inputs).split())))

# # IO_in2.txt
# import sys
# for line in sys.stdin.readlines():
#     if line == '0 0\n': break
#     print(sum(map(int, line.split())))

# # IO_in3.txt
# import sys
# for line in sys.stdin.readlines():
#     print(sum(map(int, line.split())))

# # IO_in3.txt, same input file as before
# import sys
# for c, line in enumerate(sys.stdin.readlines(), 1):
#     print("Case %s: %s\n" % (c, sum(map(int, line.split()))))

# # IO_in3.txt, same input file as before
# import sys
# for c, line in enumerate(sys.stdin.readlines(), 1):
#     if c > 1: print()
#     print("Case %s: %s" % (c, sum(map(int, line.split()))))

# # IO_in4.txt
# import sys
# for line in sys.stdin.readlines():
#     print(sum(map(int, line.split()[1:]))) # skip the first integer

# # IO_in5.txt
# import sys
# for line in sys.stdin.readlines():
#     print(sum(map(int, line.split())))
