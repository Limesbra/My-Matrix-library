# My Implementation of a Matrix Library


## Matrix operations

Here is a brief description of the matrix operations that are implemented in the developing library:

| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const My_Matrix& other)` | Checks matrices for equality with each other |  |
| `void SumMatrix(const My_Matrix& other)` | Adds the second matrix to the current one | different matrix dimensions |
| `void SubMatrix(const My_Matrix& other)` | Subtracts another matrix from the current one | different matrix dimensions |
| `void MulNumber(const double num) ` | Multiplies the current matrix by a number |  |
| `void MulMatrix(const My_Matrix& other)` | Multiplies the current matrix by the second matrix | the number of columns of the first matrix is not equal to the number of rows of the second matrix |
| `My_Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it |  |
| `My_Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it | the matrix is not square |
| `double Determinant()` | Calculates and returns the determinant of the current matrix | the matrix is not square |
| `My_Matrix InverseMatrix()` | Calculates and returns the inverse matrix | matrix determinant is 0 |

Apart from those operations, you also need to implement constructors and destructors:

| Method | Description |
| ----------- | ----------- |
| `My_Matrix()` | A basic constructor that initialises a matrix of some predefined dimension |  
| `My_Matrix(int rows, int cols) ` | Parametrized constructor with number of rows and columns |
| `My_Matrix(const My_Matrix& other)` | Copy constructor |
| `My_Matrix(My_Matrix&& other)` | Move constructor |
| `~My_Matrix()` | Destructor |

And you also need to overload the following operators, partly corresponding to the operations above:

| Operator | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `+`      | Addition of two matrices | different matrix dimensions |
| `-`   | Subtraction of one matrix from another | different matrix dimensions |
| `*`  | Matrix multiplication and matrix multiplication by a number | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `==`  | Checks for matrices equality (`EqMatrix`) | |
| `=`  | Assignment of values from one matrix to another one | |
| `+=`  | Addition assignment (`SumMatrix`) | different matrix dimensions |
| `-=`  | Difference assignment (`SubMatrix`) | different matrix dimensions |
| `*=`  | Multiplication assignment (`MulMatrix`/`MulNumber`) | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `(int i, int j)`  | Indexation by matrix elements (row, column) | index is outside the matrix |
