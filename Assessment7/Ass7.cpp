//16th March 2020
//Assignment 7
//Visual studio code


#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>

std::string dash(int i)
{
    std::string break_line;
    if(i=0){
	    break_line = "---------------------------------------";
    }else if(i=1){
	    break_line = "-----------------ERROR-----------------";
    }
	return break_line;
}

class vector
{

private:
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


};

//Default constructor
vector::vector() : size{3}
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


int main()
{
    std::cout << std::endl <<  "Hello world" <<std::endl;
}