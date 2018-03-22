/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



tLOCAL    its;



/*---(static variables)---------------*/
static char s_empty       [200] = "                                                                                                                                                                                                       ";
static char s_dashes      [200] = "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
static char s_equals      [200] = "=======================================================================================================================================================================================================";
static char s_unders      [200] = "_______________________________________________________________________________________________________________________________________________________________________________________________________";
static char s_dots        [200] = ".......................................................................................................................................................................................................";
static char s_pluses      [200] = "----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+";
static char s_back        [200] = "« « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « « «";
static char s_fore        [200] = "» » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » » »";
static char s_divs        [200] = "÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷ ÷";



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        ySTR_ver     [500];

char*      /* ---- : return library versioning information -------------------*/
ySTR_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strlcpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 15);
#else
   strlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (ySTR_ver, 100, "%s   %s : %s", t, YSTR_VER_NUM, YSTR_VER_TXT);
   return ySTR_ver;
}

char         /*--> set debugging mode --------------------[ ------ [ ------ ]-*/
ySTR_debug         (char a_flag)
{
   /*---(set debug flag)-----------------*/
   if   (a_flag == 'y')  its.debug   = 'y';
   else                  its.debug   = '-';
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___STRINGS_________________o (void) {;}

char         /*--> secure version of strcpy --------------[ leaf   [ ------ ]-*/
strlcpy            (char *a_dst, char *a_src, int a_max)
{
   /*---(design notes)-------------------*/
   /*
    * rc = 0 if success, -1 if truncate    (standard returns total length)
    * force a null on a zero length string (standard does not)
    *
    */
   /*---(locals)-----------+-----------+-*/
   register char *d        = a_dst;
   register char *s        = a_src;
   register int   n        = a_max;
   /*---(copy)---------------------------*/
   while (*s != '\0') {
      if (n <= 1)  break;
      *d++ = *s;
      n--;
      s++;
   }
   /*---(terminate)----------------------*/
   *d = '\0';
   /*---(check for tuncation)------------*/
   if (*s != '\0') return -1;
   /*---(complete)-----------------------*/
   return  0;
}

char             /* ---- : secure version of strcat --------------------------*/
strlcat            (char *a_dst, char *a_src, int a_max)
{
   /*---(design notes)-------------------*/
   /*
    * rc = 0 if success, -1 if truncate    (standard returns total length)
    * force a null on a zero length string (standard does not)
    * a truncate only registers on the source string
    *
    */
   /*---(locals)-------*-----------------*/
   register char *d    = a_dst;
   register char *s    = a_src;
   register int   n    = a_max;
   int            dlen = 0;
   /*---(find dst end)-------------------*/
   while (n-- >  0 && *d != '\0')  d++;
   dlen = d - a_dst;
   n    = a_max - dlen;
   /*---(copy)---------------------------*/
   while (*s != '\0') {
      if (n <= 1)  break;
      *d++ = *s;
      n--;
      s++;
   }
   /*---(terminate)----------------------*/
   *d = '\0';
   /*---(check for tuncation)------------*/
   if (*s != '\0') return -1;
   /*---(complete)-----------------------*/
   return  0;
}

char             /* ---- : secure version of truncate ------------------------*/
strltrunc          (char *a_src, int a_max)
{
   if (a_max > 0) *(a_src + a_max) = '\0';
   return 0;
}

int              /* ---- : secure version of strlen --------------------------*/
strllen            (char *a_src, int a_max)
{  /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        = 0;
   /*---(search)-------------------------*/
   while (*s != '\0') {
      if (n < 1)  break;
      c++;
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   if      (a_max == 0)  return  0;
   else if (n <= 0)      return -1;
   return c;
}

int              /* ---- : count contiguous spaces ---------------------------*/
strltrim           (char *a_src, char a_mode, int a_max)
{  /*---(design notes)-------------------*/
   /*
    *   n = none   (string untouched)
    *   h = head   (all leading spaces gone)
    *   t = tail   (all ending spaces gone)
    *   b = both   (head and tail)
    *   s = single (both plus internal not-in-strings compressed to one space)
    *   e = every  (both plus internal not-in-strings taken out)
    *   m = max    (both plus all internal taken fully out)
    *
    */
   /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        = 0;
   register char  l        = '-';
   char           m        = 31;            /* this is the marker char        */
   int            x_len    = 0;
   int            x_lim    = 0;
   char           x_str    = '-';
   /*---(get the length)-----------------*/
   x_len = strllen (a_src, a_max);
   if (x_len < 0)  {
      a_src [a_max] = '\0';
      x_len         = a_max;
   }
   /*---(mark leading)-------------------*/
   if (strchr (ySTR_ALL_HEADS, a_mode) != 0) {
      s    = a_src;
      n    = a_max;
      while (*s != '\0') {
         if (n < 1)                                  break;
         if (*s != ' ' && *s != '\t' && *s != '\v')  break;
         *s = m;
         n--;
         s++;
      }
   }
   /*---(wack trailing)------------------*/
   if (strchr (ySTR_ALL_TAILS, a_mode) != 0) {
      /*> printf ("checking tail\n");                                                 <*/
      s    = a_src + x_len - 1;
      n    = a_max;
      /*> printf ("a_src = %-10p, x_len = %-4d, s = %-10p, *s = %3d\n", a_src, x_len, s, *s);   <*/
      while (s >= a_src) {
         if (n < 1)                                  break;
         if (*s != ' ' && *s != '\t' && *s != '\v')  break;
         *s = '\0';
         --x_len;
         s--;
         n--;
      }
   }
   /*---(mark internal)------------------*/
   if (strchr (ySTR_ALL_INTER , a_mode) != 0) {
      s     = a_src;
      n     = x_len;
      x_lim = 0;
      l     = 'y';
      if (a_mode == ySTR_SINGLE) x_lim = 1;
      while (*s != '\0') {
         if (a_mode != ySTR_MAX && *s == '"') {
            if (x_str == 'y') x_str = '-';
            else              x_str = 'y';
         }
         if (n < 1) break;
         if (x_str == 'y') {
            n--;
            s++;
            continue;
         }
         if (*s != ' ' && *s != '\t' && *s != '\v') {
            if (x_lim != 0)  l = '-';
            n--;
            s++;
            continue;
         }
         if (l == 'y')  *s = m;
         l = 'y';
         n--;
         s++;
      }
   }
   /*---(compress)-----------------------*/
   c = strlddel (a_src, m, a_max);
   /*---(complete)-----------------------*/
   return x_len - c;
}

int              /* ---- : replace substrings --------------------------------*/
strlrepl           (char *a_src, char *a_old, char *a_new, int a_cnt, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   register char  *s           = a_src;         /* source pointer                 */
   register char    *t           = a_src;         /* source pointer                 */
   register char    *o           = a_old;         /* search pointer                 */
   int         n           = 0;
   int         lenf        = strlen (a_src);
   int         leno        = strlen (a_old);
   int         lenn        = strlen (a_new);
   int         lend        = lenn - leno;
   int         c           = 0;
   char        x_final     [LEN_HUGE] = "";
   /*---(defenses)-----------------------*/
   --rce;  if (a_src == NULL)           return  rce;
   --rce;  if (a_old == NULL)           return  rce;
   --rce;  if (a_new == NULL)           return  rce;
   --rce;  if (a_max >= LEN_HUGE)       return  rce;
   /*---(cycle)--------------------------*/
   --rce;
   while (1) {
      t = strstr (s, o);
      if (t == NULL)                    break;
      if (c >= a_cnt)                   break;
      if (lenf + lend >= LEN_HUGE)      break;
      if (t - a_src + lenn >= a_max)    break;
      ++c;
      n = t - s;
      strncat  (x_final, s, n);
      strcat   (x_final, a_new);
      s = t + leno;
   }
   strcat   (x_final, s);
   strlcpy  (a_src, x_final, a_max);
   /*---(complete)-----------------------*/
   return c;
}

int          /*--> clean string characters ---------------[--------[--------]-*/
strlclean          (char *a_src, char a_mode, char a_compress, int a_max)
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
   char       *x_alpha     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
   char       *x_alnum     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
   char       *x_basic     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789_-";
   char       *x_write     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789_.,:;!?-()\"\'&";
   char       *x_exten     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789_.,:;!?-()\"\'&<>{}[]+*/=#@\\^%`~^|$";
   char        x_legal     [200]   = "";
   int         i, j;                     /* loop iterators -- characters        */
   int         x_len       = 0;            /* source string length                */
   int         c           = 0;
   char           m        = 31;            /* this is the marker char        */
   /*---(defenses)-----------------------*/
   if (a_src == NULL)     return  -11;
   /*---(setup legal characters)---------*/
   switch (a_mode) {
   case ySTR_ALPHA :
      strcpy (x_legal, x_alpha);
      break;
   case ySTR_ALNUM :
      strcpy (x_legal, x_alnum);
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
   case ySTR_PRINT :
      for (i = ' '; i <= '~'; ++i) {
         j = i - ' ';
         x_legal [j    ] = i;
         x_legal [j + 1] = '\0';
      }
      break;
   case ySTR_SEVEN :
      for (i = 1; i <= 127; ++i) {
         j = i - 1;
         x_legal [j    ] = i;
         x_legal [j + 1] = '\0';
      }
      break;
   default : return -12;
   }
   /*---(clear)--------------------------*/
   x_len = strlen(a_src);
   if (x_len > a_max)  x_len = a_max;
   for (i = 0; i <= x_len; ++i) {
      if (strchr (x_legal, a_src [i]) != 0)  continue;
      ++c;
      if (a_compress == 'y')  a_src [i] = m;
      else                    a_src [i] = '_';
   }
   if (a_compress == 'y')   strlddel (a_src, m, a_max);
   /*---(complete)-----------------------*/
   return c;
}



/*====================------------------------------------====================*/
/*===----                           delimeter                          ----===*/
/*====================------------------------------------====================*/
static void      o___DELIMITER_______________o (void) {;}

int  
strldcnt           (char *a_src, char  a_del, int a_max)
{  /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        = 0;
   register char  l        = '\0';          /* duplicate space skipper        */
   /*---(search)-------------------------*/
   while (*s != '\0') {
      if (n < 1)  break;
      if (*s == a_del) {
         if      (a_del != ' ')  ++c;
         else if (l     != ' ')  ++c;
      }
      l = *s;
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   return c;
}

int          /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
strldpos           (char *a_src, char  a_del, int a_cnt, int a_max)
{  /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        = 0;
   register char  l        = '\0';          /* duplicate space skipper        */
   /*---(search)-------------------------*/
   while (*s != '\0') {
      if (n < 1)  break;
      if (*s == a_del && l != ' ') {
         ++c;
         if (c == a_cnt)  return a_max - n;
      }
      l = *s;
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   return -1;
}

int          /*--> change all delimeter in string --------[ ------ [ ------ ]-*/
strldchg           (char *a_src, char  a_del, char  a_new, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;
   register int   n        = a_max;
   register int   c        = 0;
   /*---(compress)-----------------------*/
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
strlddel           (char *a_src, char  a_del, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;
   register char  m        = a_del;
   register int   n        = a_max;
   register int   c        = 0;
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

char         /*--> encode special characters -------------[ ------ [ ------ ]-*/
strlencode         (char *a_src, char a_mode, int a_max)
{
   /*---(normal)-------------------------*/
   strldchg (a_src, G_KEY_ESCAPE, G_CHAR_ESCAPE, a_max);
   strldchg (a_src, G_KEY_TAB   , G_CHAR_TAB   , a_max);
   strldchg (a_src, G_KEY_BS    , G_CHAR_BS    , a_max);
   strldchg (a_src, G_KEY_DEL   , G_CHAR_DEL   , a_max);
   strldchg (a_src, G_KEY_GROUP , G_CHAR_GROUP , a_max);
   strldchg (a_src, G_KEY_FIELD , G_CHAR_FIELD , a_max);
   /*---(big)----------------------------*/
   if (a_mode == ySTR_MAX) {
      strldchg (a_src, G_KEY_RETURN, G_CHAR_RETURN, a_max);
      strldchg (a_src, G_KEY_SPACE , G_CHAR_SPACE , a_max);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> decode special characters -------------[ ------ [ ------ ]-*/
strldecode         (char *a_src, int a_max)
{
   /*---(normal)-------------------------*/
   strldchg (a_src, G_CHAR_RETURN , G_KEY_RETURN, a_max);
   strldchg (a_src, G_CHAR_ESCAPE , G_KEY_ESCAPE, a_max);
   strldchg (a_src, G_CHAR_GROUP  , G_KEY_GROUP , a_max);
   strldchg (a_src, G_CHAR_FIELD  , G_KEY_FIELD , a_max);
   strldchg (a_src, G_CHAR_TAB    , G_KEY_TAB   , a_max);
   strldchg (a_src, G_CHAR_BS     , G_KEY_BS    , a_max);
   strldchg (a_src, G_CHAR_DEL    , G_KEY_DEL   , a_max);
   strldchg (a_src, G_CHAR_SPACE  , G_KEY_SPACE , a_max);
   strldchg (a_src, G_CHAR_NULL   , G_KEY_NULL  , a_max);
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> reverse delayed characters ------------[ ------ [ ------ ]-*/
strlundelay        (char *a_src, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [5] = "";
   char        dslash      [5] = "\\\\";
   char        dquote      [5] = "\\\"";
   /*---(normal)-------------------------*/
   /*> printf ("a_src [%s]\n", a_src);                                                <*/
   sprintf (t, "%c", G_CHAR_DBSLASH);
   /*> printf ("    t [%s]\n", t);                                                    <*/
   /*> printf ("    c [%s]\n", dslash);                                               <*/
   strlrepl (a_src, t, dslash, 100, a_max);
   sprintf (t, "%c", G_CHAR_DDQUOTE);
   /*> printf ("    t [%s]\n", t);                                                    <*/
   /*> printf ("    c [%s]\n", dquote);                                               <*/
   strlrepl (a_src, t, dquote, 100, a_max);
   /*> printf ("    d [%s]\n", a_src);                                                <*/
   /*---(complete)-----------------------*/
   return 0;
}

uchar        /*--> convert backslashed characters --------[ ------ [ ------ ]-*/
chrslashed        (char a_ch)
{
   uchar       x_ch        = a_ch;
   /*---(primary)------------------------*/
   switch (x_ch) {
   case 'n'           : x_ch = G_CHAR_RETURN;    break;
   case G_KEY_RETURN  : x_ch = G_CHAR_RETURN;    break;
   case 'e'           : x_ch = G_CHAR_ESCAPE;    break;
   case G_KEY_ESCAPE  : x_ch = G_CHAR_ESCAPE;    break;
   case 't'           : x_ch = G_CHAR_TAB;       break;
   case G_KEY_TAB     : x_ch = G_CHAR_TAB;       break;
   case 'b'           : x_ch = G_CHAR_BS;        break;
   case G_KEY_BS      : x_ch = G_CHAR_BS;        break;
   case 'd'           : x_ch = G_CHAR_DEL;       break;
   case G_KEY_DEL     : x_ch = G_CHAR_DEL;       break;
   case 's'           : x_ch = G_CHAR_SPACE;     break;
   case G_KEY_SPACE   : x_ch = G_CHAR_SPACE;     break;
   }
   /*---(control)------------------------*/
   switch (x_ch) {
   case 'g'  :  x_ch = G_CHAR_GROUP;   break;  /* field delimiter       */
   case 'f'  :  x_ch = G_CHAR_FIELD;   break;  /* field delimiter       */
   case ','  :  x_ch = G_CHAR_WAIT;    break;  /* wait/pause            */
   case '.'  :  x_ch = G_CHAR_BREAK;   break;  /* break point           */
   case '!'  :  x_ch = G_CHAR_HALT;    break;  /* halt  <C-c>           */
   case '?'  :  x_ch = G_CHAR_DISPLAY; break;  /* force redisplay       */
   case 'a'  :  x_ch = G_CHAR_ALT;     break;  /* alt prefix            */
   case 'c'  :  x_ch = G_CHAR_CONTROL; break;  /* control prefix        */
   case '0'  :  x_ch = G_CHAR_NULL;    break;  /* null                  */
   case '+'  :  x_ch = G_CHAR_PLACE;   break;  /* place holder          */
   }
   /*---(symbols)------------------------*/
   switch (x_ch) {
   case '"'  :  x_ch = G_CHAR_DDQUOTE; break;  /* delayed quote         */
   case '\\' :  x_ch = G_CHAR_DBSLASH; break;  /* delayed backslash     */
   case '('  :  x_ch = G_CHAR_SLPAREN; break;  /* special left paren    */
   case ')'  :  x_ch = G_CHAR_SRPAREN; break;  /* special right paren   */
   case '['  :  x_ch = G_CHAR_SLBRACK; break;  /* special left bracket  */
   case ']'  :  x_ch = G_CHAR_SRBRACK; break;  /* special right bracket */
   case '<'  :  x_ch = G_CHAR_SLCHEV;  break;  /* special left chevron  */
   case '>'  :  x_ch = G_CHAR_SRCHEV;  break;  /* special right chevron */
   case '{'  :  x_ch = G_CHAR_SLBRACE; break;  /* special left brace    */
   case '}'  :  x_ch = G_CHAR_SRBRACE; break;  /* special right brace   */
   case '~'  :  x_ch = G_CHAR_APPROX;  break;
   case '='  :  x_ch = G_CHAR_NE;      break;
   case '#'  :  x_ch = G_CHAR_SMHASH;  break;
   case '1'  :  x_ch = G_CHAR_POW_1;   break;
   case '2'  :  x_ch = G_CHAR_POW_2;   break;
   case '3'  :  x_ch = G_CHAR_POW_3;   break;
   case 'x'  :  x_ch = G_CHAR_POW_X;   break;
   case 'y'  :  x_ch = G_CHAR_POW_Y;   break;
   case 'z'  :  x_ch = G_CHAR_POW_N;   break;
   case '*'  :  x_ch = G_CHAR_BIGDOT;  break;
   }
   /*---(greek)--------------------------*/
   switch (x_ch) {
   case 'A'  :  x_ch = G_CHAR_ALPHA;   break;
   case 'B'  :  x_ch = G_CHAR_BETA;    break;
   case 'G'  :  x_ch = G_CHAR_GAMMA;   break;
   case 'D'  :  x_ch = G_CHAR_DELTA;   break;
   case 'E'  :  x_ch = G_CHAR_EPSILON; break;
   case 'Z'  :  x_ch = G_CHAR_ZETA;    break;
   case 'H'  :  x_ch = G_CHAR_ETA;     break;
   case 'Y'  :  x_ch = G_CHAR_THETA;   break;
   case 'I'  :  x_ch = G_CHAR_IOTA;    break;
   case 'K'  :  x_ch = G_CHAR_KAPPA;   break;
   case 'L'  :  x_ch = G_CHAR_LAMBDA;  break;
   case 'M'  :  x_ch = G_CHAR_MU;      break;
   case 'N'  :  x_ch = G_CHAR_NU;      break;
   case 'X'  :  x_ch = G_CHAR_XI;      break;
   case 'O'  :  x_ch = G_CHAR_OMICRON; break;
   case 'P'  :  x_ch = G_CHAR_PI;      break;
   case 'R'  :  x_ch = G_CHAR_RHO;     break;
   case 'S'  :  x_ch = G_CHAR_SIGMA;   break;
   case 'T'  :  x_ch = G_CHAR_TAU;     break;
   case 'U'  :  x_ch = G_CHAR_UPSILON; break;
   case 'F'  :  x_ch = G_CHAR_PHI;     break;
   case 'C'  :  x_ch = G_CHAR_CHI;     break;
   case 'Q'  :  x_ch = G_CHAR_PSI;     break;
   case 'W'  :  x_ch = G_CHAR_OMEGA;   break;
   }
   /*---(complete)-----------------------*/
   return x_ch;
}

uchar        /*--> convert control in printable ----------[ ------ [ ------ ]-*/
chrvisible        (uchar a_ch)
{
   /*---(translate)----------------------*/
   switch (a_ch) {
   case G_KEY_RETURN  : a_ch = G_CHAR_RETURN;    break;
   case G_KEY_ENTER   : a_ch = G_CHAR_RETURN;    break;
   case G_KEY_ESCAPE  : a_ch = G_CHAR_ESCAPE;    break;
   case G_KEY_TAB     : a_ch = G_CHAR_TAB;       break;
   case G_KEY_BS      : a_ch = G_CHAR_BS;        break;
   case G_KEY_DEL     : a_ch = G_CHAR_DEL;       break;
   case G_KEY_SPACE   : a_ch = G_CHAR_SPACE;     break;
   case G_KEY_GROUP   : a_ch = G_CHAR_GROUP;     break;
   case G_KEY_FIELD   : a_ch = G_CHAR_FIELD;     break;
   case G_KEY_NULL    : a_ch = G_CHAR_NULL;      break;
   }
   if (a_ch < 32)  a_ch = G_CHAR_BIGDOT;
   /*---(complete)-----------------------*/
   return a_ch;
}

uchar        /*--> convert printable into control --------[ ------ [ ------ ]-*/
chrworking        (uchar a_ch)
{
   /*---(translate)----------------------*/
   switch (a_ch) {
   case G_CHAR_RETURN  : a_ch = G_KEY_RETURN;     break;
   case G_CHAR_ESCAPE  : a_ch = G_KEY_ESCAPE;     break;
   case G_CHAR_TAB     : a_ch = G_KEY_TAB;        break;
   case G_CHAR_BS      : a_ch = G_KEY_BS;         break;
   case G_CHAR_DEL     : a_ch = G_KEY_DEL;        break;
   case G_CHAR_SPACE   : a_ch = G_KEY_SPACE;      break;
   case G_CHAR_GROUP   : a_ch = G_KEY_GROUP;      break;
   case G_CHAR_FIELD   : a_ch = G_KEY_FIELD;      break;
   case G_CHAR_NULL    : a_ch = G_KEY_NULL;       break;
   case G_CHAR_DBSLASH : a_ch = G_KEY_BSLASH;     break;
   case G_CHAR_DDQUOTE : a_ch = G_KEY_DQUOTE;     break;
   }
   /*---(complete)-----------------------*/
   return a_ch;
}



/*====================------------------------------------====================*/
/*===----                           arguments                          ----===*/
/*====================------------------------------------====================*/
static void      o___ARGS____________________o (void) {;}

char       /*>---: PURPOSE : break string into an argv[] structure -----------*/
strlargs           (char *a_src, int a_max, int a_cnt, int *a_argc, char *a_argv[])
{
   /*---(defenses)-----------------------*/
   if (a_src == NULL) return -1;
   /*---(locals)-------------------------*/
   register char *s        = a_src;         /* source pointer                 */
   register int   n        = a_max;         /* maximum source length          */
   register int   c        = 0;             /* argument count                 */
   char           x_str    = '-';
   char           x_stop   = '-';
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_enter   (__FUNCTION__);
   DEBUG_STRG   yLOG_point   ("a_src"     , a_src);
   DEBUG_STRG   yLOG_value   ("a_max"     , a_max);
   DEBUG_STRG   yLOG_value   ("a_cnt"     , a_cnt);
   DEBUG_STRG   yLOG_point   ("a_argc"    , a_argc);
   DEBUG_STRG   yLOG_point   ("a_argv"    , a_argv);
   /*---(trucate to protect)-------------*/
   /*> strltrunc (a_src, a_max);                                                      <*/
   /*---(process string)-----------------*/
   while (*s != '\0') {
      DEBUG_STRG   yLOG_complex ("registers" , "*s=%c/%03d, n=%3d, c=%3d", *s, *s, n, c);
      /*---(end conditions)--------------*/
      if (n <= 1     )  break;
      if (c >  a_cnt )  break;
      /*---(handle character)------------*/
      if (*s != ' ' && *s != '\t' && *s != '\v') {
         DEBUG_STRG   yLOG_note    ("handle as character");
         if (x_str == '-') {
            x_str = 'y';
            if (x_stop == 'y') {
               s++;
               break;
            }
            if (c <  a_cnt) {
               a_argv [c] = s;
               c++;
            }
            if (c >= a_cnt)  x_stop = 'y';
         }
      }
      /*---(handle whitespace)-----------*/
      else {
         DEBUG_STRG   yLOG_note    ("handle as whitespace");
         x_str = '-';
         *s = '\0';
      }
      /*---(next character)--------------*/
      n--;
      s++;
   }
   /*---(update)-------------------------*/
   *a_argc = c;
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_exit    (__FUNCTION__);
   if (*s != '\0') {
      *s = '\0';
      if (c     >= a_cnt)  return -2;
      if (n     >= 0    )  return -3;
      if (a_max <= 0    )  return -4;
      if (a_cnt <= 0    )  return -5;
      return  -6;
   }
   if (n  <=  0  )  return -1;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     conversion to numeric                    ----===*/
/*====================------------------------------------====================*/
static void      o___CONVERSION______________o (void) {;}

char         /*-> interpret binary numbers ----------------[ petal  [ 2f---- ]*/
strl2bin           (char *a_src, double *a_val, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   char        x_ch        =  '-';               /* current character         */
   int         x_min       =   -1;               /* first translatable char   */
   int         x_base      =    2;               /* base position             */
   int         x_digit     =    0;               /* digit value               */
   int         x_place     =    1;               /* base position             */
   long        x_final     =    0;               /* final value               */
   int         i           =    0;               /* iterator -- character     */
   char        x_valid     [20] = "01";          /* only binary digits        */
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_STRG   yLOG_snote   ("null input");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce; if (x_len <= 2) {
      DEBUG_STRG   yLOG_snote   ("too short");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_schar   (x_ch);
   x_ch = tolower (a_src [0]);
   if (x_ch == 'b') {
      DEBUG_STRG   yLOG_snote   ("pre=b");
      x_min  =  1;
   } else if (strncmp ("0b", a_src, 2) == 0) {
      DEBUG_STRG   yLOG_snote   ("pre=0b");
      x_min  =  2;
   } else if (strncmp ("0B", a_src, 2) == 0) {
      DEBUG_STRG   yLOG_snote   ("pre=0b");
      x_min  =  2;
   }
   --rce; if (x_min <= 0) {
      DEBUG_STRG   yLOG_snote   ("wrong prefix");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_ch = tolower (a_src [x_min]);
   --rce; if (x_ch == '\0') {
      DEBUG_STRG   yLOG_snote   ("only prefix");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(run digits)---------------------*/
   DEBUG_STRG   yLOG_sint    (x_base);
   DEBUG_STRG   yLOG_snote   (x_valid);
   --rce;  for (i = x_len - 1; i >= x_min; --i) {
      x_ch = a_src [i];
      DEBUG_STRG   yLOG_schar   (x_ch);
      if (strchr (x_valid, x_ch)  == 0) {
         DEBUG_STRG   yLOG_snote   ("BOOM");
         DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      x_digit  = x_ch - '0';
      x_final += x_digit * x_place;
      DEBUG_STRG   yLOG_sint    (x_final);
      x_place *= x_base;
   }
   /*---(return value)-------------------*/
   DEBUG_STRG   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> interpret octal numbers -----------------[ petal  [ 2e---- ]*/
strl2oct           (char *a_src, double *a_val, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   char        x_ch        =  '-';               /* current character         */
   int         x_min       =   -1;               /* first translatable char   */
   int         x_base      =    8;               /* base position             */
   char        x_curr      =  '-';               /* current character         */
   int         x_digit     =    0;               /* digit value               */
   int         x_place     =    1;               /* base position             */
   long        x_final     =    0;               /* final value               */
   int         i           =    0;               /* iterator -- character     */
   char        x_valid     [20] = "01234567";    /* only octal digits           */
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_STRG   yLOG_snote   ("null input");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce; if (x_len <= 1) {
      DEBUG_STRG   yLOG_snote   ("too short");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_schar   (x_ch);
   x_ch = tolower (a_src [0]);
   if (x_ch == 'o') {
      DEBUG_STRG   yLOG_snote   ("pre=o");
      x_min  =  1;
   } else if (strncmp ("0o", a_src, 2) == 0) {
      DEBUG_STRG   yLOG_snote   ("pre=0o");
      x_min  =  2;
   } else if (x_ch == '0') {
      DEBUG_STRG   yLOG_snote   ("pre=0");
      x_min  =  1;
   }
   --rce; if (x_min <= 0) {
      DEBUG_STRG   yLOG_snote   ("wrong prefix");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_ch = tolower (a_src [x_min]);
   --rce; if (x_ch == '\0') {
      DEBUG_STRG   yLOG_snote   ("only prefix");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(run digits)---------------------*/
   DEBUG_STRG   yLOG_sint    (x_base);
   DEBUG_STRG   yLOG_snote   (x_valid);
   --rce;  for (i = x_len - 1; i >= x_min; --i) {
      x_ch = a_src [i];
      DEBUG_STRG   yLOG_schar   (x_ch);
      if (strchr (x_valid , x_ch)  == 0) {
         DEBUG_STRG   yLOG_snote   ("BOOM");
         DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      x_digit  = x_ch - '0';
      x_final += x_digit * x_place;
      DEBUG_STRG   yLOG_sint    (x_final);
      x_place *= x_base;
   }
   /*---(return value)-------------------*/
   DEBUG_STRG   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> interpret hexadecimal numbers -----------[ petal  [ 2f---- ]*/
strl2hex           (char *a_src, double *a_val, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   char        x_ch        =  '-';               /* current character         */
   int         x_min       =   -1;               /* first translatable char   */
   int         x_base      =   16;               /* base position             */
   int         x_digit     =    0;               /* digit value               */
   int         x_place     =    1;               /* base position             */
   long        x_final     =    0;               /* final value               */
   int         i           =    0;               /* iterator -- character     */
   char        x_valid     [20] = "0123456789abcdef"; /* only hex digits           */
   char        x_del       =  '-';
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_STRG   yLOG_snote   ("null input");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce; if (x_len <  2) {
      DEBUG_STRG   yLOG_snote   ("too short");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_schar   (x_ch);
   x_ch = tolower (a_src [0]);
   if (x_ch == 'x') {
      DEBUG_STRG   yLOG_snote   ("pre=x");
      x_min  =  1;
   } else if (strncmp ("0x", a_src, 2) == 0) {
      DEBUG_STRG   yLOG_snote   ("pre=0x");
      x_min  =  2;
   } else if (strncmp ("0X", a_src, 2) == 0) {
      DEBUG_STRG   yLOG_snote   ("pre=0x");
      x_min  =  2;
   }
   --rce; if (x_min <= 0) {
      DEBUG_STRG   yLOG_snote   ("wrong prefix");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_ch = tolower (a_src [x_min]);
   --rce; if (x_ch == '\0') {
      DEBUG_STRG   yLOG_snote   ("only prefix");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(run digits)---------------------*/
   DEBUG_STRG   yLOG_sint    (x_base);
   DEBUG_STRG   yLOG_snote   (x_valid);
   --rce;  for (i = x_len - 1; i >= x_min; --i) {
      x_ch = tolower (a_src [i]);
      DEBUG_STRG   yLOG_schar   (x_ch);
      if (x_ch == '\'' && x_del != 'y') {
         x_del = 'y';
         continue;
      }
      x_del = '-';
      if (strchr (x_valid   , x_ch    )  == 0) {
         DEBUG_STRG   yLOG_snote   ("BOOM");
         DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (x_ch >= '0' && x_ch <= '9')   x_digit  = x_ch - '0';
      else                              x_digit  = x_ch - 'a' + 10;
      x_final += x_digit * x_place;
      DEBUG_STRG   yLOG_sint    (x_final);
      x_place *= x_base;
   }
   /*---(return value)-------------------*/
   DEBUG_STRG   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> interpret float/int numbers -------------[ petal  [ 2g---- ]*/
strl2real          (char *a_src, double *a_val, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   char        x_temp      [LEN_HUGE ] = "";      /* temp version              */
   int         i           =    0;               /* iterator -- character     */
   char        x_curr      =  '-';               /* current character         */
   int         x_exp       =   -1;
   int         x_dec       =   -1;
   double      x_final     =    0;               /* final value               */
   double      x_power     =    1;               /* exponent                  */
   char        x_valid     [20] = "0123456789.-+";    /* only digits               */
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_STRG   yLOG_snote   ("null input");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce; if (a_src [0] == '0' && (a_src [1] != '\0' && a_src [1] != '.')) {
      DEBUG_STRG   yLOG_snote   ("bad leading zero");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (x_temp, a_src, LEN_HUGE);
   DEBUG_STRG   yLOG_snote   (x_temp);
   /*---(run digits)---------------------*/
   DEBUG_STRG   yLOG_snote   (x_valid);
   --rce;  for (i = x_len - 1; i >= 0 ; --i) {
      x_curr = x_temp [i];
      DEBUG_STRG   yLOG_schar   (x_curr);
      /*---(find exponent)---------------*/
      if (x_curr == 'e' || x_curr == 'E') {
         DEBUG_STRG   yLOG_snote   ("exp");
         if (x_exp < 0)   x_exp = i;
         else {
            DEBUG_STRG   yLOG_snote   ("BOOM");
            DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
         continue;
      }
      /*---(find decimal)----------------*/
      if (x_curr == '.') {
         DEBUG_STRG   yLOG_snote   ("dec");
         if (x_dec < 0)   x_dec = i;
         else {
            DEBUG_STRG   yLOG_snote   ("BOOM");
            DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
            return rce - 1;
         }
         continue;
      }
      /*---(check rest)------------------*/
      if (strchr (x_valid, x_curr)  == 0) {
         DEBUG_STRG   yLOG_snote   ("BOOM");
         DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
         return rce - 2;
      }
   }
   rce -= 2;
   /*---(check positions)----------------*/
   --rce;  if (x_exp > 0 && x_dec > 0 && x_exp < x_dec) {
      DEBUG_STRG   yLOG_snote   ("BOOM");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(parse value)--------------------*/
   if (x_exp > 0)  x_temp [x_exp] = '\0';
   x_final = atof (x_temp);
   if (x_exp > 0) {
      if (x_temp [x_exp + 1] != '\0')  {
         x_power = atof (x_temp + x_exp + 1);
         if (x_power != 0.0)  x_power = pow (10, x_power);
      } else {
         x_power = 0.0;
      }
   }
   if      (x_power >  0)  x_final = x_final * x_power;
   else if (x_power <  0)  x_final = x_final / (-x_power);
   else                    x_final = 0.0;
   /*---(return value)-------------------*/
   DEBUG_STRG   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = x_final;
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     strings from numerics                    ----===*/
/*====================------------------------------------====================*/
static void      o___FORMATTING______________o (void) {;}

ySTR__space_ints     (char *a_out, int a_count, char a_char)
{
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   int         j           =    0;               /* iterator -- character     */
   x_len = strlen (a_out);
   for (i = (x_len - 1) / a_count; i > 0; --i) {
      for (j = x_len; j >= x_len - (i * a_count); --j) {
         a_out [j + 1] = a_out [j];
      }
      a_out [x_len - (i * a_count)] = a_char;
      ++x_len;
      a_out [x_len] = '\0';
   }
   return 0;
}

ySTR__space_decs     (char *a_out, int a_cnt, char a_char)
{
   int         x_add       =    0;
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   /*---(defense)------------------------*/
   x_len = strlen (a_out);
   if (x_len <= a_cnt)    return 0;
   /*---(add padding)--------------------*/
   x_add = x_len % a_cnt;
   if (x_add > 0)  x_add = a_cnt - x_add;
   /*> printf ("a_out = %s, a_cnt = %d, x_len = %d, x_add %d\n", a_out, a_cnt, x_len, x_add);   <*/
   for (i = 0; i < x_add; ++i)   strcat (a_out, "0");
   /*> printf ("a_out = %s\n", a_out);                                                <*/
   ySTR__space_ints     (a_out, a_cnt, a_char);
   /*> printf ("a_out = %s\n", a_out);                                                <*/
   x_len = strlen (a_out);
   for (i = 0; i < x_add; ++i)  a_out [--x_len] = '\0';
   /*> printf ("a_out = %s\n", a_out);                                                <*/
   return 0;
}

char         /*-> format binary numbers to string ---------[ petal  [ 2f---- ]*/
strl4bin           (double a_val, char *a_out, int a_nibs, char a_fmt, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   long        x_num       =    0;
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_final     [200] = "";
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   DEBUG_STRG   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("bBnq:s", a_fmt) == NULL) {
      strlcpy (a_out, "#.fmt", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#.neg", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(any binary)-----------*/
   x_num = (long) a_val;
   if (x_num == 0)   strcat (x_temp, "0000");
   while (x_num > 0) {
      if (x_num % 2 == 0)   strcat (x_temp, "0");
      else                  strcat (x_temp, "1");
      x_num /= 2;
   }
   /*---(make prefix)----------*/
   x_len = strlen (x_temp);
   switch (x_len % 4) {
   case 1 : strcat (x_temp, "0");
   case 2 : strcat (x_temp, "0");
   case 3 : strcat (x_temp, "0");
   }
   for (i = x_len / 4; i < a_nibs; ++i)  strcat (x_temp, "0000");
   if (strchr ("bB", a_fmt) != NULL)     strcat (x_temp, "b");
   /*---(flip)-----------------*/
   x_len = strlen (x_temp) - 1;
   for (i = x_len; i >= 0; --i) x_final [x_len - i] = x_temp[i];
   /*---(delimit)--------------*/
   switch (a_fmt) {
   case 'B' :  case 'q' :  ySTR__space_ints (x_final, 4, '\'');   break;
   case ':' :              ySTR__space_ints (x_final, 4, ':');    break;
   case 's' :              ySTR__space_ints (x_final, 4, ' ');    break;
   case 'b' :  case 'n' :  break;
   }
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#.max", a_max);
      DEBUG_STRG   yLOG_snote   ("too long");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format octal numbers to string ----------[ petal  [ 2f---- ]*/
strl4oct           (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_prefix    [200] = "";  /* temp working string            */
   char        x_final     [200] = "";
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   DEBUG_STRG   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("oOzZnq:s", a_fmt) == NULL) {
      strlcpy (a_out, "#.fmt", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#.neg", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate base)-------*/
   sprintf  (x_temp, "%o",       (long)  a_val);
   /*---(make prefix)----------*/
   if (strchr ("oO", a_fmt) != NULL)  strcpy  (x_prefix, "o");
   if (strchr ("zZ", a_fmt) != NULL)  strcpy  (x_prefix, "0");
   x_len = strlen (x_temp);
   if (x_len % 3 == 1) { strcat  (x_prefix, "00"); x_len += 2; }
   if (x_len % 3 == 2) { strcat  (x_prefix,  "0"); x_len += 1; }
   for (i = x_len / 3; i < a_cnt; ++i)  strcat (x_prefix, "000");
   /*---(merge)----------------*/
   sprintf (x_final, "%s%s"  , x_prefix, x_temp);
   /*---(delimit)--------------*/
   switch (a_fmt) {
   case 'O' :
   case 'Z' :  case 'q' :  ySTR__space_ints (x_final, 3, '\'');   break;
   case ':' :              ySTR__space_ints (x_final, 3, ':');    break;
   case 's' :              ySTR__space_ints (x_final, 3, ' ');    break;
   case 'o' :  case 'n' :  break;
   }
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#.max", a_max);
      DEBUG_STRG   yLOG_snote   ("too long");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
strl4hex           (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_prefix    [200] = "";  /* temp working string            */
   char        x_final     [200] = "";
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   DEBUG_STRG   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("xXUDqQnN:sS", a_fmt) == NULL) {
      strlcpy (a_out, "#.fmt", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#.neg", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate base)-------*/
   if (strchr ("xXqns" , a_fmt) != 0)   sprintf  (x_temp, "%x", (long) a_val);
   else                                 sprintf  (x_temp, "%X", (long) a_val);
   /*---(make prefix)----------*/
   x_len = strlen (x_temp);
   if (x_len % 2 == 1) {
      strcpy  (x_prefix, "0");
      ++x_len;
   }
   for (i = x_len / 2; i < a_cnt; ++i)  strcat (x_prefix, "00");
   if (strchr ("xXUD"  , a_fmt) != 0)   sprintf (x_final, "x%s%s", x_prefix, x_temp);
   else                                 sprintf (x_final, "%s%s" , x_prefix, x_temp);
   /*---(delimit)--------------*/
   if (strchr ("XDqQ"  , a_fmt) != 0)   ySTR__space_ints (x_final, 2, '\'');
   if (strchr ("sS"    , a_fmt) != 0)   ySTR__space_ints (x_final, 2, ' ');
   if (strchr (":"     , a_fmt) != 0)   ySTR__space_ints (x_final, 2, ':');
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#.max", a_max);
      DEBUG_STRG   yLOG_snote   ("too long");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
strl4comma         (double a_val, char *a_out, int a_decs, char a_fmt, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_prefix    [200] = "";  /* temp working string            */
   char        x_suffix    [200] = "";  /* temp working string            */
   char        x_final     [200] = "";
   char        x_sign      =    1;
   double      x_round     = 0;             /* rounded off value              */
   long      x_exp       = 1;             /* exponent to round off          */
   long      x_int       = 0;             /* whole part                     */
   long      x_frac      = 0;             /* fractional part                */
   long      x_pct       = 1;             /* fractional part                */
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   DEBUG_STRG   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("ifcCaAsS$#pP?", a_fmt) == NULL) {
      strlcpy (a_out, "#.fmt", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (a_val < 0.0)    x_sign  = -1;
   if (a_fmt == '?')   a_fmt   = 'i';
   if (a_fmt == 'i')   a_decs  =  0;
   /*---(parse out)----------------------*/
   for (i = 0; i < a_decs; ++i)  x_exp *= 10;
   x_round  = round (a_val * x_sign * x_exp * x_pct);
   x_int    = x_round / x_exp;
   x_frac   = x_round - (x_int * x_exp);
   /*---(assemble prefix)----------------*/
   if (tolower (a_fmt) == '$')  strcat (x_final, "$");
   if (x_sign < 0) {
      if (strchr ("ifcsp", tolower (a_fmt)) != NULL)  strcat (x_final, "-");
      if (strchr ("a$"   , tolower (a_fmt)) != NULL)  strcat (x_final, "(");
   } else {
      if (strchr ("s"    , tolower (a_fmt)) != NULL)  strcat (x_final, "+");
   }
   DEBUG_STRG  yLOG_snote    (x_final);
   /*---(format integer part)------------*/
   sprintf (x_temp, "%lld", x_int);
   x_len = strlen (x_temp);
   if (strchr ("if", a_fmt) == NULL)  ySTR__space_ints (x_temp, 3, ',');
   strcat (x_final, x_temp);
   DEBUG_STRG  yLOG_snote    (x_temp);
   /*---(decimal part)-------------------*/
   if (a_fmt != 'i' && a_decs > 0) {
      sprintf (x_temp, "%0*lld", a_decs, x_frac);
      if (strchr ("ACS#", a_fmt) != NULL)  ySTR__space_decs (x_temp, 3, '\'');
      strcat  (x_final, ".");
      strcat  (x_final, x_temp);
   }
   DEBUG_STRG  yLOG_snote    (x_temp);
   /*---(assemble suffix)----------------*/
   if (x_sign < 0) {
      switch (tolower (a_fmt)) {
      case 'a' : case '$' : case 'p' : strcat (x_final, ")");  break;
      case '#' :                       strcat (x_final, " -"); break;
      case 'P' :                       strcat (x_final, ".");  break;
      }
   } else {
      switch (tolower (a_fmt)) {
      case 'a' : case '$' :            strcat (x_final, "_");  break;
      case 'p' :                       strcat (x_final, ")");  break;
      case 'P' :                       strcat (x_final, ".");  break;
      case '#' :                       strcat (x_final, " +"); break;
      }
   }
   DEBUG_STRG  yLOG_snote    (x_final);
   /*---(create)---------------*/
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#.max", a_max);
      DEBUG_STRG   yLOG_snote   ("too long");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
strl4sci           (double a_val, char *a_out, int a_decs, char a_fmt, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_prefix    [200] = "";  /* temp working string            */
   char        x_suffix    [200] = "";  /* temp working string            */
   char        x_final     [200] = "";
   char        x_sign      =    1;
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   if (a_val < 0.0)  x_sign  = -1;
   DEBUG_STRG   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("eE", a_fmt) == NULL) {
      strlcpy (a_out, "#.fmt", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (a_val < 0.0)    x_sign  = -1;
   if (a_decs == 0)  a_decs  =  1;
   /*---(scienfific)-----------*/
   if (tolower (a_fmt) == 'e') {
      strcpy  (x_final, "");
      /*---(make prefix)-----------------*/
      if (x_sign < 0)          strcpy (x_final, "-");
      else if (a_fmt == 'E')  strcpy (x_final, "+");
      sprintf (x_temp, "%.*e", a_decs, a_val * x_sign);
      strncat (x_final, x_temp, 2);
      /*---(save exponent/suffix)--------*/
      strcpy  (x_suffix, x_temp + a_decs + 2);
      x_temp  [a_decs + 2] = '\0';
      /*---(parse decimals)--------------*/
      strcpy  (x_prefix, x_temp + 2);
      if (a_fmt == 'E' && a_decs > 3)  ySTR__space_decs (x_prefix, 3, '\'');
      /*---(contat)----------------------*/
      strcat  (x_final, x_prefix);
      if (a_fmt == 'E')  strcat  (x_final, " ");
      strcat  (x_final, x_suffix);
   }
   /*---(create)---------------*/
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#.max", a_max);
      DEBUG_STRG   yLOG_snote   ("too long");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
strl4roman         (double a_val, char *a_out, int a_decs, char a_fmt, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         x_int       =    0;
   char        x_final     [200] = "";
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   DEBUG_STRG   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("rR", a_fmt) == NULL) {
      strlcpy (a_out, "#.fmt", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#.neg", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_val > 4000) {
      strlcpy (a_out, "#.big", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_int = (int) a_val;
   if (x_int == 0) {
      if (a_fmt == 'r')  strcpy (a_out, "o");
      else                strcpy (a_out, "O");
      return 0;
   }
   /*---(parse)--------------------------*/
   if (x_int / 3000 == 1)    {  strcat (x_final, "MMM"   );  x_int -= 3000; }
   if (x_int / 2000 == 1)    {  strcat (x_final, "MM"    );  x_int -= 2000; }
   if (x_int / 1000 == 1)    {  strcat (x_final, "M"     );  x_int -= 1000; }
   if (x_int / 900  == 1)    {  strcat (x_final, "CM"    );  x_int -=  900; }
   if (x_int / 800  == 1)    {  strcat (x_final, "DCCC"  );  x_int -=  800; }
   if (x_int / 700  == 1)    {  strcat (x_final, "DCC"   );  x_int -=  700; }
   if (x_int / 600  == 1)    {  strcat (x_final, "DC"    );  x_int -=  600; }
   if (x_int / 500  == 1)    {  strcat (x_final, "D"     );  x_int -=  500; }
   if (x_int / 400  == 1)    {  strcat (x_final, "CD"    );  x_int -=  400; }
   if (x_int / 300  == 1)    {  strcat (x_final, "CCC"   );  x_int -=  300; }
   if (x_int / 200  == 1)    {  strcat (x_final, "CC"    );  x_int -=  200; }
   if (x_int / 100  == 1)    {  strcat (x_final, "C"     );  x_int -=  100; }
   if (x_int / 100  == 1)    {  strcat (x_final, "C"     );  x_int -=  100; }
   if (x_int / 90   == 1)    {  strcat (x_final, "XC"    );  x_int -=   90; }
   if (x_int / 80   == 1)    {  strcat (x_final, "LXXX"  );  x_int -=   80; }
   if (x_int / 70   == 1)    {  strcat (x_final, "LXX"   );  x_int -=   70; }
   if (x_int / 60   == 1)    {  strcat (x_final, "LX"    );  x_int -=   60; }
   if (x_int / 50   == 1)    {  strcat (x_final, "L"     );  x_int -=   50; }
   if (x_int / 40   == 1)    {  strcat (x_final, "XL"    );  x_int -=   40; }
   if (x_int / 30   == 1)    {  strcat (x_final, "XXX"   );  x_int -=   30; }
   if (x_int / 20   == 1)    {  strcat (x_final, "XX"    );  x_int -=   20; }
   if (x_int / 10   == 1)    {  strcat (x_final, "X"     );  x_int -=   10; }
   if (x_int / 9    == 1)    {  strcat (x_final, "IX"    );  x_int -=    9; }
   if (x_int / 8    == 1)    {  strcat (x_final, "VIII"  );  x_int -=    8; }
   if (x_int / 7    == 1)    {  strcat (x_final, "VII"   );  x_int -=    7; }
   if (x_int / 6    == 1)    {  strcat (x_final, "VI"    );  x_int -=    6; }
   if (x_int / 5    == 1)    {  strcat (x_final, "V"     );  x_int -=    5; }
   if (x_int / 4    == 1)    {  strcat (x_final, "IV"    );  x_int -=    4; }
   if (x_int / 3    == 1)    {  strcat (x_final, "III"   );  x_int -=    3; }
   if (x_int / 2    == 1)    {  strcat (x_final, "II"    );  x_int -=    2; }
   if (x_int / 1    == 1)    {  strcat (x_final, "I"     );  x_int -=    1; }
   /*---(create)---------------*/
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#.max", a_max);
      DEBUG_STRG   yLOG_snote   ("too long");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (a_fmt == 'r') {
      for (i = 0; i < x_len; ++i)  x_final [i] = tolower (x_final [i]);
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
strl4mongo         (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_final     [200] = "";
   char        x_chars     [200] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   long        x_int       =    0;
   int         x_digit     =    0;
   int         x_place     =    0;
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   DEBUG_STRG   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("zZnqs:", a_fmt) == NULL) {
      strlcpy (a_out, "#.fmt", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#.neg", a_max);
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_int  = a_val;
   /*---(translate base)-------*/
   if (x_int == 0)  strcat (x_temp, "0000");
   while (x_int > 0) {
      x_digit = x_int % 62;
      x_temp [x_place++] = x_chars [x_digit];
      x_temp [x_place  ] = '\0';
      x_int /= 62;
   }
   /*---(make prefix)----------*/
   x_len = strlen (x_temp);
   switch (x_len % 4) {
   case 1 : strcat (x_temp, "0");
   case 2 : strcat (x_temp, "0");
   case 3 : strcat (x_temp, "0");
   }
   for (i = x_len / 4; i < a_cnt; ++i)  strcat (x_temp, "0000");
   if (strchr ("zZ", a_fmt) != NULL)  strcat (x_temp, "±");
   /*---(flip)-----------------*/
   x_len = strlen (x_temp) - 1;
   for (i = x_len; i >= 0; --i) x_final [x_len - i] = x_temp[i];
   /*---(delimit)--------------*/
   if (strchr ("Zq"    , a_fmt) != 0)   ySTR__space_ints (x_final, 4, '\'');
   if (strchr ("s"     , a_fmt) != 0)   ySTR__space_ints (x_final, 4, ' ');
   if (strchr (":"     , a_fmt) != 0)   ySTR__space_ints (x_final, 4, ':');
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#.max", a_max);
      DEBUG_STRG   yLOG_snote   ("too long");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format times into strings ---------------[ petal  [ 2f---- ]*/
strl4time          (double a_val, char *a_out, int a_decs, char a_fmt, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         x_int       =    0;
   char        x_final     [200] = "";
   int         i           =    0;
   long        x_now       = 0;
   tTIME      *x_time      = NULL;
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_snote   ("a_out null");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   DEBUG_STRG   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("tTdD", a_fmt) == NULL) {
      strlcpy (a_out, "#.fmt", a_max);
      DEBUG_STRG   yLOG_snote   ("format invalid");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#.neg", a_max);
      DEBUG_STRG   yLOG_snote   ("epoch number negative");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle time/date formats)-------*/
   x_now  = (long) a_val;
   x_time = localtime (&x_now);
   switch (a_fmt) {
   case 'd': strftime (x_final, 50, "%Y-%b-%d", x_time);
             break;
   case 't': strftime (x_final, 50, "%H:%M", x_time);
             break;
   case 'D': strftime (x_final, 50, "%Y-%b-%d %H:%M", x_time);
             break;
   case 'T': strftime (x_final, 50, "%Y.%m.%d.%H.%M.%S", x_time);
             break;
   }
   /*---(create)---------------*/
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#.max", a_max);
      DEBUG_STRG   yLOG_snote   ("too long");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
strl4main          (double a_val, char *a_out, int a_bytes, char a_fmt, int a_max)
{
   char        rc          = 0;
   switch (a_fmt) {
   case 'b' : case 'B' :
      rc = strl4bin   (a_val, a_out, a_bytes, a_fmt, a_max);
      break;
   case 'o' : case 'O' :
      rc = strl4oct   (a_val, a_out, a_bytes, a_fmt, a_max);
      break;
   case 'x' : case 'X' :
      rc = strl4hex   (a_val, a_out, a_bytes, a_fmt, a_max);
      break;
   case 'e' : case 'E' :
      rc = strl4sci   (a_val, a_out, a_bytes, a_fmt, a_max);
      break;
   case 'r' : case 'R' :
      rc = strl4roman (a_val, a_out, a_bytes, a_fmt, a_max);
      break;
   case 'z' : case 'Z' :
      rc = strl4mongo (a_val, a_out, a_bytes, a_fmt, a_max);
      break;
   case 'd' : case 't' : case 'D' : case 'T' :
      rc = strl4time  (a_val, a_out, a_bytes, a_fmt, a_max);
      break;
   default :
      rc = strl4comma (a_val, a_out, a_bytes, a_fmt, a_max);
      break;
   }
   /*---(complete)-----------------------*/
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        padding strings                       ----===*/
/*====================------------------------------------====================*/
static void      o___PADDING_________________o (void) {;}


char
strlpad              (char *a_src, char *a_out, char a_fil, char a_ali, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   char        x_temp      [200] = "";
   char        x_final     [200] = "";
   char       *x_back      = s_empty;
   char       *x_fore      = s_empty;
   int         i           =    0;
   char       *x_aligns    = "?<|>[^]{}";
   int         x_npre      =    0;              /* number of prefix fills     */
   int         x_nsuf      =    0;              /* number of suffix fills     */
   int         x_beg       =    0;              /* position of content beg    */
   int         x_width     =    0;
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_STRG   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_snote   ("a_out null");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   DEBUG_STRG   yLOG_spoint  (a_src);
   --rce;  if (a_src == NULL) {
      strlcpy (a_out, "#.src", a_max);
      DEBUG_STRG   yLOG_snote   ("a_src null");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_schar   (a_ali);
   --rce;  if (strchr (x_aligns, a_ali) == NULL) {
      strlcpy (a_out, "#.ali", a_max);
      DEBUG_STRG   yLOG_snote   ("alignment bad");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (a_ali == '?')  a_ali = '<';
   /*---(handle too short)---------------*/
   x_len  = strlen (a_src);
   if (x_len >  a_max) {
      sprintf (a_out, "%-*.*s>", a_max - 1, a_max - 1, a_src);
      return 0;
   }
   /*---(handle exact size)--------------*/
   if (x_len == a_max) {
      sprintf (a_out, "%-*.*s", a_max, a_max, a_src);
      return 0;
   }
   /*---(set filler)---------------------*/
   if      (a_fil == '-')    x_fore = x_back = s_dashes;
   else if (a_fil == '=')    x_fore = x_back = s_equals;
   else if (a_fil == '_')    x_fore = x_back = s_unders;
   else if (a_fil == '.')    x_fore = x_back = s_dots;
   else if (a_fil == '+')    x_fore = x_back = s_pluses;
   else if (a_fil == '/')    x_fore = x_back = s_divs;
   else if (a_fil == '"')  { x_fore = s_fore;  x_back = s_back; }
   else                      x_fore = x_back = s_empty;
   /*---(prefix/suffix)------------------*/
   sprintf (x_temp, "%s"     , a_src);
   if (x_len + 4 <  a_max) {
      if      (a_ali == '{')  {
         sprintf (x_temp, "%2.2s%s", x_back + 1, a_src);
      }
      else if (a_ali == '}') {
         sprintf (x_temp, "%s%2.2s", a_src, x_fore + x_len + 1);
      }
   }
   if (a_ali == '{')  a_ali = '[';
   if (a_ali == '}')  a_ali = ']';
   x_len  = strlen (x_temp);
   /*---(fix formats)--------------------*/
   if (x_len + 2 > a_max) {
      switch (a_ali) {
      case '[' :    a_ali = '<'; break;
      case ']' :    a_ali = '>'; break;
      }
   }
   /*---(create)-------------------------*/
   x_npre  = (a_max - x_len) / 2;
   x_nsuf  = a_max - x_len - x_npre;
   switch (a_ali) {
   case '<' :
      sprintf (x_final, "%s%.*s", x_temp, a_max - x_len, x_fore + x_len);
      break;
   case '>' :
      sprintf (x_final, "%.*s%s", a_max - x_len, x_back, x_temp);
      break;
   case '|' :
      sprintf (x_final, "%.*s%s%.*s", x_npre, x_back, x_temp, x_nsuf, x_fore + x_len + x_npre);
      break;
   case '[' :
      sprintf (x_final, "[%s%.*s]", x_temp, a_max - x_len - 2, x_fore + x_len + 1);
      break;
   case ']' :
      sprintf (x_final, "[%.*s%s]", a_max - x_len - 2, x_back + 1, x_temp);
      break;
   case '^' :
      sprintf (x_final, "[%.*s%s%.*s]", x_npre - 1, x_back + 1, x_temp, x_nsuf - 1, x_fore + x_len + x_npre);
      break;
   }
   /*---(copy)---------------------------*/
   strlcpy (a_out, x_final, a_max + 1);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

#define       LEN_TEXT  2000
char          unit_answer [ LEN_TEXT ];

char*            /* [------] unit test accessor ------------------------------*/
ySTR_unit          (char *a_question, int a_num)
{
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "ySTR_unit, unknown request", 100);
   /*---(string testing)-----------------*/
   if      (strncmp(a_question, "string"    , 20)  == 0) {
      snprintf (unit_answer, LEN_TEXT, "ySTR string      : [%s]", its.strtest);
   }
   /*---(argument testing)---------------*/
   else if (strncmp(a_question, "argc"      , 20)  == 0) {
      snprintf (unit_answer, LEN_TEXT, "ySTR argc        : %d", its.argc);
   }
   else if (strncmp(a_question, "argv"      , 20)  == 0) {
      if (a_num < 20 && a_num < its.argc)  {
         snprintf (unit_answer, LEN_TEXT, "ySTR argv (%2d)   : %3d [%-.40s]", a_num, strllen (its.argv[a_num], 2000), its.argv[a_num]);
      } else {
         snprintf (unit_answer, LEN_TEXT, "ySTR argv (%2d)   : index out of range", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

char       /*----: set up program urgents/debugging --------------------------*/
ySTR_testquiet     (void)
{
   ySTR_debug ('-');
   its.logger = yLOG_begin ("ySTR" , yLOG_SYSTEM, yLOG_QUIET);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ySTR_testloud      (void)
{
   ySTR_debug ('y');
   its.logger = yLOG_begin ("ySTR" , yLOG_SYSTEM, yLOG_NOISE);
   DEBUG_STRG   yLOG_info     ("ySTR"    , ySTR_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ySTR_testend       (void)
{
   yLOG_end     ();
   return 0;
}



/*===[[ END ]]================================================================*/
