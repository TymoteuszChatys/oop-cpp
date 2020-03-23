//Assessment8 - Class hierarchy to describe the properties of 2D and 3D shapes.
//Tymoteusz Chatys
//23/03/2020

//Abstract base class with pure virtual functions and a virtual destructor.
#include<string>
#include<cmath>
#include<vector>

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
public:
    circle() : ellipse() {}
    circle(const double &radius) : ellipse(radius,radius){}
    double area(){return pi()*parameters[0]*parameters[1];}
};

//-----------
//3D Shapes
//-----------

class cuboid : public three_dimensional
{
public:
    cuboid() : three_dimensional() {}
    cuboid(const double &length, const double &width, const double &height) : three_dimensional(length,width,height){}
    double volume(){return parameters[0]*parameters[1]*parameters[2];}
};
class cube: public cuboid
{
public:
    cube() : cuboid() {}
    cube(const double &length) : cuboid(length, length, length) {}
};

class ellipsoid : public three_dimensional
{
public:
    ellipsoid() : three_dimensional() {}
    ellipsoid(const double &length, const double &width, const double &height) : three_dimensional(length,width,height){}
    double volume(){return (4/3)*pi()*parameters[0]*parameters[1]*parameters[2];}
};

class sphere: public ellipsoid
{
public:
    sphere() : ellipsoid() {}
    sphere(const double &length) : ellipsoid(length, length, length) {}
};

class prism : public three_dimensional
{
private:
	double depth;
	two_dimensional *shape_of_prism;
public:
	prism() : depth(0), shape_of_prism(0) {}
	prism(double depth, two_dimensional *floor_shape) : three_dimensional(depth, floor_shape->parameters[0], floor_shape->parameters[1]) {}
	~prism(){};
	double volume(){return depth*(shape_of_prism->area()); }
};

int main()
{
    std::vector<shape *> shapes;
    shapes.push_back(new rectangle{4, 6});
    shapes.push_back(new square{2});
    shapes.push_back(new ellipse{1, 6});
    shapes.push_back(new circle{5});
    shapes.push_back(new cuboid{1, 2, 3});
    shapes.push_back(new cube{5});
    shapes.push_back(new ellipsoid{1, 2, 3});
    shapes.push_back(new sphere{5});
    shapes.push_back(new prism(12, ellipse{1, 6}));
}