LDZ #0x342A
LDA #0x00BB
STA 0xAADD
LDA #0x00BB
STA 0xAADE
LD B,#0x00CD
LDA #0x00C3
SBB A,B
STA 0x01FA
LD B,#0x001C
LDA #0x00EE
SBB A,B
STA 0x01FB
LD B,#0x0021
LDA #0x00E3
SBB A,B
STA 0x01FC
LD B,#0x00B9
LDA #0x00F7
SBB A,B
STA 0x01FD
LD B,#0x0081
LDA #0x002D
SBB A,B
STA 0x01FE
LD B,#0x0098
LDA #0x0076
SBB A,B
STA 0x01FF
LD B,#0x0043
LDA #0x00CC
SBB A,B
CSA
STA 0x0200
LD B,#0x00FC
LDA #0x0075
SBB A,B
CSA
STA 0x0201
LD B,#0x006F
LDA #0x0004
SBB A,B
CSA
STA 0x0202
LD B,#0x000F
LDA #0x0034
SBB A,B
CSA
STA 0x0203
LD B,#0x00AE
LDA #0x0042
SBB A,B
CSA
STA 0x0204
LD B,#0x0045
LDA #0x00EB
SBB A,B
CSA
STA 0x0205
HLT 