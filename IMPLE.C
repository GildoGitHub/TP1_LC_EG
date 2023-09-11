#include<stdio.h>
#include "VTEXTO.h"
#include "utypes.h"
#include <go32.h> 
#include <sys/farptr.h> 
#include<stdlib.h>
//  unsigned long base = 0xB8000;
   int tamanhoString(char*str);
   char*num_to_string(int num);
   char*invertString(char*str);
   void troca(char *str, int i, int j);
   char*inverte(char *str);
   int num_digito(int num);

Bool printCharAt(char ch, int x, int y, char attributes){
     char chr;
      if((x<0 && x>25)&&(y<0 && y>80)){
         return false;
      }else{ 
               unsigned long offset = x*(80*2)+y*2;
            _farpokeb(_dos_ds,VIDEO_TEXT+offset,ch);
            _farpokeb(_dos_ds,VIDEO_TEXT+offset+1,attributes);
            chr=_farpeekb(_dos_ds,VIDEO_TEXT);
	        return  true;
	  }
}

Bool printStringAt(char*str, int x,int y, char attributes){
     int posicao= 0;
     char c;
     if((x<0 && x>25)&&(y<0 && y>80)){
      return false;
    }else{
        unsigned long  offset = x*(80*2)+y*2;
          while(str[posicao]!='\0'){
            _farpokeb(_dos_ds,VIDEO_TEXT+offset,str[posicao]);
            _farpokeb(_dos_ds,VIDEO_TEXT+offset+1,attributes);
            c =_farpeekb(_dos_ds,VIDEO_TEXT);
            offset+=2;
            posicao++;
          }
          return true; 
       }
}
//funcoes auxiliares

//troca posicoes de uma string
void troca(char *str, int i, int j)
{
    char aux = str[i];
    str[i] = str[j];
    str[j] = aux;
}
//invert string
char* inverteString(char *str){
    int tam = tamanhoString(str);
    int i, j;

    for(i=0, j=tam-1; i < j; ++i, --j) {
        troca(str, i, j);
    }
    return str;
}
//numero de digitos
int num_digito(int num){
    int d = 1;

    while(num >= 10) {
        num /= 10;
        ++d;
    }
    return d;
}
//conversao de numero para string
char* num_to_string(int num){
    int digit = num_digito(num);
    char*str = (char*) malloc((digit+1)*sizeof(char));
    int i;
    for( i=0; i < digit; ++i ) {
        str[i] = num%10 + 48;
        num /= 10;
    }
    str[digit] = '\0';
    return inverteString(str) ;
}
//tamanho de string
int tamanhoString(char*str){
     int i = 0;
     while(str[i]!='\0'){
        i++;
     }
    return i;
}

// funcao de implementacao 
Bool printIntAt(int num, int x,int y, char attributes){
      char*str = num_to_string(num);
      char ch;
     if((x<0 && x>25)&&(y<0 && y>80)){
      return false;
    }else{
        unsigned long offset = x*(80*2)+y*2;
         int i = 0;
         while(str[i]!='\0'){
              
            _farpokeb(_dos_ds,VIDEO_TEXT+offset,str[i]);
            _farpokeb(_dos_ds,VIDEO_TEXT+offset+1,attributes);
            ch=_farpeekb(_dos_ds,VIDEO_TEXT);
            offset +=2;          
            i++;
         }
		 
        return true; 
       }
	    free(str);
}
Bool drawFrame(char *title, char attributes,int x, int y, int width, int height)
{
    const char VERTICL = 186;
    const char HORIZONTL = 205;
    const char CANTO_INFERIOR_ESQUERDO = 200;
    const char CANTO_SUPERIOR_ESQUERDO = 201;
    const char CANTO_SUPERIOR_DIREITO = 187;
    const char CANTO_INFERIOR_DIREITO = 188;

     if( (x < 0 && x > 80) || (y < 0 && y > 25) || x + width > WIDTH ||
         y + height > HEIGHT || width <= 0 || height <= 0 )
        return false;

    int tamanho_titulo = tamanhoString(title);

    if( tamanho_titulo > width )
        return false;

    int centro_x = (width - tamanho_titulo + 2)/2;
    int centro_y = (height + 2)/2;

    printStringAt(title, x + centro_x-6, y + centro_y-2, attributes);
      int i;
    for(i = x; i < x + width + 2; ++i)
    {
        if( i == x)
        {
            printCharAt(CANTO_SUPERIOR_ESQUERDO, i, y, attributes);
            printCharAt(CANTO_INFERIOR_ESQUERDO, i, y + height + 1, attributes);
        }
        else if( i == x + width + 1 )
        {
            printCharAt(CANTO_SUPERIOR_DIREITO, i, y, attributes);
            printCharAt(CANTO_INFERIOR_DIREITO, i, y + height + 1, attributes);
        }
        else
        {
            printCharAt(HORIZONTL, i, y, attributes);
            printCharAt(HORIZONTL, i, y + height + 1, attributes);
        }
    }
       int k;
    for(k = y+1; k < y + height + 1; ++k)
    {
        printCharAt(VERTICL, x, k, attributes);
        printCharAt(VERTICL, x + width + 1, k, attributes);
    }

    return true;
}
 
