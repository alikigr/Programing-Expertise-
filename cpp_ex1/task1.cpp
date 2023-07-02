#include <iostream>
// nhello.cpp - compile with: "g++ -o nhello nhello.cpp"


void helloworld(int times=10){
	for (int i = 0; i < times; i++) {
		std::cout << "Hello, World!" << std::endl;
	}
}


int main( ) {
	helloworld(3);
	return 0;
}
