#include <gtest/gtest.h>

#include "my_matrix_oop.h"

TEST(cols_, checkCols) {
  My_Matrix TestMatrix1(5, 6);
  EXPECT_EQ(TestMatrix1.cols(), 6);
}

TEST(rows_, checkRows) {
  My_Matrix TestMatrix1(5, 6);
  EXPECT_EQ(TestMatrix1.rows(), 5);
}

TEST(constructor, checkDefaultConstructor) {
  My_Matrix m;
  ASSERT_TRUE(3 == m.rows());
  ASSERT_TRUE(3 == m.cols());
}

TEST(incorrectInit, checkFalse0) {
  EXPECT_THROW  (My_Matrix TestMatrix(3, -4), std::invalid_argument);
}

TEST(incorrectInit, checkFalse1) {
  EXPECT_THROW  (My_Matrix TestMatrix(-5, 1), std::invalid_argument);
}

TEST(incorrectInit, checkFalse2) {
  EXPECT_THROW  (My_Matrix TestMatrix(0, 3), std::invalid_argument);
}

TEST(constructor, checkConstructor) {
  const int rows = 5;
  const int cols = 5;
  My_Matrix m(rows, cols);
  ASSERT_TRUE(rows == m.rows());
  ASSERT_TRUE(cols == m.cols());
}

TEST(constructor, checkconstructorCopy) {
  My_Matrix m(4, 3);
  for (int i = 0; i < m.rows(); i++)
    for (int j = 0; j < m.cols(); j++) m(i, j) = i + j;
  My_Matrix m2(m);
  ASSERT_TRUE(m == m2);
}

TEST(constructor, checkconstructorMove) {
  My_Matrix m(5, 4);
  for (int i = 0; i < m.rows(); i++)
    for (int j = 0; j < m.cols(); j++) m(i, j) = i + j;
  My_Matrix m1(m);
  My_Matrix m2 = std::move(m);
  ASSERT_TRUE(m1 == m2);
}

TEST(checkEqual, checkFalse0) {
  My_Matrix a(3, 2);
  My_Matrix b(2, 2);
  ASSERT_FALSE(a == b);
}

TEST(checkEqual, checkFalse1) {
  My_Matrix a(3, 3);
  My_Matrix b(3, 2);
  ASSERT_FALSE(a == b);
}

TEST(checkEqual, checkFalse2) {
  My_Matrix a(2, 2);
  My_Matrix b(2, 2);
  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < a.cols(); j++) {
      a(i, j) = i + 1;
      b(i, j) = i;
    }
  }
  ASSERT_FALSE(a == b);
}

TEST(checkEqual, checkTrue0) {
  My_Matrix a(5, 5);
  My_Matrix b(5, 5);
  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < a.cols(); j++) {
      double rand_val = rand();
      a(i, j) = rand_val;
      b(i, j) = rand_val;
    }
  }
  ASSERT_TRUE(a == b);
}

TEST(sum, wrongSize0) {
  My_Matrix a(4, 4);
  My_Matrix b(3, 3);
  EXPECT_THROW(a.SumMatrix(b), std::invalid_argument);
}

TEST(sum, wrongSize1) {
  My_Matrix a(3, 4);
  My_Matrix b(3, 3);
  EXPECT_THROW(a.SumMatrix(b), std::invalid_argument);
}

TEST(sum, checkTrue0) {
  My_Matrix a(5, 5);
  My_Matrix b(5, 5);
  My_Matrix sum(5, 5);
  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < a.cols(); j++) {
      a(i, j) = i+j;
      b(i, j) = i+j;
      sum(i, j) = a(i, j) + b(i, j);
    }
  }
  a.SumMatrix(b);
  ASSERT_TRUE(a == sum);
}

TEST(sub, wrongSize0) {
  My_Matrix a(4, 4);
  My_Matrix b(3, 3);
  EXPECT_THROW(a.SubMatrix(b), std::invalid_argument);
}

TEST(sub, checkTrue0) {
  My_Matrix a(5, 5);
  My_Matrix b(5, 5);
  My_Matrix sub(5, 5);
  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < a.cols(); j++) {
      a(i, j) = i + j;
      b(i, j) = i - j;
      sub(i, j) = a(i, j) - b(i, j);
    }
  }
  a.SubMatrix(b);
  ASSERT_TRUE(a == sub);
}

TEST(mulNumber, checkTrue0) {
  My_Matrix a(4, 4);
  My_Matrix check(4, 4);
  double number = 3;
  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < a.cols(); j++) {
      a(i, j) = i + j + 3;
      check(i, j) = a(i, j) * number;
    }
  }
  a.MulNumber(number);
  ASSERT_TRUE(a == check);
}

TEST(mulNumber, checkTrue1) {
  My_Matrix a(4, 4);
  My_Matrix check(4, 4);
  double number = 1.0/0.0;
  EXPECT_THROW(a.MulNumber(number), std::invalid_argument);
}

TEST(mulMatrix, checkTrue0) {
  My_Matrix a{2, 3};
  My_Matrix b{3, 3};
  My_Matrix res{2, 3};

  a(0, 0) = 2.25;
  a(0, 1) = 2.35;
  a(0, 2) = -4.5;
  a(1, 0) = 7;
  a(1, 1) = 9;
  a(1, 2) = 8;

  b(0, 0) = 9;
  b(0, 1) = 8;
  b(0, 2) = 7;
  b(1, 0) = 6;
  b(1, 1) = 5;
  b(1, 2) = 4;
  b(2, 0) = 3;
  b(2, 1) = 2;
  b(2, 2) = 1;

  res(0, 0) = 20.85;
  res(0, 1) = 20.75;
  res(0, 2) = 20.65;
  res(1, 0) = 141;
  res(1, 1) = 117;
  res(1, 2) = 93;

  a.MulMatrix(b);
  ASSERT_TRUE(a == res);
}

TEST(mulMatrix, checkTrue1) {
  My_Matrix a{3, 2};
  My_Matrix b{2, 3};
  My_Matrix res{3, 3};

  a(0, 0) = 0.1;
  a(0, 1) = -1.01;
  a(1, 0) = 1.11;
  a(1, 1) = 0.11;
  a(2, 0) = -0.68;
  a(2, 1) = 0.55;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(0, 2) = 3;
  b(1, 0) = 4;
  b(1, 1) = 5;
  b(1, 2) = 6;

  res(0, 0) = -3.94;
  res(0, 1) = -4.85;
  res(0, 2) = -5.76;
  res(1, 0) = 1.55;
  res(1, 1) = 2.77;
  res(1, 2) = 3.99;
  res(2, 0) = 1.52;
  res(2, 1) = 1.39;
  res(2, 2) = 1.26;

  a.MulMatrix(b);

  ASSERT_TRUE(a == res);
}

TEST(mulMatrix, wrongSize0) {
  My_Matrix a(3, 3);
  My_Matrix b(2, 2);
  EXPECT_THROW(a.MulMatrix(b), std::invalid_argument);
}

TEST(transpose, checkTrue0) {
  My_Matrix a{2, 3};
  My_Matrix b{3, 2};

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;

  b(0, 0) = 1;
  b(0, 1) = 4;
  b(1, 0) = 2;
  b(1, 1) = 5;
  b(2, 0) = 3;
  b(2, 1) = 6;

  My_Matrix res = a.Transpose();
  ASSERT_TRUE(b == res);
}

TEST(complements, checkTrue0) {
  My_Matrix a(3, 3);
  My_Matrix res(3, 3);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 0;
  a(1, 1) = 4;
  a(1, 2) = 2;
  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1;

  res(0, 0) = 0;
  res(0, 1) = 10;
  res(0, 2) = -20;
  res(1, 0) = 4;
  res(1, 1) = -14;
  res(1, 2) = 8;
  res(2, 0) = -8;
  res(2, 1) = -2;
  res(2, 2) = 4;

  My_Matrix r(a.CalcComplements());
  ASSERT_TRUE(res == r);
}

TEST(complements, wrongSize0) {
  My_Matrix a(5, 3);
  EXPECT_THROW(a.CalcComplements(), std::invalid_argument);
}

TEST(inverse, checkFalse0) {
  My_Matrix matrix_a(4, 3);

  matrix_a(0, 0) = 88;
  matrix_a(0, 1) = -13;
  matrix_a(0, 2) = 66.6;
  matrix_a(1, 0) = 111;
  matrix_a(1, 1) = 3.9;
  matrix_a(1, 2) = 3.2;
  matrix_a(2, 0) = 8.14;
  matrix_a(2, 1) = 0.1;
  matrix_a(2, 2) = -854;
  matrix_a(3, 0) = 40;
  matrix_a(3, 1) = 39.8;
  matrix_a(3, 2) = 22;

  EXPECT_THROW(matrix_a.InverseMatrix(), std::invalid_argument);
}

TEST(inverse, checkTrue0) {
  My_Matrix matrix_a(3, 3);
  My_Matrix result(3, 3);

  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 6;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 2;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;

  result(0, 0) = 0.0322581;
  result(0, 1) = 0.0483871;
  result(0, 2) = 0.1290323;
  result(1, 0) = 0.6129032;
  result(1, 1) = -0.5806452;
  result(1, 2) = 0.4516129;
  result(2, 0) = -0.3548387;
  result(2, 1) = 0.4677419;
  result(2, 2) = -0.4193548;

  ASSERT_TRUE(matrix_a.InverseMatrix().EqMatrix(result));
}

TEST(inverse, checkTrue1) {
  My_Matrix matrix_c(1, 1);
  My_Matrix matrix_c_res(1, 1);
  matrix_c_res(0, 0) = 1;
  matrix_c(0, 0) = 1;
  ASSERT_TRUE(matrix_c.InverseMatrix().EqMatrix(matrix_c_res));
}

TEST(inverse, checkTrue2) {
  My_Matrix matrix_b(3, 3);
  matrix_b(0, 0) = 1;
  matrix_b(0, 1) = 2;
  matrix_b(0, 2) = 3;
  matrix_b(1, 0) = 4;
  matrix_b(1, 1) = 5;
  matrix_b(1, 2) = 6;
  matrix_b(2, 0) = 7;
  matrix_b(2, 1) = 8;
  matrix_b(2, 2) = 9;

  EXPECT_THROW(matrix_b.InverseMatrix(), std::invalid_argument);
}

TEST(inverse, checkTrue3) {
  My_Matrix a{1, 1};
  a(0, 0) = 4;
  My_Matrix res = a.InverseMatrix();
  EXPECT_EQ(res(0, 0), 0.25);
}

TEST(determinant, checkTrue0) {
  My_Matrix a{3, 3};
  a(0, 0) = 9;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 4;
  a(1, 1) = 9;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;
  EXPECT_EQ(std::fabs(a.Determinant() - 216.0) < EPS, true);
}

TEST(determinant, checkTrue1) {
  My_Matrix a{3, 3};
  a(0, 0) = 1.4;
  a(0, 1) = 0.5;
  a(0, 2) = 6;
  a(1, 0) = -7;
  a(1, 1) = 8;
  a(1, 2) = 9;
  a(2, 0) = 0.4;
  a(2, 1) = 6.8;
  a(2, 2) = -9.8;
  EXPECT_EQ(std::fabs(a.Determinant() + 532.74) < EPS, true);
}

TEST(determinant, checkTrue2) {
  My_Matrix a{1, 1};
  a(0, 0) = 5;
  EXPECT_EQ(std::fabs(a.Determinant() - 5) < EPS, true);
}

TEST(opPlus, checkTrue0) {
  My_Matrix a(3, 2);
  My_Matrix b(3, 2);
  My_Matrix c = a + b;
  a.SumMatrix(b);
  ASSERT_TRUE(a == c);
}

TEST(opMinus, checkTrue0) {
  My_Matrix a(2, 2);
  My_Matrix b(2, 2);
  My_Matrix c = a - b;
  a.SubMatrix(b);
  ASSERT_TRUE(a == c);
}

TEST(opMultNumber, checkTrue0) {
  My_Matrix a(2, 4);
  double n = 8.333333;
  My_Matrix c = a * n;
  a.MulNumber(n);
  ASSERT_TRUE(a == c);
}

TEST(opMultMatrix, checkTrue0) {
  My_Matrix a(2, 3);
  My_Matrix b(3, 1);
  My_Matrix c = a * b;
  a.MulMatrix(b);
  ASSERT_TRUE(a == c);
}

TEST(opIsEqual, checkTrue0) {
  My_Matrix a(4, 4);
  My_Matrix b(4, 4);
  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < a.cols(); j++) {
      a(i, j) = i;
      b(i, j) = i;
    }
  }
  ASSERT_TRUE(a == b);
}

TEST(opIsEqual, checkFalse0) {
  My_Matrix a(4, 4);
  My_Matrix b(4, 4);
  for (int i = 0; i < a.rows(); i++) {
    for (int j = 0; j < a.cols(); j++) {
      a(i, j) = i;
      b(i, j) = j;
    }
  }
  ASSERT_FALSE(a == b);
}

TEST(opIsEqual, checkFalse1) {
  My_Matrix a(3, 2);
  My_Matrix b(2, 3);
  ASSERT_FALSE(a == b);
}

TEST(opAssign, checkTrue0) {
  My_Matrix a(2, 2);
  My_Matrix c(3, 3);
  a = c;
  ASSERT_TRUE(a == c);
}

TEST(opAssignMove, checkTrue0) {
  My_Matrix a(2, 2);
  My_Matrix c(2, 2);
  if(1){
    My_Matrix b(1, 1);
    b(0, 0) = 15;
    a = std::move(b);
  }
  ASSERT_TRUE(a(0, 0) == 15);
}

TEST(opPlusEq, checkTrue0) {
  My_Matrix a(2, 2);
  My_Matrix b(2, 2);
  My_Matrix c = a + b;
  a += b;
  ASSERT_TRUE(a == c);
}

TEST(opMinusEq, checkTrue0) {
  My_Matrix a(4, 2);
  My_Matrix b(4, 2);
  My_Matrix c = a - b;
  a -= b;
  ASSERT_TRUE(a == c);
}

TEST(opMultMatrixEq, checkTrue0) {
  My_Matrix a(2, 2);
  My_Matrix b(2, 2);
  My_Matrix c = a * b;
  a *= b;
  ASSERT_TRUE(a == c);
}

TEST(opMultNumberEq, checkTrue0) {
  My_Matrix a(2, 2);
  double n = 4.48;
  My_Matrix c = a * n;
  a *= n;
  ASSERT_TRUE(a == c);
}

TEST(opBraces, checkTrue0) {
  My_Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;
  double n = a(0, 0);
  ASSERT_TRUE(1 == n);
  n = a(0, 1);
  ASSERT_TRUE(n == 2);
}

TEST(opBraces, checkTrue1) {
  const My_Matrix a(2, 2);
  double n = a(0, 0);
  ASSERT_TRUE(0 == n);
}

TEST(opBraces, checkTrue2) {
  const My_Matrix a(2, 2);
  EXPECT_THROW(a(5, 5), std::invalid_argument);
}

TEST(bracesInvalidArgument, checkTrue0) {
  My_Matrix m(2, 2);
  EXPECT_THROW(m(5, 5), std::invalid_argument);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
