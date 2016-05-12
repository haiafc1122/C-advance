char* words_arr[10000000];
int chiso;
void loaddata(BTA *dic)
{
    //BTA *pfile;
    //btinit();
    //pfile = btopn("word.dic",0,0);
    //int chiso;
    int rsize;
    char key[200], data[500];
    chiso = 0;
    btpos(dic, 1);
    while((bnxtky(dic, key, &rsize)==0))
    {
        //printf("%s\n",key);
        words_arr[chiso] = (char*) malloc(200);
        strncpy(words_arr[chiso],key,200);
        chiso++;
        //printf("%s\n",key);
        //printf("%s\t",words_arr[chiso]);

    }
    //btcls(pfile);
}

char *my_generator (const char *text, int state)
{
    static int list_index, len;
    const char *name;

    if (!state)
    {
        list_index = 0;
        len = strlen (text);
    }

    while (name = words_arr[list_index])
    {
        list_index++;
        if (strncmp (name, text, len) == 0)
            return strdup (name);
        if(list_index>10000000)
            break;
    }

    // If no names matched, then return NULL.
    return ((char *) NULL);
}

// Custom completion function
static char **my_completion (const char *text, int start, int end)
{
    // This prevents appending space to the end of the matching word
    rl_completion_append_character = '\0';

    char **matches = (char **) NULL;
    if (start == 0)
    {
        matches = rl_completion_matches ((char *) text, &my_generator);
    }
    //else rl_bind_key ('\t', rl_abort);
    return matches;
}
void insertarray(char *key)
{
    words_arr[chiso] = (char*) malloc(200);
    strcpy(words_arr[chiso],key);
    chiso++;
}

void deletearray(char *key)
{
    int pos = searcharray(key);
    int i = 0;
    for ( i = pos - 1 ; i < 10000000 - 1 ; i++ )
         words_arr[i] = words_arr[i+1];
    //printf("%s", words_arr[0]);
}

int searcharray(char *key)
{
    int i = 0;
    int pos = 0;
    for(i=0;i<10000000;i++)
        if(strcmp(key,words_arr[i])!=0)
            pos++;
        else
            break;
    return pos+1;
    //printf("%s", words_arr[0]);
}
void trim(char *s)
{
    char *p=s+strlen(s)-1;
    while(*p==' '||*p=='\t')
        *p--='\0';
	p=s;
	while(*p==' '||*p=='\t')
        p++;
	while(*p!='\0')
	{
		if(*p==' '||*p=='\t')
		{
		    *s++=' ';
            while(*++p==' '||*p=='\t');
        }
		*s++=*p++;
	}
	*s='\0';
}
