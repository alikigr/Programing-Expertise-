//g++ -std=c++17 -o task3 task3.cpp
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
    std::unordered_map<std::string, int>ECsummary(std::string filename);
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

std::unordered_map<std::string, int> Parser::ECsummary(std::string filename) {
    //std::cout << "this is the EC summary function, called with " << filename << std::endl;

    std::ifstream infile;
    std::string line = "";

    std::regex rname("^id: ");
    std::regex rEC("^xref: EC:");
    std::regex stop("^$");

    bool match = false;
    bool xref = false;

    std::string ECs = "";
    std::vector<std::string> all_ec= {};

    infile.open(filename);

    while (std::getline(infile, line)) {

        // check if current entry is in namespace
        if (std::regex_search(line, rname)) {
            match = true;
            xref = false;
        }

        // check if current entry is obsolete
        if (std::regex_search(line, rEC)) {
            xref = true;
            ECs = regex_replace(line, std::regex("xref: "), "");
            ECs = regex_replace(ECs, std::regex("(EC:[0-9]+\\.[0-9]+)(.*)"), "$1");
        }

        // if entry is finished and not obsolete, count that
        if (std::regex_search(line,stop) && match && xref ) {
            all_ec.push_back(ECs);
            match = false;
            xref = false;
        }
    }
    std::unordered_map<std::string, int> count;  // holds count of each encountered number
    for (int i=0;  i<all_ec.size();  i++)
        count[all_ec[i]]++;             // magic !

    infile.close();
    return (count);
}

} //end of namespace

void usage (char * appname) {
    std::cout << std::endl;
    std::cout << "This is a help message. Please use the app as indicated below.\n" << std::endl;
    std::cout << appname << " taskname function(optional) filename" <<std::endl;
    std::cout << "\nThe available tasks are:  summary and ECsummary.\n" <<
              "If the chosen task is summary, then the user has to choose one function too:\n" <<
              "molecular_function, biological_process, cellular_componenet\n" <<
              "In case you want to work with more than one input files, put them at the end."<< std::endl;
    //std::cout << "The go-id should have the following format: e.g. GO:0000004 " <<std::endl;
    std::cout <<std::endl;
}



int main(int argc, char **argv) {
    auto ps = GO::Parser();
    //ps.test();

    //using namespace std;
    namespace fs = std::filesystem;

    if (argc < 3) {
        usage(argv[0]);
        exit(1);
    }
    else {

        //std::cout << "this is else"  <<  std::endl;
        std::string cmd = std::string(argv[1]) ;

        if (cmd != "ECsummary" && cmd!="summary") {
            std::cout << "Taskname should be either summary or ECsummary"  <<  std::endl;
        }

        if (cmd == "summary") {

            //std::cout << "this is summary cdm "  <<  std::endl;
            std::string fun = std::string(argv[2]) ;

            if((fun!="molecular_function") && (fun!="biological_process") && (fun!="cellular_component")) {
                usage(argv[0]);
                exit(0);
            }

            for (int i=3; i<argc; i++) {
                if (!std::filesystem::exists(argv[i])) {
                    std::cout << "Error: File " << argv[i] << " does not exists!\n";
                    exit(1);
                }

                else {
                    auto res = ps.summary(argv[i],fun) ;
                    std::cout << "function is: " << fun <<std::endl;
                    std::cout << "file is: " << argv[i] <<std::endl;
                    for (std::pair<std::string, int> t:res) {
                        std::cout << t.first << "\t" << t.second <<std::endl;
                    }
                }
            }
        }
        
		if (cmd == "ECsummary") {

            for(int i=2; i<argc; i++) {
                if (!std::filesystem::exists(argv[i])) {
                    std::cout << "Error: File " << argv[i]<< " does not exists!\n";
                    exit(0);
                }
                else {
                    std::unordered_map<std::string, int> res = ps.ECsummary(argv[i]);
                    for (std::pair<std::string, int> t:res) {
                        std::cout<<argv[i] <<"\t"<< t.first << "\t" << t.second <<std::endl;
                    }
                }
            }
        }
    }
    return 0;
}
