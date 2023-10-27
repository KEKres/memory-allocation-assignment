
#include "assignedLL.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

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

    // start recording duration
    auto start = std::chrono::high_resolution_clock::now();

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
    list->printLists();
    std::cout << "Total Allocation Requests: " << list->getAllocationRequests() << std::endl;
    std::cout << "Total Deallocation Requests: " << list->getDeallocationRequests() << std::endl;

    delete list;

    auto stop = std::chrono::high_resolution_clock::now();

    // Calculates time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Print the total runtime in microseconds
    std::cout << "Total runtime: " << duration.count() << " microseconds" << std::endl;


    return 0;

}
