
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string instring;
    std::ifstream infile("./test.txt");

    if(!infile) {
        std::cout << "Unable to open file!\n";
    } else {
        while(std::getline(infile, instring)) {
            std::cout << instring << std::endl;
        }
    }


    infile.close();
    std::cin.get();
    return 0;
}

