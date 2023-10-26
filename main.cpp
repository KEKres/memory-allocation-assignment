
#include "assignedLL.h"
#include <vector>
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    std::vector<int> size;
    std::vector<std::string> function;
    
    //read in data from file

    std::ifstream in;
    in.open(argv[1]);
    
    if(!in){
        std::cout << "Error opening file" << std::endl;
        exit(1);
    }
    std::string line;


    while (std::getline(in, line)) {
        int a;
        std::string b;
        //split the string by colon
        std::string delimiter = ":";

        size_t pos = 0;
        if (line.find(delimiter) == std::string::npos) {

            b = "dealloc";
            size.push_back(0);
            function.push_back(b);
        }
        else{

            pos = line.find(delimiter);

            a = std::stoi(line.substr(pos+2));
            b = line.substr(0, pos);

            size.push_back(a);
            function.push_back(b);
        }
    }

    // program actually starts here
    AssignedLL* list = new AssignedLL();

    for (std::vector<int>::size_type i = 0; i < size.size(); i++) {
        if (function[i] == "alloc") {
            list->alloc(size[i]);
        }
        else if (function[i] == "dealloc") {
            list->dealloc();
        }
        else {
            std::cout << "Error: invalid function" << std::endl;
        }
    }
    list->printAllocatedList();
    delete list;
    return 0;

}
