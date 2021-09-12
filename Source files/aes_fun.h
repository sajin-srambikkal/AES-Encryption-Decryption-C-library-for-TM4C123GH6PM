//Embedded Project


#define AES_BIT 128


#if AES_BIT==128
    #define KEY_SIZE 176
    #define ROUND 10
#elif AES_BIT==192
    #define KEY_SIZE 208
    #define ROUND 12
#elif AES_BIT==256
    #define KEY_SIZE 240
    #define ROUND 14
#else
    #define KEY_SIZE 176
    #define ROUND 10
#endif

unsigned char Key[KEY_SIZE];
unsigned char state[16];//State vector
unsigned char state_temp[16];


//Key Expansion function
void Key_Expansion(unsigned char* key );
int rotate_word(unsigned num, int num_rotate);
int Sub_word(int num);
void Add_Round_key(unsigned char* message, unsigned char* key, unsigned char* state);
void Sub_byte(unsigned char* state);
void Sub_byte_rotate(unsigned char * state, unsigned char* state_temp );
void  Mix_column (void);
char Gallois_Mul(char a, char b);
void Sub_byte_rotate_dec(unsigned char * state);
void  Mix_column_dec (void);


void Key_Expansion(unsigned char* key );
void AES_Encrypt(unsigned char* Message,unsigned char* Result);
void AES_Decrypt(unsigned char* Message,unsigned char* Result);
void Encrypt_Message_ECB(char* Message, int Message_Length,char* Result);
void Encrypt_Message_CBC(char* Message, int Message_Length,char* Result);
void Decrypt_Message_ECB(char* Message, int Message_Length,char* Result);
void Decrypt_Message_CBC(char* Message, int Message_Length,char* Result);
