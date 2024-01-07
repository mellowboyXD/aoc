#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std::chrono;

int main(int argc, char** argv) {
    std::string instring;
    std::ifstream infile;
    int count = 0;
    int floor = 0;
    bool basementReached = false;
    int basementChar;

    if(argc > 1) {
        std::string file = argv[1];
        infile.open(file);
    } else {
        infile.open("test.txt");
    }


    if(!infile) {
        std::cout << "Unable to open file!\n";
    } else {
        auto start = high_resolution_clock::now();
        while(std::getline(infile, instring)) {
            for(long unsigned int i = 0; i < instring.length(); i++) {
                std::cout << ++count << "\t";
                switch (instring.at(i)) {
                    case '(':
                        std::cout << "Inc\t floor: " << ++floor << "\n";
                        
                        break;
                    case ')':
                        std::cout << "Dec\t floor: " << --floor << "\n";
                        break;
                    default: continue;
                }
                if(floor == -1 && !basementReached) {
                    std::cout << "Basement Reached on character: " << count << "\n";
                    basementChar = count;
                    basementReached = true;
                    
                    std::cout << "Press Enter to continue!";
                    std::cin.get();
                }
            }
        }
        std::cout << "Final floor: " << floor << "\t Position of first basement enter: " << basementChar << std::endl;
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        auto duration_micro = duration_cast<microseconds>(stop - start);
        std::cout << "Time: " << duration.count() << " ms\t" << duration_micro.count() << " microseconds" << std::endl;
    }


    infile.close();

    std::cout << "\nPress Enter to Exit!";
    std::cin.get();
    return 0;
}

