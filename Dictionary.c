#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/acct.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "bt.h"
#include "bc.h"
#include "btree.h"
#include "soundex.h"
#include "readline.h"

struct timespec ts, start, end;
BTA *dic=NULL,*soundex=NULL;
void add_new(BTA *dic,BTA *soundex, char* ckey);         //them tu vao tu dien
void edit(BTA *dic, BTA *soundex, char *key);           //cap nhat tu dien
void delete_word(BTA *dic,BTA *soundex,char *key);      //delete_word
void seacrch_word(BTA *dic, BTA *soundex,char *key);    //tim kiem
void insert(BTA *dic,BTA *soundex, char *key, char *data);
void update(BTA *dic,BTA *soundex, char *key, char *data);
void delete(BTA *dic,BTA *soundex, char *key);

int main(int argc ,char *argv[])
{   
    int i;
    btinit(); //mo file btree
    dic=btopn("word.dic",0,1);
    if(dic==NULL)
    {
        printf("No data! Data automatically generated empty!\n");
        dic=btcrt("word.dic",0,1);
    }
    soundex=btopn("soundex.dic",0,1);
    if(soundex==NULL)
    {
        printf("No data! Data automatically generated empty!\n");
        soundex=btcrt("soundex.dic",0,1);
    }
    loaddata();

    //---------------------------------------------------
    // case 1: add new word

    if (argc == 3 && strcmp(argv[1],"new") == 0) {
        add_new(dic, soundex, argv[2]);
    }

    //----------------------------------------------------
    // case 2: edit meaning
    if (argc == 3 && strcmp(argv[1],"edit")==0){
        edit(dic, soundex, argv[2]);
    }
    //---------------------------------------------------
    // case 3: delete word
    if(argc == 3 && strcmp(argv[1],"delete")==0){
        delete_word(dic,soundex,argv[2]);
    }
    //----------------------------------------------------
    // case :search word
    if(argc == 3 && strcmp(argv[1],"search")==0){
        seacrch_word(dic,soundex,argv[2]);  
    }
    btcls(dic);
    btcls(soundex);
}

void insertmenu()
{

    system("clear");
    printf("------------------------------- Add new word ---------------------------------\n");
}
void insert(BTA *dic,BTA *soundex, char *key, char *data)
{
    char soundexcode[10];
    int i;
    clock_gettime(CLOCK_REALTIME, &start);
    SoundEx(soundexcode,key,4,1);//chuyen thanh xau soundex
    btins(dic,key,data,strlen(data)+1);//chen vao dic
    i=btins(soundex,key,soundexcode,strlen(key)+1); //chen soundex_word vao soundex
    if(i!=0)
        printf("\nError adding new words to soundex!\n");
    else
        printf("\n Add \"%s\" successful!\n", key);
    insertarray(key);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Running time:  %u nanoseconds\n", (unsigned int)((end.tv_nsec - start.tv_nsec)));
    loaddata(dic);
}

void add_new(BTA *dic,BTA *soundex, char* ckey)
{
    loaddata();
    system("clear");
    char soundexcode[10],cdata[500],*data,*key, choice;
    int i,rsize;
    do
    {
        insertmenu();
        trim(ckey);
        key = strtok(ckey,"\n");
        if(ckey[0]=='\n')
        {
            printf("\nEnter the missing data!\n\n Input any key for input again or press Esc for exit: ");
            scanf("%c", &choice);
            while(getchar()!='\n');
            if(choice!=27)
                continue;
            else
                break;
        }
        else if(ckey[0]==27)
            break;
        else
        {
            trim(key);
            if(bfndky(dic,key,&rsize)==0)
            {
                btsel(dic,ckey,cdata,500,&rsize);
                printf("\"%s\" already in this dictionary!\n\nPress any key for update \"%s\" or press Esc for exit: ", key,key);
                scanf("%c", &choice);
                while(getchar()!='\n');
                if(choice!=27)
                {
                    back_insert_update: ;
                    system("clear");
                    printf("---------------------------update---------------------------\n");
                    printf("Word : ");
                    printf("%s\n", key);
                    printf("Meaning: %s\n", cdata);
                    printf("Update : ");
                    fgets(cdata,500,stdin);
                    trim(cdata);
                    data = strtok(cdata,"\n");
                    if(cdata[0]=='\n')
                    {
                        printf("\nInput the missing data!\n\nPress any key for input again or press Esc for exit: ");
                        scanf("%c", &choice);
                        while(getchar()!='\n');
                        if(choice!=27)
                            goto back_insert_update;
                        else
                            break;
                    }
                    else if(cdata[0]==27)
                        break;
                    else
                    {
                        trim(data);
                        update(dic, soundex, key, data);
                    }
                }
                else
                    break;
            }
            else
            {
                back_insert: ;
                insertmenu();
                printf("Input word: ");
                printf("%s\n", key);
                printf("Input meaning: ");
                fgets(cdata,500,stdin);
                trim(cdata);
                data = strtok(cdata,"\n");
                if(cdata[0]=='\n')
                {
                    printf("\nInput the missing data!\n\nPress any key for input again or press Esc for exit: ");
                    scanf("%c", &choice);
                    while(getchar()!='\n');
                    if(choice!=27)
                        goto back_insert;
                    else
                        break;
                }
                else if(data[0]==27)
                    break;
                else
                {
                    trim(data);
                    insert(dic, soundex, key, data);
                }
            }

        }
        printf("\n(Press any key for input to update again or press Esc for exit) ");
        scanf("%c", &choice);
        while(getchar()!='\n');
        if(choice!=27)
            continue;
        else
            break;
    }while(1);
    system("clear");
}

void updatemenu()
{
    system("clear");
    printf("---------------------------Update new meaning ---------------------------\n");
}

void update(BTA *dic,BTA *soundex, char *key, char *data)
{
    char soundexcode[10];
    int i;
    clock_gettime(CLOCK_REALTIME, &start);
    SoundEx(soundexcode,key,4,1);//chuyen thanh xau soundex
    btupd(dic,key,data,strlen(data)+1);//chen vao dic
    i=btupd(soundex,key,soundexcode,strlen(key)+1); //chen soundex_word vao soundex
    if(i!=0)
        printf("\nError updating means in soundex!\n");
    else
        printf("\nUpdate \"%s\" successful! !!!\n", key);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Running time: %u nanoseconds\n", (unsigned int)((end.tv_sec - end.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec)));
}
//---------------------------------------------------------------------------------------------------------------
void edit(BTA *dic,BTA *soundex, char *key)
{
    system("clear");
    char soundexcode[100],ckey[200],cdata[500],*data, ch, choice;
    int i,rsize;
    do
    {
        updatemenu();
        if(bfndky(dic,key,&rsize)!=0)
            {
                printf("\n \"%s\" not in the dictionary of Natural \n press any key to add the word \"%s\" or press ESC for exit:", key,key);
                scanf("%c", &choice);
                while(getchar()!='\n');
                if(choice!=27)
                {
                    back_update_insert: ;
                    system("clear");
                    printf("----------------------------- Update (Add new Word)----------------------------\n");
                    printf("Word : ");
                    printf("%s\n", key);
                    printf("\nMeaning: ");
                    fgets(cdata,500,stdin);
                    trim(cdata);
                    data = strtok(cdata,"\n");
                    if(cdata[0]=='\n')
                    {
                        printf("\nInput the missing data!\n\nPress any key for input again or press Esc for exit: ");
                        scanf("%c", &choice);
                        while(getchar()!='\n');
                        if(choice!=27)
                            goto back_update_insert;
                        else
                            break;
                    }
                    else if(cdata[0]==27)
                        break;
                    else
                    {
                        trim(data);
                        insert(dic, soundex, key, data);
                    }
                }
                else
                    break;
            }
            
            else
            {
                back_update: ;
                updatemenu();
                btsel(dic,key,cdata,500,&rsize);
                printf("\nMeaning : %s", cdata);
                printf("\nUpdate: ");
                fgets(cdata,500,stdin);
                data = strtok(cdata,"\n");
                 if(cdata[0]=='\n')
                {
                    printf("\nInput the missing data!\n\nPress any key for input again or press Esc for exit: ");
                    scanf("%c", &choice);
                    while(getchar()!='\n');
                    if(choice!=27)
                        goto back_update;
                    else
                        break;
                }
                else if(data[0]==27)
                        break;
                else
                    update(dic, soundex, key, data);
            }
        printf("\n(Press any key for update again or press Esc for exit:): ");
        scanf("%c", &choice);
        while(getchar()!='\n');
        if(choice!=27)
            continue;
        else
            break;
    }while(1);
    system("clear");
}  

void deletemenu()
{
    system("clear");
    printf("-----------------------------------Delete word --------------------------------\n");
}

void delete(BTA *dic,BTA *soundex, char *key)
{
    char soundexcode[100];
    int i;
    clock_gettime(CLOCK_REALTIME, &start);
    SoundEx(soundexcode,key,4,1);//chuyen thanh xau soundex
    btdel(dic,key);//chen vao dic
    i=btdel(soundex,key); //chen soundex_word vao soundex
    if(i!=0)
        printf("\nError updating means in soundex!\n");
    else
        printf("\n Delete \"%s\" successful!\n", key);
    //deletearray(key);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Running time:  %u nanoseconds\n", (unsigned int)((end.tv_nsec - start.tv_nsec)));
    loaddata(dic);
}

void delete_word(BTA *dic,BTA *soundex,char *key)
{
    system("clear");
    char soundexcode[100],ckey[200],cdata[500],*data, ch, choice;
    int i,rsize;
        deletemenu();
    if(bfndky(dic,key,&rsize)!=0)
    {
        printf("\n\"%s\" not in this dictionary!\n\n", key);
    }
    else 
        delete(dic, soundex, key);
}
//-----------------------------------------------------------------------------------------------------------------


void searchmenu()
{
    system("clear");
    printf("----------------------------- Search Word ----------------------------------\n");
}

void seacrch_word(BTA *dic, BTA *soundex,char *key)
{
     system("clear");
    char soundexcode[100],ckey[200],cdata[500],*data, ch, choice,*soundextemp[20];
    char soundexcodesearch[20],soundexkey[81];
    int i,j,rsize,size;
    searchmenu();
    i = 0;
    if(btsel(dic,key,cdata,100, &rsize) !=0)
    {
        printf("\n\"%s\" not in this dictionary\nBelow the same  \"%s\": \n\n", key,key);
        SoundEx(soundexcodesearch,key, 4,1);
        btpos(soundex,1);
        while ( btseln(soundex, soundexkey, soundexcode,200, &size)==0)
        {
            if((strcmp(soundexcodesearch,soundexcode)==0) && (strcmp(soundexkey,key)!=0))
            {
                printf("%s\t",soundexkey);
                soundextemp[i] = (char*) malloc(200);
                strcpy(soundextemp[i],soundexkey);
                i++;
            }
        }
        printf("\n");

        if(i==0)
        {
            printf("\nNot any word same \"%s\" in this dictionary !\n",key);
            
        }

    }
    else
    {
        printf("\n\"%s\" ---> %s\n", key, cdata);
        printf("\n Found \"%s\" in this dictionary \n",key);
    }
}

