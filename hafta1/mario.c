#include <stdio.h>
#include<cs50.h>
int main()
{  bool a=true;
   while(a==true)
   {
          int yukseklik=get_int("yukseklik: ");
          
         if(yukseklik>=1&&yukseklik<=8)
         {  a=false;
             for(int i=0;i<yukseklik;i++)
             {
                 for(int j=0;j<yukseklik-(i+1);j++)
                 {
                     printf(" ");
                 }
                 for(int j=0;j<i+1;j++)
                 {
                     printf("#");
                 }
                 printf("\n");
             }
         }
    }
}
