#ifndef _AESHW_H
#define _AESHW_H

#include <cstdio>
#include <cstring>
#include <cstdint>

class AESHW
{
public:
	AESHW();
	AESHW(const uint8_t key[], const size_t length=16);
	~AESHW();
	void encrypt(const uint8_t in[16], uint8_t out[16]);
	void decrypt(const uint8_t in[16], uint8_t out[16]);
    void printkey();

//private:
	// used for GF28
	uint8_t table[256];
	uint8_t arc_table[256];

	// SBOX and inverse SBOX;
    static const uint8_t SBox[256];
    static const uint8_t invSBox[256];
    
    static const uint32_t rcon[];
    static const uint8_t mixcolumn[16];
    static const uint8_t invmixcolumn[16];
    
    typedef enum {
        LEFT,
        RIGHT
    }SHIFT;

    typedef enum{
        ENCRYPT,
        DECRYPT
    }OPET;

	// Secret key, the length of which can be 16, 24, 32bytes.
	size_t len_key;
	uint8_t AES_key[32];
	uint32_t Expended_key[44];
	int Num_round;//128bit = 10, 192 bit = 12, 256 bit = 16
	int Num_column; // = 4 at 128bit
	
	void init_table();
	void keyExpansion();
    void Shift_Rows(uint8_t state[16], OPET opt);
    void Sub_Bytes(uint8_t state[16], OPET opt);
    void printarray(const uint8_t array[16], int label);
    
    inline void GET_UINT8(const uint32_t in, uint8_t output[4]);
    
	inline uint32_t GET_UINT32(uint8_t * const array, const int pos);
	inline uint32_t SUB32(const uint32_t in);
    // array[pos+3] | array[pos+2] | array[pos+1] | array[pos]
	inline uint8_t SUB8(const uint8_t in);

	void line_shift(uint8_t array[4], const int n);// right shift. Left shift = 4 - n
    void RoundKey(uint8_t state[16], int round);// round = 0 ~ 10, 11 rounds in total
    void MixColumn(uint8_t state[16], OPET operation);
    
    uint8_t GF28Multi(const uint8_t x, const uint8_t y);
    uint32_t shift(const uint32_t in, SHIFT opt, int n);
	
};

#endif
