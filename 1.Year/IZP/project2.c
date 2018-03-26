/* Projekt c.2
 * Autor: Jozef Drab, xdrabj00@fit.vutbr.cz
 * Skupina: 13 (1BIA)
 * Datum: 2016/11/22
 * Nazov souboru: proj2.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double taylor_log(double x, unsigned int n);                                            // Prototypy funkcií
double cfrac_log(double x, unsigned int n);
double taylor_pow(double x, double y, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);
double mylog(double x);
double mypow(double x, double y);
double alternativ(double x);

int main(int argc, char *argv[])                                                        //volanie hlavnej funkcie
{
  double logX=0.0;                                                                      //inicializovanie premenných
  long long int logN=0;
  double powX=0.0;
  double powY=0.0;
  long long int powN=0;
  char *ptr=0;
  double mylogX=0.0;
  double mypowX=0.0;
  double mypowY=0.0;


    if(argc==3)
     {                                                                       //ak sa pocet argumentov rovna dvom, rob..
        if(strcmp(argv[1],"--mylog")==0)                                             //porovnaj ci sa prvy argument rovna "--mylog"
            {
              mylogX= strtod(argv[2],&ptr);                                            //zapis hodnotu argumentu do premennej
              if((*ptr != 0) || (mylogX <= 0))
                {
                  fprintf(stderr,"CHYBA VSTUPU!\n");
                  return 0;
                }
              else printf("pocet interacii bol = %g\n",mylog(mylogX));                       //vypis
            }
         else
            {
                fprintf(stderr,"CHYBNY ARGUMENT NA VSTUPE!\n");
                return 0;
            }
     }
    else if(argc==4)
    {                                                                               //ak sa pocet argumentov rovná 4 rob..
        if(strcmp(argv[1],"--log")==0)                                              //porovnaj ci sa prvy argument rovna "--log"
            {
              logX= strtod(argv[2],&ptr);
              if((*ptr != 0) || (logX<=0))
                {
                  fprintf(stderr,"CHYBA VSTUPU!\n");
                  return 0;
                }
              logN= strtoul(argv[3],&ptr,0);                                          //z argumentu sa zapíše hodnota do premennej logN
              if((*ptr != 0) || (logN<=0))
                {
                  fprintf(stderr,"CHYBA VSTUPU!\n");
                  return 0;
                }
              else
              {
              printf("       log(%g) = %.12g\n",logX,log(logX));                        //výpis hodnoty logaritmu z matematickej knihovne
              printf(" cfrac_log(%g) = %.12g \n",logX,cfrac_log(logX,logN));            //vypis hodnoty logaritmu z funkcie zretazených zlomkov
              printf("taylor_log(%g) = %.12g \n",logX,taylor_log(logX,logN));           //výpis hodnoty logaritmu z funkcie taylorovho polynomu
              }
            }

        if(strcmp(argv[1],"--mypow")==0)                                                //porovnaj ci sa prvy argument rovna "--mypow"
            {
               mypowX= strtod(argv[2],&ptr);
              if((*ptr != 0) || (mypowX==0))
                {
                  fprintf(stderr,"CHYBA VSTUPU!\n");
                  return 0;
                }
              mypowY= strtod(argv[2],&ptr);                                             //zapis hodnotu argumentu do premennej
              if(*ptr != 0)
                {
                  fprintf(stderr,"CHYBA VSTUPU!\n");
                  return 0;
                }
              printf("pocet interacii bol = %g\n",mypow(mypowX,mypowY));                //vypis
            }
       if((strcmp(argv[1],"--mypow")!=0) && (strcmp(argv[1],"--log")!=0))
        {
          fprintf(stderr,"CHYBNY ARGUMENT NA VSTUPE!\n");
          return 0;
        }
    }

     else if(argc==5)
      {                                                                                 //ak sa poeet argumentov rovná 5 rob..
            if(strcmp(argv[1],"--pow")==0)                                              //prvý argument musí byt --pow
            {
              powX= strtod(argv[2],NULL);                                               //výpis hodnôt argumentov do premenných
              powY= strtod(argv[3],NULL);
              powN= strtoul(argv[4],NULL,0);
              if(powN<=0)
                {
                  fprintf(stderr,"CHYBA VSTUPU!\n");
                  return 0;
                }
              else if((powX==0)&&(powY<0))
                {
                  printf("         pow(%g,%g) = NAN\n",powX,powY);         //vypis exponencialnej funkcie z matematickej knohovne
                 printf("  taylor_pow(%g,%g) = NAN\n",powX,powY);         //vypis exponencialnej funkcie pomocou funkcie zretazenych zlomkov
                printf("taylorcf_pow(%g,%g) = NAN\n",powX,powY);          //vypis exponencialnej funkcie pomocou funkcie taylorovho p.
                }
              else
              {
               printf("         pow(%g,%g) = %.12g\n",powX,powY,pow(powX,powY));         //vypis exponencialnej funkcie z matematickej knohovne
               printf("  taylor_pow(%g,%g) = %.12g\n",powX,powY,taylor_pow(powX,powY,powN)); //vypis exponencialnej funkcie pomocou funkcie zretazenych zlomkov
               printf("taylorcf_pow(%g,%g) = %.12g\n",powX,powY,taylorcf_pow(powX,powY,powN)); //vypis exponencialnej funkcie pomocou funkcie taylorovho p.
              }
            }
           else
            {
              fprintf(stderr,"CHYBA VSTUPU!\n");
              return 0;
            }
      }
     else //((argc!=3)&&(argc!=4)&&(argc!=5))
        {
          fprintf(stderr,"Chybny pocet argumentov!\n");
          return 0;
        }
}


double taylor_log(double x, unsigned int n)             //funkcia pre vypocet taylorovho polynomu
{
  double result=0.0;                                    //deklaracia premennych
  double expon;
  double y=0.0;


    if((0<x) && (x<1))                                  //ak zadané eíslo je z intervalu nula až jedna rob..
    {
         y=1-x;                                         //odvod si y
         expon=y;

         for(unsigned long long int i=0;i<n;i++)        //n-krat rob syklus (n je pocet interacii)
         {
          result-= expon/(i+1);                         //vysledne cislo sa zapise do premennej result
          expon*=y;                                     //y sa umocní
         }
    }
    else if(x>=1)                                       // ak zadane cislo je rovne alebo vacsie ako 1 rob..
    {
         double hodn=0.0;                               //inicializacia premenných
         hodn= ((x-1) / x);
                                                        //zapis do premennej hodnota
         for(unsigned long long int i=0;i<n;i++)        //cyklus opakujuci sa n krat (n je pocet interacii)
         {
           result+=(hodn / (i+1));                      //zapis taylorovho polynomu do hodnoty result
           hodn*=((x-1) / x);
         }
    }
  return result;                                        //funkcia vracia hodnotu result


}

double cfrac_log(double x, unsigned int n)              //funkcia pre vypocet cisla pomocou zretazenych zlomkov
{
  double z=0.0;                                         //deklaracia premennych
  int odc=(2*n)-1;
  double result=0.0;
  double delit=odc;


  z=(x-1)/(1+x);
  for (unsigned long long int i=n;i>1;i--)                        //cyklus opakujuci sa n-krát (n je pocet interacii)
    {
       odc-=2;
       delit= ((i-1)*(i-1)*z*z)/delit;
       delit= odc-delit;
    }
  result= (2*z) / delit;
  return result;                                        //funkcia vracia hodnotu result
}


double taylor_pow(double x, double y, unsigned int n)       //funkcia pre vypocet exponencialnej rovnice pomocou taylorovho polynomu
{
  double ln=taylor_log(x,n);                                //deklaracia premennych
  double ln0=ln;
  double y0=y;
  double result=1;
  unsigned long long int fact=1;

  if((x==0)&&(y!=0)) return 0;
  if((x==0)&&(y==0)) return 1;
  if((x==0)&&(y<0))
    {
        fprintf(stderr,"Chyba vstupu!\n");
        return 0;
    }
  for(unsigned int i=1;i<=n;i++)                  //cyklus opakujuci sa n-krat (n je pocet interacii)
    {
      result+= (y*ln)/fact;
      y*=y0;
      fact*=(i+1);
      ln*=ln0;
      if(i>=20)                                     //ak bude viac ako 20 interacii, pretecie faktorial
      {
          fprintf(stderr,"Max velkost faktorialu!\n");
          return 0;
      }
    }

  return result;                                            //funkcia vracajuca hodnotu result
}

double taylorcf_pow(double x, double y, unsigned int n)     //funkcia pre vypocet exponencialnej rovnice pomocou zretazenych zlomkov
{
  double ln=cfrac_log(x,n);                                //deklaracia premennych
  double ln0=ln;
  double y0=y;
  double result=1;
  unsigned long long int fact=1;

  if((x==0)&&(y!=0)) return 0;
  if((x==0)&&(y<0))
    {
        fprintf(stderr,"Chyba vstupu!\n");
        return 0;
    }
  for(unsigned int i=1;i<=n;i++)                            //cyklus opakujuci sa n krat (n je pocet interacií)
    {
      result+= (y*ln)/fact;
      y*=y0;
      fact*=(i+1);
      ln*=ln0;
      if(i>=20)                                             //ak bude viac ako 20 interacii, pretecie faktorial
      {
          fprintf(stderr,"Max velkost faktorialu!\n");
          return 0;
      }
    }

  return result;                                            //funkcia vraca hodnotu result
}

double mylog(double x)                          //funkcia pre vypocet poctov interacii
{
  double eps=1e-9;                              //inicializacia premennej epsylon na hodnotu 0.000000001
  double result=0.0;
  double result0=0.0;
  double expon;
  double y=0.0;
  long int i=1;


  if(0<x)                                    //ak je x vacsie ako nula rob..
    {
         y=1-x;
         expon=y;
         result=-expon;                         //výpis prve interacie
         while(fabs(result-result0)>=eps)       //ak je absolut. hodnota rozdielu interacie a predchadzajuce interacie vacsia ako epsylon rob..
             {
              result0=result;
              result-= expon/(i+1);
              expon*=y;
              i++;
             }
         printf("\n result0 je %.20g",result0);     //vypis predposlednej interacie
         printf("\n  result je %.20g \n",result);   //vypis poslednej interacie
    }
  return i;                                         //funkcia vraca pocet interacii
}

double mypow(double x, double y)
{
  double ln=alternativ(x);                                  //deklaracia premennych
  double eps=1e-9;
  double ln0=ln;
  double y0=y;
  double result=1.0;
  double result0=0.0;
  int fact=1;
  long int i=1;

  while(fabs(result-result0)>=eps)                           //cyklus opakujuci sa n-krat (n je pocet interacii)
    {
      result0=result;
      result+= (y*ln)/fact;
      y*=y0;
      fact*=(i);
      ln*=ln0;
      i++;                                                    //vypocet
    }
    printf("\n result0 je %.20g",result0);
    printf("\n  result je %.20g \n",result);                 //výpis predchadzajucej a poslednej hodnoty
  return i;                                                 //funkcia vracajuca pocet interacii
}


double alternativ(double x)                     //alternaticna funkcia na vypocet logaritmu bez zadanych interacii
{
  double eps=1e-9;                              //inicializacia premennej epsylon na hodnotu 0.000000001
  double result=0.0;
  double result0=0.0;
  double expon;
  double y=0.0;
  long int i=1;

  if(x==0)                                      //ak sa zadane cislo rovna nule, vypis chybu
    {
        fprintf(stderr,"Chybne x!\n");
        return 0;
    }
    if(0<x)                                    //ak je x vacsie ako nula rob..
    {
         y=1-x;
         expon=y;
         result=-expon;                         //výpis prve interacie
         while(fabs(result-result0)>=eps)       //ak je absolut. hodnota rozdielu poslednej interacie a predchadzajuce interacie vacsia ako epsylon rob..
         {
          result0=result;
          result-= expon/(i+1);
          expon*=y;
          i++;
         }
    }
  return fabs(result);                                         //funkcia vraca absolutnu hodnotu resultu
}


