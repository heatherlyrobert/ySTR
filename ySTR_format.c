/*============================[[    beg-code    ]]============================*/
/*········´ ´·············headers·´ ´·········································*/
#include    "ySTR.h"
#include    "ySTR_priv.h"
/*········´ ´·····················´ ´·········································*/



/*===[[ BEG GNU GENERAL PUBLIC LICENSE (GPL) WARNING ]]=======================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2013 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might¦"    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ END GNU GENERAL PUBLIC LICENSE (GPL) WARNING ]]=======================*/



/*
 *   ySTR_format is all about human-consumable numbers for use on displays,
 *   for reports, and in ascii-text data files.  i do not want to invent an
 *   editor for all my applications.  vim is my editor of choice.  so, i
 *   will also make the input use of delimiters forgiving to keep editing
 *   quicker.  it will also tolerate misplaced commas or apostrophes as
 *   often happens in editing, and which do not change the value.
 *
 *   bin      2     
 *   oct      8     
 *   real    10     
 *   sci     10
 *   comma   10
 *   hex     16
 *   mongo   64
 *   roman   --
 */


/*
 *     999,999,999,999,999          1110á0011á0101á1111á0101á1101á1001á0011
 *
 *
 */

/*
 * --format-code- --binary----  --octal-----  --hex-------  --mongo-----
 *   -    none    11010011      131366        a59eba        k3VLqsLtn
 *   #    alt     ##-#--##      ·             ··             
 *   d    dels    1101'0011     131'366       a5'9e'ba      k3VL'qsLtn
 *   s    simple  0b11010011    0o131366      0xa59eba      0zk3VL'qsLtn
 *   c    clear   b'1101'0011   o'131'366     x'a5'9e'ba    z'k3VL'qsLtn
 *   g    greek   é'1101'0011   ö'131'366     õ'a5'9e'ba    ÿ'k3VL'qsLtn
 *   :    colon   é:1101:0011   ö:131:366     õ:a5:9e:ba    ÿ:k3VL:qsLtn
 *   t    tick    éá1101á0011   öá131á366     õáa5á9eába    ÿák3VLáqsLtn
 * 
 * 
 */

/*> static char s_numeric     [20] = "0123456789.-+";    /+ only digits               +/   <*/
/*> static char s_empty       [200] = "                                                                                                                                                                                                       ";   <*/


/*===[[ METIS ]]==============================================================*/
/*
 * metis  ww2··  convert comma representation back to real number
 * metis  ww1··  convert dollar and other misc in uncomma conversion
 *
 *
 *
 */

/*
 *  doubles can only reliably, precisely handle 15 digits,
 *  so i limit my integer formats to 15 digits as well
 */
#define   MAX_PRECISION   999999999999999LL


/* max significant digits, values set to block in whole bytes */
#define   MAX_SBIN        64    /*  b'1010'1010'1010'1010          8 bytes */
#define   MAX_SOCT        21    /*  o'123'456'701'234'567'234'567  8 bytes */
#define   MAX_SHEX        12    /*  x'12'34'56'78'9a'bc            6 bytes */
#define   MAX_SMONGO       8    /*  z'3VLq'sLtn                    6 bytes */



/*> #define   MAX_SBIN        16    /+  b'1010'1010'1010'1010          2 bytes +/     <*/
/*> #define   MAX_SOCT        15    /+  o'123'456'701'234'567'567'567  8 bytes +/     <*/
/*> #define   MAX_SHEX        12    /+  x'12'34'56'78'9a'bc'9a'bc      8 bytes +/     <*/
/*> #define   MAX_SMONGO       8    /+  z'3VLq'sLtn                    6 bytes +/     <*/

/* max values, based on significant digits, LEN_TITLE, logical lengths */
#define   MAX_VBIN             16777216.0  /*  2^24   */
#define   MAX_VOCT       35184372088832.0  /*  8^15   */
#define   MAX_VHEX      281474976710656.0  /* 16^12   */
#define   MAX_VMONGO    281474976710656.0  /* 64^08   */
#define   MAX_VROMAN               3999.0  /* classic */



/*====================------------------------------------====================*/
/*===----                 support for string to number                 ----===*/
/*====================------------------------------------====================*/
static void      o___STRING2SUPPORT__________o (void) {;}

char
ystr2_defense           (char a_src [LEN_HUND], ullong *r_ullong, double *r_double, char a_under, char a_pre, char a_greek, char *r_len, char *r_beg)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   char        x_1st       =  '-';
   char        x_2nd       =  '-';
   char        x_min       =   -1;               /* first translatable char   */
   char        x_beg       =  '-';
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_ullong != NULL)  *r_ullong =   0;
   if (r_double != NULL)  *r_double = 0.0;
   if (r_len    != NULL)  *r_len    =   0;
   if (r_beg    != NULL)  *r_beg    =   0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL || a_src [0] == '\0') {
      DEBUG_YSTR   yLOG_snote   ("a_src null/empty");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_spoint  (r_ullong);
   DEBUG_YSTR   yLOG_spoint  (r_double);
   --rce; if (r_ullong == NULL && r_double == NULL) {
      DEBUG_YSTR   yLOG_snote   ("a_ullong and r_double can not both be null");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce; if (r_ullong != NULL && r_double != NULL) {
      DEBUG_YSTR   yLOG_snote   ("a_ullong and r_double can not both be used");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(verify length)------------------*/
   DEBUG_YSTR   yLOG_snote   (a_src);
   x_len = strlen (a_src);
   DEBUG_YSTR   yLOG_sint    (x_len);
   DEBUG_YSTR   yLOG_sint    (a_under);
   --rce; if (x_len < a_under) {
      DEBUG_YSTR   yLOG_snote   ("a_src too short");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_pre == 'b') {
      if (x_len >= LEN_HUND) {
         DEBUG_YSTR   yLOG_snote   ("a_src binary too long");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   } else if (a_pre == 'o') {
      if (x_len >= LEN_DESC) {
         DEBUG_YSTR   yLOG_snote   ("a_src octal too long");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   } else if (x_len >= LEN_TITLE) {
      DEBUG_YSTR   yLOG_snote   ("a_src too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick-out)----------------------*/
   DEBUG_YSTR   yLOG_schar   (a_pre);
   DEBUG_YSTR   yLOG_schar   (a_greek);
   if (a_pre == 0 && a_greek == 0) {
      DEBUG_YSTR   yLOG_snote   ("no prefix to eval");
      if (r_len  != NULL)  *r_len   = x_len;
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return 0;
   }
   /*---(prepare)------------------------*/
   x_1st = tolower (a_src [0]);
   DEBUG_YSTR   yLOG_schar   (x_1st);
   x_2nd = tolower (a_src [1]);
   DEBUG_YSTR   yLOG_schar   (x_2nd);
   /*---(octal exception)----------------*/
   if (a_pre == 'o' && x_1st == '0') {
      DEBUG_YSTR   yLOG_snote   ("octal zero prefix");
      if (strchr ("oOö", x_2nd) == NULL) x_min  =  1;
      else                               x_min  =  2;
   }
   /*---(check prefixes)-----------------*/
   else if (a_pre != 0 && x_1st == a_pre) {
      DEBUG_YSTR   yLOG_snote   ("simple prefix");
      x_min  =  1;
   } else if (a_pre != 0 && x_1st == '0' && x_2nd == a_pre) {
      DEBUG_YSTR   yLOG_snote   ("zeroed prefix");
      x_min  =  2;
   } else if (a_greek != 0 && x_1st == a_greek) {
      DEBUG_YSTR   yLOG_snote   ("greek prefix");
      x_min  =  1;
   }
   DEBUG_YSTR   yLOG_sint    (x_min);
   if (x_min < 1) {
      DEBUG_YSTR   yLOG_snote   ("unknown prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for value)----------------*/
   x_beg = tolower (a_src [x_min]);
   --rce; if (x_beg == '\0') {
      if (a_pre == 'o' && x_1st == '0' && x_len == 1) {
         x_min = 0;
      } else {
         DEBUG_YSTR   yLOG_snote   ("prefix without value");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(save-back)----------------------*/
   if (r_len  != NULL)  *r_len   = x_len;
   if (r_beg  != NULL)  *r_beg   = x_min;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                  convert string to number                    ----===*/
/*====================------------------------------------====================*/
static void      o___STRING2NUMBER___________o (void) {;}

char         /*-> interpret binary numbers ----------------[ petal  [ 2f---- ]*/
ystr2bin                (char a_src [LEN_HUND], ullong *r_ullong, double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_type      =  'd';
   char        x_maxsig    =   48;               /* max full byte at 15 significant digits   */
   char        x_len       =    0;
   char        x_beg       =   -1;               /* first translatable char   */
   char        x_ch        =  '-';
   char        x_base      =    2;               /* base position             */
   char        x_digit     =    0;               /* digit value               */
   llong       x_place     =    1;               /* base position             */
   llong       x_final     =    0;               /* final value               */
   int         i           =    0;
   char       *x_valid     = "01";               /* only binary digits        */
   char        c           =    0;               /* digits included           */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_ullong != NULL)  *r_ullong =   0;
   if (r_double != NULL)  *r_double = 0.0;
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src,  r_ullong, r_double, 2 , 'b', 'é', &x_len, &x_beg);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   if (r_double == NULL)  { x_type = 'l'; x_maxsig = 64; }
   DEBUG_YSTR   yLOG_complex ("type"      , "%c, %d", x_type, x_maxsig);
   /*---(run digits)---------------------*/
   DEBUG_YSTR   yLOG_info    ("x_valid"   , x_valid);
   --rce;  for (i = x_len - 1; i >= x_beg; --i) {
      /*---(select)----------------------*/
      x_ch = a_src [i];
      DEBUG_YSTR   yLOG_char    ("x_ch"      , x_ch);
      /*---(filter)----------------------*/
      if (strchr ("':á", x_ch) != NULL) {
         DEBUG_YSTR   yLOG_note    ("skipping separator");
         continue;
      }
      if (strchr (x_valid, x_ch) == NULL) {
         DEBUG_YSTR   yLOG_note    ("BAD CHARACTER");
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(process)---------------------*/
      x_digit  = x_ch - '0';
      x_final += x_digit * x_place;
      DEBUG_YSTR   yLOG_complex ("update"    , "%2d, %llu", x_digit, x_final);
      /*---(overflow)--------------------*/
      if (x_type == 'd') {
         if (x_final < 0) {
            DEBUG_YSTR   yLOG_note    ("UNDERFLOW");
            DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         if (x_final > MAX_PRECISION) {
            DEBUG_YSTR   yLOG_note    ("OVERFLOW");
            DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      /*---(accepted digits)-------------*/
      ++c;
      DEBUG_YSTR   yLOG_value   ("c"         , c);
      if (c > x_maxsig) {
         DEBUG_YSTR   yLOG_note    ("TOO MANY SIGS");
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(next)------------------------*/
      x_place *= x_base;
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   if (r_ullong != NULL)  *r_ullong = x_final;
   if (r_double != NULL)  *r_double = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> interpret octal numbers -----------------[ petal  [ 2e---- ]*/
ystr2oct                (char a_src [LEN_TITLE], double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_len       =    0;
   char        x_beg       =   -1;               /* first translatable char   */
   char        x_ch        =  '-';               /* current character         */
   int         x_base      =    8;               /* base position             */
   char        x_curr      =  '-';               /* current character         */
   int         x_digit     =    0;               /* digit value               */
   llong       x_place     =    1;               /* base position             */
   llong       x_final     =    0;               /* final value               */
   int         i           =    0;               /* iterator -- character     */
   char        x_valid     [20] = "01234567";    /* only octal digits           */
   char        c           =    0;               /* digits included           */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, NULL    , r_double,  1 , 'o', 'ö', &x_len, &x_beg);
   DEBUG_YSTR   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(run digits)---------------------*/
   DEBUG_YSTR   yLOG_sint    (x_base);
   DEBUG_YSTR   yLOG_snote   (x_valid);
   --rce;  for (i = x_len - 1; i >= x_beg; --i) {
      /*---(select)----------------------*/
      x_ch = a_src [i];
      DEBUG_YSTR   yLOG_schar   (x_ch);
      /*---(filter)----------------------*/
      if (strchr ("':á", x_ch) != NULL)  continue;
      if (strchr (x_valid , x_ch)  == 0) {
         DEBUG_YSTR   yLOG_snote   ("BAD CHAR");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(process)---------------------*/
      x_digit  = x_ch - '0';
      x_final += x_digit * x_place;
      DEBUG_YSTR   yLOG_sint    (x_final);
      /*---(overflow)--------------------*/
      if (x_final < 0 || x_final > MAX_PRECISION) {
         DEBUG_YSTR   yLOG_snote   ("OVERFLOW");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(accepted digits)-------------*/
      ++c;
      DEBUG_YSTR   yLOG_sint    (c);
      if (c > MAX_SOCT) {
         DEBUG_YSTR   yLOG_snote   ("TOO MANY SIGS");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(next)------------------------*/
      x_place *= x_base;
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (r_double != NULL)  *r_double = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> interpret hexadecimal numbers -----------[ petal  [ 2f---- ]*/
ystr2hex                (char a_src [LEN_TITLE], double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_len       =    0;
   char        x_beg       =   -1;               /* first translatable char   */
   char        x_ch        =  '-';               /* current character         */
   int         x_base      =   16;               /* base position             */
   int         x_digit     =    0;               /* digit value               */
   llong       x_place     =    1;               /* base position             */
   llong       x_final     =    0;               /* final value               */
   int         i           =    0;               /* iterator -- character     */
   char        c           =    0;               /* digits included           */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, NULL    , r_double,  2 , 'x', 'õ', &x_len, &x_beg);
   DEBUG_YSTR   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YSTR   yLOG_sint    (x_base);
   DEBUG_YSTR   yLOG_snote   (YSTR_HEX);
   /*---(run digits)---------------------*/
   --rce;  for (i = x_len - 1; i >= x_beg; --i) {
      /*---(select)----------------------*/
      x_ch = tolower (a_src [i]);
      DEBUG_YSTR   yLOG_schar   (x_ch);
      /*---(filter)----------------------*/
      if (strchr ("':á", x_ch) != NULL)  continue;
      if (strchr (YSTR_HEX, x_ch    )  == 0) {
         DEBUG_YSTR   yLOG_snote   ("BAD CHAR");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(process)---------------------*/
      if (x_ch >= '0' && x_ch <= '9')   x_digit  = x_ch - '0';
      else                              x_digit  = x_ch - 'a' + 10;
      x_final += x_digit * x_place;
      DEBUG_YSTR   yLOG_sint    (x_final);
      /*---(overflow)--------------------*/
      if (x_final < 0 || x_final > MAX_PRECISION) {
         DEBUG_YSTR   yLOG_snote   ("OVERFLOW");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(accepted digits)-------------*/
      ++c;
      DEBUG_YSTR   yLOG_sint    (c);
      if (c > MAX_SHEX) {
         DEBUG_YSTR   yLOG_snote   ("TOO MANY SIGS");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(next)------------------------*/
      x_place *= x_base;
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (r_double != NULL)  *r_double = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ystr2_divide            (char a_src [LEN_TITLE], char r_int [LEN_TITLE], char r_dec [LEN_TITLE], char r_exp [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_src       [LEN_TITLE] = "";
   int         l           =    0;
   char        n           =    0;
   char        c           =    0;
   char        x_dec       =  '-';
   char        x_exp       =  '-';
   char       *p           = NULL;
   char        x_sign      =  ' ';
   /*---(default)------------------------*/
   if (r_int   != NULL)  strcpy (r_int, "");
   if (r_dec   != NULL)  strcpy (r_int, "");
   if (r_exp   != NULL)  strcpy (r_int, "");
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   ystrlcpy (x_src, a_src, LEN_TITLE);
   DEBUG_YSTR   yLOG_snote   (x_src);
   l = strlen (x_src);
   DEBUG_YSTR   yLOG_sint    (l);
   /*---(count decimal points)-----------*/
   c = ystrlddcnt (x_src, '.', LEN_TITLE);
   DEBUG_YSTR   yLOG_sint    (c);
   --rce;  if (c > 1) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (c == 1)  x_dec = 'y';
   /*---(count exponent markers)---------*/
   c = n  = ystrlddcnt (x_src, 'Ë', LEN_TITLE);
   DEBUG_YSTR   yLOG_sint    (n);
   if (n == 1 && x_exp == '-')  x_exp = 'Ë';
   else {
      c += n = ystrlddcnt (x_src, 'e', LEN_TITLE);
      DEBUG_YSTR   yLOG_sint    (n);
      if (n == 1 && x_exp == '-')  x_exp = 'e';
      else {
         c += n = ystrlddcnt (x_src, 'E', LEN_TITLE);
         DEBUG_YSTR   yLOG_sint    (n);
         if (n == 1 && x_exp == '-')  x_exp = 'E';
      }
   }
   --rce;  if (c > 1) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(trailing sign)------------------*/
   DEBUG_YSTR   yLOG_schar   (x_src [l - 2]);
   DEBUG_YSTR   yLOG_schar   (x_src [l - 1]);
   --rce;  if (l >= 3 && x_src [l - 2] == ' ') {
      switch (x_src [l - 1]) {
      case '-' : x_sign = '-';        break;
      case '+' : x_sign = '+';        break;
      default  :
                 DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
                 return rce;
                 break;
      }
      l -= 2;
      x_src [l] = '\0';
   }
   /*---(trailing extra)-----------------*/
   if (x_src [l - 1] == ')') {
      x_src [--l] = '\0';
   }
   /*---(count delimiters)---------------*/
   c  = ystrlddcnt (x_src, ',' , LEN_TITLE);
   c += ystrlddcnt (x_src, '\'', LEN_TITLE);
   /*---(break off exponent)-------------*/
   DEBUG_YSTR   yLOG_schar   (x_exp);
   --rce;  if (x_exp != '-') {
      p = strchr (x_src, x_exp);
      DEBUG_YSTR   yLOG_spoint  (p);
      if (p == NULL) {
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      p [0] = '\0';
      ++p;
      DEBUG_YSTR   yLOG_snote   (p);
      if (strlen (p) == 0 || (strlen (p) == 1 && strchr ("+-", p [0]) != NULL)) {
         DEBUG_YSTR   yLOG_snote   ("no exp num");
         if (r_int  != NULL)  strcpy (r_int, "");
         if (r_dec  != NULL)  strcpy (r_dec, "");
         if (r_exp  != NULL)  strcpy (r_exp, "");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (r_exp  != NULL)  ystrlcpy (r_exp, p    , LEN_TITLE);
   }
   /*---(break out decimal)--------------*/
   l = 0;
   p = strchr (x_src, '.');
   DEBUG_YSTR   yLOG_spoint  (p);
   if (p != NULL) {
      p [0] = '\0';
      ++p;
      DEBUG_YSTR   yLOG_snote   (p);
      if (strlen (p) == 0) {
         DEBUG_YSTR   yLOG_snote   ("no dec num");
         if (r_int  != NULL)  strcpy (r_int, "");
         if (r_dec  != NULL)  strcpy (r_dec, "");
         if (r_exp  != NULL)  strcpy (r_exp, "");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      l += strlen (p);
      if (r_dec  != NULL)  ystrlcpy (r_dec, p    , LEN_TITLE);
   }
   /*---(save integer)-------------------*/
   if (r_int  != NULL)  {
      DEBUG_YSTR   yLOG_snote   (x_src);
      if (x_src [0] == '(')  x_src [0] = '-';
      if (x_sign == '-')  snprintf (r_int, LEN_TITLE, "%c%s", x_sign, x_src);
      else                ystrlcpy (r_int, x_src, LEN_TITLE);
      if (strlen (x_src) == 0 || (strlen (x_src) == 1 && strchr ("+-", x_src [0]) != NULL)) {
         DEBUG_YSTR   yLOG_snote   ("no int num");
         if (r_int  != NULL)  strcpy (r_int, "");
         if (r_dec  != NULL)  strcpy (r_dec, "");
         if (r_exp  != NULL)  strcpy (r_exp, "");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      l += strlen (x_src);
      if (strchr ("+-", x_src [0]) != NULL)  --l;
   }
   /*---(total significant)--------------*/
   l -= c;
   DEBUG_YSTR   yLOG_sint    (l);
   --rce;  if (l > 15) {
      DEBUG_YSTR   yLOG_snote   ("TOO MANY SIGS");
      if (r_int  != NULL)  strcpy (r_int, "");
      if (r_dec  != NULL)  strcpy (r_dec, "");
      if (r_exp  != NULL)  strcpy (r_exp, "");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ystr2_part              (char a_part, char a_src [LEN_TITLE], double *r_double)
{  /*---(design notes)-------------------*/
   /*
    *  i = integer part
    *  d = decimal part
    *  e = exponent part
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_len       =    0;
   char        x_beg       =    0;
   char        x_sign      =    1;
   int         i           =    0;
   char        x_ch        =  '-';
   char       *x_valid     = "0123456789";
   char        x_out       [LEN_TITLE] = "";
   char        n           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_double != NULL)  *r_double = 0.0;
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, NULL    , r_double,  1 ,  0 ,  0 , &x_len, NULL);
   DEBUG_YSTR   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(strip signs)--------------------*/
   DEBUG_YSTR   yLOG_schar   (a_part);
   if      (a_src [x_beg] == '$' && a_part == 'i')   { ++x_beg;   }
   else if (a_src [x_beg] == '(' && a_part == 'i')   { ++x_beg; x_sign = -1; }
   else if (a_src [x_beg] == '+' && a_part != 'd')   { ++x_beg;   }
   else if (a_src [x_beg] == '-' && a_part != 'd')   { ++x_beg; x_sign = -1; }
   DEBUG_YSTR   yLOG_sint    (x_sign);
   /*---(check for no payload)-----------*/
   DEBUG_YSTR   yLOG_sint    (x_beg);
   --rce;  if (x_beg == x_len) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(leading zero)-------------------*/
   DEBUG_YSTR   yLOG_schar   (a_src [x_beg]);
   --rce;  if (a_part == 'i' && x_beg + 1 < x_len && a_src [x_beg] == '0') {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle decimals)----------------*/
   if (a_part == 'd') { strcpy (x_out, "0."); n = 2; }
   /*---(run digits)---------------------*/
   DEBUG_YSTR   yLOG_snote   (x_valid);
   --rce;  for (i = x_beg; i < x_len; ++i) {
      /*---(select)----------------------*/
      x_ch = a_src [i];
      DEBUG_YSTR   yLOG_schar   (x_ch);
      /*---(filter)----------------------*/
      if (a_part == 'i' && x_ch == ',' )  continue;
      if (a_part == 'd' && x_ch == '\'')  continue;
      if (strchr (x_valid, x_ch) == NULL) {
         DEBUG_YSTR   yLOG_snote   ("BAD CHAR");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(process)---------------------*/
      x_out [n]   = x_ch;
      x_out [++n] = '\0';
      /*---(done)------------------------*/
   }
   /*---(exponent exception)-------------*/
   --rce;  if (a_part == 'e' && n > 2) {
      DEBUG_YSTR   yLOG_snote   ("EXP TOO LONG");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (r_double != NULL)  *r_double = atof (x_out) * x_sign;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ystr2comma              (char a_src [LEN_TITLE], double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_int       [LEN_TITLE] = "";
   double      x_vint      =  0.0;
   char        x_dec       [LEN_TITLE] = "";
   double      x_vdec      =  0.0;
   char        x_exp       [LEN_TITLE] = "";
   double      x_vexp      =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_double != NULL)  *r_double = 0.0;
   /*---(parttion)-----------------------*/
   rc = ystr2_divide (a_src, x_int, x_dec, x_exp);
   DEBUG_YSTR   yLOG_value   ("divide"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(nothing case)-------------------*/
   --rce;  if (strcmp (x_int, "") == 0 && strcmp (x_dec, "") == 0) {
      DEBUG_YSTR   yLOG_note    ("both integer and decimal parts empty");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(integer part)-------------------*/
   DEBUG_YSTR   yLOG_info    ("x_int"     , x_int);
   --rce;  if (strcmp (x_int, "") != 0) {
      rc = ystr2_part     ('i', x_int, &x_vint);
      DEBUG_YSTR   yLOG_value   ("int"       , rc);
      if (rc < 0) {
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YSTR   yLOG_double  ("x_vint"    , x_vint);
   }
   /*---(decimal part)-------------------*/
   DEBUG_YSTR   yLOG_info    ("x_dec"     , x_dec);
   --rce;  if (strcmp (x_dec, "") != 0) {
      rc = ystr2_part     ('d', x_dec, &x_vdec);
      DEBUG_YSTR   yLOG_value   ("dec"       , rc);
      if (rc < 0) {
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YSTR   yLOG_double  ("x_vdec"    , x_vdec);
   }
   /*---(exponent part)------------------*/
   DEBUG_YSTR   yLOG_info    ("x_exp"     , x_exp);
   --rce;  if (strcmp (x_exp, "") != 0) {
      rc = ystr2_part     ('e', x_exp, &x_vexp);
      DEBUG_YSTR   yLOG_value   ("exp"       , rc);
      if (rc < 0) {
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YSTR   yLOG_double  ("x_vexp"    , x_vexp);
   }
   /*---(save-back)----------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (r_double != NULL) {
      if (x_vint >= 0.0)  *r_double = x_vint + x_vdec;
      else                *r_double = x_vint - x_vdec;
      if (x_vexp != 0.0) {
         x_vexp = pow (10, x_vexp);
         if  (x_vexp >= 0)  *r_double = *r_double * x_vexp;
         else               *r_double = *r_double / (-x_vexp);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char ystr2real  (char a_src [LEN_TITLE], double *r_double) { return ystr2comma (a_src, r_double); }
char ystr2sci   (char a_src [LEN_TITLE], double *r_double) { return ystr2comma (a_src, r_double); }

struct {  /* roman numerals classically only went 1 - 3999 */
   char        r_chars     [LEN_SHORT];
   char        r_wide;
   int         r_value;
} S_roman [LEN_DESC] = {
   { "MMM"   , 3 ,  3000 },
   { "MM"    , 2 ,  2000 },
   { "M"     , 1 ,  1000 },
   { "CM"    , 2 ,   900 },
   { "DCCC"  , 4 ,   800 },
   { "DCC"   , 3 ,   700 },
   { "DC"    , 2 ,   600 },
   { "D"     , 1 ,   500 },
   { "CD"    , 2 ,   400 },
   { "CCC"   , 3 ,   300 },
   { "CC"    , 2 ,   200 },
   { "C"     , 1 ,   100 },
   { "XC"    , 2 ,    90 },
   { "LXXX"  , 4 ,    80 },
   { "LXX"   , 3 ,    70 },
   { "LX"    , 2 ,    60 },
   { "L"     , 1 ,    50 },
   { "XL"    , 2 ,    40 },
   { "XXX"   , 3 ,    30 },
   { "XX"    , 2 ,    20 },
   { "X"     , 1 ,    10 },
   { "IX"    , 2 ,     9 },
   { "VIII"  , 4 ,     8 },
   { "VII"   , 3 ,     7 },
   { "VI"    , 2 ,     6 },
   { "V"     , 1 ,     5 },
   { "IV"    , 2 ,     4 },
   { "III"   , 3 ,     3 },
   { "II"    , 2 ,     2 },
   { "I"     , 1 ,     1 },
   {  0      , 0 ,     0 },
};

char
ystr2roman              (char a_src [LEN_TITLE], double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_src       [LEN_TITLE] = "";
   char        l           =    0;
   char       *p           = NULL;
   int         i           =    0;
   int         x_final     =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, NULL    , r_double,  1 ,  0 ,  0 , &l, NULL);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_value   ("l"         , l);
   /*---(quick-out)----------------------*/
   if (strcmp (a_src, "N") == 0 || strcmp (a_src, "n") == 0) {
      DEBUG_YSTR   yLOG_snote   ("found N/n (zero)");
      DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   ystrlcpy   (x_src, a_src, LEN_TITLE);
   ystrlupper (x_src, LEN_TITLE);
   DEBUG_YSTR   yLOG_info    ("x_src"     , x_src);
   p = x_src;
   DEBUG_YSTR   yLOG_info    ("current"   , p);
   for (i = 0; i < LEN_DESC; ++i) {
      if (strncmp (p, S_roman [i].r_chars, S_roman [i].r_wide) == 0) {
         DEBUG_YSTR   yLOG_info    ("found"     , S_roman [i].r_chars);
         x_final += S_roman [i].r_value;
         p       += S_roman [i].r_wide;
         DEBUG_YSTR   yLOG_info    ("current"   , p);
      }
   }
   /*---(troubles)-----------------------*/
   DEBUG_YSTR   yLOG_point   ("end"       , x_src + l);
   --rce;  if (p < x_src + l) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_value   ("x_final"   , x_final);
   --rce;  if (x_final < 0 || x_final >= 4000) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (r_double != NULL)  *r_double = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ystr2mongo              (char a_src [LEN_TITLE], double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_len       =    0;
   char        x_beg       =   -1;               /* first translatable char   */
   char        x_ch        =  '-';               /* current character         */
   char        x_base      =   64;               /* base position             */
   char        x_digit     =    0;               /* digit value               */
   ullong      x_place     =    1;               /* base position             */
   ullong      x_final     =    0;               /* final value               */
   int         i           =    0;               /* iterator -- character     */
   char       *p           = NULL;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_double != NULL)  *r_double = 0.0;
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, NULL    , r_double,  5 , 'z', 'ÿ', &x_len, &x_beg);
   DEBUG_YSTR   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   DEBUG_YSTR   yLOG_snote   (YSTR_MONGO);
   x_base = strlen (YSTR_MONGO);
   DEBUG_YSTR   yLOG_sint    (x_base);
   /*---(run digits)---------------------*/
   --rce;  for (i = x_len - 1; i >= x_beg; --i) {
      /*---(select)----------------------*/
      x_ch = a_src [i];
      DEBUG_YSTR   yLOG_schar   (x_ch);
      /*---(filter)----------------------*/
      if (strchr ("':á", x_ch) != NULL)  continue;
      p = strchr (YSTR_MONGO, x_ch);
      if (p == NULL) {
         DEBUG_YSTR   yLOG_snote   ("BAD CHAR");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(process)---------------------*/
      x_digit = p - YSTR_MONGO;
      x_final += x_digit * x_place;
      DEBUG_YSTR   yLOG_sint    (x_final);
      /*---(overflow)--------------------*/
      if (x_final < 0 || x_final > MAX_PRECISION) {
         DEBUG_YSTR   yLOG_snote   ("OVERFLOW");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(accepted digits)-------------*/
      ++c;
      DEBUG_YSTR   yLOG_sint    (c);
      if (c > MAX_SMONGO) {
         DEBUG_YSTR   yLOG_snote   ("TOO MANY SIGS");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(next)------------------------*/
      x_place *= x_base;
      /*---(done)------------------------*/
   }
   /*---(save-back)----------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (r_double != NULL)  *r_double = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    number to string driver                   ----===*/
/*====================------------------------------------====================*/
static void      o___2DRIVER_________________o (void) {;}

char         /*-> check string for numeric value ----------[ petal  [ 2g---- ]*/
ystr2num                (char a_src [LEN_TITLE], double *r_double)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   double      x_value     =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_double  != NULL)  *r_double = 0.0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> DEBUG_YSTR   yLOG_value   ("a_src [0]" , a_src [0]);                           <*/
   /*> DEBUG_YSTR   yLOG_info    ("valid"     , YSTR_NUMERIC);                        <*/
   /*> --rce;  if (a_src [0] == 0 || strchr ("éõöí" YSTR_NUMERIC "$()", a_src [0]) == NULL) {   <* 
    *>    DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <*/
   x_len = strlen (a_src);
   /*---(oct, bin, hex)------------------*/
   DEBUG_YSTR   yLOG_value   ("a_src [1]" , a_src [1]);
   if (x_len > 1) {
      switch (a_src [0]) {
      case 'é':
         DEBUG_YSTR   yLOG_note    ("binary");
         rc = ystr2bin   (a_src, NULL    , &x_value);
         DEBUG_YSTR   yLOG_value   ("ystr2bin"  , rc);
         break;
      case 'ö':
         DEBUG_YSTR   yLOG_note    ("octal");
         rc = ystr2oct   (a_src, &x_value);
         DEBUG_YSTR   yLOG_value   ("ystr2oct"  , rc);
         break;
      case 'õ':
         DEBUG_YSTR   yLOG_note    ("hexadecimal");
         rc = ystr2hex   (a_src, &x_value);
         DEBUG_YSTR   yLOG_value   ("ystr2hex"  , rc);
         break;
      case 'ÿ':
         DEBUG_YSTR   yLOG_note    ("mongo");
         rc = ystr2mongo (a_src, &x_value);
         DEBUG_YSTR   yLOG_value   ("ystr2mongo", rc);
         break;
      }
   }
   /*---(scientific)---------------------*/
   if (rc < 0 && strchr (a_src, 'Ë') != NULL) {
      DEBUG_YSTR   yLOG_note    ("scientific notation");
      rc = ystr2sci (a_src, &x_value);
      DEBUG_YSTR   yLOG_value   ("ystr2sci"  , rc);
   }
   /*---(commma)-------------------------*/
   if (rc < 0 && strchr (a_src, ',') != NULL) {
      DEBUG_YSTR   yLOG_note    ("comma notation");
      rc = ystr2comma (a_src, &x_value);
      DEBUG_YSTR   yLOG_value   ("ystr2comma", rc);
   }
   /*---(roman)--------------------------*/
   if (rc < 0) {
      DEBUG_YSTR   yLOG_note    ("roman");
      rc = ystr2roman (a_src, &x_value);
      DEBUG_YSTR   yLOG_value   ("ystr2roman", rc);
   }
   /*---(float, int)---------------------*/
   if (rc < 0) {
      DEBUG_YSTR   yLOG_note    ("float/int");
      rc = ystr2real (a_src, &x_value);
      DEBUG_YSTR   yLOG_value   ("real"      , rc);
   }
   /*---(save-back)----------------------*/
   DEBUG_YSTR   yLOG_value   ("rc"        , rc);
   if (rc >= 0) {
      DEBUG_YSTR   yLOG_double  ("x_value"   , x_value);
      if (r_double != NULL)  *r_double = x_value;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                 support for number to string                 ----===*/
/*====================------------------------------------====================*/
static void      o___STRING4SUPPORT__________o (void) {;}

char
ystr4_defense           (char a_type, double a_val, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   char        x_1st       =  '-';
   char        x_2nd       =  '-';
   char        x_min       =   -1;               /* first translatable char   */
   char        x_beg       =  '-';
   double      x_max       =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_out  != NULL)   strcpy (r_out, "");

   return 0;

   /*---(check output)-------------------*/
   DEBUG_YSTR   yLOG_sint    (a_max);
   --rce; if (a_max < 4 || a_max >= LEN_TITLE) {
      DEBUG_YSTR   yLOG_snote   ("bad max");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce; if (r_out  == NULL) {
      DEBUG_YSTR   yLOG_snote   ("no out field");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_schar   (a_type);
   --rce; if (a_type == NULL || strchr ("box,emrt", a_type) == NULL) {
      DEBUG_YSTR   yLOG_snote   ("illegal type");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce; if (strchr ("boxmrt", a_type) != NULL && a_val < 0) {
      DEBUG_YSTR   yLOG_snote   ("a_val can not be negative");
      ystrlcpy (r_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(maximum values)-----------------*/
   DEBUG_YSTR   yLOG_sdouble (a_val);
   --rce; if (a_val > MAX_PRECISION) {
      DEBUG_YSTR   yLOG_snote   ("general overflow");
      ystrlcpy (r_out, "#p/big", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce; if (strchr ("boxmr", a_type) != NULL) {
      switch (a_type) {
      case 'b' : x_max = MAX_VBIN;    break;
      case 'o' : x_max = MAX_VOCT;    break;
      case 'x' : x_max = MAX_VHEX;    break;
      case 'm' : x_max = MAX_VMONGO;  break;
      case 'r' : x_max = MAX_VROMAN;  break;
      }
      if (a_val > x_max) {
         DEBUG_YSTR   yLOG_snote   ("too many significant digits");
         ystrlcpy (r_out, "#p/big", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check standard formats)---------*/
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("boxm", a_type) != NULL) {
      if (a_fmt  == NULL || strchr ("-#dscg:t", a_fmt ) == NULL) {
         DEBUG_YSTR   yLOG_snote   ("illegal format");
         ystrlcpy (r_out, "#p/fmt", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ystr4_units             (char a_unit, double *b_value)
{
   double      x_scale     =  0.0;
   char       *x_valid     = "-YZEPTGMKHD.dcmunpfazy";
   /*---(defense)------------------------*/
   if (b_value == NULL)    return -1;
   /*---(units up)-----------------------*/
   switch (a_unit) {
   case 'Y' :  x_scale = 1000000000000000000000000.0;      break;
   case 'Z' :  x_scale = 1000000000000000000000.0;         break;
   case 'E' :  x_scale = 1000000000000000000.0;            break;
   case 'P' :  x_scale = 1000000000000000.0;               break;
   case 'T' :  x_scale = 1000000000000.0;                  break;
   case 'G' :  x_scale = 1000000000.0;                     break;
   case 'M' :  x_scale = 1000000.0;                        break;
   case 'K' :  x_scale = 1000.0;                           break;
   case 'H' :  x_scale = 100.0;                            break;
   case 'D' :  x_scale = 10.0;                             break;
   case '-' :  x_scale = 1.0;                              break;
   case '.' :  x_scale = 1.0;                              break;
   case 'd' :  x_scale = 0.1;                              break;
   case 'c' :  x_scale = 0.01;                             break;
   case 'm' :  x_scale = 0.001;                            break;
   case 'u' :  x_scale = 0.000001;                         break;
   case 'n' :  x_scale = 0.000000001;                      break;
   case 'p' :  x_scale = 0.000000000001;                   break;
   case 'f' :  x_scale = 0.000000000000001;                break;
   case 'a' :  x_scale = 0.000000000000000001;             break;
   case 'z' :  x_scale = 0.000000000000000000001;          break;
   case 'y' :  x_scale = 0.000000000000000000000001;       break;
   default  :  return -2;                                  break;
   }
   *b_value /= x_scale;
   /*---(complete)-----------------------*/
   return 0;
}

char
ystr4_space_ints        (char a_every, char a_char, char b_out [LEN_TITLE])
{
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   int         j           =    0;               /* iterator -- character     */
   x_len = strlen (b_out);
   for (i = (x_len - 1) / a_every; i > 0; --i) {
      for (j = x_len; j >= x_len - (i * a_every); --j) {
         b_out [j + 1] = b_out [j];
      }
      b_out [x_len - (i * a_every)] = a_char;
      ++x_len;
      b_out [x_len] = '\0';
   }
   return 0;
}

char
ystr4_space_decs        (char a_every, char a_char, char b_out [LEN_TITLE])
{
   int         x_add       =    0;
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   /*---(defense)------------------------*/
   x_len = strlen (b_out);
   if (x_len <= a_every)    return 0;
   /*---(add padding)--------------------*/
   x_add = x_len % a_every;
   if (x_add > 0)  x_add = a_every - x_add;
   /*> printf ("b_out = %s, a_every = %d, x_len = %d, x_add %d\n", b_out, a_every, x_len, x_add);   <*/
   for (i = 0; i < x_add; ++i)   strcat (b_out, "0");
   /*> printf ("b_out = %s\n", b_out);                                                <*/
   ystr4_space_ints     (a_every, a_char, b_out);
   /*> printf ("b_out = %s\n", b_out);                                                <*/
   x_len = strlen (b_out);
   for (i = 0; i < x_add; ++i)  b_out [--x_len] = '\0';
   /*> printf ("b_out = %s\n", b_out);                                                <*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                  convert number to string                    ----===*/
/*====================------------------------------------====================*/
static void      o___STRING4NUMBER___________o (void) {;}

char
ystrl4bool              (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   long        x_num       =    0;
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_final     [200] = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce;  if (r_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strcpy (r_out, " ");
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("yY"    , a_fmt) == NULL) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   /*---(any binary)-----------*/
   if (a_val == 0) {
      switch (a_fmt) {
      case 'Y' :   strcpy  (r_out, "Ú");    break;
      case 'y' :   strcpy  (r_out, "·");    break;
      }
   } else if (a_val < 0) {
      switch (a_fmt) {
      case 'Y' :   strcpy  (r_out, "Û");    break;
      case 'y' :   strcpy  (r_out, "t");    break;
      }
   } else {
      switch (a_fmt) {
      case 'Y' :   strcpy  (r_out, "Û");    break;
      case 'y' :   strcpy  (r_out, "T");    break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format binary numbers to string ---------[ petal  [ 2f---- ]*/
ystrl4bin           (ullong a_ullong, double a_double, char a_cnt, char a_fmt, char a_max, char r_out [LEN_HUND])
{ 
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   ullong      x_num       =    0;
   char        x_on        [LEN_TERSE] = "1";
   char        x_off       [LEN_TERSE] = "0";
   int         x_len       =    0;
   char        x_revs      [LEN_HUND]  = "";
   int         i           =    0;
   char        x_flip      [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr4_defense  ('b', a_double, a_fmt, a_max, r_out);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   if (a_fmt == '#') { strcpy (x_on  , "#"); strcpy (x_off , "-"); }
   if (a_ullong != 0)  x_num = a_ullong;
   else                x_num = (ullong) a_double;
   DEBUG_YSTR   yLOG_value   ("x_num"     , x_num);
   /*---(handle zero)--------------------*/
   if (x_num == 0) {
      DEBUG_YSTR   yLOG_note    ("found a zero");
      if (a_fmt == '#')     strcpy (x_revs, "----");
      else                  strcpy (x_revs, "0000");
   }
   /*---(build up content)---------------*/
   while (x_num > 0) {
      if (x_num % 2 == 0)   strcat (x_revs, x_off);
      else                  strcat (x_revs, x_on);
      x_num /= 2;
   }
   DEBUG_YSTR   yLOG_info    ("x_revs"    , x_revs);
   /*---(fill as necessary)--------------*/
   x_len = strlen (x_revs);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   switch (x_len % 4) {
   case 1 : strcat (x_revs, x_off);
   case 2 : strcat (x_revs, x_off);
   case 3 : strcat (x_revs, x_off);
   }
   DEBUG_YSTR   yLOG_info    ("x_revs"    , x_revs);
   /*---(pad front)----------------------*/
   x_len = strlen (x_revs);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   for (i = x_len / 4; i < a_cnt; ++i) {
      if (a_fmt == '#')     strcat (x_revs, "----");
      else                  strcat (x_revs, "0000");
   }
   DEBUG_YSTR   yLOG_info    ("x_revs"    , x_revs);
   /*---(flip)---------------------------*/
   x_len = strlen (x_revs) - 1;
   for (i = x_len; i >= 0; --i) x_flip [x_len - i] = x_revs [i];
   DEBUG_YSTR   yLOG_info    ("x_flip"    , x_flip);
   /*---(delimit)------------------------*/
   switch (a_fmt) {
   case 'd' :  case 'c' :  case 'g' : ystr4_space_ints (4, '\'', x_flip); break;
   case ':' :                         ystr4_space_ints (4, ':' , x_flip); break;
   case 't' :                         ystr4_space_ints (4, 'á' , x_flip); break;
   }
   DEBUG_YSTR   yLOG_info    ("x_flip"    , x_flip);
   /*---(set prefix)---------------------*/
   switch (a_fmt) {
   case '-' : case '#' : case 'd' :   break;
   case 's' :  strcpy (r_out, "0b");  break;
   case 'c' :  strcpy (r_out, "b'");  break;
   case 'g' :  strcpy (r_out, "é'");  break;
   case ':' :  strcpy (r_out, "é:");  break;
   case 't' :  strcpy (r_out, "éá");  break;
   }
   DEBUG_YSTR   yLOG_info    ("r_out"     , r_out);
   /*---(check length trouble)-----------*/
   --rce;  if (strlen (r_out) + strlen (x_flip) > a_max) {
      DEBUG_YSTR   yLOG_note    ("too long to fit");
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)------------*/
   ystrlcat (r_out, x_flip, LEN_HUND);
   DEBUG_YSTR   yLOG_info    ("r_out"     , r_out);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> format octal numbers to string ----------[ petal  [ 2f---- ]*/
ystrl4oct           (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_DESC])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_prefix    [200] = "";  /* temp working string            */
   char        x_final     [200] = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce;  if (r_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (r_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("oOzZnq:s", a_fmt) == NULL) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      ystrlcpy (r_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate base)-------*/
   sprintf  (x_temp, "%o",       (long)  a_val);
   /*---(make prefix)----------*/
   if (strchr ("oO", a_fmt) != NULL)  strcpy  (x_prefix, "ö");
   if (strchr ("zZ", a_fmt) != NULL)  strcpy  (x_prefix, "ö");
   x_len = strlen (x_temp);
   if (x_len % 3 == 1) { strcat  (x_prefix, "00"); x_len += 2; }
   if (x_len % 3 == 2) { strcat  (x_prefix,  "0"); x_len += 1; }
   for (i = x_len / 3; i < a_cnt; ++i)  strcat (x_prefix, "000");
   /*---(merge)----------------*/
   sprintf (x_final, "%s%s"  , x_prefix, x_temp);
   /*---(delimit)--------------*/
   switch (a_fmt) {
   case 'O' :
   case 'Z' :  case 'q' :  ystr4_space_ints (3, '\'', x_final);   break;
   case ':' :              ystr4_space_ints (3, ':' , x_final);   break;
   case 's' :              ystr4_space_ints (3, ' ' , x_final);   break;
   case 'o' :  case 'n' :  break;
   }
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy  (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
ystrl4hex           (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_prefix    [200] = "";  /* temp working string            */
   char        x_final     [200] = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce;  if (r_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (r_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("xXUDqQnN:sS", a_fmt) == NULL) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      ystrlcpy (r_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate base)-------*/
   if (strchr ("xXqns" , a_fmt) != 0)   sprintf  (x_temp, "%x", (long) a_val);
   else                                 sprintf  (x_temp, "%X", (long) a_val);
   DEBUG_YSTR   yLOG_snote   (x_temp);
   /*---(make prefix)----------*/
   x_len = strlen (x_temp);
   DEBUG_YSTR   yLOG_sint    (x_len);
   if (x_len % 2 == 1) {
      strcpy  (x_prefix, "0");
      ++x_len;
   }
   for (i = x_len / 2; i < a_cnt; ++i)  strcat  (x_prefix, "00");
   if (strchr ("xXUD"  , a_fmt) != 0)   sprintf (x_final, "õ%s%s", x_prefix, x_temp);
   else                                 sprintf (x_final, "%s%s" , x_prefix, x_temp);
   /*---(delimit)--------------*/
   if (strchr ("XDqQ"  , a_fmt) != 0)   ystr4_space_ints (2, '\'', x_final);
   if (strchr ("sS"    , a_fmt) != 0)   ystr4_space_ints (2, ' ' , x_final);
   if (strchr (":"     , a_fmt) != 0)   ystr4_space_ints (2, ':' , x_final);
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy  (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
ystrl4comma         (double a_val, char a_decs, char a_fmt, char a_unit, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_prefix    [200] = "";  /* temp working string            */
   char        x_suffix    [200] = "";  /* temp working string            */
   char        x_final     [200] = "";
   char        x_sign      =    1;
   double      x_scaled    = 0.0;           /* scaled version                 */
   char        x_unit      [LEN_SHORT];
   double      x_round     = 0.0;           /* rounded off value              */
   long      x_exp       = 1;             /* exponent to round off          */
   long      x_int       = 0;             /* whole part                     */
   long      x_frac      = 0;             /* fractional part                */
   long      x_pct       = 1;             /* fractional part                */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce;  if (r_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (r_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("iIfF,cCaAsS$#pP?", a_fmt) == NULL) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }

   if (a_val < 0.0)    x_sign  = -1;
   if (a_fmt == '?')   a_fmt   = 'i';
   if (a_fmt == 'i')   a_decs  =  0;
   /*---(scale)--------------------------*/
   x_scaled = a_val;
   rc = ystr4_units (a_unit, &x_scaled);
   --rce;  if (rc < 0) {
      ystrlcpy (r_out, "#p/uni", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if      (a_unit == '-')   strcpy  (x_unit, "");
   else if (a_unit == '.')   sprintf (x_unit, "%c", G_CHAR_BIGDOT);
   else                      sprintf (x_unit, "%c", a_unit);
   /*---(parse out)----------------------*/
   for (i = 0; i < a_decs; ++i)  x_exp *= 10;
   x_round  = round (x_scaled * x_sign * x_exp * x_pct);
   x_int    = x_round / x_exp;
   x_frac   = x_round - (x_int * x_exp);
   /*---(assemble prefix)----------------*/
   if (tolower (a_fmt) == '$')  strcat (x_final, "$");
   if (x_sign < 0) {
      if (strchr ("iIf,cspP", tolower (a_fmt)) != NULL)  strcat (x_final, "-");
      if (strchr ("a$"      , tolower (a_fmt)) != NULL)  strcat (x_final, "(");
   } else {
      if (strchr ("s"       , tolower (a_fmt)) != NULL)  strcat (x_final, "+");
   }
   DEBUG_YSTR  yLOG_snote    (x_final);
   /*---(format integer part)------------*/
   sprintf (x_temp, "%lld", x_int);
   x_len = strlen (x_temp);
   if (strchr ("iIfF", a_fmt) == NULL)  ystr4_space_ints (3, ',', x_temp);
   strcat (x_final, x_temp);
   DEBUG_YSTR  yLOG_snote    (x_temp);
   /*---(decimal part)-------------------*/
   if (strchr ("iI", a_fmt) == 0 && a_decs > 0) {
      sprintf (x_temp, "%0*lld", a_decs, x_frac);
      if (strchr ("ACS#F", a_fmt) != NULL)  ystr4_space_decs (3, '\'', x_temp);
      strcat  (x_final, ".");
      strcat  (x_final, x_temp);
   }
   DEBUG_YSTR  yLOG_snote    (x_temp);
   /*---(assemble suffix)----------------*/
   strcat (x_final, x_unit);
   if (x_sign < 0) {
      switch (a_fmt) {
      case 'a' : case 'A' : case '$' : strcat (x_final, ")");  break;
      case 'p' :                       strcat (x_final, ")");  break;
      case 'P' :                       strcat (x_final, "´");  break;
      case '#' :                       strcat (x_final, " -"); break;
      }
   } else {
      switch (a_fmt) {
      case 'a' : case 'A' : case '$' : strcat (x_final, "_");  break;
      case 'p' :                       strcat (x_final, ")");  break;
      case 'P' :                       strcat (x_final, "´");  break;
      case '#' :                       strcat (x_final, " +"); break;
      }
   }
   if (a_fmt == 'I' && a_decs > 0) {
      for (i = 0; i <= a_decs; ++i)  strcat (x_final, " ");
   }
   DEBUG_YSTR  yLOG_snote    (x_final);
   /*---(create)---------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy  (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
ystrl4sci           (double a_val, char a_decs, char a_fmt, char a_max, char r_out [LEN_TITLE])
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
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce;  if (r_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (r_out, YSTR_EMPTY, a_max);
   if (a_val < 0.0)  x_sign  = -1;
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("eE", a_fmt) == NULL) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)---------------------*/
   if (a_val < 0.0)  x_sign  = -1;
   if (a_decs == 0)  a_decs  =  1;
   strcpy  (x_final, "");
   /*---(make prefix)-----------------*/
   if (x_sign < 0)          strcpy (x_final, "-");
   else if (a_fmt == 'E')   strcpy (x_final, "+");
   sprintf (x_temp, "%.*e", a_decs, a_val * x_sign);
   strncat (x_final, x_temp, 2);
   /*---(save exponent/suffix)--------*/
   if (a_fmt == 'E')  strcpy  (x_suffix, x_temp + a_decs + 2);
   else               sprintf (x_suffix, "Ë%d", atoi (x_temp + a_decs + 3));
   x_temp  [a_decs + 2] = '\0';
   /*---(parse decimals)--------------*/
   strcpy  (x_prefix, x_temp + 2);
   if (a_fmt == 'E' && a_decs > 3)  ystr4_space_decs (3, '\'', x_prefix);
   /*---(contat)----------------------*/
   strcat  (x_final, x_prefix);
   /*> if (a_fmt == 'E')  strcat  (x_final, " ");                                     <*/
   strcat  (x_final, x_suffix);
   /*---(create)---------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrldchg (x_final, 'e', 'Ë', a_max);
   ystrldchg (x_final, 'E', 'Ë', a_max);
   ystrlcpy  (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
ystrl4roman         (double a_val, char a_decs, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         x_int       =    0;
   char        x_final     [LEN_TITLE] = "";
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defualt)------------------------*/
   if (r_out != NULL)  ystrlcpy (r_out, YSTR_EMPTY, a_max);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce;  if (r_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (a_fmt == 0 ||strchr ("rR", a_fmt) == NULL) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      ystrlcpy (r_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_val >= 4000) {
      ystrlcpy (r_out, "#p/big", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(starting point)-----------------*/
   x_int = (int) a_val;
   /*---(zero)---------------------------*/
   if (x_int == 0) {
      DEBUG_YSTR   yLOG_snote   ("handling zero");
      if (a_fmt == 'r')  ystrlcpy (r_out, "n", a_max);
      else               ystrlcpy (r_out, "N", a_max);
      DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   for (i = 0; i < LEN_DESC; ++i) {
      DEBUG_YSTR   yLOG_value   ("x_int"     , x_int);
      if (x_int - S_roman [i].r_value >= 0) {
         DEBUG_YSTR   yLOG_info    ("found"     , S_roman [i].r_chars);
         ystrlcat (x_final, S_roman [i].r_chars, LEN_TITLE);
         x_int -= S_roman [i].r_value;
      }
   }
   DEBUG_YSTR   yLOG_point   ("x_int"     , x_int);
   --rce;  if (x_int != 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(overflow)-----------------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(handgle lower case)-------------*/
   if (a_fmt == 'r') {
      for (i = 0; i < x_len; ++i)  x_final [i] = tolower (x_final [i]);
   }
   /*---(save-back)----------------------*/
   if (r_out  != NULL)  ystrlcpy  (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
ystrl4mongo         (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_final     [200] = "";
   long        x_int       =    0;
   int         x_digit     =    0;
   long        x_place     =    0;
   int         x_inc       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce;  if (r_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (r_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("zZnqs:", a_fmt) == NULL) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      ystrlcpy (r_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_int  = a_val;
   /*---(translate base)-------*/
   if (x_int == 0)  strcat (x_temp, "0000");
   x_inc   = strlen (YSTR_MONGO);
   while (x_int > 0) {
      x_digit = x_int % x_inc;
      x_temp [x_place++] = YSTR_MONGO [x_digit];
      x_temp [x_place  ] = '\0';
      x_int /= x_inc;
   }
   /*---(make prefix)----------*/
   x_len = strlen (x_temp);
   switch (x_len % 4) {
   case 1 : strcat (x_temp, "0");
   case 2 : strcat (x_temp, "0");
   case 3 : strcat (x_temp, "0");
   }
   for (i = x_len / 4; i < a_cnt; ++i)  strcat (x_temp, "0000");
   if (strchr ("zZ", a_fmt) != NULL)    strcat (x_temp, "ÿ");
   /*---(flip)-----------------*/
   x_len = strlen (x_temp) - 1;
   for (i = x_len; i >= 0; --i) x_final [x_len - i] = x_temp[i];
   /*---(delimit)--------------*/
   if (strchr ("Zq"    , a_fmt) != 0)   ystr4_space_ints (4, '\'', x_final);
   if (strchr ("s"     , a_fmt) != 0)   ystr4_space_ints (4, ' ' , x_final);
   if (strchr (":"     , a_fmt) != 0)   ystr4_space_ints (4, ':' , x_final);
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy  (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format times into strings ---------------[ petal  [ 2f---- ]*/
ystrl4time          (double a_val, char a_decs, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         x_int       =    0;
   char        x_final     [200] = "";
   int         i           =    0;
   long        x_now       = 0;
   tTIME      *x_time      = NULL;
   char        x_hrs       =    0;
   char        x_min       =    0;
   char        x_shift     =    0;
   char        t           [LEN_TERSE] = "";
   char       *x_shifts    = "gdmoauei";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce;  if (r_out == NULL) {
      DEBUG_YSTR   yLOG_snote   ("r_out null");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy (r_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("tTdD", a_fmt) == NULL) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_snote   ("format invalid");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      ystrlcpy (r_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_snote   ("epoch number negative");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle time/date formats)-------*/
   x_now  = (long) a_val;
   x_time = localtime (&x_now);
   switch (a_fmt) {
   case 'd': strftime (x_final, 50, "%Y-%b-%d", x_time);
             x_final [5] = tolower (x_final [5]);
             break;
   case 't': strftime (x_final, 50, "%H:%M", x_time);
             break;
   case 'D': strftime (x_final, 50, "%Y-%b-%d %H:%M", x_time);
             x_final [5] = tolower (x_final [5]);
             break;
   case 'T': strftime (x_final, 50, "%Y.%m.%d.%H.%M.%S.%u.%W.%j", x_time);
             sprintf (t, "%-2.2s", x_final + 11);
             x_hrs = atoi (t);
             sprintf (t, "%-2.2s", x_final + 14);
             x_min = atoi (t);
             switch (x_hrs) {
             case 23 : case  0 :
                x_shift = 7;  break;
             case  1 :
                if (x_min < 30) x_shift = 7;  else x_shift = 0;  break;
             case  2 : case  3 :
                x_shift = 0;  break;
             case  4 :
                if (x_min < 30) x_shift = 0;  else x_shift = 1;  break;
             case  5 : case  6 :
                x_shift = 1;  break;
             case  7 :
                if (x_min < 30) x_shift = 1;  else x_shift = 2;  break;
             case  8 : case  9 :
                x_shift = 2;  break;
             case 10 :
                if (x_min < 30) x_shift = 2;  else x_shift = 3;  break;
             case 11 : case 12 :
                x_shift = 3;  break;
             case 13 :
                if (x_min < 30) x_shift = 3;  else x_shift = 4;  break;
             case 14 : case 15 :
                x_shift = 4;  break;
             case 16 :
                if (x_min < 30) x_shift = 4;  else x_shift = 5;  break;
             case 17 : case 18 :
                x_shift = 5;  break;
             case 19 :
                if (x_min < 30) x_shift = 5;  else x_shift = 6;  break;
             case 20 : case 21 :
                x_shift = 6;  break;
             case 22 :
                if (x_min < 30) x_shift = 6;  else x_shift = 7;  break;
             }
             sprintf (t, ".%d%c", x_shift, x_shifts [x_shift]);
             strcat  (x_final, t);
             break;

   }
   /*---(create)---------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   ystrlcpy  (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    number to string driver                   ----===*/
/*====================------------------------------------====================*/
static void      o___4DRIVER_________________o (void) {;}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
ystrl4main          (double a_double, char a_bytes, char a_fmt, char a_unit, char a_max, char r_out [LEN_TITLE])
{
   char        rc          = 0;
   DEBUG_YSTR   yLOG_value   ("a_bytes"   , a_bytes);
   DEBUG_YSTR   yLOG_char    ("a_fmt"     , a_fmt);
   DEBUG_YSTR   yLOG_char    ("a_fmt"     , a_unit);
   DEBUG_YSTR   yLOG_value   ("a_max"     , a_max);
   if (ystr9format (a_fmt) < 0) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_snote   ("filler bad");
      return -1;
   }
   if (ystr9decs (a_bytes) < 0) {
      ystrlcpy (r_out, "#p/dec", a_max);
      DEBUG_YSTR   yLOG_snote   ("filler bad");
      return -2;
   }
   switch (a_fmt) {
   case 'y' : case 'Y' :
      rc = ystrl4bool  (a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case 'b' : case 'B' :
      rc = ystrl4bin   (NULL    , a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case 'o' : case 'O' :
      rc = ystrl4oct   (a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case 'x' : case 'X' :
      rc = ystrl4hex   (a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case 'e' : case 'E' :
      rc = ystrl4sci   (a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case 'r' : case 'R' :
      rc = ystrl4roman (a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case 'z' : case 'Z' :
      rc = ystrl4mongo (a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case 'd' : case 't' : case 'D' : case 'T' :
      rc = ystrl4time  (a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   default :
      rc = ystrl4comma (a_double, a_bytes, a_fmt, a_unit, a_max, r_out);
      break;
   }
   /*---(complete)-----------------------*/
   return rc;
}

char*
ystrl4quick             (double a_val, char a_ali, char a_fmt, char a_cnt, char a_uom, char a_fil, char a_zer, char a_neg, char a_max)
{
   char        rc          =    0;
   char        t           [LEN_HUND]  = "";
   static char x_print     [LEN_HUND]  = "";
   if      (a_zer != ' ' && a_val == 0.0)  sprintf (t, "%c", a_zer);
   else if (a_neg != ' ' && a_val <  0.0)  sprintf (t, "%c", a_neg);
   else    rc = ystrl4main (a_val, a_cnt, a_fmt, a_uom, a_max + 1, t);
   rc = ystrlpad   (t, x_print, a_fil, a_ali, a_max);
   return x_print;
}



/*====================------------------------------------====================*/
/*===----                       bit related                            ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALIZED_____________o (void) {;}

char
ystrlbit2bin            (char *a_bits, char a_blen, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   int         i           =    0;
   char        t           [LEN_LABEL] = "";
   strcpy (r_out, "");
   for (i = 0; i < a_blen; ++i) {
      if (i > 0 )  ystrlcat (r_out, ":", a_max);
      /*> ystrl4bin (a_bits [0], 2, a_fmt, LEN_LABEL, t);                             <*/
      ystrlcat (r_out, t, a_max);
   }
   return 0;
}

/*> char                                                                                         <* 
 *> ystrlbin2bit            (char *a_src, char *r_bits, char a_blen)                  <* 
 *> {                                                                                            <* 
 *>    int         i           =    0;                                                           <* 
 *>    int         x_bits      =    0;                                                           <* 
 *>    int         x_byte      =    0;                                                           <* 
 *>    int         x_val       =    0;                                                           <* 
 *>    uchar       c           =  ' ';                                                           <* 
 *>    for (i = 0; i < x_bits; ++i) {                                                            <* 
 *>       x_val = pow (2, 15 - i);                                                               <* 
 *>       c = g_char [a_index].image [y][i];                                                     <* 
 *>       if (c == '#')  x_byte += x_val;                                                        <* 
 *>       DEBUG_YSTR    yLOG_complex ("loop"      , "%2d, %5d, %c, %5c", x, x_val, c, x_byte);   <* 
 *>    }                                                                                         <* 
 *> }                                                                                            <*/

/*> char                                                                                         <* 
 *> ystrlbin2val            (char  *a_src, double *r_val)                             <* 
 *> {                                                                                            <* 
 *>    int         x_byte      =    0;                                                           <* 
 *>    int         x_val       =    0;                                                           <* 
 *>    uchar       c           =  ' ';                                                           <* 
 *>    x_byte = 0;                                                                               <* 
 *>    for (x = 0; x < x_bits; ++x) {                                                            <* 
 *>       x_val = pow (2, 15 - x);                                                               <* 
 *>       c = g_char [a_index].image [y][x];                                                     <* 
 *>       if (c == '#')  x_byte += x_val;                                                        <* 
 *>       DEBUG_INPT    yLOG_complex ("loop"      , "%2d, %5d, %c, %5c", x, x_val, c, x_byte);   <* 
 *>    }                                                                                         <* 
 *>    ystrl4bin ((double) x_byte, 4, 'n', LEN_LABEL, t);                                        <* 
 *> }                                                                                            <*/


