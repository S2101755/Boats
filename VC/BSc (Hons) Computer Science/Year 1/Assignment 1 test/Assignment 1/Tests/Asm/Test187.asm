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
LDA #0x006D
LD B,#0x0071
CMP A,B
RMI
LDA #0x005C
RTN
HLT 
J507:
LDA #0x0064
LD B,#0x005C
CMP A,B
RMI
LDA #0x0036
RTN
HLT 
J508:
LDA #0x0054
LD B,#0x0040
CMP A,B
RMI
LDA #0x0080
RTN
HLT 
J509:
LDA #0x0027
LD B,#0x002E
CMP A,B
RMI
LDA #0x008D
RTN
HLT 
J510:
LDA #0x00AA
LD B,#0x00E0
CMP A,B
RMI
LDA #0x0075
RTN
HLT 
J511:
LDA #0x0058
LD B,#0x00D6
CMP A,B
RMI
LDA #0x0032
RTN
HLT 
J512:
LDA #0x008C
LD B,#0x003A
CMP A,B
RMI
LDA #0x0051
RTN
HLT 
J513:
LDA #0x009B
LD B,#0x0047
CMP A,B
RMI
LDA #0x0077
RTN
HLT 
J514:
LDA #0x0075
LD B,#0x00C9
CMP A,B
RMI
LDA #0x0021
RTN
HLT 
J515:
LDA #0x0022
LD B,#0x0026
CMP A,B
RMI
LDA #0x00DC
RTN
HLT 
J516:
LDA #0x00BC
LD B,#0x001F
CMP A,B
RMI
LDA #0x007B
RTN
HLT 
J517:
LDA #0x00B3
LD B,#0x0086
CMP A,B
RMI
LDA #0x00DE
RTN
HLT 
