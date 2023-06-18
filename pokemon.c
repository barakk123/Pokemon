// Pokemon by Barak Daniel
// Software engineer, second semester, first year
// Course: C programing
// To compile: gcc pokemon.c Pokemons.txt -o pokemon.exe
// To run: .\pokemon.exe Pokemons.txt
// Date: 25/03/2022

// Updated: 19/06/2023 - I only changed the comments up here to upload it as an example of a small C project that I made a year ago.
// Everything found here reflected my knowledge in the first year of the degree and of course does not reflect my current skills or knowledge
//*****-----------------------------------*****

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POKS 6

int id=0;
int ALLPOKS = 151;

//-----*****---**Structs**---*****-------------------------------ד-----------------------------------------------------------------
typedef struct
{
    int ID; //A number given to Pokémons to be recognized
    char* number; //It starts with #
    char* name;
    char* type1;
    char* type2; //Can be NULL for some Pokémons
} Pokemon;

typedef struct 
{
    char* firstName;
    char* lastName;
    Pokemon* pokemonsInBank; //The number of Pokémons the trainer have
    Pokemon pokemonsHeldByTheTrainer[POKS] ; //The Pokémons currently held by the trainer
    
    int AmountOfPokeInBank;
    int AmountOfPokeInHand;
} Trainer;

//-----*****---**Functions declarations**---*****---------------------------------------------------------------------------------
int menu(void);
void changeName(Trainer p);
Pokemon* loadNewPokemons(Pokemon* p1);
void printByType(Pokemon* p);
void exportByType(Pokemon* p,Trainer t);
void sortByName(Pokemon* p);
void sortByType1(Pokemon* p);
void sortByType2(Pokemon* p);
void exportPokemons(Pokemon* p, char* column);
void exportPokemonsByAlphabetical(Pokemon* p,char* column);
Trainer* catchPokemon(Trainer *t , Pokemon *p);
void inBagPrint(Trainer t);
void inBankPrint(Trainer t);
int searchInBank(Trainer* t,int buff);
int pokeToBag(Trainer *t , Pokemon *p,char buffer[]);
int sendToBank(Trainer *t , Pokemon *p,char buffer[],int size);
int swapFromHandToBank(Trainer *t,Pokemon *p,char pokeToBank[],char* pokeToHand,int choice,int i);
int swapFromHandToBank2(Trainer *t,Pokemon *p);
int setPokeFree(Trainer *t,Pokemon *p,int size,int sizeBank,int chs);

//-----*****---**Main**---*****---------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{   
    Trainer t1;
    
    t1.AmountOfPokeInBank=0;
    t1.AmountOfPokeInHand=0;
    char buffer[1024]={'\0'};
    FILE *f = NULL;

if (argc > 1) {
    f = fopen(argv[1], "r");
} else {
    f = fopen("Pokemons.txt", "r");
}

if (f == NULL) {
    printf("Failed to open file\n");
    return 1;
}
    
    printf("\nHowdy new trainer, what is your name? {example:'first name' 'last name'}\n");
    scanf("%s",buffer);
    
    t1.firstName = (char*)malloc(strlen(buffer)+1);
    if (t1.firstName==NULL)
    {
        printf("Out of memory.\n");
        return 1;
    }
    strcpy(t1.firstName,buffer);
    scanf("%s",buffer);
    t1.lastName = (char*)malloc(strlen(buffer)+1);
    if (t1.lastName==NULL)
    {
        printf("Out of memory.\n");
        return 1;
    }
    strcpy(t1.lastName,buffer);
    printf("\nHello %s %s\nWelcome to Pokemon!\n",t1.firstName,t1.lastName);
    
    
    Trainer pokemonsHeldByTheTrainer[POKS]= {'\0'};
    Trainer pokemonsInBank={'\0'};
    
    for (int i = 0; i < POKS; i++)
    {
        t1.pokemonsHeldByTheTrainer[i].number=NULL;
        t1.pokemonsHeldByTheTrainer[i].name=NULL;
        t1.pokemonsHeldByTheTrainer[i].type1=NULL;
        t1.pokemonsHeldByTheTrainer[i].type2=NULL;
    }


    Pokemon *p1=(Pokemon*)malloc(ALLPOKS*sizeof(Pokemon));
    t1.pokemonsInBank=(Pokemon*)malloc((ALLPOKS)*sizeof(char));
    
    for (int i = 0; i < ALLPOKS; i++)
    {
        if (buffer[0]!='#')
        {
            fscanf(f,"%s",buffer);
            p1[i].number = (char *)malloc(strlen(buffer)+1);
            if (p1[i].number==NULL)
            {
                printf("Out of memory.\n");
                return 1;
            }
            strcpy(p1[i].number,buffer);
        }
        else
        {
            p1[i].number = (char *)malloc(strlen(buffer)+1);
            if (p1[i].number==NULL)
            {
                printf("Out of memory.\n");
                return 1;
            }
            strcpy(p1[i].number,buffer);
        }
        
        fscanf(f,"%s",buffer); 
        p1[i].name = (char*)malloc(strlen(buffer)+1);
        if (p1[i].name==NULL)
        {
            printf("Out of memory.\n");
            return 1;
        }
        strcpy(p1[i].name,buffer);
    

        fscanf(f,"%s",buffer);
        p1[i].type1 = (char*)malloc(strlen(buffer)+1);
        if (p1[i].type1==NULL)
        {
            printf("Out of memory.\n");
            return 1;
        }
        strcpy(p1[i].type1,buffer);


        fscanf(f,"%s",buffer);
        p1[i].type2 = (char*)malloc(strlen(buffer)+1);
        if (p1[i].type2==NULL)
        {
            printf("Out of memory.\n");
            return 1;
        }
    
        if (buffer[0]=='#')
        {
            strcpy(p1[i].type2," ");
        }
        else if ((strcmp(p1[i].type1, buffer)==0))
        {
            strcpy(p1[i].type2," ");
        }
        
        else
        strcpy(p1[i].type2,buffer);
        id++;
        p1[i].ID=id;     
    }

    fclose(f);

    /*int op=0;
    while (op!=ALLPOKS)
    {
        printf("\n %d %s %s %s %s ",p1[op].ID,p1[op].number,p1[op].name,p1[op].type1,p1[op].type2);
        ++op;
    }
    */

    printf("\n");
    int chs;
    char column[40];
    menu();
    int n;
    while(scanf("%d",&n) != 1)
    {
        printf("\t*Please enter an integer*: ");
        while(getchar() != '\n');
    }
    while (n != 0)
    {
        switch(n)
        {
            case 1:
                changeName(t1);
                break;
            case 2:
                loadNewPokemons(p1);
                break;
            case 3:
                printByType(p1);
                break;
            case 4:
                exportByType(p1,t1);
                break;
            case 5:
                printf("\nChoose which column do you want to sort and export {Name, Type1, Type2}: ");
				scanf("%s", column);
				exportPokemonsByAlphabetical(p1,column);
                break;
            case 6:
                catchPokemon(&t1,p1);
                break;
            case 7:
                if ((t1.AmountOfPokeInBank==0)||t1.AmountOfPokeInHand==0)
                    {
                        printf("\n* You have no pokemons in the bank yet, you must fill your bag with pokemons first before you can send one to the bank*\n");
                        break;
                    }
                swapFromHandToBank2(&t1,p1);
                break;
            case 8:
                
                printf("\n1 - Release pokemon from your bag\n2 - Release pokemon from your bank\n");
                scanf("%d",&chs);
                if(chs==1)
                {
                    t1.AmountOfPokeInHand=setPokeFree(&t1,p1,t1.AmountOfPokeInHand,t1.AmountOfPokeInBank,chs);
                }
                else if(chs==2)
                {
                    t1.AmountOfPokeInBank=setPokeFree(&t1,p1,t1.AmountOfPokeInHand,t1.AmountOfPokeInBank,chs);        
                }
                else
                {
                    printf("\n*Wrong choice*\n");
                }
                break;
            case 9:
                inBagPrint(t1);
                break;
            case 10:
                inBankPrint(t1);
                break;    
            default:
            printf("\n\t*Please insert valid number*\n");      
        }  
     
    printf("\n");
    menu();

    while(scanf("%d",&n) != 1)
    {
        printf("\t*Please enter an integer*: ");
        while(getchar() != '\n');
    }
    }
    for(int i=0;i<ALLPOKS;i++)
    {
        free(p1[i].name);
        free(p1[i].number);
        free(p1[i].type1);
        free(p1[i].type2);
        free(t1.pokemonsInBank[i].name);
        free(t1.pokemonsInBank[i].number);
        free(t1.pokemonsInBank[i].type1);
        free(t1.pokemonsInBank[i].type2);
    }
    for(int i=0;i<6;i++)
    {
        free(t1.pokemonsHeldByTheTrainer[i].name);
        free(t1.pokemonsHeldByTheTrainer[i].number);
        free(t1.pokemonsHeldByTheTrainer[i].type1);
        free(t1.pokemonsHeldByTheTrainer[i].type2);
    }
    free(t1.firstName);
    free(t1.lastName);
    free(p1);
    

    return 0;
}

//-----*****---**Functions defenitions**---*****----------------------------------------------------------------------------------
int menu(void)
{
    printf("\n\t\t\t          ** Menu **");
    printf("\n\t\t\t          ----------\n");
        printf("\t1  - To change your name\t\t6  - Gotta catch one\n\t2  - To load new Pokemons \t\t7  - Swap Pokemon\n\t3  - Print pokemons by choosen type\t8  - To set Pokemon free\n\t4  - Export pokemons by choosen type\t9  - Pokemons in bag\n\t5  - Alphabetical export\t\t10 - Pokemons in the bank\n ");
        printf("\n\t\t\t          0 - To exit\n");
        printf("\t\t\t          -----------\n");
        printf("\n\t\t    Please choose a number from the menu: ");
}


void changeName(Trainer p)
{
    char buffer[1024]={'\0'};
    printf("Please enter new first name: \n");
    scanf("%s",buffer);
    p.firstName = (char*)realloc(p.firstName, strlen(buffer)+1);
    if(p.firstName == NULL)
    {
        printf("Out of memory.\n");
        exit;
    }
    strcpy(p.firstName,buffer);
    printf("Please enter new last name: \n");
    scanf("%s",buffer);
    p.lastName = (char*)realloc(p.lastName, strlen(buffer)+1);
    if(p.lastName == NULL)
    {
        printf("Out of memory.\n");
        exit;
    }
    strcpy(p.lastName,buffer);
    printf("\nYou changed your name to: %s %s\n",p.firstName,p.lastName);
}


Pokemon* loadNewPokemons(Pokemon* p1)
{
    int count = 0;
    char line;
    char buffer1[1024]= {'\0'};
    char* str = NULL;
    printf("\nPlease enter the name of the file: ");
    scanf("%s",buffer1);
    str = (char*)malloc(strlen(buffer1)+1);
    if (str==NULL)
    {
        printf("Out of memory.\n");
        exit(1);
    }
    
    strcpy(str,buffer1);
    FILE* file;
    fopen_s(&file, str, "r");
    if(file == NULL)
    {
        printf("* Failed opening the file. *\n");
        exit(1);
    }
    for (line = getc(file); line != EOF; line = getc(file))
    {
        if (line == '\n')
        {
            count++;
        }
    }
    count++;
    int previusAllPoks=ALLPOKS;
    ALLPOKS=ALLPOKS + count;
    
    fclose(file);
    fopen_s(&file, str, "r");
    
    char buffer[1024]= {'\0'};

    p1=(Pokemon*)realloc(p1,(ALLPOKS)*sizeof(Pokemon));

    for (int i = previusAllPoks; i < ALLPOKS; i++)
    {
        if (buffer[0]!='#')
        {
            fscanf(file,"%s",buffer);
            p1[i].number = (char *)malloc(strlen(buffer)+1);
            if (p1[i].number==NULL)
            {
                printf("Out of memory.\n");
                exit(1);
            }
            strcpy(p1[i].number,buffer);
        }
        else
        {
            p1[i].number = (char *)malloc(strlen(buffer)+1);
            if (p1[i].number==NULL)
            {
                printf("Out of memory.\n");
                exit(1);
            }
            strcpy(p1[i].number,buffer);
        }
            
        fscanf(file,"%s",buffer); 
        p1[i].name = (char*)malloc(strlen(buffer)+1);
        if (p1[i].name==NULL)
        {
            printf("Out of memory.\n");
            exit(1);
        }
        strcpy(p1[i].name,buffer);
        fscanf(file,"%s",buffer);
        p1[i].type1 = (char*)malloc(strlen(buffer)+1);
        if (p1[i].type1==NULL)
        {
            printf("Out of memory.\n");
            exit(1);
        }
        strcpy(p1[i].type1,buffer);


        fscanf(file,"%s",buffer);
        p1[i].type2 = (char*)malloc(strlen(buffer)+1);
        if (p1[i].type2==NULL)
        {
            printf("Out of memory.\n");
            exit(1);
        }
        
        if (buffer[0]=='#')
        {
            strcpy(p1[i].type2," ");
        }
        else if ((strcmp(p1[i].type1, buffer)==0))
        {
            strcpy(p1[i].type2," ");
        }
            
        else
        strcpy(p1[i].type2,buffer);
        id++;
        p1[i].ID=id;
    }

    fclose(file);
    
    printf("\n*All the new poks loaded successfully*\n");
    return p1;
}

void printByType(Pokemon* p)
{
    char buffer[40]={'\0'};
    int numb=0;
    printf("Please enter a type: ");
    scanf("%s",buffer);
    printf("\n");
    for (int i = 0; i < ALLPOKS; i++)
    {
        if ((strcmp(p[i].type1, buffer)==0) || (strcmp(p[i].type2, buffer) ==0))
        {
            ++numb;
            printf("%s\n",p[i].name);
        }
    }
    printf("\nTotal number of all %s type Pokemons:%d\n",buffer,numb);
}

void exportByType(Pokemon* p,Trainer t)
{
    char buffer[1024]={'\0'};
    char str[1024]={'\0'};
    printf("Please enter a type: ");
    scanf("%s",str);
    FILE* fl = fopen("type.txt", "w");
        if(fl == NULL)
        {
            printf("\n* Failed opening the file. *\n");
            exit(1);
        }
    for (int i = 0; i < ALLPOKS; i++)
    {
        if ((strcmp(p[i].type1, str)==0) || (strcmp(p[i].type2, str) ==0))
        {
            fprintf(fl,"%s %s %s %s\n",p[i].number,p[i].name,p[i].type1,p[i].type2);
        }
    }
    fclose(fl);
    printf("\n* All of the selected type Pokemons exported to file name 'type.txt' *\n");
}


Trainer* catchPokemon(Trainer *t , Pokemon *p)
{
    int fg;
    int flag1=0;
    int bl;
    int flag=0;
    char buffer[1024]={'\0'};
    int pick;
    int counter = 0;
    printf("Please enter the Pokemon name: ");
    scanf("%s",buffer);
    printf("\n");
    for (int i = 0; i < ALLPOKS; i++)
    {
        if ((strcmp(p[i].name,buffer) == 0))
        {
            counter=1;
        }
    }

    if (counter==0)

        printf("\n*There is no such Pokemon named %s*\n",buffer);
    if (counter==1)
    {
        for (int i = 0; i < ALLPOKS; i++)
        {
            if ((strcmp(p[i].name,buffer) == 0))
            {
                for (int j = 0; j < POKS; j++)
                {
                    if ((t->pokemonsHeldByTheTrainer[j].number==NULL) && (flag!=1))
                    {
                        ++id;
                        bl=pokeToBag(t,p,buffer);
                        t->pokemonsHeldByTheTrainer[bl].ID=id;
                        flag=1;
                        return t;
                    }
                    else if (flag == 1)
                    {
                          break;
                    } 
                }

                if (flag ==0)
                {
                    menu1:
                    pick = 0;
                    printf("*Your bag is full*\n\nWhat would you like to do about %s?\n",buffer);
                    printf("1 - Send to bank\n2 - Keep %s in your bag and send another Pokemon to the bank\n3 - Release %s to the wild\n",buffer,buffer);
                    printf("\nPlease choose a number from the menu: ");
                    printf("\n");
                        
                    while(scanf("%d",&pick) != 1)
                    {
                        printf("\nPlease enter an integer: ");
                        while(getchar() != '\n');
                            
                    }

                    if ((pick == 1) && (flag1!=1))
                    {
                        bl=sendToBank(t,p,buffer,t->AmountOfPokeInBank);
                        ++id;
                        t->pokemonsInBank[bl-1].ID=id;
                        t->AmountOfPokeInBank=bl;
                        //printf("\n* %s moved to the Bank *\n",buffer);

                        flag1=1;
                        return t;
                    }

                    else if (pick == 2)
                    {
                        int choice;
                        int counting=0;
                        int tempo;
                        printf("\nPlease choose a Pokemon from your bag\n");
                        for (tempo = 0; tempo < t->AmountOfPokeInHand; tempo++)
                        {  
                            if (!(t->pokemonsHeldByTheTrainer[tempo].name==NULL))
                            {
                                printf("%d - %s\n",tempo+1,t->pokemonsHeldByTheTrainer[tempo].name);
                                ++counting;
                            }
                        }

                        scanf("%d",&choice);
                        if ((choice>counting) || (choice<1))
                        {
                            printf("\n*You have no Pokemons in this spot*\n");
                            goto menu1;
                        }
                        choice=choice-1;
                        swapFromHandToBank(t,p,t->pokemonsHeldByTheTrainer[choice].name,buffer,choice+1,i);
                        return t;
                    }

                    else if (pick == 3)
                    {
                        printf("\n*You have released %s to the wild*\n",buffer);
                    }

                    else
                    {
                        printf("\nWorng input!\nLoading session again...........\n\n\n");
                        goto menu1;
                    }
                } 
            }
        }
    } 
}


void inBagPrint(Trainer t)
    {
        if (t.AmountOfPokeInHand==0)
        {
            printf("You have no pokemons in your bag");
        }
        for (int i = 0; i < POKS; i++)
        {
            if (!(t.pokemonsHeldByTheTrainer[i].name==NULL))
            {
            printf("\n%d %s %s %s %s",t.pokemonsHeldByTheTrainer[i].ID,t.pokemonsHeldByTheTrainer[i].number,t.pokemonsHeldByTheTrainer[i].name,t.pokemonsHeldByTheTrainer[i].type1,t.pokemonsHeldByTheTrainer[i].type2);
            }
        }
        
    }


void inBankPrint(Trainer t)
{
    if (t.AmountOfPokeInBank==0)
    {
        printf("\n*You have no pokemons in your Bank*\n");
    }
        
    for (int op=0;op<t.AmountOfPokeInBank;op++)
    {
        if (!(t.pokemonsInBank[op].name==NULL))
        {
            printf("\n %d %s %s %s %s",t.pokemonsInBank[op].ID,t.pokemonsInBank[op].number,t.pokemonsInBank[op].name,t.pokemonsInBank[op].type1,t.pokemonsInBank[op].type2);
        }
    }
}
    

int searchInBank(Trainer* t,int buff)
{
    for (int i = 0; i < t->AmountOfPokeInBank+1; i++)
    {
        if (t->pokemonsInBank[i].ID==buff)
        {
            printf("\n*Error*\n");
            return i;
        }
        for (int j = 0; j < POKS; j++)
        {
            if (t->pokemonsInBank[i].ID==t->pokemonsHeldByTheTrainer[j].ID)
            {
                printf("\n*Error, The same poke in two places*\n");
            }
        }
    }

    return -1;
}

int pokeToBag(Trainer *t , Pokemon *p,char buffer[])  
{
    int flag=0;
    for (int i = 0; i < ALLPOKS; i++)
    {
        if ((strcmp(p[i].name,buffer) == 0))
            {
                for (int j = 0; j < POKS; j++)
                {
                    if ((t->pokemonsHeldByTheTrainer[j].number==NULL) && (flag!=1))
                    {
                    //Number
                        t->pokemonsHeldByTheTrainer[j].number=(char*)malloc(strlen(p[i].number)*sizeof(char)+1);
                        if (t->pokemonsHeldByTheTrainer[j].number==NULL)
                        {
                            printf("malloc error");
                            exit(1);
                        }
                        t->pokemonsHeldByTheTrainer[j].number = p[i].number;
                    //Name

                        t->pokemonsHeldByTheTrainer[j].name=(char*)malloc(strlen(p[i].name)*sizeof(char)+1);
                        if (t->pokemonsHeldByTheTrainer[j].name==NULL)
                        {
                            printf("malloc error");
                            exit(1);
                        }
                        t->pokemonsHeldByTheTrainer[j].name = p[i].name;
                    //Type1    

                        t->pokemonsHeldByTheTrainer[j].type1=(char*)malloc(strlen(p[i].type1)*sizeof(char)+1);
                        if (t->pokemonsHeldByTheTrainer[j].type1==NULL)
                        {
                            printf("malloc error");
                            exit(1);
                        }
                        t->pokemonsHeldByTheTrainer[j].type1 = p[i].type1;
                    //Type2

                        t->pokemonsHeldByTheTrainer[j].type2=(char*)malloc(strlen(p[i].type2)*sizeof(char)+1);
                        if (t->pokemonsHeldByTheTrainer[j].type2==NULL)
                        {
                            printf("malloc error");
                            exit(1);
                        }
                        t->pokemonsHeldByTheTrainer[j].type2 = p[i].type2;
                        
                    //Id                
                        t->pokemonsHeldByTheTrainer[j].ID = id;
                        printf("\n* %s can be found at spot %d in your bag *\n",buffer,j);
                        flag=1;
                        ++t->AmountOfPokeInHand;
                                    
                        return j;
                    }
                }
            }    
    }
    return -1;
}


int sendToBank(Trainer* t , Pokemon* p,char buffer[],int size)
{
    int flag;
    int test;
    
    for (int i = 0; i < ALLPOKS; i++)
    {
        if ((strcmp(p[i].name,buffer) == 0))
        {
            test = searchInBank(t,p[i].ID);
            if(test!=-1)
            {
                printf("%s already in bank",p[i].name);
                return -2;
            }
        }  
    }

    if(test ==-1)
    {
        int i;
        for (i = 0; i < ALLPOKS; i++)
        {
            if ((strcmp(p[i].name,buffer) == 0))
            {
                break;
            }
        }
             
    //Number              
        t->pokemonsInBank[t->AmountOfPokeInBank].number=(char*)malloc(strlen(p[i].number)*sizeof(char)+1);
        if (t->pokemonsInBank[t->AmountOfPokeInBank].number==NULL)
        {
            printf("malloc error");
            exit(1);
        }
        strcpy(t->pokemonsInBank[t->AmountOfPokeInBank].number,p[i].number);

    //Name
        t->pokemonsInBank[t->AmountOfPokeInBank].name=(char*)malloc(strlen(p[i].name)*sizeof(char)+1);
        if (t->pokemonsInBank[t->AmountOfPokeInBank].name==NULL)
        {
            printf("malloc error");
            exit(1);
        }
        strcpy(t->pokemonsInBank[t->AmountOfPokeInBank].name,p[i].name);

    //Type1
        t->pokemonsInBank[t->AmountOfPokeInBank].type1=(char*)malloc(strlen(p[i].type1)*sizeof(char)+1);
        if (t->pokemonsInBank[t->AmountOfPokeInBank].type1==NULL)
        {
            printf("malloc error");
            exit(1);
        }
        strcpy(t->pokemonsInBank[t->AmountOfPokeInBank].type1,p[i].type1);
                        
    //Type2
        t->pokemonsInBank[t->AmountOfPokeInBank].type2=(char*)malloc(strlen(p[i].type2)*sizeof(char)+1);
        if (t->pokemonsInBank[t->AmountOfPokeInBank].type2==NULL)
        {
            printf("malloc error");
            exit(1);
        }
        strcpy(t->pokemonsInBank[t->AmountOfPokeInBank].type2,p[i].type2);
    
    //AmountOfPokeInBank size    
        t->AmountOfPokeInBank=t->AmountOfPokeInBank+1;
        printf("\n* %s moved to the Bank *\n",buffer);                
        return t->AmountOfPokeInBank;
    }   

    return t->AmountOfPokeInBank;             
}


int pokeToBagSwap(Trainer *t , Pokemon *p,char buffer[],int j)                                               
{
    int flag=0;
    for (int i = 0; i < ALLPOKS; i++)
    {
        if ((strcmp(p[i].name,buffer) == 0))
        {
        //Number        
            t->pokemonsHeldByTheTrainer[j].number=(char*)malloc(strlen(p[i].number)*sizeof(char)+1);
            if (t->pokemonsHeldByTheTrainer[j].number==NULL)
            {
                printf("malloc error");
                exit(1);
            }
            t->pokemonsHeldByTheTrainer[j].number = p[i].number;
            
        //Name
            t->pokemonsHeldByTheTrainer[j].name=(char*)malloc(strlen(p[i].name)*sizeof(char)+1);
            if (t->pokemonsHeldByTheTrainer[j].name==NULL)
            {
                printf("malloc error");
                exit(1);
            }
            t->pokemonsHeldByTheTrainer[j].name = p[i].name;
            
        //Type1
            t->pokemonsHeldByTheTrainer[j].type1=(char*)malloc(strlen(p[i].type1)*sizeof(char)+1);
            if (t->pokemonsHeldByTheTrainer[j].type1==NULL)
            {
                printf("malloc error");
                exit(1);
            }
            t->pokemonsHeldByTheTrainer[j].type1 = p[i].type1;
            
        //Type2
            t->pokemonsHeldByTheTrainer[j].type2=(char*)malloc(strlen(p[i].type2)*sizeof(char)+1);
            if (t->pokemonsHeldByTheTrainer[j].type2==NULL)
            {
                printf("malloc error");
                exit(1);
            }
            t->pokemonsHeldByTheTrainer[j].type2 = p[i].type2;
                   
            printf("\n* %s can be found in the %dth position in your bag *\n",buffer,j+1);
            flag=1;
            if (t->AmountOfPokeInHand<6)
            {
               ++t->AmountOfPokeInHand;
            }
                        
            return j;
        }    
    }
    return -1;
}


int swapFromHandToBank(Trainer *t,Pokemon *p,char pokeToBank[],char* pokeToHand,int choice,int i)
{
    int bl;
    int fg;
    fg=sendToBank(t,p,t->pokemonsHeldByTheTrainer[choice-1].name,t->AmountOfPokeInBank);
    t->pokemonsInBank[fg-1].ID=t->pokemonsHeldByTheTrainer[choice-1].ID;

    bl=pokeToBagSwap(t,p,pokeToHand,choice-1);
    ++id;
    t->pokemonsHeldByTheTrainer[bl].ID = id;
   
}


int swapFromHandToBank2(Trainer *t,Pokemon *p)
{   
    int count=0;
    int te;
    char* pokeToHand; 
    int choose;
    int fg;
    int bl;
    int k; 
    printf("\nPlease choose a Pokemon from the Bank\n");
    for ( k = 0; k < t->AmountOfPokeInBank; k++)
    {
            if (!(t->pokemonsInBank[k].name==NULL))
            {
                printf("%d - %s\n",k+1,t->pokemonsInBank[k].name);
                ++count;
            }
    }

    scanf("%d",&choose);
    if ((choose>count) || (choose<1))
            {
                printf("\n*You have no Pokemons in this spot*\n");
                return 1;
            }
    choose=choose-1;
    pokeToHand=t->pokemonsInBank[choose].name; 
    
    char* buffer1;
    int temp; 
    int flagg=0; 
    int choice;
    int i;
    int counting=0;
    for ( i = 0; i < ALLPOKS; i++)
    {
        if ((strcmp(p[i].name,pokeToHand) == 0)&&(flagg==0))
        {   int tempo;
            printf("\nPlease choose a Pokemon from your bag\n");
            for (tempo = 0; tempo < t->AmountOfPokeInHand; tempo++)
            {
               if (!(t->pokemonsHeldByTheTrainer[tempo].name==NULL))
                {
                printf("%d - %s\n",tempo+1,t->pokemonsHeldByTheTrainer[tempo].name);
                ++counting;
                }
            }
            
            scanf("%d",&choice);
            te=choice;
            if ((choice>counting) || (choice<1))
            {
                printf("\n*You have no Pokemons in this spot*\n");
                return 1;
            }
        
        //Number
            buffer1=t->pokemonsInBank[choose].number;
            t->pokemonsInBank[choose].number=(char*)malloc(strlen(t->pokemonsHeldByTheTrainer[choice-1].number)*sizeof(char)+1);
            t->pokemonsInBank[choose].number=t->pokemonsHeldByTheTrainer[choice-1].number;
            t->pokemonsHeldByTheTrainer[choice-1].number= (char *)malloc(strlen(buffer1)+1);
            t->pokemonsHeldByTheTrainer[choice-1].number=buffer1;

        //Name
            buffer1=t->pokemonsInBank[choose].name;
            //printf("\n*%s*\n",buffer1);
            t->pokemonsInBank[choose].name=(char*)malloc(strlen(t->pokemonsHeldByTheTrainer[choice-1].name)*sizeof(char)+1);
            t->pokemonsInBank[choose].name=t->pokemonsHeldByTheTrainer[choice-1].name;
            t->pokemonsHeldByTheTrainer[choice-1].name=(char*)malloc(strlen(t->pokemonsInBank[choose].name)*sizeof(char)+1);
            t->pokemonsHeldByTheTrainer[choice-1].name=buffer1;
            
        //Type1
            buffer1=t->pokemonsInBank[choose].type1;
            //printf("\n*%s*\n",buffer1);
            t->pokemonsInBank[choose].type1=(char*)malloc(strlen(t->pokemonsHeldByTheTrainer[choice-1].type1)*sizeof(char)+1);
            t->pokemonsInBank[choose].type1=t->pokemonsHeldByTheTrainer[choice-1].type1;
            t->pokemonsHeldByTheTrainer[choice-1].type1=(char*)malloc(strlen(t->pokemonsInBank[choose].type1)*sizeof(char)+1);
            t->pokemonsHeldByTheTrainer[choice-1].type1=buffer1;

        //Type2
            buffer1=t->pokemonsInBank[choose].type2;
            //printf("\n*%s*\n",buffer1);
            t->pokemonsInBank[choose].type2=(char*)malloc(strlen(t->pokemonsHeldByTheTrainer[choice-1].type2)*sizeof(char)+1);
            t->pokemonsInBank[choose].type2=t->pokemonsHeldByTheTrainer[choice-1].type2;
            t->pokemonsHeldByTheTrainer[choice-1].type2=(char*)malloc(strlen(t->pokemonsInBank[choose].type2)*sizeof(char)+1);
            t->pokemonsHeldByTheTrainer[choice-1].type2=buffer1;

        //ID    
            temp=t->pokemonsInBank[choose].ID;
            t->pokemonsInBank[choose].ID=t->pokemonsHeldByTheTrainer[choice-1].ID;
            t->pokemonsHeldByTheTrainer[choice-1].ID=temp;
            flagg=1;
            printf("\n* %s can be found in the %dth position in your bag *",pokeToHand,te);
            printf("\n* %s moved to the bank *\n",t->pokemonsInBank[choose].name);
            return 0;
        }          
    }
}


int setPokeFree(Trainer *t,Pokemon *p,int size,int sizeBank,int chs)
{         
    int choose;
    char* te;
    if (chs==1)
    {
        if(size==0)
        {
            printf("\nYou dont even have one pokemon in your bag.\n");
            return 0;
        }
        
        printf("\nPlease choose a Pokemon from your bag\n");
        for (int i = 0; i < size; i++)
        {
            if (!(t->pokemonsHeldByTheTrainer[i].name==NULL))
            {
                printf("%d - %s\n",i+1,t->pokemonsHeldByTheTrainer[i].name);
            }
        }

        scanf("%d",&choose);
        if ((choose>size)||(choose<1))
        {
            printf("\nYou have no Pokemons in this spot\n");
            return size;
        }
        
        choose=choose-1;
        te = strdup(t->pokemonsHeldByTheTrainer[choose].name);
        free(t->pokemonsHeldByTheTrainer[choose].name);
        t->pokemonsHeldByTheTrainer[choose].name = NULL;
        free(t->pokemonsHeldByTheTrainer[choose].number);
        t->pokemonsHeldByTheTrainer[choose].number = NULL;
        free(t->pokemonsHeldByTheTrainer[choose].type1);
        t->pokemonsHeldByTheTrainer[choose].type1 = NULL;
        if (t->pokemonsHeldByTheTrainer[choose].type2)
        {
            free(t->pokemonsHeldByTheTrainer[choose].type2);
            t->pokemonsHeldByTheTrainer[choose].type2 = NULL;
        }
                
        if (choose < size)
        {
            Trainer *temp = malloc(sizeof(Trainer));
            for (int k = 0; k < size; k++)
            {
                temp->pokemonsHeldByTheTrainer[k].ID = 0;
                temp->pokemonsHeldByTheTrainer[k].name = NULL;
                temp->pokemonsHeldByTheTrainer[k].number = NULL;
                temp->pokemonsHeldByTheTrainer[k].type1 = NULL;
                temp->pokemonsHeldByTheTrainer[k].type2 = NULL;
            }
            for (int k = 0, z = 0; k < size; k++)
                if (k != choose)
                    temp->pokemonsHeldByTheTrainer[z++] = t->pokemonsHeldByTheTrainer[k];
            for (int k = 0; k < size; k++)
                t->pokemonsHeldByTheTrainer[k] = temp->pokemonsHeldByTheTrainer[k];
            size--;
            printf("\n*You have released %s to the wild*\n", te);
            free(te);
            return size;
        }    
    }

    else if (chs==2)
    {
        
        int i;
        int id=0;
        char buff[1024]={' '};
        printf("\nEnter the id of the Pokemon you wish to release\n");
        scanf("%d",&id);
        for(i=0;i<sizeBank;i++)
        {
            if(t->pokemonsInBank[i].ID==id)
            {
                printf("\n*You have released %s to the wild*\n",t->pokemonsInBank[i].name);
                t->pokemonsInBank[i].ID=0;
                strcpy(t->pokemonsInBank[i].number,buff);
                strcpy(t->pokemonsInBank[i].name,buff);
                strcpy(t->pokemonsInBank[i].type1,buff);
                strcpy(t->pokemonsInBank[i].type2,buff);
                sizeBank--;
                return sizeBank;
            }
        }
        printf("\n* Could not find this id in your Bank *\n");
        return sizeBank;
    }
}


void sortByName(Pokemon* p)
{
	for (int i = 0; i < ALLPOKS; i++)
		for (int k = 0; k < ALLPOKS; k++)
			if (strcmp(p[i].name, p[k].name) < 0)
			{
				Pokemon t = p[i];
				p[i] = p[k];
				p[k] = t;
			}
}

void sortByType1(Pokemon* p)
{
	for (int i = 0; i < ALLPOKS; i++)
		for (int k = 0; k < ALLPOKS; k++)
			if (strcmp(p[i].type1, p[k].type1) < 0)
			{
				Pokemon t = p[i];
				p[i] = p[k];
				p[k] = t;
			}
}

void sortByType2(Pokemon* p)
{
	Pokemon t;
	for (int i = 0; i < ALLPOKS; i++)
		for (int k = 0; k < ALLPOKS; k++)
			if (p[i].type2 && p[k].type2 == NULL)
			{
				t = p[i];
				p[i] = p[k];
				p[k] = t;
				break;
			}
	for (int i = 0; i < ALLPOKS; i++)
		for (int k = 0; k < ALLPOKS; k++)
			if (p[i].type2 && p[k].type2 && strcmp(p[i].type2, p[k].type2) < 0)
			{
				t = p[i];
				p[i] = p[k];
				p[k] = t;
			}
}

void exportPokemons(Pokemon* p, char* column)
{
	char txt[40] = "Pokemons_";
	strcpy(txt, column);
	strcat(txt, ".txt");
	FILE* files = fopen(txt, "w");
	if (files)
	{
		for (int i = 0; i < ALLPOKS; i++)
		{
			fprintf(files, "%s %s %s ", p[i].number, p[i].name, p[i].type1);
			if (p[i].type2)
				fprintf(files, "%s\n", p[i].type2);
			else
				fprintf(files, "\n");
		}
		printf("\n* The pokemons saved succesfully in '%s' *\n", txt);
		fclose(files);
	}
	else
		printf("\n*Could not open a file*\n");
}

void exportPokemonsByAlphabetical(Pokemon* p,char* column)
{
	int choose = 0;
	if (strcmp(column, "Name") == 0)
	{
		sortByName(p);
		choose = 1;
	}
	if (strcmp(column, "Type1") == 0)
	{
		sortByType1(p);
		choose = 1;
	}
	if (strcmp(column, "Type2") == 0)
	{
		sortByType2(p);
		choose = 1;
	}
	if (choose)
		exportPokemons(p, column);
	else
		printf("\n* The column is not match! *\n");
}





