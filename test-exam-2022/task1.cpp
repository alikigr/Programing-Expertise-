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
    std::cout << appname << " gene-ontology-file  command  id(optional) \nSee example: \n";
    std::cout << "./task1 gene_ontology_edit.obo.2022-01-13 tabMetaCyc \n" ;
    std::cout << "The available commands are: tabMetaCyc, getMetaCyc." <<std::endl;
    std::cout << "In the case of getMetaCyc, you should also provide the id  RXN or PWY." <<std::endl;
    std::cout << "\n";
}

int main(int argc, char **argv) {

    namespace fs = std::filesystem;

    if (argc < 3 || argc >4) {
        usage(argv[0]);
        return(0);

    }
    if(argc == 3) {
        std::string file = argv[1];
        std::string taskname = argv[2];
        std::cout << "this is 3 arg" <<std::endl;

        if (!fs::exists(file)) {
            std::cout << "Error: File " << file << " does not exists!\n";
            exit(1);
        }
        if (taskname!="tabMetaCyc") {

            std::cout << "Taskname should be getMetaCyc or tabMetaCyc. See usage."<< std::endl;
            exit(0);
        }

        if (taskname == "tabMetaCyc") {

            std::cout << "this is tabmetacyc cmd" << std::endl;
        }


    }
    if (argc == 4) {

        std::string file = argv[1];
        std::string taskname = argv[2];
        std::string id =argv[3];
        //RXN or PWY
        std::regex ss(".*[R,P][X,W][N,Y]");

        std::cout << "this is 4" <<std::endl;

        if (!fs::exists(file)) {
            std::cout << "Error: File " << file << " does not exists!\n";
            exit(1);
        }

        if (taskname!="getMetaCyc") {
            std::cout << "Taskname should be getMetaCyc or tabMetaCyc. See usage."<< std::endl;
            exit(1);
        }
        if (!std::regex_match(id,ss))     {
            std::cout << "Given id is not valid. \n"<<"ID should be either RXN or PWY"<< std::endl;
            exit(1);
        }

        if (taskname == "getMetaCyc") {
            std::cout << "this is getmetacyc cmd" << std::endl;

        }
    }


    return 0;
}
