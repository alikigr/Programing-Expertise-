//g++ -std=c++17 -o task5 task5.cpp

# include <iostream>
# include <filesystem>
# include <fstream>
# include <regex>
# include <map>



class Util {

public:
    void test() {
        std::cout << "This is a test" << std::endl;
    }
    std::string getInfo(std::string filename, std::string id);
    std::string searchEC(std::string filename, std::string id);

private:
    int x = 0;
};


std::string  Util::getInfo(std::string filename, std::string id) {
    //std::cout << "this is the  getEntry function" << std::endl;
    std::ifstream infile;
    infile.open(filename);

    std::string line;
    std::string entry = {};
    bool flag = false;

    std::string pattern = "^id: " + id;
    std::regex rx(pattern);

    //std:: regex EndEntry("\\[T.*\\]"); //match[Term] or [Typedef]
    std:: regex EndEntry("^$"); //


    while (std::getline(infile,line)) {
        if (std::regex_search(line,rx)) {
            //std::cout << "found " << line << "\n";
            flag = true;
        }

        if(std::regex_search(line, EndEntry)) {

            if (flag) {
                break;
            }
        }

        if (flag) {
            entry = entry + line + "\n" ;
        }
    }
    return(entry);
}

void usage (char * appname) {
    std::cout << "This is a help message. Please use the app as indicated below." << std::endl;
    std::cout << appname << " gene-ontology-file  taskname go-id" <<std::endl;
    std::cout << "The available commands are:  searchEC, getInfo " <<std::endl;
    std::cout << "The go-id should have the following format: e.g. GO:0000003 " <<std::endl;
}


int main(int argc, char **argv) {


    auto goutil = Util();
    goutil.test();

    namespace fs = std::filesystem;

    if (argc != 4) {
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


        //std::cout << "command  is: " << cmd << std::endl;

        //std::string id = std::string(argv[3]) ;
        //std::cout << "id  is: " << id << std::endl;

        if (cmd == "searchEC") {
            //std::string res = goutil.getName(argv[1],argv[3]) ;
            std::cout << "this is search ec cdm"  <<  std::endl;
        }
        
        if (cmd == "getInfo") {
            std::string res = goutil.getInfo(argv[1],argv[3]);
            std::cout << res <<  std::endl;
        }

    }
    return 0;
}
