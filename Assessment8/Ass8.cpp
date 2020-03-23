//Assessment8 - Class hierarchy to describe the properties of 2D and 3D shapes.
//Tymoteusz Chatys
//23/03/2020

//Abstract base class with pure virtual functions and a virtual destructor.
#include<string>
#include<cmath>

constexpr double pi() { return std::atan(1)*4; };

//Structure of classes below
//shape classes
//-->2D
//   -->Rectangle
//      -->Square (specialisation)
//   -->Ellipse
//      -->Circle (specialisation)
//-->3D

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
    two_dimensional() : shape(2){};
    two_dimensional(const double parameter_one, const double parameter_two);
    virtual double area();
};

two_dimensional::two_dimensional(const double parameter_one, const double parameter_two): shape(2){
    parameters[0] = parameter_one;
    parameters[1] = parameter_two;
};

class three_dimensional : public shape
{
public:
    three_dimensional(): shape(3){};
    three_dimensional(const double parameter_one, const double parameter_two, const double parameter_three);
    virtual double volume();
};

three_dimensional::three_dimensional(const double parameter_one, const double parameter_two, const double parameter_three): shape(3){
    parameters[0] = parameter_one;
    parameters[1] = parameter_two;
    parameters[2] = parameter_three;
};
//-----------
//2D Shapes
//-----------
class rectangle : public two_dimensional
{
public:
    rectangle() : two_dimensional() {}
    rectangle(const double &length, const double &width) : two_dimensional(length,width){}
    double area(){return parameters[0]*parameters[1];}
};
class square: public rectangle
{
public:
    square() : rectangle() {}
    square(const double &length) : rectangle(length, length) {}
};

class ellipse: public two_dimensional
{
public:
    ellipse() : two_dimensional() {}
    ellipse(const double &semi_major, const double &semi_minor) : two_dimensional(semi_major,semi_minor){}
    double area(){return pi()*parameters[0]*parameters[1];}
};

class circle: public ellipse
{
    circle() : ellipse() {}
    circle(const double &radius) : ellipse(radius,radius){}
    double area(){return pi()*parameters[0]*parameters[1];}
};

//-----------
//3D Shapes
//-----------

int main()
{

}