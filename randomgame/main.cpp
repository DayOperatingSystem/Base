#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>

#define VERSION "3.11"

using namespace std;

int main(int argc, char* argv[])
{
	unsigned int seed = syscall1(15, 0);			
	srand(seed);
	cout << "Got seed " << seed << endl;
	
	cout << "Random Number Game v" << rand() % 9 << "." << rand() % 999 << endl;
	
	unsigned int number = rand();
	unsigned int inputNumber = 0;

	char buffer[512];
	
	while(inputNumber != number)
	{
		cout << "Input a number: ";
		//cin >> inputNumber;
		//fgets(buffer, sizeof(buffer), stdin);    
		gets(buffer);	
		inputNumber = atoi(buffer);

		if(inputNumber > number)
			cout << "Your number is greater than my one" << endl;
		else if(inputNumber < number)
			cout << "Your number is smaller than my one" << endl;
	}

	cout << "You won!" << endl;
	
	return 0;
}
