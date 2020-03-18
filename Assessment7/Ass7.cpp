//18th March 2020
//Tymoteusz Chatys
//Assignment 7
//Visual studio code


#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>

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

class vector
{
    //friends of the class
    friend std::istream& operator>>(std::istream& in_stream, vector& a_vector);
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
double &vector::operator[](const size_t index) {
  if (index < 0){
    std::cout << dash(1) << std::endl << "Error: invalid input" << std::endl << "Index cannot be negative" << dash(1); exit(1);
  }else if(index > size-1){
    std::cout << dash(1) << std::endl << "Error: invalid input" << std::endl << "Index provided out of range of vector" << dash(1); exit(1);    
  }
  return vector_data[index];
}
//Overload << operator to output vectors
std::ostream &operator<<(std::ostream &out_stream, const vector &a_vector){
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
std::istream& operator>>(std::istream& in_stream, vector& a_vector)
{
	/*
	Input example:
	1 2 12
	*/
	//Get the number of rows and columns
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

double vector::operator*(const vector& a_vector) const
{
    double dot_product{0};
    if (size != a_vector.size) {
        std::cout << "Error: vectors must have the same size" << std::endl; exit(1);
    }
    for (int i{0}; i < size; i++) {
    dot_product += vector_data[i] * a_vector.vector_data[i];
    }
    return dot_product;
}


void vector_class_output()
{
    //Demonstrate default constructor
    vector v1;
    std::cout << "Default constructor (v1): " << std::endl << v1 << std::endl << dash(0) << std::endl;
    //Demonstrate parameterized constructor
    /* Make vector v2
    |1 2|
    |3 4|
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
    |2 2|
    |2 2|
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
    |5 1|
    |0 7|
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
    // Move assignment demonstration
    std::cout << "moving v5 back to v2 using move assignment: " << std::endl;
    v2 = std::move(v5);
    std::cout << "v2:" << std::endl << v2 << std::endl;
    std::cout << "v5:" << std::endl << v5;
    std::cout << "v5 now empty, has moved to v2 " << std::endl << dash(0) << std::endl;
    

    vector first_vector;
    vector second_vector;
    std::cin >> first_vector;
    std::cout << dash(0) << std::endl;
    std::cin >> second_vector;
    std::cout << dash(0) << std::endl;
    std::cout << "Your vectors: " << std::endl << "v1: " << std::endl << first_vector << std::endl;
    std::cout << "v2: " << std::endl << second_vector << std::endl << dash(0) << std::endl;
    //Multiplication of 2 vectors
    std::cout << "Dot product (v1*v2): " << std::endl << first_vector*second_vector << std::endl << dash(0) << std::endl;
    std::string option;
    getline(std::cin, option);
}

int main()
{
    //Clears prvious inputs in the terminal
    std::system("clear");
	std::cout << std::setprecision(3);
	std::cout << dash(0) << dash(0) << std::endl << "vector calculator" << std::endl << dash(0) << dash(0) << std::endl;
	std::cout << "Which option would you like to choose?" << std::endl;
	std::cout << "1 - vector class" << std::endl;
	std::cout << "2 - 4-vector class" << std::endl;
    std::cout << "3 - particle class" << std::endl;
	std::cout << "4 - all" << std::endl << dash(0) << dash(0) << std::endl;
	//Asks user to choose an option
	std::string option;
	getline(std::cin, option);
    if (option == "1") {
		vector_class_output();
	}
    else if (option == "2") {}
        /*
	}else if (option == "3") {
		std::cout << dash() << std::endl;
		std::cout << "Instructions for input" << std::endl;
		std::cout << dash() << std::endl;
		std::cout << "You can enter your numbers as space seperated string for example: " << std::endl;
		std::cout << " 1 2 12 2 5 7 12 2 1 " << std::endl;
		std::cout << "or you can enter them by pressing enter 1 by 1 for example: " << std::endl;
		std::cout << "1" << std::endl << "2" << std::endl << "12" << std::endl << "2" << std::endl << "5" << std::endl << "7" << std::endl;
		std::cout << "12" << std::endl << "2" << std::endl << "1" << std::endl << dash() << std::endl;
		std::cout << "The output format for this vector would be : " << std::endl;
		std::cout << "|1 2 12|" << std::endl;
		std::cout << "|2 5 7| " << std::endl;
		std::cout << "|12 2 1|" << std::endl;
		std::cout << dash() << std::endl;
		std::cout << "Thank you for using the program, restart the program to use" << std::endl;
		std::cout << dash() << std::endl;
	}
    */
    
	std::cout << "Input anything to exit " << std::endl;
	std::cin.ignore();
	std::cin.get();
	return 0;

}