#include<iostream> //Required for std_in and std_out
#include<fstream> //Required to read from files
#include<cstdlib> //Required for exit
#include <stdint.h> //Required for uint_t type
#include <vector>
#include <string>
#include <stdlib.h> 
#include <cmath>
#include <cstdio>
using namespace std;



int main(int argc, char *argv[]){ //Arg stuff added for command line inputs

	vector<uint32_t>instruction_set;
	
	ifstream bin_in;
	
	bin_in.open(argv[1], ios::binary); //the first parameter will be name / location of bin
	
	if(!(bin_in.is_open())){ //if not opened then return error
		cout<<"Error, binary not found"<<endl; 
		exit(-21);//error should be this type, I think?
	}
	//Now to read it
	char a;
	vector<char> set;// Array of characters
	string input;
	//index starts at 0
	int i = 0; // Number of inputs
	// gets the value from the binary file 
	
	//cout << "The size of the file :" << bin_in.tellg() << endl;
	while(bin_in.get(a)){
		set.push_back(a);	
	i++;
	}
	
	bin_in.close();
	// Cheeky bit of testing for each byte;
	for(int k = 0; k<i; k++){
		//printf ("0x%X\n", set[k]);
	}
	
	int no_inputs = i/4;
	
	// The process from combining the 4 char files into one single 32 bit number;
	int32_t byte1 = 0,byte2 = 0 ,byte3 = 0,byte4 = 0,total = 0;
	
	for (int j =0; j <no_inputs; j++){ 
	
	byte1 = set[0 + (no_inputs*j)] << 24;
	byte2 = set[1 + (no_inputs*j)] << 16;
	byte3 = set[2 + (no_inputs*j)] << 8;
	byte4 = set[3 + (no_inputs*j)];
	total = (byte1 | byte2 | byte3 | byte4);
	cout << "Value of the Data Stored: " << total << endl;
	instruction_set.push_back(total);
	byte1 = 0;byte2 = 0;byte3 = 0;byte4 = 0;total = 0;
	}
	
	/* Cheeky bit of testing the number input.
	cout << "The number of inputs : " << i << endl;  
	cout << "Value of the total " << total << endl;
	
	cout << "Value of the total " << byte1 << endl; 
	 
	cout << "Value of the total " << byte2 << endl;
	 
	cout << "Value of the total " << byte3 << endl;
	 
	cout << "Value of the total " << byte4 << endl;
	*/
	return 0;
}


