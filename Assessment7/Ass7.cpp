//16th March 2020
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
    if(i=0){
	    break_line = "---------------------------------------";
    }else if(i=1){
	    break_line = "-----------------ERROR-----------------";
    }
	return break_line;
}

class vector
{
    //friends of the class
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
    vector operator*(const vector& a_vector) const;
    //get and set functions
    size_t get_size() const
	{
		return size;
	}
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

// overload [] operator for accessing elements of the vector
double &vector::operator[](const size_t index) {
  if (index < 0){
    std::cout << dash(1) << std::endl << "Error: invalid input" << std::endl << "Index cannot be negative" << dash(1); exit(1);
  }else if(index > size-1){
    std::cout << dash(1) << std::endl << "Error: invalid input" << std::endl << "Index provided out of range of vector" << dash(1); exit(1);    
  }
  return vector_data[index];
}

//Outstream for vector
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
    out_stream << "vector is empty";
  }
  return out_stream;
}


int main()
{
    std::cout << std::endl <<  "Hello world" << std::endl;
}