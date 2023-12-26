#include "my_matrix_oop.h"

My_Matrix::My_Matrix() : rows_(3), cols_(3){
    matrix_ = new double* [rows_]();
    for(int i = 0; i < rows_; i++){
        matrix_[i] = new double [cols_]();
    }
}

My_Matrix::My_Matrix(int rows, int cols){
    if(rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and columns must be greater than 0");
    }
    else{
        matrix_ = new double* [rows]();
        for(int i = 0; i < rows; i++){
            matrix_[i] = new double [cols]();
        }
        rows_ = rows;
        cols_ = cols;
    }
}

My_Matrix::My_Matrix(const My_Matrix& other) : My_Matrix(other.rows_, other.cols_){
    for(int i = 0; i < other.rows_; i++){
        for(int j = 0; j < other.cols_; j++){
            this -> matrix_[i][j] = other.matrix_[i][j];
        }
    }  
}

My_Matrix::My_Matrix(My_Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_){
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

My_Matrix::~My_Matrix(){
    for(int i = 0; i < rows_; i++){
        delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
}

My_Matrix &My_Matrix::operator=(const My_Matrix& right){
    My_Matrix copyRight(right);
    std::swap(rows_, copyRight.rows_);
    std::swap(cols_, copyRight.cols_);
    std::swap(matrix_, copyRight.matrix_);
    return *this;
}

My_Matrix &My_Matrix::operator=(My_Matrix&& right) noexcept {
    std::swap(rows_, right.rows_);
    std::swap(cols_, right.cols_);
    std::swap(matrix_, right.matrix_);
    return *this;
}

bool My_Matrix::EqMatrix(const My_Matrix& other) const{
    if (other.rows_ != rows_ || other.cols_ != cols_) return false;
    for (int i = 0; i < rows_; i++) 
      for (int j = 0; j < cols_; j++) 
        if (fabs(other.matrix_[i][j] - matrix_[i][j]) > EPS) 
          return false;
  return true;
}

bool My_Matrix::operator==(const My_Matrix& right) const{
    return EqMatrix(right);
}

void My_Matrix::SumMatrix(const My_Matrix& other){
    if (other.rows_ != this->rows_ || other.cols_ != this->cols_) {
        throw std::invalid_argument("Matrix sizes are not equal");
    } else {
        for (int i = 0; i < other.rows_; i++) {
            for (int j = 0; j < other.cols_; j++) {
                this->matrix_[i][j] += other.matrix_[i][j];
            }
        }
    }
}

My_Matrix My_Matrix::operator+(const My_Matrix& right){
    My_Matrix result(*this);
    result.SumMatrix(right);
    return result;
}

My_Matrix &My_Matrix::operator+=(const My_Matrix& right){
    SumMatrix(right);
    return *this;
}

void My_Matrix::SubMatrix(const My_Matrix& other){
    if (other.rows_ != this->rows_ || other.cols_ != this->cols_) {
        throw std::invalid_argument("Matrix sizes are not equal");
    } else {
        for (int i = 0; i < other.rows_; i++) {
            for (int j = 0; j < other.cols_; j++) {
                this->matrix_[i][j] -= other.matrix_[i][j];
            }
        }
    }
}

My_Matrix &My_Matrix::operator-=(const My_Matrix& right){
    SubMatrix(right);
    return *this;
}

My_Matrix My_Matrix::operator-(const My_Matrix& right){
    My_Matrix result(*this);
    result.SubMatrix(right);
    return result;
}

void My_Matrix::MulNumber(const double num){
    if(num != num || num == INFINITY || num == -INFINITY)
        throw std::invalid_argument("Invalid number");
    for(int i = 0; i < rows_; i++)
        for(int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void My_Matrix::MulMatrix(const My_Matrix& other){
    if (cols_ != other.rows_)
        throw std::invalid_argument("Invalid matrix sizes");
    My_Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) 
        for (int j = 0; j < other.cols_; j++) 
            for (int k = 0; k < other.rows_; k++) 
                result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];

    *this = result;
}

My_Matrix My_Matrix::operator*(const My_Matrix& right){
    My_Matrix result(*this);
    result.MulMatrix(right);
    return result;
}

 My_Matrix My_Matrix::operator*(const double& right){
    My_Matrix result(*this);
    result.MulNumber(right);
    return result;
 }

My_Matrix &My_Matrix::operator*=(const My_Matrix& right){
    MulMatrix(right);
    return *this;
}

My_Matrix &My_Matrix::operator*=(const double& right){
    MulNumber(right);
    return *this;
}

double My_Matrix::operator()(int i, int j) const {
    if (rows_ <= i || cols_ <= j || i < 0 || j < 0)
        throw std::invalid_argument("Index outside the matrix");
    return matrix_[i][j];
}

double &My_Matrix::operator()(int i, int j){
    if (rows_ <= i || cols_ <= j || i < 0 || j < 0)
        throw std::invalid_argument("Index outside the matrix");
    return matrix_[i][j];
}

My_Matrix My_Matrix::Transpose() const{
    My_Matrix tMatrix(cols_, rows_);
      for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++)
          tMatrix.matrix_[j][i] = matrix_[i][j];
    // *this = tMatrix;
  return tMatrix;
}

My_Matrix My_Matrix::minorMatrix(My_Matrix& other, int stepX, int stepY) const{
    int x = 0;
    for (int i = 0; i < other.rows_; i++) {
        if (stepX == i) continue;
        int y = 0;
        for (int j = 0; j < other.cols_; j++) {
            if (stepY == j) continue;
            matrix_[x][y] = other.matrix_[i][j];
            y++;
        }
        x++;
    }
    return *this;
}

My_Matrix My_Matrix::CalcComplements() const{
    if (rows_ != cols_ )
        throw std::invalid_argument("The matrix must be square");
    if (rows_ == 1) {
        My_Matrix calcMatrix(1, 1);
        calcMatrix.matrix_[0][0] = 1;
        return calcMatrix;
    }
    My_Matrix copyMatrix(*this);
    My_Matrix calcMatrix(rows_, cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            My_Matrix minor(rows_ - 1, cols_ - 1);
            minor.minorMatrix(copyMatrix, i, j);
            double d = minor.Determinant();
            calcMatrix.matrix_[i][j] = d;
        }
    }
    double x = 0.0;
    for (int i = 0; i < calcMatrix.rows_; i++){
        for (int j = 0; j < calcMatrix.cols_; j++) {
            x = pow(-1, (double)(i + j));
            calcMatrix.matrix_[i][j] *= x;
        }
    }
    return calcMatrix;
}

double My_Matrix::Determinant() const{
    double result = 0;
    if (rows_ != cols_ )
        throw std::invalid_argument("The matrix must be square");
    if (rows_ == 1) result = matrix_[0][0];
    else if (rows_ == 2) 
        result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    else {
        My_Matrix copyMatrix(*this);
        double m = 1.0;
        for (int i = 0; i < rows_; i++) {
            My_Matrix minor(rows_ - 1, cols_ - 1);
            minor.minorMatrix(copyMatrix, 0, i);
            double d = minor.Determinant();
            result += matrix_[0][i] * d * m;
            m *= -1;
        }
    }
  return result;

}

My_Matrix My_Matrix::InverseMatrix() const{
    double det = Determinant();
    if (det == 0.0) 
        throw std::invalid_argument("The determinant of the matrix is 0");
    return CalcComplements().Transpose() * (1/det);

}

int My_Matrix::rows() const {return rows_;}

int My_Matrix::cols() const {return cols_;}