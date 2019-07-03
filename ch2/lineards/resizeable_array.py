def main():
    # Python does not have static array
    v = [5] * 5                                  # Initial size (5) and initial value {5,5,5,5,5}
    
    print("v[2] = {}".format(v[2]))              # 5

    for i in range(5):
        v[i] = 7+i;                              # v = {7,8,9,10,11}

    print("v[2] = {}".format(v[2]))              # 9

    # arr[5] = 5;   # index out of range error generated as index 5 does not exist
    # uncomment the line above to see the error

    v.append(77)                                 # list will resize itself after appending
    print("v[5] = {}".format(v[5]))              # 77

main()
