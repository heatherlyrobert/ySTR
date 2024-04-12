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

#include    "ySTR_solo.h"

typedef     unsigned char  uchar;
typedef     const char     cchar;
typedef     long long      llong;
typedef     unsigned long long      ullong;


#define     ySTR_NOTRUNC   -1
#define     ySTR_NONE      'n'
#define     ySTR_HEAD      'h'
#define     ySTR_TAIL      't'
#define     ySTR_BOTH      'b'
#define     ySTR_SINGLE    's'
#define     ySTR_EVERY     'e'
#define     ySTR_MAX       'm'

#define     ySTR_NUMERIC   'n'
#define     ySTR_ALPHA     'a'
#define     ySTR_ALNUM     '9'
#define     ySTR_VARS      'v'
#define     ySTR_FILES     'f'
#define     ySTR_BASIC     'b'
#define     ySTR_WRITE     'w'
#define     ySTR_EXTEN     'e'
#define     ySTR_PRINT     'p'
#define     ySTR_HEATHERLY 'h'
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

#define     YSTR_CHECK     '-'   /* just that it is usable                    */
#define     YSTR_USABLE    '-'   /* same as check                             */
#define     YSTR_LEGAL     'y'   /* just check, no changes                    */
#define     YSTR_ADAPT     'a'   /* check, then grow to include if you must   */
#define     YSTR_EXACT     'e'   /* check, then grow/shrink to exact size     */
#define     YSTR_VALID     "-uyae"



char*       ySTR_version            (void);
char        ySTR_debug              (char a_flag);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(normal)------------------*/
char        ystrlcpy                (char *r_dst, char *a_src, int a_max);
char        ystrlcat                (char *r_dst, char *a_src, int a_max);
char        ystrlrev                (char *r_dst, char *a_src, int a_max);
int         ystrllen                (char *a_src, int a_max);
char        ystrltrunc              (char *b_src, int a_max);
int         ystrlupper              (char *b_src, int a_max);
int         ystrllower              (char *b_src, int a_max);
int         ystrltrim               (char *b_src, char a_mode, int  a_max);
int         ystrlrepl               (char *b_src, char *a_old, char *a_new, int a_cnt, int a_max);
/*---(configuration)-----------*/
char        ystrlfile               (char *a_option, char *a_holder, char *a_value, char *a_ext, int a_max);
char        ystrlhome               (char *a_home);
char        ystrlbase               (cchar a_name [LEN_PATH], char r_path [LEN_PATH], char r_base [LEN_HUND], char r_proj [LEN_LABEL], char *r_level);
char        ystrlproj               (char *a_home, char *a_name);
char        ystrlhere               (char *a_home, char *a_name);
char*       ystrlrecd               (cchar *a_name, int n, int *c, char *a_recd, int a_max);
char*       ystrlread               (cchar *a_name, int n, int *c);
/*---(un)----------------------*/
char        ystrlundoc              (uchar *a_src, int a_max);
char        ystrlunquote            (uchar *a_src, int a_max);
char        ystrldequote            (uchar *a_src, int a_max);
char        ystrlrequote            (uchar *a_src, int a_max);
char        ystrlunall              (uchar *a_src, int a_max);

char        ystrlgood               (uchar *a_src, char a_set, int a_max);
short       ystrlcheck              (uchar *a_src, char a_set, int a_max);
short       ystrlmark               (uchar *a_src, char a_set, int a_max);
short       ystrlclean              (uchar *a_src, char a_set, int a_max);

short       ystrlchr                (char *b_src, char a_chr, int a_max);
short       ystrldcnt               (char *b_src, char a_del, int a_max);
short       ystrlddcnt              (char *b_src, char a_del, int a_max);
short       ystrldpos               (char *b_src, char a_del, int a_cnt, int a_max);
short       ystrldchg               (char *b_src, char a_del, char a_new, int a_max);
short       ystrlddel               (char *b_src, char a_del, int a_max);

char        ystrlstore              (char *a_src, int a_max);
char        ystrlunstore            (char *a_src, int a_max);
char        ystrlencode             (char *a_src, char a_mode, int a_max);
char        ystrldecode             (char *a_src, int a_max);
char        ystrlundelay            (char *a_src, int a_max);
char        ystrl2leet              (char *a_src, int a_max);
char        ystrl4leet              (char *a_src, int a_max);
uchar       ychrslashed             (char a_ch);
uchar       ychrslashed_more        (char a_ch);
uchar       ychrbackward            (uchar a_ch, char *r_slash, char *r_base);
char        ystrlunslash            (uchar *a_src, int a_max);
uchar       ychrvisible             (uchar a_ch);
uchar       ychrworking             (uchar a_ch);
int         ystrlhint               (int n, char a_spec [LEN_SHORT], char r_label [LEN_SHORT]);
char*       ystrldisp               (char a_txt [LEN_HUND], char a_len, char *a_out, char a_max);

char        ystrlparse              (char *a_src, char *a_disp, char *a_final, char a_maxc, int *a_cnt, char *a_ptr [], int a_maxl);
/*> char        strlargs           (char *a_src, int   a_max , int  a_cnt , int *a_argc, char *argv[]);   <*/

char        ystrl2bin               (char  *a_src, double *a_val, int a_max);
char        ystrl2oct               (char  *a_src, double *a_val, int a_max);
char        ystrl2hex               (char  *a_src, double *a_val, int a_max);
char        ystrl2mongo             (char  *a_src, double *a_val, int a_max);
char        ystrl2mongor            (char  *a_src, ullong *a_val, int a_max);
char        ystrl2real              (char  *a_src, double *a_val, int a_max);
char        ystrl2sci               (char  *a_src, double *a_val, int a_max);
char        ystrl2comma             (cchar *a_src, double *a_val, int a_max);
char        ystrl2num               (char  *a_src, double *a_val, int a_max);

char        ystrl4bin               (double a_val, char   *a_out, int a_cnt, char a_fmt, int a_max);
char        ystrl4oct               (double a_val, char   *a_out, int a_cnt, char a_fmt, int a_max);
char        ystrl4hex               (double a_val, char   *a_out, int a_cnt, char a_fmt, int a_max);
char        ystrl4comma             (double a_val, char   *a_out, int a_cnt, char a_fmt, char a_unit, int a_max);
char        ystrl4sci               (double a_val, char   *a_out, int a_cnt, char a_fmt, int a_max);
char        ystrl4roman             (double a_val, char   *a_out, int a_cnt, char a_fmt, int a_max);
char        ystrl4mongo             (double a_val, char   *a_out, int a_cnt, char a_fmt, int a_max);
char        ystrl4mongor            (ullong a_val, char   *a_out, int a_cnt, char a_fmt, int a_max);
char        ystrl4time              (double a_val, char   *a_out, int a_cnt, char a_fmt, int a_max);
char        ystrl4main              (double a_val, char   *a_out, int a_cnt, char a_fmt, char a_unit, int a_max);

char        ystrlbit2bin            (char  *a_src, char a_len, char *r_out, char a_fmt, int a_max);
char        ystrlbin2bit            (char  *a_src, int a_max, char *r_bits, char a_blen);
char        ystrlbin2val            (char  *a_src, double *r_val, int a_max);

char        ystrlpad                (char *a_src, char *a_out, char a_fil, char a_ali, int a_max);
char        ystrlpadn               (int   a_src, char *a_out, char a_fil, char a_ali, int a_max);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ystr0gyges              (void *a_checker);

char        ystr2gyges              (char *a_src, int *a_tab, int *a_col, int *a_row, int *a_nada, char *a_abs, int a_def, char a_check);
char        ystr4gyges              (int a_tab, int a_col, int a_row, int a_nada, char a_abs, char *a_out, char a_check);
char        ystr6gyges              (char *a_src, int a_def, char *a_out, char a_check);
char        ystr8gyges              (char *a_src, int a_toff, int a_coff, int a_roff, int a_nada, char a_force, char *a_out, char a_check);

short       MAX_tab                 (void);
char*       LIST_tabs               (void);
char        VALID_tab               (char a_index);
char        LEGAL_tab               (int a_ntab, int a_tab);
uchar       LABEL_tab               (char  a_index);
char        INDEX_tab               (uchar a_label);

short       MAX_col                 (void);
char        VALID_col               (int a_col);
char        LEGAL_col               (int a_ncol, int a_col);
uchar*      LABEL_col               (int a_col);
int         INDEX_col               (uchar *a_label);

short       MAX_row                 (void);
char        VALID_row               (int a_row);
char        LEGAL_row               (int a_nrow, int a_row);
uchar*      LABEL_row               (int a_row);
int         INDEX_row               (uchar *a_label);

char        ystr9align              (char a_align);
char        ystr9filler             (char a_filler);
char        ystr9format             (char a_format);
char        ystr9decs               (int  a_decs);
char        ystr9unit               (char a_unit);

char        ySTR_gyges_checker_small(int b, int x, int y, int z, char a_check);


char        ystrlexport             (int a_line, char *a_recd);
char        ystrlimport             (int a_line, char *a_recd, int *a_len);
char        ystrlage                (long a_epoch, char a_fmt, char a_age [LEN_SHORT]);
char        ystrlager               (long a_now, long a_epoch, char a_fmt, char r_age [LEN_SHORT]);
char        ystrlunage              (char a_age [LEN_SHORT], int *r_secs);
char        ystrlsize               (llong a_bytes, char a_fmt, char a_size [LEN_SHORT]);
char        ystrlcount              (llong a_value, char a_fmt, char a_count [LEN_SHORT]);
char        ystr2mongo              (long a_epoch, char *a_mongo);
char        ystr4mongo              (char *a_mongo, long *a_epoch);



#endif
/*===[[ END ]]================================================================*/
