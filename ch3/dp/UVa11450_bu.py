# UVa 11450 - Wedding Shopping - Bottom Up (faster than Top Down)

def main():

    TC = int(input())
    for tc in range(TC):

        MAX_gm = 30                                        # 20 garments at most and 20 models per garment at most
        MAX_M = 210                                        # maximum budget is 200

        price = [[-1 for i in range(MAX_gm)] for j in range(MAX_gm)] # price[g (<= 20)][model (<= 20)]
        
        #reachable = [[False for i in range(MAX_M)] for j in range(MAX_gm)] # reachable table[g (<= 20)][money (<= 200)]
        
        # if using space saving technique
        reachable = [[False for i in range(MAX_M)] for j in range(2)] # reachable table[ONLY TWO ROWS][money (<= 200)]

        M, C = [int(x) for x in input().split(" ")]
        for g in range(C):
            s = [int(x) for x in input().split(" ")]
            price[g][0] = s[0]                             # store number of models in price[g][0]
            for k in range(1, price[g][0]+1):
                price[g][k] = s[k]

        # initial values (base cases), using first garment g = 0
        for k in range(1, price[0][0]+1):
            if (M-price[0][k] >= 0):
                reachable[0][M-price[0][k]] = True


        # for g in range(1, C):                            # for each remaining garment
        #   for money in range(0, M):
        #       if (reachable[g-1][money]):
        #           for k in range(1, price[g][0]+1):
        #               if (money-price[g][k] >= 0):
        #                   reachable[g][money-price[g][k]] = True  # also reachable now

        # money = 0
        # while (money <= M and not reachable[C-1][money]):
        #   money += 1

        # then we modify the main loop in main a bit

        cur = 1                                            # we start with this row
        for g in range(1, C):                              # for each remaining garment
            reachable[cur] = [False for i in range(MAX_M)] # reset row
            for money in range(0, M):
                if (reachable[1-cur][money]):
                    for k in range(1, price[g][0]+1):
                        if (money-price[g][k] >= 0):
                            reachable[cur][money-price[g][k]] = True
            cur = 1-cur                                    # IMPORTANT technique: flip the two rows


        money = 0
        while (money <= M and not reachable[1-cur][money]):
            money += 1

        if (money == M+1):
            print("no solution")
        else:
            print(str(M-money))

main()
