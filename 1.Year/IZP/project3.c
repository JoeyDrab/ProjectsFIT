/** Projekt c.3
 *  Autor: Jozef Drab, xdrabj00@fit.vutbr.cz
 *  Skupina: 13 (1BIA)
 *  Datum: 2016/11/22
 *  Nazov souboru: proj3.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // sqrtf
#include <limits.h> // INT_MAX
#include <stdbool.h>
#include <string.h>
#include <limits.h>

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct objt_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t {
    int id;
    float x;
    float y;
};

struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap)
{
    assert(c != NULL);
    assert(cap >= 0);
    assert(c != NULL);

    c->obj = malloc(sizeof(struct obj_t) * cap);						//alokacia pamate o velkosti objektu * poctu objektov
    c->capacity = cap;										            //inicializacia kapacity na zadanu velkost
    c->size = 0;										                //velkost sa zadefinuje na nulu
}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
{
    // TODO
    free(c->obj);										                //uvolnenie alokovanej pamate o velkosti celeho zhluku
    c->size = 0;										                //velkost zhluku sa rovna jednej
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    // TUTO FUNKCI NEMENTE
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
    if (arr == NULL)
        return NULL;

    c->obj = arr;
    c->capacity = new_cap;
    return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{
    // TODO
    if(c->size == c->capacity) 									            //ak mam zhluk plny, realokujem si pamat
        c = resize_cluster(c, c->capacity + CLUSTER_CHUNK);

    if(c!=NULL)
    {
        c->obj[c->size] = obj;								        // pole objektov + objekt
        c->size++;
    }
}

/*
 Seradi objekty ve shluku 'c' vzestupne podle jejich identifikacniho cisla.
 */
void sort_cluster(struct cluster_t *c);
/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c2 != NULL);
    int i = 0;

    // TODO
    if((c1->capacity) < (c1->size + c2->size)) 								//ak ma c1 nedostatok kapacity, realokujem si pamat
        c1 = resize_cluster(c1, (c1->size + c2->size));

    while(i < c2->size)									//v cykle for budem pridavat objekty do zhluku tolko krat, aka je velkost shluku c2
    {
        append_cluster(c1, c2->obj[i]);
        i++;
    }

}

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
    assert(idx < narr);
    assert(narr > 0);

    										//ulozi posledny zhluk v poli na index zhluku ktory chcem zmazat...potom pamat posledneho zhluku uvolnim
    free(carr[idx].obj);
    carr[idx] = carr[narr-1];

    return (narr-1);
}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
    assert(o1 != NULL);
    assert(o2 != NULL);
    // TODO
    float result=0.0;
    int myX = o1->x - o2->x;
    int myY = o1->y - o2->y;

    result=sqrtf(pow(myX,2) + pow(myY,2));		            //do resultu zapis hodnotu

    return result;
}

/*
 Pocita vzdalenost dvou shluku. Vzdalenost je vypoctena na zaklade nejblizsiho
 souseda.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c1->size > 0);
    assert(c2 != NULL);
    assert(c2->size > 0);

    // TODO
    float NV = 1414;        //priestor o velkosti bodov 1000*1000 bude mat najvzdialenejsie body o velkosti 1414
    float result;
    int x=0;
    int y=0;
    while(x<c1->size)
    {
        while(y<c2->size)
        {
            result = obj_distance(&c1->obj[x],&c2->obj[y]); //pomocou funkcie zistujem vzdialenost dvoch zhlukov
            if(result < NV)                                 //ak je vzdialenost mensia ako NV tak ju zapisem
                    NV = result;
            y++;
        }
     x++;
    }

    return NV;
}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 hleda dva nejblizsi shluky (podle nejblizsiho souseda). Nalezene shluky
 identifikuje jejich indexy v poli 'carr'. Funkce nalezene shluky (indexy do
 pole 'carr') uklada do pameti na adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
    assert(narr > 0);

    // TODO
    float NV = 1414; 								//zhluky nebudu od seba urcite vzdialene viac ako o 1415(pri priestore 1000*1000)
    float result;
    int idxX = 0;
    int idxY = 0;
    int x=0;
    int y=x++;

    while(x<(narr-1))                                                       // index prveho zhluku na porovnanie
    {
        while(y<narr)                                             //index druheho zhluku na porovnanie
        {
            result = cluster_distance(&carr[x], &carr[y]); 					//zistujem velkost kazdych dvoch zhlukov
            if(result < NV)
            {
                idxX = x;
                idxY = y;
                NV = result;
            }
        }
     x++;
    }
    *c1 = idxX;
    *c2 = idxY;
}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = a;
    const struct obj_t *o2 = b;
    if (o1->id < o2->id) return -1;
    if (o1->id > o2->id) return 1;
    return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    for (int i = 0; i < c->size; i++)
    {
        if (i) putchar(' ');
        printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/

int load_clusters(char *filename, struct cluster_t **arr)
{
    assert(arr != NULL);

    // TODO

    FILE *fp;
    int str, strX, strY;
    struct obj_t myObj;
    int znak;
    int buffer[7]={};
    int r,i=0;
    int count=0;
    int pocet=0;

    fp = fopen(filename, "r");
     do
    {
        znak=fgetc(fp);
        buffer[i]=znak;
        i++;
        if(i>6) fprintf(stderr,"CHYBA COUNT-U!\n");
    } while(znak!= '=');

    buffer[i]='\0';
    if(strcmp(buffer,"count=")!=0)
        {
            fprintf(stderr,"CHYBA COUNT-U!\n");
            *arr=NULL;
        }
    i=0;
    for(int pc=0;pc<7;pc++)
        buffer[pc]='\0';


   while( (znak=fgetc(fp) ) != '\n')
        {

         buffer[i]=znak;
         i++;
        }

    buffer[i]='\0';
    count=atoi(buffer);
    *arr = malloc(sizeof(struct cluster_t) * count);

    if(*arr == NULL)
        {
            printf(stderr,"Malo miesta v pameti!\n");
            fclose(fp);
            free(*arr);
            *arr = NULL;
            return 0;
        }

    while(pocet<count)
    {
       r=fscanf(fp, "%d %d %d\n", &str, &strX, &strY);
       if( r == EOF )
        {
           fprintf(stderr,"menej objektov nez ich je pozadovanych!\n");
            return 0;
            *arr=NULL;
            break;
        }
      if((str<=47) || (58<=str))
        {
            fprintf(stderr,"pismeno v identifikatore\n");
            return 0;
            *arr=NULL;
            break;
        }
      if((strX<=47) || (58<=strX))
        {
            fprintf(stderr,"pismeno v suradniciach X\n");
            return 0;
            *arr=NULL;
            break;
        }
      if((strY<=47) || (58<=strY))
        {
            fprintf(stderr,"pismeno v suradniciach Y\n");
            return 0;
            *arr=NULL;
            break;
        }
       pocet++;
       myObj.id = str;
       myObj.x = strX;
       myObj.y = strY;
       if(strX > 1000 || strY > 1000)
            {
                printf("suradnice maju vacsiu hodnotu ako 1000\n");
                *arr = NULL;
                fclose(fp);
                return 0;
            }
       init_cluster(&(*arr)[pocet], 1);
       append_cluster(&(*arr)[pocet], myObj);
    }
    fclose(fp);

    return count;
}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/
void print_clusters(struct cluster_t *carr, int narr)
{
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);
        print_cluster(&carr[i]);
    }
}

int main(int argc, char *argv[])
{
    int count;
    long ChC = 0;
    struct cluster_t *clusters;
    int i=0,c1,c2;


    if(argc== 2) 										                //ak chyba druhy parameter, pocet chcenych zhlukov inicializujem na 1
        ChC = 1;

    else if(argc== 3)
        ChC = atol(argv[2]); 						                    // z argumentu si vycitam do premennej jeho hodnotu
        if(ChC<=0)
        {
            fprintf(stderr,"Druhy argument nesmie byt nulovy/zaporny\n");
            return 0;
        }

    count = load_clusters(argv[1], &clusters);

    if(count<ChC)
    {
       fprintf(stderr,"pocet objektov v subore je mensi ako pozadovany pocet\n");
       return 0;
    }

    if(count>INT_MAX)
    {
       fprintf(stderr,"pocet objektov v subore je vacsi ako limit\n");
       return 0;
    }

    while(ChC < count)
    {
        find_neighbours(clusters,count,&c1,&c2);        //cyklus v ktorom najdem najblizsie zhluky
        merge_clusters(&clusters[c1], &clusters[c2]);   //objekty  vlozim do prveho zhluku
        count =  remove_cluster(&*clusters, count, c2); //zmazem druhy zhluk
    }

    while(i < count)                                       //v cykle budem zoradzovat objekty v zhlukoch
    {
        sort_cluster(&clusters[i]);
        i++;
    }

    print_clusters(&*clusters, count);                     //zhluky vytlacim

    i=0;
    while(i < count)                                      //v cykle budem uvolnovat zhluky po jednom
    {
        clear_cluster(&clusters[i]);
        i++;
    }
    free(clusters);                                         //uvolnim alokovanu pamet
}

