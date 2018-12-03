import java.util.*;

class AugmentedMatrix {
  public double[][] mat = new double[3][4];  // adjust this value as needed
  public AugmentedMatrix() {};
}

class ColumnVector {
  public double[] vec = new double[3];        // adjust this value as needed
  public ColumnVector() {};
}

class GaussianElimination {
  public static ColumnVector GE(int N, AugmentedMatrix Aug) {
    // input: N, Augmented Matrix Aug, output: Column vector X, the answer
    int i, j, k, l; double t;

    for (i = 0; i < N - 1; i++) {          // the forward elimination phase
      l = i;
      for (j = i + 1; j < N; j++)     // which row has largest column value
        if (Math.abs(Aug.mat[j][i]) > Math.abs(Aug.mat[l][i]))
          l = j;                                     // remember this row l
      // swap this pivot row, reason: minimize floating point error
      for (k = i; k <= N; k++) {        // t is a temporary double variable
        t = Aug.mat[i][k];
        Aug.mat[i][k] = Aug.mat[l][k];
        Aug.mat[l][k] = t;
      }
      for (j = i + 1; j < N; j++)   // the actual forward elimination phase
        for (k = N; k >= i; k--)
          Aug.mat[j][k] -= Aug.mat[i][k] * Aug.mat[j][i] / Aug.mat[i][i];
    }

    ColumnVector Ans = new ColumnVector();   // the back substitution phase
    for (j = N - 1; j >= 0; j--) {                       // start from back
      for (t = 0.0, k = j + 1; k < N; k++) t += Aug.mat[j][k] * Ans.vec[k];
      Ans.vec[j] = (Aug.mat[j][N] - t) / Aug.mat[j][j]; // the answer is here
    }
    return Ans;
  }

  public static void main(String[] args) {
    AugmentedMatrix Aug = new AugmentedMatrix();
    Aug.mat[0][0] = 1; Aug.mat[0][1] = 1; Aug.mat[0][2] = 2; Aug.mat[0][3] = 9;
    Aug.mat[1][0] = 2; Aug.mat[1][1] = 4; Aug.mat[1][2] = -3; Aug.mat[1][3] = 1;
    Aug.mat[2][0] = 3; Aug.mat[2][1] = 6; Aug.mat[2][2] = -5; Aug.mat[2][3] = 0;

    ColumnVector X = GE(3, Aug);
    System.out.printf("X = %.1f, Y = %.1f, Z = %.1f\n", X.vec[0], X.vec[1], X.vec[2]);
  }
}
