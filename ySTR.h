/*===[[ START HDOC ]]=========================================================*/
/*===[[ HEADER ]]==================================================#

 *   focus         : (PS) programming support
 *   niche         : (st) string handling
 *   heritage      : astraea (virgin goddess of justice, purity, and precision)
 *   purpose       : provide secure and useful string handling capabilities
 *
 *   base_system   : gnu/linux   (powerful, ubiquitous, technical, and hackable)
 *   lang_name     : gnu/ansi-c  (right, just, best, standard, and everlasting)
 *   dependencies  : none
 *   size goal     : small (less than 1,000 slocL)
 *
 *   author        : the_heatherlys
 *   created       : 2013_09
 *   priorities    : direct, simple, brief, vigorous, and lucid (h.w. fowler)
 *   end goal      : loosely coupled, strict interface, maintainable, portable
 *
 */
/*===[[ PURPOSE ]]=================================================#

 *   ySTR is a set of shared functions for string handling and manipulation
 *   services for use by the calling program.  it was designed to take a
 *   repeditive, tedious, haphazard, and neglected set of functions and make
 *   them systematic, shared, testable, maintainable, and reliable.
 *
 *   in keeping with the refactoring motto of "DRY: don't repeat yourself", we
 *   will build this code into a single set of shared library so that we have
 *   a single, unambiguous, authoritative version of the functions.
 *
 *   ySTR will focus on supplementing "string.h" with functions that can
 *   increase security, eliminate hidden bugs, and reduce the code intensity
 *   in programs using it...
 *      - eliminate strcat, strcpy with their potential overruns
 *      - reduce hidden errors caused by misuse of strncat and strncpy
 *      - stop small possibility of overrun in strlen
 *      - create a standard for trimming whitespace which most program need
 *      - simplify and standardize delimiter handling
 *      - anything else clever i can think of ;)
 * 
 *   many existing libraries and utilities have been built by better programmers
 *   that are likely superior in speed, size, capability, and reliability; BUT,
 *   i would not have learned nearly as much using them, so follow the adage...
 * 
 *   TO TRULY LEARN> do not seek to follow in the footsteps of the men of old;
 *   seek what they sought ~ Matsuo Basho
 */

/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YSTR_HGUARD
#define YSTR_HGUARD loaded


typedef     unsigned char  uchar;


#define     ySTR_NOTRUNC   -1
#define     ySTR_NONE      'n'
#define     ySTR_HEAD      'h'
#define     ySTR_TAIL      't'
#define     ySTR_BOTH      'b'
#define     ySTR_SINGLE    's'
#define     ySTR_EVERY     'e'
#define     ySTR_MAX       'm'

#define     ySTR_ALPHA     'a'
#define     ySTR_ALNUM     '9'
#define     ySTR_BASIC     'b'
#define     ySTR_WRITE     'w'
#define     ySTR_EXTEN     'e'
#define     ySTR_PRINT     'p'
#define     ySTR_SEVEN     '7'

#define     ySTR_NORM      '-'

/*===[[ NUMBER FORMATS ]]=====================================================*/

#define     ySTR_INT       'i'
#define     ySTR_FLOAT     'f'
#define     ySTR_EXP       'e'
#define     ySTR_EXPUP     'E'

#define     ySTR_COM       'c'
#define     ySTR_COMUP     'C'
#define     ySTR_ACC       'a'
#define     ySTR_ACCUP     'A'
#define     ySTR_DOL       '$'
#define     ySTR_SGN       's'
#define     ySTR_SGNUP     'S'
#define     ySTR_TECH      '#'
#define     ySTR_PNT       'p'
#define     ySTR_PNTUP     'P'

#define     ySTR_ROM       'r'
#define     ySTR_ROMUP     'R'

#define     ySTR_BIN       'b'
#define     ySTR_BINUP     'B'
#define     ySTR_OCT       'o'
#define     ySTR_OCTUP     'O'
#define     ySTR_HEX       'x'
#define     ySTR_HEXUP     'X'
#define     ySTR_SIX       'z'
#define     ySTR_SIXUP     'Z'

#define     ySTR_TIM       't'
#define     ySTR_TIMUP     'T'
#define     ySTR_DAT       'd'
#define     ySTR_DATUP     'D'

/*===[[ ALIGNMENTS ]]=========================================================*/

#define     ySTR_LEFT      '<'
#define     ySTR_RIGHT     '>'
#define     ySTR_CENTER    '|'


#define     YSTR_CHECK     '-'
#define     YSTR_LEGAL     'y'
#define     YSTR_ADAPT     'a'
#define     YSTR_VALID     "-ya"



/*---(normal txt2ystr)----------------*/
#define     G_KEY_NULL            0
#define     G_KEY_DEL             8
#define     G_KEY_TAB             9
#define     G_KEY_RETURN         10
#define     G_KEY_ENTER          13
#define     G_KEY_ESCAPE         27
#define     G_KEY_GROUP          29
#define     G_KEY_FIELD          31
#define     G_KEY_SPACE          32
#define     G_KEY_DQUOTE         34
#define     G_KEY_SQUOTE         39
#define     G_KEY_LT             60
#define     G_KEY_EQ             61
#define     G_KEY_GT             62
#define     G_KEY_BSLASH         92
#define     G_KEY_PIPE          124
#define     G_KEY_TILDA         126
#define     G_KEY_BS            127
/*---(complete)-----------------------*/


/*---(extended txt2ystr)--------------*/
/*---(notes)---------------------*/
#define     G_CHAR_REXCLAM      161   /*  ¡  */
#define     G_CHAR_RQUEST       162   /*  ¢  */
/*---(hidden)--------------------*/
#define     G_CHAR_NULL         163   /*  £  */
#define     G_CHAR_PLACE        164   /*  ¤  */
#define     G_CHAR_ESCAPE       165   /*  ¥  */
#define     G_CHAR_RETURN       166   /*  ¦  */
#define     G_CHAR_FIELD        167   /*  §  */
#define     G_CHAR_GROUP        168   /*  ¨  */
/*---(macro)---------------------*/
#define     G_CHAR_DISPLAY      169   /*  ©  */
#define     G_CHAR_BREAK        170   /*  ª  */
#define     G_CHAR_WAIT         171   /*  «  */
#define     G_CHAR_MASK         172   /*  ¬  */
#define     G_CHAR_TAB          173   /*  ­  */
#define     G_CHAR_SUMMARY      174   /*  ®  */
#define     G_CHAR_SYSTEM       175   /*  ¯  */
/*---(special)-------------------*/
#define     G_CHAR_HUGE         177   /*  ±  */
#define     G_CHAR_STORAGE      178   /*  ²  */
#define     G_CHAR_HALT         179   /*  ³  */
#define     G_CHAR_BIGDOT       180   /*  ´  */
/*---(delayed)-------------------*/
#define     G_CHAR_DBSLASH      181   /*  µ  */
#define     G_CHAR_DDQUOTE      182   /*  ¶  */
#define     G_CHAR_SPACE        183   /*  ·  */
/*---(grouping)------------------*/
#define     G_CHAR_SLPAREN      184   /*  ¸  */
#define     G_CHAR_SRPAREN      185   /*  ¹  */
#define     G_CHAR_SLBRACK      186   /*  º  */
#define     G_CHAR_SRBRACK      187   /*  »  */
#define     G_CHAR_SLCHEV       188   /*  ¼  */
#define     G_CHAR_SRCHEV       189   /*  ½  */
#define     G_CHAR_DEL          190   /*  ¾  */
#define     G_CHAR_BS           191   /*  ¿  */
/*---(super/sub)-----------------*/
#define     G_CHAR_SUB0         192   /*  À  */
#define     G_CHAR_SUB1         193   /*  Á  */
#define     G_CHAR_SUB2         194   /*  Â  */
#define     G_CHAR_SUB3         195   /*  Ã  */
#define     G_CHAR_SUB4         196   /*  Ä  */
#define     G_CHAR_SUBN         197   /*  Å  */
#define     G_CHAR_POW2         198   /*  Æ  */
#define     G_CHAR_POW3         199   /*  Ç  */
#define     G_CHAR_POW4         200   /*  È  */
#define     G_CHAR_POWX         201   /*  É  */
#define     G_CHAR_POWY         202   /*  Ê  */
#define     G_CHAR_SMHASH       203   /*  Ë  */
#define     G_CHAR_DEGREE       204   /*  Ì  */
#define     G_CHAR_RADIAN       205   /*  Í  */
#define     G_CHAR_SQRT         206   /*  Î  */
#define     G_CHAR_SMALL        207   /*  Ï  */
/*---(logic)---------------------*/
#define     G_CHAR_AND          208   /*  Ð  */
#define     G_CHAR_OR           209   /*  Ñ  */
#define     G_CHAR_XOR          210   /*  Ò  */
#define     G_CHAR_UP           211   /*  Ó  */
#define     G_CHAR_DOWN         212   /*  Ô  */
#define     G_CHAR_RIGHT        213   /*  Õ  */
#define     G_CHAR_LEFT         214   /*  Ö  */
#define     G_CHAR_LE           221   /*  Ý  */
#define     G_CHAR_GE           222   /*  Þ  */
#define     G_CHAR_NE           223   /*  ß  */
#define     G_CHAR_APPROX       230   /*  æ  */
/*---(greek)---------------------*/
#define     G_CHAR_ALPHA        232   /*  è  */
#define     G_CHAR_BETA         233   /*  é  */
#define     G_CHAR_GAMMA        234   /*  ê  */
#define     G_CHAR_DELTA        235   /*  ë  */
#define     G_CHAR_EPSILON      236   /*  ì  */
#define     G_CHAR_ZETA         237   /*  í  */
#define     G_CHAR_ETA          238   /*  î  */
#define     G_CHAR_THETA        239   /*  ï  */
#define     G_CHAR_IOTA         240   /*  ð  */
#define     G_CHAR_KAPPA        241   /*  ñ  */
#define     G_CHAR_LAMBDA       242   /*  ò  */
#define     G_CHAR_MU           243   /*  ó  */
#define     G_CHAR_NU           244   /*  ô  */
#define     G_CHAR_XI           245   /*  õ  */
#define     G_CHAR_OMICRON      246   /*  ö  */
#define     G_CHAR_PI           247   /*  ÷  */
#define     G_CHAR_RHO          248   /*  ø  */
#define     G_CHAR_SIGMA        249   /*  ù  */
#define     G_CHAR_TAU          250   /*  ú  */
#define     G_CHAR_UPSILON      251   /*  û  */
#define     G_CHAR_PHI          252   /*  ü  */
#define     G_CHAR_CHI          253   /*  ý  */
#define     G_CHAR_PSI          254   /*  þ  */
#define     G_CHAR_OMEGA        255   /*  ÿ  */
/*---(complete)-----------------------*/



#define     LEN_HUGE        10000       /* special cases only                 */
#define     LEN_RECD         2000       /* longer likely means hacker         */
#define     LEN_PATH          300       /* large, but not crazy length        */
#define     LEN_FULL          200       /* large string length                */
#define     LEN_HUND          100       /* conservative field/arg length      */
#define     LEN_LONG           75       /* long descrition                    */
#define     LEN_DESC           50       /* no one reads long descriptions     */
#define     LEN_TITLE          30       /* for organizing                     */
#define     LEN_LABEL          20       /* names and labels                   */
#define     LEN_USER           12       /* user names                         */
#define     LEN_HEX            10       /* hex codes                          */
#define     LEN_TERSE          10       /* terse string                       */
#define     LEN_SHORT           5       /* for small needs                    */


char*       ySTR_version       (void);
char        ySTR_debug         (char a_flag);

char        strlcpy            (char *a_dst, char *a_src , int  a_max);
char        strlcat            (char *a_dst, char *a_src , int  a_max);
int         strllen            (char *a_src, int   a_max );
char        strltrunc          (char *a_src, int   a_max );
int         strlupper          (char *a_src, int   a_max);
int         strllower          (char *a_src, int   a_max);
int         strltrim           (char *a_src, char  a_mode, int  a_max);
int         strlrepl           (char *a_src, char *a_old, char *a_new, int a_cnt, int a_max);
int         strlclean          (char *a_src, char a_mode, char a_compress, int a_max);

int         strlchr            (char *a_src, char  a_chr , int a_max);
int         strldcnt           (char *a_src, char  a_del , int  a_max);
int         strldpos           (char *a_src, char  a_del , int  a_cnt , int  a_max);
int         strldchg           (char *a_src, char  a_del , char a_new , int  a_max);
int         strlddel           (char *a_src, char  a_del , int  a_max);

char        strlstore          (char *a_src, int a_max);
char        strlunstore        (char *a_src, int a_max);
char        strlencode         (char *a_src, char a_mode, int a_max);
char        strldecode         (char *a_src, int a_max);
char        strlundelay        (char *a_src, int a_max);
uchar       chrslashed         (char a_ch);
uchar       chrvisible         (uchar a_ch);
uchar       chrworking         (uchar a_ch);

char        strlargs           (char *a_src, int   a_max , int  a_cnt , int *a_argc, char *argv[]);

char        strl2bin           (char   *a_src, double *a_val, int a_max);
char        strl2oct           (char   *a_src, double *a_val, int a_max);
char        strl2hex           (char   *a_src, double *a_val, int a_max);
char        strl2real          (char   *a_src, double *a_val, int a_max);
char        strl2comma         (char   *a_src, double *a_val, int a_max);
char        strl2num           (char   *a_src, double *a_val, int a_max);

char        strl4bin           (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4oct           (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4hex           (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4comma         (double a_val, char *a_out, int a_cnt, char a_fmt, char a_unit, int a_max);
char        strl4sci           (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4roman         (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4mongo         (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4time          (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4main          (double a_val, char *a_out, int a_cnt, char a_fmt, char a_unit, int a_max);

char        strlpad            (char *a_src, char *a_out, char a_fil, char a_ali, int a_max);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        str0gyges               (void *a_checker);

char        str2gyges               (char *a_src, int *a_tab, int *a_col, int *a_row, int *a_nada, char *a_abs, int a_def, char a_check);
char        str4gyges               (int a_tab, int a_col, int a_row, int a_nada, char a_abs, char *a_out, char a_check);
char        str6gyges               (char *a_src, int a_def, char *a_out, char a_check);
char        str8gyges               (char *a_src, int a_toff, int a_coff, int a_roff, int a_nada, char a_force, char *a_out, char a_check);

char        VALID_tab               (int a_tab);
char        LEGAL_tab               (int a_ntab, int a_tab);
uchar       LABEL_tab               (int a_tab);
int         INDEX_tab               (uchar a_label);

char        VALID_col               (int a_col);
char        LEGAL_col               (int a_ncol, int a_col);
uchar*      LABEL_col               (int a_col);
int         INDEX_col               (uchar *a_label);

char        VALID_row               (int a_row);
char        LEGAL_row               (int a_nrow, int a_row);
uchar*      LABEL_row               (int a_row);
int         INDEX_row               (uchar *a_label);

char        str9align               (char a_align);
char        str9filler              (char a_filler);
char        str9format              (char a_format);

char        ySTR_gyges_checker_small(int b, int x, int y, int z, char a_check);

#define     YSTR_BREADCRUMB    'b'

#define     YSTR_INVALID       'i'
#define     YSTR_LOCKED        'l'
#define     YSTR_QUESTIONS     '?'
#define     YSTR_RECOVER       '@'
#define     YSTR_DENIED        'D'
#define     YSTR_PASSED        'P'
#define     YSTR_FAILURE       'F'
#define     YSTR_TIMEOUT       'T'
#define     YSTR_REFRESH       'R'
#define     YSTR_CANCEL        'C'

int         ySTR_language           (void);
int         ySTR_cluster            (void);
int         ySTR_host               (void);
char        ySTR_prompt             (char a_style, int a_iso, int a_cluster, int a_host, char *a_prompt, char *a_key);
char        ySTR_password           (char a_style, int a_lang, char *a_prompt);
char        ySTR_word               (int a_lang, char a_which, char *a_word);
char        ySTR_prompt_box         (int a_lang, int a_cluster, int a_host, char *a_date, int x, int y);

#define     YSTR_GAPS          'y'
#define     YSTR_NOGAPS        '-'

char        ySTR_font               (char *a_font, int *a_wide, int *a_tall);
char        ySTR_displayer          (void *a_displayer);
char        ySTR_display            (char *a_font, char *a_text, char a_gap, int x, int y, int *a_wide, int *a_tall);
char        ystr_oneline            (char *a_text, int x, int y);
char        ySTR_wrapping           (char *a_text, int x, int y, int *a_wide, int *a_tall);



#endif
/*===[[ END ]]================================================================*/
