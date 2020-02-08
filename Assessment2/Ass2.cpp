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

double mean(double* data,int data_points);
double standard_deviation(double* data, int data_points, double mean);

int main()
{
  // Read data from file, ignoring any additional bad data
  int i{1};
  std::string file_name;
  std::ifstream input_file;  // a file stream for reading only
  std::ofstream output_file; // a file stream for writing only
  std::fstream file;         // a file stream for reading or writing
  do{
    std::cout << "Enter the filename: ";
    std::cin >> file_name;
    file.open(file_name);
    if(! file.good ()) {
      std::cerr << "Error: file with the name " << file_name << " could not be opened" << std::endl;    }
    else{
      i = 0;
    }
  }while(i==1);

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
  std::string units = "x10^-19 Coulomb";
  double data_mean = mean(data,count);
  std::cout << "Mean: " << data_mean << units << std::endl;
  double data_standard_deviation = standard_deviation(data,count,data_mean);
  std::cout << "Standard Deviation: " << data_standard_deviation << units << std::endl;
  double data_standard_error = data_standard_deviation/sqrt(count);
  std::cout << "Standard Error in the Mean: " << data_standard_error << units << std::endl;

  delete[] data;
  file.close();
  return 0;
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
