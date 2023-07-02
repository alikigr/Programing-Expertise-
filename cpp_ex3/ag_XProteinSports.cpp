#include <string>
#include <map>
#include "ag_ProteinSports.cpp"


class XProteinSports : public ProteinSports {
public:
    void menu(int num, std::string pre_choice/*, std::string pre_peptide*/) {
        std::cout << "Hi! I am the menu. Welcome to the proteins sports game!" << std::endl;
        //int n_question;
        //if (num != NULL){
        //	n_question = num;
        //}
        //else{
        //std::cout << "Hi! I am a menu! \nHow many times would you like to try the guessing game?" << std::endl;
        //std::cin >> n_question;
        //}
        std::cout << "How many seconds would you like to have for answering every question?" << std::endl;
        int user_time;
        std::cin >> user_time;
        int counter = 0;
        int inc = 0;
        float score = 0;

        std::vector<int> x;

        for (int try_number = 1; try_number <= num; try_number ++) {

            std::string choice = "";
            int ra = ProteinSports::random_aa();
            x.push_back(ra);

            while (choice != "t" && choice != "s" && choice != "m" && choice != "q" && choice != "d") {

                if (pre_choice != "") {
                    choice = pre_choice;
                }
                else {

                    std::cout << "(s)ingle letter a2aaa, (t)riplett aaa2a, (m)olecular  weight, hy(d)ropathy, weight of (p)eptide or (q)uit:" << std::endl;
                    std::cin >> choice;
                }

              if (choice == "p") {
					std::string peptide;
                    std::cout << "Please type in the peptide of which you want to know the molecular weight." << std::endl;
                    std::cin>> peptide;
                    

                    float wsol;
                    wsol = XProteinSports::aastringweight(peptide);
                    std::cout << "The molecular weight of the peptide " << peptide << " is " << wsol << "." << std::endl;
                }

                if (choice == "d") {

                    std::string aaa= aaavec[ra];
                    std::cout << "Is the amino acid " << aaa << " hydropath? \n Reply with yes, no or neu." << std::endl;
                    //std::cout << ProteinSports::aaa2a(aaa)  << std::endl;
                    std::string aaa_answer= "";
                    start_time();
                    std::cin>> aaa_answer;
                    bool in_time = check_time(user_time);
                    if (aaa_answer == XProteinSports::aa2hydropathy(aaa) && in_time) {
                        std::cout << "\033[1;32mcorrect\033[0m\n";
                        counter ++;
                    }
                    else if(aaa_answer == XProteinSports::aa2hydropathy(aaa) && !in_time) {
                        std::cout << "\033[1;33mCorrect, but try typing faster!\033[0m\n" << std::endl;;
                    }
                    else {
                        std::cout << "\033[1;31mwrong\033[0m\n";
                        inc ++;
                    }

                }

                if (choice == "s") {

                    std::string aaa= aaavec[ra];
                    std::cout << "What is the amino acid " << aaa << " in single code?" << std::endl;
                    //std::cout << ProteinSports::aaa2a(aaa)  << std::endl;
                    std::string aaa_answer= "";
                    start_time();
                    std::cin>> aaa_answer;
                    bool in_time = check_time(user_time);
                    if (aaa_answer == XProteinSports::aaa2a(aaa) && in_time) {
                        std::cout << "\033[1;32mcorrect\033[0m\n";
                        counter ++;
                    }
                    else if(aaa_answer == ProteinSports::aaa2a(aaa) && !in_time) {
                        std::cout << "\033[1;33mCorrect, but try typing faster!\033[0m\n" << std::endl;;
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
                    start_time();
                    std::cin>> a_answer;
                    bool in_time = check_time(user_time);
                    if (a_answer == ProteinSports::a2aaa(a) && in_time) {
                        std::cout << "\033[1;32mcorrect\033[0m\n";
                        counter  ++;
                    }
                    else if(a_answer == ProteinSports::a2aaa(a) && !in_time) {
                        std::cout << "\033[1;33mCorrect, but try typing faster!\033[0m\n" << std::endl;;
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
                    start_time();
                    std::cin>> molw_answer;
                    bool in_time = check_time(user_time);


                    if ((molw_answer>=min) &&  (molw_answer <= max) && in_time) {
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
                    else if((molw_answer>=min) &&  (molw_answer <= max) && !in_time) {
                        std::cout << "\033[1;33mCorrect, but try typing faster!\033[0m\n" << std::endl;;
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
        XProteinSports::display(x);
        std::cout << "Bye bye"<< std::endl;
    }


    std::string aa2hydropathy(std::string aa) {
        if (aa.length()==3) {
            aa=aaa2a(aa);
        }

        return(aa2hydropath[aa]);
    }

    void display(std::vector<int> x) {

        std::cout << "single \t" << "triple \t" << "molecular weight " << "\t" << "hydropathy" << std::endl;
        for(int i=0; i<x.size(); i++) {

            auto elm = x[i];
            std::cout << avec[elm]<< "\t" <<  aaavec[elm] << "\t" << ProteinSports::getWeight(avec[elm]) << "\t \t \t " <<  XProteinSports::aa2hydropathy(aaavec[elm])<< std::endl;
        }
    }


    float aastringweight(std::string aastr) {
        float sum=0;

        for (auto as : aastr) {
            std::string s(1, as);
            auto w = ProteinSports::getWeight(s);
            sum=sum+w;
        }
        return sum;
    }


private:
    std::map<std::string, std::string> aa2hydropath = {
        {"A","yes"},{"C","yes"},{"D","no"},{"E","no"},
        {"F","yes"},{"G","neu"},{"H","neu"},{"I","yes"},
        {"K","no"},{"L","yes"},{"M","yes"},{"N","no"},
        {"P","neu"},{"Q","no"},{"R","no"},{"S","neu"},
        {"T","neu"},{"V","yes"},{"W","yes"},{"Y","neu"}
    };


protected:
    time_t last_start_time;
    int maxtime = 5;

    void start_time() {
        last_start_time = time(NULL);
        //std::cout << last_start_time << std::endl;
    }

    bool check_time(int max_time=5) {
        time_t diff_time = time(NULL) - last_start_time;
        if (diff_time <= max_time) {
            return (true);
        }
        return (false);
    }
};




