// Assignment 3 - Tymoteusz Chatys - 19th February 2020
// A Program to manipulate and sort data
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <tuple>
#include <numeric>

std::string options();
std::tuple <std::vector<std::string>,std::vector<std::string>,std::string> file();
std::tuple <double*, int> file_processing(std::string file_name);
int manual();
bool is_number(const std::string& s);
bool sortbysec(const std::pair<std::string,std::string> &a, const std::pair<std::string,std::string> &b);
void checkInteger(int& integer_entered, int min, int max, std::string prompt, std::string fail, std::string rangefail);

//Main function of the program
int main(void)
{
    std::vector<std::string> course_code;
    std::vector<std::string> course_name;
    std::string choice;
    std::string end;

    choice = options(); //Asks user how he wants to use the program
    if(choice == "file"){
        //Looks at the file and inputs the two forms of data into vectors.
        std::tie(course_code, course_name, end) = file();
        if(end == "end"){
            return 0;
        }
    }
    else if(choice == "manual"){
        //course_code, course_name = manual();
    }    
    
    std::cout << "What courses would you like to display?" << std::endl
    << "(1) all courses as entered" << std::endl
    << "(2) by title" << std::endl
    << "(3) by course code" << std::endl
    << "(4) or would you like to see the courses for a particular year" << std::endl;
    
    int option_picked;
    checkInteger(option_picked,1, 4, "Answer value 1-4 : ", "Invalid input; please make sure you are inputting an integer", "Invalid input; integer must be between 1 and 4");
    std::vector<std::pair<std::string,std::string>> pair;
    if(option_picked == 1 || option_picked == 2 || option_picked == 3){ 
        //Pairs the two vectors (course code and corse name) together to allow manipulation later.  
        for (int i{}; i<course_code.size(); i++){
            pair.push_back(make_pair(course_code[i],course_name[i]));
        }
        if(option_picked == 2){//Sort by course name
            sort(pair.begin(), pair.end(), sortbysec); 
        }
        else if(option_picked == 3){//Sort by course code
            sort(pair.begin(), pair.end()); 
        }
    }
    else if(option_picked == 4){//Courses for a particular year
        int year_picked;
        checkInteger(year_picked,1, 4, "Which year would you like to view? (1-4): ", "Invalid input; please make sure you are inputting an integer", "Invalid input; integer must be between 1 and 4");
        for (int i=0; i<course_code.size(); i++) {
            if (course_code[i][0] == year_picked){
                pair.push_back(make_pair(course_code[i],course_name[i]));
            }
        }
    }

    //Creates a vector of output strings in the correct format ready for output.
    std::vector<std::string> output_string;
    std::string  course_string;
    for (int i=0; i<course_code.size(); i++) { 
        course_string = "PHYS" + pair[i].first + pair[i].second;
        output_string.push_back(course_string);
    } 

    //Outputs the courses needed using iterators.
    for (auto iterator = output_string.begin(); iterator != output_string.end(); iterator++) {
        std::cout << *iterator << std::endl;
    }
}

std::string options(){
    //Function is used to determine the way the user would like to use the program
    std::string option;
    std::cout << "How would you like to input courses? " << std::endl;
    std::cout << "1 - from file " << std::endl << "2 - enter manually " << std::endl;
    std::cin >> option;
    while (!(option == "1" || option == "2")){
        //If user inputs are out of our range of options
        std::cout << "Invalid input. Please enter one of the options. To view the options again enter 0 " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> option;
        if(option == "0"){
            //To remind the user of the options available
            std::cout << "How would you like to input courses? " << std::endl;
            std::cout << "1 - from file " << std::endl << "2 - enter manually " << std::endl; 
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> option;
        }
    } 
    //Now sets to the correct string that can be read and returned to the main function of the program
    if(option == "1"){
        option = "file";
    }
    else if(option == "2"){
        option = "manual";
    }
    return option;
}

std::tuple <std::vector<std::string>,std::vector<std::string>,std::string> file()
{
    //Defining variables and vectors
    std::vector<std::string> course_code;
    std::vector<std::string> course_name;
    std::string file_name;
    std::string end = "continue";

    //This checks for the file and whether it can be accessed by the program
    std::fstream file;       
    std::cout << "Enter the filename: ";
    std::cin >> file_name;
    file.open(file_name);
    if(! file.good ()) {
        std::cerr << "Error: file with the name " << file_name << " could not be opened" << std::endl;
        std::cout << "Input anything to exit " << std::endl; 
        end = "end";
        std::cin.ignore();  
        std::cin.get();
        }
    //If it can be accessed input the data from the file to vectors
    else{
        int i{};
        while (!file.eof()) {
            std::string a_line;
            getline(file, a_line);
            std::istringstream iss(a_line);
            //Seperates the line into many strings
            std::vector<std::string> line_element{
                std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>{}};
            std::string total_second_line_element;
            //Takes every seperate string after the first string and combines them to form the course name
            for(int n{1}; n < (line_element.size()) ;n++){
                total_second_line_element = total_second_line_element + " " + line_element[n];
            }
            //Checks to see if the course code is an integer, if it is, the course is entered
            if(is_number(line_element[0]) == true){
                course_code.push_back(line_element[0]);
                course_name.push_back(total_second_line_element);
                i++;
            }
            //Otherwise an error is shown.
            else{
                std::cout << "Error: Course number " << i+1 << " in " << file_name << " has a non-integer course code. " << total_second_line_element << " has been omitted. " << std::endl;
            }
        } 
    }
    file.close();
    std::tuple <std::vector<std::string>,std::vector<std::string>,std::string> values = std::make_tuple(course_code, course_name, end); //Make tuple and then return
    return values;
}

int manual(){
    bool not_finished(true);
    //o{
    //    std::cout << "Please enter a course name (or x to finish): " << std::endl;
    //    }while{}
    return 0;
}



bool is_number(const std::string& s)
//Function to check wether a string is a number
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
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

// Function to sort a vector of pairs by the second vector
bool sortbysec(const std::pair<std::string,std::string> &a, const std::pair<std::string,std::string> &b) 
{ 
    return (a.second < b.second); 
} 