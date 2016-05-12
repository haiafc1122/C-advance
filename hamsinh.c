#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.c"
#include "jrb.h"
#include "jval.c"
#include "jval.h"
#include "fields.h"
#include <time.h>
#include "bt.h"
#include "btree.h"
//timer_t start,end;
//struct timespec ts, start, end;

// void randomString(int size, char* output)
// {
//     char bangchucai[] = "abcdefghijklmnopqrstuvwxyz";
//     size = rand()%size +3;
//     int i;
//     for (i = 0; i < size; ++i)
//         output[i] = bangchucai[rand() % (sizeof(bangchucai) - 1)];
//     output[size] = 0;
// }
main()
{
    //start = time(NULL);
    FILE *p,*q,*r,*f1,*f2,*f3;
    int i,n;
    JRB a,b,c;
    a = make_jrb();
    char ch[100];
 //    printf("Nhap so tu: ");
 //    scanf("%d", &n);
 //    while(getchar()!='\n');
 //    q = fopen("file1.txt", "wt");
 //    p = fopen("file2.txt", "wt");
 //    //fputs("//Nghia Tieng Viet\n", p);
 //    //fputs("//Tu Tieng Anh\n", q);
 //    //clock_gettime(CLOCK_REALTIME, &start);
	// for (i=0; i<n; i++)
 //    {
 //        randomString(100, ch);
 //        c = jrb_find_str(a, ch);
 //        if(c == NULL)
 //        {
 //            fputs(ch,p);
 //            fputs("\n",p);
 //            jrb_insert_str(a,strdup(ch) ,new_jval_i(NULL));
 //        }
 //        else
 //            i--;
 //    }
 //    jrb_traverse(b,a)
 //    {
 //        fputs(jval_s(b->key),q);
 //        fputs("\n",q);
 //    }
 //    fclose(q);
 //    fclose(p);


    char ta[20],tv[40], x[50];
    f1 = fopen("file11.txt","rt");
    f2 = fopen("file22.txt","rt");
    f3 = fopen("sample1.dic","wt");
    fprintf(f3,"%s","[");
    fprintf(f3, "%s","\n");
    while((!feof(f1)))
    {
        fscanf(f1,"%s\n",ta);
        fprintf(f3,"%s","{");
        fprintf(f3,"%s",ta);
        fprintf(f3,"%s","}");
        fprintf(f3,"%s",":");
        fscanf(f2,"%s\n",tv);
        fprintf(f3,"%s","{");
        fprintf(f3,"%s",tv);
        fprintf(f3,"%s","}");
        if((!feof(f1)))
            fputs(",\n", f3);
    }
    fprintf(f3, "%s","\n");
    fprintf(f3,"%s","]");
    fclose(f1);
    fclose(f2);
    fclose(f3);
   // clock_gettime(CLOCK_REALTIME, &end);
    //printf("time for this algorithm = %u nanoseconds\n", (unsigned int)((end.tv_sec - end.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec)));
    //end = time(NULL);
    //printf("Thoi gian chay: %f giay", difftime(end,start));

    /*btinit();
    FILE *f = fopen("AnhViet.Dic","r");
    char key[40], w[50], s[50];
    char d;
    BTA *b1, *b2;
    b1 = btcrt("word.dic", 0, 0);
    b2 = btcrt("soundex.dic", 0, 0);
    char data[50000];
    fgetc(f);
    while (!feof(f))
    {
        fscanf(f,"%s\n", s);
        strcpy(key, s);
        n=0;
        while( (!feof(f)) && ((d=fgetc(f)) !='@') && (d!=EOF))
			 data[n++]=d;
        data[n]='\0';
        //printf("%s\n",data);
        btins(b1, key, data, strlen(data)+1);
        SoundEx(w, key, 4, 1);
        btins(b2, key, w, strlen(w)+1);
    }
    btcls(b1);
    btcls(b2);
    return 0;*/
}







//ham soundex
 int SoundEx(char *SoundEx, char *WordString, int   LengthOption, int   CensusOption)
{
    int  InSz = 31;
    char WordStr[32];     /* one bigger than InSz */
    int  SoundExLen, WSLen, i;
    char FirstLetter, *p, *p2;
    SoundExLen = WSLen = 0;
    SoundEx[0] = 0;
    if(CensusOption)
        LengthOption = 4;
    if(LengthOption)
        SoundExLen = LengthOption;
    if(SoundExLen > 10)
        SoundExLen = 10;
    if(SoundExLen < 4)
        SoundExLen = 4;
    if(!WordString)
        return(0);
      /* Copy WordString to WordStr
       * without using funcs from other
       * libraries.
      */
    for(p = WordString,p2 = WordStr,i = 0;(*p);p++,p2++,i++)
    {
        if(i >= InSz) break;
        (*p2) = (*p);
    }
    (*p2) = 0;
      /* Convert WordStr to
       * upper-case, without using funcs
       * from other libraries
      */
    for(p = WordStr;(*p);p++)
    {
        if( (*p) >= 'a' && (*p) <= 'z' )
            (*p) -= 0x20;
    }
      /* convert all non-alpha
       * chars to spaces
      */
    for(p = WordStr;(*p);p++)
    {
        if( (*p) < 'A' || (*p) > 'Z' )
            (*p) = ' ';
    }
      /* Re//move leading spaces
      */
    for(i = 0, p = p2 = WordStr;(*p);p++)
    {
        if(!i)
        {
            if( (*p) != ' ' )
            {
                (*p2) = (*p);
                p2++;
                i++;
            }
        }
        else
        {
            (*p2) = (*p);
            p2++;
        }
    }
    (*p2) = 0;
      /* Get length of WordStr
      */
    for(i = 0,p = WordStr;(*p);p++) i++;
      /* Re//move trailing spaces
      */
        for(;i;i--)
        {
            if(WordStr[i] == ' ')
                WordStr[i] = 0;
            else
              break;
        }
      /* Get length of WordStr
      */
    for(WSLen = 0,p = WordStr;(*p);p++) WSLen++;
        if(!WSLen)
            return(0);
      /* Perform our own multi-letter
       * improvements
       *
       * underscore placeholders (_) will be
       * re//moved below.
      */
    if(!CensusOption)
    {
        if(WordStr[0] == 'P' && WordStr[1] == 'S')
              WordStr[0] = '_';
        if(WordStr[0] == 'P' && WordStr[1] == 'F')
              WordStr[0] = '_';
        for(i = 0;i < WSLen;i++)
        {
            if(WordStr[i] == 'D' && WordStr[i+1] == 'G')
            {
                WordStr[i] = '_';
                i++;
                continue;
            }
            if(WordStr[i] == 'G' && WordStr[i+1] == 'H')
            {
                WordStr[i] = '_';
                i++;
                continue;
            }
            if(WordStr[i] == 'K' && WordStr[i+1] == 'N')
            {
                WordStr[i] = '_';
                i++;
                continue;
            }
            if(WordStr[i] == 'G' && WordStr[i+1] == 'N')
            {
                WordStr[i] = '_';
                i++;
                continue;
            }
            if(WordStr[i] == 'M' && WordStr[i+1] == 'B')
            {
                WordStr[i+1] = '_';
                i++;
                continue;
            }
            if(WordStr[i] == 'P' && WordStr[i+1] == 'H')
            {
                WordStr[i] = 'F';
                WordStr[i+1] = '_';
                i++;
                continue;
            }
            if(WordStr[i]  ==  'T'  && WordStr[i+1] == 'C' && WordStr[i+2] == 'H')
            {
                WordStr[i] = '_';
                i++; i++;
                continue;
            }
            if(WordStr[i] == 'M' && WordStr[i+1] == 'P' && (WordStr[i+2] == 'S' || WordStr[i+2] == 'T' || WordStr[i+2] == 'Z'))
            {
                WordStr[i+1] = '_';
                i++;
            }
        }
    } /* end if(!CensusOption) */
      /* squeeze out underscore characters
       * added as a byproduct of above process
       * (only needed in c styled replace)
      */
    for(p = p2 = WordStr;(*p);p++)
    {
        (*p2) = (*p);
        if( (*p2) != '_' )
            p2++;
    }
    (*p2) = 0;
      /* This must be done AFTER our
       * multi-letter replacements
       * since they could change
       * the first letter
      */
      FirstLetter = WordStr[0];
      /* In case we're in CensusOption
       * 1 and the word starts with
       * an 'H' or 'W'
       *  (v1.0c djr: add test for H or W)
      */
    if(FirstLetter == 'H' || FirstLetter == 'W')
        WordStr[0] = '-';
      /* In properly done census
       * SoundEx, the H and W will
       * be squezed out before
       * performing the test
       * for adjacent digits
       * (this differs from how
       * 'real' vowels are handled)
      */
    if(CensusOption == 1)
        for(p = &(WordStr[1]);(*p);p++)
            if((*p) == 'H' || (*p) == 'W')
                 (*p) = '.';
      /* Perform classic SoundEx
       * replacements.
      */
    for(p = WordStr;(*p);p++)
    {
        if( (*p) == 'A'   || (*p) == 'E'   || (*p) == 'I'   || (*p) == 'O'   || (*p) == 'U'   || (*p) == 'Y'   || (*p) == 'H'   ||(*p) == 'W')
            (*p) = '0';   /* zero */
        if( (*p) == 'B'   || (*p) == 'P'   || (*p) == 'F'   || (*p) == 'V')
            (*p) = '1';
        if( (*p) == 'C'   || (*p) == 'S'   || (*p) == 'G'   || (*p) == 'J'   || (*p) == 'K'   || (*p) == 'Q'   || (*p) == 'X'   || (*p) == 'Z')
            (*p) = '2';
        if( (*p) == 'D'   || (*p) == 'T')
            (*p) = '3';
        if( (*p) == 'L' )
            (*p) = '4';
        if( (*p) == 'M'   || (*p) == 'N')
            (*p) = '5';
        if( (*p) == 'R' )
            (*p) = '6';
    }
      /* soundex replacement loop done  */
      /* In properly done census
       * SoundEx, the H and W will
       * be squezed out before
       * performing the test
       * for adjacent digits
       * (this differs from how
       * 'real' vowels are handled)
      */
    if(CensusOption == 1)
    {
          /* squeeze out dots
          */
        for(p = p2 = &WordStr[1];(*p);p++)
        {
            (*p2) = (*p);
            if( (*p2) != '.' )
                p2++;
        }
        (*p2) = 0;
    }
      /* squeeze out extra equal adjacent digits
       * (don't include first letter)
       * v1.0c djr (now includes first letter)
      */
    for(p = p2 = &(WordStr[0]);(*p);p++)
    {
        (*p2) = (*p);
        if( (*p2) != p[1] )
            p2++;
    }
    (*p2) = 0;
      /* squeeze out spaces and zeros
       * Leave the first letter code
       * to be replaced below.
       * (In case it made a zero)
      */
    for(p = p2 = &WordStr[1];(*p);p++)
    {
        (*p2) = (*p);
        if( (*p2) != ' ' && (*p2) != '0' )
            p2++;
    }
    (*p2) = 0;
      /* Get length of WordStr
      */
    for(WSLen = 0,p = WordStr;(*p);p++) WSLen++;
      /* Right pad with zero characters
      */
        for(i = WSLen;i < SoundExLen;i++ )
            WordStr[i] = '0';
      /* Size to taste
      */
    WordStr[SoundExLen] = 0;
      /* Replace first digit with
       * first letter.
      */
    WordStr[0] = FirstLetter;
      /* Copy WordStr to SoundEx
      */
    for(p2 = SoundEx,p = WordStr;(*p);p++,p2++)
        (*p2) = (*p);
    (*p2) = 0;
      return(SoundExLen);
  }
//********************************************************



