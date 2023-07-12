//g++ -std=c++17 -o task4 task4.cpp
# include <iostream>
# include <filesystem>
# include <fstream>
# include <regex>
# include <map>




void usage (char * appname) {
    std::cout << "This is a help message. Please use the app as indicated below." << std::endl;
    std::cout << appname << " gene-ontology-file  taskname" <<std::endl;
    std::cout << "The available commands are:  searchEC, getInfo " <<std::endl;
    //std::cout << "The go-id should have the following format: e.g. GO:0000004 " <<std::endl;
}


int main(int argc, char **argv) {

	 namespace fs = std::filesystem;
    if (argc != 3) {
        usage(argv[0]);
        
    } else {
		
        if (!fs::exists(argv[1])) {
            std::cout << "Error: File " << argv[1] << " does not exists!\n";
            exit(1);
        }

        std::string cmd = std::string(argv[2]) ;
        
        if (cmd != "searchEC" && cmd != "getInfo" )  {
			std::cout << "See usage" <<std::endl;
			exit(1);
			}
			
        std::cout << " command  is: " << cmd << std::endl;
        if (cmd == "searchEC") {
            //std::string res = goutil.getName(argv[1],argv[3]) ;
            std::cout << "this is search ec cdm"  <<  std::endl;
        }
        if (cmd == "getInfo") {
            //auto res = goutil.getEntry(argv[1],argv[3]) ;
            std::cout << "this is getinfo cdm"<<  std::endl;
        }

    }
    return 0;
}
