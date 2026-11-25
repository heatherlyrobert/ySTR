/*============================[[    beg-code    ]]============================*/
/*∑∑∑∑∑∑∑∑¥ ¥∑∑∑∑∑∑∑∑∑∑∑∑∑headers∑¥ ¥∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑*/
#include    "ySTR.h"
#include    "ySTR_priv.h"
/*∑∑∑∑∑∑∑∑¥ ¥∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑¥ ¥∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑*/



/*===[[ BEG GNU GENERAL PUBLIC LICENSE (GPL) WARNING ]]=======================*/
/*>>∑∑∑∑∑∑∑∑∑1∑∑∑∑∑∑∑∑∑2∑∑∑∑∑∑∑∑∑3∑∑∑∑∑∑∑∑∑4∑∑∑∑∑∑∑∑∑5∑∑∑∑∑∑∑∑∑6∑∑∑∑∑∑∑∑∑7∑∑∑∑+∑∑∑∑8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2013 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¶"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¶"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¶" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¶"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might¶"    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*>>∑∑∑∑∑∑∑∑∑1∑∑∑∑∑∑∑∑∑2∑∑∑∑∑∑∑∑∑3∑∑∑∑∑∑∑∑∑4∑∑∑∑∑∑∑∑∑5∑∑∑∑∑∑∑∑∑6∑∑∑∑∑∑∑∑∑7∑∑∑∑+∑∑∑∑8  */
/*===[[ END GNU GENERAL PUBLIC LICENSE (GPL) WARNING ]]=======================*/



/*>>∑∑∑∑∑∑∑∑∑1∑∑∑∑∑∑∑∑∑2∑∑∑∑∑∑∑∑∑3∑∑∑∑∑∑∑∑∑4∑∑∑∑∑∑∑∑∑5∑∑∑∑∑∑∑∑∑6∑∑∑∑∑∑∑∑∑7∑∑∑∑+∑∑∑∑8  */
#define  P_OBJECTIVE   \
   "ySTR_formats.c is focused on translating machine numbers to-and-from¶"       \
   "various human-consumable formats, such as, bin, oct, hex, comma, and sci¶"   \
   "to allow quicker and better communication, as well as data maintenance."

/*
 * if you want a number translated correctly, add a greek prefix.  if you
 * can not, add a zero-prefixed letter one.  for reals, make sure a  sign,
 * plus or minus, appears first to make it obvious.
 *
 *    ---best----- ---good----- ---decent--- --pedantic-- ---chance---
 *    È'11010110   È11010110    b11010110    0b11010110   11010110
 *    ˆ'755        ˆ755         o755         0o755        0755
 *    ı'af86       ıaf86        xaf86        0xaf86       af86
 *    Ì'Fmu5       ÌFmu5        zFmu5        0zFmu5       Fmu5
 *    +1234                                               1234
 *
 *
 */

/*
 *   ySTR_format is all about human-consumable numbers for use on displays,
 *   for reports, and in ascii-text data files.
 *
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
 *
 *
 *   bit?    á≥≥≤≥Å≤≥≥≥ä≤≥≥≤Å≤≤≥≥Ü á≥≥≤≥Å≤≥≥≥ä≥≥≤≥Å≤≤≥≥Ü á≥≥≤≥Å≤≥≥≥ä≤≥≥≤Å≤≤≥≥Ü á≥≥≤≥Å≤≥≥≥ä≥≤≥≥Å≥≤≥≤Ü
 *
 *   bit?    ≥≥≤≥/≤≥≥≥/≤≥≥≤/≤≤≥≥/≥≥≤≥/≤≥≥≥/≥≥≤≥/≤≤≥≥/≥≥≤≥/≤≥≥≥/≤≥≥≤/≤≤≥≥/≥≥≤≥/≤≥≥≥/≥≤≥≥/≥≤≥≤
 *
 *   bit?    Å≥≥≤≥å≤≥≥≥Å≤≥≥≤å≤≤≥≥Å≥≥≤≥å≤≥≥≥Å≥≥≤≥å≤≤≥≥Å≥≥≤≥å≤≥≥≥Å≤≥≥≤å≤≤≥≥Å≥≥≤≥å≤≥≥≥Å≥≤≥≥å≥≤≥≤Å
 *
 *   bit?    ≥≥-≥ -≥≥≥ -≥≥- --≥≥
 *
 *   bit?    @@-@ -@@@ -@@- --@@
 *
 *   bit?    ##-# -### -##- --##
 *
 *   bit?    ¥¥≤¥ ≤¥¥¥ ≤¥¥≤ ≤≤¥¥
 *
 *   bit?    ··Ä· Ä··· Ä··Ä ÄÄ··
 */

/*
 *
 *   123,456,789.123 +
 *   123,456,789.123 -
 *   123,456,789.123+
 *   123,456,789.123-
 *
 *
 *   123,456,789∑-
 *   ∑∑∑∑456,789∑+
 *   ∑∑3,456,789
 *   ∑∑∑∑∑∑6,789
 */

/*
 *
 *
 *   a_max       5           15                       20
 *             ∑∑∑∑∑   ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑       ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑       ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑
 *   plain         5              1275                123,456,789               123,456,789 
 *   signed       -5             -1275               -123,456,789              (123,456,789)
 *   signed       +5             +1275               +123,456,789               123,456,789 
 *             ∑∑∑∑∑   ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑       ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑
 *   commas        5             1,275                123,456,789
 *                -5            -1,275               -123,456,789
 *                +5            +1,275               +123,456,789
 *             ∑∑∑∑∑   ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑       ∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑
 *   tech +      5∑+           1,275∑+              123,456,789∑+
 *   tech -      5∑-           1,275∑-              123,456,789∑-
 *
 *   - simple          123456789
 *   b  del
 *
 *
 */


/*
 *     ------a_max=20------
 *     +∑∑13,279Å631'452∑∑
 *     ∑∑∑13,279Å631'452∑+
 *
 *     ------a_max=21------
 *     ∑3,145,279Å63∑∑∑∑∑∑+
 *     ∑∑∑∑∑3,145Å279'63∑∑-
 *     ∑∑∑∑∑∑∑∑∑3Å145'279∑+
 *     ∑∑∑∑∑∑∑∑27Å∑∑∑∑∑∑∑∑+
 *
 *
 */


/*
 *     999,999,999,999,999          1110·0011·0101·1111·0101·1101·1001·0011
 *
 *
 *    0000·0011∑∑1000·1101∑∑0111·1110∑∑1010·0100∑∑1100·0110∑∑0111·1111∑∑1111·1111
 */

/*
 * --format-code- --binary----  --octal-----  --hex-------  --mongo-----   ----integer-----   ----float-------
 *   -    none    11010011      131366        a59eba51      k3VLqsLtn      123456789          123456789.0     
 *   d    dels    1101'0011     131'366       a59e'ba51     k3VL'qsLtn     123,456,789        123,456,789.0   
 *   s    simple  0b11010011    0o131366      0xa59eba51    0zk3VLqsLtn    +123456789         +123456789.0    
 *   f    formal  È11010011     ˆ131366       ıa59eba51     ˇk3VLqsLtn     +123,456,789       +123,456,789.0  
 *   c    clear   b'1101'0011   o'131'366     x'a59e'ba51   z'k3VL'qsLtn   +123,456,789       +123,456,789    
 *   g    greek   È'1101'0011   ˆ'131'366     ı'a59e'ba51   ˇ'k3VL'qsLtn   (123,456,789)      (123,456,789.0) 
 *   :    colon   È:1101:0011   ˆ:131:366     ı:a59e:ba51   ˇ:k3VL:qsLtn   +123,456,789       +123,456,789.0  
 *   t    tick    È·1101·0011   ˆ·131·366     ı·a59e·ba51   ˇ·k3VL·qsLtn   +123,456,789       +123,456,789.0  
 *   #    tech    È·11∑1·∑∑11   ˆ·131·366     ı·a59e·ba51   ˇ·k3VL·qsLtn   123,456,789∑+      123,456,789.0∑+   
 * 
 *
 * ystrl4comma         (ullong a_ullong, double a_double, char a_decs, char a_fmt, char a_unit, char a_max, char r_out [LEN_TITLE])
 *
 *                                                                      123456789-123456789-123456789
 *                                                            none      ∑∑∑∑∑∑∑∑∑18446744073709551615
 *                                                            dels      ∑∑∑18,446,744,073,709,551,615
 *                                                            simple    ∑∑∑∑∑∑∑∑+18446744073709551615
 *                                                            formal    ∑∑+18,446,744,073,709,551,615
 *                                                            greek     ∑(18,446,744,073,709,551,615)
 *                                                 colon,tick,clear     +∑∑18,446,744,073,709,551,615
 *                                                            tech      ∑18,446,744,073,709,551,615∑+
 *
 *
 *
 *        1001110110001010
 *        1∑∑111∑11∑∑∑1∑1∑
 *        ≥∑∑≥≥≥∑≥≥∑∑∑≥∑≥∑
 *        œ∑∑œœœ∑œœ∑∑∑œ∑œ∑
 *
 *        1001 1101  1000 1010  1001 1101  1000 1010
 *        1∑∑1 11∑1  1∑∑∑ 1∑1∑  1∑∑1 11∑1  1∑∑∑ 1∑1∑
 *        ≥∑∑≥ ≥≥∑≥  ≥∑∑∑ ≥∑≥∑  ≥∑∑≥ ≥≥∑≥  ≥∑∑∑ ≥∑≥∑
 *        ≥--≥ ≥≥-≥ä≥--- ≥-≥-  ≥--≥ ≥≥-≥  ≥--- ≥-≥-
 *        œ∑∑œ œœ∑œ  œ∑∑∑ œ∑œ∑  œ∑∑œ œœ∑œ  œ∑∑∑ œ∑œ∑
 *
 *       Å≥∑∑≥å≥≥∑≥Å≥∑∑∑å≥∑≥∑Å≥∑∑≥å≥≥∑≥Å≥∑∑∑å≥∑≥∑Å
 *
 * 
 */

/*> static char s_numeric     [20] = "0123456789.-+";    /+ only digits               +/   <*/
/*> static char s_empty       [200] = "                                                                                                                                                                                                       ";   <*/


/*===[[ METIS ]]==============================================================*/
/*
 * metis  ww2∑∑  convert comma representation back to real number
 * metis  ww1∑∑  convert dollar and other misc in uncomma conversion
 *
 *
 *
 */

/*
 *  doubles can only reliably, precisely handle 15 digits,
 *  so i limit my integer formats to 15 digits as well
 */

#define    TYPE_BIN    'b'
#define    TYPE_OCT    'o'
#define    TYPE_INT    'i'
#define    TYPE_HEX    'x'
#define    TYPE_MAYAN  ''
#define    TYPE_MONGO  'z'
#define    TYPE_ROMAN  'r'
#define    TYPE_FLOAT  'f'
#define    TYPE_SCI    'e'
#define    TYPE_TIME   't'
#define    TYPE_DATE   'd'
#define    TYPE_FAIL   '∞'

#define    TYPE_BASES  "boxz"
#define    TYPE_NORMS  "+-($"



static struct {  /* roman numerals classically only went 1 - 3999 */
   char        r_chars     [LEN_SHORT];
   char        r_wide;
   int         r_value;
} const S_roman [LEN_DESC] = {
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
   { "end-of", 0 ,     0 },
};


/*
 *  my symbols are almost exactly the international standard, but
 *  all greater/positive scales are upper-case, adn all 
 *  lesser/negative scales are lower-case.
 */

static struct {
   char        u_char;                    /* symbol of unit       */
   char        u_pow;                     /* power                */
   double      u_scale;                   /* multiplier           */
   char        u_name      [LEN_TERSE];   /* prefix               */
   char        u_sci       [LEN_SHORT];   /* scientific notation  */
   char        u_english   [LEN_LABEL];   /* scientific notation  */
} const S_scale [LEN_TITLE] = {
   /*---   pow   ---scale---------------------   --name--   -sci-   ----english---- */
   { '-' ,   0 ,  1.0                          , "def"   , "----" , ""              },
   /*---   pow   ---scale---------------------   --name--   -sci-   ----english---- */
   { 'Y' , +24 ,  1000000000000000000000000.0  , "yotta" , "À+24" , "septillion"    },
   { 'Z' , +21 ,  1000000000000000000000.0     , "zetta" , "À+21" , "sextillion"    },
   { 'E' , +18 ,  1000000000000000000.0        , "exa"   , "À+18" , "quintillion"   },
   { 'P' , +15 ,  1000000000000000.0           , "peta"  , "À+15" , "quadrillion"   },
   { 'T' , +12 ,  1000000000000.0              , "tera"  , "À+12" , "trillion"      },
   { 'G' ,  +9 ,  1000000000.0                 , "giga"  , "À+09" , "billion"       },
   { 'M' ,  +6 ,  1000000.0                    , "mega"  , "À+06" , "million"       },
   { 'K' ,  +3 ,  1000.0                       , "kilo"  , "À+03" , "thousand"      },
   { 'H' ,  +2 ,  100.0                        , "hecto" , "À+02" , "hundred"       },
   { 'D' ,  +1 ,  10.0                         , "deca"  , "À+01" , "ten"           },
   /*---   pow   ---scale---------------------   --name--   -sci-   ----english---- */
   { '.' ,   0 ,  1.0                          , ""      , "----" , ""              },
   /*---   pow   ---scale---------------------   --name--   -sci-   ----english---- */
   { 'd' ,  -1 ,  0.1                          , "deci"  , "À-01" , "tenth"         },
   { 'c' ,  -2 ,  0.01                         , "centa" , "À-02" , "hundredth"     },
   { 'm' ,  -3 ,  0.001                        , "milli" , "À-03" , "thousandth"    },
   { 'u' ,  -6 ,  0.000001                     , "micro" , "À-06" , "millionth"     },
   { 'n' ,  -9 ,  0.000000001                  , "nano"  , "À-09" , "billionth"     },
   { 'p' , -12 ,  0.000000000001               , "pico"  , "À-12" , "trillionth"    },
   { 'f' , -15 ,  0.000000000000001            , "femto" , "À-15" , "quadrillionth" },
   { 'a' , -18 ,  0.000000000000000001         , "atto"  , "À-18" , "quintillionth" },
   { 'z' , -21 ,  0.000000000000000000001      , "zepto" , "À-21" , "sextillionth"  },
   { 'y' , -24 ,  0.000000000000000000000001   , "yocto" , "À-24" , "septillionth"  },
   /*---   pow   ---scale---------------------   --name--   -sci-   ----english---- */
   {  0  ,   0 ,  0.0                          , ""      , ""     , ""              },
   /*---   pow   ---scale---------------------   --name--   -sci-   ----english---- */
};



/*====================------------------------------------====================*/
/*===----                 support for units                            ----===*/
/*====================------------------------------------====================*/
static void      o___UNITS___________________o (void) {;}

char
ystr_units              (char a_dir, char a_unit, double *b_value, char *r_pow, double *r_scale, char r_name [LEN_TERSE], char r_sci [LEN_SHORT], char r_english [LEN_LABEL])
{
   /*---(locals)-----------+-----------+-*/
   int         i           =    0;
   char       *x_valid     = "-YZEPTGMKHD.dcmunpfazy";
   /*---(default)------------------------*/
   if (r_pow     != NULL)  *r_pow    = 0;
   if (r_scale   != NULL)  *r_scale  = 0.0;
   if (r_name    != NULL)  strcpy (r_name   , "");
   if (r_sci     != NULL)  strcpy (r_sci    , "");
   if (r_english != NULL)  strcpy (r_english, "");
   /*---(units up)-----------------------*/
   for (i = 0; i < LEN_TITLE; ++i) {
      /*---(filter)----------------------*/
      if (S_scale [i].u_char == 0)       break;
      if (S_scale [i].u_char != a_unit)  continue;
      /*---(handle)----------------------*/
      if (b_value   != NULL) {
         if (a_dir == '>')  *b_value /= S_scale [i].u_scale;
         if (a_dir == '<')  *b_value *= S_scale [i].u_scale;
      }
      /*---(return data)-----------------*/
      if (r_pow     != NULL)  *r_pow    = S_scale [i].u_pow;
      if (r_scale   != NULL)  *r_scale  = S_scale [i].u_scale;
      if (r_name    != NULL)  ystrlcpy (r_name   , S_scale [i].u_name   , LEN_TERSE);
      if (r_sci     != NULL)  ystrlcpy (r_sci    , S_scale [i].u_sci    , LEN_SHORT);
      if (r_english != NULL)  ystrlcpy (r_english, S_scale [i].u_english, LEN_LABEL);
      return 0;
      /*---(done)------------------------*/
   }
   /*> switch (a_unit) {                                                                    <* 
    *> case 'Y' :  x_scale = 1000000000000000000000000.0;      break;  /+ yotta  À+24  +/   <* 
    *> case 'Z' :  x_scale = 1000000000000000000000.0;         break;  /+ zetta  À+21  +/   <* 
    *> case 'E' :  x_scale = 1000000000000000000.0;            break;  /+ exa    À+18  +/   <* 
    *> case 'P' :  x_scale = 1000000000000000.0;               break;  /+ peta   À+15  +/   <* 
    *> case 'T' :  x_scale = 1000000000000.0;                  break;  /+ tera   À+12  +/   <* 
    *> case 'G' :  x_scale = 1000000000.0;                     break;  /+ giga   À+09  +/   <* 
    *> case 'M' :  x_scale = 1000000.0;                        break;  /+ mega   À+06  +/   <* 
    *> case 'K' :  x_scale = 1000.0;                           break;  /+ kilo   À+03  +/   <* 
    *> case 'H' :  x_scale = 100.0;                            break;  /+ hecto  À+02  +/   <* 
    *> case 'D' :  x_scale = 10.0;                             break;  /+ deca   À+01  +/   <* 
    *> case '-' :  x_scale = 1.0;                              break;                       <* 
    *> case '.' :  x_scale = 1.0;                              break;                       <* 
    *> case 'd' :  x_scale = 0.1;                              break;  /+ deci   À-01  +/   <* 
    *> case 'c' :  x_scale = 0.01;                             break;  /+ centa  À-02  +/   <* 
    *> case 'm' :  x_scale = 0.001;                            break;  /+ milli  À-03  +/   <* 
    *> case 'u' :  x_scale = 0.000001;                         break;  /+ micro  À-06  +/   <* 
    *> case 'n' :  x_scale = 0.000000001;                      break;  /+ nano   À-09  +/   <* 
    *> case 'p' :  x_scale = 0.000000000001;                   break;  /+ pico   À-12  +/   <* 
    *> case 'f' :  x_scale = 0.000000000000001;                break;  /+ femto  À-15  +/   <* 
    *> case 'a' :  x_scale = 0.000000000000000001;             break;  /+ atto   À-18  +/   <* 
    *> case 'z' :  x_scale = 0.000000000000000000001;          break;  /+ zepto  À-21  +/   <* 
    *> case 'y' :  x_scale = 0.000000000000000000000001;       break;  /+ yocto  À-24  +/   <* 
    *> default  :  return -2;                                  break;                       <* 
    *> }                                                                                    <*/
   /*> *b_value /= x_scale;                                                           <*/
   /*---(complete)-----------------------*/
   return -1;
}

char ystrunits  (char a_unit, char *r_pow, double *r_scale, char r_name [LEN_TERSE], char r_sci [LEN_SHORT], char r_english [LEN_LABEL]) { return ystr_units ('.', a_unit, NULL, r_pow, r_scale, r_name, r_sci, r_english); }
char ystr2unit  (char a_unit, double *b_value)   { return ystr_units ('>', a_unit, b_value, NULL, NULL, NULL, NULL, NULL); }
char ystr4unit  (char a_unit, double *b_value)   { return ystr_units ('<', a_unit, b_value, NULL, NULL, NULL, NULL, NULL); }



/*====================------------------------------------====================*/
/*===----                 support for string to number                 ----===*/
/*====================------------------------------------====================*/
static void      o___2SUPPORT________________o (void) {;}

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
   DEBUG_YSTR   yLOG_snote   (a_src);
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
   x_len = strlen (a_src);
   DEBUG_YSTR   yLOG_sint    (x_len);
   DEBUG_YSTR   yLOG_sint    (a_under);
   --rce; if (x_len < a_under) {
      DEBUG_YSTR   yLOG_snote   ("a_src too short");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_pre == TYPE_BIN) {
      if (x_len >= LEN_HUND) {
         DEBUG_YSTR   yLOG_snote   ("a_src binary too long");
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   } else if (a_pre == TYPE_OCT) {
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
      DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   x_1st = tolower (a_src [0]);
   DEBUG_YSTR   yLOG_schar   (x_1st);
   x_2nd = tolower (a_src [1]);
   DEBUG_YSTR   yLOG_schar   (x_2nd);
   /*---(octal exception)----------------*/
   if (a_pre == TYPE_OCT && x_1st == '0') {
      DEBUG_YSTR   yLOG_snote   ("octal zero prefix");
      if (strchr ("oOˆ", x_2nd) == NULL) x_min  =  1;
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
      if (a_pre == TYPE_OCT && x_1st == '0' && x_len == 1) {
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

char
ystr2_sign              (char b_src [LEN_TITLE], char *r_sign)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        x_src       [LEN_TITLE] = "";
   int         l           =    0;
   char        x_beg       =    0;
   char        x_sign      =    1;
   char        x_1st       =  ' ';
   char        x_2nd       =  ' ';
   int         i           =    0;
   /*---(default)------------------------*/
   if (r_sign  != NULL)  *r_sign  = +1;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (b_src == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (x_src, b_src, LEN_TITLE);
   DEBUG_YSTR   yLOG_snote   (x_src);
   l = strlen (x_src);
   DEBUG_YSTR   yLOG_sint    (l);
   /*---(quick-out)----------------------*/
   if (l <= 1) {
      DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(leading padding)----------------*/
   for (i = x_beg; i < l; ++i) {
      if (x_src [i] == '\0')  break;
      if (strchr ("∑≤¥',·:", x_src [i]) == NULL)  break;
      ++x_beg;
   }
   DEBUG_YSTR   yLOG_sint    (x_beg);
   l = strlen (x_src);
   DEBUG_YSTR   yLOG_sint    (l);
   /*---(kill leading dollar sign)--------*/
   x_1st = x_src [x_beg];
   DEBUG_YSTR   yLOG_schar   (x_1st);
   if (x_1st == '$') {
      ++x_beg;
      x_1st = x_src [x_beg];
      DEBUG_YSTR   yLOG_schar   (x_1st);
   }
   /*---(leading sign)-------------------*/
   switch (x_1st) {
   case '+' : x_sign = +1;   ++x_beg;  break;
   case '-' : x_sign = -1;   ++x_beg;  break;
   case '(' : x_sign = -1;   ++x_beg;  break;
   }
   DEBUG_YSTR   yLOG_sint    (x_sign);
   DEBUG_YSTR   yLOG_sint    (x_beg);
   /*---(post-sign padding)--------------*/
   for (i = x_beg; i < l; ++i) {
      if (x_src [i] == '\0')  break;
      if (strchr ("∑≤¥',·:", x_src [i]) == NULL)  break;
      ++x_beg;
   }
   DEBUG_YSTR   yLOG_sint    (x_beg);
   l = strlen (x_src);
   DEBUG_YSTR   yLOG_sint    (l);
   /*---(trailing sign)------------------*/
   x_1st = x_src [l - 1];
   DEBUG_YSTR   yLOG_schar   (x_1st);
   x_2nd = x_src [l - 2];
   DEBUG_YSTR   yLOG_schar   (x_2nd);
   switch (x_1st) {
   case '+' : x_sign = +1;  x_src [l - 1] = '\0';  break;
   case '-' : x_sign = -1;  x_src [l - 1] = '\0';  break;  
   case ')' :               x_src [l - 1] = '\0';  break;
   }
   DEBUG_YSTR   yLOG_sint    (x_sign);
   /*---(trailing padding)---------------*/
   for (i = l; i > 0; --i) {
      if (strchr ("∑≤¥',·:", x_src [i]) == NULL)  break;
      x_src [i] = '\0';
   }
   /*---(save-back)----------------------*/
   ystrlcpy (b_src, x_src + x_beg, LEN_TITLE);
   if (r_sign  != NULL)  *r_sign  = x_sign;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----               convert specialty base to number               ----===*/
/*====================------------------------------------====================*/
static void      o___2BASES__________________o (void) {;}

char
ystr2base               (char a_src [LEN_HUND], char a_charset [LEN_HUND], ullong *r_ullong)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_base      =    0;
   char        x_len       =    0;
   int         i           =    0;
   char        x_ch        =  '-';
   char       *p           = NULL;
   int         x_digit     =    0;               /* digit value               */
   ullong      x_place     =    1;               /* base position             */
   ullong      x_final     =    0;               /* final value               */
   char        c           =    0;               /* digits included           */
   ullong      x_new       =    0;
   ullong      x_avail     =    0;
   ullong      x_prev      =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_ullong != NULL)  *r_ullong =   0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_point   ("a_src"     , a_src);
   --rce; if (a_src == NULL || a_src [0] == '\0') {
      DEBUG_YSTR   yLOG_note    ("a_src null/empty");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("a_src"     , a_src);
   DEBUG_YSTR   yLOG_point   ("a_charset" , a_charset);
   --rce; if (a_charset  == NULL || a_charset [0] == '\0') {
      DEBUG_YSTR   yLOG_note    ("charset null/empty");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("a_charset" , a_charset);
   /*---(prepare)------------------------*/
   x_len = strlen (a_src);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   x_base = strlen (a_charset);
   DEBUG_YSTR   yLOG_value   ("x_base"    , x_base);
   --rce;  if (x_base < 2) {
      DEBUG_YSTR   yLOG_note    ("base too small");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_base >= LEN_HUND) {
      DEBUG_YSTR   yLOG_note    ("base too large");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk string)--------------------*/
   --rce;  for (i = x_len - 1; i >= 0; --i) {
      /*---(select)----------------------*/
      x_ch = a_src [i];
      if (x_base < 36)  x_ch = tolower (x_ch);
      DEBUG_YSTR   yLOG_char    ("x_ch"      , x_ch);
      /*---(filter)----------------------*/
      if (x_base == 10 && x_ch == ',')   continue;
      if (strchr ("':·¥", x_ch) != NULL)  continue;
      /*---(check)-----------------------*/
      if (strchr ("∑≤"  , x_ch) != NULL)  x_ch = '0';
      if (strchr ("≥œ∞" , x_ch) != NULL)  x_ch = a_charset [x_base - 1];
      p = strchr (a_charset, x_ch);
      if (p == NULL) {
         DEBUG_YSTR   yLOG_note    ("BAD CHARACTER");
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(process)---------------------*/
      x_digit = p - a_charset;
      DEBUG_YSTR   yLOG_value   ("x_digit"   , x_digit);
      /*---(overflow)--------------------*/
      DEBUG_YSTR   yLOG_ullong  ("x_prev"    , x_prev);
      DEBUG_YSTR   yLOG_ullong  ("x_place"   , x_place);
      if (x_digit > 0 && x_place < x_prev) {
         DEBUG_YSTR   yLOG_note    ("TOO MANY SIGS");
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(calculate)-------------------*/
      x_new   = x_digit * x_place;
      DEBUG_YSTR   yLOG_ullong  ("x_new"     , x_new);
      if (x_digit > 0 && x_new == 0) {
         DEBUG_YSTR   yLOG_note    ("OVERFLOW");
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(check)-----------------------*/
      x_avail = MAX_ULLONG - x_final;
      DEBUG_YSTR   yLOG_ullong  ("x_avail"   , x_avail);
      if (x_new > x_avail) {
         DEBUG_YSTR   yLOG_note    ("OVERFLOW");
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(accumulate)------------------*/
      x_final += x_new;
      ++c;
      DEBUG_YSTR   yLOG_complex ("update"    , "%2dd, %2dc, %llup, %llun, %lluf, %llu", x_digit, c, x_place, x_new, x_final, x_prev);
      /*---(next)------------------------*/
      x_prev   = x_place;
      x_place *= x_base;
      /*---(done)------------------------*/
   }
   DEBUG_YSTR   yLOG_value   ("c"         , c);
   DEBUG_YSTR   yLOG_ullong  ("x_final"   , x_final);
   /*---(save-back)----------------------*/
   if (r_ullong != NULL)  *r_ullong = x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return c;
}

char         /*-> interpret binary numbers ----------------[ petal  [ 2f---- ]*/
ystr2bin                (char a_src [LEN_HUND], ullong *r_ullong, double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_beg       =   -1;               /* first translatable char   */
   ullong      x_final     =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src,  r_ullong, r_double, 2 , TYPE_BIN, 'È', NULL, &x_beg);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate)----------------------*/
   rc = ystr2base (a_src + x_beg, YSTR_BINARY, &x_final);
   DEBUG_YSTR   yLOG_value   ("ystr2base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check range)--------------------*/
   DEBUG_YSTR   yLOG_ullong  ("x_final"   , x_final);
   --rce;  if (r_double != NULL  && x_final > MAX_DOUBLE) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_ullong != NULL)  *r_ullong = x_final;
   if (r_double != NULL)  *r_double = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return rc;
}

char         /*-> interpret octal numbers -----------------[ petal  [ 2e---- ]*/
ystr2oct                (char a_src [LEN_DESC] , ullong *r_ullong, double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_beg       =   -1;               /* first translatable char   */
   ullong      x_final     =    0;               /* final value               */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, r_ullong, r_double,  1 , TYPE_OCT, 'ˆ', NULL, &x_beg);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate)----------------------*/
   rc = ystr2base (a_src + x_beg, YSTR_OCTAL , &x_final);
   DEBUG_YSTR   yLOG_value   ("ystr2base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check range)--------------------*/
   DEBUG_YSTR   yLOG_ullong  ("x_final"   , x_final);
   --rce;  if (r_double != NULL  && x_final > MAX_DOUBLE) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_ullong != NULL)  *r_ullong = x_final;
   if (r_double != NULL)  *r_double = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
ystr2int                (char a_src [LEN_TITLE], ullong *r_ullong, double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_src       [LEN_TITLE] = "";
   char        x_sign      =   +1;
   ullong      x_final     =    0;               /* final value               */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, r_ullong, r_double,  1 , 0 , 0 , NULL, NULL);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get the sign)-------------------*/
   ystrlcpy (x_src, a_src, LEN_TITLE);
   rc = ystr2_sign (x_src, &x_sign);
   DEBUG_YSTR   yLOG_value   ("ystr2_sign", rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("x_src"     , x_src);
   /*---(translate)----------------------*/
   rc = ystr2base (x_src, YSTR_NUMBER, &x_final);
   DEBUG_YSTR   yLOG_value   ("ystr2base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check range)--------------------*/
   DEBUG_YSTR   yLOG_ullong  ("x_final"   , x_final);
   --rce;  if (r_double != NULL  && x_final > MAX_DOUBLE) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check range)--------------------*/
   DEBUG_YSTR   yLOG_value   ("x_sign"    , x_sign);
   --rce;  if (x_sign   == -1 && r_ullong != NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_ullong != NULL)  *r_ullong = x_final;
   if (r_double != NULL)  *r_double = ((double) x_final) * x_sign;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return rc;
}

char         /*-> interpret hexadecimal numbers -----------[ petal  [ 2f---- ]*/
ystr2hex                (char a_src [LEN_TITLE], ullong *r_ullong, double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_beg       =   -1;               /* first translatable char   */
   ullong      x_final     =    0;               /* final value               */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, r_ullong, r_double,  2 , TYPE_HEX, 'ı', NULL, &x_beg);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate)----------------------*/
   rc = ystr2base (a_src + x_beg, YSTR_HEX   , &x_final);
   DEBUG_YSTR   yLOG_value   ("ystr2base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check range)--------------------*/
   DEBUG_YSTR   yLOG_ullong  ("x_final"   , x_final);
   --rce;  if (r_double != NULL  && x_final > MAX_DOUBLE) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_ullong != NULL)  *r_ullong = x_final;
   if (r_double != NULL)  *r_double = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return rc;
}

/*> #define     YSTR_MONGO    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#"   <* 
 *> #define     YSTR_BASE64   "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"   <*/
/*
 *  999,999,999,999,999     DjX6kxn//    3ZN'wan'd¨¨
 *                          P//////////  0F¨'¨¨¨'¨¨¨'¨¨¨   
 *
 */

char
ystr2mongo              (char a_src [LEN_TITLE], ullong *r_ullong, double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_beg       =   -1;               /* first translatable char   */
   ullong      x_final     =    0;               /* final value               */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, r_ullong, r_double,  2 , TYPE_MONGO, 'Ì', NULL, &x_beg);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate)----------------------*/
   rc = ystr2base (a_src + x_beg, YSTR_MONGO , &x_final);
   DEBUG_YSTR   yLOG_value   ("ystr2base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check range)--------------------*/
   DEBUG_YSTR   yLOG_ullong  ("x_final"   , x_final);
   --rce;  if (r_double != NULL  && x_final > MAX_DOUBLE) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_ullong != NULL)  *r_ullong = x_final;
   if (r_double != NULL)  *r_double = (double) x_final;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----              convert specialt formats to number              ----===*/
/*====================------------------------------------====================*/
static void      o___2SPECIAL________________o (void) {;}

char
ystr2roman              (char a_src [LEN_TITLE], ullong *r_ullong, double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_src       [LEN_TITLE] = "";
   char        l           =    0;
   char       *p           = NULL;
   int         i           =    0;
   ullong      x_ullong    =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, r_ullong, r_double,  1 ,  0 ,  0 , &l, NULL);
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
      return 1;
   }
   /*---(prepare)------------------------*/
   ystrlcpy   (x_src, a_src, LEN_TITLE);
   ystrlupper (x_src, LEN_TITLE);
   DEBUG_YSTR   yLOG_info    ("x_src"     , x_src);
   p = x_src;
   DEBUG_YSTR   yLOG_info    ("current"   , p);
   for (i = 0; i < LEN_DESC; ++i) {
      if (S_roman [i].r_wide == 0)   break;
      if (strncmp (p, S_roman [i].r_chars, S_roman [i].r_wide) == 0) {
         DEBUG_YSTR   yLOG_info    ("found"     , S_roman [i].r_chars);
         x_ullong += S_roman [i].r_value;
         p        += S_roman [i].r_wide;
         DEBUG_YSTR   yLOG_info    ("current"   , p);
         c += S_roman [i].r_wide;
      }
   }
   /*---(troubles)-----------------------*/
   DEBUG_YSTR   yLOG_point   ("end"       , x_src + l);
   --rce;  if (p < x_src + l) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_ullong  ("x_ullong"  , x_ullong);
   --rce;  if (x_ullong < 0 || x_ullong >= 4000) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_ullong != NULL)  *r_ullong = x_ullong;
   if (r_double != NULL)  *r_double = (double) x_ullong;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----               convert normal formats to number               ----===*/
/*====================------------------------------------====================*/
static void      o___2REALS__________________o (void) {;}

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
   int         i           =    0;
   /*---(default)------------------------*/
   if (r_int   != NULL)  strcpy (r_int, "");
   if (r_dec   != NULL)  strcpy (r_dec, "");
   if (r_exp   != NULL)  strcpy (r_exp, "");
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   ystrlcpy (x_src, a_src, LEN_TITLE);
   DEBUG_YSTR   yLOG_snote   (x_src);
   l = strlen (x_src);
   DEBUG_YSTR   yLOG_sint    (l);
   /*---(count decimal points)-----------*/
   c  = ystrlddcnt (x_src, '.', LEN_TITLE);
   c += ystrlddcnt (x_src, 'Å', LEN_TITLE);
   DEBUG_YSTR   yLOG_sint    (c);
   --rce;  if (c > 1) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (c == 1)  x_dec = 'y';
   /*---(count exponent markers)---------*/
   c = n  = ystrlddcnt (x_src, 'À', LEN_TITLE);
   DEBUG_YSTR   yLOG_sint    (n);
   if (n == 1 && x_exp == '-')  x_exp = 'À';
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
   if (p == NULL)  p = strchr (x_src, 'Å');
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
      for (i = l - 1; i > 0; --i) {
         if (p [i] != '0') break;
         p [i] = '\0';
      }
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
ystr2_part              (char a_part, char a_src [LEN_TITLE], llong *r_llong)
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
   char        x_src       [LEN_TITLE] = "";
   int         i           =    0;
   char        x_ch        =  '-';
   char        n           =    0;
   char       *p           = NULL;
   ullong      x_ullong    =    0;
   llong       x_llong     =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_llong  != NULL)  *r_llong  = 0.0;
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, r_llong , NULL    ,  1 ,  0 ,  0 , &x_len, NULL);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(strip signs)--------------------*/
   DEBUG_YSTR   yLOG_char    ("a_part"    , a_part);
   /*> if      (a_src [x_beg] == '$' && a_part == 'i')   { ++x_beg;   }               <* 
    *> else if (a_src [x_beg] == '(' && a_part == 'i')   { ++x_beg; x_sign = -1; }    <*/
   if      (a_src [x_beg] == '+' && a_part != 'd')   { ++x_beg;   }
   else if (a_src [x_beg] == '-' && a_part != 'd')   { ++x_beg; x_sign = -1; }
   DEBUG_YSTR   yLOG_value   ("x_sign"    , x_sign);
   /*---(check for no payload)-----------*/
   DEBUG_YSTR   yLOG_value   ("x_beg"     , x_beg);
   --rce;  if (x_beg == x_len) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(leading zero)-------------------*/
   DEBUG_YSTR   yLOG_char    ("beg"       , a_src [x_beg]);
   --rce;  if (a_part == 'i' && x_beg + 1 < x_len && a_src [x_beg] == '0') {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(decimal trailing zeros)---------*/
   ystrlcpy (x_src, a_src + x_beg, LEN_TITLE);
   x_len = strlen (x_src);
   if (a_part == 'd') {
      for (i = x_len - 1; i > 0; --i) {
         if (x_src [i] != '0') break;
         x_src [i] = '\0';
      }
   }
   /*---(translate)----------------------*/
   rc = ystr2base (x_src, YSTR_NUMBER, &x_ullong);
   DEBUG_YSTR   yLOG_value   ("ystr2base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(significant digits)-------------*/
   c = rc;
   DEBUG_YSTR   yLOG_value   ("c"         , c);
   --rce;  if (c > 15) {
      DEBUG_YSTR   yLOG_note    ("TOO MANY SIGS");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(integer range)------------------*/
   DEBUG_YSTR   yLOG_ullong  ("x_ullong"  , x_ullong);
   --rce;  if (x_ullong > MAX_DOUBLE) {
      DEBUG_YSTR   yLOG_note    ("DOUBLE OVERFLOW");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_llong  = (llong) x_ullong;
   x_llong *= x_sign;
   DEBUG_YSTR   yLOG_llong   ("x_llong"   , x_llong);
   /*---(exponent range)-----------------*/
   --rce;  if (a_part == 'e' && x_llong > 99) {
      DEBUG_YSTR   yLOG_note    ("EXP TOO BIG");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_llong  != NULL)  *r_llong  = x_llong;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return c;
}

char
ystr2float              (char a_src [LEN_TITLE], ullong *r_ullong, double *r_double)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_src       [LEN_TITLE] = "";
   char        x_int       [LEN_TITLE] = "";
   llong       x_vint      =    0;
   char        x_dec       [LEN_TITLE] = "";
   llong       x_vdec      =    0;
   char        x_exp       [LEN_TITLE] = "";
   llong       x_vexp      =    0;
   char        x_sigs      =    0;
   double      x_decs      =  0.0;
   double      x_double    =  0.0;
   char        x_sign      =   +1;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_double != NULL)  *r_double = 0.0;
   /*---(defense)------------------------*/
   rc = ystr2_defense (a_src, r_ullong, r_double,  1 ,  0 ,  0 , NULL, NULL);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get the sign)-------------------*/
   ystrlcpy (x_src, a_src, LEN_TITLE);
   rc = ystr2_sign (x_src, &x_sign);
   DEBUG_YSTR   yLOG_value   ("ystr2_sign", rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("x_src"     , x_src);
   /*---(parttion)-----------------------*/
   rc = ystr2_divide (x_src, x_int, x_dec, x_exp);
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
      DEBUG_YSTR   yLOG_llong   ("x_vint"    , x_vint);
      x_sigs  += rc;
      DEBUG_YSTR   yLOG_value   ("x_sigs"    , x_sigs);
      x_double += (double) x_vint;
      DEBUG_YSTR   yLOG_double  ("x_double"  , x_double);
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
      DEBUG_YSTR   yLOG_llong   ("x_vdec"    , x_vdec);
      x_sigs  += rc;
      DEBUG_YSTR   yLOG_value   ("x_sigs"    , x_sigs);
      x_decs   = ((double) x_vdec) * pow (10, -rc);
      DEBUG_YSTR   yLOG_double  ("x_decs"    , x_decs);
      x_double += x_decs;
      DEBUG_YSTR   yLOG_double  ("x_double"  , x_double);
   }
   /*---(check on sigs)------------------*/
   --rce;  if (x_sigs > 15) {
      DEBUG_YSTR   yLOG_note    ("TOO MANY TOTAL SIGS");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
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
      DEBUG_YSTR   yLOG_llong   ("x_vexp"    , x_vexp);
      x_double *= pow (10, x_vexp);
      DEBUG_YSTR   yLOG_double  ("x_double"  , x_double);
   }
   /*---(save-back llong)----------------*/
   DEBUG_YSTR   yLOG_point   ("r_double"  , r_double);
   --rce;  if (r_ullong != NULL) {
      DEBUG_YSTR   yLOG_note    ("handle as ullong");
      if (x_sign == -1) {
         DEBUG_YSTR   yLOG_note    ("ULLONG CAN NOT BE NEG");
         DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      *r_ullong = x_vint;
   }
   /*---(save-back double)---------------*/
   if (r_double != NULL) {
      DEBUG_YSTR   yLOG_note    ("handle as double");
      DEBUG_YSTR   yLOG_value   ("x_sign"    , x_sign);
      *r_double = x_double * x_sign;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return x_sigs;
}

char ystr2comma (char a_src [LEN_TITLE], ullong *r_ullong, double *r_double) { return ystr2float (a_src, r_ullong, r_double); }
char ystr2real  (char a_src [LEN_TITLE], ullong *r_ullong, double *r_double) { return ystr2float (a_src, r_ullong, r_double); }
char ystr2sci   (char a_src [LEN_TITLE], ullong *r_ullong, double *r_double) { return ystr2float (a_src, r_ullong, r_double); }



/*====================------------------------------------====================*/
/*===----                    number to string driver                   ----===*/
/*====================------------------------------------====================*/
static void      o___2DRIVER_________________o (void) {;}

char
ystr2_type              (char a_src [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        l           =    0;
   char        x_1st       =  '-';
   char        x_2nd       =  '-';
   char        x_end       =  '-';
   int         i           =    0;
   char       *p           = NULL;
   char        x_type      =  '-';
   char       *x_norms     = "+-($";
   char       *x_bases     = "boxz";
   char       *x_greek     = "ÈˆıÌ";
   char        n           =    0;
   char        c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL || a_src [0] == '\0') {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return TYPE_FAIL;
   }
   DEBUG_YSTR   yLOG_info    ("a_src"     , a_src);
   /*---(prepare)------------------------*/
   l = strlen (a_src);
   DEBUG_YSTR   yLOG_value   ("l"         , l);
   x_1st = a_src [0];
   DEBUG_YSTR   yLOG_char    ("x_1st"     , x_1st);
   /*---(handle single)------------------*/
   --rce;  if (l == 1) {
      if (strchr (YSTR_NUMBER, x_1st) != NULL) {
         DEBUG_YSTR   yLOG_note    ("single digit number");
         DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
         return TYPE_INT;
      }
      if (strchr (YSTR_ROMAN, tolower (x_1st)) != NULL) {
         DEBUG_YSTR   yLOG_note    ("single roman digit");
         DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
         return TYPE_ROMAN;
      }
      DEBUG_YSTR   yLOG_note    ("single non-number");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return TYPE_FAIL;
   }
   /*---(real numbers)-------------------*/
   c  = ystrldcnt (a_src, '.', LEN_HUND);
   c += ystrldcnt (a_src, 'Å', LEN_HUND);
   c += ystrldcnt (a_src, 'À', LEN_HUND);
   DEBUG_YSTR   yLOG_value   ("c"         , c);
   if (c > 0) {
      DEBUG_YSTR   yLOG_note    ("real number decimal or exponent");
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return TYPE_FLOAT;
   }
   /*---(normal numbers)-----------------*/
   DEBUG_YSTR   yLOG_info    ("x_norms"   , x_norms);
   p = strchr (x_norms, x_1st);
   DEBUG_YSTR   yLOG_point   ("p"         , p);
   if (p != NULL) {
      DEBUG_YSTR   yLOG_note    ("integer prefixes");
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return TYPE_INT;
   }
   /*---(technical numbers)--------------*/
   x_end = a_src [l - 1];
   DEBUG_YSTR   yLOG_char    ("x_end"     , x_end);
   p = strchr ("+-", x_end);
   DEBUG_YSTR   yLOG_point   ("p"         , p);
   if (p != NULL) {
      DEBUG_YSTR   yLOG_note    ("integer suffixes");
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return TYPE_INT;
   }
   /*---(normal prefixes)----------------*/
   DEBUG_YSTR   yLOG_info    ("x_bases"   , x_bases);
   p = strchr (x_bases, tolower (x_1st));
   DEBUG_YSTR   yLOG_point   ("p"         , p);
   if (p != NULL) {
      DEBUG_YSTR   yLOG_note    ("single letter prefix");
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return tolower (x_1st);
   }
   /*---(normal greek)-------------------*/
   DEBUG_YSTR   yLOG_info    ("x_greek"   , x_greek);
   p = strchr (x_greek, x_1st);
   DEBUG_YSTR   yLOG_point   ("p"         , p);
   if (p != NULL) {
      DEBUG_YSTR   yLOG_note    ("greek letter prefix");
      n = (char) (p - x_greek);
      DEBUG_YSTR   yLOG_value   ("n"         , n);
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return x_bases [n];
   }
   /*---(zero-led prefixes)--------------*/
   x_2nd = a_src [1];
   DEBUG_YSTR   yLOG_char    ("x_2nd"     , x_2nd);
   if (x_1st == '0') {
      if (strchr (TYPE_BASES, tolower (x_2nd)) != NULL) {
         DEBUG_YSTR   yLOG_note    ("zero-led prefix");
         DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
         return tolower (x_2nd);
      } else if (strchr (YSTR_NUMBER, x_2nd) != NULL) {
         DEBUG_YSTR   yLOG_note    ("zero led octal");
         DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
         return TYPE_OCT;
      } else if (x_2nd == '.') {
         DEBUG_YSTR   yLOG_note    ("zero plus decimal real");
         DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
         return TYPE_FLOAT;
      }
   }
   /*---(complicated)--------------------*/
   --rce;  for (i = 0; i < l; ++i) {
      /*---(filter everywhere sperators)-*/
      if (strchr ("':·"  , a_src [i]) != NULL)  continue;
      /*---(check bases)-----------------*/
      if (strchr (",rzxo", x_type) == NULL && strchr (YSTR_BINARY, a_src [i]) != NULL)  { x_type = TYPE_BIN;   continue; }
      if (strchr (",rzx" , x_type) == NULL && strchr (YSTR_OCTAL , a_src [i]) != NULL)  { x_type = TYPE_OCT;   continue; }
      if (strchr (",rz"  , x_type) == NULL && strchr (YSTR_HEXUP , a_src [i]) != NULL)  { x_type = TYPE_HEX;   continue; }
      if (strchr (",z"   , x_type) == NULL && strchr (YSTR_ROMAN , a_src [i]) != NULL)  { x_type = TYPE_ROMAN; continue; }
      if (strchr (","    , x_type) == NULL && strchr (YSTR_MONGO , a_src [i]) != NULL)  { x_type = TYPE_MONGO; continue; }
      /*---(check commas)----------------*/
      if (strchr (YSTR_NUMPLUS, a_src [i]) != NULL)  { x_type = TYPE_INT; continue; }
      /*---(trouble)---------------------*/
      DEBUG_YSTR   yLOG_note    ("found entirely illegal character");
      yLOG_exitr   (__FUNCTION__, rce);
      return TYPE_FAIL;
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return x_type;
}

char
ystr2main               (char a_src [LEN_HUND] , char *r_type, ullong *r_ullong, double *r_double)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   char        x_type      =  '-';
   double      x_double    =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_type    != NULL)  *r_type   = '-';
   if (r_ullong  != NULL)  *r_ullong =   0;
   if (r_double  != NULL)  *r_double = 0.0;
   /*---(defense)------------------------*/
   rc = ystr2_type (a_src);
   DEBUG_YSTR   yLOG_value   ("ystr2_type", rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-type)----------------------*/
   x_type = rc;
   DEBUG_YSTR   yLOG_char    ("x_type"    , x_type);
   --rce;  if (r_type    != NULL)  *r_type   = x_type;
   /*---(handle)-------------------------*/
   switch (x_type) {
   case TYPE_BIN   :
      DEBUG_YSTR   yLOG_note    ("binary");
      rc = ystr2bin    (a_src, r_ullong, r_double);
      break;
   case TYPE_OCT   :
      DEBUG_YSTR   yLOG_note    ("octal");
      rc = ystr2oct    (a_src, r_ullong, r_double);
      break;
   case TYPE_INT   :
      DEBUG_YSTR   yLOG_note    ("integer");
      rc = ystr2int    (a_src, r_ullong,  r_double);
      break;
   case TYPE_HEX   :
      DEBUG_YSTR   yLOG_note    ("hexadecimal");
      rc = ystr2hex    (a_src, r_ullong,  r_double);
      break;
   case TYPE_MONGO :
      DEBUG_YSTR   yLOG_note    ("mongo");
      rc = ystr2mongo  (a_src, r_ullong, r_double);
      break;
   case TYPE_ROMAN :
      DEBUG_YSTR   yLOG_note    ("roman");
      rc = ystr2roman  (a_src, r_ullong, r_double);
      break;
   case TYPE_FLOAT :
      DEBUG_YSTR   yLOG_note    ("comma");
      rc = ystr2float  (a_src, r_ullong, r_double);
      break;
   default         :
      DEBUG_YSTR   yLOG_note    ("UNKNOWN");
      return rce;
      break;
   }
   /*---(check trouble)------------------*/
   DEBUG_YSTR   yLOG_value   ("return"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_double != NULL) {
      DEBUG_YSTR   yLOG_double  ("r_double"  , *r_double);
   }
   if (r_ullong != NULL) {
      DEBUG_YSTR   yLOG_ullong  ("r_ullong"  , *r_ullong);
   }
   /*---(save-back)----------------------*/
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return rc;
}

char ystr2num   (char a_src [LEN_HUND] , double *r_double) { return ystr2main (a_src, NULL, NULL, r_double); }



/*====================------------------------------------====================*/
/*===----                 support for number to string                 ----===*/
/*====================------------------------------------====================*/
static void      o___4SUPPORT________________o (void) {;}

char
ystr4_defense           (char a_type, char a_greek, ullong a_ullong, double a_double, char a_fmt, char a_max, char *r_source, char r_prefix [LEN_SHORT], char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        x_source    =  'd';
   int         x_len       =    0;
   char        x_1st       =  '-';
   char        x_2nd       =  '-';
   char        x_min       =   -1;               /* first translatable char   */
   char        x_beg       =  '-';
   double      x_max       =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_source != NULL)   *r_source = 'd';
   if (r_prefix != NULL)   strcpy (r_prefix, "");
   if (r_out    != NULL)   strcpy (r_out   , "");
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (r_out);
   --rce; if (r_out  == NULL) {
      DEBUG_YSTR   yLOG_snote   ("no out field");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check max length)---------------*/
   DEBUG_YSTR   yLOG_sint    (a_max);
   --rce; if (a_type == TYPE_BIN) {
      if (a_max > LEN_HUND) {
         DEBUG_YSTR   yLOG_snote   ("a_max binary too large");
         ystrlcpy (r_out, "#p/too", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   } else if (a_type == TYPE_OCT) {
      if (a_max > LEN_DESC) {
         DEBUG_YSTR   yLOG_snote   ("a_max octal too large");
         ystrlcpy (r_out, "#p/too", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   } else if (a_max > LEN_TITLE) {
      DEBUG_YSTR   yLOG_snote   ("a_max too large");
      ystrlcpy (r_out, "#p/too", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check input type)---------------*/
   DEBUG_YSTR   yLOG_sint    (a_ullong);
   DEBUG_YSTR   yLOG_sdouble (a_double);
   --rce; if (a_ullong != 0 && a_double != 0) {
      DEBUG_YSTR   yLOG_snote   ("a_ullong and a_double can not both be used");
      ystrlcpy (r_out, "#p/inp", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   if (a_ullong != 0)  x_source = 'l';
   DEBUG_YSTR   yLOG_schar   (x_source);
   /*---(check type)---------------------*/
   DEBUG_YSTR   yLOG_schar   (a_type);
   --rce; if (a_type == NULL || a_type == '∑' || strchr ("boixz∑rt∑fe", a_type) == NULL) {
      DEBUG_YSTR   yLOG_snote   ("illegal type");
      ystrlcpy (r_out, "#p/typ", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check double ranges)------------*/
   --rce; if (x_source == 'd') {
      /*---(minimum)---------------------*/
      if (strchr ("boixz∑rt", a_type) != NULL && a_double < 0) {
         DEBUG_YSTR   yLOG_snote   ("a_double can not be negative");
         ystrlcpy (r_out, "#p/neg", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(range)-----------------------*/
      if (a_type != 'e' && (a_double > MAX_DOUBLE || a_double < -MAX_DOUBLE)) {
         DEBUG_YSTR   yLOG_snote   ("general overflow");
         ystrlcpy (r_out, "#p/ovr", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(roman)-----------------------*/
      if (a_type == TYPE_ROMAN && a_double > MAX_ROMAN) {
         DEBUG_YSTR   yLOG_snote   ("roman overflow");
         ystrlcpy (r_out, "#p/ovr", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check ullong ranges)------------*/
   else {
      if (a_type == TYPE_ROMAN && a_ullong > MAX_ROMAN) {
         DEBUG_YSTR   yLOG_snote   ("roman overflow");
         ystrlcpy (r_out, "#p/ovr", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(check format)-------------------*/
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (a_fmt == NULL || a_fmt == '∑' || a_fmt == ' ') {
      DEBUG_YSTR   yLOG_snote   ("illegal format");
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_type == 'r') {
      DEBUG_YSTR   yLOG_snote   ("roman");
      if (a_fmt  == NULL || strchr ("rR"       , a_fmt ) == NULL) {
         DEBUG_YSTR   yLOG_snote   ("illegal format");
         ystrlcpy (r_out, "#p/fmt", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (a_type == 't') {
      DEBUG_YSTR   yLOG_snote   ("time");
      if (a_fmt  == NULL || strchr ("tT∑dD"    , a_fmt ) == NULL) {
         DEBUG_YSTR   yLOG_snote   ("illegal format");
         ystrlcpy (r_out, "#p/fmt", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (strchr ("boixz", a_type) != NULL) {
      DEBUG_YSTR   yLOG_snote   ("bases");
      if (a_fmt  == NULL || strchr ("-dsfcg:t#", a_fmt ) == NULL) {
         DEBUG_YSTR   yLOG_snote   ("illegal format");
         ystrlcpy (r_out, "#p/fmt", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (strchr ("fe"   , a_type) != NULL) {
      DEBUG_YSTR   yLOG_snote   ("reals");
      if (strchr ("?∑if∑IF,∑aA$∑sS∑cC#∑pP∑eE"   , a_type) == NULL) {
         DEBUG_YSTR   yLOG_snote   ("illegal format");
         ystrlcpy (r_out, "#p/fmt", a_max);
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(assign prefix)------------------*/
   if (r_prefix != NULL && strchr ("boxz", a_type) != NULL) {
      switch (a_fmt) {
      case '-' : case 'd' :                            break;
      case 's' :  sprintf (r_prefix, "0%c", a_type);   break;
      case 'f' :  sprintf (r_prefix, "%c" , a_greek);  break;
      case 'c' :  sprintf (r_prefix, "%c'", a_type);   break;
      case 'g' :  sprintf (r_prefix, "%c'", a_greek);  break;
      case ':' :  sprintf (r_prefix, "%c:", a_greek);  break;
      case 't' :  sprintf (r_prefix, "%c·", a_greek);  break;
      case '#' :  sprintf (r_prefix, "%c·", a_greek);  break;
      }
   }
   /*---(save-back)----------------------*/
   if (r_source != NULL)   *r_source = x_source;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

/*> char                                                                                                            <* 
 *> ystrlins                (char a_pos, char a_insert [LEN_TITLE], int a_max, char b_out [LEN_RECD], int *b_len)   <* 
 *> {                                                                                                               <* 
 *>    char        rce         =  -10;                                                                              <* 
 *>    int         l           =    0;                                                                              <* 
 *>    int         w           =    0;                                                                              <* 
 *>    int         i           =    0;                                                                              <* 
 *>    --rce;  if (b_out    == NULL)  return rce;                                                                   <* 
 *>    l = strlen (b_out);                                                                                          <* 
 *>    --rce;  if (l     <= 0)        return rce;                                                                   <* 
 *>    --rce;  if (a_insert == NULL)  return rce;                                                                   <* 
 *>    w = strlen (a_insert);                                                                                       <* 
 *>    --rce;  if (w     <= 0)        return rce;                                                                   <* 
 *>    --rce;  if (a_pos <  0)        return rce;                                                                   <* 
 *>    --rce;  if (a_pos >= l)        return rce;                                                                   <* 
 *>    --rce;  if (l + w >= a_max)    return rce;                                                                   <* 
 *>    for (i = l; i >= a_pos; --i)  b_out [i + w] = b_out [i];                                                     <* 
 *>    for (i = 0; i <  w;     ++i)  b_out [a_pos + i] = a_insert [i];                                              <* 
 *>    if (b_len  != NULL)  *b_len = l + w;                                                                         <* 
 *>    return 0;                                                                                                    <* 
 *> }                                                                                                               <*/

char
ystr4_space_ints        (char a_every, char a_char, char b_out [LEN_HUND])
{
   char        rce         =  -10;
   int         l           =    0;
   uchar       x_ch        =  '-';
   char        x_pos       =  '-';
   int         i           =    0;               /* iterator -- character     */
   char        c           =    0;
   char        x_mark      [LEN_SHORT] = "";
   /*---(prepare)------------------------*/
   --rce;  if (b_out    == NULL)  return rce;
   l = strlen (b_out);
   --rce;  if (l     <= 0)        return rce;
   x_ch  = a_char;
   --rce;  if (x_ch   < 32 )      return rce;
   --rce;  if (x_ch  == 127)      return rce;
   sprintf (x_mark, "%c", x_ch);
   /*---(walk)---------------------------*/
   for (i = (l - 1) / a_every; i > 0; --i) {
      /*---(open space)------------------*/
      x_pos = l - (i * a_every);
      ystrlins (x_pos, x_mark, LEN_HUND, b_out, &l);
      /*---(put spearator)---------------*/
      /*> if (a_char == '#') {                                                        <* 
       *>    if (c % 2 == 0)  x_ch = 'Å';                                             <* 
       *>    else             x_ch = 'å';                                             <* 
       *> }                                                                           <*/
      /*> b_out [x_pos] = a_char;                                                     <*/
      ++c;
      /*---(update end)------------------*/
      /*> b_out [l] = '\0';                                                           <*/
      /*---(done)------------------------*/
   }
   return 0;
}

/*   bit?    Å≥≥≤≥å≤≥≥≥Å≤≥≥≤å≤≤≥≥Å≥≥≤≥å≤≥≥≥Å≥≥≤≥å≤≤≥≥Å≥≥≤≥å≤≥≥≥Å≤≥≥≤å≤≤≥≥Å≥≥≤≥å≤≥≥≥Å≥≤≥≥å≥≤≥≤Å */

char
ystr4_space_decs        (char a_every, char a_char, char b_out [LEN_HUND])
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

/*> char                                                                                                                             <* 
 *> ystr4_pretty            (char a_prefix [LEN_SHORT], char a_spacing, char a_cnt, char a_fmt, char a_max, char b_out [LEN_HUND])   <* 
 *> {                                                                                                                                <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                      <* 
 *>    char        rce         =  -10;                                                                                               <* 
 *>    char        rc          =    0;                                                                                               <* 
 *>    int         l           =    0;                                                                                               <* 
 *>    int         i           =    0;                                                                                               <* 
 *>    int         x_len       =    0;                                                                                               <* 
 *>    char        x_pad       [LEN_TERSE] = "";                                                                                     <* 
 *>    char        x_padding   [LEN_HUND]  = "";                                                                                     <* 
 *>    char        x_temp      [LEN_HUND]  = "";                                                                                     <* 
 *>    char        x_final     [LEN_HUND]  = "";                                                                                     <* 
 *>    char        n           =    0;                                                                                               <* 
 *>    char        c           =    0;                                                                                               <* 
 *>    /+---(header)-------------------------+/                                                                                      <* 
 *>    DEBUG_YSTR   yLOG_senter  (__FUNCTION__);                                                                                     <* 
 *>    /+---(defense)------------------------+/                                                                                      <* 
 *>    DEBUG_YSTR   yLOG_point   ("a_prefix"  , a_prefix);                                                                           <* 
 *>    --rce; if (a_prefix  == NULL) {                                                                                               <* 
 *>       DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);                                                                             <* 
 *>       return rce;                                                                                                                <* 
 *>    }                                                                                                                             <* 
 *>    DEBUG_YSTR   yLOG_info    ("a_prefix"  , a_prefix);                                                                           <* 
 *>    DEBUG_YSTR   yLOG_point   ("b_out"     , b_out);                                                                              <* 
 *>    --rce; if (b_out  == NULL || b_out [0] == '\0') {                                                                             <* 
 *>       DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);                                                                             <* 
 *>       return rce;                                                                                                                <* 
 *>    }                                                                                                                             <* 
 *>    DEBUG_YSTR   yLOG_info    ("b_out"     , b_out);                                                                              <* 
 *>    /+---(create pad)-----------+/                                                                                                <* 
 *>    sprintf (x_pad, "%*.*s", a_spacing, a_spacing, "0000000000");                                                                 <* 
 *>    debug_ystr   ylog_info    ("x_pad"     , x_pad);                                                                              <* 
 *>    /+---(handle zero)----------+/                                                                                                <* 
 *>    if (strcmp (b_out, "0") == 0) {                                                                                               <* 
 *>       strcpy   (b_out, x_pad);                                                                                                   <* 
 *>       debug_ystr   ylog_info    ("b_out"     , b_out);                                                                           <* 
 *>    }                                                                                                                             <* 
 *>    /+---(pad to spacing)-------+/                                                                                                <* 
 *>    x_len = strlen (b_out);                                                                                                       <* 
 *>    DEBUG_YSTR   yLOG_info    ("x_len"     , s_len);                                                                              <* 
 *>    n     = x_len % a_spacing;                                                                                                    <* 
 *>    DEBUG_YSTR   yLOG_info    ("n"         , n);                                                                                  <* 
 *>    if (n > 0) {                                                                                                                  <* 
 *>       for (i = a_spacing; i > n; --i)  strcat (x_padding, "0");                                                                  <* 
 *>       x_len = strlen (b_out) + strlen (x_padding);                                                                               <* 
 *>       DEBUG_YSTR   yLOG_sint    (x_len);                                                                                         <* 
 *>    }                                                                                                                             <* 
 *>    DEBUG_YSTR   yLOG_info    ("x_padding" , x_padding);                                                                          <* 
 *>    /+---(pad to a_cnt)---------+/                                                                                                <* 
 *>    for (i = x_len / a_spacing; i < a_cnt; ++i)  strcat (x_padding, x_pad);                                                       <* 
 *>    DEBUG_YSTR   yLOG_info    ("x_padding" , x_padding);                                                                          <* 
 *>    /+---(merge)----------------+/                                                                                                <* 
 *>    sprintf (x_temp, "%s%s", x_padding, b_out);                                                                                   <* 
 *>    DEBUG_YSTR   yLOG_info    ("x_temp"    , x_temp);                                                                             <* 
 *>    /+---(add separators)-------+/                                                                                                <* 
 *>    DEBUG_YSTR   yLOG_schar   (a_fmt);                                                                                            <* 
 *>    switch (a_fmt) {                                                                                                              <* 
 *>    case 'd' :  case 'c' :  case 'g' : ystr4_space_ints (a_spacing, '\'', x_temp); break;                                         <* 
 *>    case ':' :                         ystr4_space_ints (a_spacing, ':' , x_temp); break;                                         <* 
 *>    case 't' :  case '#' :             ystr4_space_ints (a_spacing, '·' , x_temp); break;                                         <* 
 *>    }                                                                                                                             <* 
 *>    DEBUG_YSTR   yLOG_info    ("x_temp"    , x_temp);                                                                             <* 
 *>    /+---(mearge)------------------+/                                                                                             <* 
 *>    sprintf (x_final, "%s%s", x_prefix, x_temp);                                                                                  <* 
 *>    DEBUG_YSTR   yLOG_info    ("x_final"    , x_final);                                                                           <* 
 *> }                                                                                                                                <*/


/*====================------------------------------------====================*/
/*===----                  convert number to string                    ----===*/
/*====================------------------------------------====================*/
static void      o___4BASES__________________o (void) {;}

char
ystrl4base              (ullong a_ullong, double a_double, char a_prefix [LEN_SHORT], char a_charset [LEN_HUND], char a_spacing, char a_cnt, char a_fmt, char a_max, char r_out [LEN_HUND])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_source    =  'd';
   int         x_base      =    0;
   int         i           =    0;
   char        x_digit     =    0;
   ullong      x_place     =    0;
   ullong      x_num       =    0;
   char        c           =    0;
   char        x_revs      [LEN_HUND]  = "";
   char        x_pad       [LEN_TERSE] = "";
   char        x_suffix    [LEN_HUND]  = "";
   int         x_len       =    0;
   char        x_flip      [LEN_HUND]  = "";
   char        x_final     [LEN_HUND]  = "";
   char        n           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_out     != NULL)   strcpy (r_out    , "");
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_point   ("a_prefix"  , a_prefix);
   --rce; if (a_prefix   == NULL) {
      DEBUG_YSTR   yLOG_note    ("a_prefix null");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("a_prefix"  , a_prefix);
   DEBUG_YSTR   yLOG_point   ("a_charset" , a_charset);
   --rce; if (a_charset  == NULL || a_charset [0] == '\0') {
      DEBUG_YSTR   yLOG_note    ("a_charset null/empty");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("a_charset" , a_charset);
   DEBUG_YSTR   yLOG_point   ("r_out"     , r_out);
   --rce; if (r_out      == NULL) {
      DEBUG_YSTR   yLOG_note    ("r_out null");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check charset)------------------*/
   x_base = strlen (a_charset);
   DEBUG_YSTR   yLOG_value   ("x_base"    , x_base);
   --rce;  if (x_base < 2) {
      DEBUG_YSTR   yLOG_note    ("base too small");
      ystrlcpy (r_out, "#p/bas", a_max);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_base >= LEN_HUND) {
      DEBUG_YSTR   yLOG_note    ("base too large");
      ystrlcpy (r_out, "#p/bas", a_max);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check inputs)-------------------*/
   DEBUG_YSTR   yLOG_ullong  ("a_ullong"  , a_ullong);
   DEBUG_YSTR   yLOG_double  ("a_double"  , a_double);
   --rce; if (a_ullong != 0 && a_double != 0) {
      DEBUG_YSTR   yLOG_note    ("a_ullong and a_double can not both be used");
      ystrlcpy (r_out, "#p/inp", a_max);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_source == 'd' && a_double < 0.0) {
      DEBUG_YSTR   yLOG_note    ("a_double can not be negative");
      ystrlcpy (r_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_ullong != 0)  x_source = 'l';
   DEBUG_YSTR   yLOG_char    ("x_source"  , x_source);
   /*---(prepare)------------------------*/
   if (x_source == 'd')  x_num = (ullong) a_double;
   else                  x_num = a_ullong;
   DEBUG_YSTR   yLOG_ullong  ("x_num"     , x_num);
   /*---(translate base)-----------------*/
   while (x_num > 0) {
      x_digit = x_num % x_base;
      x_revs [x_place++] = a_charset [x_digit];
      x_revs [x_place  ] = '\0';
      x_num /= x_base;
      ++c;
      DEBUG_YSTR   yLOG_complex ("update"    , "%2dd, %2dc, %llup, %llu", x_digit, c, x_place, x_final);
   }
   DEBUG_YSTR   yLOG_info    ("x_revs"    , x_revs);
   /*---(create pad)---------------------*/
   sprintf (x_pad, "%*.*s", a_spacing, a_spacing, "0000000000");
   DEBUG_YSTR   yLOG_info    ("x_pad"     , x_pad);
   /*---(handle zero)--------------------*/
   if (strcmp (x_revs, "") == 0) {
      if (a_fmt != ',')   strcpy   (x_revs, x_pad);
      else                strcpy   (x_revs, "0");
      DEBUG_YSTR   yLOG_info    ("x_revs"    , x_revs);
   }
   /*---(pad to spacing)-----------------*/
   x_len = strlen (x_revs);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   if (a_fmt != ',') {
      n     = x_len % a_spacing;
      DEBUG_YSTR   yLOG_value   ("n"         , n);
      if (n > 0) {
         DEBUG_YSTR   yLOG_note    ("padding small value");
         for (i = a_spacing; i > n; --i) {
            if (a_fmt != '.')  strcat (x_revs  , "0");
            else               strcat (x_suffix, "0");
         }
         x_len = strlen (x_revs);
         DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
      }
      DEBUG_YSTR   yLOG_info    ("x_revs"    , x_revs);
   }
   /*---(pad to a_cnt)-------------------*/
   if (a_fmt != ',') {
      for (i = x_len / a_spacing; i < a_cnt; ++i) {
         DEBUG_YSTR   yLOG_value   ("i"         , i);
         if (a_fmt != '.')  strcat (x_revs  , x_pad);
         else               strcat (x_suffix, x_pad);
      }
      DEBUG_YSTR   yLOG_info    ("x_revs"    , x_revs);
      x_len = strlen (x_revs);
      DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   }
   /*---(flip)---------------------------*/
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   --x_len;
   for (i = x_len; i >= 0; --i)  {
      /*> DEBUG_YSTR   yLOG_complex ("flip"      , "%c %3d>%3d %s", x_revs [i], i, x_len - i, x_flip);   <*/
      x_flip [x_len - i] = x_revs [i];
   }
   x_flip [++x_len] = '\0';
   DEBUG_YSTR   yLOG_info    ("x_flip"    , x_flip);
   if (a_fmt == '.') {
      strcat (x_flip, x_suffix);
      x_len = strlen (x_flip);
      DEBUG_YSTR   yLOG_info    ("x_flip"    , x_flip);
      DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   }
   /*---(add separators)-----------------*/
   DEBUG_YSTR   yLOG_char    ("a_fmt"     , a_fmt);
   switch (a_fmt) {
   case 'd'  :  case 'c'  :  case 'g'  : ystr4_space_ints (a_spacing, '\'', x_flip); break;
   case ':'  :                           ystr4_space_ints (a_spacing, ':' , x_flip); break;
   case 't'  :  case '#'  :              ystr4_space_ints (a_spacing, '·' , x_flip); break;
   case ','  :                           ystr4_space_ints (a_spacing, ',' , x_flip); break;
   case '.'  :                           ystr4_space_ints (a_spacing, '\'', x_flip); break;
   }
   /*---(tech version)-------------------*/
   if (a_fmt == '#') {
      if      (x_base == 2)  ystrldchg (x_flip, '0', '∑', LEN_HUND);
      else if (x_base != 10) {
         x_len = strlen (x_flip);
         for (i = 0; i < x_len; ++i) {
            if (strchr ("':·", x_flip [i]) != NULL)  continue;
            if (x_flip [i] != '0')                   break;;
            x_flip [i] = '∑';
         }
      }
   }
   /*---(add prefix)---------------------*/
   sprintf (x_final, "%s%s", a_prefix, x_flip);
   DEBUG_YSTR   yLOG_info    ("x_final"    , x_final);
   /*---(check length)-------------------*/
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len >= a_max) {
      DEBUG_YSTR   yLOG_note    ("output longer than a_max");
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_out   != NULL)  ystrlcpy (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ystrl4bool              (ullong a_ullong, double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE])
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
      case 'Y' :   strcpy  (r_out, "⁄");    break;
      case 'y' :   strcpy  (r_out, "∑");    break;
      }
   } else if (a_val < 0) {
      switch (a_fmt) {
      case 'Y' :   strcpy  (r_out, "€");    break;
      case 'y' :   strcpy  (r_out, "t");    break;
      }
   } else {
      switch (a_fmt) {
      case 'Y' :   strcpy  (r_out, "€");    break;
      case 'y' :   strcpy  (r_out, "T");    break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

/*    0000·0011∑∑1000·1101∑∑0111·1110∑∑1010·0100∑∑1100·0110∑∑0111·1111∑∑1111·1111  */
/*    0000·0011∑∑1000·1101∑∑0111·1110∑∑1010·0100∑∑1100·0110∑∑0111·1111∑∑1111·1111  */

char         /*-> format binary numbers to string ---------[ petal  [ 2f---- ]*/
ystrl4bin           (ullong a_ullong, double a_double, char a_cnt, char a_fmt, char a_max, char r_out [LEN_HUND])
{ 
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_prefix    [LEN_SHORT] = "";
   int         l           =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr4_defense  (TYPE_BIN, 'È', a_ullong, a_double, a_fmt, a_max, NULL, x_prefix, r_out);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = ystrl4base (a_ullong, a_double, x_prefix, YSTR_BINARY, 4, a_cnt, a_fmt, a_max, r_out);
   DEBUG_YSTR   yLOG_value   ("ystr4base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)------------*/
   DEBUG_YSTR   yLOG_info    ("r_out"     , r_out);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> format octal numbers to string ----------[ petal  [ 2f---- ]*/
ystrl4oct               (ullong a_ullong, double a_double, char a_cnt, char a_fmt, char a_max, char r_out [LEN_DESC])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_prefix    [LEN_SHORT] = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr4_defense  (TYPE_OCT, 'ˆ', a_ullong, a_double, a_fmt, a_max, NULL, x_prefix, r_out);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate base)-------*/
   rc = ystrl4base (a_ullong, a_double, x_prefix, YSTR_OCTAL , 3, a_cnt, a_fmt, a_max, r_out);
   DEBUG_YSTR   yLOG_value   ("ystr4base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)------------*/
   DEBUG_YSTR   yLOG_info    ("r_out"     , r_out);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ystrl4int               (ullong a_ullong, double a_double, char a_cnt, char a_fmt, char a_max, char r_out [LEN_DESC])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_prefix    [LEN_SHORT] = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr4_defense  (TYPE_INT,  0 , a_ullong, a_double, a_fmt, a_max, NULL, x_prefix, r_out);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate base)-------*/
   rc = ystrl4base (a_ullong, a_double, x_prefix, YSTR_NUMBER, 3, a_cnt, a_fmt, a_max, r_out);
   DEBUG_YSTR   yLOG_value   ("ystr4base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)------------*/
   DEBUG_YSTR   yLOG_info    ("r_out"     , r_out);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
ystrl4hex           (ullong a_ullong, double a_double, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;               /* return code for errors    */
   char        rc          =    0;
   char        x_prefix    [LEN_SHORT] = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr4_defense  (TYPE_HEX, 'ı', a_ullong, a_double, a_fmt, a_max, NULL, x_prefix, r_out);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(translate base)-------*/
   rc = ystrl4base (a_ullong, a_double, x_prefix, YSTR_HEX   , 4, a_cnt, a_fmt, a_max, r_out);
   DEBUG_YSTR   yLOG_value   ("ystr4base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)------------*/
   DEBUG_YSTR   yLOG_info    ("r_out"     , r_out);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ystrl4mongo         (ullong a_ullong, double a_double, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_prefix    [LEN_SHORT] = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr4_defense  (TYPE_MONGO, 'Ì', a_ullong, a_double, a_fmt, a_max, NULL, x_prefix, r_out);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = ystrl4base (a_ullong, a_double, x_prefix, YSTR_MONGO , 4, a_cnt, a_fmt, a_max, r_out);
   DEBUG_YSTR   yLOG_value   ("ystr4base" , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)------------*/
   DEBUG_YSTR   yLOG_info    ("r_out"     , r_out);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                  convert number to string                    ----===*/
/*====================------------------------------------====================*/
static void      o___4SPECIAL________________o (void) {;}

char
ystrl4roman         (ullong a_ullong, double a_double, char a_decs, char a_fmt, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         x_int       =    0;
   char        x_final     [LEN_TITLE] = "";
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr4_defense  (TYPE_ROMAN,  0 , a_ullong, a_double, a_fmt, a_max, NULL, NULL, r_out);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   if (a_ullong > 0)  x_int = a_ullong;
   else               x_int = (int) a_double;
   DEBUG_YSTR   yLOG_value   ("x_int"     , x_int);
   /*---(quick out for zero)-------------*/
   if (x_int == 0) {
      DEBUG_YSTR   yLOG_note    ("handling zero");
      if (a_fmt == 'r')  ystrlcpy (r_out, "n", a_max);
      else               ystrlcpy (r_out, "N", a_max);
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(prepare)------------------------*/
   for (i = 0; i < LEN_DESC; ++i) {
      if (S_roman [i].r_wide == 0)   break;
      DEBUG_YSTR   yLOG_value   ("x_int"     , x_int);
      if (x_int - S_roman [i].r_value >= 0) {
         DEBUG_YSTR   yLOG_info    ("found"     , S_roman [i].r_chars);
         ystrlcat (x_final, S_roman [i].r_chars, LEN_TITLE);
         x_int -= S_roman [i].r_value;
      }
   }
   DEBUG_YSTR   yLOG_info    ("x_final"   , x_final);
   DEBUG_YSTR   yLOG_value   ("x_int"     , x_int);
   --rce;  if (x_int != 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(overflow)-----------------------*/
   DEBUG_YSTR   yLOG_value   ("a_max"     , a_max);
   x_len = strlen (x_final);
   DEBUG_YSTR   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len > a_max) {
      ystrlcpy (r_out, "#p/max", a_max);
      DEBUG_YSTR   yLOG_note    ("too long");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handgle lower case)-------------*/
   if (a_fmt == 'r') {
      for (i = 0; i < x_len; ++i)  x_final [i] = tolower (x_final [i]);
      DEBUG_YSTR   yLOG_info    ("x_final"   , x_final);
   }
   /*---(save-back)----------------------*/
   if (r_out  != NULL)  ystrlcpy  (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                  convert number to string                    ----===*/
/*====================------------------------------------====================*/
static void      o___4REALS__________________o (void) {;}

char
ystr4_divide            (double a_source, char a_decs, char a_unit, char a_max, char *r_sign, llong *r_int, llong *r_dec, llong *r_exp, char r_unit [LEN_SHORT], char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_sign      =    1;
   double      x_scaled    =  0.0;             /* scaled version                 */
   char        x_unit      [LEN_SHORT] = "";
   int         i           =    0;
   llong       x_pow       =    1;             /* exponent to round off          */
   double      x_round     =  0.0;             /* rounded off value              */
   llong       x_int       =    0;             /* integer part                   */
   llong       x_dec       =    0;             /* fractional part                */
   llong       x_exp       =    0;             /* exponent part                  */
   /*---(default)------------------------*/
   if (r_sign  != NULL)  *r_sign = 0;
   if (r_int   != NULL)  *r_int  = 0;
   if (r_dec   != NULL)  *r_dec  = 0;
   if (r_exp   != NULL)  *r_exp  = 0;
   if (r_unit  != NULL)  strcpy (r_unit, "");
   if (r_out   != NULL)  strcpy (r_out , "");
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(set sign)-----------------------*/
   DEBUG_YSTR   yLOG_double  ("a_source"  , a_source);
   if (a_source < 0.0)    x_sign  = -1;
   DEBUG_YSTR   yLOG_value   ("x_sign"    , x_sign);
   /*---(scale full number)--------------*/
   DEBUG_YSTR   yLOG_char    ("a_unit"    , a_unit);
   --rce;  if (a_decs < 0 || a_decs > 9) {
      DEBUG_YSTR   yLOG_note    ("a_decs out of range (0-9)");
      if (r_out != NULL)  ystrlcpy (r_out, "#p/dec", a_max);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_scaled = a_source;
   rc = ystr4unit (a_unit, &x_scaled);
   DEBUG_YSTR   yLOG_value   ("units"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_note    ("a_unit not understood");
      if (r_out != NULL)  ystrlcpy (r_out, "#p/uni", a_max);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save unit)----------------------*/
   if      (a_unit == '-')   strcpy  (x_unit, "");
   else if (a_unit == '.')   sprintf (x_unit, "%c", G_CHAR_BIGDOT);
   else                      sprintf (x_unit, "%c", a_unit);
   DEBUG_YSTR   yLOG_info    ("x_unit"    , x_unit);
   /*---(parse out)----------------------*/
   for (i = 0; i < a_decs; ++i)  x_pow *= 10;
   DEBUG_YSTR   yLOG_llong   ("x_pow"     , x_pow);
   x_round  = round (x_scaled * x_sign * x_pow);
   DEBUG_YSTR   yLOG_double  ("x_round"   , x_round);
   x_int    = x_round / x_pow;
   DEBUG_YSTR   yLOG_llong   ("x_int"     , x_int);
   x_dec    = x_round - (x_int * x_pow);
   DEBUG_YSTR   yLOG_llong   ("x_dec"     , x_dec);
   /*---(save-back)----------------------*/
   if (r_sign  != NULL)  *r_sign = x_sign;
   if (r_int   != NULL)  *r_int  = x_int;
   if (r_dec   != NULL)  *r_dec  = x_dec;
   if (r_exp   != NULL)  *r_exp  = x_exp;
   if (r_unit  != NULL)  strcpy (r_unit, x_unit);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ystrl4float             (ullong a_ullong, double a_double, char a_decs, char a_fmt, char a_unit, char a_max, char r_out [LEN_TITLE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   double      x_source    =  0.0;
   char        x_sign      =    0;
   char        x_decs      =    0;
   llong       x_int       =    0;             /* integer part                   */
   llong       x_dec       =    0;             /* fractional part                */
   char        x_unit      [LEN_SHORT] = "";
   char        x_left      [LEN_TITLE] = "";
   char        x_right     [LEN_TITLE] = "";
   char        x_final     [LEN_TITLE] = "";
   int         i           =    0;
   int         l           =    0;
   char        x_sigs      =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = ystr4_defense  (TYPE_FLOAT,  0 , a_ullong, a_double, a_fmt, a_max, NULL, NULL, r_out);
   DEBUG_YSTR   yLOG_value   ("defense"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_char    ("a_fmt"     , a_fmt);
   /*---(prepare)------------------------*/
   if (a_ullong > 0)  x_source = (double)  a_ullong;
   else               x_source = a_double;
   if (strchr ("iI", a_fmt) != NULL)  x_decs = 0;
   else                               x_decs = a_decs;
   /*---(divide)-------------------------*/
   DEBUG_YSTR   yLOG_char    ("a_unit"    , a_unit);
   rc = ystr4_divide (x_source, x_decs, a_unit, a_max, &x_sign, &x_int, &x_dec, NULL, x_unit, r_out);
   DEBUG_YSTR   yLOG_value   ("divide"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prefix)-------------------------*/
   if (a_fmt == '$')  ystrlcpy (x_final, "$", LEN_TITLE);
   DEBUG_YSTR   yLOG_info    ("pre-prefix", x_final);
   /*---(pre-sign)-----------------------*/
   if (x_sign < 0) {
      if      (strchr ("iIfF,sSpP", a_fmt) != NULL)  ystrlcat (x_final, "-", LEN_TITLE);
      else if (strchr ("aA"       , a_fmt) != NULL)  ystrlcat (x_final, "(", LEN_TITLE);
   } else {
      if      (strchr ("sS"       , a_fmt) != NULL)  ystrlcat (x_final, "+", LEN_TITLE);
   }
   DEBUG_YSTR   yLOG_info    ("pre-sign"  , x_final);
   /*---(create left/integer)------------*/
   sprintf (x_left , "%lld", x_int);
   x_sigs += strlen (x_left);
   DEBUG_YSTR   yLOG_value   ("x_sigs"    , x_sigs);
   if  (strchr ("if", a_fmt) == NULL)  ystr4_space_ints (3, ',' , x_left);
   ystrlcat (x_final, x_left, LEN_TITLE);
   DEBUG_YSTR   yLOG_info    ("left"      , x_final);
   /*---(add decimal)--------------------*/
   if (strchr ("iI" , a_fmt) == NULL && a_decs > 0) {
      if (strchr ("cC" , a_fmt) != NULL)  ystrlcat (x_final, "Å", LEN_TITLE);
      else                                ystrlcat (x_final, ".", LEN_TITLE);
      DEBUG_YSTR   yLOG_info    ("decimal"   , x_final);
   }
   /*---(create right/decimals)----------*/
   DEBUG_YSTR   yLOG_value   ("a_decs"    , a_decs);
   if (strchr ("iI" , a_fmt) == NULL && a_decs > 0) {
      sprintf (x_right, "%lld", x_dec);
      x_sigs += strlen (x_right);
      l      = strlen (x_right);
      for (i = l - 1; i > 0; --i) {
         if (strchr (YSTR_NUMBER, x_right [i]) != NULL)  break;
         --x_sigs;
      }
      if  (strchr ("if", a_fmt) == NULL)  ystr4_space_decs (3, '\'', x_right);
      ystrlcat (x_final, x_right, LEN_TITLE);
      DEBUG_YSTR   yLOG_info    ("right"     , x_final);
   }
   /*---(check on sigs)------------------*/
   DEBUG_YSTR   yLOG_value   ("x_sigs"    , x_sigs);
   --rce;  if (x_sigs > 15) {
      DEBUG_YSTR   yLOG_note    ("double overflow");
      if (r_out != NULL)  ystrlcpy (r_out, "#p/ovr", a_max);
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(units)--------------------------*/
   ystrlcat (x_final, x_unit, LEN_TITLE);
   DEBUG_YSTR   yLOG_info    ("units"     , x_final);
   /*---(post-sign)----------------------*/
   if (x_sign < 0) {
      if      (strchr ("aA$", a_fmt) != NULL)  ystrlcat (x_final, ")" , LEN_TITLE);
      else if (strchr ("cC#", a_fmt) != NULL)  ystrlcat (x_final, "∑-", LEN_TITLE);
   } else {
      if      (strchr ("aA$", a_fmt) != NULL)  ystrlcat (x_final, "∑" , LEN_TITLE);
      else if (strchr ("cC#", a_fmt) != NULL)  ystrlcat (x_final, "∑+", LEN_TITLE);
   }
   if      (a_fmt == 'p') ystrlcat (x_final, ")", LEN_TITLE);
   else if (a_fmt == 'P') ystrlcat (x_final, "¥", LEN_TITLE);
   DEBUG_YSTR   yLOG_info    ("post-sign" , x_final);
   /*---(integer suffix padding)---------*/
   if (strchr ("iI" , a_fmt) != NULL) {
      for (i = 0; i <  a_decs; ++i)    ystrlcat (x_final, "∑", LEN_TITLE);
      if (                a_decs > 0)  ystrlcat (x_final, "∑", LEN_TITLE); /* for decimal point */
      if (a_fmt == 'I' && a_decs > 3)  ystrlcat (x_final, "∑", LEN_TITLE);
      if (a_fmt == 'I' && a_decs > 6)  ystrlcat (x_final, "∑", LEN_TITLE);
      DEBUG_YSTR   yLOG_info    ("padded"    , x_final);
   }
   /*---(save-back)----------------------*/
   DEBUG_YSTR   yLOG_info    ("x_final"   , x_final);
   if (r_out  != NULL)  ystrlcpy (r_out, x_final, LEN_TITLE);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> format hexadecimal numbers to string ----[ petal  [ 2f---- ]*/
ystrl4comma         (ullong a_ullong, double a_double, char a_decs, char a_fmt, char a_unit, char a_max, char r_out [LEN_TITLE])
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

   if (a_double < 0.0)    x_sign  = -1;
   if (a_fmt == '?')   a_fmt   = 'i';
   if (a_fmt == 'i')   a_decs  =  0;
   /*---(scale)--------------------------*/
   x_scaled = a_double;
   rc = ystr4unit (a_unit, &x_scaled);
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
      case 'P' :                       strcat (x_final, "¥");  break;
      case '#' :                       strcat (x_final, " -"); break;
      }
   } else {
      switch (a_fmt) {
      case 'a' : case 'A' : case '$' : strcat (x_final, "_");  break;
      case 'p' :                       strcat (x_final, ")");  break;
      case 'P' :                       strcat (x_final, "¥");  break;
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
ystrl4sci           (ullong a_ullong, double a_double, char a_decs, char a_fmt, char a_max, char r_out [LEN_TITLE])
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
   if (a_double < 0.0)  x_sign  = -1;
   DEBUG_YSTR   yLOG_schar   (a_fmt);
   --rce;  if (strchr ("eE", a_fmt) == NULL) {
      ystrlcpy (r_out, "#p/fmt", a_max);
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)---------------------*/
   if (a_double < 0.0)  x_sign  = -1;
   if (a_decs == 0)  a_decs  =  1;
   strcpy  (x_final, "");
   /*---(make prefix)-----------------*/
   if (x_sign < 0)          strcpy (x_final, "-");
   else if (a_fmt == 'E')   strcpy (x_final, "+");
   sprintf (x_temp, "%.*e", a_decs, a_double * x_sign);
   strncat (x_final, x_temp, 2);
   /*---(save exponent/suffix)--------*/
   if (a_fmt == 'E')  strcpy  (x_suffix, x_temp + a_decs + 2);
   else               sprintf (x_suffix, "À%d", atoi (x_temp + a_decs + 3));
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
   ystrldchg (x_final, 'e', 'À', a_max);
   ystrldchg (x_final, 'E', 'À', a_max);
   ystrlcpy  (r_out, x_final, a_max);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

/*
 *   ˙:
 *
 *   midnight      23-01    mi     7   i   midn
 *   graveyard     02-04    gr     0   g   grav
 *   dawn          05-07    dw     1   d   dawn
 0   morning       08-10    mo     2   m   morn
 *   noon          11-13    oo     3   o   noon
 *   afternoon     14-16    af     4   a   aftr
 *   dusk          17-19    sk     5   u   dusk
 *   evening       20-22    ev     6   e   evng
 *
 *   yyyy mm dd hh mm ss shft w wy doy
 *   2245.07.04.12.00.00.3/oo.5.26.185
 *
 *   year mo dy hr mi se w wy doy shift-
 *
 *   ˙'2245.07.04.12.00.00.5.26.185.3/noon    2245 jul 07 12:00:00 th, 26woy
 *
 *   123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-
 *   2245.07.04.5.12.00.00.3.26.185 ß 2245 jul 07 (th) 12:00 (noon), 26woy, 185doy ß
 *
 *   2245.07.04.12.00.00.5.26.185.3o
 *   45.07.04.12.00.00.5.26.185
 *
 */

char         /*-> format times into strings ---------------[ petal  [ 2f---- ]*/
ystrl4time          (ullong a_ullong, double a_double, char a_decs, char a_fmt, char a_max, char r_out [LEN_TITLE])
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
   DEBUG_YSTR   yLOG_sint    (a_double);
   --rce;  if (a_double < 0) {
      ystrlcpy (r_out, "#p/neg", a_max);
      DEBUG_YSTR   yLOG_snote   ("epoch number negative");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle time/date formats)-------*/
   x_now  = (long) a_double;
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

char
ystrl4main          (ullong a_ullong, double a_double, char a_bytes, char a_fmt, char a_unit, char a_max, char r_out [LEN_TITLE])
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
   switch (tolower (a_fmt)) {
   case 'y' : case 'Y' :
      rc = ystrl4bool  (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case TYPE_BIN :
      rc = ystrl4bin   (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case TYPE_OCT :
      rc = ystrl4oct   (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case TYPE_HEX :
      rc = ystrl4hex   (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case TYPE_MONGO :
      rc = ystrl4mongo (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case 'e' : case 'E' :
      rc = ystrl4sci   (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   case TYPE_ROMAN :
      rc = ystrl4roman (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);
      break;
      break;
   case 'd' : case 't' : case 'D' : case 'T' :
      rc = ystrl4time  (a_ullong, a_double, a_bytes, a_fmt, a_max, r_out);
      break;
   default :
      rc = ystrl4comma (a_ullong, a_double, a_bytes, a_fmt, a_unit, a_max, r_out);
      break;
   }
   /*---(complete)-----------------------*/
   return rc;
}

char*
ystrl4quick             (double a_double, char a_ali, char a_fmt, char a_cnt, char a_uom, char a_fil, char a_zer, char a_neg, char a_max)
{
   char        rc          =    0;
   char        t           [LEN_HUND]  = "";
   static char x_print     [LEN_HUND]  = "";
   if      (a_zer != ' ' && a_double == 0.0)  sprintf (t, "%c", a_zer);
   else if (a_neg != ' ' && a_double <  0.0)  sprintf (t, "%c", a_neg);
   else    rc = ystrl4main (NULL, a_double, a_cnt, a_fmt, a_uom, a_max + 1, t);
   rc = ystrlpad   (t, x_print, a_fil, a_ali, a_max);
   return x_print;
}



/*====================------------------------------------====================*/
/*===----                       bit related                            ----===*/
/*====================------------------------------------====================*/
static void      o___SPECIALIZED_____________o (void) {;}

char
ystrlsigs               (char a_charset [LEN_HUND], char a_dels [LEN_TERSE], char a_sigs, char a_mask, char a_max, char b_out [LEN_HUND])
{
   char        rce         =  -10;
   int         l           =    0;
   int         i           =    0;
   char        x_sigs      =    0;
   /*---(desfense)-----------------------*/
   --rce;  if (a_charset == NULL)  return rce;
   --rce;  if (a_dels    == NULL)  return rce;
   --rce;  if ((uchar) a_mask    <  32)    return rce;
   --rce;  if ((uchar) a_mask    == 127)   return rce;
   --rce;  if (b_out     == NULL)  return rce;
   /*---(range limits)-------------------*/
   if      (a_sigs <  0)  a_sigs = 100;
   /*---(prepare)------------------------*/
   l = strlen (b_out);
   /*> if (l > a_max)  l = a_max;                                                     <*/
   /*---(walk string)--------------------*/
   for (i = 0; i < l; ++i) {
      if (strchr (a_charset, b_out [i]) != NULL) {
         if (i < a_max && x_sigs >= a_sigs)  b_out [i] = a_mask;
         ++x_sigs;
      }
      if (i < a_max && x_sigs >= a_sigs && strchr (a_dels, b_out [i]) != NULL)  b_out [i] = a_mask;
   }
   /*---(complete)-----------------------*/
   return x_sigs;
}

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


