#include <iostream>
#include <stdint.h>
#include <string>
#include "r_type.hpp"

using namespace std;
//int32_t u32Int;
extern uint8_t RAM[67108864];
extern uint8_t ROM[16777216];

int32_t r_type(int32_t reg1, int32_t reg2, int8_t shift, int8_t function){
	int32_t temp =0;
	
	if (function == 33){ // ADDU - doesn't need to track overflow //
		return (reg1 + reg2);
	}
	// Now we have access to all the individual locations 

	else if (function == 36) { // AND -Bitwise Logical AND 
		return (reg1 & reg2);
	}

	else if ( function == 37){ // OR - Bitwise Logical OR
		return (reg1 | reg2);
	}

	else if ( function == 38){ // XOR - Bitwise Logical OR
		return (reg1 ^ reg2);
	}

	else if ( function == 35){ // SUBU - Bitwise Logical OR
		return (reg1 - reg2);
	}

	else if ( function == 43){ // SLTU - Set on Less Than Unsigned
		return (reg1 < reg2);
	}

	else if (function == 32){ // ADD - with overflow;
	
		uint32_t copy_reg1 = unsigned(reg1);
		uint32_t copy_reg2 = unsigned(reg2);
		int64_t test_overflow = 0;
		int32_t test = 0;
		test =  (uint64_t) copy_reg1 + (uint64_t) copy_reg2;
		test_overflow = (uint64_t) copy_reg1 + (uint64_t) copy_reg2;
		/* Checking the output works correctly
		cout << "The value of register 1: " << reg1 << endl;
		cout << "The value of register 2: " << reg2 << endl;
		cout << "The value of 32 bits: " << test << endl;
		cout << "The value of 64 bits: " << test_overflow << endl;
		*/ 
		if (test!=test_overflow){
			//Flag an overflow.
		}
		else {
			return test;
		}
	}
	else if (function == 0){ // Shift Word Left Logical
		return (reg2 << shift);

	}

	else if (function == 4){ // Shift Word Left Logical Variable
		return (reg2<<(reg1&0x1f));

	}
	else if (function == 2){ // Logical Word Right Shift
		uint32_t temp = reg2;
		temp = temp >> shift;
		return temp;

	}
	else if (function == 6){ // Shift Word Right Logical Variable
		uint32_t temp = reg2;
		int8_t s = ((reg1 >> 21) & 0x1f);
		temp = temp >> s;
		return temp;
		
	}
	else if (function == 3){ // Shift Word Right Arithmetic
	
		return (reg2 >> shift); 
	}

	else if (function == 7) {// Shift Word Right Arithmetic Variable
		int8_t s = ((reg1 >> 21) & 0x1f);
		temp = reg2 >> s;
		return temp;
	}
	else if (function == 2){
		temp = reg2 >> shift;
		return temp;
	} 
	
	else if (function == 34){ // sub, signed and thus overflow
		int32_t result;
		//check for overflow
		if(reg1<0){
			if(reg1<(reg2+INT32_MIN)){//bad, overflow case
				exit(-10); // exit program with correct error code
			}
		}
		else if (reg1>=0){
			if(reg1>(INT32_MAX+reg2)){// bad, overflow case
				exit(-10);
			}
		}
		return (reg1-reg2); //will only reach this point if no overflow
	}
	
	else if(function == 35){//subu, no overflow case
		return(reg1-reg2); // no need to check for overflow
	}
	else if (function == 42){
		return (reg1 < reg2);
	}
	else if (function == 43){
		uint32_t temp1 = reg1;
		uint32_t temp2 = reg2;
		return temp1 < temp2;
	}
	else{ // invalid function
		exit(-12);
	}
	
}
int64_t r_type_long(int32_t reg1, int32_t reg2, int8_t function){
	int32_t LO;
	int64_t result;
	uint32_t HIu, LOu, reg1u, reg2u; // registers 1 and 2 might need to be unsigned as LO. HI contains quotient, is always unsigned
	uint64_t resultu;
	reg1u= unsigned(reg1);
	reg2u = unsigned(reg2);
	if(function ==26){ //div
	
		//divide by 0 is undefined
		//define result of divide by 0 as 0
		
		if(reg2==0){
			return 0;
		}	
	
		LO = reg1/reg2; // LO is the quotient
		HIu = reg1u%reg2u; // HI is the remainder / modulo and is always unsigned
		
		result = int64_t(LO) <<32; // the upper half of the result should be LO
		result = result +int64_t (HIu); // the lower half of the result should be HI
		
		return result;
	}
	
	else if(function ==27){//divu
	
		//divide by 0 is undefined
		//define result of divide by 0 as 0
		if(reg2==0){
			return 0;
		}	
		
		LOu = reg1u/reg2u; // LO is the quotient
		HIu = reg1u%reg2u; // HI is the remained / modulo
		//cerr<<"Lou is "<<LOu<<" and Hiu is "<<HIu<<endl;
		result = int64_t(LOu) <<32; // the upper half of the result should be LO
		result = result +int64_t( HIu); // the lower half of the result should be HI
		//cerr<<"result is "<<result<<endl;
		return result;
	}
	else if(function ==24){//mult
		result = (int64_t(reg1)*int64_t(reg2));
		return result;
	}
	else if(function == 25){//multu
		resultu = (uint64_t(reg1u)*uint64_t(reg2u));
		//cerr<<"DEBUG, reg1 is "<< reg1u<< "reg2 is "<< reg2u << "and resultu is "<< resultu<<endl;
		return resultu;
	}
	else{ // invalid function
		exit(-12);
	}
}
		






















