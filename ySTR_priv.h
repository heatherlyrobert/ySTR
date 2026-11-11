/*===[[ HEADER GUARD ]]=======================================================*/
/*········´ ´···············guard·´ ´·········································*/
#ifndef    YSTR_priv_guard
#define    YSTR_priv_guard   loaded
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



/*===[[ BEG ONE_LINERS ]]=====================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "st (string handling)"
#define     P_SUBJECT   "useful, safe string handling"
#define     P_PURPOSE   "provide secure and useful string handling capabilities"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "astrea-kori (star-maiden)"
#define     P_PRONOUNCE "·"
#define     P_HERITAGE  "virgin goddess of justice, purity, and precision"
#define     P_BRIEFLY   "goddess of purity and precision"
#define     P_IMAGERY   "elegant woman with shinning wings, angel light, and flamming torch"
#define     P_REASON    "greek goddess of precision keeps my strings safe"
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
#define     P_FORMAL    P_NAMESAKE " " P_BRIEFLY
/*········· ··········· ´·····························´········································*/
#define     P_BASENAME  "libySTR.so"
#define     P_HOMEDIR   "/home/system/yPARSE.record_parsing"
#define     P_FULLPATH  "/usr/local/lib64/libySTR.so"
#define     P_SUFFIX    "´"
#define     P_CONTENT   "´"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 5.3.0"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
/*········· ··········· ´·····························´········································*/
#define     P_DEPSTDC   "stdio,stdlib,string,unistd,math,time"
#define     P_DEPPOSIX  ""
#define     P_DEPSECURE ""
#define     P_DEPEXTEND ""
#define     P_DEPCORE   "yLOG,yURG"
#define     P_DEPVIKEY  ""
#define     P_DEPGRAPH  ""
#define     P_DEPOTHER  ""
#define     P_DEPSOLO   ""
#define     P_DEPALIEN  ""
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2013-09"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "2.--, simplified production"
#define     P_VERMINOR  "2.1-, cleaning up campaign"
#define     P_VERNUM    "2.1d"
#define     P_VERTXT    "unit-tested ystr2real, ystr2comma, ystr2sci, and built ystr2roman ;)"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*===[[ END ONE_LINERS ]]=====================================================*/



/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
#define      _XOPEN_SOURCE
#include    <stdio.h>
#include    <stdlib.h>                  /* getenv()                            */
#include    <string.h>
#include    <unistd.h>
#include    <math.h>  
#include    <time.h>         /* C_ANSI : time, strftime, localtime            */

#include    <yURG.h>                    /* heatherly program logger            */
#include    <yLOG.h>                    /* heatherly program logger            */
#include    "ySTR.h"



/* rapidly evolving version number to aid with visual change confirmation     */



#define     ySTR_ALL_HEADS   "hbsem"
#define     ySTR_ALL_TAILS   "tbsem"
#define     ySTR_ALL_INTER   "esm"


typedef     struct   tm           tTIME;


typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char        debug;
   int         logger;
   /*---(testing)-----------*/
   char        strtest     [LEN_RECD];
   int         argc;
   char       *argv        [20];
};
extern  tLOCAL mySTR;

#define     FONT_FULL      'f'       /* [a-z][0-9] */
#define     FONT_ALPHA     'a'       /* [a-z]      */
#define     FONT_NUMS      'n'       /* [0-9]      */
#define     FONT_BINARY    'b'       /* [0-1]      */
#define     FONT_MAYANC    'm'       /* [0-1]      */


extern char   unit_answer [LEN_RECD];


char*       ySTR_unit          (char *a_question, int a_num);



/*===[[ ySTR_delim.c ]]=======================================================*/
/*········´ ´·····················´ ´·········································*/
int         ystrld_cnt              (char *b_src, char a_del, char a_dup, int a_max);
int         ystrld_pos              (char *b_src, char  a_del, int a_cnt, char a_dup, int a_max);
int         ystrld_chk              (char a_type, char *b_source, char *a_allowed, char a_compress, int a_max);
/*········´ ´················DONE·´ ´·········································*/



/*===[[ ySTR_format.c ]]======================================================*/
/*········´ ´······string2support·´ ´·········································*/
char        ystr2_defense           (char a_src [LEN_TITLE], char a_under, char a_pre, char a_greek, char *r_len, char *r_beg);
/*········´ ´·······string2number·´ ´·········································*/
char        ystr2bin                (char a_src [LEN_TITLE], double *r_val);
char        ystr2oct                (char a_src [LEN_TITLE], double *r_val);
char        ystr2hex                (char a_src [LEN_TITLE], double *r_val);
char        ystr2_divide            (char a_src [LEN_TITLE], char r_int [LEN_TITLE], char r_dec [LEN_TITLE], char r_exp [LEN_TITLE]);
char        ystr2_part              (char a_part, char a_src [LEN_TITLE], double *a_val);
char        ystr2real               (char a_src [LEN_TITLE], double *r_val);
char        ystr2comma              (char a_src [LEN_TITLE], double *r_val);
char        ystr2sci                (char a_src [LEN_TITLE], double *r_val);
char        ystr2roman              (char a_src [LEN_TITLE], double *r_val);
char        ystr2mongo              (char a_src [LEN_TITLE], double *r_val);
char        ystr2mongor             (char a_src [LEN_TITLE], ullong *r_val);
/*········´ ´·······string2driver·´ ´·········································*/
char        ystr2num                (char a_src [LEN_TITLE], double *r_val);
/*········´ ´······string4support·´ ´·········································*/
char        ystr4_units             (char a_unit, double *b_value);
char        ystr4_space_ints        (char a_every, char a_char, char b_out [LEN_TITLE]);
char        ystr4_space_decs        (char a_every, char a_char, char b_out [LEN_TITLE]);
/*········´ ´·······string4number·´ ´·········································*/
char        ystrl4bool              (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE]);
char        ystrl4bin               (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE]);
char        ystrl4oct               (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE]);
char        ystrl4hex               (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE]);
char        ystrl4comma             (double a_val, char a_cnt, char a_fmt, char a_unit, char a_max, char r_out [LEN_TITLE]);
char        ystrl4sci               (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE]);
char        ystrl4roman             (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE]);
char        ystrl4mongo             (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE]);
char        ystrl4mongor            (ullong a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE]);
char        ystrl4time              (double a_val, char a_cnt, char a_fmt, char a_max, char r_out [LEN_TITLE]);
/*········´ ´·······string4driver·´ ´·········································*/
char        ystrl4main              (double a_val, char a_cnt, char a_fmt, char a_unit, char a_max, char r_out [LEN_TITLE]);
char*       ystrl4quick             (double a_val, char a_ali, char a_fmt, char a_cnt, char a_uom, char a_fil, char a_zer, char a_neg, char a_max);
/*········´ ´·········specialized·´ ´·········································*/
char        ystrlbit2bin            (char *a_bits, char a_blen, char a_fmt, char a_max, char r_out [LEN_TITLE]);
char        ystrbin2bit             (char  a_src [LEN_TITLE], char *r_bits, char a_blen);
char        ystrbin2val             (char  a_src [LEN_TITLE], double *r_val);
/*········´ ´················DONE·´ ´·········································*/




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*> char        strl__home              (char *a_home);                               <*/
/*> char        strl__name              (char *a_home, char *a_name);                 <*/

char        ystr__gyges2tab         (char *a_src, char *a_pos, int *a_val, char *a_abs, char a_def);
char        ystr__gyges2col         (char *a_src, char *a_pos, int *a_val, char *a_abs);
char        ystr__gyges2row         (char *a_src, char *a_pos, int *a_val, char *a_abs);
char        ystr_gyges__check       (int a_tab, int a_col, int a_row, int a_abs);
char        ystr_gyges__legal       (int a_tab, int a_col, int a_row, char a_check);

char        ystr_gyges__unit_check  (int b, int x, int y, char z, char a_check);

char        ystr__getlang           (char *a_iso);

char        ystr_font__index        (char a_range, int a_letter);
char*       FONT__unit              (char *a_question, int a_num);

#endif
