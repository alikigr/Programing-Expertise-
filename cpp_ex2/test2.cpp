#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
using namespace std;

int main(){
    vector<int> v;
    //Insert values 1 to 10
    for(int i=1;i<=10;i++){
        v.push_back(i);
	}


    for(int i=0;i<v.size();i++){
        cout << v[i] << " ";
        cout << "\n";
    }
    //Prints [4 5 6 8 9 10]
    while(v.size() != 0){
	    int random = rand()%v.size();
		int sel_elem = v[random];
		v.erase(v.begin()+random);
		std::cout<<"Selected Element: "<<sel_elem<< std::endl;
	}
   return 0;
}
