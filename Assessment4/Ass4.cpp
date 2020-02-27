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
  std::string hubble_type; //E0 to E7, S0, Sa, Sb, Sc, SBa, SBb, SBc and Irr
  double redshift; //z in the range [0,10]
  double total_mass; //Mtot in the range [10^7,10^12]M⊙
  double stellar_mass_fraction; //f∗=M∗/Mtot in the range [0,0.05]
  std::vector<galaxy *> satellites; //Galaxies contain satellites. Vector for those satellites.

public:
  // Default Constructor
  galaxy() : hubble_type{"Irr"},redshift{},total_mass{},stellar_mass_fraction{} {}
  // Parameterized Constructor
  galaxy(std::string galaxy_hubble_type, double galaxy_redshift, double galaxy_total_mass, double galaxy_stellar_mass_fraction)
        : hubble_type(galaxy_hubble_type), redshift(galaxy_redshift), total_mass(galaxy_total_mass)
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

void galaxy::print_data(){
  std::cout << "The hubble type is " << hubble_type << std::endl <<
  "The redshift is " << redshift << std::endl <<
  "The total mass is " << total_mass << std::endl <<
  "The stellar mass fraction is " << stellar_mass_fraction << std::endl <<
  "The stellar mass is " << stellar_mass() << std::endl;
}

void galaxy::add_satellite(galaxy &satellite){


}
// Print out an object's data

// End of class and associated member functions

// Main program
int main()
{

  // Example using default constructor
  galaxy milky_way; 
  galaxy andromeda("Sa", 0.002430, 1e11, 0.34);

  // Example using parameterised constructor

  // print out data
  andromeda.print_data();
  // Get and print out stellar mass

  // Change Hubble type from Irr to S0
  
  // Add satellite galaxies

  return 0;
}