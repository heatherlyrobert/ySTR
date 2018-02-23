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


/*---(character constants)------------*/
/*---(hidden)----------*/
#define     G_KEY_RETURN       10
#define     G_KEY_ENTER        13
#define     G_KEY_ESCAPE       27
#define     G_KEY_TAB           9
#define     G_KEY_BS          127
#define     G_KEY_SPACE        32
#define     G_KEY_GROUP        29
#define     G_KEY_FIELD        31
#define     G_KEY_DEL           8
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
#define     G_CHAR_RETURN     166   /* ¦  return/newline   ( 10)   */
#define     G_CHAR_ESCAPE     165   /* ¥  staff            (  -)   */
#define     G_CHAR_TAB        171   /* «  tab              (  9)   */
#define     G_CHAR_BS         170   /* ª  backspace        (127)   */
#define     G_CHAR_SPACE      185   /* ¹  dot              (  -)   */
#define     G_CHAR_GROUP      194   /* Â  double broken bar( 29)   */
#define     G_CHAR_FIELD      167   /* §  field separator  ( 31)   */
/*---(control)---------*/
#define     G_CHAR_ALT        211   /* Ó  up               (  -)   */
#define     G_CHAR_CONTROL    212   /* Ô  down             (  -)   */
#define     G_CHAR_WAIT       169   /* ©  funky mark       (  -)   */
#define     G_CHAR_BREAK      191   /* ¿  block            (  -)   */
#define     G_CHAR_HALT       177   /* ±  plus-minus       (  -)   */
#define     G_CHAR_DISPLAY    168   /* ¨  eye              (  -)   */
/*---(testing)---------*/
#define     G_CHAR_DBSLASH    183   /* ·  delayed backslash(  -)   */
#define     G_CHAR_DDQUOTE    184   /* ¸  delayed dquote   (  -)   */
/*---(compare)---------*/
#define     G_CHAR_EQ          61   /* =                           */
#define     G_CHAR_NE         175   /* ¯                           */
#define     G_CHAR_LT          60   /* <                           */
#define     G_CHAR_GT          62   /* <                           */
#define     G_CHAR_LE         173   /* ­                           */
#define     G_CHAR_GE         174   /* ®                           */
#define     G_CHAR_APPROX     172   /* ¬                           */
#define     G_CHAR_EQUIV      229   /* å                           */
#define     G_CHAR_SLPAREN    200   /* È                           */
#define     G_CHAR_SRPAREN    201   /* É                           */
#define     G_CHAR_SLBRACK    202   /* Ê                           */
#define     G_CHAR_SRBRACK    203   /* Ë                           */
#define     G_CHAR_SLCHEV     204   /* Ì                           */
#define     G_CHAR_SRCHEV     205   /* Í                           */
#define     G_CHAR_SLBRACE    298   /* Æ                           */
#define     G_CHAR_SRBRACE    299   /* Ç                           */
/*---(special)---------*/
#define     G_CHAR_NULL       163   /* £  null             (  0)   */
#define     G_CHAR_PLACE      164   /* ¤  placeholder      (  -)   */
#define     G_CHAR_MARK       174   /* ®  mark             (  -)   */
#define     G_CHAR_DEGREE     176   /* °  degree mark      (  -)   */
/*---(greek)-----------*/
#define     G_CHAR_ALPHA      232   /* è  alpha      A     (  -)   */
#define     G_CHAR_BETA       233   /* é  beta       B     (  -)   */
#define     G_CHAR_GAMMA      234   /* ê  gamma      G     (  -)   */
#define     G_CHAR_DELTA      235   /* ë  delta      D     (  -)   */
#define     G_CHAR_EPSILON    236   /* ì  epsilon    E     (  -)   */
#define     G_CHAR_ZETA       237   /* í  zeta       Z     (  -)   */
#define     G_CHAR_ETA        238   /* î  eta        H     (  -)   */
#define     G_CHAR_THETA      239   /* ï  theta      Y     (  -)   */
#define     G_CHAR_IOTA       240   /* ð  iota       I     (  -)   */
#define     G_CHAR_KAPPA      241   /* ñ  kappa      K     (  -)   */
#define     G_CHAR_LAMBDA     242   /* ò  lambda     L     (  -)   */
#define     G_CHAR_MU         243   /* ó  mu         M     (  -)   */
#define     G_CHAR_NU         244   /* ô  nu         N     (  -)   */
#define     G_CHAR_XI         245   /* õ  xi         X     (  -)   */
#define     G_CHAR_OMICRON    246   /* ö  omicron    O     (  -)   */
#define     G_CHAR_PI         247   /* ÷  pi         P     (  -)   */
#define     G_CHAR_RHO        248   /* ø  rho        R     (  -)   */
#define     G_CHAR_SIGMA      249   /* ù  sigma      S     (  -)   */
#define     G_CHAR_TAU        250   /* ú  tau        T     (  -)   */
#define     G_CHAR_UPSILON    251   /* û  upsilon    U     (  -)   */
#define     G_CHAR_PHI        252   /* ü  phi        H     (  -)   */
#define     G_CHAR_CHI        253   /* ý  chi        C     (  -)   */
#define     G_CHAR_PSI        254   /* þ  psi        Q     (  -)   */
#define     G_CHAR_OMEGA      255   /* ÿ  omega      W     (  -)   */


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


#endif
/*===[[ END ]]================================================================*/
