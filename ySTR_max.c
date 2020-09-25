/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



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
   uchar      *x_alpha     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
   uchar      *x_alnum     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";
   uchar      *x_files     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.";
   uchar      *x_basic     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-";
   uchar      *x_write     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_. ,:;!?-()\"\'&";
   uchar      *x_exten     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_. ,:;!?-()\"\'&<>{}[]+*/=#@\\^%`~^|$";
   uchar       x_legal     [300]        = "";
   int         i, j;                     /* loop iterators -- characters        */
   int         x_len       = 0;            /* source string length                */
   int         x_save      = 0;            /* source string length                */
   int         c           = 0;
   uchar       m           = '¬';           /* this is the marker char        */
   /*---(defenses)-----------------------*/
   --rce;  if (a_src == NULL)     return rce;
   /*---(setup legal characters)---------*/
   --rce;  switch (a_set) {
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
   if (a_type == 'c' && a_compress == 'y')   strlddel (a_src, m, x_save);
   /*---(complete)-----------------------*/
   --rce;  if (a_type == 'g' && c != 0)  return rce;
   return c;
}

char         /*--> check for character -------------------[--------[--------]-*/
strlgood           (uchar *a_src, char a_set, int a_max)
{
   return ystr__check ('g', a_src, a_set, '-', a_max);
}

short        /*--> find and count bad characters ---------[--------[--------]-*/
strlcheck          (uchar *a_src, char a_set, int a_max)
{
   return ystr__check ('k', a_src, a_set, '-', a_max);
}

short        /*--> find and mark bad characters ----------[--------[--------]-*/
strlmark           (uchar *a_src, char a_set, int a_max)
{
   return ystr__check ('c', a_src, a_set, '-', a_max);
}

short        /*--> find and remove bad characters --------[--------[--------]-*/
strlclean          (uchar *a_src, char a_set, int a_max)
{
   return ystr__check ('c', a_src, a_set, 'y', a_max);
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
      strlcpy (a_out, "#p/src", a_max);
      DEBUG_YSTR   yLOG_snote   ("a_src null");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (a_ali);
   --rce;  if (str9align (a_ali) < 0) {
      strlcpy (a_out, "#p/ali", a_max);
      DEBUG_YSTR   yLOG_snote   ("alignment bad");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (a_fil);
   --rce;  if (str9filler (a_fil) < 0) {
      strlcpy (a_out, "#p/fil", a_max);
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
      case '<' : case '[' : case '{' : case ':' : default :
         x_adj  = a_max - 1;
         x_off  = 0;
         sprintf (a_out, "%-*.*s>", x_adj, x_adj, a_src + x_off);
         break;
      case '|' : case '^' :
         x_adj  = a_max - 2;
         x_off  = x_len - a_max - ((x_len - a_max) / 2) + 1;
         sprintf (a_out, "<%-*.*s>", x_adj, x_adj, a_src + x_off);
         break;
      case '>' : case ']' : case '}' : case '\'' :
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
   case '~': x_fore = x_back = s_ruler;           break;
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
   case ':' : sprintf (x_final, "%s%.*s:", x_temp, a_max - x_len - 1, x_back + x_len);                                break;
   case '>' : sprintf (x_final, "%.*s%s", a_max - x_len, x_fore, x_temp);                                             break;
   case '\'': sprintf (x_final, "%.*s%s:", a_max - x_len - 1, x_fore, x_temp);                                        break;
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
