
// Assignment 1 - Tymoteusz Chatys - 28th January 2020

// A Program to calculate transition energy using simple Bohr formula

#include<iostream>
#include<iomanip>
#include<cmath> 
#include<tuple>
#include<limits>
#include<algorithm>

int repeat();
std::tuple <double,std::string> compute(int atomic_number,int qnumber_1,int qnumber_2,int eVoJ);
void checkInteger(int& integer_entered, int min, int max, std::string prompt, std::string fail, std::string rangefail);

int main()
// Main Function of the program
{
    int atomic_number,qnumber_1,qnumber_2,eVorJ;
    std::string eVorJ2;
    double dE;
    int cont{1};
    do{
      checkInteger(atomic_number,1, 200, "Enter atomic number: ", "Please enter a positive integer", "Atomic number must be a positive integer 1-200");
      checkInteger(qnumber_1,1, std::numeric_limits<int>::max(), "Enter first quantum number: ", "Please enter a positive integer", "First quantum number must be a positive integer 1,2,3...");
      checkInteger(qnumber_2,qnumber_1+1, std::numeric_limits<int>::max(), "Enter second quantum number: ", "Please enter a positive integer", "For a transition to occur the second quantum number must be a positive integer larger than the first quantum number...");
      checkInteger(eVorJ,1, 2, "Answer displayed in units of eV (1) or Joules (2)?  ", "Invalid input; please enter 1 for eV or 2 for J.", "Invalid input; please enter 1 for eV or 2 for J.");
      tie(dE,eVorJ2) = compute(atomic_number,qnumber_1,qnumber_2,eVorJ); std::cout<<"Your answer in " << eVorJ2 << " is " << dE << std::endl;
      cont = repeat();
     }while (cont==1);
  return 0;
}

int repeat()
// Function is used to ask the user whether the user would like to make another calculation
{
  int loop{2};
  std::string yes_or_no;
  do{
    std::cout << "Would you like to make another calculation? y/n ";
    std::cin >> yes_or_no;
    std::for_each(yes_or_no.begin(), yes_or_no.end(), [](char & c){
  	c = ::tolower(c);});
    if (yes_or_no == "y" || yes_or_no == "yes"){
      loop = 1;
    }
    else if (yes_or_no == "n" || yes_or_no == "no"){
      loop = 0;
    }
    else {
      std::cout << "Invalid input please try again " << std::endl;
    }
  }while (loop==2);
  return loop;
}

std::tuple <double,std::string> compute(int atomic_number,int qnumber_1,int qnumber_2,int eVorJ)
//This function computes the photon energy, in Joules or Electron volts whichever one was chosen by the user
//Calculation in electron volts
{
    double dE=13.6*pow(atomic_number,2)*((1/pow(qnumber_1,2))-(1/pow(qnumber_2,2))); 
    if (eVorJ == 1){
      std::string eVorJ2 = "eV";
      std::tuple <double, std::string> var = make_tuple(dE, eVorJ2);
	    return var;
    }
    //Convertion to Joules
    else if (eVorJ == 2){
      std::string eVorJ2 = "Joules";
      std::tuple <double, std::string> var = make_tuple(dE*(1.6*pow(10,-19)), eVorJ2);
      return var;
    }
}

void checkInteger(int& integer_entered, int min, int max, std::string prompt, std::string fail, std::string rangefail)
//Function to check whether the input is an integer. Also checks if the value lies within the limits specified.
//Adapted from stackoverflow user Jo-Jo
//checkInteger(variable, min, max, question, failure message when no integer, failure message when out of range )
{
    while(1) {
        std::string str;
        std::cout << prompt;
        std::cin >> str;
        std::istringstream ss(str);
        int value_entered;
        ss >> value_entered;
        if(!ss.eof()) {
            std::cout << fail << std::endl;
            ss.clear();
            continue;
        } else {
            ss.clear();
            integer_entered = value_entered;
            if(integer_entered > max || integer_entered < min) {
              std::cout << rangefail << std::endl;
              continue;
        }
        }
        break;
    }
}