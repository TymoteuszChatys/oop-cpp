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
  std::fstream file;         // a file stream for reading or writing
  std::string units = "10^-19 Coulomb";
  int count{};
  double* data = NULL;

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
  std::tie(data,count) = file_processing(file_name);
  double data_mean = mean(data,count);
  double data_standard_deviation = standard_deviation(data,count,data_mean);
  double data_standard_error = data_standard_deviation/sqrt(count);
  std::cout << "Mean: " << data_mean << std::endl;
  std::cout << "Standard Deviation: " << data_standard_deviation << std::endl;
  std::cout << "Standard Error in the Mean: " << data_standard_error << std::endl;
  std::cout << "All in units of " << units << std::endl;
  delete[] data;
  std::cout << " " << std::endl << " " << std::endl << "Input anything to exit " << std::endl; 
  std::cin.ignore();  
  std::cin.get(); 
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
    if (a_line.length() > 0) {
      number_of_data_points = number_of_data_points +1;
      }
  }
  double* data = NULL;
  data = new double[number_of_data_points]; 
  int count{};
  file.close();
  
  file.open(file_name);
  while (!file.eof()) {
    std::string a_line;
    getline(file, a_line);
    std::istringstream iss(a_line);
    double value_entered;
    if (iss >> value_entered) {
      if(iss.eof()) {
        std::cout << "Error in text file" << std::endl;
      }
      else{
        data[count] = value_entered;
        count = count + 1;
      }
      } 
  }
  std::cout << file_name << " has " << count << " valid data points and " << (number_of_data_points-count) << " error/errors were detected." << std::endl;
  std::tuple <double*, int> values = std::make_tuple(data, count);
  return values;
}

double mean(double* data,int data_points){
  double mean{};
  double sum{};
  for(int i{}; i < data_points; i++){
    sum = sum + data[i];
  }
  mean = sum/data_points;
  return mean;
}

double standard_deviation(double* data, int data_points, double mean){
  double sum{};
  for(int i{}; i < data_points; i++){
    sum = pow(data[i] - mean,2) + sum;
  }
  double standard_deviation = sqrt(sum/(data_points-1));
  return standard_deviation;
}

