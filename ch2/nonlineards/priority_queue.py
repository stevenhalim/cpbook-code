import heapq

def main():
    # suppose we enter these 7 money-name pairs below
    '''
    100 john
    10 billy
    20 andy
    100 steven
    70 felix
    2000 grace
    70 martin
    '''
    pq = []
    pq.append((-100, "john"))
    pq.append((-10, "billy"))
    pq.append((-20, "andy"))
    pq.append((-100, "steven"))
    pq.append((-70, "felix"))
    pq.append((-2000, "grace"))
    pq.append((-70, "martin"))

    # priority queue will arrange items in 'heap' based
    # on the first key in pair, which is money (integer), largest first
    # if first keys tie, use second key, which is name, smallest first in python
    heapq.heapify(pq)

    # the internal content of pq heap MAY be something like this (we negated the weights to make python heap a max heap):
    # re-read (max) heap concept if you do not understand this diagram
    # the primary keys are money (integer), secondary keys are names (string)!
    #                         (2000,grace)
    #            (100,steven)               (70,martin)   


    #let's print out the top 3 person with most money
    result = heapq.heappop(pq);    # O(1) to access the top / max element and O(log n) to delete the top and repair the structure
    print('{:s} has {:d} $'.format(result[1], -result[0]))

    result = heapq.heappop(pq);
    print('{:s} has {:d} $'.format(result[1], -result[0]))

    result = heapq.heappop(pq);
    print('{:s} has {:d} $'.format(result[1], -result[0]))


if __name__ == "__main__":
    main()
