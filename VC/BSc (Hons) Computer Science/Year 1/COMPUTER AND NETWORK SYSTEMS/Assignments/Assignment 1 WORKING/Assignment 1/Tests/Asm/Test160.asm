LDA #0x00BB
STA 0xAADD
LDA #0x00BB
STA 0xAADE
LDA #0x002F
LD B,#0x0028
CMP A,B
JP J506
LDA #0x00E3
J506:
STA 0x01FB
LDA #0x003E
LD B,#0x00AE
CMP A,B
JP J508
LDA #0x00D6
J508:
STA 0x01FD
LDA #0x0013
LD B,#0x0058
CMP A,B
JP J510
LDA #0x0075
J510:
STA 0x01FF
LDA #0x0042
LD B,#0x006E
CMP A,B
JP J512
LDA #0x0028
J512:
STA 0x0201
LDA #0x000A
LD B,#0x0051
CMP A,B
JP J514
LDA #0x002B
J514:
STA 0x0203
LDA #0x00C5
LD B,#0x007E
CMP A,B
JP J516
LDA #0x00DC
J516:
STA 0x0205
HLT 
data506: dw J506
data508: dw J508
data510: dw J510
data512: dw J512
data514: dw J514
data516: dw J516
