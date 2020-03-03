// PHYS 30762 Programming in C++
// Assignment 5 - skeleton code

// Class for complex numbers

#include<iostream>
#include<cmath>

class complex
{
  // Make function to overload operator<< a friend
  friend std::ostream & operator<<(std::ostream &out_stream, const complex &complex_number);
  friend std::istream & operator<<(std::istream &in_stream, const complex &complex_number);
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
  complex operator+(const complex &v) const
  {
    complex temp{real+v.real,imaginary+v.imaginary};
    return temp;
  }
  // Overload - operator for subtraction
  complex operator-(const complex &v) const
  {
    complex temp{real-v.real,imaginary-v.imaginary};
    return temp;
  }
  // Overload * operator for multiplication, z1*z2
  complex operator*(const complex &v) const
  {
    double total_real = real*v.real-imaginary*v.imaginary;
    double total_imaginary = real*v.imaginary+v.real*imaginary;
    complex temp{total_real, total_imaginary};
    return temp;
  }
  // Overload / operator for division, z1/z2
  complex operator/(const complex &v) const
  {
  complex conjugate = v.conjugate();
  complex numerator = operator*(conjugate);
  double denominator = pow(v.modulus(),2);
  complex temp{numerator.real/denominator, numerator.imaginary/denominator};
  return temp;
  }
};

complex complex::conjugate() const
{
  complex temporary(real, imaginary);
  temporary.set_real_part(real);
  temporary.set_imaginary_part(imaginary*-1);
  return temporary;
}

std::ostream & operator<<(std::ostream &out_stream, const complex &complex_number)
{
  if (complex_number.imaginary >= 0){
    out_stream<<complex_number.real<<"+i"<<complex_number.imaginary;
  }
  else{
    out_stream<<complex_number.real<<"-i"<<abs(complex_number.imaginary);
  }
  return out_stream;
}

std::istream & operator>>(std::istream &in_stream, complex &complex_number)
{
  double real_part;
  double imaginary_part;
  char sign_imaginary_part;

  in_stream >> real_part >> sign_imaginary_part >> imaginary_part;
  //This will fail due to the 'i' after sign_imaginary_part so we need a statement:
  if(in_stream.fail()){
    in_stream.clear();
    in_stream.ignore();
    in_stream >> imaginary_part;
  }
  else{
    in_stream.ignore();
  }
  complex_number.set_real_part(real_part);
  if ((imaginary_part == 0) || (sign_imaginary_part == '+')){
    complex_number.set_imaginary_part(imaginary_part);
  }
  else{
    complex_number.set_imaginary_part(imaginary_part * -1);
  }
}

// Function to overload << operator for complex numbers
void dash(){
  std::cout << "----------------------------------" << std::endl;
}

int main()
{  
  dash();
  std::cout << "Complex numbers program ULTRA8000" << std::endl;
  dash();
  std::cout.precision(3);
  // Create two complex numbers
  complex a{3,4};
  complex b{1,-2};
  std::cout << "Pre-set example, complex numbers: " << std::endl;
  std::cout << "     " << a <<  "     and     " << b <<std::endl;
  dash();
  // Get real and imaginary components, modulus and argument
  // Get sum, difference, product and quotient of a and b
  std::cout << "Results: " << std::endl;
  std::cout << "sum " <<  a + b <<std::endl;
  std::cout << "difference " << a - b <<std::endl;
  std::cout << "product " << a * b <<std::endl;
  std::cout << "quotient " << a / b <<std::endl;
  std::cout << "conjugate of " << a << ": " << a.conjugate() << std::endl;
  std::cout << "conjugate of " << b << ": " << b.conjugate() << std::endl;
  dash();
  // Print out results, also demonstrating use of overloaded operator<<
  // Show results of overloading arithmetic operators

  complex first_complex_number;
  complex second_complex_number;

  std::cout << first_complex_number << std::endl;
  std::cout << "Enter first complex number: " << std::endl;
  std::cin >> first_complex_number;
  std::cout << "Enter second complex number: " << std::endl;
  std::cin >> second_complex_number;
  dash();
  std::cout << "Your complex numbers: " << std::endl;
  std::cout << " " << first_complex_number <<  " and " << second_complex_number <<std::endl;
  dash();
  std::cout << "Results: " << std::endl;
  std::cout << "sum " <<  first_complex_number + second_complex_number <<std::endl;
  std::cout << "difference " << first_complex_number - second_complex_number <<std::endl;
  std::cout << "product " << first_complex_number * second_complex_number <<std::endl;
  std::cout << "quotient " << first_complex_number / second_complex_number <<std::endl;
  std::cout << "conjugate of " << first_complex_number << ": " << first_complex_number.conjugate() << std::endl;
  std::cout << "conjugate of " << second_complex_number << ": " << second_complex_number.conjugate() << std::endl;
  dash();


  return 0;
}