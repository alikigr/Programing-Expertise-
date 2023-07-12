// g++ -std=c++17 -o task3 task3.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <filesystem>
//using namespace std;

class Parser {
public:
    std::vector<std::vector<std::string> >getMetaCyc(std::string filename, std::string id);
    std::vector<std::vector<std::string> >tabMetaCyc(std::string filename);
    void test() {
        std::cout << "this is a class test" << std::endl;
    }

};

std::vector<std::vector<std::string> >Parser::tabMetaCyc(std::string filename) {

    //std::cout << "this is tabMetaCyc function" << std::endl;
    std::ifstream infile;
    infile.open(filename);
    std::string line;

    std::regex rgoid("^id: ");
    std::regex rec("^xref: EC:");
    std::regex rxf("^xref:.*RXN$");
    std::regex stop("^$");

    std::string goid = "";
    std::string ec = "";
    std::string rxn = "";

    bool flag_rxf = false;
    bool flag_rec = false;

    std::vector<std::vector<std::string> > res;

    while (std::getline(infile,line)) {
        if (std::regex_search(line,rgoid)) {
            //std::cout << "found " << line << "\n";
            //flag = true;
            goid = std::regex_replace(line,std::regex("id: "),"");
            //std::cout << "this is goid: "<< goid << std::endl;
        }
        if (std::regex_search(line,rec)) {
            //name = line;
            ec = std::regex_replace(line,std::regex("xref: "),"");
            //std::cout << "this is name: "<< name << std::endl;
            flag_rec = true;
        }
        if (std::regex_search(line,rxf)) {
            //name = line;
            rxn = std::regex_replace(line,std::regex("xref: "),"");
            flag_rxf = true;
        }

        if (std::regex_search(line, stop)) {

            if (flag_rxf && flag_rec) {

                flag_rxf  = false;
                flag_rec = false;

                std::vector<std::string> v1;

                v1.push_back(goid);
                v1.push_back(ec);
                v1.push_back(rxn);

                res.push_back(v1);
            }

            if (flag_rxf && !flag_rec) {

                flag_rxf  = false;
                flag_rec = false;

                std::vector<std::string> v1;

                v1.push_back(goid);
                v1.push_back("NA");
                v1.push_back(rxn);

                res.push_back(v1);
            }
        }
    }
    infile.close();
    return(res);

}

std::vector<std::vector<std::string> >Parser::getMetaCyc(std::string filename, std::string id) {

    //std::cout << "this is GetMetaCyc function" << std::endl;
    std::ifstream infile;
    infile.open(filename);
    std::string line;

    std::regex rgoid("id: ");
    std::regex rname("name: ");
    std::regex rnsp("^namespace: ");
    std::string pattern = "^xref:.*" + id + "$";
    std::regex rx(pattern);
    std::regex stop("^$");

    std::string goid = "";
    std::string name = "";
    std::string namespc = "";
    std::string xref = "";


    bool flag = false;

    std::vector<std::vector<std::string> > res;

    while (std::getline(infile,line)) {
        if (std::regex_search(line,rgoid)) {
            //std::cout << "found " << line << "\n";
            //flag = true;
            goid = std::regex_replace(line,std::regex("id: "),"");
            //std::cout << "this is goid: "<< goid << std::endl;
        }
        if (std::regex_search(line,rname)) {
            //name = line;
            name = std::regex_replace(line,std::regex("name: "),"");
            //std::cout << "this is name: "<< name << std::endl;
        }
        if (std::regex_search(line,rnsp)) {
            //name = line;
            namespc = std::regex_replace(line,std::regex("namespace: "),"");
        }
        if (std::regex_search(line,rx)) {
            //name = line;
            xref = std::regex_replace(line,std::regex("xref: "),"");
            flag = true;
        }
        if (flag && std::regex_search(line, stop)) {

            flag  = false;

            std::vector<std::string> v1;

            v1.push_back(goid);
            v1.push_back(name);
            v1.push_back(namespc);
            v1.push_back(xref);

            res.push_back(v1);

        }
    }
    infile.close();
    return(res);
}




void usage (char * appname) {
    std::cout << "This is a help message. Please use the app as indicated below." << std::endl;
    std::cout << appname << " gene-ontology-file  command  id(optional)\n";
    std::cout << "The available commands are: tabMetaCyc, getMetaCyc." <<std::endl;
    std::cout << "In the case of getMetaCyc, you should also provide the id  RXN or PWY." <<std::endl;
}

int main(int argc, char **argv) {

    namespace fs = std::filesystem;
    auto ps = Parser();
    //ps.test();
    std::string file = argv[1];
    std::string taskname = argv[2];
    std::regex ss(".*[R,P][X,W][N,Y]");

    if (argc < 3 ) {
        usage(argv[0]);
        return(0);
    }
    else
    {
        std::cout << "this is else" <<std::endl;
        if (!fs::exists(file)) {
            std::cout << "Error: File " << file << " does not exists!\n";
            exit(0);
        }
        if (taskname!="tabMetaCyc" && taskname!="getMetaCyc") {

            std::cout << "Taskname should be getMetaCyc or tabMetaCyc. See usage."<< std::endl;
            exit(0);
        }

        if (taskname == "tabMetaCyc") {

            std::cout << "this is tabmetacyc cmd" << std::endl;
            std::vector<std::vector<std::string> >res = ps.tabMetaCyc(file);
            for (int i = 0; i < res.size(); i++) {
                for (int j = 0; j < res[i].size(); j++)
                    std::cout << res[i][j] << " \t";
                std::cout << std::endl;
            }
        }

        if (taskname=="getMetaCyc") {
			 std::cout << "this is getmetacyc cmd" << std::endl;
            for (int i=3; i < argc; i++) {
                //std::cout << argv[i] <<std::endl;
                if (!std::regex_match(argv[i],ss))     {
                    std::cout << "Given id is not valid. \n"<<"ID should be either RXN or PWY"<< std::endl;
                    exit(0);
                }
            }
            for (int i=3; i < argc; i++) {
                //std::cout << argv[i] <<std::endl;
                std::vector<std::vector<std::string> >res = ps.getMetaCyc(file,argv[i]);
                for (int i = 0; i < res.size(); i++) {
                    for (int j = 0; j < res[i].size(); j++)
                        std::cout << res[i][j] << " \t";
                    std::cout << std::endl;
                }
            }
        }
    }
    return 0;
}
