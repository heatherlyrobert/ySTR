
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


/*---(identifiers)--------------------*/
#define     YSTR_IUPPER   'A'
#define     YSTR_ILOWER   'a'
#define     YSTR_INUMBER  '0'
#define     YSTR_IGREEK   '�'
#define     YSTR_IFULL    '*'
/*---(sets)---------------------------*/
#define     YSTR_FULL     "�������������������������������� !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~���������������������������������������������������������������������������������������������������������������������������������"
#define     YSTR_UPPER    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define     YSTR_LOWER    "abcdefghijklmnopqrstuvwxyz"
#define     YSTR_NUMBER   "0123456789"
#define     YSTR_GREEK    "������������������������"
#define     YSTR_BPUNC    "_.,:;!?-()&"
#define     YSTR_PUNCT    "_. ,:;!?-()\"\'&<>{}[]+*/=#@\\^%`~^|$"
#define     YSTR_LEET     "46()3[&#!;<1-=0+9~57_|8*?2"
#define     YSTR_MAYANC   "qlyzdghsmkntwxr"
#define     YSTR_MAYANV   "aeiouvf"
#define     YSTR_MENU     "fevisomdtplbgaxcsh"
/*> "file, edit, veiw, insert, select, format, modify, dataset, tools, palette, layers, buffer, language, auditor, execute, configure, script, share"   <+/   <*/
/*---(combination)--------------------*/
#define     YSTR_UPNUM    "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define     YSTR_UPLOW    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define     YSTR_LOWUP    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define     YSTR_CHARS    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define     YSTR_ALPHA    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
#define     YSTR_ALNUM    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"
#define     YSTR_FILES    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_./"
#define     YSTR_BASIC    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-"
#define     YSTR_WRITE    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_. ,:;!?-()\"\'&"
#define     YSTR_EXTEN    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_. ,:;!?-()\"\'&<>{}[]+*/=#@\\^%`~^|$"
/*---(numeric)------------------------*/
#define     YSTR_TICK     "'+"
#define     YSTR_BINARY   "01"
#define     YSTR_NUMERIC  "0123456789.-+"
#define     YSTR_HEX      "0123456789abcdef"
/*---(general)------------------------*/
#define     YSTR_EMPTY     "                                                                                                                                                                                                       "
#define     YSTR_DASH      "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
#define     YSTR_EQUAL     "======================================================================================================================================================================================================="
#define     YSTR_UNDER     "_______________________________________________________________________________________________________________________________________________________________________________________________________"
#define     YSTR_EDOTS     "�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������"
#define     YSTR_PLUS      "����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����"
/*---(yVIKEYS)------------------------*/
#define     YSTR_LARROW    "׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷׷�"
#define     YSTR_RARROW    "ַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַַ�"
#define     YSTR_LEFT      "�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������"
#define     YSTR_RIGHT     "�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������"
#define     YSTR_PLACE     "�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������"
#define     YSTR_BIGDOT    "�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������"
#define     YSTR_RULER     "���������1���������2���������3���������4���������5���������6���������7���������8���������9���������A���������B���������C���������D���������E���������F���������G���������H���������I���������J���������K���������L���������M���������N���������O���������P���������Q���������R���������S���������T���������U���������V���������W���������X���������Y���������Z"
#define     YSTR_RULERISH  "����+���������+����·���+����÷���+����ķ���+���������+���������+����·���+����÷���+����ķ���+���������+���������+����·���+����÷���+����ķ���+���������+���������+����·���+����÷���+����ķ���+����"
#define     YSTR_DELIMIT   "123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789"
#define     YSTR_MACRO     "����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����+����"
/*---(yLOG)---------------------------*/
#define     YSTR_YLOG      "+��+�����+��+�����+��+�����+�����+��+�����+��+�����+�����+��+�����+��+�����+�����+��+�����+��+�����+�����+��+�����+��+�����+�����+��+�����+��+�����+�����+��+�����+��+�����+�����+��+�����+��+�����+���"
/*---(yUNIT)--------------------------*/
#define     YSTR_CSTEP     ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ."
#define     YSTR_ESTEP     " �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� "
#define     YSTR_COND      " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "



/*---(normal txt2ystr)----------------*/
#define     G_KEY_NULL            0  /* NUL */
#define     G_KEY_NOOP            0  /* NUL */
#define     G_KEY_SKIP            6  /* ACK -- acknowledge     */
#define     G_KEY_DEL             8  /* DEL */
#define     G_KEY_TAB             9
#define     G_KEY_RETURN         10
#define     G_KEY_ENTER          13
#define     G_KEY_ESCAPE         27
#define     G_KEY_GROUP          29
#define     G_KEY_FIELD          31  /* US  -- unit separator  */
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
#define     G_KEY_BS            127  /* BS  */
/*---(complete)-----------------------*/


/*---(extended txt2ystr)--------------*/
/*---(notes)---------------------*/
#define     G_CHAR_REXCLAM      161   /*  �  */
#define     G_CHAR_RQUEST       162   /*  �  */
/*---(hidden)--------------------*/
#define     G_CHAR_NULL         163   /*  �  */
#define     G_CHAR_PLACE        164   /*  �  */
#define     G_CHAR_ESCAPE       165   /*  �  */
#define     G_CHAR_RETURN       166   /*  �  */
#define     G_CHAR_FIELD        167   /*  �  */
#define     G_CHAR_GROUP        168   /*  �  */
#define     G_CHAR_RFIELD       231   /*  �  */
#define     G_CHAR_TAB          152   /*     */
/*---(macro)---------------------*/
#define     G_CHAR_DISPLAY      169   /*  �  */
#define     G_CHAR_BREAK        170   /*  �  */
#define     G_CHAR_WAIT         171   /*  �  */
#define     G_CHAR_HALT         179   /*  �  */
#define     G_CHAR_BIGDOT       180   /*  �  */
#define     G_CHAR_HUGEDOT      207   /*  �  */
/*---(special)-------------------*/
#define     G_CHAR_STORAGE      178   /*  �  */
#define     G_CHAR_MASK         172   /*  �  */
#define     G_CHAR_SUMMARY      174   /*  �  */
#define     G_CHAR_SYSTEM       175   /*  �  */
/*---(delayed)-------------------*/
#define     G_CHAR_DBSLASH      181   /*  �  */
#define     G_CHAR_DDQUOTE      182   /*  �  */
#define     G_CHAR_SPACE        183   /*  �  */
/*---(grouping)------------------*/
#define     G_CHAR_SLPAREN      184   /*  �  */
#define     G_CHAR_SRPAREN      185   /*  �  */
#define     G_CHAR_SLBRACK      186   /*  �  */
#define     G_CHAR_SRBRACK      187   /*  �  */
#define     G_CHAR_SLCHEV       188   /*  �  */
#define     G_CHAR_SRCHEV       189   /*  �  */
#define     G_CHAR_DEL          190   /*  �  */
#define     G_CHAR_BS           191   /*  �  */
#define     G_CHAR_LGULL        229   /*  �  */
#define     G_CHAR_RGULL        230   /*  �  */
/*---(super/sub)-----------------*/
#define     G_CHAR_SUB0         192   /*  �  */
#define     G_CHAR_SUB1         193   /*  �  */
#define     G_CHAR_SUB2         194   /*  �  */
#define     G_CHAR_SUB3         195   /*  �  */
#define     G_CHAR_SUB4         196   /*  �  */
#define     G_CHAR_SUBN         197   /*  �  */
#define     G_CHAR_POW2         198   /*  �  */
#define     G_CHAR_POW3         199   /*  �  */
#define     G_CHAR_POW4         200   /*  �  */
#define     G_CHAR_POWX         201   /*  �  */
#define     G_CHAR_POWY         202   /*  �  */
#define     G_CHAR_SMHASH       203   /*  �  */
#define     G_CHAR_DEGREE       204   /*  �  */
#define     G_CHAR_RADIAN       205   /*  �  */
#define     G_CHAR_SQRT         206   /*  �  */
/*---(logic)---------------------*/
#define     G_CHAR_AND          208   /*  �  */
#define     G_CHAR_OR           209   /*  �  */
#define     G_CHAR_XOR          210   /*  �  */
#define     G_CHAR_XNOR         211   /*  �  */
#define     G_CHAR_UP           212   /*  �  */
#define     G_CHAR_DOWN         213   /*  �  */
#define     G_CHAR_RIGHT        214   /*  �  */
#define     G_CHAR_LEFT         215   /*  �  */
#define     G_CHAR_LE           220   /*  �      <=  */
#define     G_CHAR_GE           221   /*  �      >=  */
#define     G_CHAR_NE           222   /*  �      !=  */
#define     G_CHAR_APPROX       223   /*  �      =~  */
#define     G_CHAR_RANGE        177   /*  �  */
/*---(greek)---------------------*/
#define     G_CHAR_ALPHA        232   /*  �  */
#define     G_CHAR_BETA         233   /*  �  */
#define     G_CHAR_GAMMA        234   /*  �  */
#define     G_CHAR_DELTA        235   /*  �  */
#define     G_CHAR_EPSILON      236   /*  �  */
#define     G_CHAR_ZETA         237   /*  �  */
#define     G_CHAR_ETA          238   /*  �  */
#define     G_CHAR_THETA        239   /*  �  */
#define     G_CHAR_IOTA         240   /*  �  */
#define     G_CHAR_KAPPA        241   /*  �  */
#define     G_CHAR_LAMBDA       242   /*  �  */
#define     G_CHAR_MU           243   /*  �  */
#define     G_CHAR_NU           244   /*  �  */
#define     G_CHAR_XI           245   /*  �  */
#define     G_CHAR_OMICRON      246   /*  �  */
#define     G_CHAR_PI           247   /*  �  */
#define     G_CHAR_RHO          248   /*  �  */
#define     G_CHAR_SIGMA        249   /*  �  */
#define     G_CHAR_TAU          250   /*  �  */
#define     G_CHAR_UPSILON      251   /*  �  */
#define     G_CHAR_PHI          252   /*  �  */
#define     G_CHAR_CHI          253   /*  �  */
#define     G_CHAR_PSI          254   /*  �  */
#define     G_CHAR_OMEGA        255   /*  �  */
/*---(logic)--------------------------*/
#define     G_CHAR_THEREFORE    176   /*  �  */
#define     G_CHAR_FALSE        153   /*  �  */
#define     G_CHAR_UNLIKELY     216   /*  �  */
#define     G_CHAR_LIKELY       217   /*  �  */
#define     G_CHAR_TRUE         154   /*  �  */
#define     G_CHAR_INFINITY     218   /*  �  */
#define     G_CHAR_FUNCTION     219   /*  �  */
#define     G_CHAR_FOREACH      228   /*  �  */
#define     G_CHAR_EQUIV        224   /*  �      == */
#define     G_CHAR_EXISTS       225   /*  �  */
#define     G_CHAR_SUBSET       226   /*  �  */
#define     G_CHAR_MEMBER       227   /*  �  */
#define     G_CHAR_BOX          173   /*  �  */
#define     G_CHAR_EMPTY        160   /*  �  */
#define     G_CHAR_DIAMOND      231   /*  �  */
#define     G_CHAR_SETMATH      229   /*  �  */
#define     G_CHAR_OPEN         143   /*  �  */

/*---(complete)-----------------------*/

