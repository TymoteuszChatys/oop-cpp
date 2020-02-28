#include<iostream>
#include<string>
#include<vector>
#include<cmath>

class galaxy
{
private:
  std::string name; //name of the galaxy/satellite
  std::string hubble_type; //E0 to E7, S0, Sa, Sb, Sc, SBa, SBb, SBc and Irr
  double redshift; //z in the range [0,10]
  double total_mass; //Mtot in the range [10^7,10^12]M⊙
  double stellar_mass_fraction; //f∗=M∗/Mtot in the range [0,0.05]
  std::vector<galaxy *> satellites; //Galaxies contain satellites. Vector for those satellites.

public:
  // Default Constructor
  galaxy() : name{"NaN"},hubble_type{"Irr"},redshift{},total_mass{},stellar_mass_fraction{} {}
  // Parameterized Constructor
  galaxy(std::string galaxy_name, std::string galaxy_hubble_type, double galaxy_redshift, double galaxy_total_mass, double galaxy_stellar_mass_fraction)
        : name(galaxy_name), hubble_type(galaxy_hubble_type), redshift(galaxy_redshift), total_mass(galaxy_total_mass)
        ,stellar_mass_fraction(galaxy_stellar_mass_fraction) {}
  // Destructor
  ~ galaxy() {}
  // Return stellar mass (M_* = f_* x M_tot)
  double stellar_mass() {return (stellar_mass_fraction * total_mass);}
  // Functions to change parameters after initialization
  void change_name(std::string new_name) {name = new_name;};
  void change_type(std::string new_type) {hubble_type = new_type;}
  void change_redshift(double new_redshift) {redshift = new_redshift;}
  void change_total_mass(double new_total_mass) {total_mass = new_total_mass;}
  void change_stellar_mass_fraction(double new_stellar_mass_fraction) {stellar_mass_fraction = new_stellar_mass_fraction;}
  // Prototype for function to print out an object's data
  void print_data();
  // Add satellite galaxy
  void add_satellite(galaxy &satellite); 
};

void galaxy::print_data(){// Print out an object's data
  std::cout << "Name: " << name << std::endl;
  std::cout << "The hubble type is " << hubble_type << std::endl <<
  "The redshift is " << redshift << std::endl <<
  "The total mass is " << total_mass << std::endl <<
  "The stellar mass fraction is " << stellar_mass_fraction << std::endl <<
  "The stellar mass is " << stellar_mass() << std::endl;

  if (satellites.size() > 0){//Prints out the satellites if present
    std::cout << "---" << name << " has " << satellites.size() << " satellites---" << std::endl;
    int satellite_number{1};
    for (auto iterator = satellites.begin(); iterator != satellites.end(); iterator++) {
      std::cout << "Satellite " << satellite_number++ << " properties: " << std::endl;
      (*iterator)->print_data();
    } 
  }     
}

void galaxy::add_satellite(galaxy &satellite){// Adds the satellite to the respective satellites vector
  satellites.push_back(&satellite);
}

// Main program
int main()
{
  // Vector holding the details of all galaxies
  std::vector<galaxy *> galaxies;
  // Example using default constructor
  galaxy ngc_5866; 
  std::cout << "-----------------------------" << std::endl
            << "Default constructor values: " << std::endl;
  ngc_5866.print_data();
  // Example using Parameterized constructor
  std::cout << "-----------------------------" << std::endl
            << "Parameterized constructor values: " << std::endl
            << "(Including the change of type): " << std::endl;
  // Change Hubble type from Irr to S0
  ngc_5866.change_type("S0");
  ngc_5866.change_name("Spindle Galaxy");
  ngc_5866.change_redshift(0.002);
  ngc_5866.change_total_mass(1e12);
  ngc_5866.change_stellar_mass_fraction(0.03);
  ngc_5866.print_data();
  std::cout << "-----------------------------" << std::endl;

  // galaxies
  galaxy ngc_5236("Southern Pinwheel Galaxy","Sa", 0.002430, 1.3e11, 0.0343);
  galaxy ngc_4826("Black Eye Galaxy","Sb",0.001361, 2.3e11,0.0412);
  // galaxies with satellites;
  galaxy milky_way("Milky Way Galaxy","Sb",0,0.5e12,0.032);
    galaxy large_magellanic_cloud("Large Magellanic Cloud","Sb",0,1e11,0.02);
    galaxy sagittarius_dwarf_spheroidal("Sagittarius Dwarf Spheroidal Galaxy","E0",0,7e9,0.04);
    milky_way.add_satellite(large_magellanic_cloud);
    milky_way.add_satellite(sagittarius_dwarf_spheroidal);
  // push to vector of galaxies ready for print out
  galaxies.push_back(&ngc_5236);
  galaxies.push_back(&ngc_4826);
  galaxies.push_back(&milky_way);
  galaxies.push_back(&ngc_5866);

  std::cout << "All galaxies and satellites print out: " << std::endl;
  int galaxy_number{1}; // counter 
  for (auto iterator = galaxies.begin(); iterator != galaxies.end(); iterator++) {
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Galaxy " << galaxy_number << " ";
    (*iterator)->print_data();
    galaxy_number++;
  }
  std::cout << "-----------------------------" << std::endl;
  std::cout << "Input anything to exit " << std::endl; 
  std::cin.ignore();  
  std::cin.get();
}