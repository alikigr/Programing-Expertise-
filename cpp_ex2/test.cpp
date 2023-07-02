#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include<bits/stdc++.h>

int randint(int min, int max) {
    if (min == max) {
        return (min);
    }

    std::cout << time(NULL) << std::endl;

    srand((int) time(NULL));

    int rnd = rand();

    int len = max - min;

    rnd = (rnd % len + 1) + min;

    return (rnd);
}

int main(){
	std::cout << randint(1,20) << std::endl;
	return 0;
	}
