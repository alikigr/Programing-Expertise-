#include <iostream>
#include <stdlib.h>
using namespace std;


int addition() {
	int number1, number2, sum, answer;
	int range = 200 - 10 + 1;
	srand(time(0));
	number1 = rand() % range + 10;
	number2 = rand() % range + 10;
	sum = number1 + number2;
	int count;
	
	cout<< "What is "<< number1 << " + " << number2 << "?\n";
	cin >> answer ;
	if (answer == sum){
		cout << "correct" << endl;
		count = 1;
	} else {
		cout << "incorrect" << endl;
		count = 0;
	}
	return(count);
}

int  substraction() {
	int number1, number2, sub, answer;
	srand(time(0));
	number1 = (rand()%10) + 1;
	number2 = (rand()%10) + 1;
	sub = number1 - number2;
	int count ;
	
	cout<< "What is "<< number1 << " - " << number2 << "?\n";
	cin >> answer ;
	if (answer == sub){
		cout << "correct" << endl;
		count = 1;
	} else {
		cout << "incorrect" << endl;
		count = 0;
	}
	return(count);
}


int prime(){
	
	int i, n;
	string answer;
	int count ; 
	int is_prime = 1;
	
	int range = 200 - 1 + 1;
	srand(time(0));
	n =  rand() % range + 1;
	
	cout << "Is " << n << " a prime number? (y)es or (n)o? \n";
	cin >> answer;
	
	//calculate if n is prime or not
	if (n == 1) {
	is_prime = 0;
	}

  // loop to check if n is prime
	for (i = 2; i <= n/2; ++i) {
	if (n % i == 0) {
		is_prime = 0;
		break;
		}
	}

	if (is_prime == 1){
		if (answer == "y")
		{
		cout << "correct" << endl;
		count = 1 ;
		}
		else
		{
			cout << "incorrect" << endl;
			count = 0;
		}
	}
	if(is_prime == 0){
		if (answer == "n")
		{
		cout << "correct" << endl;
		count = 1 ;
		}
		else
		{
			cout << "incorrect" << endl;
			count = 0;
		}
	}
	//cout << count;
	return(count);
}


int fib() {
	int  first = 0, second = 1, next;
	int N, res, answer, count;
	
	int range = 10 - 1 + 1;
	srand(time(0));
	N =  rand() % range + 1;
	
	
	for (int Index = 0; Index < N; Index++){
		if (Index <= 1){
			next = Index;
		}
		else
		{
			next = first + second;
			first = second;
			second = next;
		}
			//cout << next << ' ';
	}
	res = next;
	//cout << "Value of chosen term is:" << res;
	cout << "What is the value of the the " << N << "th term in the fib seq? \n" ;
	cin >> answer;
	
	if (answer == res){
		cout << "correct" << endl;;
		count = 1;
		}
	else{
		cout << "incorrect"<< endl;;
		count = 0;
	}
	return(count);
}

int square(){
	int number, res, answer;
	srand(time(0));
	number = rand() %10;

	res = number*number;
	int count;
	
	cout<< "What is the square of the "<< number << "?\n";
	cin >> answer ;
	if (answer == res){
		cout << "correct" << endl;
		count = 1;
	} else {
		cout << "incorrect" << endl;
		count = 0;
	}
	return(count);
}


void menu(int n_question = 10) {
	cout << "How many times would you like to try? \n";
	cin >> n_question;
	char count_a, count_s, count_p; 
	int total_counter = 0;
	for (int try_number = 1; try_number <= n_question; try_number ++) {
		
		string choice = "";
		
		while (choice != "a" && choice != "s" && choice != "q") {
			cout << "Try #" << try_number << ", choose (a)ddition, (s)ubstraction, (p)rime or (q)uit:" << endl;
			cin >> choice;
			cout << endl;
			
			if (choice == "p") {
				count_p = prime();
				if (count_p == 1){
					total_counter = total_counter +1;
					} 
				}
			if (choice == "s") {
				count_s = substraction() ;
				if (count_s ==1) {
					total_counter = total_counter +1;
					}
				}
			if (choice == "a") {
				count_a = addition();
				if (count_a == 1){
					total_counter = total_counter +1;
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
	cout << "Number of successfull answers is: " << total_counter << "\n";
		
	string goon = "";
	cout << "Would you like to continue with fibonacci and square exercises? (y)es or (n)o \n";
	cin >> goon;
	if (goon == "n"){
		exit(1);
		}
	cout << "How many times would you like to try? \n";
	cin >> n_question;
		
	char count_f, count_r;
	int total_counter_2 = 0;
		
	for (int try_number = 1; try_number <= n_question; try_number ++) {
		
		string choice = "";
		
		while (choice != "f" && choice != "r" && choice != "q") {
			cout << "Try #" << try_number << ", choose (f)ibonacci, squa(r)e or (q)uit:" << endl;
			cin >> choice;
			cout << endl;
			
			if (choice == "f") {
				count_f = fib();
				if (count_f == 1){
					total_counter_2 = total_counter_2 +1;
					} 
				}
			if (choice == "r") {
				count_r = square() ;
				if (count_r ==1) {
					total_counter_2= total_counter_2 +1;
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
	cout << "Number of successfull answers is: " << total_counter_2 << "\n";
}



int main(){
	menu(4);
}
