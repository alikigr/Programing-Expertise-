#include <iostream>
#include <vector>
#include <regex>
#include <string>


#include <iostream>
#include <vector>
#include <regex>
#include <string>
namespace agu {

// a C++ grep which works like the R grep
std::vector<int> grep (std::string pattern, std::string str,
                       const std::regex::flag_type & flag = std::regex::extended) {
    std::regex rx;
    rx =std::regex(pattern,flag);
    std::vector<int> index_matches; // results saved here
    for(auto it =
                std::sregex_iterator(str.begin(), str.end(), rx);
            it != std::sregex_iterator(); ++it) {
        index_matches.push_back(it->position());
    }
    return(index_matches);
}


std::vector<int> grep (std::string pattern,
                       std::vector<std::string> vstring,
                       const std::regex::flag_type & flag = std::regex::extended) {
    std::regex rx;
    rx =std::regex(pattern,flag);
    std::vector<int> index_matches = {}; // results saved here
    int i = 0;
    for (auto el : vstring) {
        if (std::regex_search(el,rx)) {
            index_matches.push_back(i);
        }
        i=i+1;
    }
    return(index_matches);
}


std::vector<std::string> gsub( std::string pattern,  std::string replacement, std::vector<std::string> text) {

    std::vector<std::string> output = {};

    std::regex re;
    re =std::regex(pattern);
    std::string new_text = "";
    for (auto r : text) {
        new_text =  std::regex_replace(r, re, replacement);
        output.push_back(new_text);
    }
    return(output);
}


std::string gsub( std::string pattern,  std::string replacement, std::string text) {

    std::string output;
    std::regex re;
    re =std::regex(pattern);
    output = std::regex_replace(text, re, replacement);

    return(output);
}

bool grepl (std::string pattern, std::string str,
            const std::regex::flag_type & flag = std::regex::extended) {
    //Task 1A
    std::regex rx;
    rx = std::regex(pattern,flag);
    //std::cout << "match?\n";
    bool out=std::regex_search(str,rx);
    return(out);
}


std::vector<bool> grepl (std::string pattern, std::vector<std::string> strs,
                         const std::regex::flag_type & flag = std::regex::extended) {
    std::vector<bool> res ;
    std::regex rx;
    rx = std::regex(pattern,flag);
    for (auto el : strs) {
        if(std::regex_search(el,rx)) {
            res.push_back(true);
        } else {
            res.push_back(false);
        }
    }
    //Task 1B
    return(res);
}


bool any (std::vector<bool> elements) {
    //Task 1C
    for (auto el : elements) {
        if (el) {
            return(true);
        }
    }
    return(false);
}


bool all (std::vector<bool> elements) {
    //Task 1D
    for (auto el : elements) {
        if (!el) {
            return(false);
        }
    }
    return(true);
}



}


/* int main (int argc, char ** argv) {

   std::cout << agu::gsub("L","l", "ALiki") << std::endl;
   std::cout << agu::gsub("(geeks)(.*)","$2", "its all about geeksforgeeks") << std::endl;
   for (auto new_word : agu::gsub("L","l", std::vector<std::string>({"ALiki", "LLalouba"}))){
	   std::cout << "new word is  " << new_word << std::endl;}

}
*/
