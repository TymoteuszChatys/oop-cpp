
// Simple code to store courses using vectors and strings

 
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <tuple>

std::string options();
std::tuple <std::vector<std::string>,std::vector<std::string>,std::string> file();
std::tuple <double*, int> file_processing(std::string file_name);
int manual();
bool checkforint();

//Main function of the program
int main(void)
{
    std::vector<std::string> course_code;
    std::vector<std::string> course_name;
    std::string choice;
    std::string end;

    choice = options(); //Asks user how he wants to use the program
    if(choice == "file"){
        std::tie(course_code, course_name, end) = file();
        if(end == "end"){
            return 0;
        }
    }
    else if(choice == "manual"){
        //course_code, course_name = manual();
    }    
    //    } while(not_finished);

    // Print out full list of courses
    std::cout << "List of courses:"<<std::endl;
    std::cout << course_name[3] << std::endl;

    // Extract courses belonging to a certain year
    //string yearChoice;
    //cout<<"Please enter year: ";
    //cin>>yearChoice;
    //cout>>"Sort by code or name: ";
    //cin>>sortOption;

    return 0;
}

std::string options(){
    std::string option;
    // Gather list of courses and their codes from user,
    std::cout << "How would you like to input courses? " << std::endl;
    std::cout << "1 - from file " << std::endl << "2 - enter manually " << std::endl;
    std::cin >> option;
    while (!(option == "1" || option == "2")){
        std::cout << "Invalid input. Please enter one of the options. To view the options again enter 0 " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> option;
        if(option == "0"){
            std::cout << "How would you like to input courses? " << std::endl;
            std::cout << "1 - from file " << std::endl << "2 - enter manually " << std::endl; 
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> option;
        }
    }
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
    std::vector<std::string> course_code;
    std::vector<std::string> course_name;
    std::string file_name;
    std::string end = "continue";

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
    else{
        int i{};
        while (!file.eof()) {
            std::string a_line;
            getline(file, a_line);
            std::istringstream iss(a_line);
            std::vector<std::string> line_element{
                std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>{}
                };

            std::string total_second_line_element;
            for(int n{1}; n < (line_element.size()) ;n++){
                total_second_line_element = total_second_line_element + " " + line_element[n];

            }
            course_code.push_back(line_element[0]);
            course_name.push_back(total_second_line_element);
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

bool checkforint() {
	//Checks that the user entered a integer
	if (std::cin.fail()) {
		std::cout << "An integer must be entered" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return true;
	}

}
