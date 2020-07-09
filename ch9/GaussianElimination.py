def GaussianElimination(N, mat):
  for i in range(N-1):
    l = i
    for j in range(i+1, N):
      if abs(mat[j][i]) > abs(mat[l][i]):
        l = j
    for k in range(i, N+1):
      mat[i][k], mat[l][k] = mat[l][k], mat[i][k]
    for j in range(i+1, N):
      for k in range(N, i-1, -1):
        mat[j][k] -= mat[i][k] * mat[j][i] / mat[i][i]

    ans = [0] * N
  for j in range(N-1, -1, -1):
    t = 0.0
    for k in range(j+1, N):
      t += mat[j][k] * ans[k]
    ans[j] = (mat[j][N]-t) / mat[j][j]

  return ans


def main():
  mat = [None] * 3
  mat[0] = [1, 1, 2, 9]
  mat[1] = [2, 4, -3, 1]
  mat[2] = [3, 6, -5, 0]

  X = GaussianElimination(3, mat)
  print('X = %.1lf, Y = %.1lf, Z = %.1lf' % (X[0], X[1], X[2]))


main()
