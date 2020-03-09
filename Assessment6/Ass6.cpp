// PHYS 30762 Programming in C++
// Assignment 6

/*  
Output example:
|1 2 12|
|2 5 7|
|12 2 1|
*/

#include<iostream>

class matrix
{
  // Friends of the class
  friend std::ostream & operator<<(std::ostream &out_stream, const matrix &the_matrix);
private:
  double *matrix_data {nullptr};
  size_t rows{};
  size_t columns{};
public: 
  // Default, Parameterized, Copy, Move Constructor
  matrix();
  matrix(size_t n, size_t m); 
  matrix(const matrix &a_matrix) ;
  matrix(matrix &&a_matrix); 
  // Destructor
  ~matrix(){std::cout<<"Destructor called" << std::endl; delete[] matrix_data;};
  //Copy and Move Assignment operators
  matrix& operator=(matrix &a_matrix);
  matrix& operator=(matrix &&a_matrix);
  //Addition, Subtraction and Multiplication overloading
  matrix operator+(const matrix &a_matrix) const;
  matrix operator-(const matrix &a_matrix) const; 
  matrix operator*(const matrix &a_matrix) const;
  //Calculation of the determinant
  matrix minor(size_t n, size_t m) const;
  double determinant() const;

  //Access functions
  void set_value(const size_t &i, const size_t &j, const double &value)
  {//Set value of i,j component of the matrix
    matrix_data[((j-1) + (i-1) * columns)] = value;
  }
  void set_rows(const size_t &new_rows)
  {
    rows = new_rows;
  }
  void set_columns(const size_t &new_columns)
  {
    columns = new_columns;
  }
  size_t get_rows() const 
  {
    return rows;
  } 
  size_t get_columns() const 
  {
    return columns;
  } 
  size_t index(size_t m, size_t n) const 
  {//Return position in array of element (m,n)
    if(m>0 && m<=rows && n>0 && n<=columns) {
      return (n-1)+(m-1)*columns;
    }else {
      std::cout<<"Error: out of range"<<std::endl; exit(1);
      throw("Out of Bounds error");
    }
  }
  double& operator()(size_t m, size_t n) 
  {
    return matrix_data[index(m,n)];
  }
};

//Default constructor
matrix::matrix() : rows{2}, columns{2}
{
  std::cout<<"Default constructor called" << std::endl; 
  matrix_data = new double[rows*columns]{};
}
//Parameterized constructor
matrix::matrix(size_t row_number, size_t column_number) : rows{row_number} , columns{column_number}
{
  std::cout<<"Parameterized constructor called" << std::endl;
  if (rows == 0 || columns == 0){
    std::cout << "Error: 0 dimensional matrix";
    exit(1);
  }else{
    matrix_data = new double[rows*columns]{};
  }
}
//Copy constructor
matrix::matrix(const matrix &a_matrix) : rows{a_matrix.rows} , columns{a_matrix.columns}
{
  std::cout << "Copy constructor" << std::endl; 
  size_t size = rows*columns;
  matrix_data = nullptr;
  if(size>0){
    matrix_data = new double[size]{};
    for(size_t i{}; i<size; i++){
      matrix_data[i] = a_matrix.matrix_data[i]; 
    }
  } 
}
//Move constructor (steals the data)
matrix::matrix(matrix &&a_matrix)
{
  std::cout << "Move constructor" << std::endl;
  rows = a_matrix.rows;
  columns = a_matrix.columns;
  matrix_data = a_matrix.matrix_data;
  a_matrix.rows, a_matrix.columns = {};
  a_matrix.matrix_data = nullptr;
}
//Copy assignment operator
matrix & matrix::operator=(matrix &a_matrix)
{
  std::cout << "Copy assignment" << std::endl;
  if(&a_matrix == this){ //no self assignment
    return *this;
  } 
  //First need to delete the objects array
  delete[] matrix_data;
  matrix_data = nullptr;
  rows = {};
  columns = {};
  //Copy the size and declare new array
  size_t size = a_matrix.rows*a_matrix.columns;
  if(size>0){
    matrix_data = new double[size];
    //Copy values into new array
    for(size_t i{}; i<size;i++){
      matrix_data[i] = a_matrix.matrix_data[i];
    }
  }
  return *this;
}
//Move assignment operator
matrix & matrix::operator=(matrix &&a_matrix)
{
  std::cout << "Move assignment" <<std::endl;
  std::swap(rows,a_matrix.rows);
  std::swap(columns,a_matrix.columns);
  std::swap(matrix_data,a_matrix.matrix_data);
  return *this;
}
//Overload << operator to output matrices
std::ostream & operator<<(std::ostream &out_stream, const matrix &a_matrix)
{ 
  /*  
  Output example:
  |1 2 12|
  |2 5 7|
  |12 2 1|
  */
  for(size_t i=1; i<a_matrix.rows+1; i++){
    for (size_t j=1; j<a_matrix.columns+1; j++){
      if(a_matrix.columns==1){ //Single column special case
        out_stream << '|' << " " << a_matrix.matrix_data[a_matrix.index(i,j)] << " " << '|' << std::endl;
      }else{
        if(j==1){
          out_stream << '|' << " " << a_matrix.matrix_data[a_matrix.index(i,j)] << " ";
        }else if(j==a_matrix.columns){
          out_stream << a_matrix.matrix_data[a_matrix.index(i,j)] << " " << '|' << std::endl; 
        }else {
          out_stream << a_matrix.matrix_data[a_matrix.index(i,j)] << " ";
        }
      }
    }
  }
  return out_stream;
}

//Overload >> operator to input matrices
std::istream &operator>>(std::istream &in_stream, matrix &a_matrix) 
{ 
  //Get the number of rows and columns
  size_t number_of_rows, number_of_columns; 
  std::cout << "Enter the number of rows: ";
  std::cin >> number_of_rows;
  if (std::cin.fail() || number_of_rows == 0) {
    std::cout<<"Error: invalid input"<<std::endl; exit(1);
    throw("positive integer error");
  }
  std::cout << "Enter the number of columns: ";
  std::cin >> number_of_columns;
  if (std::cin.fail() || number_of_columns == 0) {
    std::cout<<"Error: invalid input"<<std::endl; exit(1);
    throw("positive integer error");
  }
  a_matrix.set_rows(number_of_rows);
  a_matrix.set_columns(number_of_columns);
  //Get matrix values 
  std::cout << "Enter values of the matrix (" << number_of_rows*number_of_columns << " values)" << std::endl;
  //Loop to fill the matrix from input
  double temporary; 
  for (size_t i=1; i < number_of_rows+1; i++) {
    for (size_t j=1; j < number_of_columns+1; j++) {
      std::cin >> temporary;             
      a_matrix.set_value(i,j, temporary); 
      std::cin.ignore();
      if (std::cin.fail()) {
        std::cout<<"Error: invalid input"<<std::endl; exit(1);
        throw("new element of matrix error");
      }
    }
  }
  return in_stream;
}
//Main program

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
  matrix a2;
  // Set values for a2 here
  std::cin >> a2;
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