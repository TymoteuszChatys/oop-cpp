// Assignment 2 - Tymoteusz Chatys
// Millikan's experiment
// 8th February 2020
// Program to compute mean, standard deviation and standard error on the mean.

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<sstream>
#include<string>
#include<tuple>

double mean(double* data,int data_points);
double standard_deviation(double* data, int data_points, double mean);
std::tuple <double*, int> file_processing(std::string file_name);

int main()
// Main part of the program. Calls all the needed functions.
{
  std::string file_name;
  std::fstream file;       
  std::string units = "10^-19 Coulomb";
  int count{};
  double* data = NULL;

  //Checks for filename 
  std::cout << "Enter the filename: ";
  std::cin >> file_name;
  file.open(file_name);
  if(! file.good ()) {
    std::cerr << "Error: file with the name " << file_name << " could not be opened" << std::endl;
    std::cout << "Input anything to exit " << std::endl; 
    std::cin.ignore();  
    std::cin.get(); 
    return 0;
  }
  file.close();

  //Next lines call the required functions and obtains results
  std::tie(data,count) = file_processing(file_name);
  double data_mean = mean(data,count);
  double data_standard_deviation = standard_deviation(data,count,data_mean);
  double data_standard_error = data_standard_deviation/sqrt(count);

  //Outputs the data to the user
  std::cout << std::fixed << std::setprecision(5) << "Mean: " << data_mean << std::endl;
  std::cout << std::fixed << std::setprecision(5) << "Standard Deviation: " << data_standard_deviation << std::endl;
  std::cout << std::fixed << std::setprecision(5) << "Standard Error in the Mean: " << data_standard_error << std::endl;
  std::cout << "All in units of " << units << std::endl;
  std::cout << " " << std::endl << " " << std::endl << "Input anything to exit " << std::endl; 
  std::cin.ignore();  
  std::cin.get(); 

  //Deletes the allocated memory and exits the program
  delete[] data;
  return 0;
}

std::tuple <double*, int> file_processing(std::string file_name)
//This function reads the file, finds the amount of data points in the file 
//Stores the data points into an array and returns the array and number of data points.
{  
  std::fstream file; 
  file.open(file_name);
  int number_of_data_points{};
  while (!file.eof()) {
    std::string a_line;
    getline(file, a_line);
    if (a_line.length() > 0) { //If a line has some characters, count it as a data point
      number_of_data_points = number_of_data_points +1;
      }
  }
  double* data = NULL;
  data = new double[number_of_data_points];  //Make an array given the counted number of data points
  int count{};
  
  file.close();         //Program has reached the end of the file therefore we want to read from
  file.open(file_name); //the beginning again. Therefore we can close it and open it again

  while (!file.eof()) {
    std::string a_line;
    getline(file, a_line);
    std::istringstream iss(a_line); 
    double value_entered;
    if (iss >> value_entered) { //If string can be converted into a double (omitting all whitespace)
      data[count] = value_entered; 
      count = count + 1;  //Count number of valid data (those that converted to double)
      } 
  }
  std::cout << file_name << " has " << count << " valid data points and " << (number_of_data_points-count) << " error/errors were detected." << std::endl;
  std::tuple <double*, int> values = std::make_tuple(data, count); //Make tuple and then return
  return values;
}

double mean(double* data,int data_points)
{
  //calculates and returns the mean of given array if number of data points are known
  double mean{};
  double sum{};
  for(int i{}; i < data_points; i++){
    sum = sum + data[i];
  }
  mean = sum/data_points;
  return mean;
}

double standard_deviation(double* data, int data_points, double mean)
{
  //calculates and returns the standard deviation of given array if number of data
  //points and the mean is known
  double sum{};
  for(int i{}; i < data_points; i++){
    sum = pow(data[i] - mean,2) + sum;
  }
  double standard_deviation = sqrt(sum/(data_points-1));
  return standard_deviation;
}

