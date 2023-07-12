//g++ -std=c++17 -o task2 task2.cpp
# include <iostream>
# include <filesystem>
# include <fstream>
# include <regex>
# include <map>

namespace GO {

class Parser {
public:
    void test() {
        std::cout << "This is a test" << std::endl;
    }
    std::map <std::string, int> summary(std::string filename, std::string nmspace);
private:
    int x =0;
};


 std::map< std::string, int > Parser::summary(std::string filename, 
                                                std::string nmspace) {
    std::ifstream infile;
    std::string line = "";

    std::regex rxNmspace("^namespace: " + nmspace);
    std::regex rxObs("^is_obsolete: true");
    std::regex stop("^$");

    bool match = false;
    bool is_obs = false;

    int non_obs = 0;
    int     obs = 0;

    std::map< std::string, int > res = {};
    
    infile.open(filename);
    
    while (std::getline(infile, line)) {
        
        // check if current entry is in namespace
        if (std::regex_search(line, rxNmspace)) {
            match = true;
            is_obs = false;
        }

        // check if current entry is obsolete
        if (std::regex_search(line, rxObs)) {
            is_obs = true;
        }

        // if entry is finished and not obsolete, count that
        if (std::regex_search(line,stop)) {
            if (is_obs && match) {
                obs ++;
                match = false;
				is_obs = false;              
            } 
            if(match && !is_obs) {
                non_obs ++;
                match = false;
				is_obs = false;
            }
        } 
    }
    res["is_obsolete"] = obs;
    res["non_obsolete"] = non_obs;
	
	infile.close();
    return (res);
}



} //end f namespace


void usage (char * appname) {
	std::cout << "\n";
    std::cout << "This is a help message. Please use the app as indicated below." << std::endl;
    std::cout << appname << " filename taskname" <<std::endl;
    std::cout << "The available tasks are:  summary and children.\n" <<
    "If the chosen task is summay, then the user has to choose one of these three too:\n" <<
    "molecular_function, biological_process, cellular_componenet" << std::endl;
    std::cout << "\n";
    //std::cout << "The go-id should have the following format: e.g. GO:0000004 " <<std::endl;
}


int main(int argc, char **argv) {
    auto ps = GO::Parser();
    //ps.test();

    //using namespace std;
    namespace fs = std::filesystem;

    if (argc != 4) {
        usage(argv[0]);
        exit(1);

    } else {

        if (!std::filesystem::exists(argv[1])) {
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
            //std::cout << "this is summary cdm"  <<  std::endl;
            auto res = ps.summary(argv[1],argv[3]) ;
            for (std::pair<std::string, int> t:res) {
                std::cout << t.first << "\t" << t.second <<std::endl;
            }
        }

        if (cmd == "children") {
            //auto res = goutil.getEntry(argv[1],argv[3]) ;
            std::cout << "this is children cdm"<<  std::endl;
        }
    }
    return 0;
}
