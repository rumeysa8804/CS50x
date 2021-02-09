#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        fprintf(stderr,"Usage: ./recover infile\n");
        return 1;
    }

   
    FILE  *ptr=fopen("card.raw","r");
    

    if(ptr==NULL)
    {
        fprintf(stderr,"Could not open\n");
        return 2;
    }
    
    BYTE  *arabellek=malloc(sizeof(BYTE)*512);
    
    int bulunanjpg=0;
    FILE *img=NULL;
    
    while(fread(arabellek,512,1,ptr)==1)
    {
        fread(arabellek,512,1,ptr);
        if(arabellek[0] == 0xff && arabellek[1] == 0xd8 && arabellek[2] == 0xff && (arabellek[3] & 0xf0) == 0xe0)
        {
            if(bulunanjpg==1)
            {
                fclose(img);
            }
          
          
             char yenidosya[8];
            sprintf(yenidosya, "%03i.jpg",bulunanjpg );
            img=fopen(yenidosya,"w");
            
            fwrite(arabellek,512,1,img);
            bulunanjpg++;
           
        }
        
        else
        {
           if(bulunanjpg==0)
            {
                fseek(ptr,sizeof(BYTE)*512,SEEK_CUR);
            }
            
            else
                fwrite(arabellek,512,1,img);
            
        }
         
           
    }
  
   free(arabellek);
   fclose(ptr);
   fclose(img);
   return 0;
    


}





