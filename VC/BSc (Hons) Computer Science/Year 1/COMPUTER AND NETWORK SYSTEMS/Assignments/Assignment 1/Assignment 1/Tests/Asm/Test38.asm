LDZ #0x342A
LDA #0x00BB
STA 0xAADD
LDA #0x00BB
STA 0xAADE
LD D,#0x0055
LDA #0x00A3
EOR A,D
STA 0x01FA
LD D,#0x007B
LDA #0x0079
EOR A,D
STA 0x01FB
LD D,#0x00E6
LDA #0x00CB
EOR A,D
STA 0x01FC
LD D,#0x00FB
LDA #0x00A4
EOR A,D
STA 0x01FD
LD D,#0x0024
LDA #0x00AB
EOR A,D
STA 0x01FE
LD D,#0x00E7
LDA #0x00CE
EOR A,D
STA 0x01FF
LD D,#0x0094
LDA #0x007D
EOR A,D
CSA
STA 0x0200
LD D,#0x00CF
LDA #0x0096
EOR A,D
CSA
STA 0x0201
LD D,#0x00DE
LDA #0x0055
EOR A,D
CSA
STA 0x0202
LD D,#0x0004
LDA #0x000B
EOR A,D
CSA
STA 0x0203
LD D,#0x0077
LDA #0x0053
EOR A,D
CSA
STA 0x0204
LD D,#0x007E
LDA #0x0025
EOR A,D
CSA
STA 0x0205
HLT 
