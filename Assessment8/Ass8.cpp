//Assessment8 - Class hierarchy to describe the properties of 2D and 3D shapes.
//Tymoteusz Chatys
//23/03/2020

//Abstract base class with pure virtual functions and a virtual destructor.
class shape
{
public:
	virtual ~shape(){}
	virtual double area()=0;  //2D shapes
	virtual double volume()=0;//3D shapes
};

