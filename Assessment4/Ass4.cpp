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
  // Constructors
  
  // Destructor

  // Return stellar mass (M_* = f_* x M_tot)
  double stellar_mass() { }
  // Change galaxy's Hubble type
  void change_type(std::string new_type) { }
  // Prototype for function to print out an object's data
  void print_data();
  // Add satellite galaxy

};
// Print out an object's data

// End of class and associated member functions

// Main program
int main()
{

  // Example using default constructor
  galaxy g1; 

  // Example using parameterised constructor

  // print out data

  // Get and print out stellar mass

  // Change Hubble type from Irr to S0
  
  // Add satellite galaxies

  return 0;
}