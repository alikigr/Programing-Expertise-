#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include<bits/stdc++.h>


class ProteinSports {
public:

    std::string test() {
        return("testing test\n");
    }

    std::string a2aaa(std::string a) {
        auto res = std::lower_bound(avec.begin(),avec.end(),a);
        int index = std::distance(avec.begin(),res); // res-avec.begin()
        return(aaavec[index]);
    }

    std::string aaa2a(std::string aaa) {
        int i = 0;
        std::string a = "";
        for (auto ai : aaavec) {
            if (ai == aaa) {
                a=avec[i];
                break;
            }
            i++;
        }
        return(a);

    }

    float getWeight(std::string aa) {
        float weight = 0;
        int index = 0;
        if (aa.length() == 1) {
            auto res = std::lower_bound(avec.begin(),avec.end(),aa);
            index = std::distance(avec.begin(),res);
        } else {
            std::string a = aaa2a(aa);
            return(getWeight(a));
        }
        return(aweight[index]);
    }

    int random_aa() {

        srand(time(NULL));
        int ra = rand() % 20;
        return(ra);
    }

    void display(std::vector<int> x) {

        std::cout << "single \t" << "triple \t" << "molecular weight " << std::endl;
        for(int i=0; i<x.size(); i++) {

            auto elm = x[i];
            std::cout << avec[elm]<< "\t" <<  aaavec[elm] << "\t" << ProteinSports::getWeight(avec[elm]) << std::endl;
        }
    }

    void menu(int n_question) {

        std::cout << "Hi! I am a menu! \nHow many times would you like to try the guessing game?" << std::endl;
        std::cin >> n_question;
        int counter = 0;
        int inc = 0;
        float score = 0;

        std::vector<int> x;

        for (int try_number = 1; try_number <= n_question; try_number ++) {

            std::string choice = "";
            int ra = ProteinSports::random_aa();
            x.push_back(ra);

            while (choice != "t" && choice != "s" && choice != "m" && choice != "q") {

                std::cout << "(s)ingle letter a2aaa, (t)riplett aaa2a, (m)olecular  weight, or (q)uit:" << std::endl;
                std::cin >> choice;

                if (choice == "s") {

                    std::string aaa= aaavec[ra];
                    std::cout << "What is the amino acid " << aaa << " in single code?" << std::endl;
                    //std::cout << ProteinSports::aaa2a(aaa)  << std::endl;
                    std::string aaa_answer= "";
                    std::cin>> aaa_answer;

                    if (aaa_answer == ProteinSports::aaa2a(aaa)) {
                        std::cout << "\033[1;32mcorrect\033[0m\n";
                        counter ++;
                    }
                    else {
                        std::cout << "\033[1;31mwrong\033[0m\n";
                        inc ++;
                    }

                }
                if (choice == "t") {
                    std::string a=avec[ra];
                    std::cout << "What is the amino acid " << a << " in triple code?" << std::endl;
                    //std::cout << ProteinSports::a2aaa(a)  << std::endl;
                    std::string a_answer= "";
                    std::cin>> a_answer;

                    if (a_answer == ProteinSports::a2aaa(a)) {
                        std::cout << "\033[1;32mcorrect\033[0m\n";
                        counter  ++;
                    }
                    else {
                        std::cout << "\033[1;31mwrong\033[0m\n";
                        inc ++;
                    }
                }
                if (choice == "m") {

                    std::string aa= aaavec[ra];
                    std::cout << "What is the  molecular weight of the aminoacid " << aa << "?\nDeviation of +- 20 is acceptable." << std::endl;
                    float molw = ProteinSports::getWeight(aa);
                    float max = molw + 20;
                    float min = molw -20;
                    //std::cout << molw << "\n"<< max << "\n" << min << std::endl;

                    float molw_answer;
                    std::cin>> molw_answer;



                    if ((molw_answer>=min) &&  (molw_answer <= max)) {
                        std::cout << "\033[1;32mcorrect\033[0m\n";
                        counter ++;
                        float diff = molw - molw_answer;

                        if (diff > 0) {
                            score = score+20 - diff;
                        }
                        else if (diff <0) {
                            score = score+20+diff;
                        }
                    }
                    else {
                        std::cout << "\033[1;31mwrong\033[0m\n";
                        inc++;
                    }
                }
                if (choice == "q") {

                    break;
                }
            }
            if (choice == "q") {
                break;
            }
        }
        std::cout << "Number of successfull answers is: " << counter << std::endl;
        std::cout << "Number of NOT successfull answers is: " << inc << std::endl;
        std::cout << "MOl weight score is: " << score << std::endl;
        float total = counter + score;
        std::cout << "total score is " << total << std::endl;
        ProteinSports::display(x);
        std::cout << "Bye bye"<< std::endl;
    }





protected:
    std::vector<std::string> aaavec = {
        "Ala", "Cys", "Asp", "Glu", "Phe",
        "Gly", "His", "Ile", "Lys", "Leu",
        "Met", "Asn", "Pro", "Gln", "Arg",
        "Ser", "Thr", "Val", "Trp", "Tyr"
    } ;
    std::vector<std::string> avec   = {
        "A","C","D","E","F",
        "G","H","I","K","L",
        "M","N","P","Q","R",
        "S","T","V","W","Y"
    } ;
    std::vector<float> aweight = {
        71.08, 103.14,115.09,129.12,147.18,
        57.05, 137.14,113.16,128.17,113.16,
        131.19, 114.10, 97.12, 128.13, 156.19,
        87.08, 101.11, 99.13, 186.21, 163.18
    } ;
};



//int  main(int argc, char **argv){
//	ProteinSports ps=ProteinSports();
//	ps.menu();
//	return 0;
//}

// loop for tabular display
// https://www.tutorialride.com/cpp-structure-programs/display-student-details-in-tabular-form-c.htm
