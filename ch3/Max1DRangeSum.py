n = 9
A = [4, -5, 4, -3, 4, 4, -4, 4, -5]
running_sum = ans = 0
for i in range(n):
    if running_sum + A[i] >= 0:
        running_sum += A[i]
        ans = max(ans, running_sum)
    else:
        running_sum = 0
print("Max 1D Range Sum =", ans)
