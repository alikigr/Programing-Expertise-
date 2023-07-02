//compile like this:
// g++ -std=c++17 -o GoUtil AG_GoUtil.cxx
// It works on unzipped gene-ontology files.


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <filesystem>
//#include "ghc-filesystem.hpp"
//namespace fs = ghc::filesystem;

namespace dgu {

class GoUtil {

public:
    void test() {
        std::cout << "This is a test" << std::endl;
    }
    std::string getName(std::string filename, std::string id);
    std::string getEntry(std::string filename, std::string id);
    bool isObsolete(std::string filename, std::string id);
    std::map<std::string,std::string> getParents(std::string filename, std::string id);
    //void getParents(std::string filename, std::string id);
private:
    int x = 0;
};

std::string GoUtil::getName(std::string filename, std::string id) {
    std::ifstream infile;
    infile.open(filename);
    std::string line;
    std::string pattern = "^id: " + id;
    std::regex rx(pattern);
    std::regex rname("^name: ");
    std::regex stop("^$");
    std::string name = "";
    bool flag_id = false;
    bool flag_name = false;
    while (std::getline(infile,line)) {
        if (std::regex_search(line,rx)) {
            //std::cout << "found " << line << "\n";
            flag_id = true;
        } 
        if (std::regex_search(line,rname)) {
            //name = line;
            name = std::regex_replace(line,std::regex("name: "),"");
            flag_name = true;
        }
        if (std::regex_search(line,stop) && flag_name && flag_id){
			
			break;
			}
    }
    infile.close();
    return(name);
}



std::string GoUtil::getEntry(std::string filename, std::string id) {
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
    infile.close();
    return(entry);
}



bool GoUtil::isObsolete(std::string filename, std::string id) {

    std::string s= GoUtil::getEntry(filename, id);
    //std::cout << "this is the is obsolete function" <<std::endl;
    std::smatch m;
    std::regex e ("is_obsolete: ");
    bool is_obs = false;

    while (std::regex_search (s,m,e)) {
        for (auto x:m)
            //std::cout << x << " ";
            is_obs  = true;
        s = m.suffix().str();
    }
    //infile.close();
    return(is_obs);

}

std::map<std::string,std::string>  GoUtil::getParents(std::string filename, std::string id) {

    std::string s= GoUtil::getEntry(filename, id);
    std::smatch m;
    std::regex e ("is_a: GO:[0-9]{7}");
    std::vector< std::string > result;
    std::string ids = "";
    std::map< std::string, std::string > res = {};

    while (std::regex_search (s,m,e)) {
        for (std::string x:m) {
            ids = std::regex_replace(x, std::regex("is_a: "), "");
            result.push_back(ids);
        }

        s = m.suffix().str();
    }
    for (auto l:result) {
        res[l] =  getName(filename, l);
    }
    //infile.close();
    return(res);
}


} // end of namespace dgu
//#ifdef GOUTIL




void usage (char * appname) {
    std::cout << "This is a help message. Please use the app as indicated below." << std::endl;
    std::cout << appname << " gene-ontology-file  command go-id\n";
    std::cout << "The available commands are: getEntry, getName, getParents, isObsolete." <<std::endl;
    std::cout << "The go-id should have the following format: e.g. GO:0000004 " <<std::endl;
}

int main(int argc, char **argv) {

    auto goutil = dgu::GoUtil();
	namespace fs = std::filesystem;
    
    if (argc != 4) {
        usage(argv[0]);
        
    } else {
		
        if (!fs::exists(argv[1])) {
            std::cout << "Error: File " << argv[1] << " does not exists!\n";
            exit(1);
        }
        std::string id = std::string(argv[3]) ;
        std::regex e("GO:[0-9]{7}");
        
        if (!std::regex_match(id,e))     {
            std::cout << "Given GO-id is not valid. "<< "\n";
            exit(1);
        }
        std::string cmd = std::string(argv[2]) ;
        if (cmd!= "getName" && cmd!="isObsolete" && cmd!= "getEntry" && cmd!="getParents"){
		std::cout << "taskname should be getName or isObsolete or getEntry or getParents" <<std::endl;
			 }
        //std::cout << " command  is: " << cmd << "\n";
        if (cmd == "getName") {
            std::string res = goutil.getName(argv[1],argv[3]) ;
            std::cout << "name is: " << res << "\n";
        }
        if (cmd == "getEntry") {
            auto res = goutil.getEntry(argv[1],argv[3]) ;
            std::cout << res<< "\n";
        }
        if (cmd == "isObsolete") {
            bool res = goutil.isObsolete(argv[1],argv[3]);
            std::cout << "is obsolete: " << res << "\n";
        }
        if (cmd == "getParents") {
            auto res =  goutil.getParents(argv[1],argv[3]);
            //std::cout << "Parents " << "\t" << "Names" <<  std::endl;
            for (std::pair<std::string, std::string> t:res) {
                std::cout << t.first << "\t" << t.second <<std::endl;
            }
        }
    }
    return 0;
}

//#endif
