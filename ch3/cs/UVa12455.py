import sys

def LSOne(S):
    return (-S) & S

def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        p = int(input())
        bars = list(map(int, input().split()))
        
        found = 0
        for i in range(1 << p): #iterate through all subsets
            sum = 0
            mask = i
            while mask > 0:
                ls = LSOne(mask)  #pick Least Sig Bit
                j = (ls ^ (ls-1)).bit_length()-1 #trailing zeroes
                sum += bars[j]
                mask -= ls
            if sum == n:
                found = 1
                break

        print("YES" if found else "NO") 
        
main()
