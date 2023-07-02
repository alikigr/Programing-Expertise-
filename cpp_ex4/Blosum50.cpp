#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class Blosum50 {
    std::vector< std::vector<int> > data;
    std::vector<std::string> rownames;
    std::vector<std::string> colnames;
    size_t cols;
public:
    Blosum50() {
        typedef std::vector< std::vector<int> > IntMatrix;
        std::stringstream ss(blosum50);
        std::string line;
        int value;
        std::string name;
        while (std::getline(ss, line,'\n')) {
            if (line[0] == '#')  {
                continue;
            }
            if (line[0] == ' ') {
                std::istringstream converter(&line[0]); // &line[1] to skip leading letter
                while (converter >> name) {
                    colnames.push_back(name);
                }
            } else {

                std::istringstream converter(&line[0]);
                converter >> name;
                rownames.push_back(name);
                std::vector<int> rowvalues = {};
                while (converter >> value) {
                    rowvalues.push_back(value);

                }
                data.push_back(rowvalues);
            }
        }
    }
    int &operator()(int x, int y) {
        return data.at(x).at(y);
    }
    int &operator()(char cx, char cy) {
        int x = base2num(cx);
        int y = base2num(cy);
        return data.at(x).at(y);
    }
    int &operator()(std::string cx, std::string cy) {
        int x = base2num(cx);
        int y = base2num(cy);
        return data.at(x).at(y);
    }
    void read_matrix(std::string const & filename) {
        std::ifstream infile(filename);
        std::string line;
        int value;
        std::string name;
        while (std::getline(infile, line,'\n')) {
            if (line[0] == '#')  {
                continue;
            }
            if (line[0] == ' ') {
                std::istringstream converter(&line[0]); // &line[1] to skip leading letter
                while (converter >> name) {
                    colnames.push_back(name);
                }
            } else {

                std::istringstream converter(&line[0]);
                converter >> name;
                rownames.push_back(name);
                std::vector<int> rowvalues = {};
                while (converter >> value) {
                    rowvalues.push_back(value);

                }
                data.push_back(rowvalues);
            }
        }
    }
protected:
    // TODO: could be better take the letters from the first row
    int base2num (std::string s) {
        for (int i = 0; i < colnames.size(); i++) {
            if (s == colnames[i]) {
                return(i);
            }
        }
        return(-1);

    }
    int base2num(char b) {
        std::string s;
        s = b;
        return(base2num(s));
    }
    std::string blosum50 =
        "   A  R  N  D  C  Q  E  G  H  I  L  K  M  F  P  S  T  W  Y  V  B  J  Z  X  *\n"
        "A  5 -2 -1 -2 -1 -1 -1  0 -2 -1 -2 -1 -1 -3 -1  1  0 -3 -2  0 -2 -2 -1 -1 -5*\n"
        "R -2  7 -1 -2 -4  1  0 -3  0 -4 -3  3 -2 -3 -3 -1 -1 -3 -1 -3 -1 -3  0 -1 -5*\n"
        "N -1 -1  7  2 -2  0  0  0  1 -3 -4  0 -2 -4 -2  1  0 -4 -2 -3  5 -4  0 -1 -5*\n"
        "D -2 -2  2  8 -4  0  2 -1 -1 -4 -4 -1 -4 -5 -1  0 -1 -5 -3 -4  6 -4  1 -1 -5*\n"
        "C -1 -4 -2 -4 13 -3 -3 -3 -3 -2 -2 -3 -2 -2 -4 -1 -1 -5 -3 -1 -3 -2 -3 -1 -5*\n"
        "Q -1  1  0  0 -3  7  2 -2  1 -3 -2  2  0 -4 -1  0 -1 -1 -1 -3  0 -3  4 -1 -5*\n"
        "E -1  0  0  2 -3  2  6 -3  0 -4 -3  1 -2 -3 -1 -1 -1 -3 -2 -3  1 -3  5 -1 -5*\n"
        "G  0 -3  0 -1 -3 -2 -3  8 -2 -4 -4 -2 -3 -4 -2  0 -2 -3 -3 -4 -1 -4 -2 -1 -5*\n"
        "H -2  0  1 -1 -3  1  0 -2 10 -4 -3  0 -1 -1 -2 -1 -2 -3  2 -4  0 -3  0 -1 -5*\n"
        "I -1 -4 -3 -4 -2 -3 -4 -4 -4  5  2 -3  2  0 -3 -3 -1 -3 -1  4 -4  4 -3 -1 -5*\n"
        "L -2 -3 -4 -4 -2 -2 -3 -4 -3  2  5 -3  3  1 -4 -3 -1 -2 -1  1 -4  4 -3 -1 -5*\n"
        "K -1  3  0 -1 -3  2  1 -2  0 -3 -3  6 -2 -4 -1  0 -1 -3 -2 -3  0 -3  1 -1 -5*\n"
        "M -1 -2 -2 -4 -2  0 -2 -3 -1  2  3 -2  7  0 -3 -2 -1 -1  0  1 -3  2 -1 -1 -5*\n"
        "F -3 -3 -4 -5 -2 -4 -3 -4 -1  0  1 -4  0  8 -4 -3 -2  1  4 -1 -4  1 -4 -1 -5*\n"
        "P -1 -3 -2 -1 -4 -1 -1 -2 -2 -3 -4 -1 -3 -4 10 -1 -1 -4 -3 -3 -2 -3 -1 -1 -5*\n"
        "S  1 -1  1  0 -1  0 -1  0 -1 -3 -3  0 -2 -3 -1  5  2 -4 -2 -2  0 -3  0 -1 -5*\n"
        "T  0 -1  0 -1 -1 -1 -1 -2 -2 -1 -1 -1 -1 -2 -1  2  5 -3 -2  0  0 -1 -1 -1 -5*\n"
        "W -3 -3 -4 -5 -5 -1 -3 -3 -3 -3 -2 -3 -1  1 -4 -4 -3 15  2 -3 -5 -2 -2 -1 -5*\n"
        "Y -2 -1 -2 -3 -3 -1 -2 -3  2 -1 -1 -2  0  4 -3 -2 -2  2  8 -1 -3 -1 -2 -1 -5*\n"
        "V  0 -3 -3 -4 -1 -3 -3 -4 -4  4  1 -3  1 -1 -3 -2  0 -3 -1  5 -3  2 -3 -1 -5*\n"
        "B -2 -1  5  6 -3  0  1 -1  0 -4 -4  0 -3 -4 -2  0  0 -5 -3 -3  6 -4  1 -1 -5*\n"
        "J -2 -3 -4 -4 -2 -3 -3 -4 -3  4  4 -3  2  1 -3 -3 -1 -2 -1  2 -4  4 -3 -1 -5*\n"
        "Z -1  0  0  1 -3  4  5 -2  0 -3 -3  1 -1 -4 -1  0 -1 -2 -2 -3  1 -3  5 -1 -5*\n"
        "X -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -5*\n"
        "* -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5 -5  1*\n"
        ;

};

/*int main (int argc, char ** argv) {
    Blosum50 bl=Blosum50();
    std::cout << "Blossum!" << std::endl;
    std::cout << bl(0,0) << std::endl;
    std::cout << bl(3,3) << std::endl;
    std::cout << bl('L','A') << std::endl;
    std::cout << bl('D','Q') << std::endl;
    std::cout << bl("Q","D") << std::endl;
    std::cout << bl("A","A") << std::endl;
    std::cout << bl("A","R") << std::endl;
    std::cout << bl("R","R") << std::endl;
    return(0);
}



*/
