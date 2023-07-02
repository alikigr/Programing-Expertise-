#include "ag_XProteinSports.cpp"
#include </home/aliki/Desktop/uni/SoSe22/ProgExp/exercises/argparse/include/argparse/argparse.hpp>
#include <string>

//int main(int argc, char const *argv[]){
//   XProteinSports xps=XProteinSports();
//   std::cout<< xps.aa2hydropathy("D") << std::endl;
//   std::cout<< xps.aa2hydropathy("Ala") << std::endl;
//  std::cout<< xps.aa2hydropathy("Tyr") << std::endl;
//   xps.menu(5, "");
//  return 0;
//}


int main(int argc, char const *argv[]) {
    argparse::ArgumentParser parser("XProteinSport");

    parser.add_argument("-n", "--entries")
    .help("Specify number of games you wish to play.")
    .default_value(10)
    .action([](const std::string& value) {
        return std::stoi(value);
    });

    parser.add_argument("-t", "--triple")
    .help("Only do triple letter exercises.")
    .default_value(false)
    .implicit_value(true);

    parser.add_argument("-s", "--single")
    .help("Only do single letter exercises.")
    .default_value(false)
    .implicit_value(true);

    parser.add_argument("-d", "--hydropathy")
    .help("Only do hydropathy exerxises.")
    .default_value(false)
    .implicit_value(true);

    parser.add_argument("-m", "--molweight")
    .help("Only do mol. mass guessing exercises.")
    .default_value(false)
    .implicit_value(true);

    parser.add_argument("-p", "--peptide")
    .help("Calculate the molecular weight of a peptide e.g ALASKA.");
    //.default_value(false)
    //.implicit_value(true);
    
    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << parser;
        exit(0);
    }

    auto pe = XProteinSports();

    int n_try = parser.get<int>("--entries");
    /*auto pep = parser.get<std::string>("--peptide");
    std::string peptide = pep;
*/
    std::string only_task = "";

    if (parser["--triple"] == true) {
        only_task = "t";
    }
    if (parser["--single"] == true) {
        only_task = "s";
    }
    if (parser["--hydropathy"] == true) {
        only_task = "d";
    }
    if (parser["--molweight"] == true) {
        only_task = "m";
    }
   if (auto fn = parser.present("-p")){
		std::cout << "String: " <<*fn << std::endl;
		float w = 0;
		for (auto c : *fn) {
			std::cout << c << std::endl;
			w=w+pe.getWeight(std::string(1,c));
			}
			std::cout << w << std::endl;
		} 


    pe.menu(n_try, only_task/*, peptide*/);

    return 0;
}
