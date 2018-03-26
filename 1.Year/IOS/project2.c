//*     Proj2.c            */
//*      Jozef Drab      */
//*       xdrabj00           */
//*      01.05.2017          */
//* -------- VUT FIT --------- */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define mutex mutex_xdrabj00 //
#define AdultEnterQueue AdultEnterQueue_xdrabj00
#define AdultLeaveQueue AdultLeaveQueue_xdrabj00
#define AdultLeave AdultLeave_xdrabj00
#define ChildEnterQueue ChildEnterQueue_xdrabj00
#define ChildLeaveQueue ChildLeaveQueue_xdrabj00
#define ChildEnter ChildEnter_xdrabj00
#define AllStop AllStop_xdrabj00
 
long long checking(char *x)     //functions checking if argument is Correct
{
    char *ptr;
    double res= strtod(x,&ptr);

    if (strcmp(ptr,"\0"))
        res= -1;

    else if (res < 0)
        res = -1;

    return res;
}

int main(int argc, char *argv[])
{
    int adult=0, adult_help=0;
    int child=0, child_help=0;
    int Adult_Gen_Time=0, AGTH=0;
    int Child_Gen_Time=0, CGTH=0;
    int Adult_Waiting_Time=0, AWTH=0;
    int Child_Waiting_Time=0, CWTH=0;
    if (argc==7)
    {
        adult_help=checking(argv[1]);
       // printf("adult_help %d\n", adult_help);
       //  if( isdigit(adult_help) ) printf("AHOJ\n");                                                   //// ADULT
        if(adult_help > 0)
        {
            adult=adult_help;
            //printf("adult %d\n", adult);
        }
        else
        {
            fprintf(stderr,"INCORRECT PARAMETER OF ADULT!\n");   // EXIT CODE
            exit(1);
        }
        child_help=checking(argv[2]);                                                       //// CHILD
        if(child_help > 0)
        {
            child=child_help;
        }
        else
        {
            fprintf(stderr,"INCORRECT PARAMETER OF CHILD!\n");   // EXIT CODE
            exit(1);
        }
        AGTH=checking(argv[3]);                                                       //// ADULT_GEN_TIME
        if((AGTH >= 0) && (AGTH < 5001))
        { 
            Adult_Gen_Time=AGTH;
        }
        else
        {
            fprintf(stderr,"INCORRECT PARAMETER OF Adult_Gen_Time!\n");   // EXIT CODE
            exit(1);
        }
        CGTH=checking(argv[4]);                                                       //// CHILD_GEN_TIME
        if((CGTH >= 0) && (CGTH < 5001))
        {
            Child_Gen_Time=CGTH;
        }
        else
        {
            fprintf(stderr,"INCORRECT PARAMETER OF Child_Gen_Time!\n");   // EXIT CODE
            exit(1);
        }

        AWTH=checking(argv[5]);                                                       //// ADULT_WAITING_TIME
        if((AWTH >= 0) && (AWTH < 5001))
        {
            Adult_Waiting_Time=AWTH;
        }
        else
        {
            fprintf(stderr,"INCORRECT PARAMETER OF Adult_Waiting_Time!\n");   // EXIT CODE
            exit(1);
        }
        CWTH=checking(argv[6]);                                                       //// CHILD_WAITING_TIME
        if((CWTH >= 0) && (CWTH < 5001))
        {
            Child_Waiting_Time=CWTH;            
        }
        else
        {
            fprintf(stderr,"INCORRECT PARAMETER OF Adult_Waiting_Time!\n");   // EXIT CODE
            exit(1);
        }
    }
    else
    {
        fprintf(stderr,"INCORRECT NUMB OF ARGUMENTS!\n");   // EXIT CODE
        exit(1);
    }
    

    // opening file for writing
    FILE *f = fopen("proj2.out","wb");
    if (f == NULL)
    {
        fprintf(stderr,"CANNOT OPEN FILE\n");
        exit(-1);
    }

    setbuf(f,NULL);
    setbuf(stderr,NULL);
    
    //############ creating shared variables  ############//

    int *count = mmap(NULL, sizeof(count), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *count=1;     //is variable incerementing after every writing
    int *AdultInCent = mmap(NULL, sizeof(AdultInCent), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *AdultInCent=0;   //is count of adults in cent..
    int *ChildInCent = mmap(NULL, sizeof(ChildInCent), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *ChildInCent=0;   //is count of kids in cent..
    int *AvisitC = mmap(NULL, sizeof(AvisitC), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *AvisitC= adult;  //is count of adults, who haven't visited cent..
    int *AllEnd = mmap(NULL, sizeof(AllEnd), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *AllEnd= adult + child; //is count of all process
    int *sum = mmap(NULL, sizeof(AllEnd), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *sum = adult + child +2;  //varible for loop
    int *semchild = mmap(NULL, sizeof(semchild), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *semchild = 0;
    //############ creating semaphores ############//

    sem_t *mutex;         //checking if 1 process starts, after other finishes
    sem_t *AdultEnterQueue;   //semaphore for writing, while process adult wanna enter
    sem_t *AdultLeaveQueue;   //semafore for adults, while adult can't leaves
    sem_t *AdultLeave;      //semaphore for writing,while adult wanna leave
    sem_t *ChildEnterQueue;     //semafore where childs wait while can't enter
    sem_t *ChildLeaveQueue;   //semaphore for kids, while they wanna leave
    sem_t *ChildEnter;      //semaphore for kids, for enter
    sem_t *AllStop;       //semaphore where all process wait till the last one unlocks them


    /* mapping shared variables and semaphores */
    mutex= mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    AdultEnterQueue= mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    AdultLeaveQueue= mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    AdultLeave= mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    ChildEnterQueue= mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    ChildLeaveQueue= mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    ChildEnter= mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    AllStop= mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // initialization of semaphores
    sem_init(mutex,1,1);
    sem_init(AdultEnterQueue,1,1);
    sem_init(AdultLeaveQueue,1,0);
    sem_init(AdultLeave,1,1); 
    sem_init(ChildEnterQueue,1,0);
    sem_init(ChildLeaveQueue,1,1);
    sem_init(ChildEnter,1,1);
    sem_init(AllStop,1,0);    
    pid_t pid;            //forking main process (adult+child)
    pid = fork(); 

    if (pid != 0)
    {                             // creating adult
        
        for (int i = 1; i <= adult; i++)  //forking new adult process "adult" times
        {
           if ((Adult_Gen_Time != 0) && (i != 1))
            usleep(rand() % ((Adult_Gen_Time + 1)*1000)); //time generating new proces adult
            pid = fork(); 
            if (pid == 0)
            {

                //sem_wait(AdultEnterQueue);
                sem_wait(mutex);
                fprintf(f,"%d\t: A %d\t: started\n", *count, i);
                fflush(f);
                *count+=1;
                sem_post(mutex);
                ///////////////////////////////////////////////////////////////
                sem_wait(mutex);
                fprintf(f,"%d\t: A %d\t: enter\n", *count, i);
                fflush(f);
                *AdultInCent += 1;

                //if(i!=1) sem_post(AdultLeaveQueue);

                for (int f = 0; f <3; ++f)
                  sem_post(ChildEnterQueue);

                //3x sem post
                //sem_post(AdultLeaveQueue);
                *count += 1;   
                sem_post(mutex);    
                //sem_post(AdultEnterQueue);  
                sem_wait(AdultLeave);
           
                if (Adult_Waiting_Time != 0)      
                  usleep(rand() % ((Adult_Waiting_Time + 1)*1000));  
                ///////////////////////////////////////////////////////////
                sem_wait(mutex);
                fprintf(f,"%d\t: A %d\t: trying to leave\n", *count, i);
                fflush(f);
                *count+=1;
                sem_post(mutex);
                ///////////////////////////////////////////////////////////
                if (*ChildInCent > ((( *AdultInCent )-1)*3))
                {
                    sem_wait(mutex);
                    fprintf(f,"%d\t: A %d\t: waiting:\t %d\t: %d\n", *count, i, *AdultInCent, *ChildInCent);
                    fflush(f);
                    *count+=1;
                    sem_post(mutex);
                    sem_post(AdultLeave);                    
                    *semchild+=1;
                    sem_wait(AdultLeaveQueue);
                }
                ////////////////////////////////////////////////////////////
                sem_wait(mutex);
                fprintf(f,"%d\t: A %d\t: leave\n", *count, i);
                fflush(f);
                *AdultInCent-=1;
                *count+=1;
                *AvisitC-=1;
                *AllEnd-=1;
                  for (int g = 0; g <3; ++g)
                    sem_wait(ChildEnterQueue);
                sem_post(mutex);
                sem_post(AdultLeave);
                //////////////////////////////////////////////////////
                if (*AllEnd == 0)               
                  { 
                  sem_wait(mutex);                  //all process're waiting for last one
                  fprintf(f,"%d\t: A %d\t: finished\n", *count, i);
                  fflush(f);
                  *count+=1;               
                  sem_post(mutex);                //last one porcess unlocks all other, waiting on semaphore "AllStop"
                  //printf("............. gfhgfgfhj %d\n", *sum);
                    for(int teddy2=0; teddy2 < *sum; teddy2++)
                    { 
                      //printf("...... blabla\n");
                      sem_post(AllStop);
                    }
                    exit(0);
                  }
                else
                {  
                  sem_wait(AllStop);                //all process're waiting for last one
                  sem_wait(mutex);
                  fprintf(f,"%d\t: A %d\t: finished\n", *count, i);
                  fflush(f);
                  *count+=1;               
                  sem_post(mutex);
                  exit(0);
              }
           } 
        }
        
    }
    else
    {                           //creating child
        for (int j = 1; j <= child; j++)          //forking "child" times
        {
           if ((Child_Gen_Time != 0) && (j!=1))     // time generating of new child process
            usleep(rand() % ((Child_Gen_Time + 1)*1000));
           pid = fork(); 
           if (pid == 0)
           {
                //sem_wait(ChildEnter);
                sem_wait(mutex);
                fprintf(f,"%d\t: C %d\t: started\n", *count, j);
                fflush(f);
                *count+=1;
                sem_post(mutex);
                if ( *AvisitC == 0)
                {
                  sem_wait(ChildEnter);
                  sem_wait(mutex);
                  fprintf(f,"%d\t: C %d\t: enter\n", *count, j);
                  fflush(f);
                  *ChildInCent += 1;
                  *count += 1;                             
                  sem_post(mutex);
                  //sem_post(ChildEnter);
                 
                  sem_wait(mutex);
                  fprintf(f,"%d\t: C %d\t: trying to leave\n", *count, j);
                  fflush(f);
                  *count+=1;
                  sem_post(mutex);

                  sem_wait(mutex);
                  fprintf(f,"%d\t: C %d\t: leave\n", *count, j);
                  fflush(f);
                  *ChildInCent -= 1;
                  *count+=1;
                  *AllEnd-=1;
                  sem_post(mutex);
                  sem_post(ChildEnter);                
                }
                else 
                {
                  
                  if (*ChildInCent >= (( *AdultInCent )*3))
                  {
                    sem_wait(mutex);
                    fprintf(f,"%d\t: C %d\t: waiting:\t %d\t: %d\n", *count, j, *AdultInCent, *ChildInCent);
                    fflush(f);
                    *count+=1;
                    sem_post(mutex);
                    //sem_post(ChildEnter);                  
                  }

                  sem_wait(ChildEnterQueue); //blocking

                  sem_wait(mutex);
                  fprintf(f,"%d\t: C %d\t: enter\n", *count, j);
                  fflush(f);
                  *ChildInCent += 1;
                  *count += 1;
                  sem_post(mutex);
                  //sem_post(ChildEnter);   

                  if( Child_Waiting_Time != 0)
                  usleep(rand() % ((Child_Waiting_Time + 1)*1000));
                      
                  sem_wait(ChildLeaveQueue);   
                  sem_wait(mutex);
                  fprintf(f,"%d\t: C %d\t: trying to leave\n", *count, j);
                  fflush(f);
                  *count+=1;
                  sem_post(mutex);

                  sem_wait(mutex);
                  fprintf(f,"%d\t: C %d\t: leave\n", *count, j);
                  fflush(f);
                  sem_post(ChildEnterQueue);
                  *ChildInCent -= 1;
                  ///////////////////////////////////////////////
                  if (*ChildInCent <= ((( *AdultInCent )-1)*3))
                    if(((*ChildInCent % 3)==0) && (*semchild == 1))
                      {sem_post(AdultLeaveQueue);
                       *semchild-=1;  
                        }
                  //////////////////////////////////////////                  
                  *count+=1;
                  *AllEnd-=1;
                  sem_post(mutex);
                  sem_post(ChildLeaveQueue);
                } 
                ///////////////////////////////////////////////////////////////////
                if (*AllEnd == 0)             //last one process unlocks other process
                {                 
                sem_wait(mutex);              // all process wait for last one on smeaphore "AllStop"
                fprintf(f,"%d\t: C %d\t: finished\n", *count, j);
                fflush(f);
                *count+=1;               
                sem_post(mutex);  
                  for(int teddy=0; teddy < *sum; ++teddy)
                  {
                    sem_post(AllStop);
                  }  
                  exit(0);   
                } 
                else 
                {
                  sem_wait(AllStop);              // all process wait for last one on smeaphore "AllStop"
                  sem_wait(mutex);
                  fprintf(f,"%d\t: C %d\t: finished\n", *count, j);
                  fflush(f);
                  *count+=1;               
                  sem_post(mutex);
                  exit(0); 
                }            
            }    
       } 
    }

    sem_destroy(mutex);             //destroying shared variables and semaphores
    munmap(mutex, sizeof(sem_t));

    sem_destroy(ChildEnterQueue);
    munmap(ChildEnterQueue, sizeof(sem_t));

    sem_destroy(AdultEnterQueue);
    munmap(AdultEnterQueue, sizeof(sem_t));

    sem_destroy(AdultLeaveQueue);
    munmap(AdultLeaveQueue, sizeof(sem_t));

    sem_destroy(ChildLeaveQueue);
    munmap(ChildLeaveQueue, sizeof(sem_t));

    sem_destroy(ChildEnter);
    munmap(ChildEnter, sizeof(sem_t));

    sem_destroy(AdultLeave);
    munmap(AdultLeave, sizeof(sem_t));

    munmap(count, sizeof(unsigned));
    munmap(semchild, sizeof(unsigned));
    munmap(AdultInCent, sizeof(unsigned));
    munmap(ChildInCent, sizeof(unsigned));
    munmap(AvisitC, sizeof(unsigned));
    munmap(sum, sizeof(unsigned));
    fclose(f);                //closing file
    sem_wait(AllStop);            //main process waits for other process
    sem_destroy(AllStop);         //destroying semaphore AllStop
    munmap(AllEnd, sizeof(unsigned));     //following by unmapping
    usleep(1000000);
    exit(0);                  //exit main process
}
