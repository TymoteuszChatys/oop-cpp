// Tymoteusz Grzegorz Chatys
// Assignment 4
// Simple demonstration of a C++ class 
// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]
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
  galaxy() : name{" "},hubble_type{"Irr"},redshift{},total_mass{},stellar_mass_fraction{} {}
  // Parameterized Constructor
  galaxy(std::string galaxy_name, std::string galaxy_hubble_type, double galaxy_redshift, double galaxy_total_mass, double galaxy_stellar_mass_fraction)
        : name(galaxy_name), hubble_type(galaxy_hubble_type), redshift(galaxy_redshift), total_mass(galaxy_total_mass)
        ,stellar_mass_fraction(galaxy_stellar_mass_fraction) {}
  // Destructor
  ~ galaxy() {}
  // Return stellar mass (M_* = f_* x M_tot)
  double stellar_mass() {return (stellar_mass_fraction * total_mass);}
  // Change galaxy's Hubble type
  void change_type(std::string new_type) {hubble_type = new_type;}
  // Prototype for function to print out an object's data
  void print_data();
  // Add satellite galaxy
  void add_satellite(galaxy &satellite); 
};

void galaxy::print_data(){// Print out an object's data
  std::cout << "The hubble type is " << hubble_type << std::endl <<
  "The redshift is " << redshift << std::endl <<
  "The total mass is " << total_mass << std::endl <<
  "The stellar mass fraction is " << stellar_mass_fraction << std::endl <<
  "The stellar mass is " << stellar_mass() << std::endl;

  if (satellites.size() > 0){
    std::cout << "The Galaxy has " << satellites.size() << " satellites." << std::endl;
    int i{1};
    for (auto iterator = satellites.begin(); iterator != satellites.end(); iterator++) {
      std::cout << "  Satellite " << i++ << " properties: ";
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
  galaxy milky_way; 

  // Andromeda Details
  galaxy andromeda("Andromeda","Sa", 0.002430, 1e11, 0.34);
  galaxy M32("M32","E2", 0.004486, 5.4e9, 0.13);
  galaxy M110("M110","E5", 0.005875, 2e10, 0.11);
  andromeda.add_satellite(M32);
  andromeda.add_satellite(M110);
  andromeda.print_data();

  // Change Hubble type from Irr to S0

  galaxies.push_back(&milky_way);
  galaxies.push_back(&andromeda);
  for (auto iterator = galaxies.begin(); iterator != galaxies.end(); iterator++) {
    (*iterator)->print_data();
  return 0;
  }
}