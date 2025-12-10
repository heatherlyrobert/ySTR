/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



/*====================------------------------------------====================*/
/*===----                     delimiter count                          ----===*/
/*====================------------------------------------====================*/
static void      o___COUNT___________________o (void) {;}

int           /*-> count delimiters in string */
ystrld_cnt              (char *b_source, char a_del, char a_dup, int a_max)
{  /*---(locals)-----------+------+----+-*/
   char           rce      =   -10;
   register char *s        = b_source;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        =     0;
   register char  l        =  '\0';          /* duplicate space skipper        */
   /*---(defense)------------------------*/
   --rce;  if (b_source == NULL)  return rce;
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

int    ystrldcnt   (char *b_source, char a_del, int a_max)  { return ystrld_cnt (b_source, a_del, 0, a_max); }
int    ystrlddcnt  (char *b_source, char a_del, int a_max)  { return ystrld_cnt (b_source, a_del, 1, a_max); }



/*====================------------------------------------====================*/
/*===----                    delimiter position                        ----===*/
/*====================------------------------------------====================*/
static void      o___POSITION________________o (void) {;}

int          /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
ystrld_pos              (char *b_source, char  a_del, int a_cnt, char a_dup, int a_max)
{  /*---(locals)-----------+-----------+-*/
   char           rce      =   -10;
   register char *s        = b_source;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        = 0;
   register char  l        = '\0';          /* duplicate skipper              */
   /*---(defense)------------------------*/
   --rce;  if (b_source == NULL)  return rce;
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

int    ystrldpos   (char *b_source, char a_del, int a_cnt, int a_max)  { return ystrld_pos (b_source, a_del, a_cnt, 0, a_max); }
int    ystrlddpos  (char *b_source, char a_del, int a_cnt, int a_max)  { return ystrld_pos (b_source, a_del, a_cnt, 1, a_max); }

int          /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
ystrlchr            (char *b_source, char  a_chr, int a_max)
{
   return ystrldpos (b_source, a_chr, 0, a_max);
}



/*====================------------------------------------====================*/
/*===----                    change and delete                         ----===*/
/*====================------------------------------------====================*/
static void      o___CHANGE__________________o (void) {;}

int          /*--> change all delimeter in string --------[ ------ [ ------ ]-*/
ystrldchg           (char *b_source, char  a_del, char  a_new, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char           rce      =   -10;
   register char *s        = b_source;
   register int   n        = a_max;
   register int   c        = 0;
   /*---(defense)------------------------*/
   --rce;  if (b_source == NULL)  return rce;
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
ystrlddel           (char *b_source, char  a_del, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char           rce      =   -10;
   register char *s        = b_source;
   register char  m        = a_del;
   register int   n        = a_max;
   register int   c        = 0;
   /*---(defense)------------------------*/
   --rce;  if (b_source == NULL)  return rce;
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
   return (short) c;
}



/*====================------------------------------------====================*/
/*===----                    character sets                            ----===*/
/*====================------------------------------------====================*/
static void      o___SETS____________________o (void) {;}

int
ystrld_chk              (char a_type, char *b_source, char *a_allowed, char a_compress, int a_max)
{
   /*---(design notes)-------------------*/
   /*
    *   a = alpha    lower and upper case letters only
    *   n = alnum    alpha plus numbers
    *   b = basic    alnum plus space, dash, and underscore
    *   w = write    basic plus normal punctuation
    *   p = print    all 7-bit printable ascii characters
    *   e = exten    write plus coding symbols
    *   7 = seven    all minus upper and lower controls
    *   h = heath    all but lower controls
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar      *x_legal     = NULL;
   int         x_len       =    0;
   int         x_save      =    0;
   int         i           =    0;
   int         c           =    0;
   uchar       m           =  '°';           /* this is the marker char        */
   char        x_set       =    0;
   /*---(defenses)-----------------------*/
   --rce;  if (b_source == NULL)       return rce;
   --rce;  if (b_source [0] == '\0')   return rce;
   /*---(setup legal characters)---------*/
   --rce;  if ((int) a_allowed > 0 && (int) a_allowed < 256) {
      x_set = (int) a_allowed;
      switch (x_set) {
      case ySTR_NUMERIC : x_legal = YSTR_NUMBER; break;
      case ySTR_ALPHA   : x_legal = YSTR_ALPHA;  break;
      case ySTR_ALNUM   : x_legal = YSTR_ALNUM;  break;
      case ySTR_VARS    : x_legal = YSTR_VARS;   break;
      case ySTR_FILES   : x_legal = YSTR_FILES;  break;
      case ySTR_BASIC   : x_legal = YSTR_BASIC;  break;
      case ySTR_WRITE   : x_legal = YSTR_WRITE;  break;
      case ySTR_EXTEN   : x_legal = YSTR_EXTEN;  break;
      case ySTR_SEVEN   : x_legal = YSTR_SEVEN;  break;
      case ySTR_PRINT   : x_legal = YSTR_PRINT;  break;
      case ySTR_HEATH   : x_legal = YSTR_HEATH;  break;
      default  : return rce;
      }
   } else x_legal = a_allowed;
   /*---(length)-------------------------*/
   x_len = x_save = strlen (b_source);
   if (x_len > a_max)   x_len = a_max;
   --rce;  if (a_type == 'g' && x_len != x_save)  return rce;
   /*---(clean)--------------------------*/
   for (i = 0; i < x_len; ++i) {
      if (x_legal [0] == '_' && i == 0) {
         if (strchr (x_legal + 1, b_source [i]) != 0)  continue;
      } else if (strchr (x_legal, b_source [i]) != 0)  continue;
      ++c;
      if (a_type == 'c')  b_source [i] = m;
   }
   if (a_type == 'c' && a_compress == 'y')   ystrlddel (b_source, m, x_save);
   /*---(complete)-----------------------*/
   --rce;  if (a_type == 'g' && c != 0)  return rce;
   return c;
}

char         /*--> check for character -------------------[--------[--------]-*/
ystrlgood           (char *b_source, char *a_allowed, int a_max)
{
   return ystrld_chk  ('g', b_source, a_allowed, '-', a_max);
}

int          /*--> find and count bad characters ---------[--------[--------]-*/
ystrlcheck          (char *b_source, char *a_allowed, int a_max)
{
   return ystrld_chk  ('k', b_source, a_allowed, '-', a_max);
}

int          /*--> find and mark bad characters ----------[--------[--------]-*/
ystrlmark           (char *b_source, char *a_allowed, int a_max)
{
   return ystrld_chk  ('c', b_source, a_allowed, '-', a_max);
}

int          /*--> find and remove bad characters --------[--------[--------]-*/
ystrlclean          (char *b_source, char *a_allowed, int a_max)
{
   return ystrld_chk  ('c', b_source, a_allowed, 'y', a_max);
}


