#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
using namespace std;




class ProteinSports{
	public:
	void a2aaa();
	void aaa2a();
	int randint(int min, int max);
	void menu();
	private:
	array<string, 20> triple {"Ala", "Cys", "Asp", "Glu", "Phe", "Gly", "His", "Ile", "Lys", "Leu", "Met", "Asn", "Pro", "Gln", "Arg", "Ser", "Thr", "Val", "Trp", "Tyr"};
	array<string, 20> single {"A","C","D","E","F","G","H","I","K","L","M","N","P","Q","R","S","T","V","W","Y"};
	array< float, 20> weights {71.08, 103.14,115.09,129.12, 147.18,57.05, 137.14,113.16, 128.17,113.16,131.19, 114.10, 97.12, 128.13,  156.19, 87.08, 101.11, 99.13, 186.21, 163.18};
	int n_aminos = sizeof(single) / sizeof(single[0]);
	//cout << n_aminos;
};


void ProteinSports::a2aaa(){
	cout << "test a2aaa \n";
	;
}

void ProteinSports::aaa2a(){
	cout << "test aaa2a \n";

}
	
void ProteinSports::menu(){
	cout << "test menu \n";
        string choice = "";

        while (choice != "t" && choice != "s" && choice != "q") {
            cout << " (s)ingle letter a2aaa, (t)riplett aaa2a, or (q)uit:" << endl;
            cin >> choice;
            cout << endl;

            if (choice == "t") {
                aaa2a();
            } 
            if (choice == "s") {
                a2aaa();
            } 
            if (choice == "q") {
                break;
            } 
        }
}



int ProteinSports::randint(int min, int max) {
    if (min == max) {
        return (min);
    }

    cout << "test"<< time(NULL) << endl;

    srand((int) time(NULL));

    int rnd = rand();

    int len = max - min;

    rnd = (rnd % len + 1) + min;
    cout << rnd;
    return (rnd);
}

	

int main(){
	ProteinSports ps;
	ps.a2aaa();
	ps.aaa2a();
	ps.menu();
	return(0);
}
