LDZ #0x342A
LDA #0x00BB
STA 0xAADD
LDA #0x00BB
STA 0xAADE
LODS #0xAA54
CALL J506
STA 0x01FA
CALL J507
STA 0x01FB
CALL J508
STA 0x01FC
CALL J509
STA 0x01FD
CALL J510
STA 0x01FE
CALL J511
STA 0x01FF
CALL J512
STA 0x0200
CALL J513
STA 0x0201
CALL J514
STA 0x0202
CALL J515
STA 0x0203
CALL J516
STA 0x0204
CALL J517
STA 0x0205
HLT 
J506:
LDA #0x006F
LD B,#0x0074
CMP A,B
RCS
LDA #0x007D
RTN
HLT 
J507:
LDA #0x0079
LD B,#0x008F
CMP A,B
RCS
LDA #0x0095
RTN
HLT 
J508:
LDA #0x00D7
LD B,#0x0079
CMP A,B
RCS
LDA #0x0004
RTN
HLT 
J509:
LDA #0x000C
LD B,#0x00B2
CMP A,B
RCS
LDA #0x0037
RTN
HLT 
J510:
LDA #0x00E2
LD B,#0x0072
CMP A,B
RCS
LDA #0x0098
RTN
HLT 
J511:
LDA #0x00E3
LD B,#0x00C3
CMP A,B
RCS
LDA #0x004A
RTN
HLT 
J512:
LDA #0x00EB
LD B,#0x00CC
CMP A,B
RCS
LDA #0x000F
RTN
HLT 
J513:
LDA #0x00F2
LD B,#0x00F4
CMP A,B
RCS
LDA #0x00C6
RTN
HLT 
J514:
LDA #0x0017
LD B,#0x0057
CMP A,B
RCS
LDA #0x005D
RTN
HLT 
J515:
LDA #0x003F
LD B,#0x003F
CMP A,B
RCS
LDA #0x0023
RTN
HLT 
J516:
LDA #0x0071
LD B,#0x00BE
CMP A,B
RCS
LDA #0x00B6
RTN
HLT 
J517:
LDA #0x0049
LD B,#0x00CA
CMP A,B
RCS
LDA #0x0072
RTN
HLT 
