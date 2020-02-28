// PHYS 30762 Programming in C++
// Assignment 5 - skeleton code

// Class for complex numbers

#include<iostream>
#include<cmath>

class complex
{
  // Make function to overload operator<< a friend
    friend std::ostream & operator<<(std::ostream &os, const complex &z);
private:
    double real,imaginary;
public:
  // Constructors & destructor
    complex(){real=imaginary=0;}
    complex(double real_part, double imaginary_part) : real{real_part}, imaginary{imaginary_part} {}
    ~complex(){}

  // Get functions
    double get_real_part() const {return real;}
    double get_imaginary_part() const {return imaginary;}
  // Set functions
    void set_real_part(const double new_real) {real = new_real;}
    void set_imaginary_part(const double new_imaginary) {imaginary = new_imaginary;}
  // Return modulus
    double modulus() const {return sqrt(real*real+imaginary*imaginary);}
  // Return argument
    double argument() const {return atan2(imaginary,real);}
  // Return complex conjugate function (outside class)
    complex conjugate() const;
  // Overload + operator for addition 

  // Overload - operator for subtraction

  // Overload * operator for multiplication, z1*z2

  // Overload / operator for division, z1/z2

};

complex complex::conjugate() const
{
    complex temporary(real, imaginary);
    temporary.set_real_part(real);
    temporary.set_imaginary_part(imaginary*-1);
    return temporary;
}

std::ostream & operator<<(std::ostream &os, const complex &v)
  {
    os<<v.real<<","<<v.imaginary<<std::endl;
    return os;
  }

// Function to overload << operator for complex numbers

int main()
{  
    std::cout.precision(3);

  // Create two complex numbers
    complex a{3,4};
    complex b{1,-2};
    std::cout << a;
    std::cout << a.conjugate();
 // Get real and imaginary components, modulus and argument

  // Get conjugates

  // Get sum, difference, product and quotient of a and b

  // Print out results, also demonstrating use of overloaded operator<<

  // Show results of overloading arithmetic operators

    return 0;
}