// PHYS 30762 Programming in C++
// Tymoteusz Chatys
// 9th March 2020
// Assignment 6
/*
Input example: 
1 2 12 2 5 7 12 2 1
Output example:
|1 2 12|
|2 5 7|
|12 2 1|
*/
#include<iostream>
#include<cmath>

// Functions to return a break line for a better viewing experience
std::string dash()
{
  std::string break_line;
  break_line = "---------------------------------------";
  return break_line;
}
std::string dash_error()
{
  std::string break_line;
  break_line = "-----------------ERROR-----------------";
  return break_line;
}

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
  ~matrix(){delete[] matrix_data;};
  //Copy and Move Assignment operators
  matrix& operator=(matrix &a_matrix);
  matrix& operator=(matrix &&a_matrix);
  //Addition, Subtraction and Multiplication overloading
  matrix operator+(const matrix &a_matrix) const;
  matrix operator-(const matrix &a_matrix) const; 
  matrix operator*(const matrix &a_matrix) const;
  //Calculation of the determinant
  matrix minor(size_t n, size_t m) const;
  float determinant() const;

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
  size_t get_value(size_t j,size_t i) const
  {
    return matrix_data[(i-1)+(j-1)*columns];
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
matrix::matrix() : rows{3}, columns{3}
{
  matrix_data = new double[rows*columns]{};
}
//Parameterized constructor
matrix::matrix(size_t row_number, size_t column_number) : rows{row_number} , columns{column_number}
{
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
  rows = a_matrix.rows;
  columns = a_matrix.columns;
  matrix_data = a_matrix.matrix_data;
  a_matrix.rows, a_matrix.columns = {};
  a_matrix.matrix_data = nullptr;
}
//Copy assignment operator
matrix &matrix::operator=(matrix &a_matrix)
{
  if(&a_matrix == this){ //no self assignment
    return *this;
  } 
  //First need to delete the objects array
  delete[] matrix_data;
  matrix_data = {};
  //Copy the size and declare new array
  rows = a_matrix.rows;
  columns = a_matrix.columns;
  size_t size = rows*columns;
  matrix_data = new double[size];
    //Copy values into new array
  for(size_t i{}; i<size;i++){
    matrix_data[i] = a_matrix.matrix_data[i];
  }
  return *this;
}
//Move assignment operator
matrix & matrix::operator=(matrix &&a_matrix)
{
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
        out_stream << '|' << a_matrix.matrix_data[a_matrix.index(i,j)] << '|' << std::endl;
      }else{
        if(j==1){
          out_stream << '|' << a_matrix.matrix_data[a_matrix.index(i,j)] << " ";
        }else if(j==a_matrix.columns){
            if(i==a_matrix.rows){
              out_stream << a_matrix.matrix_data[a_matrix.index(i,j)] << '|'; //Last row we dont need a new line for proceeding rows. 
            }else{
              out_stream << a_matrix.matrix_data[a_matrix.index(i,j)] << '|' << std::endl;
            }
          
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
  /*
  Input example: 
  1 2 12 2 5 7 12 2 1
  */
  //Get the number of rows and columns
  int number_of_rows, number_of_columns; 
  std::cout << "Enter the number of rows: ";
  std::cin >> number_of_rows;
  if (std::cin.fail() || number_of_rows < 1) {
    std::cout<<"Error: invalid input"<<std::endl; exit(1);
    throw("positive integer error");
  }
  std::cout << "Enter the number of columns: ";
  std::cin >> number_of_columns;
  if (std::cin.fail() || number_of_columns < 1) {
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
//Overload + for addition of matrices
matrix matrix::operator+(const matrix& a_matrix) const
{
  matrix result_matrix{};
	if (rows != a_matrix.rows || columns != a_matrix.columns) {
		std::cout << dash_error() << dash() << std::endl << "Addition of these matrices is not possible, default displayed " << std::endl << dash_error() << dash() << std::endl;
	}else{
    result_matrix.set_rows(rows);
    result_matrix.set_columns(columns);
	  size_t array_size{rows*columns};
	  for (size_t i{}; i < array_size; ++i){
      result_matrix.matrix_data[i] = a_matrix.matrix_data[i] + matrix_data[i];
    }
  }
	return result_matrix;
}
//Overload - for subtraction of matrices
matrix matrix::operator-(const matrix& a_matrix) const
{
  matrix result_matrix{};
	if (rows != a_matrix.rows || columns != a_matrix.columns) {
		std::cout << dash_error() << dash() << std::endl << "Subtraction of these matrices is not possible, default displayed " << std::endl << dash_error() << dash() << std::endl;
	}else{
    result_matrix.set_rows(rows);
    result_matrix.set_columns(columns);
	  size_t array_size{rows*columns};
	  for (size_t i{}; i < array_size; ++i){
      result_matrix.matrix_data[i] = + matrix_data[i] - a_matrix.matrix_data[i] ;
    }
  }
	return result_matrix;
}
//Overload - for multiplication of matrices
matrix matrix::operator*(const matrix& a_matrix) const
{
  matrix result_matrix{};
	if (columns != a_matrix.rows) {
		std::cout << dash_error() << dash() << std::endl << "Multiplication of these matrices is not possible, default displayed " << std::endl << dash_error() << dash() << std::endl;
	}else{
    result_matrix.set_rows(rows);
    result_matrix.set_columns(a_matrix.columns);
    for(size_t i{1}; i < result_matrix.rows+1; i++){
      for(size_t j{1}; j < result_matrix.columns+1; j++){
        for(size_t k{1}; k < columns+1; k++){
          result_matrix.set_value(i,j,get_value(i,k)*a_matrix.get_value(k,j)+result_matrix.get_value(i,j));
        } 
      }
    }
  }
	return result_matrix;
}

//Return a matrix with the ith row and jth column deleted
matrix matrix::minor(size_t row_to_delete, size_t column_to_delete) const
{
  matrix reduced_matrix;
  //Checks if the row and column selected to delete is valid within the range
  //There is 3 things to check for
  //1. is the row/column a positive integer
  //2. does the row/column supplied exist within the matrix to perform the minor on
  //3. is our initial matrix a square matrix
  //4. initial matrix has to be at least 2x2
	if (row_to_delete > rows || row_to_delete < 1 || column_to_delete > columns || column_to_delete < 1 || rows != columns || rows < 2 || columns < 2){
		std::cout << dash_error() << std::endl << "Minor of this matrix is not possible, default displayed " << std::endl << dash_error() << std::endl;
	}else{
    //set the rows and columns so that new matrix is a smaller matrix 
    reduced_matrix.set_rows(rows-1);
    reduced_matrix.set_columns(columns-1);
    size_t new_index{};
    if (rows == 1) return *this;
    for (size_t index{1}; index < rows*columns+1; index++){
      //Skip columns and rows that are to be deleted from new matrix data
      if (abs(index-column_to_delete) % columns == 0){
        continue;
      }else if (index > ((row_to_delete- 1)*columns) && index < (row_to_delete*columns)+1){
        continue;
      } 
      //Input into new matrix if not a value from one of the deleted columns or rows
      reduced_matrix.matrix_data[new_index] = matrix_data[index-1];
      new_index++;
    }
  }
  return reduced_matrix;
}

float matrix::determinant() const
{
  float det{};
	//check if square matrix
	if (rows != columns){
		std::cout << dash_error() << dash() << std::endl << "Determinant cannot be calculated for this matrix: " << std::endl << dash_error() << dash() << std::endl;
	}else{
    if(columns == 1){
      det = get_value(1,1);
    /*}else if(columns == 2){
      det = (get_value(1,1)*get_value(2,2))-(get_value(1,2)*get_value(2,1));
      std::cout << get_value(1,1)*get_value(2,2) << " " << get_value(1,2)*get_value(2,1) << std::endl;
      std::cout << det << std::endl;
      std::cout << get_value(1,1) << " " << get_value(2,2) << " " << get_value(1,2) << " " << get_value(2,1) << std::endl;
    */}else{
      for(int i{1}; i <= columns; i++){
        matrix matrix_minor;
        matrix_minor = (*this).minor(1,i);
        det += pow(-1,1+i)*get_value(1,i)*matrix_minor.determinant();
      }
    }  
	}
	return det;
}

//Main program
int main()
{
  std::cout << dash() << dash() << std::endl << "Matrix calculator" << std::endl << dash() << dash() << std::endl;
  std::cout << "Which option would you like to choose?" << std::endl;
  std::cout << "1 - matrix calculator" << std::endl;
  std::cout << "2 - copy/move constructors/assignment demonstration using matrices" << std::endl << dash() << dash() << std::endl;
  //Asks user to choose an option
  std::string option;
  getline(std::cin, option);
  if(option=="1"){
    matrix first_matrix;
    matrix second_matrix;
    std::cin >> first_matrix;
    std::cout << dash() << std::endl;
    std::cin >> second_matrix;
    std::cout << dash() << std::endl;
    std::cout << "Your matrices: " << std::endl << "m1: " << std::endl << first_matrix << std::endl;
    std::cout << "m2: " << std::endl << second_matrix << std::endl << dash() << std::endl;
    // Addition of 2 matrices
    std::cout << "Addition (m1+m2): " << std::endl << first_matrix+second_matrix << std::endl << dash() << std::endl;
    // Subtraction of 2 matrices
    std::cout << "Subtraction (m1-m2): " << std::endl << first_matrix-second_matrix << std::endl << dash() << std::endl;
    // Multiplication of 2 matrices
    std::cout << "Multiplication (m1*m2): " << std::endl << first_matrix*second_matrix << std::endl << dash() << std::endl;
    // Determinant
    std::cout << "Determinant (m1): " << first_matrix.determinant() << std::endl << dash() << std::endl;
    std::cout << "Determinant (m2): " << second_matrix.determinant() << std::endl << dash() << std::endl;
  }else if(option=="2"){
    //Demonstrate default constructor
    matrix a1;
    std::cout << "Default constructor (a1): " << std::endl << a1 << std::endl << dash() << std::endl;
    //Demonstrate parameterized constructor
    /* Make matrix a2
    |1 2| 
    |3 4|
    */
    const int m{2};
    const int n{2};
    matrix a2{m,n};
    a2.set_value(1,1,1); a2.set_value(1,2,2); a2.set_value(2,1,3); a2.set_value(2,2,4);
    std::cout << "Parameterized constructor (a2): " << std::endl << a2 << std::endl << dash() << std::endl; 
    //Deep copy by assignment: define new matrix a3 then copy from a2 to a3
    std::cout << "Deep copy by assignmnent: " << std::endl;
    matrix a3{m,n};
    std::cout << "Default (a3): " << std::endl << a3 << std::endl; 
    a3=a2;
    std::cout << "Deep copy (a2 to a3): " << std::endl << a3 << std::endl << dash() << std::endl;
    //Modify contents of original matrix and show assigned matrix is unchanged here
    std::cout << "Now modifying a2 and outputting a3: " << std::endl;
    /* change a2 to
    |2 2| 
    |2 2|
    */
    a2.set_value(1,1,2); a2.set_value(1,2,2); a2.set_value(2,1,2); a2.set_value(2,2,2);
    std::cout << "a2: " << std::endl << a2 << std::endl;
    std::cout << "a3: " << std::endl << a3 << std::endl << dash() << std::endl;
    //Deep copy using copy constructor
    std::cout << "Deep copy using copy constructor (a2 to a4): " << std::endl; 
    matrix a4{a2};
    std::cout << "a4:" << std::endl << a4 << std::endl << dash() << std::endl;
    //Modify contents of original matrix and show copied matrix is unchanged here
    std::cout << "Now modifying a2 and outputting a4: " << std::endl; 
    /* change a2 to
    |5 1| 
    |0 7|
    */
    a2.set_value(1,1,5); a2.set_value(1,2,1); a2.set_value(2,1,0); a2.set_value(2,2,7);
    std::cout << "a2:" << std::endl << a2 << std::endl;
    std::cout << "a4:" << std::endl << a4 << std::endl << dash() << std::endl;
    //Move copy construction demonstration
    std::cout << "a5 creation using move constructor from a2: " << std::endl;
    matrix a5(std::move(a2));
    std::cout << "a2:" << std::endl << a2;
    std::cout << "a2 now empty, it has moved to a5 " << std::endl;
    std::cout << "a5:" << std::endl << a4 << std::endl << dash() << std::endl;
    // Move assignment demonstration
    std::cout << "moving a5 back to a2 using move assignment: " << std::endl;
    a2 = std::move(a5);
    std::cout << "a2:" << std::endl << a2 << std::endl;
    std::cout << "a5:" << std::endl << a5;
    std::cout << "a5 now empty, has moved to a2 " << std::endl << dash() << std::endl;
    }

  return 0;
}