//g++ -std=c++17 -o task1 task1.cpp


# include <iostream>
# include <filesystem>
# include <fstream>
# include <regex>
# include <map>




void usage (char * appname) {
	std::cout << "\n";
    std::cout << "This is a help message. Please use the app as indicated below." << std::endl;
    std::cout << appname << " filename taskname" <<std::endl;
    std::cout << "The available tasks are:  summary and children." <<std::endl;
    std::cout << "\n";
    //std::cout << "The go-id should have the following format: e.g. GO:0000004 " <<std::endl;
}


int main(int argc, char **argv) {

	 namespace fs = std::filesystem;
    if (argc != 3) {
        usage(argv[0]);
        exit(1);
        
    } else {
		
        if (!fs::exists(argv[1])) {
            std::cout << "Error: File " << argv[1] << " does not exists!\n";
            exit(1);
        }

        std::string cmd = std::string(argv[2]) ;
        //std::cout << "command  is: " << cmd << std::endl;
        
        if (cmd != "summary" && cmd!= "children") {
        //std::string res = goutil.getName(argv[1],argv[3]) ;
        std::cout << "Taskname should be either summary or children."  <<  std::endl;
        }
        
        if (cmd == "summary") {
            //std::string res = goutil.getName(argv[1],argv[3]) ;
            std::cout << "this is summary cdm"  <<  std::endl;
        }
        
        if (cmd == "children") {
            //auto res = goutil.getEntry(argv[1],argv[3]) ;
            std::cout << "this is children cdm"<<  std::endl;
        }

    }
    return 0;
}
