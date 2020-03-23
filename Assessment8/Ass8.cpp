//Assessment8 - Class hierarchy to describe the properties of 2D and 3D shapes.
//Tymoteusz Chatys
//23/03/2020

//Abstract base class with pure virtual functions and a virtual destructor.
class shape
{
protected:
    int dimensions; 
    double *parameters; 
public:
    shape(const int &dimension) {parameters = new double[dimensions];}
    virtual ~shape() {delete[] parameters;};          
};

class two_dimensional : public shape
{
public:
    virtual double area();
    two_dimensional() : shape(2){};
    two_dimensional(const double parameter_one, const double parameter_two);
};

class three_dimensional : public shape
{
public:
    virtual double volume();
    three_dimensional(): shape(3){};
    three_dimensional(const double parameter_one, const double parameter_two, const double parameter_three);
};

class rectangle : public two_dimensional
{

};

int main()
{

}