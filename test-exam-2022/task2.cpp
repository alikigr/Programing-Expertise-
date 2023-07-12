// g++ -std=c++17 -o task2 task2.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <filesystem>
//using namespace std;


std::vector<std::vector<std::string> >getMetaCyc(std::string filename, std::string id) {

    //std::cout << "this is GetMetaCyc function" << std::endl;
    std::ifstream infile;
    infile.open(filename);
    std::string line;

    std::regex rgoid("^id: ");
    std::regex rname("^name: ");
    std::regex rnsp("^namespace: ");
    std::string pattern = "^xref:.*" + id;
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
	std::cout << "\n";
    std::cout << "This is a help message. Please use the app as indicated below." << std::endl;
	std::cout << appname << " gene-ontology-file  command  id(optional) \nSee example: \n";
    std::cout << "./task2 gene_ontology_edit.obo.2022-01-13 tabMetaCyc \n" ;
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
        //std::cout << "this is 3 arg" <<std::endl;

        if (!fs::exists(file)) {
            std::cout << "Error: File " << file << " does not exists!\n";
            exit(1);
        }
        if (taskname!="tabMetaCyc") {

            std::cout << "Taskname should be getMetaCyc or tabMetaCyc. See usage."<< std::endl;
            exit(1);
        }

        if (taskname == "tabMetaCyc") {

            //std::cout << "this is tabmetacyc cmd" << std::endl;
        }


    }
    if (argc == 4) {

        std::string file = argv[1];
        std::string taskname = argv[2];
        std::string id =argv[3];
        //RXN or PWY
        std::regex ss(".*[R,P][X,W][N,Y]");

        //std::cout << "this is 4" <<std::endl;

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
            //std::cout << "this is getmetacyc cmd" << std::endl;
            std::vector<std::vector<std::string> >res = getMetaCyc(file,id);
            for (int i = 0; i < res.size(); i++) {
                for (int j = 0; j < res[i].size(); j++)
                    std::cout << res[i][j] << " \t";
                std::cout << std::endl;
            }

        }
    }


    return 0;
}
