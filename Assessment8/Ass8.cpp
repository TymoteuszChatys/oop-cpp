//Assessment8 - Class hierarchy to describe the properties of 2D and 3D shapes.
//Tymoteusz Chatys
//27/03/2020

//Abstract base class with pure virtual functions and a virtual destructor.
#include<string>
#include<cmath>
#include<vector>
#include<iostream>

constexpr double pi() { return std::atan(1)*4; };

//custom break lines for better output visualisation 
std::string dash()
{
    std::string break_line;
    break_line = "---------------------------------------";
	return break_line;
}

class shape
{
    friend class prism;
protected:
    int dimensions; 
    double *parameters; 
public:
    shape(const int &dimension) {parameters = new double[dimensions];}
    virtual ~shape() {delete[] parameters;};    
    virtual double area()=0;     
    virtual double volume()=0;   
    virtual std::string name()=0;
};

class two_dimensional : public shape
{
public:
    two_dimensional() : shape(2){};
    two_dimensional(const double parameter_one, const double parameter_two);
    double volume(){return 0;}
};

two_dimensional::two_dimensional(const double parameter_one, const double parameter_two): shape(2)
{
    parameters[0] = parameter_one;
    parameters[1] = parameter_two;
};

class three_dimensional : public shape
{
public:
    three_dimensional(): shape(3){};
    three_dimensional(const double parameter_one, const double parameter_two, const double parameter_three);
};

three_dimensional::three_dimensional(const double parameter_one, const double parameter_two, const double parameter_three): shape(3)
{
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
    ~rectangle(){}
    double area(){return parameters[0]*parameters[1];}
    std::string name(){return "rectangle";}
};
class square: public rectangle
{
public:
    square() : rectangle() {}
    square(const double &length) : rectangle(length, length) {}
    ~square(){}
    std::string name(){return "square";}
};

class ellipse: public two_dimensional
{
public:
    ellipse() : two_dimensional() {}
    ellipse(const double &semi_major, const double &semi_minor) : two_dimensional(semi_major,semi_minor){}
    ~ellipse(){}
    double area(){return pi()*parameters[0]*parameters[1];}
    std::string name(){return "ellipse";}
};

class circle: public ellipse
{
public:
    circle() : ellipse() {}
    circle(const double &radius) : ellipse(radius,radius){}
    ~circle(){}
    double area(){return pi()*parameters[0]*parameters[1];}
    std::string name(){return "circle";}
};

//-----------
//3D Shapes
//-----------

class cuboid : public three_dimensional
{
public:
    cuboid() : three_dimensional() {}
    cuboid(const double &length, const double &width, const double &height) : three_dimensional(length,width,height){}
    ~cuboid(){}
    double volume(){return parameters[0]*parameters[1]*parameters[2];}
    double area(){return 2*parameters[0]*parameters[1]+2*parameters[1]*parameters[2]+2*parameters[0]*parameters[2];}
    std::string name(){return "cuboid";}
};
class cube: public cuboid
{
public:
    cube() : cuboid() {}
    cube(const double &length) : cuboid(length, length, length) {}
    ~cube(){}
    std::string name(){return "cube";}
};

class ellipsoid : public three_dimensional
{
public:
    ellipsoid() : three_dimensional() {}
    ellipsoid(const double &length, const double &width, const double &height) : three_dimensional(length,width,height){}
    ~ellipsoid(){}
    double volume(){return (4/3)*pi()*parameters[0]*parameters[1]*parameters[2];}
    double area();
    std::string name(){return "ellipsoid";}
};

double ellipsoid::area()
/* estimate based on
https://web.archive.org/web/20110930084035/http://www.numericana.com/answer/ellipsoid.htm
power p is approximated to 1.6075 with 4p*[(a^pb^p+a^pc^p+b^pc^p)/3]^1/p error within 1%.
*/
{
    return 4*pi()*pow((
            pow(parameters[0]*parameters[1],1.6075)
             + pow(parameters[0]*parameters[2],1.6075) 
             + pow(parameters[1] * parameters[2], 1.6075) )/3,1/1.6075);
}
class sphere: public ellipsoid
{
public:
    sphere() : ellipsoid() {}
    sphere(const double &length) : ellipsoid(length, length, length) {}
    ~sphere(){}
    std::string name(){return "sphere";}
};

class prism : public three_dimensional
{
private:
    double depth;
	double face_area;
    std::string face_name;
	shape *shape_of_face;
public:
	prism(const double &depth, shape *shape_of_face) : three_dimensional(depth, shape_of_face->parameters[0], shape_of_face->parameters[1]) {face_area = shape_of_face->area(); face_name = shape_of_face->name();}
	~prism(){}
    double volume(){return parameters[0]*face_area;}
    double area(){return 0;}
    std::string name(){return face_name + " prism";}
};

int main()
{
    std::vector<shape *> shapes;
    shapes.push_back(new rectangle{4, 6});
    shapes.push_back(new square{5});
    shapes.push_back(new ellipse{1, 6});
    shapes.push_back(new circle{5});
    shapes.push_back(new cuboid{1, 2, 3});
    shapes.push_back(new cube{5});
    shapes.push_back(new ellipsoid{1, 2, 3});
    shapes.push_back(new sphere{5});
    shapes.push_back(new prism{2, new rectangle{2,3}});

    //output  iterator
    for (auto iterator = shapes.begin(); iterator!= shapes.end(); iterator++) {
        std::cout << dash() << std::endl << (*iterator)->name() 
        << std::endl << "area :" << (*iterator)->area() << "   " 
        << "volume :" << (*iterator)->volume() << std::endl << dash() << std::endl;
    }

    //clear iterator
    for (auto iterator = shapes.begin(); iterator < shapes.end();++iterator) {
        delete *iterator;
    }
	shapes.clear();
}