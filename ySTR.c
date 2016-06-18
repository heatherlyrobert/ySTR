/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



tLOCAL    its;



/*---(static variables)---------------*/
char        ySTR_ver     [500];



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

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
   if (strchr ("hbsem", a_mode) != 0) {
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
   if (strchr ("tbsem", a_mode) != 0) {
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
   if (strchr ("esm" , a_mode) != 0) {
      s     = a_src;
      n     = x_len;
      x_lim = 0;
      l     = 'y';
      if (a_mode == 's') x_lim = 1;
      while (*s != '\0') {
         if (a_mode != 'm' && *s == '"') {
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
   /*> s = a_src;                                                                     <* 
    *> n = a_max;                                                                     <* 
    *> c = 0;                                                                         <* 
    *> while (*(s + c) != '\0') {                                                     <* 
    *>    if (n  <  1)  break;                                                        <* 
    *>    n--;                                                                        <* 
    *>    if (*(s + c) == m) {                                                        <* 
    *>       --x_len;                                                                 <* 
    *>       c++;                                                                     <* 
    *>       continue;                                                                <* 
    *>    }                                                                           <* 
    *>    *s = *(s + c);                                                              <* 
    *>    s++;                                                                        <* 
    *> }                                                                              <* 
    *> *s = '\0';                                                                     <*/
   /*---(complete)-----------------------*/
   return x_len - c;
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

/*> char*        /+--> clean string characters ---------------[--------[--------]-+/                                                      <* 
 *> ySTR_clean         (char *a_source, char a_mode, char a_compress)                                                                     <* 
 *> {                                                                                                                                     <* 
 *>    /+---(design notes)-------------------+/                                                                                           <* 
 *>    /+                                                                                                                                 <* 
 *>     *   a = alpha    lower and upper case letters only                                                                                <* 
 *>     *   n = alnum    alpha plus numbers                                                                                               <* 
 *>     *   b = basic    alnum plus space, dash, and underscore                                                                           <* 
 *>     *   w = write    basic plus normal punctuation                                                                                    <* 
 *>     *   e = exten    write plus coding symbols                                                                                        <* 
 *>     *   p = print    all 7-bit printable ascii characters                                                                             <* 
 *>     *   7 = seven    all 7-bit, safe ascii characters                                                                                 <* 
 *>     *                                                                                                                                 <* 
 *>     +/                                                                                                                                <* 
 *>    /+---(locals)-----------+-----------+-+/                                                                                           <* 
 *>    char       *x_alpha     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";                                                 <* 
 *>    char       *x_alnum     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";                                       <* 
 *>    char       *x_basic     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789_-";                                     <* 
 *>    char       *x_write     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789_.,:;!?-()\"\'&";                        <* 
 *>    char       *x_exten     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789_.,:;!?-()\"\'&<>{}[]++/=#@\\^%`~^|$";   <* 
 *>    char        x_legal     [MAX_STR]   = "";                                                                                          <* 
 *>    int         i, j;                     /+ loop iterators -- characters        +/                                                    <* 
 *>    int         x_len       = 0;            /+ source string length                +/                                                  <* 
 *>    /+---(header)-------------------------+/                                                                                           <* 
 *>    DEBUG_YSTR  yLOG_enter   (__FUNCTION__);                                                                                           <* 
 *>    DEBUG_YSTR  yLOG_point   ("a_source"  , a_source);                                                                                 <* 
 *>    DEBUG_YSTR  yLOG_char    ("a_mode"    , a_mode);                                                                                   <* 
 *>    DEBUG_YSTR  yLOG_char    ("a_compress", a_compress);                                                                               <* 
 *>    /+---(defenses)-----------------------+/                                                                                           <* 
 *>    strcpy (s_string, "(null)");                                                                                                       <* 
 *>    if (a_source == NULL) {                                                                                                            <* 
 *>       DEBUG_YSTR  yLOG_note    ("null source, exiting");                                                                              <* 
 *>       DEBUG_YSTR  yLOG_exit    (__FUNCTION__);                                                                                        <* 
 *>       return NULL;                                                                                                                    <* 
 *>    }                                                                                                                                  <* 
 *>    DEBUG_YSTR  yLOG_info    ("a_source"  , a_source);                                                                                 <* 
 *>    x_len = strlen(a_source);                                                                                                          <* 
 *>    DEBUG_YSTR  yLOG_value   ("len"       , x_len);                                                                                    <* 
 *>    strcpy (s_string, "(empty)");                                                                                                      <* 
 *>    if (x_len    <= 0   ) {                                                                                                            <* 
 *>       DEBUG_YSTR  yLOG_note    ("no length, exiting");                                                                                <* 
 *>       DEBUG_YSTR  yLOG_exit    (__FUNCTION__);                                                                                        <* 
 *>       return NULL;                                                                                                                    <* 
 *>    }                                                                                                                                  <* 
 *>    /+---(setup legal characters)---------+/                                                                                           <* 
 *>    switch (a_mode) {                                                                                                                  <* 
 *>    case 'n' : strncpy (s_string, a_source, MAX_STR);                                                                                  <* 
 *>               DEBUG_YSTR  yLOG_note    ("no clean mode, exiting");                                                                    <* 
 *>               DEBUG_YSTR  yLOG_exit    (__FUNCTION__);                                                                                <* 
 *>               return a_source;                                                                                                        <* 
 *>               break;                                                                                                                  <* 
 *>    case 'a' : strcpy (x_legal, x_alpha);            break;                                                                            <* 
 *>    case '9' : strcpy (x_legal, x_alnum);            break;                                                                            <* 
 *>    case 'b' : strcpy (x_legal, x_basic);            break;                                                                            <* 
 *>    case 'w' : strcpy (x_legal, x_write);            break;                                                                            <* 
 *>    case 'e' : strcpy (x_legal, x_exten);            break;                                                                            <* 
 *>    case 'p' : for (i = ' '; i <= '~'; ++i) {                                                                                          <* 
 *>                  j = i - ' ';                                                                                                         <* 
 *>                  x_legal [j    ] = i;                                                                                                 <* 
 *>                  x_legal [j + 1] = '\0';                                                                                              <* 
 *>               }                                                                                                                       <* 
 *>               break;                                                                                                                  <* 
 *>    case '7' : for (i = 1; i <= 127; ++i) {                                                                                            <* 
 *>                  j = i - 1;                                                                                                           <* 
 *>                  x_legal [j    ] = i;                                                                                                 <* 
 *>                  x_legal [j + 1] = '\0';                                                                                              <* 
 *>               }                                                                                                                       <* 
 *>               break;                                                                                                                  <* 
 *>    default : strcpy (s_string, "(bad mode)");                                                                                         <* 
 *>              DEBUG_YSTR  yLOG_note    ("unknown mode, exiting");                                                                      <* 
 *>              DEBUG_YSTR  yLOG_exit    (__FUNCTION__);                                                                                 <* 
 *>              return NULL;                                                                                                             <* 
 *>    }                                                                                                                                  <* 
 *>    DEBUG_YSTR  yLOG_info    ("x_legal"   , x_legal);                                                                                  <* 
 *>    /+---(clear)--------------------------+/                                                                                           <* 
 *>    for (i = 0; i <= x_len; ++i) {                                                                                                     <* 
 *>       if (strchr (x_legal, a_source[i]) != 0)  continue;                                                                              <* 
 *>       if (a_compress == '\0') {                                                                                                       <* 
 *>          for (j = i; j <= x_len; ++j)  a_source[j] = a_source[j + 1];                                                                 <* 
 *>          --x_len;                                                                                                                     <* 
 *>          --i;                                                                                                                         <* 
 *>          continue;                                                                                                                    <* 
 *>       }                                                                                                                               <* 
 *>       a_source [i] = a_compress;                                                                                                      <* 
 *>    }                                                                                                                                  <* 
 *>    /+---(prepare for testing)------------+/                                                                                           <* 
 *>    strncpy (s_string, a_source, MAX_STR);                                                                                             <* 
 *>    /+---(complete)-----------------------+/                                                                                           <* 
 *>    DEBUG_YSTR  yLOG_exit    (__FUNCTION__);                                                                                           <* 
 *>    return a_source;                                                                                                                   <* 
 *> }                                                                                                                                     <*/


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



/*===[[ END ]]================================================================*/
