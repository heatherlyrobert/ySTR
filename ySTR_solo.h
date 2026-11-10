/*===[[ HEADER GUARD ]]=======================================================*/
/*········´ ´···············guard·´ ´·········································*/
#ifndef    YSTR_solo_guard
#define    YSTR_solo_guard   loaded
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


/*---(shared clipboard)---------------*/
#define     YSTR_CLIP     "/tmp/vi_clip.txt"


typedef     unsigned char       uchar;
typedef     unsigned short      ushort;
typedef     unsigned int        uint;
typedef     long long           llong;
typedef     unsigned long long  ullong;
typedef     const char          cchar;


/*---(simple functions)---------------*/
char        ystrutrim               (uchar *b_src, int a_max);
char        ystruencode             (uchar *b_src);
char        ystrudecode             (uchar *b_src);
char        ystrureplace            (uchar *a_src, uchar *a_old, uchar *a_new, int a_max);
char        ystruundelay            (uchar *a_src, int a_max);


/*---(standard lengths)---------------*/
#define     LEN_MASS       100000       /* special cases only                 */
#define     LEN_HUGE        10000       /* special cases only                 */
#define     LEN_RECD         2000       /* longer likely means hacker         */
#define     LEN_THOU         1000       /* thousand long                      */
#define     LEN_HALF          500       /* serious string length              */
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

/*---(alignment)----------------------*/
#define     YSTR_TEXT_LEF     '<'       /* align text left                    */
#define     YSTR_TEXT_RIG     '>'       /* align text right                   */
#define     YSTR_TEXT_CEN     '|'       /* align text center                  */

/*---(identifiers)--------------------*/
#define     YSTR_INIT         'I'
#define     YSTR_IUPPER       'A'
#define     YSTR_ILOWER       'a'
#define     YSTR_INUMBER      '0'
#define     YSTR_IGREEK       'è'
#define     YSTR_IFULL        '*'
/*---(sets)---------------------------*/
#define     YSTR_FULL     "································ !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~½€‚ƒ„…†‡ˆ‰Š‹ŒŽ‘’“”•–—˜™š›œžŸ ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
#define     YSTR_UPPER    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define     YSTR_LOWER    "abcdefghijklmnopqrstuvwxyz"
#define     YSTR_NUMBER   "0123456789"
#define     YSTR_NUML     "éöõí0123456789"
#define     YSTR_FLOAT    "0123456789."
#define     YSTR_GREEK    "èéêëìíîïðñòóôõö÷øùúûüýþÿ"
#define     YSTR_BPUNC    "_.,:;!?-()&"
#define     YSTR_PUNCT    "_. ,:;!?-()\"\'&<>{}[]+*/=#@\\^%`~^|$"
#define     YSTR_LEET     "46()3[&#!;<1-=0+9~57_|8*?2"
#define     YSTR_MENU     "fevisomdtplbgaxcsh"
#define     YSTR_TABS     "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ®¯¤¢"
#define     YSTR_COLORS   "wruybpocWRGYBPOC"
#define     YSTR_COLORGL  "-ohiwrknlysgabdpmcuvteOHIWRKNLYSGABDPMCUVTE!"
/*> "file, edit, view, insert, select, format, modify, dataset, tools, palette, layers, buffer, language, auditor, execute, configure, script, share"   <+/   <*/
#define     YSTR_CALC_PRE "#~=¼&!"
#define     YSTR_CALC_SPC "#=¼"
/*---(mayan)--------------------------*/
#define     YSTR_MAYANF   "dgnlswyqtkhzmcDGTQK"
#define     YSTR_MAYANC   "dgnlswyqtkhzmc"
#define     YSTR_MAYANV   "aieovuf"
#define     YSTR_MAYANE   "aieovufbjprx"
#define     YSTR_MAYANO   "´Ö×ÕÔ€„"
/*---(combination)--------------------*/
#define     YSTR_UPNUM    "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define     YSTR_UPLOW    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define     YSTR_LOWUP    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define     YSTR_CHARS    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define     YSTR_ALLCHAR  "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZèéêëìíîïðñòóôõö÷øùúûüýþÿ"
#define     YSTR_NUMDEV   "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:/_-"
#define     YSTR_ALPHA    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
#define     YSTR_ALNUM    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"
#define     YSTR_VARS     "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define     YSTR_FILES    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_./"
#define     YSTR_BASIC    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.-"
#define     YSTR_WRITE    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_. ,:;!?-()\"\'&"
#define     YSTR_EXTEN    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_. ,:;!?-()\"\'&<>{}[]+*/=#@\\^%`~^|$"
#define     YSTR_PRINT    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
#define     YSTR_SEVEN    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
#define     YSTR_HEATH    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~€‚ƒ„…†‡ˆ‰Š‹ŒŽ‘’“”•–—˜™š›œžŸ ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ"
#define     YSTR_MAXX     " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~€‚ƒ„…†‡ˆ‰Š‹ŒŽ‘’“”•–—˜™š›œžŸ ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ\x09\x0a\x0d\x1b\x1c\x1d\x1e\x1f"
/*---(special)------------------------*/
#define     YSTR_VERBS    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_#]>+@"
#define     YSTR_UNIV     "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ®¯¤¢"
#define     YSTR_ADDR     "@$0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ®¯¤¢"
#define     YSTR_OPER     "|&=!<>*/%+-.?:^~#©ÑÐÒÔÓÕÆÇÈÉÊÎËÍÌ´`àÞÜÝ¬°âãá"
#define     YSTR_GROUP    "()[]¸¹º»"
#define     YSTR_SEQ      "()[]¸¹,"
#define     YSTR_SUBS     "ÀÁÂÃÄÅ"
#define     YSTR_POWS     "ÆÇÈÎÉÊ"
#define     YSTR_SJOIN    "ÐÑÒ"
#define     YSTR_CJOIN    "ÐÑÒÓÔÕ"
#define     YSTR_JOIN     "ÐÑÒÓÔÕ"
#define     YSTR_VARL     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZèéêëìíîïðñòóôõö÷øùúûüýþÿ_ç@®"
#define     YSTR_VARN     "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789èéêëìíîïðñòóôõö÷øùúûüýþÿ_ÀÁÂÃÄÅ"
/*---(numeric)------------------------*/
#define     YSTR_TICK     "'+"
#define     YSTR_BINARY   "01"
#define     YSTR_BINPLUS  "01'+-Ï"
#define     YSTR_NUMERIC  "0123456789.-+"
#define     YSTR_HEX      "0123456789abcdef"
#define     YSTR_HEXUP    "0123456789abcdefABCDEF"
#define     YSTR_OCTAL    "01234567"
#define     YSTR_ROMAN    "oivxlcdmOIVXLCDM"
#define     YSTR_MONGO    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define     YSTR_MUCHO    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzÐÑÒÓÔÕÖ×ØÙÜÝÞßèéêëìíîïðñòóôõö÷øùúûüýþÿ"
#define     YSTR_MUCHO2   "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz€Ž’“”•–—žŸœèéêëìíîïðñòóôõö÷øùúûüýþÿ"
#define     YSTR_COUNT    "·123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ°"
#define     YSTR_BIGGUN   "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZèéêëìíîïðñòóôõö÷øùúûüýþÿ_.,:;!?-()¶'&<>{}[]+*/=#@^%`~^|$ÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãä¸¹¼½¾¿º»åæ®¯ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎ€‚ƒ„…†‡ˆ‰Š‹ŒŽ‘’“”•–—°"
/*---(general)------------------------*/
#define     YSTR_EMPTY     "                                                                                                                                                                                                       "
#define     YSTR_DASH      "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
#define     YSTR_EQUAL     "======================================================================================================================================================================================================="
#define     YSTR_UNDER     "_______________________________________________________________________________________________________________________________________________________________________________________________________"
#define     YSTR_EDOTS     "·······································································································································································································"
#define     YSTR_PLUS      "····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····"
#define     YSTR_COLS      "----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----·----"
#define     YSTR_HORZ      "€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€€"
/*---(yVIKEYS)------------------------*/
#define     YSTR_LARROW    "×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×·×"
#define     YSTR_RARROW    "Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö·Ö"
#define     YSTR_LEFT      "¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿·¿"
#define     YSTR_RIGHT     "¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾·¾"
#define     YSTR_PLACE     "¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤··¤"
#define     YSTR_BIGDOT    "´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´··´"
#define     YSTR_RULER     "····´····1····´····2····´····3····´····4····´····5····´····6····´····7····´····8····´····9····´····A····´····B····´····C····´····D····´····E····´····F····´····G····´····H····´····I····´····J····´····K····´····L····´····M····´····N····´····O····´····P····´····Q····´····R····´····S····´····T····´····U····´····V····´····W····´····X····´····Y····´····Z"
#define     YSTR_RULERISH  "····+····Á····+····Â····+····Ã····+····Ä····+····À····+····Á····+····Â····+····Ã····+····Ä····+····À····+····Á····+····Â····+····Ã····+····Ä····+····À····+····Á····+····Â····+····Ã····+····Ä····+····"
#define     YSTR_DELIMIT   "123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789"
#define     YSTR_MACRO     "····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····+····"
#define     YSTR_ZEROS     "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
#define     YSTR_ONES      "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
/*---(yLOG)---------------------------*/
#define     YSTR_YLOG      "+··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´··+··+··´··+··+··´··+··´"
/*---(yUNIT)--------------------------*/
#define     YSTR_CSTEP     ".  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  ."
#define     YSTR_ESTEP     " ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· ·· "
#define     YSTR_COND      " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "



/*---(normal txt2ystr)----------------*/
#define     G_KEY_NULL            0  /* NUL */
#define     G_KEY_NOOP            0  /* NUL */
#define     G_KEY_SHIFT          15  /* SI shift in, totally unused */
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
#define     G_CHAR_DISPLAY      173   /*  ­  */
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
#define     G_CHAR_SCINOTE      203   /*  Ë  */
#define     G_CHAR_SQRT         206   /*  Î  */
#define     G_CHAR_POW2         198   /*  Æ  */
#define     G_CHAR_POW3         199   /*  Ç  */
#define     G_CHAR_POW4         200   /*  È  */
#define     G_CHAR_POWX         201   /*  É  */
#define     G_CHAR_POWY         202   /*  Ê  */
#define     G_CHAR_DEGREE       204   /*  Ì  */
#define     G_CHAR_RADIAN       205   /*  Í  */
/*---(logic)---------------------*/
#define     G_CHAR_AND          208   /*  Ð  */
#define     G_CHAR_OR           209   /*  Ñ  */
#define     G_CHAR_XOR          210   /*  Ò  */
#define     G_CHAR_XNOR         211   /*  Ó  */
#define     G_CHAR_UP           212   /*  Ô  */
#define     G_CHAR_DOWN         213   /*  Õ  */
#define     G_CHAR_RIGHT        214   /*  Ö  */
#define     G_CHAR_LEFT         215   /*  ×  */
/*---(math)----------------------*/
#define     G_CHAR_LE           220   /*  Ü      <=  */
#define     G_CHAR_GE           221   /*  Ý      >=  */
#define     G_CHAR_EQUIV        224   /*  à      == */
#define     G_CHAR_NE           222   /*  Þ      !=  */
#define     G_CHAR_APPROX       223   /*  ß      =~  */
#define     G_CHAR_RANGE        152   /*  ˜  */
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
#define     G_CHAR_REDACT       176   /*  °  */
#define     G_CHAR_FALSE        218   /*  Ú  */
#define     G_CHAR_UNLIKELY     216   /*  Ø  */
#define     G_CHAR_LIKELY       217   /*  Ù  */
#define     G_CHAR_TRUE         219   /*  Û  */
#define     G_CHAR_INFINITY     153   /*  ™  */
#define     G_CHAR_FUNCTION     154   /*  š  */
#define     G_CHAR_FOREACH      228   /*  ä  */
#define     G_CHAR_POINT        225   /*  á  */
#define     G_CHAR_SUBSET       226   /*  â  */
#define     G_CHAR_MEMBER       227   /*  ã  */
#define     G_CHAR_DSLASH       155   /*  ›  */
#define     G_CHAR_EMPTY        160   /*     */
#define     G_CHAR_DIAMOND      169   /*  ©  */
#define     G_CHAR_SUFFIX       177   /*  ±  */
#define     G_CHAR_BTICK         96   /*  `  */
#define     G_CHAR_RFIELD       143   /*    */
#define     G_CHAR_LOCAL        231   /*  ç  */
/*---(complete)-----------------------*/

#endif
