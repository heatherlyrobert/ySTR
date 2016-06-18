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


/* rapidly evolving version number to aid with visual change confirmation     */
#define YSTR_VER_NUM   "0.2b"
#define YSTR_VER_TXT   "add strlddel, its testing, and add to strltrim"


#define       ySTR_NOTRUNC   -1
#define       ySTR_NONE      'n'
#define       ySTR_HEAD      'h'
#define       ySTR_TAIL      't'
#define       ySTR_BOTH      'b'
#define       ySTR_SINGLE    's'
#define       ySTR_EVERY     'e'
#define       ySTR_MAX       'm'


char*       ySTR_version       (void);
char        ySTR_debug         (char a_flag);

char        strlcpy            (char *a_dst, char *a_src , int a_max);
char        strlcat            (char *a_dst, char *a_src , int a_max);
int         strllen            (char *a_src, int   a_max );
char        strltrunc          (char *a_dst, int   a_max );
int         strltrim           (char *a_src, char  a_mode, int a_max);

int         strldcnt           (char *a_src, char  a_del , int a_max);
int         strldpos           (char *a_src, char  a_del , int a_cnt , int  a_max);
int         strlddel           (char *a_src, char  a_del , int a_max);

char        strlargs           (char *a_src, int   a_max , int a_cnt , int *a_argc, char *argv[]);



#endif
/*===[[ END ]]================================================================*/
