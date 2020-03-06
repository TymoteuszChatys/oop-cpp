// PHYS 30762 Programming in C++
// Assignment 5 - Tymoteusz Chatys
// 6th March 2020

#include<iostream>
#include<cmath>
#include<string>

// Class for complex numbers
class complex
{
  // Friends of the class
  friend std::ostream & operator<<(std::ostream &out_stream, const complex &complex_number);
  friend std::istream & operator>>(std::istream &in_stream, const complex &complex_number);
private:
  double real,imaginary;
public:
  // Constructors & destructor
  complex(){real=imaginary={};}
  complex(double real_part, double imaginary_part) : real{real_part}, imaginary{imaginary_part} {}
  ~complex(){}
  // Get functions
  double get_real_part() const 
  {
    return real;
  }
  double get_imaginary_part() const 
  {
    return imaginary;
  }
  // Set functions
  void set_real_part(const double new_real) 
  {
    real = new_real;
  }
  void set_imaginary_part(const double new_imaginary) 
  {
    imaginary = new_imaginary;
  }
  // Return modulus
  double modulus() const 
  {
    return sqrt(real*real+imaginary*imaginary);
  }
  // Return argument
  double argument() const 
  {
    return atan2(imaginary,real);
  }
  // Return complex conjugate function (outside class)
  complex conjugate() const;
  // Overload + operator for addition 
  complex operator+(const complex &complex_number) const
  {
    complex temp{real+complex_number.real,imaginary+complex_number.imaginary};
    return temp;
  }
  // Overload - operator for subtraction
  complex operator-(const complex &complex_number) const
  {
    complex temp{real-complex_number.real,imaginary-complex_number.imaginary};
    return temp;
  }
  // Overload * operator for multiplication, z1*z2
  complex operator*(const complex &complex_number) const
  {
    double total_real = real*complex_number.real-imaginary*complex_number.imaginary;
    double total_imaginary = real*complex_number.imaginary+complex_number.real*imaginary;
    complex temp{total_real, total_imaginary};
    return temp;
  }
  // Overload / operator for division, z1/z2
  complex operator/(const complex &complex_number) const
  {
    complex conjugate = complex_number.conjugate();
    complex numerator = operator*(conjugate);
    double denominator = pow(complex_number.modulus(),2);
    complex temp{numerator.real/denominator, numerator.imaginary/denominator};
    if (complex_number.real == 0 && complex_number.imaginary == 0){
      complex temp{std::nan(""), std::nan("")};
    }
    return temp;
  }
};

//calculates the conjugate (flips the imaginary sign)
complex complex::conjugate() const
{
  complex temporary(real, imaginary);
  if(imaginary != 0){
    temporary.set_imaginary_part(imaginary*-1);
  }
  return temporary;
}

//Outstream operator overload
std::ostream & operator<<(std::ostream &out_stream, const complex &complex_number)
{
  if (complex_number.imaginary >= 0){
    out_stream<<complex_number.real<<"+i"<<complex_number.imaginary;
  }else{
    out_stream<<complex_number.real<<"-i"<<abs(complex_number.imaginary);
  }
  return out_stream;
}

//Instream operator overload function
std::istream & operator>>(std::istream &in_stream, complex &complex_number)
{
  double real_part;
  double imaginary_part;
  char sign_imaginary_part;
  //In order to make it work for a+bi and a+ib we have the following code:
  in_stream >> real_part >> sign_imaginary_part >> imaginary_part;
  //This will fail due to the 'i' after sign_imaginary_part in case of a+ib format so we need a statement:
  if(in_stream.fail()){
    in_stream.clear();
    in_stream.ignore();
    in_stream >> imaginary_part;
  }else{
    in_stream.ignore();
  }
  complex_number.set_real_part(real_part);

  if ((imaginary_part == 0) || (sign_imaginary_part == '+')){
    complex_number.set_imaginary_part(imaginary_part);
  }else if (sign_imaginary_part == '-'){
    complex_number.set_imaginary_part(imaginary_part * -1);
  }
  return in_stream;
}

// Function to return a break for a better viewing experience
std::string dash(){
  std::string break_line;
  break_line = "--------------------------------------";
  return break_line;
}

int main()
{ 
  // Introductory output
  std::cout << dash() << std::endl << "Complex numbers program by T Chatys" << std::endl << dash() << std::endl;
  // Sets precision of output
  std::cout.precision(3);
  // Create two complex numbers
  complex a{3,4};
  complex b{1,-2};
  std::cout << "Pre-set example, complex numbers: " << std::endl;
  std::cout << "     " << a <<  "     and     " << b <<std::endl << dash() << std::endl;
  // //Output the results of preset example:
  std::cout << "Results: " << std::endl;
  std::cout << "sum " <<  a + b <<std::endl;
  std::cout << "difference " << a - b <<std::endl;
  std::cout << "product " << a * b <<std::endl;
  std::cout << "quotient " << a / b <<std::endl;
  std::cout << "conjugate of " << a << ": " << a.conjugate() << std::endl;
  std::cout << "conjugate of " << b << ": " << b.conjugate() << std::endl << dash() << std::endl;

  bool to_stop{};
  std::string string_to_stop;
  do{
    std::cout << "complex number in format a+ib" << std::endl;
    std::cout << "a and b to be specified even if zero." << std::endl ;
    std::cout << "enter more complex numbers? (y/n)" << std::endl << dash() << std::endl;
    //Asks user whether to continue
    getline(std::cin, string_to_stop);
    if(string_to_stop=="n"){
      //If n is entered exit while loop;
      to_stop = true;
    }else if(string_to_stop=="y"){
      //Ask for first complex number
      complex first_complex_number;
      std::cout << std::endl << "Enter first complex number: " << std::endl << dash() << std::endl;
      std::cin >> first_complex_number;
      std::cin.ignore();
      //Ask for second complex number
      complex second_complex_number;
      std::cout << dash() << std::endl << "Enter second complex number: " << std::endl << dash() << std::endl;;
      std::cin >> second_complex_number;
      std::cin.ignore();
      //Output the results:
      std::cout << dash() << std::endl << "Your complex numbers: " << std::endl << dash() <<std::endl;
      std::cout << " " << first_complex_number <<  " and " << second_complex_number <<std::endl << dash() << std::endl;
      std::cout << "Results: " << std::endl;
      std::cout << "sum " <<  first_complex_number + second_complex_number <<std::endl;
      std::cout << "difference " << first_complex_number - second_complex_number <<std::endl;
      std::cout << "product " << first_complex_number * second_complex_number <<std::endl;
      std::cout << "quotient " << first_complex_number / second_complex_number <<std::endl;
      std::cout << "conjugate of " << first_complex_number << ": " << first_complex_number.conjugate() << std::endl;
      std::cout << "conjugate of " << second_complex_number << ": " << second_complex_number.conjugate() << std::endl << dash() << std::endl;
    }
  }while(to_stop == false);
  //End program at input
  std::cout << "Input anything to exit " << std::endl; 
  std::cin.ignore();  
  std::cin.get(); 
  return 0;
}