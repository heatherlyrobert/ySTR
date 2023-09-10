/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



/*====================------------------------------------====================*/
/*===----                     delimiter count                          ----===*/
/*====================------------------------------------====================*/
static void      o___COUNT___________________o (void) {;}

int           /*-> count delimiters in string */
strld_cnt               (char *b_src, char a_del, char a_dup, int a_max)
{  /*---(locals)-----------+------+----+-*/
   char           rce      =   -10;
   register char *s        = b_src;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        =     0;
   register char  l        =  '\0';          /* duplicate space skipper        */
   /*---(defense)------------------------*/
   --rce;  if (b_src == NULL)  return rce;
   /*---(search)-------------------------*/
   while (*s != '\0') {
      if (n < 1)  break;
      if (*s == a_del) {
         if      (l != *s)            ++c;
         else if (a_dup)              ++c;
      }
      l = *s;
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   return c;
}

int  ystrldcnt   (char *b_src, char a_del, int a_max)  { return strld_cnt (b_src, a_del, 0, a_max); }
int  ystrlddcnt  (char *b_src, char a_del, int a_max)  { return strld_cnt (b_src, a_del, 1, a_max); }



/*====================------------------------------------====================*/
/*===----                    delimiter position                        ----===*/
/*====================------------------------------------====================*/
static void      o___POSITION________________o (void) {;}

int          /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
strld_pos               (char *b_src, char  a_del, int a_cnt, char a_dup, int a_max)
{  /*---(locals)-----------+-----------+-*/
   char           rce      =   -10;
   register char *s        = b_src;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        = 0;
   register char  l        = '\0';          /* duplicate skipper              */
   /*---(defense)------------------------*/
   --rce;  if (b_src == NULL)  return rce;
   /*---(search)-------------------------*/
   while (*s != '\0') {
      if (n < 1)  break;
      if (*s == a_del) {
         if      (l != *s)            ++c;
         else if (a_dup)              ++c;
         if (c == a_cnt + 1)  return a_max - n;
      }
      l = *s;
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   return --rce;
}

int  ystrldpos   (char *b_src, char a_del, int a_cnt, int a_max)  { return strld_pos (b_src, a_del, a_cnt, 0, a_max); }
int  strlddpos  (char *b_src, char a_del, int a_cnt, int a_max)  { return strld_pos (b_src, a_del, a_cnt, 1, a_max); }

int          /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
ystrlchr            (char *b_src, char  a_chr, int a_max)
{
   return ystrldpos (b_src, a_chr, 0, a_max);
}



/*====================------------------------------------====================*/
/*===----                    change and delete                         ----===*/
/*====================------------------------------------====================*/
static void      o___CHANGE__________________o (void) {;}

int          /*--> change all delimeter in string --------[ ------ [ ------ ]-*/
ystrldchg           (char *b_src, char  a_del, char  a_new, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char           rce      =   -10;
   register char *s        = b_src;
   register int   n        = a_max;
   register int   c        = 0;
   /*---(defense)------------------------*/
   --rce;  if (b_src == NULL)  return rce;
   /*---(change)-------------------------*/
   while (*s != '\0') {
      if (n  <  1)  break;
      if (*s == a_del) {
         ++c;
         *s = a_new;
      }
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   return c;
}

int          /*--> remove all delimeter in string --------[ ------ [ ------ ]-*/
strlddel_OLD       (char *b_src, char  a_del, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char           rce      =   -10;
   register char *s        = b_src;
   register char  m        = a_del;
   register int   n        = a_max;
   register int   c        = 0;
   /*---(defense)------------------------*/
   --rce;  if (b_src == NULL)  return rce;
   /*---(compress)-----------------------*/
   while (*(s + c) != '\0') {
      if (n  <  1)  break;
      n--;
      if (*(s + c) == m) {
         c++;
         continue;
      }
      *s = *(s + c);
      s++;
   }
   *s = '\0';
   /*---(complete)-----------------------*/
   return c;
}

int          /*--> remove all delimeter in string --------[ ------ [ ------ ]-*/
ystrlddel           (char *b_src, char  a_del, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char           rce      =   -10;
   register char *s        = b_src;
   register char  m        = a_del;
   register int   n        = a_max;
   register int   c        = 0;
   /*---(defense)------------------------*/
   --rce;  if (b_src == NULL)  return rce;
   /*---(compress)-----------------------*/
   while (*(s + c) != '\0') {
      n--;
      if (n >= 0 && *(s + c) == m) {
         c++;
         continue;
      }
      *s = *(s + c);
      s++;
   }
   *s = '\0';
   /*---(complete)-----------------------*/
   return c;
}


