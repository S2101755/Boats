LDZ #0x342A
LDA #0x00BB
STA 0xAADD
LDA #0x00BB
STA 0xAADE
LD E,#0x00D3
LDA #0x0095
AND A,E
STA 0x01FA
LD E,#0x00E4
LDA #0x00B9
AND A,E
STA 0x01FB
LD E,#0x0080
LDA #0x008D
AND A,E
STA 0x01FC
LD E,#0x00C1
LDA #0x0026
AND A,E
STA 0x01FD
LD E,#0x00D6
LDA #0x0078
AND A,E
STA 0x01FE
LD E,#0x008A
LDA #0x0033
AND A,E
STA 0x01FF
LD E,#0x0046
LDA #0x00E2
AND A,E
CSA
STA 0x0200
LD E,#0x001B
LDA #0x002D
AND A,E
CSA
STA 0x0201
LD E,#0x0044
LDA #0x00AC
AND A,E
CSA
STA 0x0202
LD E,#0x0071
LDA #0x00EB
AND A,E
CSA
STA 0x0203
LD E,#0x0063
LDA #0x00A7
AND A,E
CSA
STA 0x0204
LD E,#0x00F5
LDA #0x0091
AND A,E
CSA
STA 0x0205
HLT 
