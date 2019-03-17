/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



tLOCAL    mySTR;



/*---(static variables)---------------*/
static char s_empty       [200] = "                                                                                                                                                                                                       ";
static char s_dashes      [200] = "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
static char s_equals      [200] = "=======================================================================================================================================================================================================";
static char s_unders      [200] = "_______________________________________________________________________________________________________________________________________________________________________________________________________";
static char s_dots        [200] = "·······································································································································································································";
static char s_pluses      [200] = "····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····";
static char s_fore        [200] = "Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö";
static char s_back        [200] = "Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ";
static char s_fore2       [200] = "¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿";
static char s_back2       [200] = "¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾";
static char s_place       [200] = "¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤";
static char s_bigdot      [200] = "´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´";
static char s_ruler       [200] = "····+····Á····+····Â····+····Ã····+····Ä····+····À····+····Á····+····Â····+····Ã····+····Ä····+····À····+····Á····+····Â····+····Ã····+····Ä····+····À····+····Á····+····Â····+····Ã····+····Ä····+····";
static char s_number      [200] = "123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789";
static char s_ylog        [200] = "+··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´";

static char s_numeric     [20] = "0123456789.-+";    /* only digits               */

/*                                 ÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏ   ÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏÏ   ·!¶#$%&'()*+,-./   @ABCDEFGHIJKLMNO   PQRSTUVWXYZ[µ]~_   `abcdefghijklmno   pqrstuvwxyz{|}~Ï   */
static char s_slashed     [128] = "________________" "________________" "·°¶Ë__Ð_¸¹_¨©-Î " "Ïèéýëìüê_ð_ñòóôö" "êþøùúû_ÿõï_ºµ»__" "_Ì¿_¾¥§¯Ö_ÔÓÖ_¦_" "¤_Í·«___ÉÊÅ­Ñ®¬_";



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
   snprintf (ySTR_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return ySTR_ver;
}

char         /*--> set debugging mode --------------------[ ------ [ ------ ]-*/
ySTR_debug         (char a_flag)
{
   /*---(set debug flag)-----------------*/
   if   (a_flag == 'y')  mySTR.debug   = 'y';
   else                  mySTR.debug   = '-';
   /*---(complete)-----------------------*/
   return 0;
}

char
str9align            (char a_align)
{
   if (a_align  == ' ')                                              return -1;
   if (a_align  ==  0 )                                              return -2;
   if (strchr ("? <|> [^] {}", a_align) == NULL)                     return -3;
   return 0;
}

char
str9filler           (char a_filler)
{
   if (a_filler == ' ')                                              return -1;
   if (a_filler ==  0 )                                              return -2;
   if (strchr ("? !-=_ +./ qQ@ :# *", a_filler) == 0)                return -3;
   return 0;
}

char
str9format           (char a_format)
{
   if (a_format == ' ')                                              return -1;
   if (a_format ==  0 )                                              return -2;
   if (strchr ("? ifF cCaAsS$;p eE rR bBoOxXzZ tTdD", a_format) == 0) return -3;
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

int          /*--> clean string characters ---------------[--------[--------]-*/
strlupper          (char *a_src, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         c           =    0;
   /*---(defense)------------------------*/
   if (a_src == NULL)  return  -11;
   if (a_max <  0   )  a_max  = 0;
   /*---(move)---------------------------*/
   for (i = 0; i <= a_max; ++i) {
      a_src [i] = toupper (a_src [i]);
      if (a_src [i] == 0)  break;
      ++c;
   }
   a_src [a_max - 1] = '\0';
   if (c > a_max)  --c;
   /*---(complete)-----------------------*/
   return c;
}

int          /*--> clean string characters ---------------[--------[--------]-*/
strllower          (char *a_src, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         c           =    0;
   /*---(defense)------------------------*/
   if (a_src == NULL)  return  -11;
   if (a_max <  0   )  a_max  = 0;
   /*---(move)---------------------------*/
   for (i = 0; i <= a_max; ++i) {
      a_src [i] = tolower (a_src [i]);
      if (a_src [i] == 0)  break;
      ++c;
   }
   a_src [a_max - 1] = '\0';
   if (c > a_max)  --c;
   /*---(complete)-----------------------*/
   return c;
}



/*====================------------------------------------====================*/
/*===----                           delimeter                          ----===*/
/*====================------------------------------------====================*/
static void      o___DELIMITER_______________o (void) {;}

int          /*-> tbd --------------------------------[ leaf   [gn.530.341.50]*/ /*-[02.0000.000.!]-*/ /*-[--.---.---.--]-*/
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
         if (c >= a_cnt)  return a_max - n;
      }
      l = *s;
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   return -1;
}

int          /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
strlchr            (char *a_src, char  a_chr, int a_max)
{
   return strldpos (a_src, a_chr, 1, a_max);
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



/*====================------------------------------------====================*/
/*===----                     extended ascii                           ----===*/
/*====================------------------------------------====================*/
static void      o___EXTENDED________________o (void) {;}

char         /*--> encode special characters -------------[ ------ [ ------ ]-*/
strlstore          (char *a_src, int a_max)
{
   strldchg (a_src, G_KEY_SPACE, G_CHAR_STORAGE, a_max);
   return 0;
}

char         /*--> encode special characters -------------[ ------ [ ------ ]-*/
strlunstore        (char *a_src, int a_max)
{
   strldchg (a_src, G_CHAR_STORAGE, G_KEY_SPACE, a_max);
   return 0;
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
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_ch        = a_ch;
   /*--- phoenicia/shrike mapping -------------*/
   switch (x_ch) {
   /*---(notes)---------------------*/
   case '-'  : x_ch = G_KEY_FIELD      ;  break;    /*    45 - =  31    */
   case '!'  : x_ch = G_CHAR_REXCLAM   ;  break;    /*    33 ! = 161 ¡   */
   case '?'  : x_ch = G_CHAR_RQUEST    ;  break;    /*    63 ? = 162 ¢   */
   /*---(hidden)--------------------*/
   case '0'  : x_ch = G_CHAR_NULL      ;  break;    /*    48 0 = 163 £   */
   case 'p'  : x_ch = G_CHAR_PLACE     ;  break;    /*   112 p = 164 ¤   */
   case 'e'  : x_ch = G_CHAR_ESCAPE    ;  break;    /*   101 e = 165 ¥   */
   case 'n'  : x_ch = G_CHAR_RETURN    ;  break;    /*   110 n = 166 ¦   */
   case 'f'  : x_ch = G_CHAR_FIELD     ;  break;    /*   102 f = 167 §   */
   case 'g'  : x_ch = G_CHAR_GROUP     ;  break;    /*   103 g = 168 ¨   */
   /*---(macro)---------------------*/
   case '+'  : x_ch = G_CHAR_DISPLAY   ;  break;    /*    43 + = 169 ©   */
   case '.'  : x_ch = G_CHAR_BREAK     ;  break;    /*    46 . = 170 ª   */
   case ','  : x_ch = G_CHAR_WAIT      ;  break;    /*    44 , = 171 «   */
   case '*'  : x_ch = G_CHAR_MASK      ;  break;    /*    42 * = 172 ¬   */
   case 't'  : x_ch = G_CHAR_TAB       ;  break;    /*   116 t = 173 ­   */
   case ':'  : x_ch = G_CHAR_SUMMARY   ;  break;    /*    58 : = 174 ®   */
   case '%'  : x_ch = G_CHAR_SYSTEM    ;  break;    /*    37 % = 175 ¯   */
   /*---(special)-------------------*/
   case '$'  : x_ch = G_CHAR_HUGE      ;  break;    /*    36 $ = 177 ±   */
   case ' '  : x_ch = G_CHAR_STORAGE   ;  break;    /*    32   = 178 ²   */
   case 'q'  : x_ch = G_CHAR_HALT      ;  break;    /*   113 q = 179 ³   */
   case '@'  : x_ch = G_CHAR_BIGDOT    ;  break;    /*    64 @ = 180 ´   */
   /*---(delayed)-------------------*/
   case '\\' : x_ch = G_CHAR_DBSLASH   ;  break;    /*    92 \ = 181 µ   */
   case '"'  : x_ch = G_CHAR_DDQUOTE   ;  break;    /*    34 " = 182 ¶   */
   case 's'  : x_ch = G_CHAR_SPACE     ;  break;    /*   115 s = 183 ·   */
   /*---(grouping)------------------*/
   case '('  : x_ch = G_CHAR_SLPAREN   ;  break;    /*    40 ( = 184 ¸   */
   case ')'  : x_ch = G_CHAR_SRPAREN   ;  break;    /*    41 ) = 185 ¹   */
   case '['  : x_ch = G_CHAR_SLBRACK   ;  break;    /*    91 [ = 186 º   */
   case ']'  : x_ch = G_CHAR_SRBRACK   ;  break;    /*    93 ] = 187 »   */
   case '{'  : x_ch = G_CHAR_SLCHEV    ;  break;    /*   123 { = 188 ¼   */
   case '}'  : x_ch = G_CHAR_SRCHEV    ;  break;    /*   125 } = 189 ½   */
   case 'd'  : x_ch = G_CHAR_DEL       ;  break;    /*   100 d = 190 ¾   */
   case 'b'  : x_ch = G_CHAR_BS        ;  break;    /*    98 b = 191 ¿   */
   /*---(super/sub)-----------------*/
   case '5'  : x_ch = G_CHAR_SUB0      ;  break;    /*    53 5 = 192 À   */
   case '6'  : x_ch = G_CHAR_SUB1      ;  break;    /*    54 6 = 193 Á   */
   case '7'  : x_ch = G_CHAR_SUB2      ;  break;    /*    55 7 = 194 Â   */
   case '8'  : x_ch = G_CHAR_SUB3      ;  break;    /*    56 8 = 195 Ã   */
   case '9'  : x_ch = G_CHAR_SUB4      ;  break;    /*    57 9 = 196 Ä   */
   case 'z'  : x_ch = G_CHAR_SUBN      ;  break;    /*   122 z = 197 Å   */
   case '2'  : x_ch = G_CHAR_POW2      ;  break;    /*    50 2 = 198 Æ   */
   case '3'  : x_ch = G_CHAR_POW3      ;  break;    /*    51 3 = 199 Ç   */
   case '4'  : x_ch = G_CHAR_POW4      ;  break;    /*    52 4 = 200 È   */
   case 'x'  : x_ch = G_CHAR_POWX      ;  break;    /*   120 x = 201 É   */
   case 'y'  : x_ch = G_CHAR_POWY      ;  break;    /*   121 y = 202 Ê   */
   case '#'  : x_ch = G_CHAR_SMHASH    ;  break;    /*    35 # = 203 Ë   */
   case 'o'  : x_ch = G_CHAR_DEGREE    ;  break;    /*   111 o = 204 Ì   */
   case 'r'  : x_ch = G_CHAR_RADIAN    ;  break;    /*   114 r = 205 Í   */
   case '1'  : x_ch = G_CHAR_SQRT      ;  break;    /*    49 1 = 206 Î   */
   case '\'' : x_ch = G_CHAR_SMALL     ;  break;    /*    39 ' = 207 Ï   */
   /*---(logic)---------------------*/
   case '&'  : x_ch = G_CHAR_AND       ;  break;    /*    38 & = 208 Ð   */
   case '|'  : x_ch = G_CHAR_OR        ;  break;    /*   124 | = 209 Ñ   */
   case '^'  : x_ch = G_CHAR_XOR       ;  break;    /*    94 ^ = 210 Ò   */
   case 'k'  : x_ch = G_CHAR_UP        ;  break;    /*   107 k = 211 Ó   */
   case 'j'  : x_ch = G_CHAR_DOWN      ;  break;    /*   106 j = 212 Ô   */
   case 'l'  : x_ch = G_CHAR_RIGHT     ;  break;    /*   108 l = 213 Õ   */
   case 'h'  : x_ch = G_CHAR_LEFT      ;  break;    /*   104 h = 214 Ö   */
   case '<'  : x_ch = G_CHAR_LE        ;  break;    /*    60 < = 221 Ý   */
   case '>'  : x_ch = G_CHAR_GE        ;  break;    /*    62 > = 222 Þ   */
   case '='  : x_ch = G_CHAR_NE        ;  break;    /*    61 = = 223 ß   */
   case '~'  : x_ch = G_CHAR_APPROX    ;  break;    /*   126 ~ = 230 æ   */
   /*---(greek)---------------------*/
   case 'A'  : x_ch = G_CHAR_ALPHA     ;  break;    /*    65 A = 232 è   */
   case 'B'  : x_ch = G_CHAR_BETA      ;  break;    /*    66 B = 233 é   */
   case 'G'  : x_ch = G_CHAR_GAMMA     ;  break;    /*    71 G = 234 ê   */
   case 'D'  : x_ch = G_CHAR_DELTA     ;  break;    /*    68 D = 235 ë   */
   case 'E'  : x_ch = G_CHAR_EPSILON   ;  break;    /*    69 E = 236 ì   */
   case 'Z'  : x_ch = G_CHAR_ZETA      ;  break;    /*    90 Z = 237 í   */
   case 'H'  : x_ch = G_CHAR_ETA       ;  break;    /*    72 H = 238 î   */
   case 'Y'  : x_ch = G_CHAR_THETA     ;  break;    /*    89 Y = 239 ï   */
   case 'I'  : x_ch = G_CHAR_IOTA      ;  break;    /*    73 I = 240 ð   */
   case 'K'  : x_ch = G_CHAR_KAPPA     ;  break;    /*    75 K = 241 ñ   */
   case 'L'  : x_ch = G_CHAR_LAMBDA    ;  break;    /*    76 L = 242 ò   */
   case 'M'  : x_ch = G_CHAR_MU        ;  break;    /*    77 M = 243 ó   */
   case 'N'  : x_ch = G_CHAR_NU        ;  break;    /*    78 N = 244 ô   */
   case 'X'  : x_ch = G_CHAR_XI        ;  break;    /*    88 X = 245 õ   */
   case 'O'  : x_ch = G_CHAR_OMICRON   ;  break;    /*    79 O = 246 ö   */
   case 'P'  : x_ch = G_CHAR_PI        ;  break;    /*    80 P = 247 ÷   */
   case 'R'  : x_ch = G_CHAR_RHO       ;  break;    /*    82 R = 248 ø   */
   case 'S'  : x_ch = G_CHAR_SIGMA     ;  break;    /*    83 S = 249 ù   */
   case 'T'  : x_ch = G_CHAR_TAU       ;  break;    /*    84 T = 250 ú   */
   case 'U'  : x_ch = G_CHAR_UPSILON   ;  break;    /*    85 U = 251 û   */
   case 'F'  : x_ch = G_CHAR_PHI       ;  break;    /*    70 F = 252 ü   */
   case 'C'  : x_ch = G_CHAR_CHI       ;  break;    /*    67 C = 253 ý   */
   case 'Q'  : x_ch = G_CHAR_PSI       ;  break;    /*    81 Q = 254 þ   */
   case 'W'  : x_ch = G_CHAR_OMEGA     ;  break;    /*    87 W = 255 ÿ   */
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
   /*> DEBUG_YSTR   yLOG_senter  (__FUNCTION__);                                      <*/
   /*> DEBUG_YSTR   yLOG_sint    (a_ch);                                              <*/
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
   /*> DEBUG_YSTR   yLOG_sint    (a_ch);                                              <*/
   /*> DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);                                      <*/
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
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   DEBUG_YSTR   yLOG_point   ("a_src"     , a_src);
   DEBUG_YSTR   yLOG_value   ("a_max"     , a_max);
   DEBUG_YSTR   yLOG_value   ("a_cnt"     , a_cnt);
   DEBUG_YSTR   yLOG_point   ("a_argc"    , a_argc);
   DEBUG_YSTR   yLOG_point   ("a_argv"    , a_argv);
   /*---(trucate to protect)-------------*/
   /*> strltrunc (a_src, a_max);                                                      <*/
   /*---(process string)-----------------*/
   while (*s != '\0') {
      DEBUG_YSTR   yLOG_complex ("registers" , "*s=%c/%03d, n=%3d, c=%3d", *s, *s, n, c);
      /*---(end conditions)--------------*/
      if (n <= 1     )  break;
      if (c >  a_cnt )  break;
      /*---(handle character)------------*/
      if (*s != ' ' && *s != '\t' && *s != '\v') {
         DEBUG_YSTR   yLOG_note    ("handle as character");
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
         DEBUG_YSTR   yLOG_note    ("handle as whitespace");
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
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
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
   char       *x_fore     = s_empty;
   char       *x_back     = s_empty;
   int         i           =    0;
   int         x_npre      =    0;              /* number of prefix fills     */
   int         x_nsuf      =    0;              /* number of suffix fills     */
   int         x_off       =    0;              /* position of content beg    */
   int         x_adj       =    0;              /* adjusted width             */
   int         x_width     =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_snote   ("a_out null");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, s_empty, a_max);
   DEBUG_YSTR   yLOG_spoint  (a_src);
   --rce;  if (a_src == NULL) {
      strlcpy (a_out, "#.src", a_max);
      DEBUG_YSTR   yLOG_snote   ("a_src null");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (a_ali);
   --rce;  if (str9align (a_ali) < 0) {
      strlcpy (a_out, "#.ali", a_max);
      DEBUG_YSTR   yLOG_snote   ("alignment bad");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (a_fil);
   --rce;  if (str9filler (a_fil) < 0) {
      strlcpy (a_out, "#.fil", a_max);
      DEBUG_YSTR   yLOG_snote   ("filler bad");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   if (a_ali == '?')  a_ali = '<';
   x_len  = strlen (a_src);
   /*---(shortcut for exact size)--------*/
   if (x_len == a_max) {
      sprintf (a_out, "%-*.*s", a_max, a_max, a_src);
      return 0;
   }
   /*---(shortcut for too long)----------*/
   else if (x_len >  a_max) {
      switch (a_ali) {
      case '<' : case '[' : case '{' : default :
         x_adj  = a_max - 1;
         x_off  = 0;
         sprintf (a_out, "%-*.*s>", x_adj, x_adj, a_src + x_off);
         break;
      case '|' : case '^' :
         x_adj  = a_max - 2;
         x_off  = x_len - a_max - ((x_len - a_max) / 2) + 1;
         sprintf (a_out, "<%-*.*s>", x_adj, x_adj, a_src + x_off);
         break;
      case '>' : case ']' : case '}' :
         x_adj  = a_max - 1;
         x_off  = x_len - a_max + 1;
         sprintf (a_out, "<%-*.*s", x_adj, x_adj, a_src + x_off);
         break;
      }
      return 0;
   }
   /*---(set filler)---------------------*/
   switch (a_fil) {
   case '-': x_fore = x_back = s_dashes;          break;
   case '=': x_fore = x_back = s_equals;          break;
   case '_': x_fore = x_back = s_unders;          break;
   case '.': x_fore = x_back = s_dots;            break;
   case '+': x_fore = x_back = s_pluses;          break;
   case '/': x_fore = x_back = s_place;           break;
   case '@': x_fore = x_back = s_bigdot;          break;
   case ':': x_fore = x_back = s_ruler;           break;
   case '#': x_fore = x_back = s_number;          break;
   case 'q': x_fore = s_fore ; x_back = s_back;   break;
   case 'Q': x_fore = s_fore2; x_back = s_back2;  break;
   default : x_fore = x_back = s_empty;           break;
   }
   /*---(prefix/suffix)------------------*/
   sprintf (x_temp, "%s"     , a_src);
   switch (a_ali) {
   case '{' :
      if (x_len + 4 <= a_max)  sprintf (x_temp, "%2.2s%s", x_fore + 1, a_src);
      a_ali = '[';
      break;
   case '}' :
      if (x_len + 4 <= a_max)  sprintf (x_temp, "%s%2.2s", a_src, x_back + a_max - 3);
      a_ali = ']';
      break;
   }
   x_len  = strlen (x_temp);
   /*---(fix formats)--------------------*/
   if (x_len + 2 > a_max) {
      switch (a_ali) {
      case '[' :    a_ali = '<'; break;
      case ']' :    a_ali = '>'; break;
      }
   }
   /*---(create)-------------------------*/
   x_nsuf  = (a_max - x_len) / 2;
   x_npre  = a_max - x_len - x_nsuf;
   switch (a_ali) {
   case '<' : sprintf (x_final, "%s%.*s", x_temp, a_max - x_len, x_back + x_len);                                     break;
   case '>' : sprintf (x_final, "%.*s%s", a_max - x_len, x_fore, x_temp);                                             break;
   case '|' : sprintf (x_final, "%.*s%s%.*s", x_npre, x_fore, x_temp, x_nsuf, x_back + x_len + x_npre);               break;
   case '[' : sprintf (x_final, "[%s%.*s]", x_temp, a_max - x_len - 2, x_back + x_len + 1);                           break;
   case ']' : sprintf (x_final, "[%.*s%s]", a_max - x_len - 2, x_fore + 1, x_temp);                                   break;
   case '^' : sprintf (x_final, "[%.*s%s%.*s]", x_npre - 1, x_fore + 1, x_temp, x_nsuf - 1, x_back + x_len + x_npre); break;
   }
   /*---(copy)---------------------------*/
   strlcpy (a_out, x_final, a_max + 1);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char          unit_answer [LEN_RECD];

char*            /* [------] unit test accessor ------------------------------*/
ySTR_unit          (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        s           [LEN_LABEL];
   char        t           [LEN_RECD ];
   int         i           =    0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "ySTR_unit, unknown request", 100);
   /*---(string testing)-----------------*/
   if      (strncmp(a_question, "string"    , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "ySTR string      : [%s]", mySTR.strtest);
   }
   else if (strncmp(a_question, "values"    , 20)  == 0) {
      strlcpy (t, "", LEN_RECD);
      for (i = 0; i < 10; ++i) {
         if (mySTR.strtest [i] == 0)  break;
         sprintf (s, "%03d", mySTR.strtest [i]);
         if (i > 0)  strlcat (t, " ", LEN_RECD);
         strlcat (t, s  , LEN_RECD);
      }
      snprintf (unit_answer, LEN_RECD, "ySTR values      : %s", t);
   }
   /*---(argument testing)---------------*/
   else if (strncmp(a_question, "argc"      , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "ySTR argc        : %d", mySTR.argc);
   }
   else if (strncmp(a_question, "argv"      , 20)  == 0) {
      if (a_num < 20 && a_num < mySTR.argc)  {
         snprintf (unit_answer, LEN_RECD, "ySTR argv (%2d)   : %3d [%-.40s]", a_num, strllen (mySTR.argv[a_num], 2000), mySTR.argv[a_num]);
      } else {
         snprintf (unit_answer, LEN_RECD, "ySTR argv (%2d)   : index out of range", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

char       /*----: set up program urgents/debugging --------------------------*/
ySTR_testquiet     (void)
{
   ySTR_debug ('-');
   mySTR.logger = yLOGS_begin ("ySTR" , YLOG_SYS, YLOG_QUIET);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ySTR_testloud      (void)
{
   ySTR_debug ('y');
   mySTR.logger = yLOGS_begin ("ySTR" , YLOG_SYS, YLOG_NOISE);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   DEBUG_YSTR   yLOG_info     ("ySTR"    , ySTR_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ySTR_testend       (void)
{
   yLOGS_end     ();
   return 0;
}



/*===[[ END ]]================================================================*/
