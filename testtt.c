void seacrch_word(BTA *dic, BTA *soundex,char *key)
{
     system("clear");
    char soundexcode[100],ckey[200],cdata[500],*data, ch, choice,*soundextemp[20];
    char soundexcodesearch[20],soundexkey[81];
    int i,j,rsize,size;

    searchmenu();
    back_search_2: ;
    
    clock_gettime(CLOCK_REALTIME, &start);
    if(btsel(dic,key,cdata,100, &rsize) !=0)
    {
        printf("\n\"%s\" This is not in the dictionary! \nHere are words similar to \"%s\": \n\n", key,key);
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
        if(i==0)
        {
            printf("\nNo words similar to  \" %s \" in this dictionary!\n",key);
        }
    }
    else
    {
        printf("\"%s\": %s\n", key, cdata);
        clock_gettime(CLOCK_REALTIME, &end);
        printf("Thoi gian chay :  %u nanoseconds\n", (unsigned int)((end.tv_nsec - start.tv_nsec)));
        loaddata(dic);
    }
}