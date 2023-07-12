// g++ -std=c++17 -o task2 task2.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <filesystem>

class Parser {
public:
    void test() {
        std::cout << "This is a test" << std::endl;
    }
std::vector<std::vector<std::string> >ConsiderTable(std::string filename) ;
std::vector<std::vector<std::string> >ConsiderTable_Namespace(std::string filename, std::string namesp) ;
private:
    int x =0;
};

std::vector<std::vector<std::string> > Parser::ConsiderTable(std::string filename) {

    //std::cout << " this is the considertable function " << std::endl;
    std::ifstream infile;
    std::string line = "";

    std::regex rgoid("^id: ");
    std::regex robs("^is_obsolete: ");
    std::regex rcon("^consider: ");
    std::regex stop("^$");

    bool match= false;
    bool is_obs = false;
    bool con = false;


    std::string goid = "";
    std::string considers = "";

    std::vector<std::vector<std::string> > res;
    std::vector<std::string> v1;
    infile.open(filename);

    while (std::getline(infile, line)) {

        // check if current entry is in namespace


        if (std::regex_search(line, rgoid)) {
            match = true;
            goid = std::regex_replace(line,std::regex("^id: "),"");
            // std::cout << goid <<std::endl;
            v1.push_back(goid);
            v1.clear();
            //is_obs = false;
        }

        // check if current entry is obsolete
        if (std::regex_search(line, robs)) {
            is_obs = true;
            //     std::cout << line <<std::endl;
        }

        if (std::regex_search(line, rcon)) {
            con = true;
            considers = std::regex_replace(line,std::regex("consider: "),"");
            //  std::cout << considers <<std::endl;
            v1.push_back(considers);
        }

        // if entry is finished and not obsolete, count that
        if (std::regex_search(line,stop)) {
            if (match && is_obs && con) {

                match = false;
                is_obs = false;
                con = false;
                res.push_back(v1);
                v1.clear();

            }
            if(match && is_obs && !con) {
                match = false;
                is_obs = false;
                v1.push_back("NA");
                res.push_back(v1);
                v1.clear();
            }
        }
    }

    infile.close();
    return (res);
}


std::vector<std::vector<std::string> > Parser::ConsiderTable_Namespace(std::string filename, std::string namesp) {

    //std::cout << " this is the considertable function " << std::endl;
    std::ifstream infile;
    std::string line = "";

    std::regex rgoid("^id: ");
    std::regex rnmsp("^namespace: ");
    std::regex robs("^is_obsolete: ");
    std::regex rcon("^consider: ");
    std::regex stop("^$");

    bool match= false;
    bool namespac = false;
    bool is_obs = false;
    bool con = false;


    std::string goid = "";
    std::string considers = "";

    std::vector<std::vector<std::string> > res;
    std::vector<std::string> v1;
    infile.open(filename);

    while (std::getline(infile, line)) {

        // check if current entry is in namespace


        if (std::regex_search(line, rgoid)) {
            match = true;
            goid = std::regex_replace(line,std::regex("^id: "),"");
            // std::cout << goid <<std::endl;
            //v1.push_back(goid);
            //is_obs = false;
        }
        if (std::regex_search(line, rnmsp)) {
            namespac = true;
            //     std::cout << line <<std::endl;
        }


        // check if current entry is obsolete
        if (std::regex_search(line, robs)) {
            is_obs = true;
            //     std::cout << line <<std::endl;
        }

        if (std::regex_search(line, rcon)) {
            con = true;
            considers = std::regex_replace(line,std::regex("consider: "),"");
            //  std::cout << considers <<std::endl;
            v1.push_back(considers);
        }

        // if entry is finished and not obsolete, count that
        if (std::regex_search(line,stop)) {
            if (match && namespac && is_obs && con) {

                match = false;
                is_obs = false;
                con = false;
                namespac = false;
                res.push_back(v1);
                v1.clear();

            }
            if(match && namespac && is_obs && !con) {
                match = false;
                is_obs = false;
                namespac = false;
                v1.push_back("NA");
                res.push_back(v1);
                v1.clear();
            }
        }
    }

    infile.close();
    return (res);
}



void usage (char * appname) {
    std::cout << "\n";
    std::cout << "This is a help message. Please use the app as indicated below." << std::endl;
    std::cout << appname << " filename taskname" <<std::endl;
    std::cout << "The available tasks are:  considerTable and obsoleteStats" <<std::endl;
    std::cout << "optional 4th argument molecular_function or biological_process or cellular_component"   << std::endl;
              std::cout << "\n";
    //std::cout << "The go-id should have the following format: e.g. GO:0000004 " <<std::endl;
}


int main(int argc, char **argv) {

    namespace fs = std::filesystem;
    auto ps = Parser();
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
         //   std::cout << "  is:  3" << cmd << std::endl;


            if (cmd != "considerTable" && cmd!= "obsoleteStats") {
                //std::string res = goutil.getName(argv[1],argv[3]) ;
                std::cout << "Taskname should be either  considerTable or obsoleteStats"  <<  std::endl;
                exit(0);
            }

            if (cmd == "considerTable" ) {
                //std::string res = goutil.getName(argv[1],argv[3]) ;
         //    std::cout << "this is considerTable cdm"  <<  std::endl;
             auto res = ps.ConsiderTable(argv[1]) ;
            for (int i = 0; i < res.size(); i++) {
                for (int j = 0; j < res[i].size(); j++)
                    std::cout << res[i][j] << " \t";
                std::cout << std::endl;
            }
            }

            if (cmd == "obsoleteStats") {
                //auto res = goutil.getEntry(argv[1],argv[3]) ;
                std::cout << "this is obsoleteStats cdm"<<  std::endl;
            }
        }

        if (argc == 4) {

            std::string cmd = std::string(argv[2]) ;
            std::string namesp = std::string(argv[3]) ;
           // std::cout << "  is: 4 " << cmd << std::endl;


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
               //std::cout << "this is considerTable cdm 4"  <<  std::endl;
                 //            std::cout << "this is considerTable cdm"  <<  std::endl;
             auto res = ps.ConsiderTable_Namespace(argv[1], namesp) ;
            for (int i = 0; i < res.size(); i++) {
                for (int j = 0; j < res[i].size(); j++)
                    std::cout << res[i][j] << " \t";
                std::cout << std::endl;
            }
            }

            if (cmd == "obsoleteStats") {
                //auto res = goutil.getEntry(argv[1],argv[3]) ;
                std::cout << "this is obsoleteStats cdm 4"<<  std::endl;
            }
        }

    }
    return(0);

}

