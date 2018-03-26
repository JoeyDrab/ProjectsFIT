/* Projekt c.1
 * Autor: Jozef Drab, xdrabj00@fit.vutbr.cz
 * Skupina: 13 (1BIA)
 * Datum: 2016/10/30
 * Nazov souboru: proj1.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void argument_0();                                   //funkcia bez prepinaca
void argument_x();                                 //funkcia pre prepinac -x
void argument_r();                                //funkcia pre prepinac -r
void argument_Sm(int pocetsm);                   //funkcia pre prepinac -S M
void argument_sn(int pocetsn);		            //funkcia pre prepinac -s M
void argument_smnn(int pocetm, int pocetn);      //funkcia pre prepinac -s M -n N


int main(int argc, char *argv[])
{
    unsigned int pocetsm=0;
    int pocetsn=0;
    int pocetm=0,pocetn=0;

    if   (argc == 1)        //ak nebol zadany ziaden prepinac
    {
        argument_0();
    }

    if (argc == 2)                //ak bol zadany jeden argument rob..
        if ((argv[1][0]) == '-')      //ak dany argument zacina "-" rob...
          {

            if ((argv[1][1])=='x')  //ak argument je "-x" preved funkciu
            {
                    argument_x();   //zavolaj funkciu
            }
            if ((argv[1][1])=='r')  //ak argument je "-r" preved funkciu
            {
                argument_r();       //zavolaj funkciu 
            }
            if(((argv[1][1])!='x') && ((argv[1][1])!='r')) fprintf(stderr,"CHYBA, NEKOREKTNY ARGUMENT"); //ak argument sa nerovna "-r"...
                                                                                                         // alebo "-x" vypis chybu
          }


    if(argc == 3)                     // ak je pocet argumentov rovny nule pokracuj...
    {

        if((argv[1][1])== 'S')            //ak sa argument rovna 's' tak pokracuj..
        {

            pocetsm= strtol(argv[2],NULL,10);   //zapis hodnotu argumentu
            argument_Sm(pocetsm);               //zavolaj funkciu
        }
        if((argv[1][1])== 's')            //ak sa argument rovna 's' tak pokracuj..
        {
            pocetsn= strtol(argv[2],NULL,10);   //zapis hodnotu argumentu
            argument_sn(pocetsn);               //zavolaj funkciu
        }
        if(((argv[1][1])!='S') && ((argv[1][1])!='s')) fprintf(stderr,"CHYBA, NEKOREKTNY ARGUMENT"); //ak argument sa nerovna "-S" alebo "-s" vypis chybu
    }


    if(argc == 5)                    // ak je pocet argumentov rovny 5 pokracuj...
      if((argv[1][1])== 's')              //ak sa argument rovna 's' tak pokracuj..
      {
        if((argv[3][1])== 'n')           //ak sa argument rovna 'n' tak pokracuj..
        {
            pocetm= strtol(argv[2],NULL,10);    //nacitaj hodnotu argumentu
            pocetn= strtol(argv[4],NULL,10);    // 2x
            argument_smnn(pocetm,pocetn);         //zavolaj funkciu
        }
        else fprintf(stderr,"CHYBA, NEKOREKTNY ARGUMENT");
      }
        else fprintf(stderr,"CHYBA, NEKOREKTNY ARGUMENT");
    if((argc!=1) && (argc!=2) && (argc!=3) && (argc != 5)) fprintf(stderr, "CHYBA, NEKOREKTNY POCET ARGUMENTOV");   //ak je pocet argumentov vacsi...
                                                                                                                          // ako 5, vypis chybu
}



 void argument_0()
{
    int charznak;                     //definicia premennych
    int i=0,j=0,del;
    char pole[15]={};
    while((charznak=getchar()) != EOF)      //cyklus opakujuci sa dokym neprecita vsetky znaky
    {
        if(isprint(charznak))
            pole[i]=charznak;
        else
            pole[i]=('.');
        if(i==0)
            printf("%08x  ",j);
        if(i==7)
            printf("%x  ",charznak);
        else
            printf("%02x ",charznak);

        if(i==15)                                  //ak presiahne dlzku 16, vypis pole do zatvoriek
        {
            printf(" |%-16s|",pole);                    //vypis
            i=0;                                        //anuluj i
            printf("\n");
            for(del=0;del<16;del++);                    //pre premennu del, 16x opakuj cyklus v ktorom sa vymaze pole
            {
               pole[i]=0;
               i++;
            }
            i=0;
        }
        else i++;
        j++;
    }
     printf(" |%-16s|",pole);
}


  void argument_x()                 //funkcia pre vypis hexadec. podoby (nevracia nic)
{
    int znak=0;
    while ((znak=getchar()) != EOF)             //cyklus kt. bude citat znaky
    {
        if(znak!=92)
     printf("%02x",znak);            // vo funkcii sa znaky vypisu
    }

}

 void argument_r() // ctype.h
{
    int znak;
    int pocet=1;
    int result=0,expo=16;
    while ((znak=getchar()) != EOF)                            //citaj znaky kym nebude EOF
    {
      if(((znak) != (32)) && ((znak) != (0)) && (znak != (10)))        //ak je znak tlacitelny rob...
      {
        if((znak > 48) && (znak < 57))                         //cisla z ascii
            switch (znak)
                {
                    case 48 :
                        znak= 0;
                        break;
                    case 49 : znak= 1;
                    break;
                    case 50 : znak= 2;
                    break;
                    case 51 : znak= 3;
                    break;
                    case 52 : znak= 4;
                    break;
                    case 53 : znak= 5;
                    break;
                    case 54 : znak= 6;
                    break;
                    case 55 : znak= 7;
                    break;
                    case 56 : znak= 8;
                    break;
                    case 57 : znak= 9;
                    break;
                }
      else  if((znak > 65) && (znak < 90))                     //velke pismena z ascii
            switch (znak)
                 {
                    case 65 : znak= 10;
                    break;
                    case 66 : znak= 11;
                    break;
                    case 67 : znak= 12;
                    break;
                    case 68 : znak= 13;
                    break;
                    case 69 : znak= 14;
                    break;
                    case 70 : znak= 15;
                    break;
                 }
     else   if((znak > 97) && (znak < 122))                         //male pismena z asci
           switch (znak)
                {
                    case 97 : znak= 10;
                    break;
                    case 98 : znak= 11;
                    break;
                    case 99 : znak= 12;
                    break;
                    case 100 : znak= 13;
                    break;
                    case 101 : znak= 14;
                    break;
                    case 102 : znak= 15;
                 }
        if(pocet==1) expo=16;                            //v prvom cykle pocet nastaveny na 1, exponent bude 16
        else if(pocet==2) expo=1;                        //v druhom cykle bude pocet 2, exponent 1

        result+=(znak*expo);                             //v prvok cykle result bude prve cislo*16,
                                                         //v druhom cykle result vysledok plus nove cislo
        if(pocet==2)
            if(result!=865) printf("%c",result);                //v druhom cykle sa result vypise
        pocet++;                                         //inkrementuj i
        if(pocet==3)                                     //pocet sa inkrementuje na 3, kde sa resetuje spolu s resultom
            {
                pocet=1;
                result=0;
            }
        } //if isprint()
    } //** while cyklus
}


void argument_Sm(int pocetsm)
{
     int charznak;                       //deklaracia premennej ktora bude vyberat znaky typu char
    int i=0,j,k=0;
    char pole[200];                      // deklaracia pola typu char



    if(pocetsm>200)            // ak zadany pocet N je vacsi ako 200, vypise chybu*
            {
                printf("zadany pocet znakov je vyssi ako 200\n");
            }

    while((charznak=getchar()) != EOF)      //citaj znak po znaku kym nebude EOF
    {
        if(charznak != (92))                         //ak znak nebude "\" rob..
        {
           if(k!=1)                                  //ak k bude 0 rob..
           {
            pole[i]=charznak;                        //zapis znak do pola
            i++;                                     //inkrementuj i
           }
           else                                      //ak k bude 1 rob..
           {
              if((charznak==110)||(charznak==48)) k=0;  //znak za / musi byt n alebo 0
              else                                      //ak nebude, vypis chybu
              {
                printf("chyba");
              }
           }
        }
        else                                        //ak znak bude / rob..
        { k=1;                                      //zmen k na 1
          if(i>=pocetsm)                            //ak pocet cyklov bude vacsi ako zadany argument pokracuj..
          {
            for(j=0;j<i;j++)                        //vypis cele pole
                printf("%c",pole[j]);
            i=0;                                    //premennej i pridel 0
            printf("\n");                           //odriatkuj
          }
          else i=0;
        }
    } //while
}



void argument_sn(int pocetsn)
{
    int charznak;                  //deklaracia premennej typu int
    int i=1,j=0;
    char pole[200]={};
    if(pocetsn>200)                 // ak zadany pocet N je vacsi ako 200, vypise chybu
                fprintf(stderr,"CHYBA!");

    while((charznak=getchar()) != EOF)      //citaj znak po znaku kym nebude EOF
    {
        if(i==pocetsn)                      //ak sa pocet cyklu rovna zadanemu argumentu rob..
            printf("%08x  ",i);             //vytlac vstupny bajt
        if(i>pocetsn)                      //ak je pocet cyklu vacsi ako parameter argumentu..
        {
           printf("%02x ",charznak);           //..tak vytlac znaky
           pole[j]=charznak;                    //ak pocet cyklov vyhovuje zadanemu argumentu, pis do pola znak
           j++;                                 //inkrementuj j
        }
       i++;
    } //while
    printf("  |%-16s|",pole);
}


void argument_smnn(int pocetm, int pocetn)
{
    char charznak;                       //deklaracia premennej typu char
    int i=0,j=0,k=0,x;
    char pole[100]={};                   //deklaracia pola

    while((charznak=getchar()) != EOF)      //citaj znak po znaku kym nebude EOF
    {
       if(charznak==10)
       {
           fprintf(stderr,"CHYBA");
       }
       if(pocetm==i) printf("%08x  ",i);
       if((pocetm<=i) && (i<(pocetm+pocetn)))       //ak je pocet cyklov vyhovujuci argumentom
       {
           if(isprint(charznak)) pole[j]=charznak;   //do pola zapis kazdy znak ktory splna podmienku
           else pole[i]=('.');                       //ak nie je znak tlacitelny, zapis bodku
           if(k==0) printf("%02x ",charznak);        //vytlac znak v hexadecimalnom stave
           j++;                                      //inkrementuj j
           k++;
           if(k==16)                                 //ak vypise 16 znakov rob..
           {
            printf("  |%-16s|",pole);                //vypis pole ako string medzi zatvorky
            for(x=0;x<16;x++)                        //vynuluj pole
            {
              pole[x]=0;
            }
            j=0;
            k=0;
            printf("\n");                           //odriatku a vypisuj dalej
            printf("%08x  ",i);
           }
       }
       else if(i==(pocetm+pocetn)) printf("  |%-16s|",pole);     //ak nacita a vypise vsetky vyhovujuce..
       i++;                                                //..znaky,vytlac pole
    }//while
}
