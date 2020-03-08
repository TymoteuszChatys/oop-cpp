// PHYS 30762 Programming in C++
// Assignment 6

// A matrix class - skeleton code

// You are advised to write your own code from scratch but
// you may use this code if you do not know how to get started.

// Note: for longer functions, you are advised to prototype them
// within class and put the function code itself immediately below class. 

#include<iostream>

class matrix
{
  // Friends of the class
  friend std::ostream & operator<<(std::ostream &out_stream, const matrix &the_matrix);
private:
  double *matrix_data {nullptr};
  int rows{};
  int columns{};
public: 
  // Default, Parameterized, Copy, Move Constructor
  matrix();
  matrix(int a, int b); 
  matrix(const matrix &a_matrix) ;
  matrix(matrix &&a_matrix); 
  // Destructor
  ~matrix(){std::cout<<"Destructor called" << std::endl; delete[] matrix_data;};
  // Access functions
  int get_rows() const 
  { // Return number of rows
    return rows;
  } 
  int get_columns() const 
  { // Return number of columns
    return columns;
  } 
  int index(int m, int n) const 
  { // Return position in array of element (m,n)
    if(m>0 && m<=rows && n>0 && n<=columns) {
      return (n-1)+(m-1)*columns;
    }
    else {
      std::cout<<"Error: out of range"<<std::endl; exit(1);
    }
  }
  double& operator()(int m, int n) 
  {
    return matrix_data[index(m,n)];
  }
  //Copy and Move Assignment operators
  matrix& operator=(matrix &a_matrix);
  matrix& operator=(matrix &&a_matrix);
  //Addition, Subtraction and Multiplication overloading
  matrix operator+(const matrix &a_matrix) const;
  matrix operator-(const matrix &a_matrix) const; 
  matrix operator*(const matrix &a_matrix) const;
  //Calculation of the determinant
  matrix minor(int, int) const;
  double determinant() const;
};
//Default constructor
matrix::matrix() : rows{2}, columns{2}
{
  std::cout<<"Default constructor called" << std::endl; 
  matrix_data = new double[rows*columns]{};
}
//Parameterized constructor
matrix::matrix(int row_number, int column_number) : rows{row_number} , columns{column_number}
{
  std::cout<<"Parameterized constructor called" << std::endl;
  if (rows == 0 || columns == 0){
    std::cout << "Error: 0 dimensional matrix";
    exit(1);
  }else{
    matrix_data = new double[rows*columns]{};
  }
}
//copy constructor
matrix::matrix(const matrix &a_matrix) : rows{a_matrix.rows} , columns{a_matrix.columns}
{
  std::cout << "copy constructor" << std::endl; 
  size_t size = rows*columns;
  new_matrix = new double[size]{};
  for(size_t i{}; i<size; i++;){
    a_matrix[i] = matrix.new_matrix[i];
  }
}
//Move constructor
matrix::matrix(matrix &&a_matrix)
{
  std::cout << "move constructor" << std::endl;
  rows = a_matrix.rows;
  columns = a_matrix.columns;
  matrix_data = a_matrix.matrix_data;
}
// Member functions defined outside class



// Overload insertion to output stream for matrices
std::ostream & operator<<(std::ostream &out_stream, const matrix &the_matrix)
{
  // Code goes here
  return out_stream;
}

// Main program

int main()
{
  //
  // First part of assignment: constructing and deep copying matrices
  //

  // Demonstrate default constructor
  matrix a1;
  std::cout<<a1;
   // Parameterized constructor
  const int m{2};
  const int n{2};
  matrix a2{m,n};
  // Set values for a2 here
  // Print matrix a2
  std::cout<<a2;
  // Deep copy by assignment: define new matrix a3 then copy from a2 to a3
  matrix a3{m,n};
  std::cout<<a3;
  a3=a2;
  std::cout<<a3;
  // Modify contents of original matrix and show assigned matrix is unchanged here
  std::cout<<a2;
  std::cout<<a3;
  // Deep copy using copy constructor 
  matrix a4{a2};
  std::cout<<a4;
  // Modify contents of original matrix and show copied matrix is unchanged here
  std::cout<<a2;
  std::cout<<a4;
  // Move copy construction demonstration

  // Move assignment demonstration

  //
  // Second part of assignment: matrix operations
  //

  // Addition of 2 matrices

  // Subtraction of 2 matrices

  // Multiplication of 2 matrices


  // Determinant

  
  return 0;
}