
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
#define     LEN_TERSE          10       /* terse string                       */
#define     LEN_SHORT           5       /* for small needs                    */



/*---(sets)---------------------------*/
#define     LTRS_UPPER    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define     LTRS_LOWER    "abcdefghijklmnopqrstuvwxyz"
#define     LTRS_NUMBER   "0123456789"
#define     LTRS_GREEK    "èéêëìíîïðñòóôõö÷øùúûüýþÿ"
#define     LTRS_BPUNC    "_.,:;!?-()&"
#define     LTRS_PUNCT    "_. ,:;!?-()\"\'&<>{}[]+*/=#@\\^%`~^|$"
#define     LTRS_MAYANC   "qlyzdghsmkntwxr"
#define     LTRS_MAYANV   "aeiouvf"
/*---(combination)--------------------*/
#define     LTRS_UPNUM    "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define     LTRS_UPLOW    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define     LTRS_CHARS    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define     LTRS_ALPHA    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
#define     LTRS_ALNUM    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"
#define     LTRS_FILES    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_./"
#define     LTRS_BASIC    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-"
#define     LTRS_WRITE    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_. ,:;!?-()\"\'&"
#define     LTRS_EXTEN    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_. ,:;!?-()\"\'&<>{}[]+*/=#@\\^%`~^|$"
/*---(numeric)------------------------*/
#define     LTRS_TICK     "'+"
#define     LTRS_BINARY   "01"
#define     LTRS_NUMERIC  "0123456789.-+"
#define     LTRS_HEX      "0123456789abcdef"
/*---(general)------------------------*/
#define     STR_EMPTY     "                                                                                                                                                                                                       "
#define     STR_DASH      "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
#define     STR_EQUAL     "======================================================================================================================================================================================================="
#define     STR_UNDER     "_______________________________________________________________________________________________________________________________________________________________________________________________________"
#define     STR_EDOTS     "·······································································································································································································"
#define     STR_PLUS      "····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····"
/*---(yVIKEYS)------------------------*/
#define     STR_LARROW    "Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö"
#define     STR_RARROW    "Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ·Õ"
#define     STR_LEFT      "¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿"
#define     STR_RIGHT     "¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾"
#define     STR_PLACE     "¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤"
#define     STR_BIGDOT    "´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´"
#define     STR_RULER     "····+····Á····+····Â····+····Ã····+····Ä····+····À····+····Á····+····Â····+····Ã····+····Ä····+····À····+····Á····+····Â····+····Ã····+····Ä····+····À····+····Á····+····Â····+····Ã····+····Ä····+····"
#define     STR_NUMBER    "123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789"
#define     STR_MACRO     "····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····"
/*---(yLOG)---------------------------*/
#define     STR_YLOG      "+··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´"
/*---(yUNIT)--------------------------*/
#define     STR_CSTEP     ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ."
#define     STR_ESTEP     " ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· "
#define     STR_COND      " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "



/*---(normal txt2ystr)----------------*/
#define     G_KEY_NULL            0
#define     G_KEY_NOOP            0
#define     G_KEY_ACK             6
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
#define     G_KEY_BTICK          96
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
#define     G_CHAR_RFIELD       231   /*  ç  */
#define     G_CHAR_TAB          152   /*     */
/*---(macro)---------------------*/
#define     G_CHAR_DISPLAY      169   /*  ©  */
#define     G_CHAR_BREAK        170   /*  ª  */
#define     G_CHAR_WAIT         171   /*  «  */
#define     G_CHAR_HALT         179   /*  ³  */
#define     G_CHAR_BIGDOT       180   /*  ´  */
#define     G_CHAR_HUGEDOT      207   /*  Ï  */
/*---(special)-------------------*/
#define     G_CHAR_STORAGE      178   /*  ²  */
#define     G_CHAR_MASK         172   /*  ¬  */
#define     G_CHAR_SUMMARY      174   /*  ®  */
#define     G_CHAR_SYSTEM       175   /*  ¯  */
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
#define     G_CHAR_LGULL        229   /*  å  */
#define     G_CHAR_RGULL        230   /*  æ  */
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
/*---(logic)---------------------*/
#define     G_CHAR_AND          208   /*  Ð  */
#define     G_CHAR_OR           209   /*  Ñ  */
#define     G_CHAR_XOR          210   /*  Ò  */
#define     G_CHAR_XNOR         211   /*  Ó  */
#define     G_CHAR_UP           212   /*  Ô  */
#define     G_CHAR_DOWN         213   /*  Õ  */
#define     G_CHAR_RIGHT        214   /*  Ö  */
#define     G_CHAR_LEFT         215   /*  ×  */
#define     G_CHAR_LE           220   /*  Ü      <=  */
#define     G_CHAR_GE           221   /*  Ý      >=  */
#define     G_CHAR_NE           222   /*  Þ      !=  */
#define     G_CHAR_APPROX       223   /*  ß      =~  */
#define     G_CHAR_RANGE        177   /*  ±  */
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
/*---(logic)--------------------------*/
#define     G_CHAR_THEREFORE    176   /*  °  */
#define     G_CHAR_FOREACH      228   /*  ä  */
#define     G_CHAR_UNLIKELY     216   /*  Ø  */
#define     G_CHAR_LIKELY       217   /*  Ù  */
#define     G_CHAR_INFINITY     218   /*  Ú  */
#define     G_CHAR_FUNCTION     219   /*  Û  */
#define     G_CHAR_BOX          173   /*  ­  */
#define     G_CHAR_EQUIV        224   /*  à      == */
#define     G_CHAR_EXISTS       225   /*  á  */
#define     G_CHAR_SUBSET       226   /*  â  */
#define     G_CHAR_MEMBER       227   /*  ã  */
#define     G_CHAR_EMPTY        160   /*     */
#define     G_CHAR_DIAMOND      231   /*  ›  */
#define     G_CHAR_SETMATH      229   /*  ˜  */
#define     G_CHAR_OPEN         143   /*    */

/*---(complete)-----------------------*/

