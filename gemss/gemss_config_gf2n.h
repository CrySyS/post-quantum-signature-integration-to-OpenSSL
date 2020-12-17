#ifndef _CONFIG_GF2N_H
#define _CONFIG_GF2N_H


/* An irreducible polynomial f(x) of degree n in GF(2)[x] is chosen.
    f is a trinomial s.t. f(x) = x^n + x^GEMSS_K3 + 1, 
    or f is a pentanomial s.t. f(x) = x^n + x^GEMSS_K3 + x^GEMSS_K2 + x^GEMSS_K1 + 1. */


#include "gemss_parameters_HFE.h"

/* Warning: 0 < GEMSS_K3 <= 32 is required (excepted for special cases) */
/* Warning: 0 < GEMSS_K1 < GEMSS_K2 < GEMSS_K3 <= 32 is required (excepted for special cases) */

/* The value before (GEMSS_HFEn==2) are special cases */

#if(GEMSS_HFEn==103)
    #define GEMSS_K3 31U
#elif(GEMSS_HFEn==184)
    #define GEMSS_K3 27U
    #define GEMSS_K2 24U
    #define GEMSS_K1 1U
#elif(GEMSS_HFEn==265)
    #define GEMSS_K3 42U
#elif(GEMSS_HFEn==266)
    #define GEMSS_K3 47U
#elif(GEMSS_HFEn==312)
    #define GEMSS_K3 128U
    #define GEMSS_K2 15U
    #define GEMSS_K1 5U
#elif(GEMSS_HFEn==313)
    #define GEMSS_K3 79U
#elif(GEMSS_HFEn==354)
    #define GEMSS_K3 99U
#elif(GEMSS_HFEn==358)
    #define GEMSS_K3 57U
#elif(GEMSS_HFEn==402)
    #define GEMSS_K3 171U
#elif(GEMSS_HFEn==448)
    #define GEMSS_K3 64U
    #define GEMSS_K2 39U
    #define GEMSS_K1 33U
#elif(GEMSS_HFEn==544)
    #define GEMSS_K3 128U
    #define GEMSS_K2 3U
    #define GEMSS_K1 1U
#elif(GEMSS_HFEn==2)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==3)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==4)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==5)
    #define GEMSS_K3 2
#elif(GEMSS_HFEn==6)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==7)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==8)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==9)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==10)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==11)
    #define GEMSS_K3 2
#elif(GEMSS_HFEn==12)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==13)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==14)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==15)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==16)
    #define GEMSS_K3 5
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==17)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==18)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==19)
    #define GEMSS_K3 5
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==20)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==21)
    #define GEMSS_K3 2
#elif(GEMSS_HFEn==22)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==23)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==24)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==25)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==26)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==27)
    #define GEMSS_K3 5
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==28)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==29)
    #define GEMSS_K3 2
#elif(GEMSS_HFEn==30)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==31)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==32)
    #define GEMSS_K3 11
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==33)
    #define GEMSS_K3 10
#elif(GEMSS_HFEn==34)
    #define GEMSS_K3 7
#elif(GEMSS_HFEn==35)
    #define GEMSS_K3 2
#elif(GEMSS_HFEn==36)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==37)
    #define GEMSS_K3 6
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==38)
    #define GEMSS_K3 6
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==39)
    #define GEMSS_K3 4
#elif(GEMSS_HFEn==40)
    #define GEMSS_K3 9
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==41)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==42)
    #define GEMSS_K3 7
#elif(GEMSS_HFEn==43)
    #define GEMSS_K3 6
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==44)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==45)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==46)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==47)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==48)
    #define GEMSS_K3 11
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==49)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==50)
    #define GEMSS_K3 9
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==51)
    #define GEMSS_K3 6
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==52)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==53)
    #define GEMSS_K3 6
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==54)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==55)
    #define GEMSS_K3 7
#elif(GEMSS_HFEn==56)
    #define GEMSS_K3 15
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==57)
    #define GEMSS_K3 4
#elif(GEMSS_HFEn==58)
    #define GEMSS_K3 19
#elif(GEMSS_HFEn==59)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==60)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==61)
    #define GEMSS_K3 5
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==62)
    #define GEMSS_K3 29
#elif(GEMSS_HFEn==63)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==64)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==65)
    #define GEMSS_K3 18
#elif(GEMSS_HFEn==66)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==67)
    #define GEMSS_K3 5
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==68)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==69)
    #define GEMSS_K3 10
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==70)
    #define GEMSS_K3 5
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==71)
    #define GEMSS_K3 6
#elif(GEMSS_HFEn==72)
    #define GEMSS_K3 16
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==73)
    #define GEMSS_K3 25
#elif(GEMSS_HFEn==74)
    #define GEMSS_K3 6
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==75)
    #define GEMSS_K3 6
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==76)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==77)
    #define GEMSS_K3 10
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==78)
    #define GEMSS_K3 7
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==79)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==80)
    #define GEMSS_K3 14
    #define GEMSS_K2 13
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==81)
    #define GEMSS_K3 4
#elif(GEMSS_HFEn==82)
    #define GEMSS_K3 8
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==83)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==84)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==85)
    #define GEMSS_K3 8
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==86)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==87)
    #define GEMSS_K3 13
#elif(GEMSS_HFEn==88)
    #define GEMSS_K3 9
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==89)
    #define GEMSS_K3 7
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==90)
    #define GEMSS_K3 27
#elif(GEMSS_HFEn==91)
    #define GEMSS_K3 8
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==92)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==93)
    #define GEMSS_K3 2
#elif(GEMSS_HFEn==94)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==95)
    #define GEMSS_K3 11
#elif(GEMSS_HFEn==96)
    #define GEMSS_K3 16
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==97)
    #define GEMSS_K3 6
#elif(GEMSS_HFEn==98)
    #define GEMSS_K3 11
#elif(GEMSS_HFEn==99)
    #define GEMSS_K3 6
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==100)
    #define GEMSS_K3 15
#elif(GEMSS_HFEn==101)
    #define GEMSS_K3 7
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==102)
    #define GEMSS_K3 29
#elif(GEMSS_HFEn==103)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==104)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==105)
    #define GEMSS_K3 4
#elif(GEMSS_HFEn==106)
    #define GEMSS_K3 15
#elif(GEMSS_HFEn==107)
    #define GEMSS_K3 16
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==108)
    #define GEMSS_K3 17
#elif(GEMSS_HFEn==109)
    #define GEMSS_K3 7
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==110)
    #define GEMSS_K3 6
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==111)
    #define GEMSS_K3 10
#elif(GEMSS_HFEn==112)
    #define GEMSS_K3 15
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==113)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==114)
    #define GEMSS_K3 11
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==115)
    #define GEMSS_K3 12
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==116)
    #define GEMSS_K3 4
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==117)
    #define GEMSS_K3 5
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==118)
    #define GEMSS_K3 9
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==119)
    #define GEMSS_K3 8
#elif(GEMSS_HFEn==120)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==121)
    #define GEMSS_K3 18
#elif(GEMSS_HFEn==122)
    #define GEMSS_K3 6
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==123)
    #define GEMSS_K3 2
#elif(GEMSS_HFEn==124)
    #define GEMSS_K3 19
#elif(GEMSS_HFEn==125)
    #define GEMSS_K3 18
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==126)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==127)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==128)
    #define GEMSS_K3 7
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==129)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==130)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==131)
    #define GEMSS_K3 13
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==132)
    #define GEMSS_K3 17
#elif(GEMSS_HFEn==133)
    #define GEMSS_K3 18
    #define GEMSS_K2 15
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==134)
    #define GEMSS_K3 7
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==135)
    #define GEMSS_K3 11
#elif(GEMSS_HFEn==136)
    #define GEMSS_K3 11
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==137)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==138)
    #define GEMSS_K3 8
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==139)
    #define GEMSS_K3 14
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==140)
    #define GEMSS_K3 15
#elif(GEMSS_HFEn==141)
    #define GEMSS_K3 10
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==142)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==143)
    #define GEMSS_K3 9
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==144)
    #define GEMSS_K3 11
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==145)
    #define GEMSS_K3 6
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==146)
    #define GEMSS_K3 9
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==147)
    #define GEMSS_K3 14
#elif(GEMSS_HFEn==148)
    #define GEMSS_K3 27
#elif(GEMSS_HFEn==149)
    #define GEMSS_K3 18
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==150)
    #define GEMSS_K3 8
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==151)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==152)
    #define GEMSS_K3 16
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==153)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==154)
    #define GEMSS_K3 15
#elif(GEMSS_HFEn==155)
    #define GEMSS_K3 18
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==156)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==157)
    #define GEMSS_K3 16
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==158)
    #define GEMSS_K3 15
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==159)
    #define GEMSS_K3 31
#elif(GEMSS_HFEn==160)
    #define GEMSS_K3 7
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==161)
    #define GEMSS_K3 18
#elif(GEMSS_HFEn==162)
    #define GEMSS_K3 27
#elif(GEMSS_HFEn==163)
    #define GEMSS_K3 8
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==164)
    #define GEMSS_K3 13
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==165)
    #define GEMSS_K3 16
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==166)
    #define GEMSS_K3 6
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==167)
    #define GEMSS_K3 6
#elif(GEMSS_HFEn==168)
    #define GEMSS_K3 18
    #define GEMSS_K2 15
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==169)
    #define GEMSS_K3 12
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==170)
    #define GEMSS_K3 11
#elif(GEMSS_HFEn==171)
    #define GEMSS_K3 14
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==172)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==173)
    #define GEMSS_K3 10
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==174)
    #define GEMSS_K3 13
#elif(GEMSS_HFEn==175)
    #define GEMSS_K3 16
#elif(GEMSS_HFEn==176)
    #define GEMSS_K3 15
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==177)
    #define GEMSS_K3 8
#elif(GEMSS_HFEn==178)
    #define GEMSS_K3 31
#elif(GEMSS_HFEn==179)
    #define GEMSS_K3 4
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==180)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==181)
    #define GEMSS_K3 7
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==182)
    #define GEMSS_K3 8
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==183)
    #define GEMSS_K3 14
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==184)
    #define GEMSS_K3 18
    #define GEMSS_K2 13
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==185)
    #define GEMSS_K3 24
#elif(GEMSS_HFEn==186)
    #define GEMSS_K3 11
#elif(GEMSS_HFEn==187)
    #define GEMSS_K3 18
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==188)
    #define GEMSS_K3 15
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==189)
    #define GEMSS_K3 18
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==190)
    #define GEMSS_K3 18
    #define GEMSS_K2 17
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==191)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==192)
    #define GEMSS_K3 7
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==193)
    #define GEMSS_K3 15
#elif(GEMSS_HFEn==194)
    #define GEMSS_K3 11
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==195)
    #define GEMSS_K3 10
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==196)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==197)
    #define GEMSS_K3 14
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==198)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==199)
    #define GEMSS_K3 9
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==200)
    #define GEMSS_K3 8
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==201)
    #define GEMSS_K3 14
#elif(GEMSS_HFEn==202)
    #define GEMSS_K3 8
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==203)
    #define GEMSS_K3 8
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==204)
    #define GEMSS_K3 27
#elif(GEMSS_HFEn==205)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==206)
    #define GEMSS_K3 11
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==207)
    #define GEMSS_K3 9
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==208)
    #define GEMSS_K3 9
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==209)
    #define GEMSS_K3 6
#elif(GEMSS_HFEn==210)
    #define GEMSS_K3 7
#elif(GEMSS_HFEn==211)
    #define GEMSS_K3 12
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==212)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==213)
    #define GEMSS_K3 8
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==214)
    #define GEMSS_K3 5
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==215)
    #define GEMSS_K3 23
#elif(GEMSS_HFEn==216)
    #define GEMSS_K3 7
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==217)
    #define GEMSS_K3 12
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==218)
    #define GEMSS_K3 11
#elif(GEMSS_HFEn==219)
    #define GEMSS_K3 8
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==220)
    #define GEMSS_K3 7
#elif(GEMSS_HFEn==221)
    #define GEMSS_K3 16
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==222)
    #define GEMSS_K3 6
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==223)
    #define GEMSS_K3 8
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==224)
    #define GEMSS_K3 21
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==225)
    #define GEMSS_K3 32
#elif(GEMSS_HFEn==226)
    #define GEMSS_K3 20
    #define GEMSS_K2 17
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==227)
    #define GEMSS_K3 20
    #define GEMSS_K2 12
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==228)
    #define GEMSS_K3 8
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==229)
    #define GEMSS_K3 10
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==230)
    #define GEMSS_K3 13
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==231)
    #define GEMSS_K3 26
#elif(GEMSS_HFEn==232)
    #define GEMSS_K3 23
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==233)
    #define GEMSS_K3 9
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==234)
    #define GEMSS_K3 31
#elif(GEMSS_HFEn==235)
    #define GEMSS_K3 9
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==236)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==237)
    #define GEMSS_K3 7
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==238)
    #define GEMSS_K3 5
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==239)
    #define GEMSS_K3 12
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==240)
    #define GEMSS_K3 16
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==241)
    #define GEMSS_K3 15
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==242)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==243)
    #define GEMSS_K3 8
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==244)
    #define GEMSS_K3 9
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==245)
    #define GEMSS_K3 6
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==246)
    #define GEMSS_K3 11
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==247)
    #define GEMSS_K3 21
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==248)
    #define GEMSS_K3 26
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==249)
    #define GEMSS_K3 7
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==250)
    #define GEMSS_K3 15
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==251)
    #define GEMSS_K3 14
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==252)
    #define GEMSS_K3 15
#elif(GEMSS_HFEn==253)
    #define GEMSS_K3 7
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==254)
    #define GEMSS_K3 7
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==255)
    #define GEMSS_K3 11
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==256)
    #define GEMSS_K3 16
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==257)
    #define GEMSS_K3 12
#elif(GEMSS_HFEn==258)
    #define GEMSS_K3 26
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==259)
    #define GEMSS_K3 15
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==260)
    #define GEMSS_K3 15
#elif(GEMSS_HFEn==261)
    #define GEMSS_K3 11
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==262)
    #define GEMSS_K3 22
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==263)
    #define GEMSS_K3 13
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==264)
    #define GEMSS_K3 10
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==265)
    #define GEMSS_K3 15
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==266)
    #define GEMSS_K3 7
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==267)
    #define GEMSS_K3 14
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==268)
    #define GEMSS_K3 25
#elif(GEMSS_HFEn==269)
    #define GEMSS_K3 7
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==270)
    #define GEMSS_K3 18
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==271)
    #define GEMSS_K3 16
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==272)
    #define GEMSS_K3 27
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==273)
    #define GEMSS_K3 23
#elif(GEMSS_HFEn==274)
    #define GEMSS_K3 11
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==275)
    #define GEMSS_K3 16
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==276)
    #define GEMSS_K3 6
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==277)
    #define GEMSS_K3 30
    #define GEMSS_K2 19
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==278)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==279)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==280)
    #define GEMSS_K3 15
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==281)
    #define GEMSS_K3 9
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==282)
    #define GEMSS_K3 8
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==283)
    #define GEMSS_K3 26
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==284)
    #define GEMSS_K3 12
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==285)
    #define GEMSS_K3 19
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==286)
    #define GEMSS_K3 15
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==287)
    #define GEMSS_K3 25
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==288)
    #define GEMSS_K3 11
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==289)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==290)
    #define GEMSS_K3 11
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==291)
    #define GEMSS_K3 16
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==292)
    #define GEMSS_K3 7
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==293)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==294)
    #define GEMSS_K3 16
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==295)
    #define GEMSS_K3 9
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==296)
    #define GEMSS_K3 15
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==297)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==298)
    #define GEMSS_K3 23
    #define GEMSS_K2 15
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==299)
    #define GEMSS_K3 18
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==300)
    #define GEMSS_K3 5
#elif(GEMSS_HFEn==301)
    #define GEMSS_K3 11
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==302)
    #define GEMSS_K3 16
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==303)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==304)
    #define GEMSS_K3 11
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==305)
    #define GEMSS_K3 9
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==306)
    #define GEMSS_K3 7
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==307)
    #define GEMSS_K3 25
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==308)
    #define GEMSS_K3 15
#elif(GEMSS_HFEn==309)
    #define GEMSS_K3 18
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==310)
    #define GEMSS_K3 8
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==311)
    #define GEMSS_K3 13
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==312)
    #define GEMSS_K3 14
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==313)
    #define GEMSS_K3 7
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==314)
    #define GEMSS_K3 15
#elif(GEMSS_HFEn==315)
    #define GEMSS_K3 10
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==316)
    #define GEMSS_K3 10
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==317)
    #define GEMSS_K3 7
    #define GEMSS_K2 4
    #define GEMSS_K1 2
#elif(GEMSS_HFEn==318)
    #define GEMSS_K3 12
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==319)
    #define GEMSS_K3 11
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==320)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==321)
    #define GEMSS_K3 31
#elif(GEMSS_HFEn==322)
    #define GEMSS_K3 17
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==323)
    #define GEMSS_K3 10
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==324)
    #define GEMSS_K3 4
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==325)
    #define GEMSS_K3 15
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==326)
    #define GEMSS_K3 10
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==327)
    #define GEMSS_K3 18
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==328)
    #define GEMSS_K3 8
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==329)
    #define GEMSS_K3 12
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==330)
    #define GEMSS_K3 12
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==331)
    #define GEMSS_K3 16
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==332)
    #define GEMSS_K3 6
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==333)
    #define GEMSS_K3 2
#elif(GEMSS_HFEn==334)
    #define GEMSS_K3 5
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==335)
    #define GEMSS_K3 14
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==336)
    #define GEMSS_K3 7
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==337)
    #define GEMSS_K3 10
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==338)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==339)
    #define GEMSS_K3 23
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==340)
    #define GEMSS_K3 14
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==341)
    #define GEMSS_K3 24
    #define GEMSS_K2 23
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==342)
    #define GEMSS_K3 11
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==343)
    #define GEMSS_K3 15
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==344)
    #define GEMSS_K3 7
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==345)
    #define GEMSS_K3 22
#elif(GEMSS_HFEn==346)
    #define GEMSS_K3 21
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==347)
    #define GEMSS_K3 14
    #define GEMSS_K2 12
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==348)
    #define GEMSS_K3 18
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==349)
    #define GEMSS_K3 12
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==350)
    #define GEMSS_K3 11
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==351)
    #define GEMSS_K3 11
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==352)
    #define GEMSS_K3 13
    #define GEMSS_K2 11
    #define GEMSS_K1 6
#elif(GEMSS_HFEn==353)
    #define GEMSS_K3 20
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==354)
    #define GEMSS_K3 16
    #define GEMSS_K2 15
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==355)
    #define GEMSS_K3 6
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==356)
    #define GEMSS_K3 12
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==357)
    #define GEMSS_K3 28
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==358)
    #define GEMSS_K3 24
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==359)
    #define GEMSS_K3 9
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==360)
    #define GEMSS_K3 13
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==361)
    #define GEMSS_K3 7
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==362)
    #define GEMSS_K3 13
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==363)
    #define GEMSS_K3 8
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==364)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==365)
    #define GEMSS_K3 18
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==366)
    #define GEMSS_K3 29
#elif(GEMSS_HFEn==367)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==368)
    #define GEMSS_K3 8
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==369)
    #define GEMSS_K3 14
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==370)
    #define GEMSS_K3 9
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==371)
    #define GEMSS_K3 16
    #define GEMSS_K2 15
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==372)
    #define GEMSS_K3 17
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==373)
    #define GEMSS_K3 9
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==374)
    #define GEMSS_K3 16
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==375)
    #define GEMSS_K3 16
#elif(GEMSS_HFEn==376)
    #define GEMSS_K3 15
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==377)
    #define GEMSS_K3 8
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==378)
    #define GEMSS_K3 17
    #define GEMSS_K2 13
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==379)
    #define GEMSS_K3 17
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==380)
    #define GEMSS_K3 17
    #define GEMSS_K2 12
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==381)
    #define GEMSS_K3 5
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==382)
    #define GEMSS_K3 9
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==383)
    #define GEMSS_K3 9
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==384)
    #define GEMSS_K3 27
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==385)
    #define GEMSS_K3 6
#elif(GEMSS_HFEn==386)
    #define GEMSS_K3 16
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==387)
    #define GEMSS_K3 8
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==388)
    #define GEMSS_K3 14
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==389)
    #define GEMSS_K3 17
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==390)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==391)
    #define GEMSS_K3 28
#elif(GEMSS_HFEn==392)
    #define GEMSS_K3 15
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==393)
    #define GEMSS_K3 7
#elif(GEMSS_HFEn==394)
    #define GEMSS_K3 15
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==395)
    #define GEMSS_K3 22
    #define GEMSS_K2 20
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==396)
    #define GEMSS_K3 25
#elif(GEMSS_HFEn==397)
    #define GEMSS_K3 22
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==398)
    #define GEMSS_K3 23
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==399)
    #define GEMSS_K3 26
#elif(GEMSS_HFEn==400)
    #define GEMSS_K3 14
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==401)
    #define GEMSS_K3 19
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==402)
    #define GEMSS_K3 22
    #define GEMSS_K2 19
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==403)
    #define GEMSS_K3 28
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==404)
    #define GEMSS_K3 14
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==405)
    #define GEMSS_K3 28
    #define GEMSS_K2 18
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==406)
    #define GEMSS_K3 29
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==407)
    #define GEMSS_K3 13
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==408)
    #define GEMSS_K3 7
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==409)
    #define GEMSS_K3 15
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==410)
    #define GEMSS_K3 16
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==411)
    #define GEMSS_K3 18
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==412)
    #define GEMSS_K3 18
    #define GEMSS_K2 12
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==413)
    #define GEMSS_K3 10
    #define GEMSS_K2 7
    #define GEMSS_K1 6
#elif(GEMSS_HFEn==414)
    #define GEMSS_K3 13
#elif(GEMSS_HFEn==415)
    #define GEMSS_K3 12
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==416)
    #define GEMSS_K3 27
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==417)
    #define GEMSS_K3 10
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==418)
    #define GEMSS_K3 15
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==419)
    #define GEMSS_K3 21
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==420)
    #define GEMSS_K3 7
#elif(GEMSS_HFEn==421)
    #define GEMSS_K3 7
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==422)
    #define GEMSS_K3 10
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==423)
    #define GEMSS_K3 25
#elif(GEMSS_HFEn==424)
    #define GEMSS_K3 19
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==425)
    #define GEMSS_K3 12
#elif(GEMSS_HFEn==426)
    #define GEMSS_K3 20
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==427)
    #define GEMSS_K3 18
    #define GEMSS_K2 13
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==428)
    #define GEMSS_K3 24
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==429)
    #define GEMSS_K3 13
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==430)
    #define GEMSS_K3 14
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==431)
    #define GEMSS_K3 5
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==432)
    #define GEMSS_K3 23
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==433)
    #define GEMSS_K3 15
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==434)
    #define GEMSS_K3 12
    #define GEMSS_K2 11
    #define GEMSS_K1 5
#elif(GEMSS_HFEn==435)
    #define GEMSS_K3 13
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==436)
    #define GEMSS_K3 15
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==437)
    #define GEMSS_K3 6
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==438)
    #define GEMSS_K3 20
    #define GEMSS_K2 19
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==439)
    #define GEMSS_K3 10
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==440)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==441)
    #define GEMSS_K3 7
#elif(GEMSS_HFEn==442)
    #define GEMSS_K3 21
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==443)
    #define GEMSS_K3 10
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==444)
    #define GEMSS_K3 12
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==445)
    #define GEMSS_K3 23
    #define GEMSS_K2 12
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==446)
    #define GEMSS_K3 19
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==447)
    #define GEMSS_K3 9
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==448)
    #define GEMSS_K3 13
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==449)
    #define GEMSS_K3 17
    #define GEMSS_K2 12
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==450)
    #define GEMSS_K3 22
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==451)
    #define GEMSS_K3 16
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==452)
    #define GEMSS_K3 10
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==453)
    #define GEMSS_K3 19
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==454)
    #define GEMSS_K3 8
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==455)
    #define GEMSS_K3 15
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==456)
    #define GEMSS_K3 25
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==457)
    #define GEMSS_K3 16
#elif(GEMSS_HFEn==458)
    #define GEMSS_K3 27
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==459)
    #define GEMSS_K3 12
    #define GEMSS_K2 5
    #define GEMSS_K1 2
#elif(GEMSS_HFEn==460)
    #define GEMSS_K3 19
#elif(GEMSS_HFEn==461)
    #define GEMSS_K3 7
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==462)
    #define GEMSS_K3 20
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==463)
    #define GEMSS_K3 18
    #define GEMSS_K2 17
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==464)
    #define GEMSS_K3 19
    #define GEMSS_K2 18
    #define GEMSS_K1 13
#elif(GEMSS_HFEn==465)
    #define GEMSS_K3 31
#elif(GEMSS_HFEn==466)
    #define GEMSS_K3 16
    #define GEMSS_K2 15
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==467)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==468)
    #define GEMSS_K3 27
#elif(GEMSS_HFEn==469)
    #define GEMSS_K3 9
    #define GEMSS_K2 5
    #define GEMSS_K1 2
#elif(GEMSS_HFEn==470)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==471)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==472)
    #define GEMSS_K3 17
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==473)
    #define GEMSS_K3 11
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==474)
    #define GEMSS_K3 22
    #define GEMSS_K2 17
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==475)
    #define GEMSS_K3 18
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==476)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==477)
    #define GEMSS_K3 16
    #define GEMSS_K2 15
    #define GEMSS_K1 7
#elif(GEMSS_HFEn==478)
    #define GEMSS_K3 6
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==479)
    #define GEMSS_K3 19
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==480)
    #define GEMSS_K3 15
    #define GEMSS_K2 9
    #define GEMSS_K1 6
#elif(GEMSS_HFEn==481)
    #define GEMSS_K3 10
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==482)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==483)
    #define GEMSS_K3 9
    #define GEMSS_K2 6
    #define GEMSS_K1 4
#elif(GEMSS_HFEn==484)
    #define GEMSS_K3 11
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==485)
    #define GEMSS_K3 30
    #define GEMSS_K2 25
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==486)
    #define GEMSS_K3 26
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==487)
    #define GEMSS_K3 14
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==488)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==489)
    #define GEMSS_K3 14
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==490)
    #define GEMSS_K3 17
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==491)
    #define GEMSS_K3 15
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==492)
    #define GEMSS_K3 7
#elif(GEMSS_HFEn==493)
    #define GEMSS_K3 20
    #define GEMSS_K2 15
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==494)
    #define GEMSS_K3 17
#elif(GEMSS_HFEn==495)
    #define GEMSS_K3 15
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==496)
    #define GEMSS_K3 21
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==497)
    #define GEMSS_K3 13
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==498)
    #define GEMSS_K3 31
    #define GEMSS_K2 12
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==499)
    #define GEMSS_K3 20
    #define GEMSS_K2 12
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==500)
    #define GEMSS_K3 27
#elif(GEMSS_HFEn==501)
    #define GEMSS_K3 23
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==502)
    #define GEMSS_K3 16
    #define GEMSS_K2 12
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==503)
    #define GEMSS_K3 3
#elif(GEMSS_HFEn==504)
    #define GEMSS_K3 15
    #define GEMSS_K2 14
    #define GEMSS_K1 6
#elif(GEMSS_HFEn==505)
    #define GEMSS_K3 24
    #define GEMSS_K2 18
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==506)
    #define GEMSS_K3 23
#elif(GEMSS_HFEn==507)
    #define GEMSS_K3 26
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==508)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==509)
    #define GEMSS_K3 24
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==510)
    #define GEMSS_K3 6
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==511)
    #define GEMSS_K3 10
#elif(GEMSS_HFEn==512)
    #define GEMSS_K3 8
    #define GEMSS_K2 5
    #define GEMSS_K1 2
#elif(GEMSS_HFEn==513)
    #define GEMSS_K3 26
#elif(GEMSS_HFEn==514)
    #define GEMSS_K3 14
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==515)
    #define GEMSS_K3 25
    #define GEMSS_K2 18
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==516)
    #define GEMSS_K3 21
#elif(GEMSS_HFEn==517)
    #define GEMSS_K3 28
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==518)
    #define GEMSS_K3 17
    #define GEMSS_K2 15
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==519)
    #define GEMSS_K3 17
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==520)
    #define GEMSS_K3 15
    #define GEMSS_K2 11
    #define GEMSS_K1 2
#elif(GEMSS_HFEn==521)
    #define GEMSS_K3 32
#elif(GEMSS_HFEn==522)
    #define GEMSS_K3 29
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==523)
    #define GEMSS_K3 18
    #define GEMSS_K2 14
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==524)
    #define GEMSS_K3 9
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==525)
    #define GEMSS_K3 6
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==526)
    #define GEMSS_K3 9
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==527)
    #define GEMSS_K3 9
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==528)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 2
#elif(GEMSS_HFEn==529)
    #define GEMSS_K3 7
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==530)
    #define GEMSS_K3 25
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==531)
    #define GEMSS_K3 18
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==532)
    #define GEMSS_K3 1
#elif(GEMSS_HFEn==533)
    #define GEMSS_K3 4
    #define GEMSS_K2 3
    #define GEMSS_K1 2
#elif(GEMSS_HFEn==534)
    #define GEMSS_K3 7
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==535)
    #define GEMSS_K3 13
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==536)
    #define GEMSS_K3 7
    #define GEMSS_K2 5
    #define GEMSS_K1 3
#elif(GEMSS_HFEn==537)
    #define GEMSS_K3 10
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==538)
    #define GEMSS_K3 5
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==539)
    #define GEMSS_K3 27
    #define GEMSS_K2 22
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==540)
    #define GEMSS_K3 9
#elif(GEMSS_HFEn==541)
    #define GEMSS_K3 30
    #define GEMSS_K2 27
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==542)
    #define GEMSS_K3 8
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==543)
    #define GEMSS_K3 16
#elif(GEMSS_HFEn==544)
    #define GEMSS_K3 8
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==545)
    #define GEMSS_K3 14
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==546)
    #define GEMSS_K3 8
    #define GEMSS_K2 2
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==547)
    #define GEMSS_K3 20
    #define GEMSS_K2 17
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==548)
    #define GEMSS_K3 25
    #define GEMSS_K2 17
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==549)
    #define GEMSS_K3 25
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==550)
    #define GEMSS_K3 14
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==551)
    #define GEMSS_K3 9
    #define GEMSS_K2 4
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==552)
    #define GEMSS_K3 19
    #define GEMSS_K2 16
    #define GEMSS_K1 9
#elif(GEMSS_HFEn==553)
    #define GEMSS_K3 21
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==554)
    #define GEMSS_K3 21
    #define GEMSS_K2 11
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==555)
    #define GEMSS_K3 32
    #define GEMSS_K2 16
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==556)
    #define GEMSS_K3 6
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==557)
    #define GEMSS_K3 26
    #define GEMSS_K2 16
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==558)
    #define GEMSS_K3 25
    #define GEMSS_K2 5
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==559)
    #define GEMSS_K3 13
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==560)
    #define GEMSS_K3 11
    #define GEMSS_K2 9
    #define GEMSS_K1 6
#elif(GEMSS_HFEn==561)
    #define GEMSS_K3 14
    #define GEMSS_K2 13
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==562)
    #define GEMSS_K3 27
    #define GEMSS_K2 20
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==563)
    #define GEMSS_K3 20
    #define GEMSS_K2 7
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==564)
    #define GEMSS_K3 6
    #define GEMSS_K2 3
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==565)
    #define GEMSS_K3 11
    #define GEMSS_K2 6
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==566)
    #define GEMSS_K3 20
    #define GEMSS_K2 13
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==567)
    #define GEMSS_K3 28
#elif(GEMSS_HFEn==568)
    #define GEMSS_K3 26
    #define GEMSS_K2 9
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==569)
    #define GEMSS_K3 12
    #define GEMSS_K2 10
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==570)
    #define GEMSS_K3 19
    #define GEMSS_K2 16
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==571)
    #define GEMSS_K3 10
    #define GEMSS_K2 5
    #define GEMSS_K1 2
#elif(GEMSS_HFEn==572)
    #define GEMSS_K3 12
    #define GEMSS_K2 8
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==573)
    #define GEMSS_K3 24
    #define GEMSS_K2 19
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==574)
    #define GEMSS_K3 13
#elif(GEMSS_HFEn==575)
    #define GEMSS_K3 25
    #define GEMSS_K2 18
    #define GEMSS_K1 1
#elif(GEMSS_HFEn==576)
    #define GEMSS_K3 22
    #define GEMSS_K2 19
    #define GEMSS_K1 1
#endif



#ifdef GEMSS_K2
    /* Choice of pentanomial for modular reduction in GF(2^n) */
    #define GEMSS___PENTANOMIAL_GF2N__
#elif (defined GEMSS_K3)
    /* Choice of trinomial for modular reduction in GF(2^n) */
    #define GEMSS___TRINOMIAL_GF2N__
#endif



#if (defined(GEMSS___TRINOMIAL_GF2N__)&&defined(GEMSS___PENTANOMIAL_GF2N__))||\
  (!(defined(GEMSS___TRINOMIAL_GF2N__)||defined(GEMSS___PENTANOMIAL_GF2N__)))
    #error "Choose between trinomial or pentanomial"
#endif

#ifdef GEMSS___TRINOMIAL_GF2N__
    #if (!GEMSS_K3)
        #error "GEMSS_K3!=0 is required"
    #endif

    #if ( (GEMSS_K3>32) && (!((GEMSS_K3<64)&&(GEMSS_HFEn<289)&&(GEMSS_HFEn>256))) && (GEMSS_HFEn!=354) &&\
(GEMSS_HFEn!=358) && (GEMSS_HFEn!=402) )
        #error "The modular reduction does not support GEMSS_K3>32"
    #endif
#endif

#ifdef GEMSS___PENTANOMIAL_GF2N__
    #if ((GEMSS_K1==0)||(GEMSS_K1>=GEMSS_K2)||(GEMSS_K2>=GEMSS_K3))
        #error "0 < GEMSS_K1 < GEMSS_K2 < GEMSS_K3 is required"
    #endif

    #if (((GEMSS_HFEn!=312)&&(GEMSS_HFEn!=448)&&(GEMSS_HFEn!=544)&&(GEMSS_K3>32))||((GEMSS_HFEn==448)&&\
(GEMSS_K3>64))||((GEMSS_HFEn==312)&&(GEMSS_K3!=128)&&(GEMSS_K2!=15)&&(GEMSS_K1!=5))||\
((GEMSS_HFEn==544)&&(GEMSS_K3!=128)&&(GEMSS_K2!=3)&&(GEMSS_K1!=1)))
        #error "The modular reduction does not support GEMSS_K3>32"
    #endif
#endif



#endif

