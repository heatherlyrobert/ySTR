/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



/*====================------------------------------------====================*/
/*===----                     delimiter count                          ----===*/
/*====================------------------------------------====================*/
static void      o___COUNT___________________o (void) {;}

short         /*-> count delimiters in string */
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

short  ystrldcnt   (char *b_src, char a_del, int a_max)  { return strld_cnt (b_src, a_del, 0, a_max); }
short  ystrlddcnt  (char *b_src, char a_del, int a_max)  { return strld_cnt (b_src, a_del, 1, a_max); }



/*====================------------------------------------====================*/
/*===----                    delimiter position                        ----===*/
/*====================------------------------------------====================*/
static void      o___POSITION________________o (void) {;}

short        /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
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

short  ystrldpos   (char *b_src, char a_del, int a_cnt, int a_max)  { return strld_pos (b_src, a_del, a_cnt, 0, a_max); }
short  ystrlddpos (char *b_src, char a_del, int a_cnt, int a_max)  { return strld_pos (b_src, a_del, a_cnt, 1, a_max); }

short        /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
ystrlchr            (char *b_src, char  a_chr, int a_max)
{
   return ystrldpos (b_src, a_chr, 0, a_max);
}



/*====================------------------------------------====================*/
/*===----                    change and delete                         ----===*/
/*====================------------------------------------====================*/
static void      o___CHANGE__________________o (void) {;}

short        /*--> change all delimeter in string --------[ ------ [ ------ ]-*/
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

short        /*--> remove all delimeter in string --------[ ------ [ ------ ]-*/
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

short        /*--> remove all delimeter in string --------[ ------ [ ------ ]-*/
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



/*====================------------------------------------====================*/
/*===----                    character sets                            ----===*/
/*====================------------------------------------====================*/
static void      o___SETS____________________o (void) {;}

short
ystr__check        (char a_type, uchar *a_src, char a_set, char a_compress, int a_max)
{
   /*---(design notes)-------------------*/
   /*
    *   a = alpha    lower and upper case letters only
    *   n = alnum    alpha plus numbers
    *   b = basic    alnum plus space, dash, and underscore
    *   w = write    basic plus normal punctuation
    *   e = exten    write plus coding symbols
    *   p = print    all 7-bit printable ascii characters
    *   7 = seven    all 7-bit, safe ascii characters
    *
    */
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   uchar      *x_numeric   = YSTR_NUMERIC;
   uchar      *x_alpha     = YSTR_ALPHA;
   uchar      *x_alnum     = YSTR_ALNUM;
   uchar      *x_files     = YSTR_FILES;
   uchar      *x_basic     = YSTR_BASIC;
   uchar      *x_write     = YSTR_WRITE;
   uchar      *x_exten     = YSTR_EXTEN;
   uchar       x_legal     [300]        = "";
   int         i, j;                     /* loop iterators -- characters        */
   int         x_len       = 0;            /* source string length                */
   int         x_save      = 0;            /* source string length                */
   int         c           = 0;
   /*> uchar       m           = '¬';           /+ this is the marker char        +/   <*/
   /*> uchar       m           = 26;            /+ this is the marker char        +/   <*/
   uchar       m           = '°';           /* this is the marker char        */
   /*---(defenses)-----------------------*/
   --rce;  if (a_src == NULL)     return rce;
   /*---(setup legal characters)---------*/
   --rce;  switch (a_set) {
   case ySTR_NUMERIC :
      strcpy (x_legal, x_numeric);
      break;
   case ySTR_ALPHA :
      strcpy (x_legal, x_alpha);
      break;
   case ySTR_ALNUM :
   case ySTR_VARS  :
      strcpy (x_legal, x_alnum);
      break;
   case ySTR_FILES :
      strcpy (x_legal, x_files);
      break;
   case ySTR_BASIC :
      strcpy (x_legal, x_basic);
      break;
   case ySTR_WRITE :
      strcpy (x_legal, x_write);
      break;
   case ySTR_EXTEN :
      strcpy (x_legal, x_exten);
      break;
   case ySTR_SEVEN :
      for (i = 1; i <= 127; ++i) {
         j = i - 1;
         x_legal [j    ] = i;
         x_legal [j + 1] = '\0';
      }
      break;
   case ySTR_PRINT :
      for (i = ' '; i <= '~'; ++i) {
         j = i - ' ';
         x_legal [j    ] = i;
         x_legal [j + 1] = '\0';
      }
      for (i = (uchar) '¡'; i <= (uchar) 'ÿ'; ++i) {
         j = i - (uchar) '¡' + ('~' - ' ' + 1);
         x_legal [j    ] = i;
         x_legal [j + 1] = '\0';
      }
      break;
   case ySTR_HEATHERLY :
      j = 0;
      for (i = ' '; i <= (uchar) 'ÿ'; ++i) {
         if (i == 127)  continue;
         x_legal [j  ] = i;
         x_legal [++j] = '\0';

      }
      break;
   default : return rce;
   }
   /*---(length)-------------------------*/
   x_len = x_save = strlen (a_src);
   if (x_len > a_max)   x_len = a_max;
   --rce;  if (a_type == 'g' && x_len != x_save)  return rce;
   /*---(clean)--------------------------*/
   for (i = 0; i < x_len; ++i) {
      if (a_set == ySTR_VARS && i == 0) {
         if (strchr (x_alpha, a_src [i]) != 0)  continue;
      } else if (strchr (x_legal, a_src [i]) != 0)  continue;
      ++c;
      if (a_type == 'c')  a_src [i] = m;
   }
   if (a_type == 'c' && a_compress == 'y')   ystrlddel (a_src, m, x_save);
   /*---(complete)-----------------------*/
   --rce;  if (a_type == 'g' && c != 0)  return rce;
   return c;
}

char         /*--> check for character -------------------[--------[--------]-*/
ystrlgood           (uchar *a_src, char a_set, int a_max)
{
   return ystr__check ('g', a_src, a_set, '-', a_max);
}

short        /*--> find and count bad characters ---------[--------[--------]-*/
ystrlcheck          (uchar *a_src, char a_set, int a_max)
{
   return ystr__check ('k', a_src, a_set, '-', a_max);
}

short        /*--> find and mark bad characters ----------[--------[--------]-*/
ystrlmark           (uchar *a_src, char a_set, int a_max)
{
   return ystr__check ('c', a_src, a_set, '-', a_max);
}

short        /*--> find and remove bad characters --------[--------[--------]-*/
ystrlclean          (uchar *a_src, char a_set, int a_max)
{
   return ystr__check ('c', a_src, a_set, 'y', a_max);
}


