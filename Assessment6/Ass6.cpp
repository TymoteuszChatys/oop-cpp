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
  matrix() : rows = {}, columns = {}, matrix_data = {};
  matrix(int, int); 
  matrix(const matrix&);
  matrix(matrix&&); 
  // Destructor
  ~matrix();
  // Access functions
  int get_rows() const { // Return number of rows
    return rows;
  } 
  int get_columns() const { // Return number of columns
    return columns;
  } 
  int index(int m, int n) const // Return position in array of element (m,n)
  {
    if(m>0 && m<=rows && n>0 && n<=columns) {
      return (n-1)+(m-1)*columns;
    }
    else {
      std::cout<<"Error: out of range"<<std::endl; exit(1);
    }
  }
  double & operator()(int m, int n) {
    return matrix_data[index(m,n)];
  }
  //Copy and Move Assignment operators
  matrix& operator=(const matrix&);
  matrix& operator=(matrix &&);
  //Addition, Subtraction and Multiplication overloading
  matrix operator+(const matrix&) const;
  matrix operator-(const matrix&) const; 
  matrix operator*(const matrix&) const;

  //Calculation of the determinant
  matrix minor(int, int) const;
  double determinant() const;
};

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
   // Parameterized constructor
  // Set values for a2 here

  // Print matrix a2
  // Deep copy by assignment: define new matrix a3 then copy from a2 to a3

  // Modify contents of original matrix and show assigned matrix is unchanged here
  // Deep copy using copy constructor 
  // Modify contents of original matrix and show copied matrix is unchanged here
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