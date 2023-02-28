/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"

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
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_YSTR   yLOG_snote   ("null input");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce; if (x_len <= 1) {
      DEBUG_YSTR   yLOG_snote   ("too short");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (x_ch);
   x_ch = tolower (a_src [0]);
   /*> if (x_ch == 'b') {                                                             <* 
    *>    DEBUG_YSTR   yLOG_snote   ("pre=b");                                        <* 
    *>    x_min  =  1;                                                                <* 
    *> } else if (strncmp ("0b", a_src, 2) == 0) {                                    <* 
    *>    DEBUG_YSTR   yLOG_snote   ("pre=0b");                                       <* 
    *>    x_min  =  2;                                                                <* 
    *> } else if (strncmp ("0B", a_src, 2) == 0) {                                    <* 
    *>    DEBUG_YSTR   yLOG_snote   ("pre=0b");                                       <* 
    *>    x_min  =  2;                                                                <* 
    *> }                                                                              <*/
   if (x_ch == 'b') {
      DEBUG_YSTR   yLOG_snote   ("pre=b");
      x_min  =  1;
   } else if (strncmp ("0b", a_src, 2) == 0) {
      DEBUG_YSTR   yLOG_snote   ("pre=0b");
      x_min  =  2;
   } else if (strncmp ("0B", a_src, 2) == 0) {
      DEBUG_YSTR   yLOG_snote   ("pre=0B");
      x_min  =  2;
   } else if (x_ch == 'é') {
      DEBUG_YSTR   yLOG_snote   ("pre=é");
      x_min  =  1;
   }
   --rce; if (x_min <= 0) {
      DEBUG_YSTR   yLOG_snote   ("wrong prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_ch = tolower (a_src [x_min]);
   --rce; if (x_ch == '\0') {
      DEBUG_YSTR   yLOG_snote   ("only prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(run digits)---------------------*/
   DEBUG_YSTR   yLOG_sint    (x_base);
   DEBUG_YSTR   yLOG_snote   (x_valid);
   --rce;  for (i = x_len - 1; i >= x_min; --i) {
      x_ch = a_src [i];
      DEBUG_YSTR   yLOG_schar   (x_ch);
      if (strchr (x_valid, x_ch)  == 0) {
         DEBUG_YSTR   yLOG_snote   ("BOOM");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      x_digit  = x_ch - '0';
      x_final += x_digit * x_place;
      DEBUG_YSTR   yLOG_sint    (x_final);
      x_place *= x_base;
   }
   /*---(return value)-------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_YSTR   yLOG_snote   ("null input");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce; if (x_len <  2) {
      DEBUG_YSTR   yLOG_snote   ("too short");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (x_ch);
   x_ch = tolower (a_src [0]);
   /*> if (x_ch == 'o') {                                                             <* 
    *>    DEBUG_YSTR   yLOG_snote   ("pre=o");                                        <* 
    *>    x_min  =  1;                                                                <* 
    *> } else if (strncmp ("0o", a_src, 2) == 0) {                                    <* 
    *>    DEBUG_YSTR   yLOG_snote   ("pre=0o");                                       <* 
    *>    x_min  =  2;                                                                <* 
    *> } else if (x_ch == '0') {                                                      <* 
    *>    DEBUG_YSTR   yLOG_snote   ("pre=0");                                        <* 
    *>    x_min  =  1;                                                                <* 
    *> }                                                                              <*/
   if (x_ch == 'o') {
      DEBUG_YSTR   yLOG_snote   ("pre=o");
      x_min  =  1;
   } else if (x_ch == 'ö') {
      DEBUG_YSTR   yLOG_snote   ("pre=ö");
      x_min  =  1;
   } else if (x_ch == '0') {
      DEBUG_YSTR   yLOG_snote   ("pre=0");
      x_min  =  1;
   }
   --rce; if (x_min <= 0) {
      DEBUG_YSTR   yLOG_snote   ("wrong prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_ch = tolower (a_src [x_min]);
   --rce; if (x_ch == '\0') {
      DEBUG_YSTR   yLOG_snote   ("only prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(run digits)---------------------*/
   DEBUG_YSTR   yLOG_sint    (x_base);
   DEBUG_YSTR   yLOG_snote   (x_valid);
   --rce;  for (i = x_len - 1; i >= x_min; --i) {
      x_ch = a_src [i];
      DEBUG_YSTR   yLOG_schar   (x_ch);
      if (strchr (x_valid , x_ch)  == 0) {
         DEBUG_YSTR   yLOG_snote   ("BOOM");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      x_digit  = x_ch - '0';
      x_final += x_digit * x_place;
      DEBUG_YSTR   yLOG_sint    (x_final);
      x_place *= x_base;
   }
   /*---(return value)-------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   char        x_del       =  '-';
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_YSTR   yLOG_snote   ("null input");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce; if (x_len <  2) {
      DEBUG_YSTR   yLOG_snote   ("too short");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (x_ch);
   x_ch = tolower (a_src [0]);
   if (x_ch == 'x') {
      DEBUG_YSTR   yLOG_snote   ("pre=x");
      x_min  =  1;
   } else if (strncmp ("0x", a_src, 2) == 0) {
      DEBUG_YSTR   yLOG_snote   ("pre=0x");
      x_min  =  2;
   } else if (strncmp ("0X", a_src, 2) == 0) {
      DEBUG_YSTR   yLOG_snote   ("pre=0x");
      x_min  =  2;
   } else if (x_ch == 'õ') {
      DEBUG_YSTR   yLOG_snote   ("pre=õ");
      x_min  =  1;
   }
   --rce; if (x_min <= 0) {
      DEBUG_YSTR   yLOG_snote   ("wrong prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_ch = tolower (a_src [x_min]);
   --rce; if (x_ch == '\0') {
      DEBUG_YSTR   yLOG_snote   ("only prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(run digits)---------------------*/
   DEBUG_YSTR   yLOG_sint    (x_base);
   DEBUG_YSTR   yLOG_snote   (YSTR_HEX);
   --rce;  for (i = x_len - 1; i >= x_min; --i) {
      x_ch = tolower (a_src [i]);
      DEBUG_YSTR   yLOG_schar   (x_ch);
      if (x_ch == '\'' && x_del != 'y') {
         x_del = 'y';
         continue;
      }
      x_del = '-';
      if (strchr (YSTR_HEX, x_ch    )  == 0) {
         DEBUG_YSTR   yLOG_snote   ("BOOM");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (x_ch >= '0' && x_ch <= '9')   x_digit  = x_ch - '0';
      else                              x_digit  = x_ch - 'a' + 10;
      x_final += x_digit * x_place;
      DEBUG_YSTR   yLOG_sint    (x_final);
      x_place *= x_base;
   }
   /*---(return value)-------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> interpret hexadecimal numbers -----------[ petal  [ 2f---- ]*/
strl2mongor        (char *a_src, ullong *a_val, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   char        x_ch        =  '-';               /* current character         */
   int         x_min       =   -1;               /* first translatable char   */
   int         x_base      =    0;               /* base position             */
   ullong      x_digit     =    0;               /* digit value               */
   ullong      x_place     =    1;               /* base position             */
   ullong      x_final     =    0;               /* final value               */
   int         i           =    0;               /* iterator -- character     */
   char        x_del       =  '-';
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_YSTR   yLOG_snote   ("null input");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce; if (x_len <  5) {
      DEBUG_YSTR   yLOG_snote   ("too short");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (x_ch);
   x_ch = tolower (a_src [0]);
   if (x_ch == 'í') {
      DEBUG_YSTR   yLOG_snote   ("pre=í");
      x_min  =  1;
   }
   --rce; if (x_min <= 0) {
      DEBUG_YSTR   yLOG_snote   ("wrong prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_ch = a_src [x_min];
   --rce; if (x_ch == '\0') {
      DEBUG_YSTR   yLOG_snote   ("only prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(run digits)---------------------*/
   x_base = strlen (YSTR_MONGO);
   DEBUG_YSTR   yLOG_sint    (x_base);
   DEBUG_YSTR   yLOG_snote   (YSTR_HEX);
   --rce;  for (i = x_len - 1; i >= x_min; --i) {
      x_ch = a_src [i];
      DEBUG_YSTR   yLOG_schar   (x_ch);
      if (x_ch == '\'' && x_del != 'y') {
         x_del = 'y';
         continue;
      }
      x_del = '-';
      p = strchr (YSTR_MONGO, x_ch);
      if (p == NULL) {
         DEBUG_YSTR   yLOG_snote   ("BOOM");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      x_digit = p - YSTR_MONGO;
      x_final += x_digit * x_place;
      DEBUG_YSTR   yLOG_sint    (x_final);
      x_place *= x_base;
   }
   /*---(return value)-------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> interpret hexadecimal numbers -----------[ petal  [ 2f---- ]*/
strl2mongo         (char *a_src, double *a_val, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   char        x_ch        =  '-';               /* current character         */
   int         x_min       =   -1;               /* first translatable char   */
   int         x_base      =    0;               /* base position             */
   int         x_digit     =    0;               /* digit value               */
   long        x_place     =    1;               /* base position             */
   long        x_final     =    0;               /* final value               */
   int         i           =    0;               /* iterator -- character     */
   char        x_del       =  '-';
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_YSTR   yLOG_snote   ("null input");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce; if (x_len <  5) {
      DEBUG_YSTR   yLOG_snote   ("too short");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_schar   (x_ch);
   x_ch = tolower (a_src [0]);
   if (x_ch == 'í') {
      DEBUG_YSTR   yLOG_snote   ("pre=í");
      x_min  =  1;
   }
   --rce; if (x_min <= 0) {
      DEBUG_YSTR   yLOG_snote   ("wrong prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_ch = a_src [x_min];
   --rce; if (x_ch == '\0') {
      DEBUG_YSTR   yLOG_snote   ("only prefix");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(run digits)---------------------*/
   x_base = strlen (YSTR_MONGO);
   DEBUG_YSTR   yLOG_sint    (x_base);
   DEBUG_YSTR   yLOG_snote   (YSTR_HEX);
   --rce;  for (i = x_len - 1; i >= x_min; --i) {
      x_ch = a_src [i];
      DEBUG_YSTR   yLOG_schar   (x_ch);
      if (x_ch == '\'' && x_del != 'y') {
         x_del = 'y';
         continue;
      }
      x_del = '-';
      p = strchr (YSTR_MONGO, x_ch);
      if (p == NULL) {
         DEBUG_YSTR   yLOG_snote   ("BOOM");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      x_digit = p - YSTR_MONGO;
      x_final += x_digit * x_place;
      DEBUG_YSTR   yLOG_sint    (x_final);
      x_place *= x_base;
   }
   /*---(return value)-------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_src);
   --rce; if (a_src == NULL) {
      DEBUG_YSTR   yLOG_snote   ("null input");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_snote   (a_src);
   x_len = strllen (a_src, LEN_HUGE);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce; if (a_src [0] == '0' && (a_src [1] != '\0' && a_src [1] != '.')) {
      DEBUG_YSTR   yLOG_snote   ("bad leading zero");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (x_temp, a_src, LEN_HUGE);
   DEBUG_YSTR   yLOG_snote   (x_temp);
   /*---(run digits)---------------------*/
   DEBUG_YSTR   yLOG_snote   (YSTR_NUMERIC);
   --rce;  for (i = x_len - 1; i >= 0 ; --i) {
      x_curr = x_temp [i];
      DEBUG_YSTR   yLOG_schar   (x_curr);
      /*---(find exponent)---------------*/
      if (x_curr == 'Í') {
         DEBUG_YSTR   yLOG_snote   ("exp");
         if (x_exp < 0)   x_exp = i;
         else {
            DEBUG_YSTR   yLOG_snote   ("BOOM");
            DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
         continue;
      }
      /*---(find decimal)----------------*/
      if (x_curr == '.') {
         DEBUG_YSTR   yLOG_snote   ("dec");
         if (x_dec < 0)   x_dec = i;
         else {
            DEBUG_YSTR   yLOG_snote   ("BOOM");
            DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
            return rce - 1;
         }
         continue;
      }
      /*---(check rest)------------------*/
      if (strchr (YSTR_NUMERIC, x_curr)  == 0) {
         DEBUG_YSTR   yLOG_snote   ("BOOM");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce - 2;
      }
   }
   rce -= 2;
   /*---(check positions)----------------*/
   --rce;  if (x_exp > 0 && x_dec > 0 && x_exp < x_dec) {
      DEBUG_YSTR   yLOG_snote   ("BOOM");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
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
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> interpret float/int numbers -------------[ petal  [ 2g---- ]*/
strl2sci           (char *a_src, double *a_val, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =  -10;
   int         l           =    0;
   char        x_temp      [LEN_HUGE ] = "";      /* temp version              */
   int         c           =    0;
   char       *p           = NULL;
   char        x_base      [LEN_LABEL] = "";
   char        x_exp       [LEN_LABEL] = "";
   double      b           =  0.0;
   double      e           =  0.0;
   double      m           =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_point   ("a_src"     , a_src);
   --rce; if (a_src == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("a_src"     , a_src);
   l = strlen (a_src);
   DEBUG_YSTR   yLOG_value   ("l"         , l);
   --rce; if (l <  3) {
      DEBUG_YSTR   yLOG_note    ("too short");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (x_temp, a_src, LEN_HUGE);
   DEBUG_YSTR   yLOG_info    ("x_temp"    , x_temp);
   /*---(divide)-------------------------*/
   c = strldcnt (x_temp, 'Ë', LEN_HUGE);
   DEBUG_YSTR   yLOG_value   ("c"         , c);
   --rce; if (c != 1) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   p = strchr (x_temp, 'Ë');
   DEBUG_YSTR   yLOG_point   ("p"         , p);
   --rce; if (p == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   p [0] = '\0';
   ++p;
   strlcpy (x_base, x_temp, LEN_LABEL);
   DEBUG_YSTR   yLOG_info    ("x_base"    , x_base);
   strlcpy (x_exp , p     , LEN_LABEL);
   DEBUG_YSTR   yLOG_info    ("x_exp"     , x_exp);
   /*---(process base)-------------------*/
   DEBUG_YSTR   yLOG_note    ("process base");
   l = strlen (x_base);
   DEBUG_YSTR   yLOG_value   ("l"         , l);
   --rce; if (l <  1) {
      DEBUG_YSTR   yLOG_note    ("too short");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = strl2real (x_base, &b, LEN_LABEL);
   DEBUG_YSTR   yLOG_value   ("strl2real" , rc);
   --rce; if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(process exponent)---------------*/
   DEBUG_YSTR   yLOG_note    ("process exponent");
   l = strlen (x_base);
   DEBUG_YSTR   yLOG_value   ("l"         , l);
   --rce; if (l <  1) {
      DEBUG_YSTR   yLOG_note    ("too short");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_value   ("l"         , l);
   for (i = 0; i < l; ++i) {
      if (strchr ("0123456789+-", x_exp [i]) != NULL)  continue;
      DEBUG_YSTR   yLOG_complex ("badchar"   , "%2d, %3d, %c", i, x_exp [i], x_exp [i]);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = strl2real (x_exp , &e, LEN_LABEL);
   DEBUG_YSTR   yLOG_value   ("strl2real" , rc);
   --rce; if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(merge)--------------------------*/
   m = 1;
   if (e >= 0)  { for (i = 0; i < e; ++i)   m *= 10; }
   else         { for (i = 0; i > e; --i)   m /= 10; }
   /*---(return value)-------------------*/
   DEBUG_YSTR   yLOG_snote   ("assigning");
   if (a_val != NULL)  *a_val = b * m;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ystr__prefix       (cchar *a_src, char *a_out)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   int         c           =    0;
   int         d           =    0;
   int         i, j;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(strip prefixes)-----------------*/
   if (a_src [0]  == '$')  strlcpy (a_out, a_src + 1, LEN_RECD);
   else                    strlcpy (a_out, a_src    , LEN_RECD);
   /*---(convert signs)------------------*/
   if (a_out [0] == '(')    a_out [0] = '-';
   /*---(prepare)------------------------*/
   DEBUG_YSTR   yLOG_info    ("a_out"     , a_out);
   x_len  = strlen (a_out);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   /*---(walk digits)--------------------*/
   --rce;  for (i = x_len - 4; i > 0; i -= 4) {
      /*--(filter)-----------------------*/
      DEBUG_YSTR   yLOG_complex ("del check" , "%2dl, %2di, %s, %c", x_len, i, a_out, a_out [i]);
      ++d;
      if (a_out [i] != ',')  continue;
      /*--(remove)-----------------------*/
      for (j = i; j <= x_len; ++j)  a_out [j] = a_out [j + 1];
      --x_len;
      ++c;
      DEBUG_YSTR   yLOG_complex ("updated"   , "%2d[%s]", x_len, a_out);
      /*--(done)-------------------------*/
   }
   /*---(check)--------------------------*/
   DEBUG_YSTR   yLOG_complex ("counts"    , "%dd, %dc", d, c);
   --rce;  if (c > 0 && d != c) {
      strlcpy (a_out, "0", LEN_RECD);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*--(bad characters)---------------*/
   --rce;  for (i = 0; i < x_len; ++i) {
      DEBUG_YSTR   yLOG_complex ("char check", "%2dl, %2di, %s, %c", x_len, i, a_out, a_out [i]);
      if      (x_len == 1 && a_out [i] == '0')                        continue;
      else if (i == 0 && strchr ("-+123456789", a_out [i]) != NULL)   continue;
      else if (i >  0 && strchr ("1234567890" , a_out [i]) != NULL)   continue;
      strlcpy (a_out, "0", LEN_RECD);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ystr__suffix       (cchar *a_src, char *a_out)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   int         c           =    0;
   int         d           =    0;
   int         i, j;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   strlcpy (a_out, a_src, LEN_RECD);
   DEBUG_YSTR   yLOG_info    ("a_out"     , a_out);
   x_len  = strlen (a_out);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   /*---(strip suffixes)-----------------*/
   if (a_out [x_len - 1] == ')')  a_out [x_len - 1] = '\0';
   /*---(walk digits)--------------------*/
   --rce;  for (i = 3; i < x_len; i += 3) {
      /*--(filter)-----------------------*/
      DEBUG_YSTR   yLOG_complex ("del check" , "%2dl, %2di, %s, %c", x_len, i, a_out, a_out [i]);
      ++d;
      if (a_out [i] != '\'')  continue;
      /*--(remove)-----------------------*/
      for (j = i; j <= x_len; ++j)  a_out [j] = a_out [j + 1];
      --x_len;
      ++c;
      DEBUG_YSTR   yLOG_complex ("updated"   , "%2d[%s]", x_len, a_out);
      /*--(done)-------------------------*/
   }
   /*---(check)--------------------------*/
   DEBUG_YSTR   yLOG_complex ("counts"    , "%dd, %dc", d, c);
   --rce;  if (c > 0 && d != c) {
      strlcpy (a_out, "0", LEN_RECD);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*--(bad characters)---------------*/
   --rce;  for (i = 0; i < x_len; ++i) {
      DEBUG_YSTR   yLOG_complex ("char check", "%2dl, %2di, %s, %c", x_len, i, a_out, a_out [i]);
      if (strchr ("1234567890" , a_out [i]) != NULL)   continue;
      strlcpy (a_out, "0", LEN_RECD);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
strl2comma         (cchar *a_src, double *a_val, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   char       *x_dec       = NULL;
   char        x_pre1      [LEN_RECD]  = "";
   char        x_pre2      [LEN_RECD]  = "";
   char        x_suf1      [LEN_RECD]  = "";
   char        x_suf2      [LEN_RECD]  = "";
   char        x_result    [LEN_RECD]  = "";
   int         x_places    =    0;
   int         l           =    0;
   char        x_sign      =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_val != NULL)  *a_val = 0.0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("a_src"     , a_src);
   /*---(find decimal)-------------------*/
   x_dec  = strchr (a_src, '.');
   DEBUG_YSTR   yLOG_point   ("x_dec"     , x_dec);
   /*---(check trailing sign)------------*/
   l  = strlen (a_src);
   DEBUG_YSTR   yLOG_value   ("l"         , l);
   if (l >= 3) {
      DEBUG_YSTR   yLOG_char    ("l - 2"     , a_src [l - 2]);
      DEBUG_YSTR   yLOG_char    ("l - 1"     , a_src [l - 1]);
      if (a_src [l - 2] == ' ' && strchr ("+-", a_src [l - 1]) != NULL) {
         switch (a_src [l - 1]) {
         case '+' : x_sign = +1;  break;
         case '-' : x_sign = -1;  break;
         }
      }
   }
   /*---(prepare parts)------------------*/
   if (x_dec == NULL) {
      strlcpy (x_pre1, a_src, LEN_RECD);
   } else {
      x_places  = x_dec - a_src + 1;
      DEBUG_YSTR   yLOG_point   ("x_places"  , x_places);
      strlcpy (x_pre1, a_src, x_places);
      strlcpy (x_suf1, x_dec + 1, LEN_RECD);
      l = strlen (x_suf1);
      if (x_sign != 0)  x_suf1 [l - 2] = '\0';
   }
   DEBUG_YSTR   yLOG_info    ("x_pre1"    , x_pre1);
   DEBUG_YSTR   yLOG_info    ("x_suf1"    , x_suf1);
   /*---(process prefix)-----------------*/
   rc = ystr__prefix (x_pre1, x_pre2);
   DEBUG_YSTR   yLOG_value   ("prefix"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("x_pre2"    , x_pre2);
   strlcpy (x_result, x_pre2, LEN_RECD);
   /*---(process suffix)-----------------*/
   if (x_dec != NULL) {
      rc = ystr__suffix (x_suf1, x_suf2);
      DEBUG_YSTR   yLOG_value   ("suffix"    , rc);
      --rce;  if (rc < 0) {
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_YSTR   yLOG_info    ("x_suf2"    , x_suf2);
      sprintf (x_result, "%s.%s", x_pre2, x_suf2);
   }
   /*---(save back)----------------------*/
   if (x_sign == 0)  x_sign = 1;
   if (a_val != NULL)  *a_val = atof (x_result) * x_sign;;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> check string for numeric value ----------[ petal  [ 2g---- ]*/
strl2num           (char *a_src, double *a_val, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   double      x_value     =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_value   ("a_src [0]" , a_src [0]);
   DEBUG_YSTR   yLOG_info    ("valid"     , YSTR_NUMERIC);
   --rce;  if (a_src [0] == 0 || strchr ("éõöí" YSTR_NUMERIC "$()", a_src [0]) == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_len = strllen (a_src, a_max);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   /*---(oct, bin, hex)------------------*/
   DEBUG_YSTR   yLOG_value   ("a_src [1]" , a_src [1]);
   if (x_len > 1) {
      switch (a_src [0]) {
      case 'é':
         DEBUG_YSTR   yLOG_note    ("binary");
         rc = strl2bin   (a_src, &x_value, a_max);
         break;
      case 'ö':
         DEBUG_YSTR   yLOG_note    ("octal");
         rc = strl2oct   (a_src, &x_value, a_max);
         break;
      case 'õ':
         DEBUG_YSTR   yLOG_note    ("hexadecimal");
         rc = strl2hex   (a_src, &x_value, a_max);
         break;
      case 'í':
         DEBUG_YSTR   yLOG_note    ("mongo");
         rc = strl2mongo (a_src, &x_value, a_max);
         break;
      }
   }
   /*---(scientific)---------------------*/
   if (rc < 0 && strchr (a_src, 'Ë') != NULL) {
      DEBUG_YSTR   yLOG_note    ("scientific notation");
      rc = strl2sci (a_src, &x_value, a_max);
   }
   /*---(commma)-------------------------*/
   if (rc < 0 && strchr (a_src, ',') != NULL) {
      DEBUG_YSTR   yLOG_note    ("comma notation");
      rc = strl2comma (a_src, &x_value, a_max);
   }
   /*---(float, int)---------------------*/
   if (rc < 0) {
      DEBUG_YSTR   yLOG_note    ("float/int");
      rc = strl2real (a_src, &x_value, a_max);
   }
   /*---(save result)--------------------*/
   DEBUG_YSTR   yLOG_value   ("rc"        , rc);
   if (rc >= 0) {
      DEBUG_YSTR   yLOG_double  ("x_value"   , x_value);
      if (a_val != NULL)  *a_val = x_value;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return rc;
}


/*====================------------------------------------====================*/
/*===----                     strings from numerics                    ----===*/
/*====================------------------------------------====================*/
static void      o___FORMATTING______________o (void) {;}

char
ystr__units          (double *a_value, char a_unit)
{
   double      x_scale     =  0.0;
   char       *x_valid     = "-YZEPTGMKHD.dcmunpfazy";
   /*---(defense)------------------------*/
   if (a_value == NULL)    return -1;
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
   *a_value /= x_scale;
   /*---(complete)-----------------------*/
   return 0;
}

ystr__space_ints     (char *a_out, int a_count, char a_char)
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

ystr__space_decs     (char *a_out, int a_cnt, char a_char)
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
   ystr__space_ints     (a_out, a_cnt, a_char);
   /*> printf ("a_out = %s\n", a_out);                                                <*/
   x_len = strlen (a_out);
   for (i = 0; i < x_add; ++i)  a_out [--x_len] = '\0';
   /*> printf ("a_out = %s\n", a_out);                                                <*/
   return 0;
}

char
strl4bool          (double a_val, char *a_out, int a_nibs, char a_fmt, int a_max)
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
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("yY"    , a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   /*---(any binary)-----------*/
   if (a_val == 0) {
      switch (a_fmt) {
      case 'Y' :   strlcpy  (a_out, "Ú", a_max);    break;
      case 'y' :   strlcpy  (a_out, "·", a_max);    break;
      }
   } else if (a_val < 0) {
      switch (a_fmt) {
      case 'Y' :   strlcpy  (a_out, "Û", a_max);    break;
      case 'y' :   strlcpy  (a_out, "t", a_max);    break;
      }
   } else {
      switch (a_fmt) {
      case 'Y' :   strlcpy  (a_out, "Û", a_max);    break;
      case 'y' :   strlcpy  (a_out, "T", a_max);    break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("bBnq:s", a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
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
   if (strchr ("bB", a_fmt) != NULL)     strcat (x_temp, "é");
   /*---(flip)-----------------*/
   x_len = strlen (x_temp) - 1;
   for (i = x_len; i >= 0; --i) x_final [x_len - i] = x_temp[i];
   /*---(delimit)--------------*/
   switch (a_fmt) {
   case 'B' :  case 'q' :  ystr__space_ints (x_final, 4, '\'');   break;
   case ':' :              ystr__space_ints (x_final, 4, ':');    break;
   case 's' :              ystr__space_ints (x_final, 4, ' ');    break;
   case 'b' :  case 'n' :  break;
   }
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("oOzZnq:s", a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#p/neg", a_max);
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
   case 'Z' :  case 'q' :  ystr__space_ints (x_final, 3, '\'');   break;
   case ':' :              ystr__space_ints (x_final, 3, ':');    break;
   case 's' :              ystr__space_ints (x_final, 3, ' ');    break;
   case 'o' :  case 'n' :  break;
   }
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("xXUDqQnN:sS", a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#p/neg", a_max);
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
   if (strchr ("XDqQ"  , a_fmt) != 0)   ystr__space_ints (x_final, 2, '\'');
   if (strchr ("sS"    , a_fmt) != 0)   ystr__space_ints (x_final, 2, ' ');
   if (strchr (":"     , a_fmt) != 0)   ystr__space_ints (x_final, 2, ':');
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
strl4comma         (double a_val, char *a_out, int a_decs, char a_fmt, char a_unit, int a_max)
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
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("iIfF,cCaAsS$#pP?", a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }

   if (a_val < 0.0)    x_sign  = -1;
   if (a_fmt == '?')   a_fmt   = 'i';
   if (a_fmt == 'i')   a_decs  =  0;
   /*---(scale)--------------------------*/
   x_scaled = a_val;
   rc = ystr__units (&x_scaled, a_unit);
   --rce;  if (rc < 0) {
      strlcpy (a_out, "#p/uni", a_max);
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
   if (strchr ("iIf", a_fmt) == NULL)  ystr__space_ints (x_temp, 3, ',');
   strcat (x_final, x_temp);
   DEBUG_YSTR  yLOG_snote    (x_temp);
   /*---(decimal part)-------------------*/
   if (strchr ("iI", a_fmt) == 0 && a_decs > 0) {
      sprintf (x_temp, "%0*lld", a_decs, x_frac);
      if (strchr ("ACS#F", a_fmt) != NULL)  ystr__space_decs (x_temp, 3, '\'');
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
      strlcpy (a_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   if (a_val < 0.0)  x_sign  = -1;
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("eE", a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
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
   if (a_fmt == 'E' && a_decs > 3)  ystr__space_decs (x_prefix, 3, '\'');
   /*---(contat)----------------------*/
   strcat  (x_final, x_prefix);
   /*> if (a_fmt == 'E')  strcat  (x_final, " ");                                     <*/
   strcat  (x_final, x_suffix);
   /*---(create)---------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strldchg (x_final, 'e', 'Ë', a_max);
   strldchg (x_final, 'E', 'Ë', a_max);
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("rR", a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_val > 4000) {
      strlcpy (a_out, "#p/big", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_int = (int) a_val;
   if (x_int == 0) {
      if (a_fmt == 'r')  strcpy (a_out, "o");
      else               strcpy (a_out, "O");
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
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (a_fmt == 'r') {
      for (i = 0; i < x_len; ++i)  x_final [i] = tolower (x_final [i]);
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
strl4mongor        (ullong a_val, char *a_out, int a_cnt, char a_fmt, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;               /* return code for errors    */
   int         x_len       =    0;
   int         i           =    0;               /* iterator -- character     */
   char        x_temp      [200] = "";
   char        x_final     [200] = "";
   ullong      x_int       =    0;
   ullong      x_digit     =    0;
   ullong      x_place     =    0;
   int         x_inc       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("zZnqs:", a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#p/neg", a_max);
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
   if (strchr ("zZ", a_fmt) != NULL)    strcat (x_temp, "í");
   /*---(flip)-----------------*/
   x_len = strlen (x_temp) - 1;
   for (i = x_len; i >= 0; --i) x_final [x_len - i] = x_temp[i];
   /*---(delimit)--------------*/
   if (strchr ("Zq"    , a_fmt) != 0)   ystr__space_ints (x_final, 4, '\'');
   if (strchr ("s"     , a_fmt) != 0)   ystr__space_ints (x_final, 4, ' ');
   if (strchr (":"     , a_fmt) != 0)   ystr__space_ints (x_final, 4, ':');
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   long        x_int       =    0;
   int         x_digit     =    0;
   long        x_place     =    0;
   int         x_inc       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("zZnqs:", a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#p/neg", a_max);
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
   if (strchr ("zZ", a_fmt) != NULL)    strcat (x_temp, "í");
   /*---(flip)-----------------*/
   x_len = strlen (x_temp) - 1;
   for (i = x_len; i >= 0; --i) x_final [x_len - i] = x_temp[i];
   /*---(delimit)--------------*/
   if (strchr ("Zq"    , a_fmt) != 0)   ystr__space_ints (x_final, 4, '\'');
   if (strchr ("s"     , a_fmt) != 0)   ystr__space_ints (x_final, 4, ' ');
   if (strchr (":"     , a_fmt) != 0)   ystr__space_ints (x_final, 4, ':');
   /*---(check)----------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defence)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_snote   ("a_out null");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out, YSTR_EMPTY, a_max);
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("tTdD", a_fmt) == NULL) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_snote   ("format invalid");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_sint    (a_val);
   --rce;  if (a_val < 0) {
      strlcpy (a_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_snote   ("epoch number negative");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
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
   DEBUG_YSTR   yLOG_sint    (a_max);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len > a_max) {
      strlcpy (a_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_snote   ("too long");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (a_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
strl4main          (double a_val, char *a_out, int a_bytes, char a_fmt, char a_unit, int a_max)
{
   char        rc          = 0;
   DEBUG_YSTR   yLOG_value   ("a_bytes"   , a_bytes);
   DEBUG_YSTR   yLOG_char    ("a_fmt"     , a_fmt);
   DEBUG_YSTR   yLOG_char    ("a_fmt"     , a_unit);
   DEBUG_YSTR   yLOG_value   ("a_max"     , a_max);
   if (str9format (a_fmt) < 0) {
      strlcpy (a_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_snote   ("filler bad");
      return -1;
   }
   if (str9decs (a_bytes) < 0) {
      strlcpy (a_out, "#p/dec", a_max);
      DEBUG_YSTR   yLOG_snote   ("filler bad");
      return -2;
   }
   switch (a_fmt) {
   case 'y' : case 'Y' :
      rc = strl4bool  (a_val, a_out, a_bytes, a_fmt, a_max);
      break;
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
      rc = strl4comma (a_val, a_out, a_bytes, a_fmt, a_unit, a_max);
      break;
   }
   /*---(complete)-----------------------*/
   return rc;
}
