// g++ -std=c++17 -o task1 task1.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <filesystem>


void usage (char * appname) {
    std::cout << "\n";
    std::cout << "This is a help message. Please use the app as indicated below." << std::endl;
    std::cout << appname << " filename taskname namespace(optional)" <<std::endl;
    std::cout << "The available tasks are:  considerTable and obsoleteStats" <<std::endl;
    std::cout << "optional 4th argument molecular_function or biological_process or cellular_component"   << std::endl;
              std::cout << "\n";
    //std::cout << "The go-id should have the following format: e.g. GO:0000004 " <<std::endl;
}


int main(int argc, char **argv) {

    namespace fs = std::filesystem;
    //auto ps = GO::Parser();
    if (argc < 3) {
        usage(argv[0]);
        exit(1);

    } else {

        if (!fs::exists(argv[1])) {
            std::cout << "Error: File " << argv[1] << " does not exists!\n";
            exit(1);
        }

        if (argc == 3) {

            std::string cmd = std::string(argv[2]) ;
            //std::string mol_fun = std::string(argv[3]) ;
            std::cout << "  is:  3" << cmd << std::endl;


            if (cmd != "considerTable" && cmd!= "obsoleteStats") {
                //std::string res = goutil.getName(argv[1],argv[3]) ;
                std::cout << "Taskname should be either  considerTable or obsoleteStats"  <<  std::endl;
                exit(0);
            }

            if (cmd == "considerTable" ) {
                //std::string res = goutil.getName(argv[1],argv[3]) ;
                std::cout << "this is considerTable cdm"  <<  std::endl;
            }

            if (cmd == "obsoleteStats") {
                //auto res = goutil.getEntry(argv[1],argv[3]) ;
                std::cout << "this is obsoleteStats cdm"<<  std::endl;
            }
        }

        if (argc == 4) {

            std::string cmd = std::string(argv[2]) ;
            std::string namesp = std::string(argv[3]) ;
            std::cout << "  is: 4 " << cmd << std::endl;


            if (cmd != "considerTable" && cmd!= "obsoleteStats") {
                //std::string res = goutil.getName(argv[1],argv[3]) ;
                std::cout << "Taskname should be either  considerTable or obsoleteStats"  <<  std::endl;
                exit(0);
            }

            if (namesp != "molecular_function" && namesp!= "biological_process" && namesp!="cellular_component") {
                //std::string res = goutil.getName(argv[1],argv[3]) ;
                std::cout << "choose either molecular_function, biological_process or cellular_component"  <<  std::endl;
                exit(0);
            }

            if (cmd == "considerTable" ) {
                //std::string res = goutil.getName(argv[1],argv[3]) ;
                std::cout << "this is considerTable cdm 4"  <<  std::endl;
            }

            if (cmd == "obsoleteStats") {
                //auto res = goutil.getEntry(argv[1],argv[3]) ;
                std::cout << "this is obsoleteStats cdm 4"<<  std::endl;
            }
        }

    }
    return(0);

}

