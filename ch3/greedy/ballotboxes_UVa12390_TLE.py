import sys, heapq, math

def main():
    inputs = sys.stdin.read().splitlines()
    ln = 0
    while True:
        N,B = map(int, inputs[ln].split())
        if N == -1 and B == -1: break
        ln += 1
       
        pq = [] # min pq in Python, we will insert negatives to make it max pq
        for _ in range(N):
            a = int(inputs[ln])
            ln += 1
            heapq.heappush(pq, (-a, -a, -1)) # state of tuple = (population_per_box, population, boxes)
        ln += 1 # skip this empty line

        B -= N; # every city must be assigned at least one box
        while True:
            B -= 1 # after that we do a greedy strategy using PQ, to give additional box to the city with currently highest ratio
            population_per_box, population, boxes = pq[0]
            if -population_per_box == 1.0: break # what's the point to continue, each city already have one box (maybe this optimization is not that useful)
            heapq.heappop(pq) # ok pop that
            heapq.heappush(pq, (population/(1-boxes), population, boxes-1))
            if B == 0: break # if don't have extra box to reduce overall load

        print(math.ceil(-pq[0][0])) # this is the final answer

main()
