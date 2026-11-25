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



tLOCAL    mySTR;





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
   ystrlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   ystrlcpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 15);
#else
   ystrlcpy (t, "[unknown    ]", 15);
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
ystr9align            (char a_align)
{
   if (a_align  == ' ')                                               return -1;
   if (a_align  ==  0 )                                               return -2;
   if (strchr ("? <|> [^] {} :'", a_align) == NULL)                   return -3;
   return 0;
}

char
ystr9filler           (char a_filler)
{
   if (a_filler == ' ')                                               return -1;
   if (a_filler ==  0 )                                               return -2;
   if (strchr ("?² !-=_.· +@~"    , a_filler) == 0)                     return -3;
   return 0;
}

char
ystr9format           (char a_format)
{
   if (a_format == ' ')                                                return -1;
   if (a_format ==  0 )                                                return -2;
   if (strchr ("? if IF, aA$ sS cC# pP eE rR bB oO xX zZ- tTdD yY", a_format) == 0) return -3;
   return 0;
}

char
ystr9decs             (int a_decs)
{
   if (a_decs < 0)  return -1;
   if (a_decs > 9)  return -2;
   return 0;
}

/*
 *    source 123456.789901
 *
 *                                            positive                                                                           negative                                      
 *       ‡€€€€€€€€€€€€€€€€€€€€‰€€€€€€€€€€€€€€€€€€€€‰€€€€€€€€€€€€€€€€€€€€‰€€€€€€€€€€€€€€€€€€€€Š€€€€€€€€€€€€€€€€€€€€‰€€€€€€€€€€€€€€€€€€€€‰€€€€€€€€€€€€€€€€€€€€‰€€€€€€€€€€€€€€€€€€€€†
 *              decs = 0            decs = 2           dec = 4              decs = 6            decs = 0            decs = 2           dec = 4              decs = 6     
 *                                                                                                                                                                       
 *  i                 123457           123457···         123457·····       123457·······             -123457          -123457···        -123457·····      -123457······· 
 *  f                 123457           123456.79         123456.7899       123456.789901             -123457          -123456.79        -123456.7899      -123456.789901 
 *                                                                                                                                                                       
 *  I                123,457          123,457···       123,457······     123,457········            -123,457         -123,457···      -123,457······    -123,457········ 
 *  F,               123,457          123,456.79       123,456.789'9     123,456.789'901            -123,457         -123,456.79      -123,456.789'9    -123,456.789'901 
 *                                                                                                                                                                       
 *  aA               123,457          123,456.79       123,456.789'9     123,456.789'901           (123,457)        (123,456.79)     (123,456.789'9)   (123,456.789'901) 
 *  $               $123,457         $123,456.79      $123,456.789'9    $123,456.789'901          $(123,457)       $(123,456.79)    $(123,456.789'9)  $(123,456.789'901) 
 *                                                                                                                                                                       
 *  sS              +123,457         +123,456.79      +123,456.789'9    +123,456.789'901            -123,457         -123,456.79      -123,456.789'9    -123,456.789'901 
 *                                                                                                                                                                       
 *  #              123,457·+        123,45679·+     123,456789'9·+   123,456789'901·+           123,457·-        123,45679·-     123,456789'9·-   123,456789'901·- 
 *                                                                                                                                                                       
 *  p                     5)               5.1·)             5.1···)           5.1·····)                 -5)              -5.1·)            -5.1···)          -5.1·····) 
 *  P                     5´               5.1·´             5.1···´           5.1·····´                 -5´              -5.1·´            -5.1···´          -5.1·····´ 
 *                                                                                                                                                                       
 *  e                   1Ë+5             1.23Ë+5          1.234'5Ë+5        1.234'567Ë+5               -1Ë+5            -1.23Ë+5         -1.234'5Ë+5       -1.234'567Ë+5 
 *  E                 +1Ë+·5           +1.23Ë+·5        +1.234'5Ë+·5      +1.234'567Ë+·5              +1Ë+·5           +1.23Ë+·5        -1.234'5Ë+·5      -1.234'567Ë+·5 
 *                                                                                                                                                                       
 *  I+K                 123K             123···K          123······K        123········K               -123K            -123···K         -123······K       -123········K 
 *  F+K                 123K             123.45K          123.456'7K        123.456'790K               -123K            -123.45K         -123.456'7K       -123.456'790K 
 *                                                                                                                                                                       
 * #                                                                                                                                                                     
 *  s=1            1··,··· +        1··,····· +    1··,········· +   1··,·········· +           1··,··· -        1··,····· -    1··,········· -   1··,·········· - 
 *  s=2            12·,··· +        12·,····· +    12·,········· +   12·,·········· +           12·,··· -        12·,····· -    12·,········· -   12·,·········· - 
 *  s=4            123,4·· +        123,4···· +    123,4········ +   123,4········· +           123,4·· -        123,4···· -    123,4········ -   123,4········· - 
 
 
 * dec=6        sigs = 0            sigs = 2           sig = 4              sigs = 6            decs = 0            decs = 2           dec = 4              decs = 6     
 *  base   1··,·········· +   12·,·········· +   123,45········ +   123,456······· + 
 *  pi           3······· +         31······ +        ·3141···· +         3141'59· + 
 *  482.6      4········· +       48········ +       4826······ +       4826······ + 
 *
 *
 *
 */

char
ystrl9output_translate  (char a_fmt, char *r_type, char *r_pre, char *r_fmt)
{
   char        rce         =  -10;
   char        x_type      =  'i';
   char        x_decs      =    0;
   char        x_fmt       =  '-';
   char        x_pre       =    0;
   --rce;  if (r_type == NULL)  return rce;
   --rce;  if (r_pre  == NULL)  return rce;
   --rce;  if (r_fmt  == NULL)  return rce;
   /*---(basics)-------------------------*/
   switch (a_fmt) {
   case '?' :
   case 'i' :  /* int  , unformatted */   x_type = 'i';  x_fmt = '-';  break;
   case 'I' :  /* int  , delimited   */   x_type = 'i';  x_fmt = 'd';  break;
   case 'f' :  /* float, unformatted */   x_type = 'f';  x_fmt = '-';  break;
   case 'F' :  /* float, delimited   */   x_type = 'f';  x_fmt = 'd';  break;
   }
   /*---(formal)-------------------------*/
   switch (a_fmt) {
   case ',' :
   case 's' :
   case 'S' :  /* comma, signed      */   x_type = 'f';  x_fmt = 'f';  break;
   case 'a' :
   case 'A' :  /* acct format        */   x_type = 'f';  x_fmt = 'g';  break;
   case '$' :  /* dollar format      */   x_type = 'f';  x_fmt = 'g';  x_pre = '$';  break;
   case '#' :  /* technical          */   x_type = 'f';  x_fmt = '#';  break;
   case 'c' :
   case 'C' :  /* comma, formatted   */   x_type = 'f';  x_fmt = '!';  break;
   }
   /*---(sci)----------------------------*/
   switch (a_fmt) {
   case 'e' :  /* sci-small          */   x_type = 's';  x_fmt = 'e';  break;
   case 'E' :  /* sci-big            */   x_type = 's';  x_fmt = 'E';  break;
   }
   /*---(bases)--------------------------*/
   switch (a_fmt) {
   case 'b' :  /* clear              */   x_type = 'b';  x_fmt = 'c';  break;
   case 'B' :  /* technical          */   x_type = 'b';  x_fmt = '#';  break;
   case 'o' :  /* clear              */   x_type = 'o';  x_fmt = 'c';  break;
   case 'O' :  /* technical          */   x_type = 'o';  x_fmt = '#';  break;
   case 'x' :  /* clear              */   x_type = 'x';  x_fmt = 'c';  break;
   case 'X' :  /* technical          */   x_type = 'x';  x_fmt = '#';  break;
   case 'z' :  /* clear              */   x_type = 'z';  x_fmt = 'c';  break;
   case 'Z' :  /* technical          */   x_type = 'Z';  x_fmt = '#';  break;
   }
   /*---(special)------------------------*/
   switch (a_fmt) {
   case 'r' :  /* lower case         */   x_type = 'r';  x_fmt = 'r';  break;
   case 'R' :  /* upper case         */   x_type = 'r';  x_fmt = 'R';  break;
   case 'p' :  /* lower case         */   x_type = 'f';  x_fmt = 'p';  break;
   case 'P' :  /* upper case         */   x_type = 'f';  x_fmt = 'P';  break;
   }
   /*---(time)---------------------------*/
   switch (a_fmt) {
   case 't' :  /* small time         */   x_type = 't';  x_fmt = 't';  break;
   case 'T' :  /* big time           */   x_type = 't';  x_fmt = 'T';  break;
   case 'd' :  /* small date         */   x_type = 't';  x_fmt = 'd';  break;
   case 'D' :  /* big date           */   x_type = 't';  x_fmt = 'D';  break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ystrl9output        (double a_double, char a_align, char a_format, char a_decs, char a_unit, char a_fill, char a_zero, char a_sigs, char a_max, char **r_out)
{
   /*> char        rc          = 0;                                                      <* 
    *> DEBUG_YSTR   yLOG_value   ("a_bytes"   , a_bytes);                                <* 
    *> DEBUG_YSTR   yLOG_char    ("a_fmt"     , a_fmt);                                  <* 
    *> DEBUG_YSTR   yLOG_char    ("a_fmt"     , a_unit);                                 <* 
    *> DEBUG_YSTR   yLOG_value   ("a_max"     , a_max);                                  <* 
    *> if (ystr9format (a_fmt) < 0) {                                                    <* 
    *>    ystrlcpy (r_out, "#p/fmt", a_max);                                             <* 
    *>    DEBUG_YSTR   yLOG_snote   ("filler bad");                                      <* 
    *>    return -1;                                                                     <* 
    *> }                                                                                 <* 
    *> if (ystr9decs (a_bytes) < 0) {                                                    <* 
    *>    ystrlcpy (r_out, "#p/dec", a_max);                                             <* 
    *>    DEBUG_YSTR   yLOG_snote   ("filler bad");                                      <* 
    *>    return -2;                                                                     <* 
    *> }                                                                                 <* 
    *> switch (tolower (a_fmt)) {                                                        <* 
    *> case 'y' : case 'Y' :                                                             <* 
    *>    rc = ystrl4bool  (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);           <* 
    *>    break;                                                                         <* 
    *> case TYPE_BIN :                                                                   <* 
    *>    rc = ystrl4bin   (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);           <* 
    *>    break;                                                                         <* 
    *> case TYPE_OCT :                                                                   <* 
    *>    rc = ystrl4oct   (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);           <* 
    *>    break;                                                                         <* 
    *> case TYPE_HEX :                                                                   <* 
    *>    rc = ystrl4hex   (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);           <* 
    *>    break;                                                                         <* 
    *> case TYPE_MONGO :                                                                 <* 
    *>    rc = ystrl4mongo (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);           <* 
    *>    break;                                                                         <* 
    *> case 'e' : case 'E' :                                                             <* 
    *>    rc = ystrl4sci   (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);           <* 
    *>    break;                                                                         <* 
    *> case TYPE_ROMAN :                                                                 <* 
    *>    rc = ystrl4roman (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);           <* 
    *>    break;                                                                         <* 
    *>    break;                                                                         <* 
    *> case 'd' : case 't' : case 'D' : case 'T' :                                       <* 
    *>    rc = ystrl4time  (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);           <* 
    *>    break;                                                                         <* 
    *> default :                                                                         <* 
    *>    rc = ystrl4comma (a_ullong, a_double, a_bytes, a_fmt, a_unit, a_max, r_out);   <* 
    *>    break;                                                                         <* 
    *> }                                                                                 <* 
    *> /+---(complete)-----------------------+/                                          <* 
    *> return rc;                                                                        <*/
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
   uchar       t           [LEN_RECD ];
   int         i           =    0;
   /*---(initialize)---------------------*/
   ystrlcpy (unit_answer, "ySTR_unit, unknown request", 100);
   /*---(string testing)-----------------*/
   if      (strncmp(a_question, "string"    , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "ySTR string      : [%s]", mySTR.strtest);
   }
   else if (strncmp(a_question, "values"    , 20)  == 0) {
      ystrlcpy (t, "", LEN_RECD);
      for (i = 0; i < 10; ++i) {
         if (mySTR.strtest [i] == 0)  break;
         sprintf (s, "%03d", (uchar) mySTR.strtest [i]);
         if (i > 0)  ystrlcat (t, " ", LEN_RECD);
         ystrlcat (t, s  , LEN_RECD);
      }
      snprintf (unit_answer, LEN_RECD, "ySTR values      : %s", t);
   }
   else if (strncmp(a_question, "work"      , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "ySTR work        : %2d[%s]", strlen (mySTR.strtest), mySTR.strtest);
   }
   /*---(argument testing)---------------*/
   else if (strncmp(a_question, "argc"      , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "ySTR argc        : %d", mySTR.argc);
   }
   else if (strncmp(a_question, "argv"      , 20)  == 0) {
      if (a_num < 20 && a_num < mySTR.argc)  {
         snprintf (unit_answer, LEN_RECD, "ySTR argv (%2d)   : %3d [%-.40s]", a_num, ystrllen (mySTR.argv[a_num], 2000), mySTR.argv[a_num]);
      } else {
         snprintf (unit_answer, LEN_RECD, "ySTR argv (%2d)   : index out of range", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


/*===[[ END ]]================================================================*/
