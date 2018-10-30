/*===[[ START HDOC ]]=========================================================*/
/*===[[ HEADER ]]==================================================#

 *   focus         : (PS) programming support
 *   niche         : (st) string handling
 *   application   : ySTR
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



/*---(character constants)------------*/
/*---(hidden)----------*/
#define     G_KEY_RETURN       10
#define     G_KEY_ENTER        13
#define     G_KEY_ESCAPE       27
#define     G_KEY_TAB           9
#define     G_KEY_BS          127  /* linux unique */
#define     G_KEY_SPACE        32
#define     G_KEY_GROUP        29
#define     G_KEY_FIELD        31
#define     G_KEY_DEL           8  /* linux unique */
/*---(special)---------*/
#define     G_KEY_NULL          0
/*---(normal)----------*/
#define     G_KEY_SQUOTE       39
#define     G_KEY_DQUOTE       34
#define     G_KEY_BSLASH       92
#define     G_KEY_PIPE        124
#define     G_KEY_TILDA       126



/*---(character constants)------------*/
/*---(hidden)----------*/
#define     G_CHAR_RETURN     '¦'
#define     G_CHAR_ESCAPE     '¥'
#define     G_CHAR_TAB        '­'
#define     G_CHAR_BS         '¿'
#define     G_CHAR_DEL        '¾'
#define     G_CHAR_SPACE      '·'
#define     G_CHAR_GROUP      '¨'
#define     G_CHAR_FIELD      '§'
#define     G_CHAR_BIGDOT     '´'
/*---(control)---------*/
#define     G_CHAR_WAIT       '«'
#define     G_CHAR_BREAK      'ª'
#define     G_CHAR_HALT       '³'
#define     G_CHAR_DISPLAY    '©'
#define     G_CHAR_NULL       '£'
#define     G_CHAR_PLACE      '¤'
/*---(testing)---------*/
#define     G_CHAR_DBSLASH    'µ'
#define     G_CHAR_DDQUOTE    '¶'
/*---(compare)---------*/
#define     G_CHAR_RADIAN     'Í'
#define     G_CHAR_DEGREE     'Ì'
#define     G_CHAR_EQ         '='
#define     G_CHAR_LT         '<'
#define     G_CHAR_GT         '>'
#define     G_CHAR_APPROX     'æ'
#define     G_CHAR_EQUIV      'å'
#define     G_CHAR_ANGLE      '±'
#define     G_CHAR_RANGLE     '°'
#define     G_CHAR_CURVE      '²'
/*---(orders)----------*/
#define     G_CHAR_SMHASH     'Ë'
#define     G_CHAR_SUB0       'À'
#define     G_CHAR_SUB1       'Á'
#define     G_CHAR_SUB2       'Â'
#define     G_CHAR_SUB3       'Ã'
#define     G_CHAR_SUB4       'Ä'
#define     G_CHAR_SUBN       'Å'
/*---(powers)----------*/
#define     G_CHAR_POW2       'Æ'
#define     G_CHAR_POW3       'Ç'
#define     G_CHAR_POW4       'È'
#define     G_CHAR_POWX       'É'
#define     G_CHAR_POWY       'Ê'
#define     G_CHAR_SQRT       'Î'
#define     G_CHAR_CBRT       'Ï'
/*---(grouping)--------*/
#define     G_CHAR_SLPAREN    '¸'
#define     G_CHAR_SRPAREN    '¹'
#define     G_CHAR_SLBRACK    'º'
#define     G_CHAR_SRBRACK    '»'
#define     G_CHAR_SLCHEV     '¼'
#define     G_CHAR_SRCHEV     '½'
/*---(special)---------*/
#define     G_CHAR_SUMMARY    '®'
#define     G_CHAR_SYSTEM     '¯'
#define     G_CHAR_REVQUEST   '¢'
#define     G_CHAR_AND        'Ð'
#define     G_CHAR_OR         'Ñ'
#define     G_CHAR_XOR        'Ò'
#define     G_CHAR_LEFT       'Ö'
#define     G_CHAR_RIGHT      'Õ'
#define     G_CHAR_UP         'Ó'
#define     G_CHAR_DOWN       'Ô'
/*---(greek)-----------*/
#define     G_CHAR_ALPHA      'è'
#define     G_CHAR_BETA       'é'
#define     G_CHAR_GAMMA      'ê'
#define     G_CHAR_DELTA      'ë'
#define     G_CHAR_EPSILON    'ì'
#define     G_CHAR_ZETA       'í'
#define     G_CHAR_ETA        'î'
#define     G_CHAR_THETA      'ï'
#define     G_CHAR_IOTA       'ð'
#define     G_CHAR_KAPPA      'ñ'
#define     G_CHAR_LAMBDA     'ò'
#define     G_CHAR_MU         'ó'
#define     G_CHAR_NU         'ô'
#define     G_CHAR_XI         'õ'
#define     G_CHAR_OMICRON    'ö'
#define     G_CHAR_PI         '÷'
#define     G_CHAR_RHO        'ø'
#define     G_CHAR_SIGMA      'ù'
#define     G_CHAR_TAU        'ú'
#define     G_CHAR_UPSILON    'û'
#define     G_CHAR_PHI        'ü'
#define     G_CHAR_CHI        'ý'
#define     G_CHAR_PSI        'þ'
#define     G_CHAR_OMEGA      'ÿ'


typedef     unsigned char  uchar;


char*       ySTR_version       (void);
char        ySTR_debug         (char a_flag);

char        strlcpy            (char *a_dst, char *a_src , int  a_max);
char        strlcat            (char *a_dst, char *a_src , int  a_max);
int         strllen            (char *a_src, int   a_max );
char        strltrunc          (char *a_dst, int   a_max );
int         strltrim           (char *a_src, char  a_mode, int  a_max);
int         strlrepl           (char *a_src, char *a_old, char *a_new, int a_cnt, int a_max);
int         strlclean          (char *a_src, char a_mode, char a_compress, int a_max);

int         strldcnt           (char *a_src, char  a_del , int  a_max);
int         strldpos           (char *a_src, char  a_del , int  a_cnt , int  a_max);
int         strldchg           (char *a_src, char  a_del , char a_new , int  a_max);
int         strlddel           (char *a_src, char  a_del , int  a_max);

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
char        strl4comma         (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4sci           (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4roman         (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4mongo         (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4time          (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4main          (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);

char        strlpad            (char *a_src, char *a_out, char a_fil, char a_ali, int a_max);


char        str0gyges          (void *a_checker);
char        str2gyges          (char *a_src, int *x, int *y, int *z, char *a_abs, int a_def);
char        str4gyges          (int   x, int y, int z, char a_abs, char *a_out);
char        str6gyges          (char *a_src, int a_def, char *a_out);
char        str8gyges          (char *a_src, int xo, int yo, int zo, char *a_out);


#endif
/*===[[ END ]]================================================================*/
