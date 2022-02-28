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
#define     ySTR_VARS      'v'
#define     ySTR_FILES     'f'
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

#define     YSTR_CHECK     '-'   /* just that it is usable                    */
#define     YSTR_USABLE    '-'   /* same as check                             */
#define     YSTR_LEGAL     'y'   /* just check, no changes                    */
#define     YSTR_ADAPT     'a'   /* check, then grow to include if you must   */
#define     YSTR_EXACT     'e'   /* check, then grow/shrink to exact size     */
#define     YSTR_VALID     "-uyae"

#define     YSTR_CLIP      "/root/z_gehye/vi_clip.txt"


char*       ySTR_version            (void);
char        ySTR_debug              (char a_flag);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(normal)------------------*/
char        strlcpy                 (char *a_dst, char *a_src , int  a_max);
char        strlcat                 (char *a_dst, char *a_src , int  a_max);
char        strlrev                 (char *a_dst, char *a_src , int  a_max);
int         strllen                 (char *a_src, int   a_max );
char        strltrunc               (char *a_src, int   a_max );
int         strlupper               (char *a_src, int   a_max);
int         strllower               (char *a_src, int   a_max);
int         strltrim                (char *a_src, char  a_mode, int  a_max);
int         strlrepl                (char *a_src, char *a_old, char *a_new, int a_cnt, int a_max);
/*---(configuration)-----------*/
char        strlfile                (char *a_option, char *a_holder, char *a_value, char *a_ext, int a_max);
char        strlhome                (char *a_home);
char        strlproj                (char *a_home, char *a_name);
char        strlhere                (char *a_home, char *a_name);
char*       strlrecd                (cchar *a_name, int n, int *c, char *a_recd, int a_max);
char*       strlread                (cchar *a_name, int n, int *c);
/*---(un)----------------------*/
char        strlundoc               (uchar *a_src, int a_max);
char        strlunquote             (uchar *a_src, int a_max);
char        strldequote             (uchar *a_src, int a_max);
char        strlrequote             (uchar *a_src, int a_max);
char        strlunall               (uchar *a_src, int a_max);

char        strlgood                (uchar *a_src, char a_set, int a_max);
short       strlcheck               (uchar *a_src, char a_set, int a_max);
short       strlmark                (uchar *a_src, char a_set, int a_max);
short       strlclean               (uchar *a_src, char a_set, int a_max);

int         strlchr                 (char *a_src, char  a_chr , int a_max);
int         strldcnt                (char *a_src, char  a_del , int  a_max);
int         strldpos                (char *a_src, char  a_del , int  a_cnt , int  a_max);
int         strldchg                (char *a_src, char  a_del , char a_new , int  a_max);
int         strlddel                (char *a_src, char  a_del , int  a_max);

char        strlstore               (char *a_src, int a_max);
char        strlunstore             (char *a_src, int a_max);
char        strlencode              (char *a_src, char a_mode, int a_max);
char        strldecode              (char *a_src, int a_max);
char        strlundelay             (char *a_src, int a_max);
char        strl2leet               (char *a_src, int a_max);
uchar       chrslashed              (char a_ch);
uchar       chrslashed_more         (char a_ch);
uchar       chrvisible              (uchar a_ch);
uchar       chrworking              (uchar a_ch);
int         strlhint                (int n, char *a_spec, char *a_label);

char        strlparse               (char *a_src, char *a_disp, char *a_final, char a_maxc, int *a_cnt, char *a_ptr [], int a_maxl);
/*> char        strlargs           (char *a_src, int   a_max , int  a_cnt , int *a_argc, char *argv[]);   <*/

char        strl2bin                (char   *a_src, double *a_val, int a_max);
char        strl2oct                (char   *a_src, double *a_val, int a_max);
char        strl2hex                (char   *a_src, double *a_val, int a_max);
char        strl2real               (char   *a_src, double *a_val, int a_max);
char        strl2comma              (cchar  *a_src, double *a_val, int a_max);
char        strl2num                (char   *a_src, double *a_val, int a_max);

char        strl4bin                (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4oct                (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4hex                (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4comma              (double a_val, char *a_out, int a_cnt, char a_fmt, char a_unit, int a_max);
char        strl4sci                (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4roman              (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4mongo              (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4time               (double a_val, char *a_out, int a_cnt, char a_fmt, int a_max);
char        strl4main               (double a_val, char *a_out, int a_cnt, char a_fmt, char a_unit, int a_max);

char        strlpad                 (char *a_src, char *a_out, char a_fil, char a_ali, int a_max);
char        strlpadn                (int   a_src, char *a_out, char a_fil, char a_ali, int a_max);


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        str0gyges               (void *a_checker);

char        str2gyges               (char *a_src, int *a_tab, int *a_col, int *a_row, int *a_nada, char *a_abs, int a_def, char a_check);
char        str4gyges               (int a_tab, int a_col, int a_row, int a_nada, char a_abs, char *a_out, char a_check);
char        str6gyges               (char *a_src, int a_def, char *a_out, char a_check);
char        str8gyges               (char *a_src, int a_toff, int a_coff, int a_roff, int a_nada, char a_force, char *a_out, char a_check);

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

char        str9align               (char a_align);
char        str9filler              (char a_filler);
char        str9format              (char a_format);
char        str9decs                (int  a_decs);
char        str9unit                (char a_unit);

char        ySTR_gyges_checker_small(int b, int x, int y, int z, char a_check);

#define     YSTR_BREADCRUMB    'b'
#define     YSTR_BREADCOLOR    'c'

#define     YSTR_USERNAME      'u'
#define     YSTR_TOKEN         't'
#define     YSTR_PASSWORD      'p'

#define     YSTR_INVALID       'I'
#define     YSTR_LOCKED        'L'
#define     YSTR_QUESTIONS     '?'
#define     YSTR_RECOVER       '@'
#define     YSTR_DENIED        'D'
#define     YSTR_PASSED        'P'
#define     YSTR_FAILURE       'F'
#define     YSTR_TIMEOUT       'T'
#define     YSTR_REFRESH       'R'
#define     YSTR_CANCEL        'C'

char        ySTR_language           (void);
char        ySTR_cluster            (char l, char n, char *a_word, char *a_content);
char        ySTR_host               (char l, char n, char *a_title, char *a_content);
char        ySTR_prompt             (char a_style, char *a_prefix, int a_lang, int a_cluster, int a_host, char *a_prompt, char *a_key);
char        ySTR_password           (char a_style, int a_lang, char *a_prompt);
char        ySTR_word               (int a_lang, char a_which, char *a_word);
char        ySTR_prompt_box         (int a_lang, int a_cluster, int a_host, char *a_date, int x, int y);

#define     YSTR_GAPS          'y'
#define     YSTR_NOGAPS        '-'

#define     YSTR_CLEAR         'c'
#define     YSTR_MERGE         'm'

char        ySTR_font               (char *a_font, int *a_wide, int *a_tall);
char        ySTR_displayer          (void *a_displayer);
char        ySTR_display            (char *a_font, char *a_text, char a_gap, int x, int y, int *a_wide, int *a_tall, char a_mode);
char        ystr_oneline            (char *a_text, int x, int y, char a_mode);
char        ySTR_wrapping           (char *a_text, int x, int y, int *a_wide, int *a_tall, char a_mode);


char        strlexport              (int a_line, char *a_recd);
char        strlimport              (int a_line, char *a_recd, int *a_len);
char        strlage                 (long a_epoch, char *a_age);
char        str2mongo               (long a_epoch, char *a_mongo);
char        str4mongo               (char *a_mongo, long *a_epoch);



#endif
/*===[[ END ]]================================================================*/
