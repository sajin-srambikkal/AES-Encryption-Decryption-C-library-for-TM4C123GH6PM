#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/uart.h>
#include "aes_fun.h"

unsigned char Message[128]={0x54, 0x77, 0x6F, 0x20, 0x4F, 0x6E, 0x65, 0x20, 0x4E, 0x69, 0x6E, 0x65, 0x20, 0x54, 0x77, 0x6F};
unsigned char Result[128]={};

char string[40];

void send_message( char *string);
void send_message_HEX( char *string);
char int_to_hex(int x);
void Init_UART(void);
void receive_message(char *string);
void send_message2( char *string);
void String_Control(char * string);
void substring(char *string, char *p, int position, int length);
void save_char_data(char* str,int index);
void save_hex_data(char* str, int index);
void uart_put_int(int freq);

int msg_length=0;
int count=0;
void Init_Systick(void);
void DisableInterrupts(void);
void Systick_INT_Handler();

int main()
{
    Init_UART();
    send_message2( "Example for AES Encryption");
    send_message("Encrypting MSG");
    send_message(Message);
    send_message_HEX(Message);
    send_message("Encrypted MSG");
    Key_Expansion(Key);
    AES_Encrypt(Message,state);
    send_message((state));
    send_message_HEX(state);
    send_message("Decrypted MSG");
    AES_Decrypt(state,state);
    send_message((state));
    send_message_HEX(state);


    while(1)
    {
        receive_message(string);
        send_message2( string);
        String_Control(string);


    }
return 0;
}




void send_message( char *string)
{
    int i=0;
UARTCharPut(UART0_BASE, '\n');
while(*string)
{
    i++;
    UARTCharPut(UART0_BASE, *(string++));
    if (i==16)
        break;

}
UARTCharPut(UART0_BASE, '\n');
UARTCharPut(UART0_BASE, 13); // Carriage Return
}


void send_message_HEX( char *string)
{
    char hex_display[48]="00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ";
    int y,x,k,z;
    int i=0;
    k=1;
    while(1)
    {    i=i+1;
        y=*(string++);
        z=y;
        while(y!=0)
        {
            x=y%16;
            hex_display[k]=int_to_hex(x);
            k=k-1;

            y=y/16;
            }
        k=k+5;
        if(z==0)k=k-2;
        else if(z<16)k=k-1;
        if(i==16)
            break;
    }
    k=0;
     while(k<=47)
     {
         if(k%3!=2)
             {UARTCharPut(UART0_BASE, hex_display[k]);
              }
         k=k+1;
     }
     UARTCharPut(UART0_BASE, '\n');
     UARTCharPut(UART0_BASE, 13);




}


char int_to_hex(int x)
{

char hex_display;
if ((x>=0) && (x<=9))
       hex_display=x+48;
else
       hex_display=x+97-10;
return hex_display;
}

void Init_UART(void)
{
    SYSCTL_RCGCUART_R |= 1;         /* provide clock to UART0 */
    SYSCTL_RCGCGPIO_R |= 0x01;      /* enable clock to GPIO_PORTA */

    /* UART0 initialization */
    UART0_CTL_R = 0;                /* disable UART0 */
    UART0_IBRD_R = 8;               /* Setting baud rate for 115200 */
    UART0_FBRD_R = 44;              /*  */
    UART0_CC_R = 0;                 /* use system clock */
    UART0_LCRH_R = 0x60;            /* 8-bit, no parity, 1-stop bit, no FIFO */
    UART0_CTL_R = 0x301;            /* enable UART0, TXE, RXE */

    /* UART0 TX0 and RX0 use PA0 and PA1. Set them up. */
    GPIO_PORTA_DEN_R = 0x03;        /* Make PA0 and PA1 as digital */
    GPIO_PORTA_AFSEL_R = 0x03;      /* Use PA0,PA1 alternate function */
    GPIO_PORTA_PCTL_R = 0x11;       /* configure PA0 and PA1 for UART */

    // Setting the Interrupt and priority
      /*  UART0_ICR_R=0x10;
        UART0_IM_R |= 0x10;
        NVIC_PRI1_R = (NVIC_PRI1_R & 0xFFFF1FFF) | 0x0000A000;
        NVIC_EN0_R=0x00000020; // enabling UART Interrupt*/
}


void receive_message(char *string)
{
    char val;
    char val1;
    int k=0;
    msg_length=0;
    do{
    while(!(UARTCharsAvail(UART0_BASE)));
    val = UARTCharGet(UART0_BASE);
    UARTCharPut(UART0_BASE, val);
    if(val==8)
    { *string='\0';
        string--;
    }

    else if(k<=10){
         if((val<=57 & val>=48)|| (val<=90 & val>=65)||(val<=122 & val>=97) )
        {
            if ( (val >= 97) & (val <= 122) & k!=10 )
                    val1=val-32;
            else
                val1=val;

            *string =val1;
             string++;
             k=k+1;
        }

    }
    else
    {
        *string =val;
         string++;
         msg_length=msg_length+1;

    }

    }while(val!=13);
        *string='\0';
}


void send_message2( char *string)
{
UARTCharPut(UART0_BASE, '\n');
while(* string)
{
    UARTCharPut(UART0_BASE, *(string++));

}
UARTCharPut(UART0_BASE, '\n');
UARTCharPut(UART0_BASE, 13); // Carriage Return
}


void String_Control(char * string)
{
        char p[20];       //string to subdivide
        char *a;
        char time1[20];
        int k;
        int time11,time12;
        int time_Diff;

       // int zz=0;
        char memory_address[20];
        char no_of_byte[20];


        if(strcmp(string,"HELP")==0)
                        {
                            send_message2("Following are the commands supported");
                            send_message2("1) Encrypt STR/HEX MESSAGE IN STRING/HEX FORMAT (16 byte long) ");
                            send_message2("2) Decrypt STR/HEX MESSAGE IN STRING/HEX FORMAT (16 byte long) ");
                            send_message2("3) Encrypt ECB Message_in_string");
                            send_message2("4) Encrypt CBC Message_in_string");
                            send_message2("5) Decrypt ECB Message in Hex (multiple of 16 byte)");
                            send_message2("6) Decrypt CBC Message in Hex (multiple of 16 byte)");

                        }

        else
        {substring(string,p,1,7);

          if(strcmp(p,"ENCRYPT")==0)
          {
              substring(string,p,8,3);
              if (strcmp(p,"ECB")==0)
              {
                  save_char_data(Message,10);
                  Encrypt_Message_ECB(Message,msg_length,Result);
                  send_message2( "Message Recieved for encryption");
                  int block_num= msg_length/16;
                  a=Message;
                  for (int i=0;i<=block_num;i++)
                  {
                      send_message(a);
                      send_message_HEX(a);
                      a=a+16;
                  }

                  send_message2( "Message Encrypted: ECB Mode");
                  a=Result;
                  for (int i=0;i<=block_num;i++)
                   {
                    send_message(a);
                    send_message_HEX(a);
                    a=a+16;
                  }

              }


              else if (strcmp(p,"CBC")==0)
                           {
                               save_char_data(Message,10);
                               Encrypt_Message_CBC(Message,msg_length,Result);
                               send_message2( "Message Recieved for encryption");
                               int block_num= msg_length/16;
                               a=Message;
                               for (int i=0;i<=block_num;i++)
                               {
                                   send_message(a);
                                   send_message_HEX(a);
                                   a=a+16;
                               }

                               send_message2( "Message Encrypted: CBC Mode");
                               a=Result;
                               for (int i=0;i<=block_num;i++)
                                {
                                 send_message(a);
                                 send_message_HEX(a);
                                 a=a+16;
                               }

                           }


              else{
              if(strcmp(p,"STR")==0)
              {

                  save_char_data(Message,10);
              }
              else if(strcmp(p,"HEX")==0)
              {
                  save_hex_data(Message,10);

              }
              Init_Systick();
              time11=NVIC_ST_CURRENT_R;
              AES_Encrypt(Message,Result);
              time12=NVIC_ST_CURRENT_R;
              __asm ("    CPSID  I\n");
              NVIC_ST_CTRL_R = 0;
              send_message2( "Message Recieved for encryption");
              send_message(Message);
              send_message_HEX(Message);
              send_message2( "Encrypted Message");
              send_message(Result);
              send_message_HEX(Result);
              send_message2( "Time taken for encryption");
              uart_put_int(time11-time12);}



          }
          else if(strcmp(p,"DECRYPT")==0)
          {
            substring(string,p,8,3);
            if (strcmp(p,"ECB")==0)
              {
                  save_hex_data(Result,10);
                  Decrypt_Message_ECB(Result,msg_length/2,Message);
                  send_message2( "Message Recieved for decryption");
                  int block_num= msg_length/32;
                  block_num=block_num-1;
                  a=Result;
                  for (int i=0;i<=block_num;i++)
                  {
                      send_message(a);
                      send_message_HEX(a);
                      a=a+16;
                  }

                  send_message2( "Message decrypted: ECB Mode");
                  a=Message;
                  for (int i=0;i<=block_num;i++)
                   {
                    send_message(a);
                    send_message_HEX(a);
                    a=a+16;
                  }

              }


              else if (strcmp(p,"CBC")==0)
                           {
                              save_hex_data(Result,10);
                               Decrypt_Message_CBC(Result,msg_length/2,Message);
                               send_message2( "Message Recieved for decryption");
                               int block_num= msg_length/32;
                               block_num=block_num-1;
                               a=Result;
                               for (int i=0;i<=block_num;i++)
                               {
                                   send_message(a);
                                   send_message_HEX(a);
                                   a=a+16;
                               }

                               send_message2( "Message Decrypted: CBC Mode");
                               a=Message;
                               for (int i=0;i<=block_num;i++)
                                {
                                 send_message(a);
                                 send_message_HEX(a);
                                 a=a+16;
                               }

                           }



            else{
            if(strcmp(p,"STR")==0)
            {
                save_char_data(Message,10);

            }
            else if(strcmp(p,"HEX")==0)
            {
                save_hex_data(Message,10);

            }

            send_message2( "Message Recieved for decryption");
            send_message(Message);
            send_message_HEX(Message);
            Init_Systick();
            time11=NVIC_ST_CURRENT_R;
            AES_Decrypt(Message,Result);
            time12=NVIC_ST_CURRENT_R;
            __asm ("    CPSID  I\n");
            NVIC_ST_CTRL_R = 0;
            send_message2( "Decrypted Message");
            send_message(Result);
            send_message_HEX(Result);
            send_message2( "Time taken for decryption");
            uart_put_int(time11-time12);

          }

          }
        }



}

void substring(char *string, char *p, int position, int length)
{
   int c;

   for (c = 0; c < length; c++)
   {
      *(p+c) = *(string+position-1);
      string++;
   }

   *(p+c) = '\0';

}


void save_hex_data(char* str, int index)
{
char buff[3];
char* a;
char val;
char * address=str;
int k=0;
while(k<(msg_length/2))
{
    a=buff;//
    *a  =*(string+index);
            a++;
    *a=*(string+index+1);
    a++;
    *a='\0';//a="e8""00"
   val= (char)(strtol(buff,&a,16));//int of (16*e+8)
   *address= val;
   *address++;
   index= index+2;

   k=k+1;
}

}

void save_char_data(char* str,int index)
{
char * address=str;
while(*(string+index))
{
*address =   *(string+index);
index=index+1;
address++;
}
*address='\0';

}



void Init_Systick(void)
{
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 0xFFFFFFFF;
    NVIC_ST_CTRL_R = 7;             /* enable SysTick interrupt, use system clock */
    count=0;
    NVIC_SYS_PRI3_R=(NVIC_SYS_PRI3_R & 0x1FFFFFFF) | 0x60000000; /*  priority 3 */
    __asm  ("    CPSIE  I\n");

}


void Systick_INT_Handler()
{
    count=count+1;
}


void DisableInterrupts(void)
{
    __asm ("    CPSID  I\n");
}


void uart_put_int(int freq)
{
    int x,y,i;
    char temp_display[10];
    y=freq;
    i=0;
    while(1)
          {
              x=y%10;
              temp_display[i]=x+48;
              i=i+1;
              y=y/10;
              if(y==0)
                  {
                      i--;
                      while(i>=0)
                          {UARTCharPut(UART0_BASE,temp_display[i]); i--;}
                      break;
                   }
             }
    UARTCharPut(UART0_BASE, '\n');
    UARTCharPut(UART0_BASE, 13);
}
