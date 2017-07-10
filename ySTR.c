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
   /*---(complete)-----------------------*/
   return x_len - c;
}

int              /* ---- : count contiguous spaces ---------------------------*/
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
   char        x_final     [2000] = "";
   /*---(defenses)-----------------------*/
   --rce;  if (a_src == NULL)     return  rce;
   --rce;  if (a_old == NULL)     return  rce;
   --rce;  if (a_new == NULL)     return  rce;
   --rce;  if (a_max >= 2000)     return  rce;
   /*---(cycle)--------------------------*/
   --rce;
   while (1) {
      t = strstr (s, o);
      if (t == NULL)              break;
      if (c >= a_cnt)             break;
      if (lenf + lend >= 2000)    break;
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
   case 'a' : strcpy (x_legal, x_alpha);            break;
   case '9' : strcpy (x_legal, x_alnum);            break;
   case 'b' : strcpy (x_legal, x_basic);            break;
   case 'w' : strcpy (x_legal, x_write);            break;
   case 'e' : strcpy (x_legal, x_exten);            break;
   case 'p' : for (i = ' '; i <= '~'; ++i) {
                 j = i - ' ';
                 x_legal [j    ] = i;
                 x_legal [j + 1] = '\0';
              }
              break;
   case '7' : for (i = 1; i <= 127; ++i) {
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
   x_len = strllen (a_src, LEN_STR);
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
   x_len = strllen (a_src, LEN_STR);
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
   x_len = strllen (a_src, LEN_STR);
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
   char        x_temp      [LEN_STR ] = "";      /* temp version              */
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
   x_len = strllen (a_src, LEN_STR);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce; if (a_src [0] == '0' && (a_src [1] != '\0' && a_src [1] != '.')) {
      DEBUG_STRG   yLOG_snote   ("bad leading zero");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (x_temp, a_src, LEN_STR);
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

ySTR__space_decs     (char *a_out, int a_count, char a_char)
{
   int         x_add       =    0;
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   x_len = strlen (a_out);
   x_add = a_count - (x_len % a_count);
   /*> printf ("a_out = %s, a_count = %d, x_len = %d, x_add %d\n", a_out, a_count, x_len, x_add);   <*/
   for (i = 0; i < x_add; ++i)  strcat (a_out, "0");
   /*> printf ("a_out = %s\n", a_out);                                                <*/
   if (x_len > 3)  ySTR__space_ints     (a_out, a_count, a_char);
   /*> printf ("a_out = %s\n", a_out);                                                <*/
   x_len = strlen (a_out);
   for (i = 0; i < x_add; ++i)  a_out [--x_len] = '\0';
   /*> printf ("a_out = %s\n", a_out);                                                <*/
   return 0;
}

char         /*-> format binary numbers to string ---------[ petal  [ 2f---- ]*/
strl4bin           (double a_val, char *a_out, int a_nibs, char a_form, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   long        x_num       =    0;
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
   strlcpy (a_out, "", a_max);
   if (a_val < 0.0)  a_val  *= -1;
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
   /*---(flip)-----------------*/
   strcat (x_temp, "b");
   x_len = strlen (x_temp) - 1;
   for (i = x_len; i >= 0; --i) x_final [x_len - i] = x_temp[i];
   /*---(create)---------------*/
   if (a_form == 'd' || a_form == 'D' || a_form == 'B')  ySTR__space_ints (x_final, 4, '\'');
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
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
strl4oct           (double a_val, char *a_out, int a_bytes, char a_form, int a_max)
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
   if (a_val < 0.0)  a_val  *= -1;
   strlcpy (a_out, "", a_max);
   /*---(translate base)-------*/
   sprintf  (x_temp, "%o",       (long)  a_val);
   /*---(make prefix)----------*/
   x_len = strlen (x_temp);
   if (x_len % 3 == 2) { strcat  (x_prefix,  "0"); x_len += 1; }
   if (x_len % 3 == 1) { strcat  (x_prefix, "00"); x_len += 2; }
   for (i = x_len / 3; i < a_bytes; ++i)  strcat (x_prefix, "000");
   /*---(create)---------------*/
   sprintf (x_final, "o%s%s" , x_prefix, x_temp);
   if (a_form == 'd' || a_form == 'D' || a_form == 'O')  ySTR__space_ints (x_final, 3, '\'');
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
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
strl4hex           (double a_val, char *a_out, int a_bytes, char a_form, int a_max)
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
   if (a_val < 0.0)  a_val  *= -1;
   strlcpy (a_out, "", a_max);
   /*---(translate base)-------*/
   switch (a_form) {
   case 'u' :  case 'd' :  case 'x' :  case 'X' :
      sprintf  (x_temp, "%x",       (long)  a_val);
      break;
   case 'U' :  case 'D' :
      sprintf  (x_temp, "%X",       (long)  a_val);
      break;
   }
   /*---(make prefix)----------*/
   x_len = strlen (x_temp);
   if (x_len % 2 == 1) {
      strcpy  (x_prefix, "0");
      ++x_len;
   }
   for (i = x_len / 2; i < a_bytes; ++i)  strcat (x_prefix, "00");
   /*---(create)---------------*/
   sprintf (x_final, "x%s%s" , x_prefix, x_temp);
   if (a_form == 'd' || a_form == 'D' || a_form == 'X')  ySTR__space_ints (x_final, 2, '\'');
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
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
strl4comma         (double a_val, char *a_out, int a_decs, char a_form, int a_max)
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
   if (a_val < 0.0)  x_sign  = -1;
   strlcpy (a_out, "", a_max);
   DEBUG_STRG   yLOG_schar   (a_form);
   --rce;  if (strchr ("ifeEcCaAsS$#prR?", a_form) == NULL) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (a_val < 0.0)    x_sign  = -1;
   if (a_form == '?')  a_form  = 'i';
   if (a_form == 'i')  a_decs  =  0;
   if (tolower (a_form) == 'e' && a_decs == 0)  a_decs  =  1;
   /*---(parse out)----------------------*/
   for (i = 0; i < a_decs; ++i)  x_exp *= 10;
   if (tolower (a_form) == 'p') x_pct = 100;
   x_round  = round (a_val * x_sign * x_exp * x_pct);
   x_int    = x_round / x_exp;
   x_frac   = x_round - (x_int * x_exp);
   /*---(assemble prefix)----------------*/
   if (tolower (a_form) == '$')  strcat (x_final, "$");
   if (x_sign < 0) {
      switch (tolower (a_form)) {
      case 'c' : case 's' : case 'i' : case 'f' : case 'e' : case 'E' : case 'p' :
         strcat (x_final, "-");
         break;
      case 'a' : case '$' :
         strcat (x_final, "(");
         break;
      }
   } else {
      switch (tolower (a_form)) {
      case 's' : case 'E' :
         strcat (x_final, "+");
         break;
      }
   }
   DEBUG_STRG  yLOG_snote    (x_final);
   /*---(format integer part)------------*/
   sprintf (x_temp, "%lld", x_int);
   x_len = strlen (x_temp);
   if (strchr ("ireE", a_form) == NULL)  ySTR__space_ints (x_temp, 3, ',');
   strcat (x_final, x_temp);
   DEBUG_STRG  yLOG_snote    (x_temp);
   /*---(decimal part)-------------------*/
   if (a_form != 'i' && a_decs > 0) {
      sprintf (x_temp, "%0*lld", a_decs, x_frac);
      if (strchr ("EACSM#", a_form) != NULL)  ySTR__space_decs (x_temp, 3, '\'');
      strcat  (x_final, ".");
      strcat  (x_final, x_temp);
   }
   DEBUG_STRG  yLOG_snote    (x_temp);
   /*---(assemble suffix)----------------*/
   if (x_sign < 0) {
      switch (tolower (a_form)) {
      case 'a' : case '$' :
         strcat (x_final, ")");
         break;
      case 'p' :
         strcat (x_final, ")");
         break;
      case '#' :
         strcat (x_final, " -");
         break;
      }
   } else {
      switch (tolower (a_form)) {
      case 'a' : case '$' :
         strcat (x_final, "_");
         break;
      case 'p' :
         strcat (x_final, ")");
         break;
      case '#' :
         strcat (x_final, " +");
         break;
      }
   }
   DEBUG_STRG  yLOG_snote    (x_final);
   /*---(scienfific)-----------*/
   if (tolower (a_form) == 'e') {
      strcpy  (x_final, "");
      /*---(make prefix)-----------------*/
      if (x_sign < 0)          strcpy (x_final, "-");
      else if (a_form == 'E')  strcpy (x_final, "+");
      sprintf (x_temp, "%.*e", a_decs, a_val * x_sign);
      strncat (x_final, x_temp, 2);
      /*---(save exponent/suffix)--------*/
      strcpy  (x_suffix, x_temp + a_decs + 2);
      x_temp  [a_decs + 2] = '\0';
      /*---(parse decimals)--------------*/
      strcpy  (x_prefix, x_temp + 2);
      if (a_form == 'E' && a_decs > 3)  ySTR__space_decs (x_prefix, 3, '\'');
      /*---(contat)----------------------*/
      strcat  (x_final, x_prefix);
      if (a_form == 'E')  strcat  (x_final, " ");
      strcat  (x_final, x_suffix);
   }
   /*---(create)---------------*/
   x_len = strlen (x_final);
   DEBUG_STRG   yLOG_sint    (a_max);
   DEBUG_STRG   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
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
strl4roman         (double a_val, char *a_out, int a_decs, char a_form, int a_max)
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
   strlcpy (a_out, "", a_max);
   DEBUG_STRG   yLOG_schar   (a_form);
   --rce;  if (strchr ("rR", a_form) == NULL) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (a_val < 0.0)  a_val  *= -1;
   DEBUG_STRG   yLOG_sint    (a_val);
   --rce;  if (a_val > 4000) {
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_int = (int) a_val;
   if (x_int == 0) {
      if (a_form == 'r')  strcpy (a_out, "o");
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
      DEBUG_STRG   yLOG_snote   ("too long");
      DEBUG_STRG   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (a_form == 'r') {
      for (i = 0; i < x_len; ++i)  x_final [i] = tolower (x_final [i]);
   }
   strlcpy  (a_out, x_final, a_max);
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
