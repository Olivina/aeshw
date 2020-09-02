#include "aeshw.h"

const uint8_t AESHW::SBox[256] =
{ // 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //a
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //b
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //c
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //d
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //e
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  //f
};

const uint8_t AESHW::invSBox[256] =
{ // 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, //0
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, //1
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, //2
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, //3
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, //4
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, //5
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, //6
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, //7
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, //8
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, //9
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, //a
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, //b
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, //c
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, //d
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, //e
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d  //f
};

const uint32_t AESHW::rcon[] =
{
    0x1000000, 0x2000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000 // 10
};

const uint8_t AESHW::mixcolumn[16] = // 4 * 4
{
    0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x03, 0x01, 0x01, 0x02
};

const uint8_t AESHW::invmixcolumn[16] = // 4 * 4
{
    0x0e, 0x0b, 0x0d, 0x09, 0x09, 0x0e, 0x0b, 0x0d, 0x0d, 0x09, 0x0e, 0x0b, 0x0b, 0x0d, 0x09, 0x0e
};

AESHW::AESHW(){
	uint8_t key[16] = {
        0x3c, 0xa1, 0x0b, 0x21,
        0x57, 0xf0, 0x19, 0x16,
        0x90, 0x2e, 0x13, 0x80,
        0xac, 0xc1, 0x07, 0xbd
    };
    memcpy(AES_key, key, 16);// 16 bytes.
    memset(Expended_key, 0, sizeof(Expended_key));
    init_table();
    keyExpansion();
}

void AESHW::printkey(){
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            printf(" 0x%02x ", AES_key[4 * i + j]);
        }
        printf("\n");
    }
    printf("Done\n");
}

AESHW::AESHW(const uint8_t key[], const size_t length){// normally length = 16
	len_key = length;
	memcpy(AES_key, key, length);
	memset(Expended_key, 0, sizeof(Expended_key));
	init_table();
	keyExpansion();
}

uint8_t AESHW::GF28Multi(const uint8_t x, const uint8_t y){
	if(!x || !y)
		return 0;
	return table[ (arc_table[x] + arc_table[y]) % 255];
}

inline uint32_t AESHW::GET_UINT32(uint8_t * const array, const int pos=0){
    return ( (array[pos] << 24) | (array[pos+1] << 16) | (array[pos+2] << 8 ) | array[pos+3] );
    // uint32_t = A[pos] | A[pos+1] | A[pos+2] | A[pos+3]
}
inline void AESHW::GET_UINT8(const uint32_t in, uint8_t output[4]){
	output[0] = (in >> 24) & 0xff;
	output[1] = (in >> 16) & 0xff;
	output[2] = (in >> 8) & 0xff;
	output[3] = in & 0xff;
}

void AESHW::line_shift(uint8_t array[4], const int n){// right shift. left shift = 4 - n.
	if (n == 0)
		return;
	int temp;
	for(int i = 0; i < n; ++i){
		temp = array[3];
		array[3] = array[2];
		array[2] = array[1];
		array[1] = array[0];
		array[0] = temp;
	}
}

void AESHW::MixColumn(uint8_t state[16], OPET operation){
	const uint8_t * mixcum;
    // so far the state is the same
    uint8_t temp[16]={};
    if(operation == ENCRYPT){
        mixcum = mixcolumn;
    }
    else{
        mixcum = invmixcolumn;
    }
	for (int i = 0; i < 4; ++i){
		for(int j = 0; j < 4; ++j){
            uint8_t temp1 = GF28Multi(mixcum[4 * i], state[j]);
            uint8_t temp2 = GF28Multi(mixcum[4 * i + 1], state[4 + j]);
            uint8_t temp3 = GF28Multi(mixcum[4 * i + 2], state[8 + j]);
            uint8_t temp4 = GF28Multi(mixcum[4 * i + 3], state[12 + j]);
            temp[4 * i + j] = temp1 ^ temp2 ^ temp3 ^ temp4;
		}
	}
    memcpy(state, temp, sizeof(temp));
}

uint32_t AESHW::shift(const uint32_t in, SHIFT opt, int n){
	if (n % 8){
        printf("n = %d\n", n);
        printf("n must be 8k!\n");
        return 0;
    }
    uint32_t a, b, c, d;
    if(opt == RIGHT) n = 32 - n;
    // consider all cases as left shift
    switch(n){
        case 8:
            c = 0xff000000;
            d = 0xff;
            break;
        case 16:
            c = 0xffff0000;
            d = 0xffff;
            break;
        case 24:
            c = 0xffffff00;
            d = 0xffffff;
            break;
        default:
            c = 0xffffffff;
            d = 0xffffffff;
            printf("n has a wrong value\n");
            break;
    }
    b = c & in;// extract first n bit
    a = in;
    a <<= n;
    b >>= (32-n);
    return a | (b & d);
}

void AESHW::init_table(){
	table[0] = 1;
	for(int i = 1; i < 255; ++i){ //g = x + 1
		// m_table[ i ] = m_table[ i - 1 ] * ( x + 1 )
		table[i] = (table[i - 1] << 1) ^ table[ i - 1 ];// in GP28, ^ means multiply.

		// if x8(table[i]) = 1, that is, x7(table[i-1]) = 1, then mod f(x) = x^8 + x^4 + x^3 + x + 1.
		// A convenient operation is to plus x^4 + x^3 + x + 1, that is, ^ 0x1b (= ^ 0001 1011)
		if(table[i-1] & 0x80)// 1000 0000
		{
			table[i] ^= 0x1b;
		}
	}

	for(int i = 0; i < 255; ++i){// inverse table;
		arc_table[ table[i] ] = i;
	}
	return;
}

inline uint8_t AESHW::SUB8(const uint8_t in){
	return SBox[in];
}

inline uint32_t AESHW::SUB32(const uint32_t in){
	uint32_t a = ((uint32_t)SUB8((uint8_t)((in >> 24) & 0xff))) << 24;
	uint32_t b = (uint32_t)(SUB8((uint8_t)((in >> 16) & 0xff))) << 16;
	uint32_t c = (uint32_t)(SUB8((uint8_t)((in >> 8) & 0xff))) << 8;
	uint32_t d = (uint32_t)(SUB8((uint8_t)(in & 0xff)));
	return a | b | c | d;
}

void AESHW::keyExpansion(){
    for(int i = 0; i < 4; i ++)
    {
        Expended_key[i] = GET_UINT32(AES_key, i << 2);// 4 * i
        // printf("Expended_key[%d] = %x\n", i, Expended_key[i]);
    }
    // w[0], w[1], w[2], w[3];
    for (int i = 4; i < 44; i ++)
    {
        if( (i % 4) == 0) // 4k
        {
            //1. left shift
            Expended_key[i] = Expended_key[i-4] ^ SUB32(shift(Expended_key[i-1], LEFT, 8)) ^ rcon[(i / 4) - 1];
        }
        else // 4k + m
        {
            Expended_key[i] = Expended_key[i-1] ^ Expended_key[i-4];
        }
//        printf("Expended_key[%d] = %x\n", i, Expended_key[i]);
    }
}

void AESHW::RoundKey(uint8_t state[16], int round){// round = 0 ~ 10 // 11 round in total
	int position = round * 4;// position, position +1, position +2, position +3
	uint8_t temp[16];
	for(int i = 0; i < 4; ++i){// transport
		temp[i * 4] = state[i];
		temp[i * 4 + 1] = state[ 4 + i ];
		temp[i * 4 + 2] = state[ 8 + i ];
		temp[i * 4 + 3] = state[ 12 + i ];
	}
	uint32_t temp2[4];
	temp2[0] = GET_UINT32(temp) ^ Expended_key[position];
	temp2[1] = GET_UINT32(temp, 4) ^ Expended_key[position + 1];
	temp2[2] = GET_UINT32(temp, 8) ^ Expended_key[position + 2];
	temp2[3] = GET_UINT32(temp, 12) ^ Expended_key[position + 3];

	GET_UINT8(temp2[0], temp);
	GET_UINT8(temp2[1], temp +4);
	GET_UINT8(temp2[2], temp +8);
	GET_UINT8(temp2[3], temp +12);

	for(int i = 0; i < 4; ++i){
		state[i * 4] = temp[i];
		state[i * 4 + 1] = temp[4 + i];
		state[i * 4 + 2] = temp[8 + i];
		state[i * 4 + 3] = temp[12 + i];
	}
}

void AESHW::Shift_Rows(uint8_t state[16], OPET opt){
    if(opt == ENCRYPT){
        //    line_shift(array, 0);
        line_shift(state + 4, 3);
        line_shift(state + 8, 2);
        line_shift(state + 12, 1);
        return;
    }
    else{
        //    line_shift(array, 0);
        line_shift(state + 4, 1);
        line_shift(state + 8, 2);
        line_shift(state + 12, 3);
    }

}

void AESHW::Sub_Bytes(uint8_t state[16], OPET opt){
    int a, b, c, d;
    const uint8_t * sb;
    if(opt == ENCRYPT){
        sb = SBox;
    }
    else{
        sb = invSBox;
    }
    for(int i = 0; i < 16; i += 4){
        a = state[i];
        b = state[i+1];
        c = state[i+2];
        d = state[i+3];
        state[i] = sb[a];
        state[i+1] = sb[b];
        state[i+2] = sb[c];
        state[i+3] = sb[d];
    }
}

void AESHW::encrypt(const uint8_t in[16], uint8_t out[16]){
    uint8_t state[16];
    for(int i = 0; i < 4; ++i){// transport
        state[i * 4] = in[i];
        state[i * 4 + 1] = in[ 4 + i ];
        state[i * 4 + 2] = in[ 8 + i ];
        state[i * 4 + 3] = in[ 12 + i ];
    }
    RoundKey(state, 0);
    for(int i = 1; i <= 10; ++i){
        Sub_Bytes(state, ENCRYPT);
        Shift_Rows(state, ENCRYPT);
        if(i != 10){
            MixColumn(state, ENCRYPT);
        }
        RoundKey(state, i);
    }
    for(int i = 0; i < 4; ++i){// transport
        out[i * 4] = state[i];
        out[i * 4 + 1] = state[ 4 + i ];
        out[i * 4 + 2] = state[ 8 + i ];
        out[i * 4 + 3] = state[ 12 + i ];
    }
    return;
}

void AESHW::printarray(const uint8_t array[16], int label){
    printf("point %d =\n", label);
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            printf(" 0x%02x ", array[i* 4 + j]);
        }
        printf("\n");
    }
}

void AESHW::decrypt(const uint8_t in[16], uint8_t out[16]){
    uint8_t state[16];
    for(int i = 0; i < 4; ++i){// transport
        state[i * 4] = in[i];
        state[i * 4 + 1] = in[ 4 + i ];
        state[i * 4 + 2] = in[ 8 + i ];
        state[i * 4 + 3] = in[ 12 + i ];
    }

    RoundKey(state, 10);
    
    for(int i = 9; i >=0; --i){
        Shift_Rows(state, DECRYPT);
        Sub_Bytes(state, DECRYPT);
        RoundKey(state, i);
        if(i){
            MixColumn(state, DECRYPT);
        }
    }
    for(int i = 0; i < 4; ++i){// transport
        out[i * 4] = state[i];
        out[i * 4 + 1] = state[ 4 + i ];
        out[i * 4 + 2] = state[ 8 + i ];
        out[i * 4 + 3] = state[ 12 + i ];
    }
    return;
    
}

AESHW::~AESHW(){}
