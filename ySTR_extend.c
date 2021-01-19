/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



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

char
strl__leet         (char a_dir, char *a_src, int a_max)
{
   int         i           =    0;
   char       *p           = NULL;
   char        c           =  '-';
   char       *x_1st       = "abcdefghijklmnopqrstuvwxyz";
   char       *x_2nd       = "46()3[&#!;<1-=0+9~57_|8*?2";
   char       *x_3rd       = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   for (i = 0; i < a_max; ++i) {
      c = a_src [i];
      if (c == '\0')  break;
      if      ((p = strchr (x_1st, c)) != NULL) {
         if (a_dir == '>')  a_src [i] = x_2nd [p - x_1st];
         else               a_src [i] = x_3rd [p - x_1st];
      }
      else if ((p = strchr (x_2nd, c)) != NULL) {
         if (a_dir == '>')  a_src [i] = x_3rd [p - x_2nd];
         else               a_src [i] = x_1st [p - x_2nd];
      }
      else if ((p = strchr (x_3rd, c)) != NULL) {
         if (a_dir == '>')  a_src [i] = x_1st [p - x_3rd];
         else               a_src [i] = x_2nd [p - x_3rd];
      }
   }
   return 0;
}

char strl2leet (char *a_src, int a_max) { return strl__leet ('>', a_src, a_max); }
char strl4leet (char *a_src, int a_max) { return strl__leet ('<', a_src, a_max); }

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
   case 'd'  : x_ch = G_CHAR_DEL       ;  break;    /*   100 d = 190 ¾   */
   case 'b'  : x_ch = G_CHAR_BS        ;  break;    /*    98 b = 191 ¿   */
               /*---(macro)---------------------*/
   case '+'  : x_ch = G_CHAR_DISPLAY   ;  break;    /*    43 + = 169 ©   */
   case '.'  : x_ch = G_CHAR_BREAK     ;  break;    /*    46 . = 170 ª   */
   case ','  : x_ch = G_CHAR_WAIT      ;  break;    /*    44 , = 171 «   */
   case 'q'  : x_ch = G_CHAR_HALT      ;  break;    /*   113 q = 179 ³   */
   case '\'' : x_ch = G_CHAR_BIGDOT    ;  break;    /*    39 ' = 207 ´   */
   case '@'  : x_ch = G_CHAR_HUGEDOT   ;  break;    /*    64 @ = 180 Ï   */
               /*---(special)-------------------*/
   case ' '  : x_ch = G_CHAR_STORAGE   ;  break;    /*    32   = 178 ²   */
   case '*'  : x_ch = G_CHAR_MASK      ;  break;    /*    42 * = 172 ¬   */
   case 't'  : x_ch = G_CHAR_TAB       ;  break;    /*   116 t = 173 ­   */
   case ':'  : x_ch = G_CHAR_SUMMARY   ;  break;    /*    58 : = 174 ®   */
   case '%'  : x_ch = G_CHAR_SYSTEM    ;  break;    /*    37 % = 175 ¯   */
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
   case 'a'  : x_ch = G_CHAR_DEGREE    ;  break;    /*    97 a = 204 Ì   */
   case 'r'  : x_ch = G_CHAR_RADIAN    ;  break;    /*   114 r = 205 Í   */
   case '1'  : x_ch = G_CHAR_SQRT      ;  break;    /*    49 1 = 206 Î   */
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
   case '/'  : x_ch = G_CHAR_NE        ;  break;    /*    61 / = 223 ß   */
   case '='  : x_ch = G_CHAR_EQUIV     ;  break;    /*    47 = = 229 å   */
   case '~'  : x_ch = G_CHAR_APPROX    ;  break;    /*   126 ~ = 230 æ   */
   case '$'  : x_ch = G_CHAR_RANGE     ;  break;    /*    36 $ = 177 ±   */
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

uchar        /*--> convert backslashed characters --------[ ------ [ ------ ]-*/
chrslashed_more   (char a_ch)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_ch        = a_ch;
   /*--- phoenicia/shrike mapping -------------*/
   switch (x_ch) {
      /*---(notes)---------------------*/
   case 't'  : x_ch = G_CHAR_BECAUSE;   break;
   case 'a'  : x_ch = G_CHAR_FOREACH;   break;
   case 'r'  : x_ch = G_CHAR_RESISTS;   break;
   case 'i'  : x_ch = G_CHAR_IMPLIES;   break;
   case 'p'  : x_ch = G_CHAR_PROVES;    break;
   case 'f'  : x_ch = G_CHAR_FORCES;    break;
   case 'c'  : x_ch = G_CHAR_CONTRA;    break;
   case 'j'  : x_ch = G_CHAR_UNION;     break;
   case 'k'  : x_ch = G_CHAR_INTERSECT; break;
   case 'h'  : x_ch = G_CHAR_SUBSET;    break;
   case 'l'  : x_ch = G_CHAR_SUPERSET;  break;
   case 'm'  : x_ch = G_CHAR_MEMBER;    break;
   case 'o'  : x_ch = G_CHAR_ONLYIF;    break;
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


