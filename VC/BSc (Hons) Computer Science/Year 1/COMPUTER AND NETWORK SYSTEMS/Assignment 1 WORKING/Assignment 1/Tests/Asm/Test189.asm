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
LDA #0x003C
LD B,#0x0069
CMP A,B
RHI
LDA #0x004D
RTN
HLT 
J507:
LDA #0x0054
LD B,#0x0062
CMP A,B
RHI
LDA #0x00B7
RTN
HLT 
J508:
LDA #0x006A
LD B,#0x00F2
CMP A,B
RHI
LDA #0x0032
RTN
HLT 
J509:
LDA #0x0033
LD B,#0x00A1
CMP A,B
RHI
LDA #0x00F3
RTN
HLT 
J510:
LDA #0x008E
LD B,#0x00C9
CMP A,B
RHI
LDA #0x0026
RTN
HLT 
J511:
LDA #0x00EC
LD B,#0x00D8
CMP A,B
RHI
LDA #0x0062
RTN
HLT 
J512:
LDA #0x00FB
LD B,#0x00D9
CMP A,B
RHI
LDA #0x00D7
RTN
HLT 
J513:
LDA #0x0076
LD B,#0x00ED
CMP A,B
RHI
LDA #0x00EB
RTN
HLT 
J514:
LDA #0x0064
LD B,#0x00BE
CMP A,B
RHI
LDA #0x00B8
RTN
HLT 
J515:
LDA #0x0035
LD B,#0x0063
CMP A,B
RHI
LDA #0x00BD
RTN
HLT 
J516:
LDA #0x0015
LD B,#0x00B1
CMP A,B
RHI
LDA #0x0004
RTN
HLT 
J517:
LDA #0x00C5
LD B,#0x0071
CMP A,B
RHI
LDA #0x001C
RTN
HLT 
