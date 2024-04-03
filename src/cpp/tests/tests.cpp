#include <gtest/gtest.h>

#include "../S21Matrix.h"

TEST(S21MatrixTest, GetRowsTest) {
  S21Matrix matrix(3, 3);
  EXPECT_EQ(matrix.GetRows(), 3);
}

TEST(S21MatrixTest, GetColsTest) {
  S21Matrix matrix(3, 3);
  EXPECT_EQ(matrix.GetRows(), 3);
}

TEST(S21MatrixTest, SetRows) {
  S21Matrix matrix(2, 2);
  matrix.SetRows(3);
  EXPECT_EQ(matrix.GetRows(), 3);
}

TEST(S21MatrixTest, DefoltCnst) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(S21MatrixTest, Coppy) {
  S21Matrix matrix(4, 4);
  matrix(2, 2) = 3;
  S21Matrix copy(matrix);
  EXPECT_EQ(copy.GetCols(), 4);
  EXPECT_EQ(copy(2, 2), 3);
}

TEST(S21MatrixTest, Transfer) {
  S21Matrix matrix(4, 4);
  matrix(2, 2) = 3;
  S21Matrix transfer(std::move(matrix));
  EXPECT_EQ(transfer.GetCols(), 4);
  EXPECT_EQ(transfer(2, 2), 3);
}

TEST(EqMatrixTest, EqualMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_TRUE(mat1.EqMatrix(mat2));
  EXPECT_TRUE(mat2.EqMatrix(mat1));
}

TEST(EqMatrixTest, UnequalMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(mat1.EqMatrix(mat2));
  EXPECT_FALSE(mat2.EqMatrix(mat1));
}

TEST(EqMatrixTest, UnequalSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 3);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(mat1.EqMatrix(mat2));
  EXPECT_FALSE(mat2.EqMatrix(mat1));
}

TEST(SumMatrixTest, Addition) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};
  double result[2][2] = {{6, 8}, {10, 12}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SumMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), result[i][j]);
    }
  }
}

TEST(SumMatrixTest, DifferentSizes) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW(mat1.SumMatrix(mat2), std::invalid_argument);
}

TEST(SumMatrixTest, EmptyMatrix) {
  double matrix[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix();

  EXPECT_THROW(mat1.SumMatrix(mat2), std::invalid_argument);
}

TEST(SubMatrixTest, SubtractMatrix) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 1}, {1, 2}};
  double expected[2][2] = {{-1, 1}, {2, 2}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SubMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(SubMatrixTest, DifferentSizes) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW(mat1.SubMatrix(mat2), std::invalid_argument);
}

TEST(SubMatrixTest, EmptyMatrix) {
  double matrix[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix();

  EXPECT_THROW(mat1.SubMatrix(mat2), std::invalid_argument);
}

TEST(MulNumberTest, MultiplyNumber) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 2;
  double expected[2][2] = {{2, 4}, {6, 8}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumberZero) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double num = 0;
  double expected[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumberNegative) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = -1;
  double expected[2][2] = {{-1, -2}, {-3, -4}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumberFraction) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 0.5;
  double expected[2][2] = {{0.5, 1}, {1.5, 2}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixIdentity) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double identity[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix identityMat = S21Matrix(3, 3);
  for (int i = 0; i < identityMat.GetRows(); i++) {
    for (int j = 0; j < identityMat.GetCols(); j++) {
      identityMat(i, j) = identity[i][j];
    }
  }

  mat.MulMatrix(identityMat);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), matrix[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixArbitrary) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{2, 0}, {0, 2}, {1, 1}};
  double expected[2][2] = {{5, 7}, {14, 16}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.MulMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixThrow) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[4][2] = {{2, 0}, {0, 2}, {1, 1}, {3, 3}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(4, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_ANY_THROW({ mat1.MulMatrix(mat2); });
}

TEST(TransposeTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double expected[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(TransposeTest, RectangularMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double expected[3][2] = {{1, 4}, {2, 5}, {3, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(TransposeTest, SingleElementMatrix) {
  double matrix[1][1] = {{42}};
  double expected[1][1] = {{42}};

  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = matrix[0][0];

  S21Matrix transposed = mat.Transpose();

  EXPECT_EQ(transposed.GetRows(), 1);
  EXPECT_EQ(transposed.GetCols(), 1);
  EXPECT_EQ(transposed(0, 0), expected[0][0]);
}

TEST(TransposeTest, NonSquareMatrix) {
  double matrix[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  double expected[2][3] = {{1, 3, 5}, {2, 4, 6}};

  S21Matrix mat = S21Matrix(3, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(DeterminantTest, SingleElementMatrix) {
  double matrix[1][1] = {{5}};

  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = matrix[0][0];

  double determinant = mat.Determinant();

  // Проверяем, что определитель матрицы из одного элемента равен значению этого
  // элемента
  EXPECT_EQ(determinant, matrix[0][0]);
}

TEST(DeterminantTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  double determinant = mat.Determinant();
  EXPECT_EQ(determinant, 0);
}

TEST(DeterminantTest, SpecificNonZeroDeterminant) {
  double matrix[3][3] = {{1, 2, 2}, {4, 5, 5}, {7, 8, 9}};
  double expectedDeterminant = -3;

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  double determinant = mat.Determinant();
  EXPECT_EQ(determinant, expectedDeterminant);
}

TEST(DeterminantTest, NonSquareMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  EXPECT_THROW(mat.Determinant(), std::logic_error);
}

TEST(CalcComplementsTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double expected[3][3] = {{-3, 6, -3}, {6, -12, 6}, {-3, 6, -3}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix complements = mat.CalcComplements();

  for (int i = 0; i < complements.GetRows(); i++) {
    for (int j = 0; j < complements.GetCols(); j++) {
      EXPECT_EQ(complements(i, j), expected[i][j]);
    }
  }
}

TEST(CalcComplementsTest, NonSquareMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  EXPECT_THROW(S21Matrix complements = mat.CalcComplements(), std::logic_error);
}

TEST(InverseMatrixTest, test1) {
  double matrix[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double matrix_throw[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double result[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  EXPECT_ANY_THROW({
    S21Matrix check = S21Matrix(2, 3);
    check.InverseMatrix();
  });
  EXPECT_ANY_THROW({
    S21Matrix check = S21Matrix(3, 3);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = matrix_throw[i][j];
      }
    }
    check.InverseMatrix();
  });
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix(3, 3);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = matrix[i][j];
      }
    }
    S21Matrix res = check.InverseMatrix();
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        EXPECT_EQ(res(i, j), result[i][j]);
      }
    }
  });
}

TEST(OperatorEqual, test1) {
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix(3, 4);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = i + j;
      }
    }
    S21Matrix result = S21Matrix();
    result = check;
    EXPECT_EQ(result.GetRows(), check.GetRows());
    EXPECT_EQ(result.GetCols(), check.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), check(i, j));
      }
    }
  });
}

TEST(OperatorEqual, test2) {
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix();
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = i + j;
      }
    }
    S21Matrix result = S21Matrix(2, 2);
    result = check;
    EXPECT_EQ(result.GetRows(), check.GetRows());
    EXPECT_EQ(result.GetCols(), check.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), check(i, j));
      }
    }
  });
}

TEST(OperatorPlus, test1) {
  EXPECT_NO_THROW({
    S21Matrix check1 = S21Matrix(3, 4);
    S21Matrix check2 = S21Matrix(3, 4);
    for (int i = 0; i < check1.GetRows(); i++) {
      for (int j = 0; j < check1.GetCols(); j++) {
        check1(i, j) = i + j;
        check2(i, j) = 2 * (i + j);
      }
    }
    S21Matrix result = S21Matrix(3, 4);
    result = check1 + check2;
    EXPECT_EQ(result.GetRows(), check1.GetRows());
    EXPECT_EQ(result.GetCols(), check1.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), check1(i, j) + check2(i, j));
      }
    }
  });
}

TEST(OperatorPlus, test2) {
  EXPECT_NO_THROW({
    S21Matrix check1 = S21Matrix(2, 3);
    S21Matrix check2 = S21Matrix(2, 3);
    for (int i = 0; i < check1.GetRows(); i++) {
      for (int j = 0; j < check1.GetCols(); j++) {
        check1(i, j) = i + j;
        check2(i, j) = 2 * (i + j);
      }
    }
    S21Matrix result = S21Matrix(2, 3);
    result = check1 + check2;
    EXPECT_EQ(result.GetRows(), check1.GetRows());
    EXPECT_EQ(result.GetCols(), check1.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), check1(i, j) + check2(i, j));
      }
    }
  });
}

TEST(OperatorPlus, test3) {
  EXPECT_ANY_THROW({
    S21Matrix check = S21Matrix(3, 4);
    S21Matrix result = S21Matrix(3, 3);
    S21Matrix result2 = result + check;
  });
}

TEST(OperatorMinus, test1) {
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix(3, 4);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = i + j;
      }
    }
    S21Matrix result = S21Matrix(3, 4);
    result = check - check;
    EXPECT_EQ(result.GetRows(), check.GetRows());
    EXPECT_EQ(result.GetCols(), check.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), 0);
      }
    }
  });
}

TEST(OperatorMinus, test2) {
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix(2, 3);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = i + j;
      }
    }
    S21Matrix result = S21Matrix(2, 3);
    result = check - check;
    EXPECT_EQ(result.GetRows(), check.GetRows());
    EXPECT_EQ(result.GetCols(), check.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), 0);
      }
    }
  });
}

TEST(OperatorMinus, test3) {
  EXPECT_ANY_THROW({
    S21Matrix check = S21Matrix(3, 4);
    S21Matrix result = S21Matrix(3, 3);
    result = result - check;
  });
}

TEST(OperatorMultNum, test1) {
  double result[2][2] = {{2, 4}, {6, 8}};
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix(2, 2);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = matrix1[i][j];
      }
    }
    check = check * 2;
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        EXPECT_EQ(check(i, j), result[i][j]);
      }
    }
  });
}

TEST(OperatorMultMatrix, test1) {
  double result[2][2] = {{2, 4}, {6, 8}};
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 0}, {0, 2}};
  EXPECT_NO_THROW({
    S21Matrix check1 = S21Matrix(2, 2);
    for (int i = 0; i < check1.GetRows(); i++) {
      for (int j = 0; j < check1.GetCols(); j++) {
        check1(i, j) = matrix1[i][j];
      }
    }
    S21Matrix check2 = S21Matrix(2, 2);
    for (int i = 0; i < check2.GetRows(); i++) {
      for (int j = 0; j < check2.GetCols(); j++) {
        check2(i, j) = matrix2[i][j];
      }
    }
    check1 = check1 * check2;
    for (int i = 0; i < check1.GetRows(); i++) {
      for (int j = 0; j < check1.GetCols(); j++) {
        EXPECT_EQ(check1(i, j), result[i][j]);
      }
    }
  });
}

TEST(OperatorMultMatrix, test2) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][2] = {{2, 0}, {0, 2}, {0, 2}};
  EXPECT_ANY_THROW({
    S21Matrix check1 = S21Matrix(2, 2);
    for (int i = 0; i < check1.GetRows(); i++) {
      for (int j = 0; j < check1.GetCols(); j++) {
        check1(i, j) = matrix1[i][j];
      }
    }
    S21Matrix check2 = S21Matrix(3, 2);
    for (int i = 0; i < check2.GetRows(); i++) {
      for (int j = 0; j < check2.GetCols(); j++) {
        check2(i, j) = matrix2[i][j];
      }
    }
    check1 = check1 * check2;
  });
}

TEST(OperatorEquality, EqualMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_TRUE(matrixA == matrixB);
  EXPECT_TRUE(matrixB == matrixA);
}

TEST(OperatorEquality, DifferentMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {4, 3}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(matrixA == matrixB);
  EXPECT_FALSE(matrixB == matrixA);
}

TEST(OperatorEquality, DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(matrixA == matrixB);
  EXPECT_FALSE(matrixB == matrixA);
}

TEST(OperatorAssignment, Assignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  matrixB = matrixA;

  EXPECT_EQ(matrixB.GetRows(), matrixA.GetRows());
  EXPECT_EQ(matrixB.GetCols(), matrixA.GetCols());

  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      EXPECT_EQ(matrixB(i, j), matrixA(i, j));
    }
  }
}

TEST(OperatorAssignment, SelfAssignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  matrixA = matrixA;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorAssignment, DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixB = matrixA;

  EXPECT_EQ(matrixB.GetRows(), matrixA.GetRows());
  EXPECT_EQ(matrixB.GetCols(), matrixA.GetCols());

  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      EXPECT_EQ(matrixB(i, j), matrixA(i, j));
    }
  }
}

TEST(OperatorMoveAssignment, MoveAssignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  matrixB = std::move(matrixA);

  EXPECT_EQ(matrixB.GetRows(), 2);
  EXPECT_EQ(matrixB.GetCols(), 2);

  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      EXPECT_EQ(matrixB(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorMoveAssignment, SelfMoveAssignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  matrixA = std::move(matrixA);

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorMoveAssignment, DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixB = std::move(matrixA);

  EXPECT_EQ(matrixB.GetRows(), 2);
  EXPECT_EQ(matrixB.GetCols(), 2);

  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      EXPECT_EQ(matrixB(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorPlusEqual, PlusEqual) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{3, 5}, {7, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA += matrixB;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorPlusEqual, PlusEqual_SelfAssignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double result[2][2] = {{2, 4}, {6, 8}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  matrixA += matrixA;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(Getter, test1) {
  S21Matrix test(3, 3);
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(Getter, test2) {
  S21Matrix test(2, 4);
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 4);
}

TEST(Getter, test3) {
  S21Matrix test(5, 1);
  EXPECT_EQ(test.GetRows(), 5);
  EXPECT_EQ(test.GetCols(), 1);
}

TEST(Getter, test4) {
  S21Matrix test = S21Matrix();
  EXPECT_EQ(test.GetRows(), 0);
  EXPECT_EQ(test.GetCols(), 0);
}

TEST(Getter, test5) {
  S21Matrix test(100, 100);
  EXPECT_EQ(test.GetRows(), 100);
  EXPECT_EQ(test.GetCols(), 100);
}

TEST(OperatorPlusEqual, PlusEqual_DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW({ matrixA += matrixB; }, std::invalid_argument);

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorMinusEqual, MinusEqual) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{-1, -1}, {-1, -1}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA -= matrixB;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMinusEqual, MinusEqual_SelfAssignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double result[2][2] = {{0, 0}, {0, 0}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  matrixA -= matrixA;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMinusEqual, MinusEqual_DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW({ matrixA -= matrixB; }, std::invalid_argument);

  // Ensure matrixA remains unchanged
  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{10, 13}, {22, 29}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA *= matrixB;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_SelfAssignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double result[2][2] = {{7, 10}, {15, 22}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  matrixA *= matrixA;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW({ matrixA *= matrixB; }, std::invalid_argument);

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_Scalar) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double scalar = 2;
  double result[2][2] = {{2, 4}, {6, 8}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= scalar;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_Scalar_Zero) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double scalar = 0;
  double result[2][2] = {{0, 0}, {0, 0}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= scalar;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_Scalar_Negative) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double scalar = -1;
  double result[2][2] = {{-1, -2}, {-3, -4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= scalar;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorParentheses, AccessElement) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(3, 3);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix[i][j]);
    }
  }
}

TEST(OperatorParentheses, AccessElement_Const) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  S21Matrix matrixA(3, 3);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      double num = matrix[i][j];
      matrixA(i, j) = num;
    }
  }

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      const double num = matrixA(i, j);
      EXPECT_EQ(matrixA(i, j), num);
    }
  }
}

TEST(OperatorParentheses, AccessExistingElement) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(3, 3);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix[i][j]);
    }
  }
}

TEST(OperatorParentheses, AccessNonexistentElement) {
  S21Matrix matrixA = S21Matrix(3, 3);

  EXPECT_THROW(
      {
        double value = matrixA(3, 2);  // Accessing row 3, col 2 (out of bounds)
        (void)value;
      },
      std::out_of_range);

  EXPECT_THROW(
      {
        double value = matrixA(1, 5);  // Accessing row 1, col 5 (out of bounds)
        (void)value;
      },
      std::out_of_range);

  EXPECT_THROW(
      {
        double value =
            matrixA(-1, 0);  // Accessing row -1, col 0 (out of bounds)
        (void)value;
      },
      std::out_of_range);
}

TEST(DopTest, ParametrizedConstructor) {
  EXPECT_THROW(S21Matrix matrix(-1, 10), std::invalid_argument);
}

TEST(DopTest, SetRow) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.SetRows(-1), std::invalid_argument);
}

TEST(DopTest, SetCols) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.SetCols(-1), std::invalid_argument);
}

TEST(DopTest, Minor) {
  S21Matrix matrix(2, 2);
  EXPECT_THROW(matrix.Minor(-1, -2), std::out_of_range);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}