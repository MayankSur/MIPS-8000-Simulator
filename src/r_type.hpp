#include <iostream>
#include <stdint.h> 

int32_t r_type(int32_t reg1, int32_t reg2, int8_t shift, int8_t function);

int64_t r_type_long(int32_t reg1, int32_t reg2, int8_t shift, int8_t function); //rtype but for when we output two words

