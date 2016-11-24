#include <stdio.h>

int main(void){
	int ch1,ch2,ch3,ch4,bytes,mask,code,temp,flag;


	flag=0;                                          //We set our flag to 0. If it becomes 1 at any point it means we have read an illegal character so the program will terminate.
	while(((ch1=getchar())!=EOF)&&(flag==0)){
	mask=0x80;
	bytes=0;
	if((ch1&mask)==0){            //We check if the first bit of the byte we read is a 0. If it is, the unicode code of our character is the same as the UTF-16 code of our character so we print out a byte of zeroes and the code's byte.
		code=ch1;
		temp=(code>>8);
		putchar(temp);
		putchar(code);


	}
	else{
		while((ch1&mask)!=0){       //We count the leftmost 1's of our first byte which happens to be indicative of the number of bytes our character is encoded with for UTF-8.
			bytes++;
			mask>>=1;
		}

    if(bytes==1){            //Bytes==1 doesn't actually mean our character is encoded with 1 byte since those characters' codes start with 0.Thus, 1xxxxxxx is an illegal bitstring.
        flag=1;
    }

	if (bytes==2){          //If our character is encoded with 2 bytes we first read another byte with getchar. Then we check that our second byte is of the form 10xxxxxx. We extract our Unicode code(which is the same as the UTF-16 code and we print out the 2 bytes)
		ch2=getchar();
		if(ch2>=0x80&&ch2<=0xBF){
            ch1&=0x1F;
            ch2&=0x3F;
            code=(ch1<<6)+ch2;
            temp=(code>>8);
            putchar(temp);
            putchar(code);
		}
		else {
            flag=1;             //If our second byte is not of the form 10xxxxxx the character is illegal.
        }

	}
    if (bytes==3){              //If our character is encoded in 3 bytes we read 2 more bytes.We check that the bytes we read are of the form 10xxxxxxx.Again we extract our unicode code and print it out in two bytes.
        ch2=getchar();
        ch3=getchar();
        if((ch2>=0x80&&ch2<=0xBF)&&(ch3>=0x80&&ch3<=0xBF)){
            ch1&=0xF;
            ch2&=0x3F;
            ch3&=0x3F;
            code=(ch1<<12)+(ch2<<6)+ch3;
            temp=(code>>8);
            putchar(temp);
            putchar(code);
        }
        else {
            flag=1;         //If any one of the two last bytes we read isn't of the form 10xxxxxx we have an illegal character.
        }
    }
    if (bytes==4){          //The characters that are encoded with 4 bytes in UTF-8 are encoded as surrogate pairs in UTF-16.We extract the unicode code and convert it to each surrogate's code. Then we output 2 bytes for each surrogate so 4 bytes in total.
        ch2=getchar();
        ch3=getchar();
        ch4=getchar();
        if((ch2>=0x80&&ch2<=0xBF)&&(ch3>=0x80&&ch3<=0xBF)&&(ch4>=0x80&&ch4<=0xBF)){
            ch1&=0x7;
            ch2&=0x3F;
            ch3&=0x3F;
            ch4&=0x3F;
            code=(ch1<<18)+(ch2<<12)+(ch3<<6)+ch4;
            code-=0x10000;
            ch1=((code&0xFFC00)>>10)+0xD800;
            ch2=(code&0x3FF)+0xDC00;
            temp=(ch1>>8);
            putchar(temp);
            putchar(ch1);
            temp=(ch2>>8);
            putchar(temp);
            putchar(ch2);
        }
        else {
            flag=1;            //If any one of the three last bytes we read isn't of the form 10xxxxxx we have an illegal character.
        }
    }
    if(bytes>=5){
    	flag=1;               //11111xxx is an illegal bitstring in UTF-8.(so is 111111xx etc.)
    }

	}
	if (flag==1){
        printf("\n\n\n Conversion terminated due to invalid character.\n");
	}
}
return 0;
}

