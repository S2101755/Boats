LDZ #0x342A
LDA #0x00BB
STA 0xAADD
LDA #0x00BB
STA 0xAADE
LD E,#0x0011
LDA #0x00F1
EOR A,E
STA 0x01FA
LD E,#0x0069
LDA #0x0074
EOR A,E
STA 0x01FB
LD E,#0x000C
LDA #0x0016
EOR A,E
STA 0x01FC
LD E,#0x001D
LDA #0x0045
EOR A,E
STA 0x01FD
LD E,#0x00E2
LDA #0x003F
EOR A,E
STA 0x01FE
LD E,#0x00C9
LDA #0x002E
EOR A,E
STA 0x01FF
LD E,#0x001C
LDA #0x00BB
EOR A,E
CSA
STA 0x0200
LD E,#0x00AE
LDA #0x005A
EOR A,E
CSA
STA 0x0201
LD E,#0x00C8
LDA #0x009D
EOR A,E
CSA
STA 0x0202
LD E,#0x005A
LDA #0x0093
EOR A,E
CSA
STA 0x0203
LD E,#0x0099
LDA #0x00E3
EOR A,E
CSA
STA 0x0204
LD E,#0x00E4
LDA #0x00DF
EOR A,E
CSA
STA 0x0205
HLT 