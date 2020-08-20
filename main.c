#include <stdio.h>
#include <stdlib.h>

char Hex[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
unsigned char code[2][16]={{0x0b,0x0d,0x02,0x0f,0x0a,0x00,0x05,0x03,0x04,0x08,0x0e,0x0c,0x01,0x09,0x07,0x06},{0x02,0x0c,0x05,0x0f,0x0a,0x03,0x08,0x00,0x0d,0x01,0x0e,0x0b,0x04,0x07,0x09,0x06}};
unsigned char decode[2][16]={{0x05,0x0c,0x02,0x07,0x08,0x06,0x0f,0x0e,0x09,0x0d,0x04,0x00,0x0b,0x01,0x0a,0x03},{0x07,0x09,0x00,0x05,0x0c,0x02,0x0f,0x0d,0x06,0x0e,0x04,0x0b,0x01,0x08,0x0a,0x03}};

unsigned int key=0;
char str[65536]={0x00};
unsigned int flag;

unsigned char Turn_Hex(unsigned char temp);
void Code();
void Decode();

int main()
{
    printf("1.code\n2.decode\n");
	scanf("%d",&flag);
	printf("Key:");
	scanf("%d",&key);
	printf("Num str:");
	scanf("%s",str);
	if(flag==1)
		Code();
	else
		Decode();
	return 0;
}

void Code()
{
    unsigned char num[65536]={0x00};//num 0-f
    unsigned int a = 0;
    while(str[++a]!=0x00);
    for(int b=0;b<a;b++)
    {
        num[2*b]=str[b]/1%16;//split in 0
        num[2*b+1]=str[b]/16%16;//split in 16
    }
    for(int b=0;b<2*a;b++)
    {
        num[b]=(num[b]+key/1%16)%16;//add the key in 0
        num[b]=code[0][num[b]];//code a
        num[b]=(num[b]+key/16%16)%16;//add the key in 16
        num[b]=code[1][num[b]];//code b
        num[b]=Hex[num[b]];//turn to hex
        key++;
    }
    printf("%s\n",num);
}

void Decode()
{
    unsigned char num[65536]={0x00};//num 0-f
    unsigned char out[65536]={0x00};//ascii data
    unsigned int a = 0;
    while(str[++a]!=0x00);
    for(int b=0;b<a;b++)
        num[b]=Turn_Hex(str[b]);//turn ascii data to hex
    for(int b=0;b<a;b++)
    {
        num[b]=decode[1][num[b]];//decode b
        num[b]=(num[b]+16-key/16%16)%16;//add the -key in 16
        num[b]=decode[0][num[b]];//decode a
        num[b]=(num[b]+16-key/1%16)%16;//add the -key in 0
        key++;
    }
    for(int b=0;b<a/2;b++)
    {
        out[b]|=num[2*b]&0x0f;
        out[b]|=(num[2*b+1]&0x0f)<<4;
    }
    printf("%s\n",out);
}

unsigned char Turn_Hex(unsigned char temp)
{
    if(temp>='0'&&temp<='9')
        return temp-'0';
    else if(temp>='a'&&temp<='f')
        return temp-'a'+10;
}
