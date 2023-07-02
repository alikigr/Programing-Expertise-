#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include <string>
#include <iostream>
# include <vector>
# include <array>
# include <algorithm>
# include "Blosum.cpp"
# include "Blosum50.cpp"
# include "argparse.hpp"

using namespace std;

int min(int a, int b){
	return((a) < (b) ? (a) : (b));
	}


int max(int a, int b){
	return((a) > (b) ? (a) : (b));
	}



int levenshtein_distance(string src, string dst, int gapcost=1) {
    //assert(src != NULL && dst != NULL);
    
    int src_len = src.length();
    int dst_len = dst.length();
    
    if (src == dst) {
        return 0;
    } else if (src.length() == 0) {
        return  dst.length()*gapcost;
    } else if (dst.length() == 0) {
        return  src.length()*gapcost;
    }

    int d[src_len + 1][dst_len + 1];
    for (int i = 0; i < src_len + 1; i++) d[i][0] = i*gapcost;
    for (int j = 0; j < dst_len + 1; j++) d[0][j] = j*gapcost;

    for (int i = 1; i < src_len + 1; i++) {
        for (int j = 1; j < dst_len + 1; j++) {
				// 			vertical/horizontal 								diagonal
            d[i][j] = min(min(d[i-1][j], d[i][j-1]) + gapcost + 1, d[i-1][j-1] + (src[i-1] == dst[j-1] ? 0 : 1));

        }
    }
    return d[src_len][dst_len];
}


int needle_wunsch62(string src, string dst, Blosum score_matrix, int gapcost) {
    //assert(src != NULL && dst != NULL);
    
    int src_len = src.length();
    int dst_len = dst.length();
    
    if (src == dst) {
        return 0;
    } else if (src.length() == 0) {
        return  dst.length()*gapcost;
    } else if (dst.length() == 0) {
        return  src.length()*gapcost;
    }

    int d[src_len + 1][dst_len + 1];
    for (int i = 0; i < src_len + 1; i++) d[i][0] = i*gapcost;
    for (int j = 0; j < dst_len + 1; j++) d[0][j] = j*gapcost;

    for (int i = 1; i < src_len + 1; i++) {
        for (int j = 1; j < dst_len + 1; j++) {
				// 			vertical/horizontal 								diagonal
            d[i][j] = max(max(d[i-1][j], d[i][j-1]) + gapcost, d[i-1][j-1] + score_matrix(src.at(i-1), dst.at(j-1)));

        }
    }
    return d[src_len][dst_len];
}

int needle_wunsch50(string src, string dst, Blosum50 score_matrix, int gapcost) {
    //assert(src != NULL && dst != NULL);
    
    int src_len = src.length();
    int dst_len = dst.length();
    
    if (src == dst) {
        return 0;
    } else if (src.length() == 0) {
        return  dst.length()*gapcost;
    } else if (dst.length() == 0) {
        return  src.length()*gapcost;
    }

    int d[src_len + 1][dst_len + 1];
    for (int i = 0; i < src_len + 1; i++) d[i][0] = i*gapcost;
    for (int j = 0; j < dst_len + 1; j++) d[0][j] = j*gapcost;

    for (int i = 1; i < src_len + 1; i++) {
        for (int j = 1; j < dst_len + 1; j++) {
				// 			vertical/horizontal 								diagonal
            d[i][j] = max(max(d[i-1][j], d[i][j-1]) + gapcost, d[i-1][j-1] + score_matrix(src.at(i-1), dst.at(j-1)));

        }
    }
    return d[src_len][dst_len];
}


int main(int argc, char const *argv[]) {    
    
    argparse::ArgumentParser program("Needleman-Wunsch");

    program.add_argument("source_string")
        .default_value<string>("ALASKA")
        .help("The source string is the string to which the distination string is going to be compared");

    program.add_argument("destination_string")
        .default_value<string>("ALABAMA")
        .help("Destination string");

    program.add_argument("-l", "--levenshtein")
        .help("Levenshtein distance of the two strings.")
        .default_value<bool>(false)
        .implicit_value(true);

    program.add_argument("-c", "--gapcost")
        .help("Specify the cost to assign to a gap in the alignment")
        .default_value<int>(-10)
        .action([](const std::string& value) {
            return std::stoi(value);
        });

    program.add_argument("-b", "--blosum62")
		//.help("Specify a file containing a formatted BLOSUM matrix")
        //.default_value<string>("");
		.help("Use Blosum62 scoring matrix")
        .default_value<bool>(true)
        .implicit_value(false);
        
    program.add_argument("-m", "--blosum50")
  		.help("Use Blosum50 scoring matrix")
        .default_value<bool>(false)
        .implicit_value(true);

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }
    
    auto src = program.get<std::string>("source_string");
    auto dst = program.get<std::string>("destination_string");

    auto gap_cost = program.get<int>("--gapcost");
    auto do_levenshtein = program.get<bool>("--levenshtein");
    auto do_blosum62 = program.get<bool>("--blosum62");
    auto do_blosum50 = program.get<bool>("--blosum50");

    if (do_levenshtein) {

        int dist = levenshtein_distance(src, dst, gap_cost);

        cout << "L.Distance between the strings " << src << " and "
            << dst << " is " << dist << endl;

    } else if (do_blosum50){
		
        Blosum50 score_mat = Blosum50();
        int score = needle_wunsch50(src, dst, score_mat, gap_cost);
        cout << "The alignment score with blosum50 of " << src << " against " << dst <<" is " << score << endl;
        
	}
	else {
		
		Blosum score_mat = Blosum();

        int score = needle_wunsch62(src, dst, score_mat, gap_cost);

        cout << "The alignment score with blosum62 of " << src << " against " << dst <<
            " is " << score << endl;
    
    }

    return 0;
}

