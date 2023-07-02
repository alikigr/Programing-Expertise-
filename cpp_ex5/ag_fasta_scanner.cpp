#include <iostream>
#include <map>
#include <filesystem>
#include <regex>
#include <fstream>
#include "ag_utils.cpp"
#include "argparse.hpp"


std::vector< std::string > scan_pattern (std::string filename, std::string pattern) {

    std::ifstream infile;
    std::string line;
    std::regex rxId("^>");
    std::string id;
    std::string sequence = "";
    std::vector< std::string > result;

    infile.open(filename);

    // go through file
    while (std::getline(infile, line)) {

        // check if we are at the start of a new sequence
        if (std::regex_search(line, rxId)) {

            // if we have a previous sequence do all the updating we need
            if (sequence.length() > 0) {

                // if found, update result vector with id
                if (agu::grepl(pattern, sequence)) {
                    result.push_back(id);
                }

            }

            id = std::regex_replace(line, std::regex(">([^ ]+) *.*"), "$1");

            sequence = "";

        } else {

            sequence.append(line);

        }
    }

    infile.close();
    return(result);
}



int main(int argc, char ** argv) {
    namespace fs = std::filesystem;
    argparse::ArgumentParser program("fasta-file parsing");

    program.add_argument("-f", "--filename")
    .required()
    .help("Specify the fasta file to be searched for an amino-acid pattern.");


    program.add_argument("-p", "--pattern")
    .required()
    .help("Specify the amino-acid pattern to be searched in the file.");

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    std::string filename = program.get<std::string>("--filename");
    std::string pattern = program.get<std::string>("--pattern");

    if (!fs::exists(filename)) {
        std::cout << "Given file does not exists!\n";
        exit(1);
    } else {
        std::cout << "Given file " << filename << " does  exists!\n";
        //
    }

    std::vector<std::string> result = scan_pattern(filename, pattern);
    for (auto r : result) {
        std::cout <<  "protein id: " << r << std::endl;
    }
    return(0);
}


