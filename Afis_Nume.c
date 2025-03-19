#include <REG51.H>
sfr ldata = 0x90; //Pin de date (P1)
sbit rs = P3^2;
sbit rw = P3^3;
sbit en = P3^4;
sbit busy = P1^7;
//Functii
void display(unsigned char code *msgchar);
void lcdcmd(unsigned char value);
void lcddata(unsigned char value);
void MSDelay(unsigned int itime);
void lcdready();

code unsigned char m1 [] = {"TEST};
//Main
void main(){
    lcdcmd(0x38);
    lcdcmd(0x0E);
    lcdcmd(0x01);
    lcdcmd(0x06);
    lcdcmd(0x80); // Linia 1, pozitia 0
    display(&m1);
}


void lcdcmd(unsigned char value)
{
    lcdready(); // Verificare LCD busy flag
    ldata = value; // Trimite date P1
    rs = 0;
    rw = 0;
    en = 1; //Enable signal
    MSDelay(1);
    en = 0;
    return;
}
void lcddata(unsigned char value)
{
    lcdready();// Verificare LCD busy flag
    ldata = value; // Trimite date P1
    rs = 1;
    rw = 0;
    en = 1; //Enable signal
    MSDelay(1);
    en = 0;
}
void lcdready()
{
    busy = 1; 
    rs = 0;
    rw = 1;
    while(busy==1){ //Verificare busy flag
        en = 0; 
        MSDelay(1);
        en = 1;
    }
}
void MSDelay(unsigned int itime){ // Delay
    unsigned int i, j;
    for(i=0;i<itime;i++)
        for(j=0;j<1275;j++);
}
void display(unsigned char code *msgchar){ //Afiseaza mesaj
    while(*msgchar!=0){ 
        lcddata(*msgchar);
        msgchar++;
    }
}
