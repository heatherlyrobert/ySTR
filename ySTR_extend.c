/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"

\

struct {
   char        prefix;
   char        base;
   uchar       trans;
} zSTR_extend [LEN_FULL] = {
   /*---(control)-------------------*/
   { 1 , '-' , G_KEY_FIELD      },  /*     */
   /*---(notes)---------------------*/
   { 1 , '!' , G_CHAR_REXCLAM   },  /*   ¢   */
   { 1 , '?' , G_CHAR_RQUEST    },  /*   °   */
   /*---(hidden)--------------------*/
   { 1 , '0' , G_CHAR_NULL      },  /*   £   */
   { 1 , 'p' , G_CHAR_PLACE     },  /*   §   */
   { 1 , 'e' , G_CHAR_ESCAPE    },  /*   •   */
   { 1 , 'n' , G_CHAR_RETURN    },  /*   ¶   */
   { 1 , 'f' , G_CHAR_FIELD     },  /*   ß   */
   { 1 , 'g' , G_CHAR_GROUP     },  /*   ®   */
   { 1 , 'd' , G_CHAR_DEL       },  /*   æ   */
   { 1 , 'b' , G_CHAR_BS        },  /*   ø   */
   /*---(macro)---------------------*/
   { 1 , '+' , G_CHAR_DISPLAY   },  /*   ≠   */
   { 1 , '.' , G_CHAR_BREAK     },  /*   ™   */
   { 1 , ',' , G_CHAR_WAIT      },  /*   ´   */
   { 1 , 'q' , G_CHAR_HALT      },  /*   ≥   */
   { 1 , '\'', G_CHAR_BIGDOT    },  /*   ¥   */
   { 1 , '@' , G_CHAR_HUGEDOT   },  /*   œ   */
   /*---(special)-------------------*/
   { 1 , ' ' , G_CHAR_STORAGE   },  /*   ≤   */
   { 1 , '*' , G_CHAR_MASK      },  /*   ¨   */
   { 1 , ':' , G_CHAR_SUMMARY   },  /*   Æ   */
   { 1 , '%' , G_CHAR_SYSTEM    },  /*   Ø   */
   { 1 , 't' , G_CHAR_POINT     },  /*   ·   */
   /*---(delayed)-------------------*/
   { 1 , '\\', G_CHAR_DBSLASH   },  /*   µ   */
   { 1 , '"' , G_CHAR_DDQUOTE   },  /*   ∂   */
   { 1 , 's' , G_CHAR_SPACE     },  /*   ∑   */
   /*---(grouping)------------------*/
   { 1 , '(' , G_CHAR_SLPAREN   },  /*   ∏   */
   { 1 , ')' , G_CHAR_SRPAREN   },  /*   π   */
   { 1 , '[' , G_CHAR_SLBRACK   },  /*   ∫   */
   { 1 , ']' , G_CHAR_SRBRACK   },  /*   ª   */
   { 1 , '{' , G_CHAR_SLCHEV    },  /*   º   */
   { 1 , '}' , G_CHAR_SRCHEV    },  /*   Ω   */
   /*---(subscript)-----------------*/
   { 1 , '5' , G_CHAR_SUB0      },  /*   ¿   */
   { 1 , '6' , G_CHAR_SUB1      },  /*   ¡   */
   { 1 , '7' , G_CHAR_SUB2      },  /*   ¬   */
   { 1 , '8' , G_CHAR_SUB3      },  /*   √   */
   { 1 , '9' , G_CHAR_SUB4      },  /*   ƒ   */
   { 1 , 'z' , G_CHAR_SUBN      },  /*   ≈   */
   { 1 , '#' , G_CHAR_SCINOTE   },  /*   À   */
   /*---(superscript)---------------*/
   { 1 , '1' , G_CHAR_SQRT      },  /*   Œ   */
   { 1 , '2' , G_CHAR_POW2      },  /*   ∆   */
   { 1 , '3' , G_CHAR_POW3      },  /*   «   */
   { 1 , '4' , G_CHAR_POW4      },  /*   »   */
   { 1 , 'x' , G_CHAR_POWX      },  /*   …   */
   { 1 , 'y' , G_CHAR_POWY      },  /*       */
   { 1 , 'o' , G_CHAR_DEGREE    },  /*   Ã   */
   { 1 , 'r' , G_CHAR_RADIAN    },  /*   Õ   */
   /*---(logic)---------------------*/
   { 1 , '&' , G_CHAR_AND       },  /*   –   */
   { 1 , '|' , G_CHAR_OR        },  /*   —   */
   { 1 , 'i' , G_CHAR_XNOR      },  /*   ”   */
   { 1 , 'v' , G_CHAR_XOR       },  /*   “   */
   /*---(arrows)--------------------*/
   { 1 , 'k' , G_CHAR_UP        },  /*   ‘   */
   { 1 , 'j' , G_CHAR_DOWN      },  /*   ’   */
   { 1 , 'l' , G_CHAR_RIGHT     },  /*   ÷   */
   { 1 , 'h' , G_CHAR_LEFT      },  /*   ◊   */
   /*---(math)----------------------*/
   { 1 , '<' , G_CHAR_LE        },  /*   ‹   */
   { 1 , '>' , G_CHAR_GE        },  /*   ›   */
   { 1 , '=' , G_CHAR_EQUIV     },  /*   ‡   */
   { 1 , '/' , G_CHAR_NE        },  /*   ﬁ   */
   { 1 , '~' , G_CHAR_APPROX    },  /*   ﬂ   */
   { 1 , '$' , G_CHAR_RANGE     },  /*   ò   */
   /*---(greek)---------------------*/
   { 1 , 'A' , G_CHAR_ALPHA     },  /*   Ë   */
   { 1 , 'B' , G_CHAR_BETA      },  /*   È   */
   { 1 , 'G' , G_CHAR_GAMMA     },  /*   Í   */
   { 1 , 'D' , G_CHAR_DELTA     },  /*   Î   */
   { 1 , 'E' , G_CHAR_EPSILON   },  /*   Ï   */
   { 1 , 'Z' , G_CHAR_ZETA      },  /*   Ì   */
   { 1 , 'H' , G_CHAR_ETA       },  /*   Ó   */
   { 1 , 'Y' , G_CHAR_THETA     },  /*   Ô   */
   { 1 , 'I' , G_CHAR_IOTA      },  /*      */
   { 1 , 'K' , G_CHAR_KAPPA     },  /*   Ò   */
   { 1 , 'L' , G_CHAR_LAMBDA    },  /*   Ú   */
   { 1 , 'M' , G_CHAR_MU        },  /*   Û   */
   { 1 , 'N' , G_CHAR_NU        },  /*   Ù   */
   { 1 , 'X' , G_CHAR_XI        },  /*   ı   */
   { 1 , 'O' , G_CHAR_OMICRON   },  /*   ˆ   */
   { 1 , 'P' , G_CHAR_PI        },  /*   ˜   */
   { 1 , 'R' , G_CHAR_RHO       },  /*   ¯   */
   { 1 , 'S' , G_CHAR_SIGMA     },  /*   ˘   */
   { 1 , 'T' , G_CHAR_TAU       },  /*   ˙   */
   { 1 , 'U' , G_CHAR_UPSILON   },  /*   ˚   */
   { 1 , 'F' , G_CHAR_PHI       },  /*   ¸   */
   { 1 , 'C' , G_CHAR_CHI       },  /*   ˝   */
   { 1 , 'Q' , G_CHAR_PSI       },  /*   ˛   */
   { 1 , 'W' , G_CHAR_OMEGA     },  /*   ˇ   */
   /*---(notes)---------------------*/
   { 2 , '!' , G_CHAR_REDACT    },  /*   ∞   */
   /*---(logic)---------------------*/
   { 2 , 'c' , G_CHAR_FALSE     },  /*   ⁄   */
   { 2 , 'u' , G_CHAR_UNLIKELY  },  /*   €   */
   { 2 , 'l' , G_CHAR_LIKELY    },  /*   Ÿ   */
   { 2 , 't' , G_CHAR_TRUE      },  /*   ÿ   */
   { 2 , 'h' , G_CHAR_SUBSET    },  /*   ‚   */
   { 2 , 'm' , G_CHAR_MEMBER    },  /*   „   */
   /*---(useful)--------------------*/
   { 2 , 'i' , G_CHAR_INFINITY  },  /*   ô   */
   { 2 , 'f' , G_CHAR_FUNCTION  },  /*   ö   */
   { 2 , 'a' , G_CHAR_FOREACH   },  /*   ‰   */
   { 2 , 'e' , G_CHAR_EMPTY     },  /*   †   */
   { 2 , 'b' , G_CHAR_DSLASH    },  /*   õ   */
   { 2 , 'd' , G_CHAR_DIAMOND   },  /*   ©   */
   { 2 , 's' , G_CHAR_SUFFIX    },  /*   ±   */
   { 2 , 'r' , G_CHAR_RFIELD    },  /*   è   */
   { 2 , 'o' , G_CHAR_LOCAL     },  /*   Á   */
   /*---(string parens)-------------*/
   { 2 , '[' , G_CHAR_LGULL     },  /*   Â   */
   { 2 , ']' , G_CHAR_RGULL     },  /*   Ê   */
   /*---(line draw)-----------------*/
   { 2 , 'H' , 'Ä'              },
   { 2 , 'V' , 'Å'              },
   { 2 , '0' , 'å'              },
   { 2 , '1' , 'É'              },
   { 2 , '2' , 'â'              },
   { 2 , '3' , 'Ç'              },
   { 2 , '4' , 'á'              },
   { 2 , '5' , 'ä'              },
   { 2 , '6' , 'Ü'              },
   { 2 , '7' , 'Ñ'              },
   { 2 , '8' , 'à'              },
   { 2 , '9' , 'Ö'              },
   { 2 , 'D' , 'î'              },
   { 2 , 'U' , 'ï'              },
   { 2 , 'B' , 'ú'              },
   { 2 , 'T' , 'ù'              },
   { 2 , 'L' , 'û'              },
   { 2 , 'R' , 'ü'              },
   { 2 , 'S' , 'ê'              },
   { 2 , 'E' , 'ë'              },
   { 2 , 'M' , 'ç'              },
   { 2 , 'N' , 'é'              },
   { 2 , 'W' , 'í'              },
   { 2 , 'X' , 'ì'              },
   { 2 , 'Y' , 'ñ'              },
   { 2 , 'Z' , 'ó'              },
   /*---(done)----------------------*/
   { 0 ,  0  ,  0               },
};



/*====================------------------------------------====================*/
/*===----                     extended ascii                           ----===*/
/*====================------------------------------------====================*/
static void      o___EXTENDED________________o (void) {;}

char         /*--> encode special characters -------------[ ------ [ ------ ]-*/
ystrlstore          (char *a_src, int a_max)
{
   ystrldchg (a_src, G_KEY_SPACE, G_CHAR_STORAGE, a_max);
   return 0;
}

char         /*--> encode special characters -------------[ ------ [ ------ ]-*/
ystrlunstore        (char *a_src, int a_max)
{
   ystrldchg (a_src, G_CHAR_STORAGE, G_KEY_SPACE, a_max);
   return 0;
}

char         /*--> encode special characters -------------[ ------ [ ------ ]-*/
ystrlencode         (char *a_src, char a_mode, int a_max)
{
   /*---(normal)-------------------------*/
   ystrldchg (a_src, G_KEY_RETURN, G_CHAR_RETURN, a_max);
   ystrldchg (a_src, G_KEY_ESCAPE, G_CHAR_ESCAPE, a_max);
   ystrldchg (a_src, G_KEY_BS    , G_CHAR_BS    , a_max);
   ystrldchg (a_src, G_KEY_DEL   , G_CHAR_DEL   , a_max);
   ystrldchg (a_src, G_KEY_GROUP , G_CHAR_GROUP , a_max);
   ystrldchg (a_src, G_KEY_FIELD , G_CHAR_FIELD , a_max);
   /*---(big)----------------------------*/
   if (a_mode == ySTR_MAX) {
      ystrldchg (a_src, G_KEY_SPACE , G_CHAR_SPACE , a_max);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*--> decode special characters -------------[ ------ [ ------ ]-*/
ystrldecode         (char *a_src, int a_max)
{
   /*---(normal)-------------------------*/
   ystrldchg (a_src, G_CHAR_RETURN , G_KEY_RETURN, a_max);
   ystrldchg (a_src, G_CHAR_ESCAPE , G_KEY_ESCAPE, a_max);
   ystrldchg (a_src, G_CHAR_GROUP  , G_KEY_GROUP , a_max);
   ystrldchg (a_src, G_CHAR_FIELD  , G_KEY_FIELD , a_max);
   ystrldchg (a_src, G_CHAR_BS     , G_KEY_BS    , a_max);
   ystrldchg (a_src, G_CHAR_DEL    , G_KEY_DEL   , a_max);
   ystrldchg (a_src, G_CHAR_SPACE  , G_KEY_SPACE , a_max);
   ystrldchg (a_src, G_CHAR_NULL   , G_KEY_NULL  , a_max);
   /*---(complete)-----------------------*/
   return 0;
}

char
strl__leet         (char a_dir, char *a_src, int a_max)
{
   int         i           =    0;
   char       *p           = NULL;
   char        c           =  '-';
   for (i = 0; i < a_max; ++i) {
      c = a_src [i];
      if (c == '\0')  break;
      if      ((p = strchr (YSTR_LOWER, c)) != NULL) {
         if (a_dir == '>')  a_src [i] = YSTR_LEET  [p - YSTR_LOWER];
         else               a_src [i] = YSTR_UPPER [p - YSTR_LOWER];
      }
      else if ((p = strchr (YSTR_LEET , c)) != NULL) {
         if (a_dir == '>')  a_src [i] = YSTR_UPPER [p - YSTR_LEET ];
         else               a_src [i] = YSTR_LOWER [p - YSTR_LEET ];
      }
      else if ((p = strchr (YSTR_UPPER, c)) != NULL) {
         if (a_dir == '>')  a_src [i] = YSTR_LOWER [p - YSTR_UPPER];
         else               a_src [i] = YSTR_LEET  [p - YSTR_UPPER];
      }
   }
   return 0;
}

char ystrl2leet (char *a_src, int a_max) { return strl__leet ('>', a_src, a_max); }
char ystrl4leet (char *a_src, int a_max) { return strl__leet ('<', a_src, a_max); }

char         /*--> reverse delayed characters ------------[ ------ [ ------ ]-*/
ystrlundelay        (char *a_src, int a_max)
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
   ystrlrepl (a_src, t, dslash, 100, a_max);
   sprintf (t, "%c", G_CHAR_DDQUOTE);
   /*> printf ("    t [%s]\n", t);                                                    <*/
   /*> printf ("    c [%s]\n", dquote);                                               <*/
   ystrlrepl (a_src, t, dquote, 100, a_max);
   /*> printf ("    d [%s]\n", a_src);                                                <*/
   /*---(complete)-----------------------*/
   return 0;
}

uchar
ychr_slashed        (char a_slash, char a_ch)
{
   /*---(design notes)-------------------*/
   /*
    * reserved backslashes for special use...
    *   \a  alt
    *   \c  control
    *   \t  tab
    *   \w  wander
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        i           =    0;
   uchar       c           =    0;
   /*---(phoenicia/shrike mapping)-------*/
   for (i = 0; i < LEN_FULL; ++i) {
      if (zSTR_extend [i].base   == 0)        break;
      if (zSTR_extend [i].prefix != a_slash)  continue;
      if (zSTR_extend [i].base   != a_ch)     continue;
      c = zSTR_extend [i].trans;
      break;
   }
   if (c == 0)  c = G_CHAR_REDACT;
   /*---(complete)-----------------------*/
   return c;
   /*> switch (x_ch) {                                                                <* 
    *>    /+---(notes)---------------------+/                                         <* 
    *> case '-'  : x_ch = G_KEY_FIELD      ;  break;    /+    45 - =  31    +/       <* 
    *> case 'w'  : x_ch = G_KEY_SPACE      ;  break;    /+    45 w =  32    +/       <* 
    *> case '!'  : x_ch = G_CHAR_REXCLAM   ;  break;    /+    33 ! = 161 °   +/       <* 
    *> case '?'  : x_ch = G_CHAR_RQUEST    ;  break;    /+    63 ? = 162 ¢   +/       <* 
    *>             /+---(hidden)--------------------+/                                <* 
    *> case '0'  : x_ch = G_CHAR_NULL      ;  break;    /+    48 0 = 163 £   +/       <* 
    *> case 'p'  : x_ch = G_CHAR_PLACE     ;  break;    /+   112 p = 164 §   +/       <* 
    *> case 'e'  : x_ch = G_CHAR_ESCAPE    ;  break;    /+   101 e = 165 •   +/       <* 
    *> case 'n'  : x_ch = G_CHAR_RETURN    ;  break;    /+   110 n = 166 ¶   +/       <* 
    *> case 'f'  : x_ch = G_CHAR_FIELD     ;  break;    /+   102 f = 167 ß   +/       <* 
    *> case 'g'  : x_ch = G_CHAR_GROUP     ;  break;    /+   103 g = 168 ®   +/       <* 
    *> case 'd'  : x_ch = G_CHAR_DEL       ;  break;    /+   100 d = 190 æ   +/       <* 
    *> case 'b'  : x_ch = G_CHAR_BS        ;  break;    /+    98 b = 191 ø   +/       <* 
    *>             /+---(macro)---------------------+/                                <* 
    *> case '+'  : x_ch = G_CHAR_DISPLAY   ;  break;    /+    43 + = 169 ©   +/       <* 
    *> case '.'  : x_ch = G_CHAR_BREAK     ;  break;    /+    46 . = 170 ™   +/       <* 
    *> case ','  : x_ch = G_CHAR_WAIT      ;  break;    /+    44 , = 171 ´   +/       <* 
    *> case 'q'  : x_ch = G_CHAR_HALT      ;  break;    /+   113 q = 179 ≥   +/       <* 
    *> case '\'' : x_ch = G_CHAR_BIGDOT    ;  break;    /+    39 ' = 207 ¥   +/       <* 
    *> case '@'  : x_ch = G_CHAR_HUGEDOT   ;  break;    /+    64 @ = 180 œ   +/       <* 
    *>             /+---(special)-------------------+/                                <* 
    *> case ' '  : x_ch = G_CHAR_STORAGE   ;  break;    /+    32   = 178 ≤   +/       <* 
    *> case 'J'  : x_ch = G_CHAR_STORAGE   ;  break;    /+    32 J = 178 ≤   +/       <* 
    *> case '*'  : x_ch = G_CHAR_MASK      ;  break;    /+    42 * = 172 ¨   +/       <* 
    *> case ':'  : x_ch = G_CHAR_SUMMARY   ;  break;    /+    58 : = 174 Æ   +/       <* 
    *> case '%'  : x_ch = G_CHAR_SYSTEM    ;  break;    /+    37 % = 175 Ø   +/       <* 
    *> case 't'  : x_ch = G_CHAR_POINT     ;  break;    /+    37 t = 225 ·   +/       <* 
    *>             /+---(delayed)-------------------+/                                <* 
    *> case '\\' : x_ch = G_CHAR_DBSLASH   ;  break;    /+    92 \ = 181 µ   +/       <* 
    *> case '"'  : x_ch = G_CHAR_DDQUOTE   ;  break;    /+    34 " = 182 ∂   +/       <* 
    *> case 's'  : x_ch = G_CHAR_SPACE     ;  break;    /+   115 s = 183 ∑   +/       <* 
    *>             /+---(grouping)------------------+/                                <* 
    *> case '('  : x_ch = G_CHAR_SLPAREN   ;  break;    /+    40 ( = 184 ∏   +/       <* 
    *> case ')'  : x_ch = G_CHAR_SRPAREN   ;  break;    /+    41 ) = 185 π   +/       <* 
    *> case '['  : x_ch = G_CHAR_SLBRACK   ;  break;    /+    91 [ = 186 ∫   +/       <* 
    *> case ']'  : x_ch = G_CHAR_SRBRACK   ;  break;    /+    93 ] = 187 ª   +/       <* 
    *> case '{'  : x_ch = G_CHAR_SLCHEV    ;  break;    /+   123 { = 188 º   +/       <* 
    *> case '}'  : x_ch = G_CHAR_SRCHEV    ;  break;    /+   125 } = 189 Ω   +/       <* 
    *>             /+---(super/sub)-----------------+/                                <* 
    *> case '5'  : x_ch = G_CHAR_SUB0      ;  break;    /+    53 5 = 192 ¿   +/       <* 
    *> case '6'  : x_ch = G_CHAR_SUB1      ;  break;    /+    54 6 = 193 ¡   +/       <* 
    *> case '7'  : x_ch = G_CHAR_SUB2      ;  break;    /+    55 7 = 194 ¬   +/       <* 
    *> case '8'  : x_ch = G_CHAR_SUB3      ;  break;    /+    56 8 = 195 √   +/       <* 
    *> case '9'  : x_ch = G_CHAR_SUB4      ;  break;    /+    57 9 = 196 ƒ   +/       <* 
    *> case 'z'  : x_ch = G_CHAR_SUBN      ;  break;    /+   122 z = 197 ≈   +/       <* 
    *> case '2'  : x_ch = G_CHAR_POW2      ;  break;    /+    50 2 = 198 ∆   +/       <* 
    *> case '3'  : x_ch = G_CHAR_POW3      ;  break;    /+    51 3 = 199 «   +/       <* 
    *> case '4'  : x_ch = G_CHAR_POW4      ;  break;    /+    52 4 = 200 »   +/       <* 
    *> case 'x'  : x_ch = G_CHAR_POWX      ;  break;    /+   120 x = 201 …   +/       <* 
    *> case 'y'  : x_ch = G_CHAR_POWY      ;  break;    /+   121 y = 202     +/       <* 
    *> case '#'  : x_ch = G_CHAR_SCINOTE   ;  break;    /+    35 # = 203 À   +/       <* 
    *> case 'o'  : x_ch = G_CHAR_DEGREE    ;  break;    /+    97 o = 204 Ã   +/       <* 
    *> case 'r'  : x_ch = G_CHAR_RADIAN    ;  break;    /+   114 r = 205 Õ   +/       <* 
    *> case '1'  : x_ch = G_CHAR_SQRT      ;  break;    /+    49 1 = 206 Œ   +/       <* 
    *>             /+---(logic)---------------------+/                                <* 
    *> case '&'  : x_ch = G_CHAR_AND       ;  break;                                  <* 
    *> case '|'  : x_ch = G_CHAR_OR        ;  break;                                  <* 
    *> case 'v'  : x_ch = G_CHAR_XOR       ;  break;                                  <* 
    *> case 'i'  : x_ch = G_CHAR_XNOR      ;  break;                                  <* 
    *> case 'k'  : x_ch = G_CHAR_UP        ;  break;                                  <* 
    *> case 'j'  : x_ch = G_CHAR_DOWN      ;  break;                                  <* 
    *> case 'l'  : x_ch = G_CHAR_RIGHT     ;  break;                                  <* 
    *> case 'h'  : x_ch = G_CHAR_LEFT      ;  break;                                  <* 
    *> case '<'  : x_ch = G_CHAR_LE        ;  break;                                  <* 
    *> case '>'  : x_ch = G_CHAR_GE        ;  break;                                  <* 
    *> case '='  : x_ch = G_CHAR_EQUIV     ;  break;                                  <* 
    *> case '/'  : x_ch = G_CHAR_NE        ;  break;                                  <* 
    *> case '~'  : x_ch = G_CHAR_APPROX    ;  break;                                  <* 
    *> case '$'  : x_ch = G_CHAR_RANGE     ;  break;                                  <* 
    *>             /+---(greek)---------------------+/                                <* 
    *> case 'A'  : x_ch = G_CHAR_ALPHA     ;  break;    /+    65 A = 232 Ë   +/       <* 
    *> case 'B'  : x_ch = G_CHAR_BETA      ;  break;    /+    66 B = 233 È   +/       <* 
    *> case 'G'  : x_ch = G_CHAR_GAMMA     ;  break;    /+    71 G = 234 Í   +/       <* 
    *> case 'D'  : x_ch = G_CHAR_DELTA     ;  break;    /+    68 D = 235 Î   +/       <* 
    *> case 'E'  : x_ch = G_CHAR_EPSILON   ;  break;    /+    69 E = 236 Ï   +/       <* 
    *> case 'Z'  : x_ch = G_CHAR_ZETA      ;  break;    /+    90 Z = 237 Ì   +/       <* 
    *> case 'H'  : x_ch = G_CHAR_ETA       ;  break;    /+    72 H = 238 Ó   +/       <* 
    *> case 'Y'  : x_ch = G_CHAR_THETA     ;  break;    /+    89 Y = 239 Ô   +/       <* 
    *> case 'I'  : x_ch = G_CHAR_IOTA      ;  break;    /+    73 I = 240    +/       <* 
    *> case 'K'  : x_ch = G_CHAR_KAPPA     ;  break;    /+    75 K = 241 Ò   +/       <* 
    *> case 'L'  : x_ch = G_CHAR_LAMBDA    ;  break;    /+    76 L = 242 Ú   +/       <* 
    *> case 'M'  : x_ch = G_CHAR_MU        ;  break;    /+    77 M = 243 Û   +/       <* 
    *> case 'N'  : x_ch = G_CHAR_NU        ;  break;    /+    78 N = 244 Ù   +/       <* 
    *> case 'X'  : x_ch = G_CHAR_XI        ;  break;    /+    88 X = 245 ı   +/       <* 
    *> case 'O'  : x_ch = G_CHAR_OMICRON   ;  break;    /+    79 O = 246 ˆ   +/       <* 
    *> case 'P'  : x_ch = G_CHAR_PI        ;  break;    /+    80 P = 247 ˜   +/       <* 
    *> case 'R'  : x_ch = G_CHAR_RHO       ;  break;    /+    82 R = 248 ¯   +/       <* 
    *> case 'S'  : x_ch = G_CHAR_SIGMA     ;  break;    /+    83 S = 249 ˘   +/       <* 
    *> case 'T'  : x_ch = G_CHAR_TAU       ;  break;    /+    84 T = 250 ˙   +/       <* 
    *> case 'U'  : x_ch = G_CHAR_UPSILON   ;  break;    /+    85 U = 251 ˚   +/       <* 
    *> case 'F'  : x_ch = G_CHAR_PHI       ;  break;    /+    70 F = 252 ¸   +/       <* 
    *> case 'C'  : x_ch = G_CHAR_CHI       ;  break;    /+    67 C = 253 ˝   +/       <* 
    *> case 'Q'  : x_ch = G_CHAR_PSI       ;  break;    /+    81 Q = 254 ˛   +/       <* 
    *> case 'W'  : x_ch = G_CHAR_OMEGA     ;  break;    /+    87 W = 255 ˇ   +/       <* 
    *>             /+---(trouble)-------------------+/                                <* 
    *> default   : x_ch = G_CHAR_REDACT    ;  break;    /+  ILLEGAL          +/       <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   return c;
}

uchar ychrslashed             (char a_ch) { return ychr_slashed (1, a_ch); }
uchar ychrslashed_more        (char a_ch) { return ychr_slashed (2, a_ch); }

/*> uchar        /+--> convert backslashed characters --------[ ------ [ ------ ]-+/   <* 
 *> ychrslashed_more   (char a_ch)                                                     <* 
 *> {                                                                                  <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                        <* 
 *>    uchar       x_ch        = a_ch;                                                 <* 
 *>    /+--- phoenicia/shrike mapping -------------+/                                  <* 
 *>    switch (x_ch) {                                                                 <* 
 *>       /+---(notes)---------------------+/                                          <* 
 *>    case '!'  : x_ch = G_CHAR_REDACT;    break;                                     <* 
 *>    case 'c'  : x_ch = G_CHAR_FALSE;     break;                                     <* 
 *>    case 'u'  : x_ch = G_CHAR_UNLIKELY;  break;                                     <* 
 *>    case 'l'  : x_ch = G_CHAR_LIKELY;    break;                                     <* 
 *>    case 't'  : x_ch = G_CHAR_TRUE;      break;                                     <* 
 *>    case 'i'  : x_ch = G_CHAR_INFINITY;  break;                                     <* 
 *>    case 'f'  : x_ch = G_CHAR_FUNCTION;  break;                                     <* 
 *>    case 'a'  : x_ch = G_CHAR_FOREACH;   break;                                     <* 
 *>    case 'q'  : x_ch = G_CHAR_EQUIV;     break;                                     <* 
 *>    case 'x'  : x_ch = G_CHAR_POINT;     break;                                     <* 
 *>    case 'h'  : x_ch = G_CHAR_SUBSET;    break;                                     <* 
 *>    case 'm'  : x_ch = G_CHAR_MEMBER;    break;                                     <* 
 *>    case 'e'  : x_ch = G_CHAR_EMPTY;     break;                                     <* 
 *>    case 'b'  : x_ch = G_CHAR_DSLASH;    break;                                     <* 
 *>    case 'd'  : x_ch = G_CHAR_DIAMOND;   break;                                     <* 
 *>    case 's'  : x_ch = G_CHAR_SUFFIX;    break;                                     <* 
 *>    case 'r'  : x_ch = G_CHAR_RFIELD;    break;                                     <* 
 *>    case '['  : x_ch = G_CHAR_LGULL;     break;                                     <* 
 *>    case ']'  : x_ch = G_CHAR_RGULL;     break;                                     <* 
 *>    case 'o'  : x_ch = G_CHAR_LOCAL;     break;                                     <* 
 *>    case 'w'  : x_ch = G_CHAR_BTICK;     break;                                     <* 
 *>    case '\'' : x_ch = G_CHAR_BTICK;     break;                                     <* 
 *>                /+---(line draw)-----------------+/                                 <* 
 *>    case 'H'  : x_ch = 'Ä';              break;                                     <* 
 *>    case 'V'  : x_ch = 'Å';              break;                                     <* 
 *>    case '0'  : x_ch = 'å';              break;                                     <* 
 *>    case '1'  : x_ch = 'É';              break;                                     <* 
 *>    case '2'  : x_ch = 'â';              break;                                     <* 
 *>    case '3'  : x_ch = 'Ç';              break;                                     <* 
 *>    case '4'  : x_ch = 'á';              break;                                     <* 
 *>    case '5'  : x_ch = 'ä';              break;                                     <* 
 *>    case '6'  : x_ch = 'Ü';              break;                                     <* 
 *>    case '7'  : x_ch = 'Ñ';              break;                                     <* 
 *>    case '8'  : x_ch = 'à';              break;                                     <* 
 *>    case '9'  : x_ch = 'Ö';              break;                                     <* 
 *>    case 'D'  : x_ch = 'î';              break;                                     <* 
 *>    case 'U'  : x_ch = 'ï';              break;                                     <* 
 *>    case 'B'  : x_ch = 'ú';              break;                                     <* 
 *>    case 'T'  : x_ch = 'ù';              break;                                     <* 
 *>    case 'L'  : x_ch = 'û';              break;                                     <* 
 *>    case 'R'  : x_ch = 'ü';              break;                                     <* 
 *>    case 'S'  : x_ch = 'ê';              break;                                     <* 
 *>    case 'E'  : x_ch = 'ë';              break;                                     <* 
 *>    case 'M'  : x_ch = 'ç';              break;                                     <* 
 *>    case 'N'  : x_ch = 'é';              break;                                     <* 
 *>    case 'W'  : x_ch = 'í';              break;                                     <* 
 *>    case 'X'  : x_ch = 'ì';              break;                                     <* 
 *>    case 'Y'  : x_ch = 'ñ';              break;                                     <* 
 *>    case 'Z'  : x_ch = 'ó';              break;                                     <* 
 *>                /+---(trouble)-------------------+/                                 <* 
 *>    default   : x_ch = G_CHAR_REDACT    ;  break;    /+  ILLEGAL          +/        <* 
 *>    }                                                                               <* 
 *>    /+---(complete)-----------------------+/                                        <* 
 *>    return x_ch;                                                                    <* 
 *> }                                                                                  <*/

uchar
ychrbackward            (uchar a_ch, char *r_slash, char *r_base)
{
   /*---(locals)-----------+-----+-----+-*/
   char        i           =    0;
   uchar       c           =    0;
   /*---(default)------------------------*/
   if (r_slash != NULL)  *r_slash = 0;
   if (r_base  != NULL)  *r_base  = '∑';
   /*---(phoenicia/shrike mapping)-------*/
   for (i = 0; i < LEN_FULL; ++i) {
      if (zSTR_extend [i].base   == 0)        break;
      if (zSTR_extend [i].trans  != a_ch)     continue;
      if (r_slash != NULL)  *r_slash = zSTR_extend [i].prefix;
      if (r_base  != NULL)  *r_base  = zSTR_extend [i].base;
      c = zSTR_extend [i].trans;
      break;
   }
   /*---(complete)-----------------------*/
   if (c > 0)  return 1;
   return 0;
}

char         /*--> decode special characters -------------[ ------ [ ------ ]-*/
ystrlunslash        (uchar *a_src, int a_max)
{
   int         i, j;
   for (i = 0; i < a_max; ++i) {
      /*---(filter)----------------------*/
      if (a_src [i] == '\0')          break;
      if (a_src [i] != G_KEY_BSLASH && a_src [i] != G_CHAR_DBSLASH)  continue;
      /*---(fix)-------------------------*/
      if (a_src [i + 1] == '_') {
         a_src [i] = ychrslashed_more (a_src [i + 2]);
         a_src [++i] = '¨';
         a_src [++i] = '¨';
      } else {
         a_src [i] = ychrslashed      (a_src [i + 1]);
         a_src [++i] = '¨';
      }
      /*---(compress)--------------------*/

   }
   ystrlddel (a_src, '¨', a_max);
   return 0;
}

uchar        /*--> convert control in printable ----------[ ------ [ ------ ]-*/
ychrvisible        (uchar a_ch)
{
   /*---(translate)----------------------*/
   switch (a_ch) {
   case G_KEY_RETURN  : a_ch = G_CHAR_RETURN;    break;
   case G_KEY_ENTER   : a_ch = G_CHAR_RETURN;    break;
   case G_KEY_ESCAPE  : a_ch = G_CHAR_ESCAPE;    break;
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
ychrworking        (uchar a_ch)
{
   /*> DEBUG_YSTR   yLOG_senter  (__FUNCTION__);                                      <*/
   /*> DEBUG_YSTR   yLOG_sint    (a_ch);                                              <*/
   /*---(translate)----------------------*/
   switch (a_ch) {
   case G_CHAR_RETURN  : a_ch = G_KEY_RETURN;     break;
   case G_CHAR_ESCAPE  : a_ch = G_KEY_ESCAPE;     break;
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


