#include <stdio.h>


int main(void){
    int ch1,ch2,ch3,ch4,unicode,temp,highsurr,lowsurr,flag;
    flag=0;                                                       //If our flag becomes 1 at any point the program terminates due to invalid input.

    while((ch1=getchar())!=EOF&&flag==0){           //We read two bytes since in UTF-16 a character is encoded with at least two bytes.
        ch2=getchar();
        unicode=(ch1<<8)+ch2;                       //The two bytes we read in UTF-16 are actually the Unicode code of the character!
        if(unicode<=0){                             //A negative Unicode code means an illegal character since all codes are greater than or equal to zero.
            flag=1;
        }
        if((unicode>=0)&&(unicode<=0x7F)){          //Codes in this interval are encoded with only 1 byte in UTF-8.(For this and the following intervals remember that the UTF-16 encoding (up to 3 bytes) is actually the unicode code of the character so we just have to turn the Unicode encoding into UTF-8.)
            putchar(ch2);
        }
        if((unicode>=0x80)&&(unicode<=0x7FF)){      //Codes in this interval are encoded with 2 bytes in UTF-8.
                ch1=(unicode>>6) + 0xC0;
                ch2=(unicode&0x3F) + 0x80;
                putchar(ch1);
                putchar(ch2);

            }
        if((unicode>=0x800&&unicode<=0xD7FF)||(unicode>=0xE000&&unicode<=0xFFFF)){      //Codes in these intervals are encoded with 3 bytes in UTF-8.
            ch1=(unicode>>12)+0xE0;
            temp=(unicode>>6)&0x3F;
            ch2=temp+0x80;
            temp=unicode&0x3F;
            ch3=temp+0x80;
            putchar(ch1);
            putchar(ch2);
            putchar(ch3);
        }

        if(unicode>=0xD800&&unicode<=0xDBFF){       //This is the interval where high surrogates belong(we read two bytes so we have the high surrogate not the low one!).
            highsurr=unicode;
            ch3=getchar();                          //Now we need to read two more bytes.
            ch4=getchar();
            lowsurr=(ch3<<8)+ch4;
            if ((lowsurr>=0xDC00)&&(lowsurr<=0xDFFF)){ //If the bytes we read correspond to the low surrogate we go on and extract the Unicode code.Then we turn the Unicode code into UTF-8(4 bytes).
                highsurr&=0x3FF;
                lowsurr&=0x3FF;
                unicode=((highsurr<<10)+lowsurr)+0x10000;
                ch1=(unicode>>18)+0xF0;
                ch2=((unicode>>12)&0x3F)+0x80;
                ch3=((unicode>>6)&0x3F)+0x80;
                ch4=(unicode&0x3F)+0x80;
                putchar(ch1);
                putchar(ch2);
                putchar(ch3);
                putchar(ch4);
            }
            else flag=1;        //If we read a pair of bytes corresponding to a high surrogate but the next pair doesn't correspond to a low one we have an invalid input.


        }

        if (flag==1){
            printf("\n\n\nConversion terminated due to invalid character.");
        }





    }
	return 0;
}

