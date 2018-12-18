#include <iostream>
#include <stdint.h>
#include <string>
#include "i_type.hpp"

using namespace std;
//int32_t u32Int;
extern uint8_t RAM[67108864];
extern uint8_t ROM[16777216];


int32_t i_type(int8_t operation, int32_t source_reg,int32_t dest_reg, int16_t immediate){

	// ANDI Instruction
	uint32_t temp;
	if (operation == 12){
		return( source_reg & immediate);
	}
	//ADDI
	else if (operation == 8) {
		uint32_t copy_source = unsigned(source_reg);
		int64_t test_overflow = 0;
		int32_t test = 0;
		test =  (uint64_t) copy_source + (uint64_t) immediate;
		test_overflow = (uint64_t)  copy_source + (uint64_t) immediate;
		/* - more testing
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
	
		//temp = source_reg + immediate;
	}
	//ADDIU
	else if (operation == 9){
		return immediate + source_reg;
	}
	 // Yet to finish
	else if (operation == 32){ // Load Byte
			// In this case our Immediate is our Offset.
			// EXCEPTIONS : TLB Refill, TLB Invalid and Address Error.
			int32_t address = source_reg + immediate;
			if (address > 67108864){
			// Return an address error;	
			}
			else {	
			return RAM[address];
			}
			// Insert an check for outside of memory;
			//dest_reg = RAM[];
		
	}

	else if (operation == 36){ // Load Byte Unsigned
			// In this case our Immediate is our Offset.
			// EXCEPTIONS : TLB Refill, TLB Invalid and Address Error.
			int32_t address = source_reg + immediate;
			if (address > 67108864){
			// Return an address error;	
			}
			else {	
			return RAM[address];
			}
			// Insert an check for outside of memory;
			//dest_reg = RAM[];
		
	} /// NEED TO CHECK ALL OF THESE
	//ANDI
	else if (operation == 12){
		return immediate & source_reg;
	}
	//ORI
	else if (operation == 13){
		return immediate | source_reg;
	}
	//XORI
	else if (operation == 14){
		return immediate ^ source_reg;
	}

	else if (operation == 15){ // Load Upper Immediate
		temp = (immediate << 16);
		temp = temp & 0xFFFF0000;
		return temp;
	
	}
	
	else if (operation == 33){ // Load Half-Word 
	
		int32_t address = ((source_reg + immediate)*4); // Since we have split the memory into from 32 bits to 8 bits;
		if ((address%2)== 0){ 
		if (address > 67108864){
			// Return an address error;	
			exit(-11);
			}
			else {	
	
			int16_t result = RAM[address]<<8;
			result += RAM[address+1];
			}
		}
		else {
			exit(-11);
		}
	}
	
	else if (operation == 37){ // Load Half-Word Unsigned
	
		int32_t address = ((source_reg + immediate)*4); // Since we have split the memory into from 32 bits to 8 bits;
		if ((address%2)== 0){ 
		if (address > 67108864){
			// Return an address error;	
			exit(-11);
			}
			else {	
	
			uint16_t result = RAM[address]<<8;
			result += RAM[address+1];
			}
		}
		else {
			exit(-11);
		}
	}
	
	//// ALL OF THESE NEED TO BE CHECK PROPERLY
	// Error check for address on the next 3 instructions
	else if (operation == 35){ // Load Word 
	
		int32_t address = ((source_reg + immediate)*4); // Since we have split the memory into from 32 bits to 8 bits;
		if ((address%4)== 0){ 
		if (address > 67108864){
			// Return an address error;	
			exit(-11);
			}
			else {	
	
			int32_t result = RAM[address]<<24;
			result += RAM[address+1]<<16;
			result += RAM[address+2]<<8;
			result += RAM[address+3];
			}
		}
		else {
			exit(-11);
		}
	}
	else if (operation == 40){ // Store Byte
		int32_t address = (source_reg + immediate)*4;
		if ((address%4)== 0){ 
		if (address > 67108864){
			// Return an address error;
			exit(-11);	
		}
			else {	
	
				RAM[address] = dest_reg;
			}
		}
		else {
			exit(-11);
		}
	}

	else if (operation == 43){ // Store Word
		int32_t address = (source_reg + immediate)*4;
	if ((address%4)== 0){ 
		if (address > 67108864){
			// Return an address error;	
			exit(-11);
		}
		else {	
			RAM[address] = ((dest_reg >> 24) & 0xff);
			RAM[address+1] = ((dest_reg >> 16) & 0xff);
			RAM[address+2] = ((dest_reg >> 8) & 0xff);
			RAM[address+3] = ((dest_reg) & 0xff);
		}
	}
		else {
			exit(-11);
		}
	}
	else if (operation == 10){ // SLTI
		int16_t temp = immediate;
		return source_reg < temp;
	}
	else if (operation == 11){ // SLTIU
		uint16_t temp = immediate;
		return source_reg < temp;
	}
	
	else{ //invalid instruction catch
		exit(-12);
	}
}

