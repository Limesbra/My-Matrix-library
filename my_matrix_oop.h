
#ifndef MATRIX_CPP_MY_MATRIX_OOP_H
#define MATRIX_CPP_MY_MATRIX_OOP_H

#include <stdexcept>
#include <cmath>
#define EPS 1e-7

class My_Matrix {

    public:
        // constructors
        My_Matrix();
        My_Matrix(int rows, int cols);
        My_Matrix(const My_Matrix& other);
        My_Matrix(My_Matrix&& other) noexcept;
        ~My_Matrix();

        // operator overloading
        My_Matrix operator+(const My_Matrix& right);
        My_Matrix operator-(const My_Matrix& right);
        My_Matrix operator*(const My_Matrix& right);
        My_Matrix operator*(const double& right);
        bool operator==(const My_Matrix& right) const;
        My_Matrix &operator=(const My_Matrix& right);
        My_Matrix &operator=(My_Matrix&& right)noexcept;
        My_Matrix &operator+=(const My_Matrix& right);
        My_Matrix &operator-=(const My_Matrix& right);
        My_Matrix &operator*=(const My_Matrix& right);
        My_Matrix &operator*=(const double& num);
        double operator()(int i, int j) const;
        double &operator()(int i, int j);


        // methods
        bool EqMatrix(const My_Matrix& other) const;
        void SumMatrix(const My_Matrix& other);
        void SubMatrix(const My_Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const My_Matrix& other);
        My_Matrix Transpose() const;
        My_Matrix CalcComplements() const;
        double Determinant() const;
        My_Matrix InverseMatrix() const;
        My_Matrix minorMatrix(My_Matrix& other, int stepX, int stepY) const;  //+
        int rows() const;
        int cols() const;

    private:
        // Attributes
        int rows_, cols_;
        double **matrix_;
    
};


#endif // MATRIX_CPP_MY_MATRIX_OOP_H