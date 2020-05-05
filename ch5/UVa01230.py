# 0.000s in Python

def main():
    N = int(input())
    for i in range(N):
        x, y, z = map(int, input().split())
        print(pow(x, y, z))
main()