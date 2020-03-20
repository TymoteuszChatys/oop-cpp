//20th March 2020
//Tymoteusz Chatys
//Assignment 7
//Visual studio code

#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>
#include<algorithm>

//custom break lines for better output visualisation 
//error(0) -> "---------------------------------------"
//error(1) -> "-----------------ERROR-----------------"
std::string dash(int i)
{
    std::string break_line;
    if(i==0){
	    break_line = "---------------------------------------";
    }else if(i==1){
	    break_line = "-----------------ERROR-----------------";
    }
	return break_line;
}

// VECTOR CLASS
class vector
{
  //friends of the class
  friend std::istream& operator>>(std::istream &in_stream, vector& a_vector);
  friend std::ostream &operator<<(std::ostream &out_stream, const vector &a_vector);

protected:
  double* vector_data{nullptr};
  size_t size{};

public:
  // Default, Parameterized, Copy, Move Constructor
  vector();
	vector(size_t length);
	vector(const vector& a_vector);
	vector(vector&& a_vector) noexcept;
	// Destructor
	~vector() {delete[] vector_data;};
  //Copy and Move Assignment operators
	vector& operator=(vector& a_vector);
	vector& operator=(vector&& a_vector) noexcept;
  //overload [] operator for accessing elements of the vector
  double& operator[](const size_t index);
  //overload * for dot product of two vectors
  double operator*(const vector& a_vector) const;
  //get and set functions
  size_t get_size() const
	{
    return size;
	}
  void set_value(const size_t& i, const double& value)
	{//Set value i'th component of the vector
		vector_data[i] = value;
	}
};
//Default constructor
vector::vector() : size{2}
{
	vector_data = new double[size]{};
}
//Parameterized constructor
vector::vector(size_t length) : size{length}, vector_data{ new double[length]{} }
{
	if (length == 0) {
		std::cout << "Error: 0 dimensional vector";
		exit(1);
	}
}
//Copy constructor
vector::vector(const vector& a_vector) : size{a_vector.size}
{
	vector_data = nullptr;
	if (size > 0) {
		vector_data = new double[size] {};
		for (size_t i{}; i < size; i++) {
			vector_data[i] = a_vector.vector_data[i];
		}
	}
}
//Move constructor (steals the data)
vector::vector(vector&& a_vector) noexcept
{
	size = a_vector.size;
	vector_data = a_vector.vector_data;
	a_vector.size = {};
	a_vector.vector_data = nullptr;
}
//Copy assignment operator
vector& vector::operator=(vector& a_vector)
{
	if (&a_vector == this) { //no self assignment
		return *this;
	}
	//First need to delete the objects array
	delete[] vector_data;
	vector_data = {};
	//Copy the size and declare new array
	size = a_vector.size;
	vector_data = new double[size];
	//Copy values into new array
	for (size_t i{}; i < size; i++) {
		vector_data[i] = a_vector.vector_data[i];
	}
	return *this;
}
//Move assignment operator
vector& vector::operator=(vector&& a_vector) noexcept
{
	std::swap(size, a_vector.size);
	std::swap(vector_data, a_vector.vector_data);
	return *this;
}

//Overload [] operator for accessing elements of the vector
double &vector::operator[](const size_t index) 
{
  if (index < 0){
    std::cout << dash(1) << std::endl << "Error: invalid input" << std::endl << "Index cannot be negative" << dash(1); exit(1);
  }else if(index > size-1){
    std::cout << dash(1) << std::endl << "Error: invalid input" << std::endl << "Index provided out of range of vector" << dash(1); exit(1);    
  }
  return vector_data[index];
}
//Overload << operator to output vectors
//In the format [1;2;3;4;5;6]
std::ostream &operator<<(std::ostream &out_stream, const vector &a_vector)
{
  if(a_vector.get_size() > 0){
    out_stream << "[";
    for (size_t index{0}; index < a_vector.get_size(); index++) {
      if (index == a_vector.get_size() - 1) {
        out_stream << a_vector.vector_data[index] << "]";
      }else{
        out_stream << a_vector.vector_data[index] << ";";
      }
    }
  }else{
    out_stream << "vector is empty" << std::endl;
  }
  return out_stream;
}

//Overload >> operator to input vectors
std::istream &operator>>(std::istream &in_stream, vector &a_vector)
{
	/*
	Input example:
	1 2 12
	*/
	//Get the size of the vector
	size_t size;
	std::cout << "Enter the size of your vector: ";
	std::cin >> size;
	if (std::cin.fail() || size < 1) {
		std::cout << "Error: invalid input" << std::endl; exit(1);
		//throw("positive integer error");
	}

	vector temporary_vector(size);
	//Get vector values 
	std::cout << "Enter values of the vector (" << size << " values)" << std::endl;
	//Loop to fill the vector from input
	for (size_t i{}; i < size; i++) {
        double temporary;
        std::cin >> temporary;
        std::cin.ignore();
        temporary_vector.set_value(i,temporary);
        if (std::cin.fail()) {
            std::cout << "Error: invalid input" << std::endl; exit(1);
            //throw("new element of vector error");
        }
	}
	a_vector = temporary_vector;
	return in_stream;
}
//Overload * to represent the dot product between vectors
double vector::operator*(const vector& a_vector) const
{
    double dot_product{};
    if (size != a_vector.size) {
        std::cout << "Error: vectors must have the same size" << std::endl; exit(1);
    }
    for (size_t i{}; i < size; i++) {
    dot_product += vector_data[i] * a_vector.vector_data[i];
    }
    return dot_product;
}
//Output function for the vector class
void vector_class_output(size_t option)
{
  if(option==0){
      std::cout << "VECTOR-CLASS" << std::endl << dash(0) << std::endl;
      //Demonstrate default constructor
      vector v1;
      std::cout << "Default constructor (v1): " << std::endl << v1 << std::endl << dash(0) << std::endl;
      //Demonstrate parameterized constructor
      /* Make vector v2
      [6;3;2]
      */
      vector v2{3};
      std::cout << "Parameterized constructor (v2): " << std::endl << v2 << std::endl << dash(0) << std::endl;
      v2.set_value(0,6); v2.set_value(1,3); v2.set_value(2,2);
      std::cout << "Parameterized constructor (v2) after setting values (6,3,2): " << std::endl << v2 << std::endl << dash(0) << std::endl;
      //Deep copy by assignment: define new vector v3 then copy from v2 to v3
      std::cout << "Deep copy by assignmnent: " << std::endl;
      vector v3{3};
      std::cout << "Default (v3): " << std::endl << v3 << std::endl;
      v3 = v2;
      std::cout << "Deep copy (v2 to v3): " << std::endl << v3 << std::endl << dash(0) << std::endl;
      //Modify contents of original vector and show assigned vector is unchanged here
      std::cout << "Now modifying v2 and outputting v3: " << std::endl;
      /* change v2 to
      [2;2;2]
      */
      v2.set_value(0,2); v2.set_value(1,2); v2.set_value(2,2);
      std::cout << "v2: " << std::endl << v2 << std::endl;
      std::cout << "v3: " << std::endl << v3 << std::endl << dash(0) << std::endl;
      //Deep copy using copy constructor
      std::cout << "Deep copy using copy constructor (v2 to v4): " << std::endl;
      vector v4{v2};
      std::cout << "v4:" << std::endl << v4 << std::endl << dash(0) << std::endl;
      //Modify contents of original vector and show copied vector is unchanged here
      std::cout << "Now modifying v2 and outputting v4: " << std::endl;
      /* change v2 to
      [5;1;0]
      */
      v2.set_value(0,5); v2.set_value(1,1); v2.set_value(2,0);
      std::cout << "v2:" << std::endl << v2 << std::endl;
      std::cout << "v4:" << std::endl << v4 << std::endl << dash(0) << std::endl;
      //Move copy construction demonstration
      std::cout << "v5 creation using move constructor from v2: " << std::endl;
      vector v5(std::move(v2));
      std::cout << "v2:" << std::endl << v2;
      std::cout << "v2 now empty, it has moved to v5 " << std::endl;
      std::cout << "v5:" << std::endl << v5 << std::endl << dash(0) << std::endl;
      //Move assignment demonstration
      std::cout << "moving v5 back to v2 using move assignment: " << std::endl;
      v2 = std::move(v5);
      std::cout << "v2:" << std::endl << v2 << std::endl;
      std::cout << "v5:" << std::endl << v5;
      std::cout << "v5 now empty, has moved to v2 " << std::endl << dash(0) << std::endl;
      std::cout << "Accessing 2nd value of vector v2 located at v2[1]: " << std::endl << v2[1] << std::endl << dash(0) << std::endl;
  }else if(option == 1){
      //If dot product only is chosen
      std::cout << "Enter two vectors to receive the dot product: " <<  std::endl;
      vector first_vector;
      vector second_vector;
      std::cin >> first_vector;
      std::cout << dash(0) << std::endl;
      std::cin >> second_vector;
      std::cout << dash(0) << std::endl;
      std::cout << "Your vectors: " << std::endl << "v1: "  << first_vector << std::endl;
      std::cout << "v2: " << second_vector << std::endl << dash(0) << std::endl;
      //Dot product of 2 vectors
      std::cout << "Dot product (v1*v2): " << std::endl << first_vector*second_vector << std::endl << dash(0) << std::endl;
  }
}

//--------------------------------------------------------------------------------------------------------------------------
//4-Vector class in the form (ct,x,y,z)
//--------------------------------------------------------------------------------------------------------------------------

class four_vector : public vector
{
  //friends of the class
  friend std::istream &operator>>(std::istream &in_stream, four_vector &a_four_vector);
  friend std::ostream &operator<<(std::ostream &out_stream, const four_vector &a_four_vector); 

public:
  //Default, Parameterized (x2), Copy, Move Constructor
  four_vector();
  four_vector(const double &ct, vector &a_vector);
  four_vector(const double &ct, const double &x, const double &y, const double &z);
  four_vector(const four_vector &a_four_vector)  : vector(a_four_vector) {};
  four_vector(four_vector &&a_four_vector) : vector(std::move(a_four_vector)) {};
  //Copy and Move Assignment operators
  four_vector &operator=(four_vector &a_four_vector);
  four_vector &operator=(four_vector &&a_four_vector);
  //Overload [] operator for accessing elements of the four vector
  using vector::operator[];
  //Dot Product for 4-vectors
  double operator*(const four_vector& a_four_vector) const;
  //gamma/Lorentz Factor
  double gamma(vector &beta);
  //Lorentz boost
  four_vector lorentz_boost(vector &beta);
};

//Default Constructor
four_vector::four_vector() : vector(4) {}
//Parameterized Constructor with a double and a vector
four_vector::four_vector(const double &ct, vector &a_vector) : vector(4) 
{
  vector_data[0] = ct;
  for(size_t i{1}; i < 4; i++){
        vector_data[i] = a_vector[i-1];
  }
}
//Parameterized Constructor with 4 doubles.
four_vector::four_vector(const double &ct, const double &x, const double &y,const double &z): vector(4) 
{
  vector_data[0] = ct;
  vector_data[1] = x;
  vector_data[2] = y;
  vector_data[3] = z;
}
//Copy Assignment
four_vector &four_vector::operator=(four_vector &a_four_vector)
{
  vector::operator=(a_four_vector);
  return *this;
}
//Move Assignment 
four_vector &four_vector::operator=(four_vector &&a_four_vector) 
{
  vector::operator=(std::move(a_four_vector));
  return *this;
}
//Dot Product for 4-vectors
double four_vector::operator*(const four_vector& a_four_vector) const
{
    double dot_product{};
    if (size != 4) {
        std::cout << "Error: vectors must have the same size" << std::endl; exit(1);
    }
    for (size_t i{1}; i < size; i++) {
    dot_product += vector_data[i] * a_four_vector.vector_data[i];
    }
    return vector_data[0] * a_four_vector.vector_data[0] - dot_product;
}

std::istream& operator>>(std::istream& in_stream, four_vector &a_four_vector)
{
	/*
	Input example:
	1 2 12 2
	*/
  size_t size = 4;
	//Get vector values 
	std::cout << "Enter values of the four-vector (" << size << " values)" << std::endl;
	//Loop to fill the vector from input
	for (size_t i{}; i < size; i++) {
        double temporary;
        std::cin >> temporary;
        std::cin.ignore();
        if (std::cin.fail()) {
            std::cout << "Error: invalid input" << std::endl; exit(1);   
        }
        a_four_vector.vector_data[i] = temporary;  
	}
	return in_stream;
}
//Output overload for four vector
//Output example
//[5;2;2;4]
std::ostream &operator<<(std::ostream &out_stream, const four_vector &a_four_vector)
{
  if(a_four_vector.get_size() > 0){
    out_stream << "[";
    for (size_t index{0}; index < a_four_vector.get_size(); index++) {
      if (index == a_four_vector.get_size() - 1) {
        out_stream << a_four_vector.vector_data[index] << "]";
      }else{
        out_stream << a_four_vector.vector_data[index] << ";";
      }
    }
  }else{
    out_stream << "vector is empty" << std::endl;
  }
  return out_stream;
}
//Lorentz boost function to calculte boosted four_vector
four_vector four_vector::lorentz_boost(vector &beta)
{
  if (beta.get_size() != 3) {
    std::cout << "Error: beta must be of size 3" << std::endl; exit(1);
  }
  //Calculation of lorentz factor
  double lorentz_factor = gamma(beta);
  double betasqared = beta*beta; 
  bool valid{true};
  
  //Now we only want to extract the position vector from the 4-vector to enable dot product
  vector position{3};
  
  //checking the validity of beta
  for(size_t i{}; i<3; i++){
    position[i] = vector_data[i+1];
    if(beta[i] >= 1 || beta[i] <= -1) {
      valid = false;
    }
  }
  if(betasqared >= 1 || valid == false){
    std::cout << "Error: this beta cannot physically exist" << std::endl; exit(1);
  }
  four_vector lorentz_boosted_vector{};
  //time component calculation
  lorentz_boosted_vector[0] = lorentz_factor*(vector_data[0]-beta*position);
  //position component calculations
  for(size_t i{0}; i<3; i++) {
    lorentz_boosted_vector[i+1] = vector_data[i+1] + beta[i]*((lorentz_factor-1)*((position*beta)/betasqared)-lorentz_factor*vector_data[0]);
  }
  return lorentz_boosted_vector;
}
//Gamma/ Lorentz factor function
double four_vector::gamma(vector &beta)
{
  return 1/sqrt(1-beta*beta);
}
//Four vector class output 
void four_vector_class_output(size_t option)
{
  if(option==0){
    std::cout << "FOUR-VECTOR-CLASS" << std::endl << dash(0) << std::endl;
    //Demonstrate default constructor
    four_vector fv1;
    std::cout << "Default constructor (fv1): " << std::endl << fv1 << std::endl << dash(0) << std::endl;
    //Demonstrate parameterised constructor
    vector v2{3};
    four_vector fv2{0,v2}; //Parameterised constructor with a double and a vector is shown but this will work equally as well with the 4 double parameterised constructor.
    std::cout << "Parameterized constructor (fv2): " << std::endl << fv2 << std::endl << dash(0) << std::endl;
    fv2[0] = 4;
    fv2[1] = 6;
    fv2[2] = 3;
    fv2[3] = 2;
    /* Make vector fv2
    [4;6;3;2|
    */
    std::cout << "Parameterized constructor (fv2) after setting values (ct,x,y,z) to (4,6,3,2): " << std::endl << fv2 << std::endl << dash(0) << std::endl;
    //Deep copy by assignment: define new vector fv3 then copy from fv2 to fv3
    std::cout << "Deep copy by assignmnent: " << std::endl;
    four_vector fv3;
    std::cout << "Default (fv3): " << std::endl << fv3 << std::endl;
    fv3=fv2;
    std::cout << "Deep copy (fv2 to fv3): " << std::endl << fv3 << std::endl << dash(0) << std::endl;
    //Modify contents of original vector and show assigned vector is unchanged here
    std::cout << "Now modifying fv2 and outputting fv3: " << std::endl;
    /* change v2 to
    [2;2;2;2]
    */
    fv2[0] = 2;
    fv2[1] = 2;
    fv2[2] = 2;
    fv2[3] = 2;
    std::cout << "fv2: " << std::endl << fv2 << std::endl;
    std::cout << "fv3: " << std::endl << fv3 << std::endl << dash(0) << std::endl;
    //Deep copy using copy constructor
    std::cout << "Deep copy using copy constructor (fv2 to fv4): " << std::endl;
    four_vector fv4{fv2};
    std::cout << "fv4:" << std::endl << fv4 << std::endl << dash(0) << std::endl;
    //Modify contents of original vector and show copied vector is unchanged here
    std::cout << "Now modifying fv2 and outputting fv4: " << std::endl;
    /* change fv2 to
    [3;5;1;0]
    */
    fv2[0] = 3;
    fv2[1] = 5;
    fv2[2] = 1;
    fv2[3] = 0;
    std::cout << "fv2:" << std::endl << fv2 << std::endl;
    std::cout << "fv4:" << std::endl << fv4 << std::endl << dash(0) << std::endl;
    //Move copy construction demonstration
    std::cout << "fv5 creation using move constructor from fv2: " << std::endl;
    four_vector fv5(std::move(fv2));
    std::cout << "fv2:" << std::endl << fv2;
    std::cout << "fv2 now empty, it has moved to fv5 " << std::endl;
    std::cout << "fv5:" << std::endl << fv5 << std::endl << dash(0) << std::endl;
    // Move assignment demonstration
    std::cout << "moving fv5 back to fv2 using move assignment: " << std::endl;
    fv2 = std::move(fv5);
    std::cout << "fv2:" << std::endl << fv2 << std::endl;
    std::cout << "fv5:" << std::endl << fv5;
    std::cout << "fv5 now empty, has moved to fv2 " << std::endl << dash(0) << std::endl;
    std::cout << "Accessing 2nd value of vector fv2 located at fv2[1]: " << std::endl << fv2[1] << std::endl << dash(0) << std::endl;
  }else if(option == 1){ //If only the dot product of 2 vectors is chosen
    std::cout << "Enter two four-vectors to receive the dot product: " <<  std::endl;
    four_vector first_four_vector;
    four_vector second_four_vector;
    std::cin >> first_four_vector;
    std::cout << dash(0) << std::endl;
    std::cin >> second_four_vector;
    std::cout << dash(0) << std::endl;
    std::cout << "Your vectors: " << std::endl << "fv1: "  << first_four_vector << std::endl;
    std::cout << "fv2: " << second_four_vector << std::endl << dash(0) << std::endl;
    //Dot product of 2 vectors
    std::cout << "Dot product (fv1*fv2): " << std::endl << first_four_vector*second_four_vector << std::endl << dash(0) << std::endl;
  }else if(option == 2){
    std::cout << "Enter the four-vector you would like to boost followed by a three-vector beta booster (3 must be specified when asked)" << std::endl;
    four_vector boost_four_vector;
    std::cin >> boost_four_vector;
    std::cout << dash(0) << std::endl;
    vector beta{3};
    std::cin >> beta;
    std::cout << dash(0) << std::endl << "Your vectors " << std::endl << "fv: " << boost_four_vector << std::endl;
    std::cout << "beta: " << beta << std::endl;
    std::cout << boost_four_vector.lorentz_boost(beta);
  }
}


//--------------------------------------------------------------------------------------------------------------------------
//PARTICLE CLASS
//--------------------------------------------------------------------------------------------------------------------------

class particle
{
  friend std::ostream &operator<<(std::ostream &out_stream, particle &a_particle);

private:
  four_vector particle_four_vector;
  vector particle_beta{3};
  double particle_mass;

public:
  //parameterised constructor
  particle(const four_vector &a_four_vector,const double &mass, const vector &beta): particle_four_vector{a_four_vector}, particle_mass{mass}, particle_beta{beta} {}
  //functions for lorentz factor, momentum and total energy
  double get_gamma();
  vector get_momentum();
  double get_total_energy();
};
//function returns gamma
double particle::get_gamma()
{
  return 1/sqrt(1-particle_beta*particle_beta);
}
//function returns momentum
vector particle::get_momentum() 
{
  vector momentum{3};
  for (int i{0}; i < 3; i++) {
    momentum[i] = get_gamma() * particle_mass * particle_beta[i];
  }
  return momentum;
}
//function returns total energy
double particle::get_total_energy() 
{
  double momentum_squared{(get_momentum())*(get_momentum())};
  double energy = sqrt(pow(particle_mass, 2) + momentum_squared);
  return energy;
}

// define ostream behaviour for particle class
std::ostream &operator<<(std::ostream &out_stream, particle &a_particle) 
{
  out_stream << "position = " << a_particle.particle_four_vector << std::endl << "beta = " << a_particle.particle_beta << std::endl << "mass = " << a_particle.particle_mass << std::endl;
  return out_stream;
}

void particle_class_output()
{
  std::cout << "PARTICLE-CLASS" << std::endl << dash(0) << std::endl;
  //Ask user for the four vector of the particle
  four_vector particle_four_vector;
  std::cout << "Position vector for the particle: " << std::endl;
  std::cout << "Suggestion: 2 4 3 2" << std::endl;
  std::cin >> particle_four_vector;
  //Ask user for the mass of the particle
  double mass;
  std::cout << dash(0) << std::endl << "Enter mass of the particle (eV): " << std::endl;
  std::cout << "Suggestion: 5e8" << std::endl;
  std::cin >> mass;
  std::cin.ignore();
  if (std::cin.fail()) {
    std::cout << "Error: invalid input" << std::endl; exit(1);   
  }
  //Ask user for the beta of the particle
  vector beta;
  std::cout << dash(0) << std::endl << "Enter beta (in units v/c (dimensionless)) (must first specify it is of size 3!): " << std::endl;
  std::cout << "Suggestion: 0.34 0.22 0.45" << std::endl;
  std::cin >> beta;
  //Check if beta is valid 
  bool valid = true;
  for(size_t i{}; i<3; i++){
    if(beta[i] >= 1 || beta[i] <= -1) {
      valid = false;
    }
  }
  if(beta*beta >= 1 || valid == false){
    std::cout << "Error: this beta cannot physically exist" << std::endl; exit(1);
  }
  //Parameterised constructor
  particle particle_1{particle_four_vector, mass, beta};
  std::cout << "Parameterised constructor" << std::endl << dash(0) << std::endl << "Particle : " << std::endl << particle_1 << dash(0) << std::endl; 
  std::cout << "This particle has the following properties:" << std::endl;
  //Lorentz factor (gamma)
  std::cout << "Lorentz factor : " << particle_1.get_gamma() <<  std::endl;
  //Momentum
  std::cout << "Momentum : " << particle_1.get_momentum() << " MeV/c" << std::endl;
  //Total energy
  std::cout << "Total energy : " << particle_1.get_total_energy() << std::endl << " MeV/c^2" << dash(0) << std::endl;
}

int main()
{
	std::cout << std::setprecision(5);
	std::cout << dash(0) << dash(0) << std::endl << "vector calculator" << std::endl << dash(0) << dash(0) << std::endl;
	std::cout << "Which option would you like to choose?" << std::endl;
	std::cout << "-1a  vector class demonstration" << std::endl;
  std::cout << "-1b  vector class dot product" << std::endl;
	std::cout << "-2a  4-vector class demonstration" << std::endl;
  std::cout << "-2b  4-vector class dot product" << std::endl;
  std::cout << "-2c  4-vector class Lorentz transform" << std::endl;
  std::cout << "-3   particle class" << std::endl;
	std::cout << "-4   all" << std::endl << dash(0) << dash(0) << std::endl;
	//Asks user to choose an option
	std::string option;
	getline(std::cin, option);
  if (option == "1a") {
		vector_class_output(0); //Demonstration only
	}else if (option == "1b"){
    vector_class_output(1); //Dot Product only
  }else if (option == "2a") {
    four_vector_class_output(0); //Demonstration only 
  }else if (option == "2b"){
    four_vector_class_output(1); //Dot product only
  }else if (option == "2c"){
    four_vector_class_output(2); // Lorentz Transform only
  }else if (option == "3"){
    particle_class_output(); //Particle class
  }else if (option == "4"){ //All of the above
    vector_class_output(0);
    vector_class_output(1);
    four_vector_class_output(0);
    four_vector_class_output(1);
    four_vector_class_output(2);
    particle_class_output();
  }else{
    std::cout << "No valid option detected " << std::endl;
  }
	std::cout << "Input anything to exit " << std::endl;
	std::cin.ignore();
	std::cin.get();
	return 0;
}