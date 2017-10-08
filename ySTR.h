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

/*---(character constants)------------*/
/*---(hidden)----------*/
#define     G_KEY_RETURN       10
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
#define     G_CHAR_RETURN     182   /* ¶  return/newline   ( 10)   */
#define     G_CHAR_ESCAPE     165   /* ¥  staff            (  -)   */
#define     G_CHAR_TAB        187   /* »  tab              (  9)   */
#define     G_CHAR_BS         171   /* «  backspace        (127)   */
#define     G_CHAR_SPACE      183   /* ·  dot              (  -)   */
#define     G_CHAR_GROUP      185   /* ¦  double bar       ( 29)   */
#define     G_CHAR_FIELD      167   /* §  field separator  ( 31)   */
/*---(control)---------*/
#define     G_CHAR_ALT        194   /* Â  up               (  -)   */
#define     G_CHAR_CONTROL    195   /* Ã  down             (  -)   */
#define     G_CHAR_WAIT       186   /* º  funky mark       (  -)   */
#define     G_CHAR_BREAK      191   /* ¿  lead question    (  -)   */
#define     G_CHAR_HALT       177   /* ±  plus-minus       (  -)   */
#define     G_CHAR_DISPLAY    162   /* ¢  weird d          (  -)   */
/*---(special)---------*/
#define     G_CHAR_NULL       188   /* ¼  null             (  0)   */
#define     G_CHAR_PLACE      164   /* ¤  placeholder      (  -)   */
#define     G_CHAR_MARK       174   /* ®  mark             (  -)   */
#define     G_CHAR_DEGREE     176   /* °  degree mark      (  -)   */
/*---(greek)-----------*/
#define     G_CHAR_ALPHA      232   /* è  alpha      A     (  -)   */
#define     G_CHAR_BETA       233   /* é  beta       B     (  -)   */
#define     G_CHAR_GAMMA      234   /* ê  gamma      G     (  -)   */
#define     G_CHAR_DELTA      235   /* ë  delta      D     (  -)   */
#define     G_CHAR_THETA      239   /* ï  theta      T     (  -)   */
#define     G_CHAR_LAMBDA     242   /* ò  lambda     L     (  -)   */
#define     G_CHAR_PI         247   /* ÷  pi         P     (  -)   */
#define     G_CHAR_SIGMA      249   /* ù  sigma      S     (  -)   */
#define     G_CHAR_PHI        252   /* ü  phi        H     (  -)   */
#define     G_CHAR_PSI        254   /* þ  psi        I     (  -)   */
#define     G_CHAR_OMEGA      255   /* ÿ  omega      O     (  -)   */



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

char        strlencode         (char *a_src, int a_max);
char        strldecode         (char *a_src, int a_max);

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
