LDA #0x00BB
STA 0xAADD
LDA #0x00BB
STA 0xAADE
LDA #0x0090
LD B,#0x00AF
CMP A,B
JVS J506
LDA #0x007E
J506:
STA 0x01FB
LDA #0x00A0
LD B,#0x0087
CMP A,B
JVS J508
LDA #0x00EF
J508:
STA 0x01FD
LDA #0x0019
LD B,#0x00F1
CMP A,B
JVS J510
LDA #0x0000
J510:
STA 0x01FF
LDA #0x006A
LD B,#0x007E
CMP A,B
JVS J512
LDA #0x0052
J512:
STA 0x0201
LDA #0x00E4
LD B,#0x0079
CMP A,B
JVS J514
LDA #0x00D2
J514:
STA 0x0203
LDA #0x007E
LD B,#0x00A7
CMP A,B
JVS J516
LDA #0x0004
J516:
STA 0x0205
HLT 
data506: dw J506
data508: dw J508
data510: dw J510
data512: dw J512
data514: dw J514
data516: dw J516
