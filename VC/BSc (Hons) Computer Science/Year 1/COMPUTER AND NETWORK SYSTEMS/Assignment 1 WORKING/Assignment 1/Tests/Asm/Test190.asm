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
LDA #0x0077
LD B,#0x00C0
CMP A,B
RLE
LDA #0x0092
RTN
HLT 
J507:
LDA #0x005E
LD B,#0x009D
CMP A,B
RLE
LDA #0x00E1
RTN
HLT 
J508:
LDA #0x0027
LD B,#0x0002
CMP A,B
RLE
LDA #0x0057
RTN
HLT 
J509:
LDA #0x00D0
LD B,#0x00EE
CMP A,B
RLE
LDA #0x00BA
RTN
HLT 
J510:
LDA #0x00E3
LD B,#0x0097
CMP A,B
RLE
LDA #0x00B0
RTN
HLT 
J511:
LDA #0x0090
LD B,#0x0083
CMP A,B
RLE
LDA #0x00D9
RTN
HLT 
J512:
LDA #0x00EF
LD B,#0x0005
CMP A,B
RLE
LDA #0x0096
RTN
HLT 
J513:
LDA #0x00EF
LD B,#0x0056
CMP A,B
RLE
LDA #0x00D2
RTN
HLT 
J514:
LDA #0x0088
LD B,#0x0066
CMP A,B
RLE
LDA #0x0050
RTN
HLT 
J515:
LDA #0x0011
LD B,#0x0035
CMP A,B
RLE
LDA #0x00C7
RTN
HLT 
J516:
LDA #0x008D
LD B,#0x0036
CMP A,B
RLE
LDA #0x0061
RTN
HLT 
J517:
LDA #0x0030
LD B,#0x0000
CMP A,B
RLE
LDA #0x0034
RTN
HLT 