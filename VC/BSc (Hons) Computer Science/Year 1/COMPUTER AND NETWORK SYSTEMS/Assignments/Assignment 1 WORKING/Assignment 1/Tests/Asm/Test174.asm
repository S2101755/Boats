LDA #0x00BB
STA 0xAADD
LDA #0x00BB
STA 0xAADE
LDA #0x0062
LD B,#0x00B3
CMP A,B
LDA #0x0000
JEQ J506
LDA #0x0055
J506:
STA 0x01FB
LDA #0x0007
LD B,#0x00A6
CMP A,B
JEQ J508
LDA #0x004C
J508:
STA 0x01FD
LDA #0x0070
LD B,#0x00BD
CMP A,B
JEQ J510
LDA #0x0083
J510:
STA 0x01FF
LDA #0x0032
LD B,#0x0004
CMP A,B
LDA #0x0000
JEQ J512
LDA #0x00D1
J512:
STA 0x0201
LDA #0x0098
LD B,#0x0033
CMP A,B
LDA #0x0000
JEQ J514
LDA #0x0099
J514:
STA 0x0203
LDA #0x003C
LD B,#0x00F4
CMP A,B
JEQ J516
LDA #0x00AC
J516:
STA 0x0205
HLT 
data506: dw J506
data508: dw J508
data510: dw J510
data512: dw J512
data514: dw J514
data516: dw J516