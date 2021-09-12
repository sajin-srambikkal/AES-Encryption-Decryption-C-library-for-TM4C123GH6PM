#include "aes_fun.h"

unsigned char sbox[]= {
        0x63 ,0x7c ,0x77 ,0x7b ,0xf2 ,0x6b ,0x6f ,0xc5 ,0x30 ,0x01 ,0x67 ,0x2b ,0xfe ,0xd7 ,0xab ,0x76
       ,0xca ,0x82 ,0xc9 ,0x7d ,0xfa ,0x59 ,0x47 ,0xf0 ,0xad ,0xd4 ,0xa2 ,0xaf ,0x9c ,0xa4 ,0x72 ,0xc0
       ,0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15
       ,0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75
       ,0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84
       ,0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf
       ,0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8
       ,0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2
       ,0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73
       ,0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb
       ,0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79
       ,0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08
       ,0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a
       ,0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e
       ,0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf
       ,0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16};

unsigned char sboxInv[] = {
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

unsigned char E_tab[] ={
      0x01, 0x03, 0x05, 0x0F, 0x11, 0x33, 0x55, 0xFF, 0x1A, 0x2E, 0x72, 0x96, 0xA1, 0xF8, 0x13, 0x35,
      0x5F, 0xE1, 0x38, 0x48, 0xD8, 0x73, 0x95, 0xA4, 0xF7, 0x02, 0x06, 0x0A, 0x1E, 0x22, 0x66, 0xAA,
      0xE5, 0x34, 0x5C, 0xE4, 0x37, 0x59, 0xEB, 0x26, 0x6A, 0xBE, 0xD9, 0x70, 0x90, 0xAB, 0xE6, 0x31,
      0x53, 0xF5, 0x04, 0x0C, 0x14, 0x3C, 0x44, 0xCC, 0x4F, 0xD1, 0x68, 0xB8, 0xD3, 0x6E, 0xB2, 0xCD,
      0x4C, 0xD4, 0x67, 0xA9, 0xE0, 0x3B, 0x4D, 0xD7, 0x62, 0xA6, 0xF1, 0x08, 0x18, 0x28, 0x78, 0x88,
      0x83, 0x9E, 0xB9, 0xD0, 0x6B, 0xBD, 0xDC, 0x7F, 0x81, 0x98, 0xB3, 0xCE, 0x49, 0xDB, 0x76, 0x9A,
      0xB5, 0xC4, 0x57, 0xF9, 0x10, 0x30, 0x50, 0xF0, 0x0B, 0x1D, 0x27, 0x69, 0xBB, 0xD6, 0x61, 0xA3,
      0xFE, 0x19, 0x2B, 0x7D, 0x87, 0x92, 0xAD, 0xEC, 0x2F, 0x71, 0x93, 0xAE, 0xE9, 0x20, 0x60, 0xA0,
      0xFB, 0x16, 0x3A, 0x4E, 0xD2, 0x6D, 0xB7, 0xC2, 0x5D, 0xE7, 0x32, 0x56, 0xFA, 0x15, 0x3F, 0x41,
      0xC3, 0x5E, 0xE2, 0x3D, 0x47, 0xC9, 0x40, 0xC0, 0x5B, 0xED, 0x2C, 0x74, 0x9C, 0xBF, 0xDA, 0x75,
      0x9F, 0xBA, 0xD5, 0x64, 0xAC, 0xEF, 0x2A, 0x7E, 0x82, 0x9D, 0xBC, 0xDF, 0x7A, 0x8E, 0x89, 0x80,
      0x9B, 0xB6, 0xC1, 0x58, 0xE8, 0x23, 0x65, 0xAF, 0xEA, 0x25, 0x6F, 0xB1, 0xC8, 0x43, 0xC5, 0x54,
      0xFC, 0x1F, 0x21, 0x63, 0xA5, 0xF4, 0x07, 0x09, 0x1B, 0x2D, 0x77, 0x99, 0xB0, 0xCB, 0x46, 0xCA,
      0x45, 0xCF, 0x4A, 0xDE, 0x79, 0x8B, 0x86, 0x91, 0xA8, 0xE3, 0x3E, 0x42, 0xC6, 0x51, 0xF3, 0x0E,
      0x12, 0x36, 0x5A, 0xEE, 0x29, 0x7B, 0x8D, 0x8C, 0x8F, 0x8A, 0x85, 0x94, 0xA7, 0xF2, 0x0D, 0x17,
      0x39, 0x4B, 0xDD, 0x7C, 0x84, 0x97, 0xA2, 0xFD, 0x1C, 0x24, 0x6C, 0xB4, 0xC7, 0x52, 0xF6, 0x01
};

unsigned char L_TAB[]={
      0x00, 0x00, 0x19, 0x01, 0x32, 0x02, 0x1A, 0xC6, 0x4B, 0xC7, 0x1B, 0x68, 0x33, 0xEE, 0xDF, 0x03,
      0x64, 0x04, 0xE0, 0x0E, 0x34, 0x8D, 0x81, 0xEF, 0x4C, 0x71, 0x08, 0xC8, 0xF8, 0x69, 0x1C, 0xC1,
      0x7D, 0xC2, 0x1D, 0xB5, 0xF9, 0xB9, 0x27, 0x6A, 0x4D, 0xE4, 0xA6, 0x72, 0x9A, 0xC9, 0x09, 0x78,
      0x65, 0x2F, 0x8A, 0x05, 0x21, 0x0F, 0xE1, 0x24, 0x12, 0xF0, 0x82, 0x45, 0x35, 0x93, 0xDA, 0x8E,
      0x96, 0x8F, 0xDB, 0xBD, 0x36, 0xD0, 0xCE, 0x94, 0x13, 0x5C, 0xD2, 0xF1, 0x40, 0x46, 0x83, 0x38,
      0x66, 0xDD, 0xFD, 0x30, 0xBF, 0x06, 0x8B, 0x62, 0xB3, 0x25, 0xE2, 0x98, 0x22, 0x88, 0x91, 0x10,
      0x7E, 0x6E, 0x48, 0xC3, 0xA3, 0xB6, 0x1E, 0x42, 0x3A, 0x6B, 0x28, 0x54, 0xFA, 0x85, 0x3D, 0xBA,
      0x2B, 0x79, 0x0A, 0x15, 0x9B, 0x9F, 0x5E, 0xCA, 0x4E, 0xD4, 0xAC, 0xE5, 0xF3, 0x73, 0xA7, 0x57,
      0xAF, 0x58, 0xA8, 0x50, 0xF4, 0xEA, 0xD6, 0x74, 0x4F, 0xAE, 0xE9, 0xD5, 0xE7, 0xE6, 0xAD, 0xE8,
      0x2C, 0xD7, 0x75, 0x7A, 0xEB, 0x16, 0x0B, 0xF5, 0x59, 0xCB, 0x5F, 0xB0, 0x9C, 0xA9, 0x51, 0xA0,
      0x7F, 0x0C, 0xF6, 0x6F, 0x17, 0xC4, 0x49, 0xEC, 0xD8, 0x43, 0x1F, 0x2D, 0xA4, 0x76, 0x7B, 0xB7,
      0xCC, 0xBB, 0x3E, 0x5A, 0xFB, 0x60, 0xB1, 0x86, 0x3B, 0x52, 0xA1, 0x6C, 0xAA, 0x55, 0x29, 0x9D,
      0x97, 0xB2, 0x87, 0x90, 0x61, 0xBE, 0xDC, 0xFC, 0xBC, 0x95, 0xCF, 0xCD, 0x37, 0x3F, 0x5B, 0xD1,
      0x53, 0x39, 0x84, 0x3C, 0x41, 0xA2, 0x6D, 0x47, 0x14, 0x2A, 0x9E, 0x5D, 0x56, 0xF2, 0xD3, 0xAB,
      0x44, 0x11, 0x92, 0xD9, 0x23, 0x20, 0x2E, 0x89, 0xB4, 0x7C, 0xB8, 0x26, 0x77, 0x99, 0xE3, 0xA5,
      0x67, 0x4A, 0xED, 0xDE, 0xC5, 0x31, 0xFE, 0x18, 0x0D, 0x63, 0x8C, 0x80, 0xC0, 0xF7, 0x70, 0x07
};



// unsigned char Key[]= {0x45, 0x6D, 0x62, 0x65, 0x64, 0x64, 0x65, 0x64, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x73, 0x31,
 //                      0x45, 0x6D, 0x62, 0x65, 0x64, 0x64, 0x65, 0x64, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x73, 0x32}; // key = embeddedsystems1embeddedsystems2


//unsigned char Key[]= {0x45, 0x6D, 0x62, 0x65, 0x64, 0x64, 0x65, 0x64, 0x73, 0x79, 0x73, 0x74, 0x65,
//                            0x6D, 0x73, 0x31,0x6D, 0x69 ,0x6E, 0x69}; // key = embeddedsystems1miniproj

unsigned char Key[]={0x45, 0x6D, 0x62, 0x65, 0x64, 0x64, 0x65, 0x64, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x73, 0x31}; // key = embeddedsystems1

//unsigned char Key[]= {0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6D, 0x79, 0x20, 0x4B, 0x75, 0x6E, 0x67, 0x20, 0x46, 0x75};

unsigned char IV[]={0xd1, 0xaf, 0x4a, 0xf9, 0xb4, 0x21, 0x02, 0x9e, 0xce, 0x4c,  0x15, 0xd8, 0x8a, 0xad, 0xb8, 0x45 };

void Key_Expansion(unsigned char* key)
{
//function store the expanded keys to Key_Ex //little endianess of ARM is assumed
//if big endian small changes requried
// for 16 byte KEY
#if AES_BIT==128
    int* temp1=(int *)key;
    int temp= *(temp1+3);
    int* store=temp1+4;
    int temp2=0x00000001;
    for (int i=0; i<ROUND;i++)
    {
      temp=rotate_word(temp,8); // cyclic change with 32 bit
      temp=Sub_word(temp);     //  substituing the word from sbox
      temp=temp ^ temp2;      // xoring -------------------------
      *store=*(temp1)^temp;  //
      *(store+1)=*(temp1+1)^*(store);
      *(store+2)=*(temp1+2)^*(store+1);
      *(store+3)=*(temp1+3)^*(store+2);

      temp1=store;
      temp=*(store+3);
      store=store+4;
      if(i==7)
          temp2=0x0000001b;
      else temp2=temp2<<1;
    }

#elif AES_BIT==192
      int* temp1=(int *)key;
      int temp= *(temp1+5);
      int* store=temp1+6;
      int temp2=0x00000001;
      for (int i=0; i<8;i++)
      {
        temp=rotate_word(temp,8); // cyclic change with 32 bit
        temp=Sub_word(temp);     //  substituing the word from sbox
        temp=temp ^ temp2;      // xoring -------------------------
        *store=*(temp1)^temp;  //
        *(store+1)=*(temp1+1)^*(store);
        *(store+2)=*(temp1+2)^*(store+1);
        *(store+3)=*(temp1+3)^*(store+2);
        if(i!=7)
            {
            *(store+4)=*(temp1+4)^*(store+3);
            *(store+5)=*(temp1+5)^*(store+4);
            }
        temp1=store;
        temp=*(store+5);
        store=store+6;
        temp2=temp2<<1;
      }
#elif AES_BIT==256
            int* temp1=(int *)key;
            int temp= *(temp1+7);
            int* store=temp1+8;
            int temp2=0x00000001;
            for (int i=0; i<7;i++)
            {
              temp=rotate_word(temp,8); // cyclic change with 32 bit
              temp=Sub_word(temp);     //  substituing the word from sbox
              temp=temp ^ temp2;      // xoring -------------------------
              *store=*(temp1)^temp;  //
              *(store+1)=*(temp1+1)^*(store);
              *(store+2)=*(temp1+2)^*(store+1);
              *(store+3)=*(temp1+3)^*(store+2);
              if(i!=6){
              *(store+4)=*(temp1+4)^Sub_word(*(store+3));
              *(store+5)=*(temp1+5)^*(store+4);
              *(store+6)=*(temp1+6)^*(store+5);
              *(store+7)=*(temp1+7)^*(store+6);
              }
              temp1=store;
              temp=*(store+7);
              store=store+8;
              temp2=temp2<<1;
            }
#else
    int* temp1=(int *)key;
      int temp= *(temp1+3);
      int* store=temp1+4;
      int temp2=0x00000001;
      for (int i=0; i<ROUND;i++)
      {
        temp=rotate_word(temp,8); // cyclic change with 32 bit
        temp=Sub_word(temp);     //  substituing the word from sbox
        temp=temp ^ temp2;      // xoring -------------------------
        *store=*(temp1)^temp;  //
        *(store+1)=*(temp1+1)^*(store);
        *(store+2)=*(temp1+2)^*(store+1);
        *(store+3)=*(temp1+3)^*(store+2);

        temp1=store;
        temp=*(store+3);
        store=store+4;
        if(i==7)
            temp2=0x0000001b;
        else temp2=temp2<<1;
      }
#endif

};

int rotate_word(unsigned int num, int num_rotate)
{
    return ((num>>num_rotate)|(num<<(32-num_rotate)));
};

int Sub_word(int num)
{
char *temp = (char *)(&num);
for(int i=0; i <4 ;i++)
{
  *temp=sbox[(int)(*temp)];
  temp++;
}
return num;
};

void AES_Encrypt(unsigned char* Message,unsigned char* Result)
{

unsigned char * temp=Key+16;
//Zero round------------------------------
Add_Round_key(Message,Key,state);
//------------------------------------------
// First round----------------------------
//Sub_byte(state);
for (int i=0; i<(ROUND-1);i++)
{
Sub_byte_rotate(state, state_temp);
Mix_column();
Add_Round_key(state,temp,state);
temp=temp+16;
}
Sub_byte_rotate(state, state_temp);
Add_Round_key(state_temp,temp,Result);

}

void Add_Round_key(unsigned char* message, unsigned char* key, unsigned char* state)
{
int *a = (int *)message; //mapping integer pointer to message array or state array
int *b = (int *)key    ; // mapping key starting address to integer pointer
int *c = (int *)state  ; // mapping state to the integer pointer
*(c) = *(a) ^ *(b);
*(c+1) = *(a+1) ^ *(b+1);
*(c+2) = *(a+2) ^ *(b+2);
*(c+3) = *(a+3) ^ *(b+3);
}



void Sub_byte_rotate(unsigned char * state, unsigned char* state_temp )
{
    *(state_temp)=sbox[(int)(*(state))];
    *(state_temp+4)=sbox[(int)(*(state+4))];
    *(state_temp+8)=sbox[(int)(*(state+8))];
    *(state_temp+12)=sbox[(int)(*(state+12))];
    *(state_temp+1)=sbox[(int)(*(state+5))];
    *(state_temp+5)=sbox[(int)(*(state+9))];
    *(state_temp+9)=sbox[(int)(*(state+13))];
    *(state_temp+13)=sbox[(int)(*(state+1))];
    *(state_temp+2)=sbox[(int)(*(state+10))];
    *(state_temp+6)=sbox[(int)(*(state+14))];
    *(state_temp+10)=sbox[(int)(*(state+2))];
    *(state_temp+14)=sbox[(int)(*(state+6))];
    *(state_temp+3)=sbox[(int)(*(state+15))];
    *(state_temp+7)=sbox[(int)(*(state+3))];
    *(state_temp+11)=sbox[(int)(*(state+7))];
    *(state_temp+15)=sbox[(int)(*(state+11))];
}

void  Mix_column (void)
{
char a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3;
unsigned char * temp=state_temp;
unsigned char * temp1=state;
for (int i=0;i<4;i++)
{   a1=*(temp);
    b1=*(temp+1);
    c1=*(temp+2);
    d1=*(temp+3);
    if(a1==0x00)
        {a2=0x00;a3=0x00;}
    else
        {a2= Gallois_Mul(a1,2) ;
         a3= Gallois_Mul(a1,3) ;
        }

    if(b1==0x00)
            {b2=0x00;b3=0x00;}
    else
            {b2= Gallois_Mul(b1,2) ;
             b3= Gallois_Mul(b1,3) ;
            }

    if(c1==0x00)
            {c2=0x00;c3=0x00;}
    else
            {c2= Gallois_Mul(c1,2) ;
             c3= Gallois_Mul(c1,3) ;
            }
    if(d1==0x00)
            {d2=0x00;d3=0x00;}
    else
            {d2= Gallois_Mul(d1,2) ;
             d3= Gallois_Mul(d1,3) ;
            }

    *temp1=     a2^ b3^ c1^ d1 ;
    *(temp1+1)= a1^ b2^ c3^ d1 ;
    *(temp1+2)= a1^ b1^ c2^ d3 ;
    *(temp1+3)= a3^ b1^ c1^ d2 ;
    temp1=temp1+4;
    temp= temp+4;
}
}

char Gallois_Mul(char a, char b)
{
int a1= L_TAB[(int)a]+L_TAB[(int)b];
if (a1>0xFF) a1=a1-0xFF;
return E_tab[a1];
}


//Functions for Decryption
void AES_Decrypt(unsigned char* Message,unsigned char* Result)
{

unsigned char * temp=Key;

#if AES_BIT==128
    temp=temp+160;
#elif AES_BIT==192
    temp=temp+192;
#elif AES_BIT==256
    temp=temp+224;
#elif
    temp=temp+160;
#endif

//Zero round------------------------------
Add_Round_key(Message,temp,state);
Sub_byte_rotate_dec(state); //result in state_temp
temp=temp-16;
for (int i=0; i<(ROUND-1);i++)
{
Add_Round_key(state_temp,temp,state_temp);//result in state_temp
Mix_column_dec(); //giving result in state
Sub_byte_rotate_dec(state);//result in state_temp
temp=temp-16;
}
//Sub_byte_rotate_dec(state);
Add_Round_key(state_temp,temp,Result);

}



void Sub_byte_rotate_dec(unsigned char * state)
{
    *(state_temp)=sboxInv[(int)(*(state))];
    *(state_temp+4)=sboxInv[(int)(*(state+4))];
    *(state_temp+8)=sboxInv[(int)(*(state+8))];
    *(state_temp+12)=sboxInv[(int)(*(state+12))];
    *(state_temp+1)=sboxInv[(int)(*(state+13))];
    *(state_temp+5)=sboxInv[(int)(*(state+1))];
    *(state_temp+9)=sboxInv[(int)(*(state+5))];
    *(state_temp+13)=sboxInv[(int)(*(state+9))];
    *(state_temp+2)=sboxInv[(int)(*(state+10))];
    *(state_temp+6)=sboxInv[(int)(*(state+14))];
    *(state_temp+10)=sboxInv[(int)(*(state+2))];
    *(state_temp+14)=sboxInv[(int)(*(state+6))];
    *(state_temp+3)=sboxInv[(int)(*(state+7))];
    *(state_temp+7)=sboxInv[(int)(*(state+11))];
    *(state_temp+11)=sboxInv[(int)(*(state+15))];
    *(state_temp+15)=sboxInv[(int)(*(state+3))];

      }

void  Mix_column_dec (void)
{
char a,b,c,d,a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4;
unsigned char * temp=state_temp; //input
unsigned char * temp1=state; //output
for (int i=0;i<4;i++)
{   a=*(temp);
    b=*(temp+1);
    c=*(temp+2);
    d=*(temp+3);
    if(a==0x00)
        {a1=0;a2=0x00;a3=0x00;a4=0;}
    else
        {
         a1= Gallois_Mul(a,9) ;
         a2= Gallois_Mul(a,11) ;
         a3= Gallois_Mul(a,13) ;
         a4= Gallois_Mul(a,14) ;
        }

    if(b==0x00)
            {b1=0;b2=0x00;b3=0x00;b4=0;}
    else
            {
            b1= Gallois_Mul(b,9) ;
            b2= Gallois_Mul(b,11) ;
             b3= Gallois_Mul(b,13) ;
             b4= Gallois_Mul(b,14) ;
            }

    if(c==0x00)
            {c1=0;c2=0x00;c3=0x00;c4=0;}
    else
            {
            c1= Gallois_Mul(c,9) ;
            c2= Gallois_Mul(c,11) ;
             c3= Gallois_Mul(c,13) ;
             c4= Gallois_Mul(c,14) ;
            }
    if(d==0x00)
            {d1=0;d2=0x00;d3=0x00;d4=0;}
    else
            {
            d1= Gallois_Mul(d,9) ;
            d2= Gallois_Mul(d,11) ;
             d3= Gallois_Mul(d,13) ;
             d4= Gallois_Mul(d,14) ;
            }

    *temp1=     a4^ b2^ c3^ d1 ;
    *(temp1+1)= a1^ b4^ c2^ d3 ;
    *(temp1+2)= a3^ b1^ c4^ d2 ;
    *(temp1+3)= a2^ b3^ c1^ d4 ;
    temp1=temp1+4;
    temp= temp+4;
}

}


void Encrypt_Message_ECB(char* Message, int Message_Length,char* Result)
{

int padding=0;
//assumption the memory is allocated to near 16 multiple
unsigned char *msg= Message;
unsigned char *result = Result;
int block_num= Message_Length/16;

if(Message_Length%16!=0)
{
    padding=16-(Message_Length%16);
    for(int i=0;i<padding;i++)
    {
        *(Message+Message_Length+i)=0x00;
    }

}
else
{
    block_num=block_num-1;
}

//encryption
for (int i=0;i<=block_num;i++)

{    AES_Encrypt(msg,result);
    msg=msg+16;
    result=result+16;
}

 }



void Encrypt_Message_CBC(char* Message, int Message_Length,char* Result)
{

int padding=0;
//assumption the memory is allocated to near 16 multiple
unsigned char *msg= Message;
unsigned char *res = Result;
int block_num= Message_Length/16;

if(Message_Length%16!=0)
{
    padding=16-(Message_Length%16);
    for(int i=0;i<padding;i++)
    {
        *(Message+Message_Length+i)=0x00;
    }

}
else
{
    block_num=block_num-1;
}
//encryption

Add_Round_key(msg,IV,state);
for (int i=0;i<=block_num;i++)
{
    AES_Encrypt(state,res);
    msg=msg+16;
    Add_Round_key(msg,res,state);
    res=res+16;
}
}


void Decrypt_Message_ECB(char* Message, int Message_Length,char* Result)
{
    unsigned char *msg= Message+Message_Length-16;
    unsigned char *res = Result+Message_Length-16;
    int block_num= Message_Length/16;
    block_num=block_num-1;


    for (int i=0;i<=block_num;i++)
    {
        AES_Decrypt(msg,res);
        msg=msg-16;
        res=res-16;
    }


}

void Decrypt_Message_CBC(char* Message, int Message_Length,char* Result)
{

    unsigned char *msg= Message+Message_Length-16;
    unsigned char *res = Result+Message_Length-16;
    int block_num= Message_Length/16;
    block_num=block_num-1;



    for (int i=0;i<=block_num;i++)
    {
        AES_Decrypt(msg,state);
        msg=msg-16;
        if(i!=block_num)
        {Add_Round_key(msg,state,res);
        res=res-16;
        }

    }

    Add_Round_key(state,IV,res);
}

