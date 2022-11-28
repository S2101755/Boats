
/*
* ======================================================================================================================================================||
* ||======================================================||		Chimera-2018-A (2022)		||======================================================||
* ||		Author Name				::			SHAUZAB MUFEED																							||
* ||		Creation Date			::			22/MAY/22																								||
* ||		Description				::			Chimera-2018-A Emulator to emulate 4 bit memory computation												||
* ||		VC tudent ID			::			S2101755																								||
* ||		UWE ID					::			21076183																								||
* ||		Revision Date			::			02/JUN/22	03:32																								||
* ======================================================================================================================================================||
*/

#include "stdafx.h"
#include <winsock2.h>

#pragma comment(lib, "wsock32.lib")


#define STUDENT_NUMBER    "21076183"

#define IP_ADDRESS_SERVER "127.0.0.1"

#define PORT_SERVER 0x1984 // We define a port that we are going to use.
#define PORT_CLIENT 0x1985 // We define a port that we are going to use.

#define WORD  unsigned short
#define DWORD unsigned long
#define BYTE  unsigned char

#define MAX_FILENAME_SIZE 500
#define MAX_BUFFER_SIZE   500

SOCKADDR_IN server_addr;
SOCKADDR_IN client_addr;

SOCKET sock;  // This is our socket, it is the handle to the IO address to read/write packets

WSADATA data;

char InputBuffer [MAX_BUFFER_SIZE];

char hex_file [MAX_BUFFER_SIZE];
char trc_file [MAX_BUFFER_SIZE];

//////////////////////////
//   Registers          //
//////////////////////////

#define FLAG_Z  0x80
#define FLAG_V  0x40
#define FLAG_I  0x08
#define FLAG_N  0x02
#define FLAG_C  0x01
#define REGISTER_A	5
#define REGISTER_F	4
#define REGISTER_E	3
#define REGISTER_D	2
#define REGISTER_C	1
#define REGISTER_B	0
WORD BaseRegister;
BYTE IndexRegister;

BYTE Registers[6];
BYTE Flags;
WORD ProgramCounter;
WORD StackPointer;


////////////
// Memory //
////////////

#define MEMORY_SIZE	65536

BYTE Memory[MEMORY_SIZE];

#define TEST_ADDRESS_1  0x01FA
#define TEST_ADDRESS_2  0x01FB
#define TEST_ADDRESS_3  0x01FC
#define TEST_ADDRESS_4  0x01FD
#define TEST_ADDRESS_5  0x01FE
#define TEST_ADDRESS_6  0x01FF
#define TEST_ADDRESS_7  0x0200
#define TEST_ADDRESS_8  0x0201
#define TEST_ADDRESS_9  0x0202
#define TEST_ADDRESS_10  0x0203
#define TEST_ADDRESS_11  0x0204
#define TEST_ADDRESS_12  0x0205


///////////////////////
// Control variables //
///////////////////////

bool memory_in_range = true;
bool halt = false;


///////////////////////
// Disassembly table //
///////////////////////

char opcode_mneumonics[][14] =
{
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"JP abs       ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"LDX  #       ", 
"LDX abs      ", 
"LDX abs,X    ", 
"LDX zpg      ", 
"LDX (ind)    ", 
"LDX bas      ", 
"RTN impl     ", 

"ADD A,B      ", 
"ADD A,C      ", 
"ADD A,D      ", 
"ADD A,E      ", 
"ADD A,F      ", 
"JCC abs      ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"LODS  #      ", 
"LODS abs     ", 
"LODS abs,X   ", 
"LODS zpg     ", 
"LODS (ind)   ", 
"LODS bas     ", 
"RCC impl     ", 

"SBB A,B      ", 
"SBB A,C      ", 
"SBB A,D      ", 
"SBB A,E      ", 
"SBB A,F      ", 
"JCS abs      ", 
"TST abs      ", 
"TST abs,X    ", 
"TSTA A,A     ", 
"LDZ  #       ", 
"LDZ abs      ", 
"LDZ abs,X    ", 
"LDZ zpg      ", 
"LDZ (ind)    ", 
"LDZ bas      ", 
"RCS impl     ", 

"CMP A,B      ", 
"CMP A,C      ", 
"CMP A,D      ", 
"CMP A,E      ", 
"CMP A,F      ", 
"JNE abs      ", 
"INC abs      ", 
"INC abs,X    ", 
"INCA A,A     ", 
"ILLEGAL     ", 
"STA abs      ", 
"STA abs,X    ", 
"STA zpg      ", 
"STA (ind)    ", 
"STA bas      ", 
"RNE impl     ", 

"OR A,B       ", 
"OR A,C       ", 
"OR A,D       ", 
"OR A,E       ", 
"OR A,F       ", 
"JEQ abs      ", 
"DEC abs      ", 
"DEC abs,X    ", 
"DECA A,A     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"REQ impl     ", 

"AND A,B      ", 
"AND A,C      ", 
"AND A,D      ", 
"AND A,E      ", 
"AND A,F      ", 
"JVC abs      ", 
"RR abs       ", 
"RR abs,X     ", 
"RRA A,A      ", 
"MV A,A       ", 
"MV A,B       ", 
"MV A,C       ", 
"MV A,D       ", 
"MV A,E       ", 
"MV A,F       ", 
"RVC impl     ", 

"EOR A,B      ", 
"EOR A,C      ", 
"EOR A,D      ", 
"EOR A,E      ", 
"EOR A,F      ", 
"JVS abs      ", 
"RLC abs      ", 
"RLC abs,X    ", 
"RLCA A,A     ", 
"MV B,A       ", 
"MV B,B       ", 
"MV B,C       ", 
"MV B,D       ", 
"MV B,E       ", 
"MV B,F       ", 
"RVS impl     ", 

"STX abs      ", 
"STX abs,X    ", 
"STX zpg      ", 
"STX (ind)    ", 
"STX bas      ", 
"JMI abs      ", 
"ASL abs      ", 
"ASL abs,X    ", 
"ASLA A,A     ", 
"MV C,A       ", 
"MV C,B       ", 
"MV C,C       ", 
"MV C,D       ", 
"MV C,E       ", 
"MV C,F       ", 
"RMI impl     ", 

"ILLEGAL     ", 
"ADCP A,C     ", 
"SBCP A,C     ", 
"ADI  #       ", 
"ILLEGAL     ", 
"JPL abs      ", 
"ASR abs      ", 
"ASR abs,X    ", 
"ASRA A,A     ", 
"MV D,A       ", 
"MV D,B       ", 
"MV D,C       ", 
"MV D,D       ", 
"MV D,E       ", 
"MV D,F       ", 
"RPL impl     ", 

"DEX impl     ", 
"XCHG A,C     ", 
"ILLEGAL     ", 
"SBI  #       ", 
"LD  #,B      ", 
"JLS abs      ", 
"LSR abs      ", 
"LSR abs,X    ", 
"LSRA A,A     ", 
"MV E,A       ", 
"MV E,B       ", 
"MV E,C       ", 
"MV E,D       ", 
"MV E,E       ", 
"MV E,F       ", 
"RHI impl     ", 

"INX impl     ", 
"CLC impl     ", 
"ILLEGAL     ", 
"CPI  #       ", 
"LD  #,C      ", 
"JLT abs      ", 
"NOT abs      ", 
"NOT abs,X    ", 
"NOTA A,A     ", 
"MV F,A       ", 
"MV F,B       ", 
"MV F,C       ", 
"MV F,D       ", 
"MV F,E       ", 
"MV F,F       ", 
"RLE impl     ", 

"DEZ impl     ", 
"SEC impl     ", 
"ILLEGAL     ", 
"ORI  #       ", 
"LD  #,D      ", 
"MAX impl     ", 
"NEG abs      ", 
"NEG abs,X    ", 
"NEGA A,0     ", 
"STS abs      ", 
"STS abs,X    ", 
"STS zpg      ", 
"STS (ind)    ", 
"STS bas      ", 
"ILLEGAL     ", 
"ILLEGAL     ", 

"INZ impl     ", 
"CLI impl     ", 
"ILLEGAL     ", 
"ANI  #       ", 
"LD  #,E      ", 
"MXA impl     ", 
"ROL abs      ", 
"ROL abs,X    ", 
"ROLA A,A     ", 
"STZ abs      ", 
"STZ abs,X    ", 
"STZ zpg      ", 
"STZ (ind)    ", 
"STZ bas      ", 
"ILLEGAL     ", 
"ILLEGAL     ", 

"ILLEGAL     ", 
"STI impl     ", 
"ILLEGAL     ", 
"XRI  #       ", 
"LD  #,F      ", 
"CSA impl     ", 
"RAR abs      ", 
"RAR abs,X    ", 
"RARA A,A     ", 
"LDA  #       ", 
"LDA abs      ", 
"LDA abs,X    ", 
"LDA zpg      ", 
"LDA (ind)    ", 
"LDA bas      ", 
"ILLEGAL     ", 

"ILLEGAL     ", 
"SEV impl     ", 
"NOP impl     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"PSH  ,A      ", 
"PSH  ,s      ", 
"PSH  ,B      ", 
"PSH  ,C      ", 
"PSH  ,D      ", 
"PSH  ,E      ", 
"PSH  ,F      ", 
"SWI impl     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 

"ILLEGAL     ", 
"CLV impl     ", 
"HLT impl     ", 
"CALL abs     ", 
"ILLEGAL     ", 
"POP A,       ", 
"POP s,       ", 
"POP B,       ", 
"POP C,       ", 
"POP D,       ", 
"POP E,       ", 
"POP F,       ", 
"RTI impl     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 
"ILLEGAL     ", 

}; 

////////////////////////////////////////////////////////////////////////////////
//                           Simulator/Emulator (Start)                       //
////////////////////////////////////////////////////////////////////////////////
BYTE fetch()
{
	BYTE byte = 0;

	if ((ProgramCounter >= 0) && (ProgramCounter <= MEMORY_SIZE))
	{
		memory_in_range = true;
		byte = Memory[ProgramCounter];
		ProgramCounter++;
	}
	else
	{
		memory_in_range = false;
	}
	return byte;
}

void set_flag_z(BYTE inReg) { //Zero Flag
	BYTE reg;
	reg = inReg;

	if (reg == 0) // all the bits are Zero
	{
		// Sets Zero Flag
		Flags = Flags | FLAG_Z;
	}
	else
	{
		// Clear Zero Flag
		Flags = Flags & (0xFF - FLAG_Z);
	}
}

void set_flag_n(BYTE inReg) { // Negative Flag
	BYTE reg;
	reg = inReg;

	if ((reg & 0x80) != 0) // msbit set
	{
		Flags = Flags | FLAG_N;
	}
	else
	{
		Flags = Flags & (0xFF - FLAG_N);
	}
}

void set_flag_c(WORD inReg) { // Carry Flag
	WORD reg;
	reg = inReg;

	if (inReg >= 0x100)
	{
		Flags = Flags | FLAG_C; // Sets the carry Flag
	}
	else
	{
		// Clears the carry Flag
		Flags = Flags & (0xFF - FLAG_C);
	}
}

void set_flag_v(BYTE in1, BYTE in2, BYTE out1) { // Overflow Flag
	BYTE reg1in;
	BYTE reg2in;
	BYTE regOut;
	reg1in = in1;
	reg2in = in2;
	regOut = out1;

	if ((((reg1in & 0x80) == 0x80) && ((reg2in & 0x80) == 0x80) && ((regOut & 0x80) != 0x80)) ||
		(((reg1in & 0x80) != 0x80) && ((reg2in & 0x80) != 0x80) && ((regOut & 0x80) == 0x80)))
	{
		// Set the overflow Flag
		Flags = Flags | FLAG_V;
	}
	else
	{
		// Clear the overflow Flag
		Flags = Flags & (0xFF - FLAG_V);
	}
}

void Group_1(BYTE opcode){
	BYTE LB = 0;
	BYTE HB = 0;
	WORD address = 0;
	WORD data = 0;
	WORD regA = 0;
	BYTE reg1 = 0;
	BYTE reg2 = 0;
	BYTE S_flag = 0;

	switch (opcode) {
		//------============================================||   ||  ||	  OPCODES / start here	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - LD #		 /start	||   ||   ||============================================------//

	case 0x94: // LD Immidiate B (#) // done

		data = fetch();
		Registers[REGISTER_B] = data;

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_B]);
		set_flag_z(Registers[REGISTER_B]);

		break;

	case 0xA4: //LD Immidiate C (#) // done

		data = fetch();
		Registers[REGISTER_C] = data;

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_C]);
		set_flag_z(Registers[REGISTER_C]);

		break;

	case 0xB4: //LD Immidiate D (#) // done

		data = fetch();
		Registers[REGISTER_D] = data;

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_D]);
		set_flag_z(Registers[REGISTER_D]);

		break;

	case 0xC4: //LD Immidiate E (#) // done

		data = fetch();
		Registers[REGISTER_E] = data;

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_E]);
		set_flag_z(Registers[REGISTER_E]);

		break;

	case 0xD4: //LD Immidiate F (#) // done

		data = fetch();
		Registers[REGISTER_F] = data;

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_F]);
		set_flag_z(Registers[REGISTER_F]);

		break;

		//------============================================||   ||  ||	  OP - LD #		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - LDA /start		||   ||   ||============================================------//

	case 0xD9: //LDA Immidiate (#) // done

		data = fetch();
		Registers[REGISTER_A] = data;

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);

		break;

	case 0xDA: //LDA Absolute (abs) // done

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Registers[REGISTER_A] = Memory[address];
		}

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);
		break;

	case 0xDB: //LDA Indexed Absolute Address with X (abs,X) // done

		address += IndexRegister;

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Registers[REGISTER_A] = Memory[address];
		}

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);

		break;

	case 0xDC:	//LDA Zero Page Adrressing (zpg) // done

		LB = fetch();
		HB = 0x00;

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < 256) {
			Registers[REGISTER_A] = Memory[address];
		}

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);

		break;

	case 0xDD: //LDA Indirect Addressing (ind) // done

		LB = fetch();
		HB = fetch();

		address = (WORD)((WORD)HB << 8) + LB;
		LB = Memory[address];
		HB = Memory[address + 1];
		address = (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
			Registers[REGISTER_A] = Memory[address];

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);

		break;

	case 0xDE: //LDA Base Offset (bas) // done

		LB = fetch();

		if (LB >= 0x80) {
			LB = 0x00 - LB;
			address += (BaseRegister - LB);
		}
		else {
			address += (BaseRegister + LB);
		}

		if (address >= 0 && address < MEMORY_SIZE)
			Registers[REGISTER_A] = Memory[address];

		set_flag_c(0);
		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);

		break;

		//------============================================||   ||  ||	  OP - LDA		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - LDX		 /start	||   ||   ||============================================------//

	case 0x09: //LDX Immidiate (#) // done

		data = fetch();
		IndexRegister = data;

		set_flag_c(0);
		set_flag_n(IndexRegister);
		set_flag_z(IndexRegister);

		break;

	case 0x0A: //LDX Absolute (abs) // done

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			IndexRegister = Memory[address];
		}

		set_flag_c(0);
		set_flag_n(IndexRegister);
		set_flag_z(IndexRegister);
		break;

	case 0x0B: //LDX Indexed Absolute Address with X (abs,X) // done

		address += IndexRegister;

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			IndexRegister = Memory[address];
		}

		set_flag_c(0);
		set_flag_n(IndexRegister);
		set_flag_z(IndexRegister);
		break;

	case 0x0C:	//LDX Zero Page Adrressing (zpg) // done

		LB = fetch();
		HB = 0x00;
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < 256) {
			IndexRegister = Memory[address];
		}

		set_flag_c(0);
		set_flag_n(IndexRegister);
		set_flag_z(IndexRegister);
		break;

	case 0x0D: //LDX Indirect Addressing (ind) // done

		LB = fetch();
		HB = fetch();

		address = (WORD)((WORD)HB << 8) + LB;
		LB = Memory[address];
		HB = Memory[address + 1];
		address = (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
			IndexRegister = Memory[address];

		set_flag_c(0);
		set_flag_n(IndexRegister);
		set_flag_z(IndexRegister);

		break;

	case 0x0E: //LDX Base Offset (bas) // done

		LB = fetch();

		if (LB >= 0x80) {
			LB = 0x00 - LB;
			address += (BaseRegister - LB);
		}
		else {
			address += (BaseRegister + LB);
		}

		if (address >= 0 && address < MEMORY_SIZE)
			IndexRegister = Memory[address];

		set_flag_c(0);
		set_flag_n(IndexRegister);
		set_flag_z(IndexRegister);

		break;

		//------============================================||   ||  ||	  OP - LDX		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - LDZ		 /start	||   ||   ||============================================------//

	case 0x29: //LDZ Immidiate (#) // done

		data = fetch();
		BaseRegister = data;

		break;

	case 0x2A: //LDZ Absolute (abs) // done

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			BaseRegister = Memory[address];
		}

		break;

	case 0x2B: //LDZ Indexed Absolute Address with X (abs,X) // done

		address += IndexRegister;

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			BaseRegister = Memory[address];
		}

		break;

	case 0x2C:	//LDZ Zero Page Adrressing (zpg) // done

		LB = fetch();
		HB = 0x00;
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < 256) {
			BaseRegister = Memory[address];
		}

		break;

	case 0x2D: //LDZ Indirect Addressing (ind) // done

		LB = fetch();
		HB = fetch();

		address = (WORD)((WORD)HB << 8) + LB;
		LB = Memory[address];
		HB = Memory[address + 1];
		address = (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE)
			BaseRegister = Memory[address];

		break;

	case 0x2E: //LDZ Base Offset (bas) // done

		LB = fetch();

		if (LB >= 0x80) {
			LB = 0x00 - LB;
			address += (BaseRegister - LB);
		}
		else {
			address += (BaseRegister + LB);
		}

		if (address >= 0 && address < MEMORY_SIZE)
			BaseRegister = Memory[address];

		break;

		//------============================================||   ||  ||	  OP - LDZ		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - STA		 /start	||   ||   ||============================================------//

	case 0x3A: //STA Absolute (abs) // done

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] = Registers[REGISTER_A];

			set_flag_c(0);
			set_flag_n(Memory[address]);
			set_flag_z(Memory[address]);
		}

		break;

	case 0x3B: //STA Indexed Absolute Address with X (abs,X) // done

		address += IndexRegister;

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] = Registers[REGISTER_A];

			set_flag_c(0);
			set_flag_n(Memory[address]);
			set_flag_z(Memory[address]);
		}

		break;

	case 0x3C: //STA Zero Page Adrressing (zpg) // done

		LB = fetch();
		HB = 0x00;
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < 256) {
			Memory[address] = Registers[REGISTER_A];

			set_flag_c(0);
			set_flag_n(Memory[address]);
			set_flag_z(Memory[address]);
		}

		break;

	case 0x3D: //STA Indirect Addressing (ind) // done

		LB = fetch();
		HB = fetch();

		address = (WORD)((WORD)HB << 8) + LB;
		LB = Memory[address];
		HB = Memory[address + 1];
		address = (WORD)((WORD)HB << 8) + LB;

		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] = Registers[REGISTER_A];

			set_flag_c(0);
			set_flag_n(Memory[address]);
			set_flag_z(Memory[address]);
		}

		break;

	case 0x3E: //STA Base Offset (bas) // done

		LB = fetch();

		if (LB >= 0x80) {
			LB = 0x00 - LB;
			address += (BaseRegister - LB);
		}
		else {
			address += (BaseRegister + LB);
		}

		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] = Registers[REGISTER_A];

			set_flag_c(0);
			set_flag_n(Memory[address]);
			set_flag_z(Memory[address]);
		}

		break;

		//------============================================||   ||  ||	  OP - STA		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - STS		 /start	||   ||   ||============================================------//

	case 0xB9: // STS Absolute (abs) // done

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE - 1) {
			Memory[address] = (BYTE)StackPointer;
			Memory[address + 1] = (BYTE)(StackPointer >> 8);
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

	case 0xBA: // STS Indexed Absolute Address with X (abs,X) // done

		address += IndexRegister;
		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;

		if (address >= 0 && address < MEMORY_SIZE - 1) {
			Memory[address] = (BYTE)StackPointer;
			Memory[address + 1] = (BYTE)(StackPointer >> 8);
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

	case 0xBB: // STS Zero Page Adrressing (zpg) // done

		address += (WORD)fetch();

		if (address >= 0 && address < MEMORY_SIZE - 1) {
			Memory[address] = (BYTE)StackPointer;
			Memory[address + 1] = (BYTE)(StackPointer >> 8);
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

	case 0xBC: // STS Indirect Addressing (ind) // done

		LB = fetch();
		HB = fetch();

		address = (WORD)((WORD)HB << 8) + LB;
		LB = Memory[address];
		HB = Memory[address + 1];
		address = (WORD)((WORD)HB << 8) + LB;

		if (address >= 0 && address < MEMORY_SIZE - 1) {
			Memory[address] = (BYTE)StackPointer;
			Memory[address + 1] = (BYTE)(StackPointer >> 8);
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

	case 0xBD: // STS Base Offset (bas) // done

		LB = fetch();

		if (LB >= 0x80) {
			LB = 0x00 - LB;
			address += (BaseRegister - LB);
		}
		else {
			address += (BaseRegister + LB);
		}

		if (address >= 0 && address < MEMORY_SIZE - 1) {
			Memory[address] = (BYTE)StackPointer;
			Memory[address + 1] = (BYTE)(StackPointer >> 8);
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

		//------============================================||   ||  ||	  OP - STS		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - STX		 /start	||   ||   ||============================================------//

	case 0x70: //STX Absolute (abs) // done

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] = IndexRegister;
		}

		set_flag_c(0);
		set_flag_n(Memory[address]);
		set_flag_z(Memory[address]);

		break;

	case 0x71: //STX Indexed Absolute Address with X (abs,X) // done

		address += IndexRegister;

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] = IndexRegister;
		}

		set_flag_c(0);
		set_flag_n(Memory[address]);
		set_flag_z(Memory[address]);

		break;

	case 0x72: //STX Zero Page Adrressing (zpg) // done

		LB = fetch();
		HB = 0x00;
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < 256) {
			Memory[address] = IndexRegister;
		}

		set_flag_c(0);
		set_flag_n(Memory[address]);
		set_flag_z(Memory[address]);

		break;

	case 0x73: // STX Indirect Addressing (ind) // done

		LB = fetch();
		HB = fetch();

		address = (WORD)((WORD)HB << 8) + LB;
		LB = Memory[address];
		HB = Memory[address + 1];
		address = (WORD)((WORD)HB << 8) + LB;

		if (address >= 0 && address < MEMORY_SIZE)
			Memory[address] = IndexRegister;

		set_flag_c(0);
		set_flag_n(Memory[address]);
		set_flag_z(Memory[address]);

		break;

	case 0x74: //STX Base Offset (bas) // done
		LB = fetch();

		if (LB >= 0x80) {
			LB = 0x00 - LB;
			address += (BaseRegister - LB);
		}
		else {
			address += (BaseRegister + LB);
		}

		if (address >= 0 && address < MEMORY_SIZE)
			Memory[address] = IndexRegister;

		set_flag_c(0);
		set_flag_n(Memory[address]);
		set_flag_z(Memory[address]);

		break;

		//------============================================||   ||  ||	  OP - STX		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - STZ		 /start	||   ||   ||============================================------//

	case 0xC9: //STZ Absolute (abs) // done

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] = BaseRegister;
		}

		break;

	case 0xCA: //STZ Indexed Absolute Address with X (abs,X) // done

		address += IndexRegister;

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] = BaseRegister;
		}

		break;

	case 0xCB: //STZ Zero Page Adrressing (zpg) // done

		LB = fetch();
		HB = 0x00;
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < 256) {
			Memory[address] = BaseRegister;
		}

		break;

	case 0xCC: //STZ Indirect Addressing (ind) // done

		LB = fetch();
		HB = fetch();

		address = (WORD)((WORD)HB << 8) + LB;
		LB = Memory[address];
		HB = Memory[address + 1];
		address = (WORD)((WORD)HB << 8) + LB;

		if (address >= 0 && address < MEMORY_SIZE)
			Memory[address] = BaseRegister;

		break;

	case 0xCD: //STZ Base Offset (bas) // done

		LB = fetch();

		if (LB >= 0x80) {
			LB = 0x00 - LB;
			address += (BaseRegister - LB);
		}
		else {
			address += (BaseRegister + LB);
		}

		if (address >= 0 && address < MEMORY_SIZE)
			Memory[address] = BaseRegister;

		break;

		//------============================================||   ||  ||	  OP - STZ		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - LODS		 /start	||   ||   ||============================================------//

	case 0x19: //LODS Immidiate (#) // done

		data = fetch();
		StackPointer = data;
		StackPointer += (WORD)fetch() << 8;

		break;

	case 0x1A: //LODS Absolute (abs) // done

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			StackPointer = Memory[address];
			StackPointer += (WORD)Memory[address + 1] << 8;
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

	case 0x1B: //LODS Indexed Absolute Address with X (abs,X) // done

		address += IndexRegister;

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			StackPointer = Memory[address];
			StackPointer += (WORD)Memory[address + 1] << 8;
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

	case 0x1C:	//LODS Zero Page Adrressing (zpg) // done

		LB = fetch();
		HB = 0x00;
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			StackPointer = Memory[address];
			StackPointer += (WORD)Memory[address + 1] << 8;
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

	case 0x1D: //LODS Indirect Addressing (ind) // done

		LB = fetch();
		HB = fetch();

		address = (WORD)((WORD)HB << 8) + LB;
		LB = Memory[address];
		HB = Memory[address + 1];
		address = (WORD)((WORD)HB << 8) + LB;

		if (address >= 0 && address < MEMORY_SIZE - 1) {
			StackPointer = Memory[address];
			StackPointer += (WORD)Memory[address + 1] << 8;
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

	case 0x1E: //LODS Base Offset (bas) // done

		LB = fetch();

		if (LB >= 0x80) {
			LB = 0x00 - LB;
			address += (BaseRegister - LB);
		}
		else {
			address += (BaseRegister + LB);
		}

		if (address >= 0 && address < MEMORY_SIZE - 1) {
			StackPointer = Memory[address];
			StackPointer += (WORD)Memory[address + 1] << 8;
		}

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		break;

		//------============================================||   ||  ||	  OP - LODS		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - MAX/MXA /start	||   ||   ||============================================------//

	case 0xB5: //MAX Implied Addressing (impl X,A) // done

		IndexRegister = Registers[REGISTER_A];

		set_flag_n(IndexRegister);

		break;

	case 0xC5: //MXA Implied Addressing (impl A,X) // done

		Registers[REGISTER_A] = IndexRegister;

		break;

		//------============================================||   ||  ||	  OP - MAX/MXA	/end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - ADD_A	 /start	||   ||   ||============================================------//

	case 0x10: //ADD (A,B) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_B];
		regA = (WORD)reg1 + (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x11: //ADD (A,C) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_C];
		regA = (WORD)reg1 + (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x12: //ADD (A,D) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_D];
		regA = (WORD)reg1 + (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x13: //ADD (A,E) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_E];
		regA = (WORD)reg1 + (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x14: //ADD (A,F) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_F];
		regA = (WORD)reg1 + (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

		//------============================================||   ||  ||	  OP - ADD_A	 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  // 
		//																																					  //
		//------============================================||   ||  ||	  OP - SBB_A	 /start	||   ||   ||============================================------//

	case 0x20: //SBB (A,B) // done

		reg1 = Registers[REGISTER_B];
		reg2 = Registers[REGISTER_A];
		regA = (WORD)reg1 - (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x21: //SBB (A,C) // done

		reg1 = Registers[REGISTER_C];
		reg2 = Registers[REGISTER_A];
		regA = (WORD)reg1 - (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x22: //SBB (A,D) // done

		reg1 = Registers[REGISTER_D];
		reg2 = Registers[REGISTER_A];
		regA = (WORD)reg1 - (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x23: //SBB (A,E) // done

		reg1 = Registers[REGISTER_E];
		reg2 = Registers[REGISTER_A];
		regA = (WORD)reg1 - (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x24: //SBB (A,F) // done

		reg1 = Registers[REGISTER_F];
		reg2 = Registers[REGISTER_A];
		regA = (WORD)reg1 - (WORD)reg2;

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		Registers[REGISTER_A] = (BYTE)regA;

		break;

		//------============================================||   ||  ||	  OP - SBB_A	 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - NOTA /start		||   ||   ||============================================------//
	
	case 0xA8: //NOTA Negate A // done

		Registers[REGISTER_A] = ~Registers[REGISTER_A];

		break;

		//------============================================||   ||  ||	  OP - NOTA		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //																																			  //
		//------============================================||   ||  ||	  OP - CMP		 /start	||   ||   ||============================================------//

	case 0x30: // CMP (A,B) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_B];
		regA = (WORD)reg1 - (WORD)reg2;

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		break;

	case 0x31: // CMP (A,C) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_C];
		regA = (WORD)reg1 - (WORD)reg2;

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		break;

	case 0x32: // CMP (A,D) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_D];
		regA = (WORD)reg1 - (WORD)reg2;

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		break;

	case 0x33: // CMP (A,E) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_E];
		regA = (WORD)reg1 - (WORD)reg2;

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		break;

	case 0x34: // CMP (A,F) // done

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_F];
		regA = (WORD)reg1 - (WORD)reg2;

		set_flag_c(regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		set_flag_v(reg1, reg2, (BYTE)regA);

		break;

		//------============================================||   ||  ||	  OP - CMP		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - CSA		/start	||   ||   ||============================================------//

	case 0xD5: // CSA Status register to Accumulator Implied (impl)

		Registers[REGISTER_A] = Flags;

		break;

		//------============================================||   ||  ||	  OP - CSA		 /end	||   ||   ||============================================------//
		//																																					  //
		//													||||||||||||||||||||||||||||||||||||||||||||||||												  //
		//																																					  //
		//------============================================||   ||  ||	  OP - PSH		 /start	||   ||   ||============================================------//

	case 0xE5: // PSH A

		if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE)) {
			StackPointer--;
			Memory[StackPointer] = Registers[REGISTER_A];
		}
		
		break;

	case 0xE6: // PSH FL

		if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE)) {
			StackPointer--;
			Memory[StackPointer] = Flags;
		}

		break;

	case 0xE7: // PSH B

		if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE)) {
			StackPointer--;
			Memory[StackPointer] = Registers[REGISTER_B];
		}

		break;

	case 0xE8: // PSH C

		if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE)) {
			StackPointer--;
			Memory[StackPointer] = Registers[REGISTER_C];
		}

		break;

	case 0xE9: // PSH D

		if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE)) {
			StackPointer--;
			Memory[StackPointer] = Registers[REGISTER_D];
		}

	case 0xEA: // PSH E

		if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE)) {
			StackPointer--;
			Memory[StackPointer] = Registers[REGISTER_E];
		}

		break;

	case 0xEB: // PSH F

		if ((StackPointer >= 1) && (StackPointer < MEMORY_SIZE)) {
			StackPointer--;
			Memory[StackPointer] = Registers[REGISTER_F];
		}

		break;

		//------============================================||   ||  ||	  OP - PSH		 /end	||   ||   ||============================================------//
		//																																					  //
		//																																					  //
		//------============================================||   ||  ||	  OP - POP		 /start	||   ||   ||============================================------//

	case 0xF5: // POP A

		if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1)) {
			Registers[REGISTER_A] = Memory[StackPointer];
			StackPointer ++;
		}

		break;

	case 0xF6: // POP FL

		if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1)) {
			Flags = Memory[StackPointer];
			StackPointer ++;
		}

		break;

	case 0xF7: // POP B

		if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1)) {
			Registers[REGISTER_B] = Memory[StackPointer];
			StackPointer ++;
		}

		break;

	case 0xF8: // POP C

		if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1)) {
			Registers[REGISTER_C] = Memory[StackPointer];
			StackPointer ++;
		}

		break;

	case 0xF9: // POP D

		if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1)) {
			Registers[REGISTER_D] = Memory[StackPointer];
			StackPointer ++;
		}

		break;

	case 0xFA: // POP E

		if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1)) {
			Registers[REGISTER_E] = Memory[StackPointer];
			StackPointer ++;
		}

		break;

	case 0xFB: // POP F

		if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 1)) {
			Registers[REGISTER_F] = Memory[StackPointer];
			StackPointer ++;
		}

		break;

		//------============================================||   ||  ||	  OP - POP		 /end	||   ||   ||============================================------//
		//																																					  //
		//																																					  //
		//------============================================||   ||  ||	  OP - JP		 /start	||   ||   ||============================================------//

	case 0x05: // JP Absolute (abs) // done

		LB = fetch();
		HB = fetch();

		address = ((WORD)HB << 8) + (WORD)LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			ProgramCounter = address;
		}
		break;

		set_flag_c(0);
		set_flag_n(Memory[StackPointer]);
		set_flag_z(Memory[StackPointer]);

		//------============================================||   ||  ||	  OP - JP		 /end	||   ||   ||============================================------//
		//																																					  //
		//																																					  //
		//------============================================||   ||  ||	  OP - CALL		 /start	||   ||   ||============================================------//

	case 0xF3: // CALL Absolute (abs) // done

		LB = fetch();
		HB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;

		if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE)) {
			StackPointer--;
			Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
			StackPointer--;
			Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
		}
		
		if (address >= 0 && address < MEMORY_SIZE) {
			ProgramCounter = address;
		}
		break;
	
		//------============================================||   ||  ||	  OP - CALL		 /end	||   ||   ||============================================------//
		//																																					  //
		//																																					  //
		//------============================================||   ||  ||	  OP - RTN		 /start	||   ||   ||============================================------//

	case 0x0F: // CALL Absolute (abs) // done

		address = ((WORD)HB << 8) + (WORD)LB;

		if ((StackPointer >= 0) && (StackPointer < MEMORY_SIZE - 2)) {
			LB = Memory[StackPointer];
			StackPointer++;
			HB = Memory[StackPointer];
			StackPointer++;
		}
		ProgramCounter = ((WORD)HB << 8) + (WORD)LB;
		
		break;

		//------============================================||   ||  ||	  OP - RTN		 /end	||   ||   ||============================================------//
		//																																					  //
		//																																					  //
		//------============================================||   ||  ||	  OP - JC* /start	||   ||   ||============================================------//

	case 0x15: // JCC CALL if carry is 0 Absolute (abs) // done

		if ((Flags & FLAG_C) == 0x00) {

			LB = fetch();
			HB = fetch();
			address = ((WORD)HB << 8) + (WORD)LB;

			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE)) {
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
			}

			if (address >= 0 && address < MEMORY_SIZE) {
				ProgramCounter = address;
			}
		}

		break;

	case 0x25: // JCS CALL if carry is set Absolute (abs) // done

		if ((Flags & FLAG_C) == 0x01) {

			LB = fetch();
			HB = fetch();
			address = ((WORD)HB << 8) + (WORD)LB;

			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE)) {
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
			}

			if (address >= 0 && address < MEMORY_SIZE) {
				ProgramCounter = address;
			}
		}

		break;

	case 0x35: // JNE CALL if result is not 0 Absolute (abs) // done

		if ((Flags & FLAG_Z) == 0x01) {

			LB = fetch();
			HB = fetch();
			address = ((WORD)HB << 8) + (WORD)LB;

			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE)) {
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
			}

			if (address >= 0 && address < MEMORY_SIZE) {
				ProgramCounter = address;
			}
		}

		break;

	case 0x45: // JEQ CALL if result equal to 0 Absolute (abs) // done

		if ((Flags & FLAG_Z) == 0) {

			LB = fetch();
			HB = fetch();
			address = ((WORD)HB << 8) + (WORD)LB;

			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE)) {
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
			}

			if (address >= 0 && address < MEMORY_SIZE) {
				ProgramCounter = address;
			}
		}

		break;

	case 0x55: // JVC CALL if carry is 0 Absolute (abs) // done

		if ((Flags & FLAG_V) == 0x00) {

			LB = fetch();
			HB = fetch();
			address = ((WORD)HB << 8) + (WORD)LB;

			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE)) {
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
			}

			if (address >= 0 && address < MEMORY_SIZE) {
				ProgramCounter = address;
			}
		}

		break;

	case 0x65: // JVS CALL if carry is set Absolute (abs) // done

		if ((Flags & FLAG_V) == 0x01) {

			LB = fetch();
			HB = fetch();
			address = ((WORD)HB << 8) + (WORD)LB;

			if ((StackPointer >= 2) && (StackPointer < MEMORY_SIZE)) {
				StackPointer--;
				Memory[StackPointer] = (BYTE)((ProgramCounter >> 8) & 0xFF);
				StackPointer--;
				Memory[StackPointer] = (BYTE)(ProgramCounter & 0xFF);
			}

			if (address >= 0 && address < MEMORY_SIZE) {
				ProgramCounter = address;
			}
		}

		break;

		//------============================================||   ||  ||	  OP - JCC /end	||   ||   ||============================================------//
		//																																					  //
		//																																					  //
		//------============================================||   ||  ||	  OP - placehold /start	||   ||   ||============================================------//

		//code

		//------============================================||   ||  ||	  OP - placehold /end	||   ||   ||============================================------//
		//																																					  //
		//																																					  //
		//------============================================||   ||  ||	  OP - temp		 /start	||   ||   ||============================================------//

	case 0x38: // INCA increment A // done

		Registers[REGISTER_A]++;

		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);

		break;

	case 0xA0: // INX increment IndexRegister // done

		IndexRegister++;

		set_flag_z(Registers[REGISTER_A]);

		break;

	case 0x36: // INC increment Memory address // done

		LB = fetch();
		HB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;

		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] ++;
		}

		set_flag_z(Memory[address]);
		set_flag_n(Memory[address]);

		break;

	case 0x37: // INC increment Memory address with X // done//

		address += IndexRegister;
		LB = fetch();
		HB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;

		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] ++;
		}
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Registers[REGISTER_A] = Memory[address];
		}

		set_flag_z(Registers[REGISTER_A]);

		break;

	case 0x46: // DEC Decrement Memory address // done

		LB = fetch();
		HB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;

		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] --;
		}

		set_flag_z(Memory[address]);
		set_flag_n(Memory[address]);

		break;

	case 0x47: // DEC Decrement Memory address with X // done//

		address += IndexRegister;
		LB = fetch();
		HB = fetch();
		address = ((WORD)HB << 8) + (WORD)LB;

		if (address >= 0 && address < MEMORY_SIZE) {
			Memory[address] --;
		}
		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Registers[REGISTER_A] = Memory[address];
		}

		set_flag_z(Registers[REGISTER_A]);

		break;

	case 0x48: // DECA Decrement A // done

		Registers[REGISTER_A]++;

		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);

		break;

	case 0x50: // AND bithwise & A,B

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_B];
		regA = (WORD)reg1 & (WORD)reg2;

		set_flag_n((BYTE) regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x51: // AND bithwise & A,C

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_C];
		regA = (WORD)reg1 & (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x52: // AND bithwise & A,D

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_D];
		regA = (WORD)reg1 & (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x53: // AND bithwise & A,E

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_E];
		regA = (WORD)reg1 & (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x54: // AND bithwise & A,F

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_F];
		regA = (WORD)reg1 & (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x40: // OR bithwise OR A,B

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_B];
		regA = (WORD)reg1 | (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x41: // OR bithwise OR A,C

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_C];
		regA = (WORD)reg1 | (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x42: // OR bithwise OR A,D

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_D];
		regA = (WORD)reg1 | (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x43: // OR bithwise OR A,E

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_E];
		regA = (WORD)reg1 | (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x44: // OR bithwise OR A,F

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_F];
		regA = (WORD)reg1 | (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;
		
	case 0x60: // EOR bithwise XOR A,B

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_B];
		regA = (WORD)reg1 ^ (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x61: // EOR bithwise XOR A,C

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_C];
		regA = (WORD)reg1 ^ (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x62: // EOR bithwise XOR A,D

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_D];
		regA = (WORD)reg1 ^ (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x63: // EOR bithwise XOR A,E

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_E];
		regA = (WORD)reg1 ^ (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;

	case 0x64: // EOR bithwise XOR A,F

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_F];
		regA = (WORD)reg1 ^ (WORD)reg2;

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;

		break;


	case 0xB3: // ORI data bitwise OR with A

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_B];
		regA = (WORD)reg1 | (WORD)reg2;
		
		if (regA >= 0x100) {
			Flags = Flags | FLAG_C;
		}
		else {
			Flags = Flags & (0xFF - FLAG_C);
		}

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;
		reg1 = (BYTE)regA;

		break;

	case 0xC3: // ANI data bitwise & with A

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_B];
		regA = (WORD)reg1 & (WORD)reg2;

		if (regA >= 0x100) {
			Flags = Flags | FLAG_C;
		}
		else {
			Flags = Flags & (0xFF - FLAG_C);
		}

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;
		reg1 = (BYTE)regA;

		break;

	case 0xD3: // XRI data bitwise XOR with A

		reg1 = Registers[REGISTER_A];
		reg2 = Registers[REGISTER_B];
		regA = (WORD)reg1 ^ (WORD)reg2;

		if (regA >= 0x100) {
			Flags = Flags | FLAG_C;
		}
		else {
			Flags = Flags & (0xFF - FLAG_C);
		}

		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		Flags = Flags & (0xFF - FLAG_V);
		Registers[REGISTER_A] = (BYTE)regA;
		reg1 = (BYTE)regA;

		break;

	case 0x83: // ADI data added to A with Carry

		reg1 = Registers[REGISTER_A];
		regA = (WORD)reg1 + (WORD)fetch();

		if ((Flags & FLAG_C) != 0) {
			regA++;
		}
		if (Flags & FLAG_C >= 0x100)
		{
			Flags = Flags | FLAG_C; 
		}
		else
		{
			Flags = Flags & (0xFF - FLAG_C);
		}

		set_flag_v(reg1, (BYTE)fetch(), (BYTE)regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		reg1 = (BYTE)regA;

		break;

	case 0xA3: // CPI data compared to A

		reg1 = Registers[REGISTER_A];
		regA = (WORD)reg1 - fetch();

		if (Flags & FLAG_C >= 0x100)
		{
			Flags = Flags | FLAG_C;
		}
		else
		{
			Flags = Flags & (0xFF - FLAG_C);
		}

		set_flag_v(reg1, - fetch(), (BYTE)regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		reg1 = (BYTE)regA;

		break;

	case 0x93: // SBI data subtracted to A with Carry

		reg1 = Registers[REGISTER_A];
		regA = (WORD)reg1 - (WORD)fetch();

		if ((Flags & FLAG_C) != 0) {
			regA--;
		}
		if (Flags & FLAG_C >= 0x100)
		{
			Flags = Flags | FLAG_C;
		}
		else
		{
			Flags = Flags & (0xFF - FLAG_C);
		}

		set_flag_v(reg1, (BYTE)fetch(), (BYTE)regA);
		set_flag_n((BYTE)regA);
		set_flag_z((BYTE)regA);
		reg1 = (BYTE)regA;

		break;

	case 0xA6: //NOT Negate A abs // done

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Registers[REGISTER_A] = Memory[address];
		}

		Registers[REGISTER_A] = ~Registers[REGISTER_A];

		break;

	case 0xA7: //NOT Negate A abs X // done

		address += IndexRegister;

		LB = fetch();
		HB = fetch();

		address += (WORD)((WORD)HB << 8) + LB;
		if (address >= 0 && address < MEMORY_SIZE) {
			Registers[REGISTER_A] = Memory[address];
		}

		Registers[REGISTER_A] = ~Registers[REGISTER_A];

		break;

	case 0x68: // RLCA
		S_flag = Flags;

		if ((Registers[REGISTER_A] & 0x80) == 0x80) {
			Flags = Flags | FLAG_C;
		}
		else {
			Flags = Flags & (0xFF - FLAG_C);
		}
		Registers[REGISTER_A] = (Registers[REGISTER_A] << 1) & 0xFE;

		if ((S_flag & FLAG_C) == 0x01) {
			Registers[REGISTER_A] = Registers[REGISTER_A] | 0x01;
		}

		set_flag_n(Registers[REGISTER_A]);
		set_flag_z(Registers[REGISTER_A]);

		break;
		


		//------============================================||   ||  ||	  OP - temp		 /end	||   ||   ||============================================------//
		//																																					  //
		//																																					  //
		//------============================================||   ||  ||	  OP - placehold /start	||   ||   ||============================================------//

		//code

		//------============================================||   ||  ||	  OP - placehold /end	||   ||   ||============================================------//
		//																																					  //
		//																																					  //
				



	}
}
void Group_2_Move(BYTE opcode) {
	//switch (opcode) {
	BYTE destination = opcode & 0x0F;
	BYTE source = opcode >> 4;
	int destReg, sourceReg;

	switch (destination) {
	case 0x09:
		destReg = REGISTER_A;
		break;
	case 0x0A:
		destReg = REGISTER_B;
		break;
	case 0x0B:
		destReg = REGISTER_C;
		break;
	case 0x0C:
		destReg = REGISTER_D;
		break;
	case 0x0D:
		destReg = REGISTER_E;
		break;
	case 0x0E:
		destReg = REGISTER_F;
		break;
	}

	switch (source) {
	case 0x05:
		sourceReg = REGISTER_A;
		break;
	case 0x06:
		sourceReg = REGISTER_B;
		break;
	case 0x07:
		sourceReg = REGISTER_C;
		break;
	case 0x08:
		sourceReg = REGISTER_D;
		break;
	case 0x09:
		sourceReg = REGISTER_E;
		break;
	case 0x0A:
		sourceReg = REGISTER_F;
		break;
	}

	Registers[destReg] = Registers[sourceReg];
	//}
}

void execute(BYTE opcode)
{

	if (((opcode >= 0x59) && (opcode <= 0x5E)) || ((opcode >= 0x69) && (opcode <= 0x6E)) ||
		((opcode >= 0x79) && (opcode <= 0x7E)) || ((opcode >= 0x89) && (opcode <= 0x8E)) ||
		((opcode >= 0x99) && (opcode <= 0x9E)) || ((opcode >= 0xA9) && (opcode <= 0xAE)))
		Group_2_Move(opcode);
	else Group_1(opcode);
}

void emulate()
{
	BYTE opcode;
	int count = 0;
	ProgramCounter = 0;
	halt = false;
	memory_in_range = true;

	printf("                    A  B  C  D  E  F  X  Z    SP\n");

	while ((!halt) && (memory_in_range) && (count < 256)) {
		printf("%04X ", ProgramCounter);           // Print current address
		opcode = fetch();
		execute(opcode);

		printf("%s  ", opcode_mneumonics[opcode]);  // Print current opcode

		printf("%02X ", Registers[REGISTER_A]);
		printf("%02X ", Registers[REGISTER_B]);
		printf("%02X ", Registers[REGISTER_C]);
		printf("%02X ", Registers[REGISTER_D]);
		printf("%02X ", Registers[REGISTER_E]);
		printf("%02X ", Registers[REGISTER_F]);
		printf("%02X ", IndexRegister);
		printf("%04X ", StackPointer);              // Print Stack Pointer

		if ((Flags & FLAG_Z) == FLAG_Z)
		{
			printf("Z=1 ");
		}
		else
		{
			printf("Z=0 ");
		}
		if ((Flags & FLAG_V) == FLAG_V)
		{
			printf("V=1 ");
		}
		else
		{
			printf("V=0 ");
		}
		if ((Flags & FLAG_I) == FLAG_I)
		{
			printf("I=1 ");
		}
		else
		{
			printf("I=0 ");
		}
		if ((Flags & FLAG_N) == FLAG_N)
		{
			printf("N=1 ");
		}
		else
		{
			printf("N=0 ");
		}
		if ((Flags & FLAG_C) == FLAG_C)
		{
			printf("C=1 ");
		}
		else
		{
			printf("C=0 ");
		}

		printf("\n");  // New line
		count++;
	}

	printf("\n");  // New line
}


////////////////////////////////////////////////////////////////////////////////
//                            Simulator/Emulator (End)                        //
////////////////////////////////////////////////////////////////////////////////


void initialise_filenames() {
	int i;

	for (i = 0; i < MAX_FILENAME_SIZE; i++) {
		hex_file[i] = '\0';
		trc_file[i] = '\0';
	}
}




int find_dot_position(char* filename) {
	int  dot_position;
	int  i;
	char chr;

	dot_position = 0;
	i = 0;
	chr = filename[i];

	while (chr != '\0') {
		if (chr == '.') {
			dot_position = i;
		}
		i++;
		chr = filename[i];
	}

	return (dot_position);
}


int find_end_position(char* filename) {
	int  end_position;
	int  i;
	char chr;

	end_position = 0;
	i = 0;
	chr = filename[i];

	while (chr != '\0') {
		end_position = i;
		i++;
		chr = filename[i];
	}

	return (end_position);
}


bool file_exists(char* filename) {
	bool exists;
	FILE* ifp;

	exists = false;

	if ((ifp = fopen(filename, "r")) != NULL) {
		exists = true;

		fclose(ifp);
	}

	return (exists);
}



void create_file(char* filename) {
	FILE* ofp;

	if ((ofp = fopen(filename, "w")) != NULL) {
		fclose(ofp);
	}
}



bool getline(FILE* fp, char* buffer) {
	bool rc;
	bool collect;
	char c;
	int  i;

	rc = false;
	collect = true;

	i = 0;
	while (collect) {
		c = getc(fp);

		switch (c) {
		case EOF:
			if (i > 0) {
				rc = true;
			}
			collect = false;
			break;

		case '\n':
			if (i > 0) {
				rc = true;
				collect = false;
				buffer[i] = '\0';
			}
			break;

		default:
			buffer[i] = c;
			i++;
			break;
		}
	}

	return (rc);
}






void load_and_run(int args, _TCHAR** argv) {
	char chr;
	int  ln;
	int  dot_position;
	int  end_position;
	long i;
	FILE* ifp;
	long address;
	long load_at;
	int  code;

	// Prompt for the .hex file

	printf("\n");
	printf("Enter the hex filename (.hex): ");

	if (args == 2) {
		ln = 0;
		chr = argv[1][ln];
		while (chr != '\0')
		{
			if (ln < MAX_FILENAME_SIZE)
			{
				hex_file[ln] = chr;
				trc_file[ln] = chr;
				ln++;
			}
			chr = argv[1][ln];
		}
	}
	else {
		ln = 0;
		chr = '\0';
		while (chr != '\n') {
			chr = getchar();

			switch (chr) {
			case '\n':
				break;
			default:
				if (ln < MAX_FILENAME_SIZE) {
					hex_file[ln] = chr;
					trc_file[ln] = chr;
					ln++;
				}
				break;
			}
		}

	}
	// Tidy up the file names

	dot_position = find_dot_position(hex_file);
	if (dot_position == 0) {
		end_position = find_end_position(hex_file);

		hex_file[end_position + 1] = '.';
		hex_file[end_position + 2] = 'h';
		hex_file[end_position + 3] = 'e';
		hex_file[end_position + 4] = 'x';
		hex_file[end_position + 5] = '\0';
	}
	else {
		hex_file[dot_position + 0] = '.';
		hex_file[dot_position + 1] = 'h';
		hex_file[dot_position + 2] = 'e';
		hex_file[dot_position + 3] = 'x';
		hex_file[dot_position + 4] = '\0';
	}

	dot_position = find_dot_position(trc_file);
	if (dot_position == 0) {
		end_position = find_end_position(trc_file);

		trc_file[end_position + 1] = '.';
		trc_file[end_position + 2] = 't';
		trc_file[end_position + 3] = 'r';
		trc_file[end_position + 4] = 'c';
		trc_file[end_position + 5] = '\0';
	}
	else {
		trc_file[dot_position + 0] = '.';
		trc_file[dot_position + 1] = 't';
		trc_file[dot_position + 2] = 'r';
		trc_file[dot_position + 3] = 'c';
		trc_file[dot_position + 4] = '\0';
	}

	if (file_exists(hex_file)) {
		// Clear Registers and Memory

		Registers[REGISTER_A] = 0;
		Registers[REGISTER_B] = 0;
		Registers[REGISTER_C] = 0;
		Registers[REGISTER_D] = 0;
		Registers[REGISTER_E] = 0;
		Registers[REGISTER_F] = 0;
		IndexRegister = 0;
		Flags = 0;
		ProgramCounter = 0;
		StackPointer = 0;

		for (i = 0; i < MEMORY_SIZE; i++) {
			Memory[i] = 0x00;
		}

		// Load hex file

		if ((ifp = fopen(hex_file, "r")) != NULL) {
			printf("Loading file...\n\n");

			load_at = 0;

			while (getline(ifp, InputBuffer)) {
				if (sscanf(InputBuffer, "L=%x", &address) == 1) {
					load_at = address;
				}
				else if (sscanf(InputBuffer, "%x", &code) == 1) {
					if ((load_at >= 0) && (load_at <= MEMORY_SIZE)) {
						Memory[load_at] = (BYTE)code;
					}
					load_at++;
				}
				else {
					printf("ERROR> Failed to load instruction: %s \n", InputBuffer);
				}
			}

			fclose(ifp);
		}

		// Emulate

		emulate();
	}
	else {
		printf("\n");
		printf("ERROR> Input file %s does not exist!\n", hex_file);
		printf("\n");
	}
}

void building(int args, _TCHAR** argv) {
	char buffer[1024];
	load_and_run(args, argv);
	sprintf(buffer, "0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X,0x%02X",
		Memory[TEST_ADDRESS_1],
		Memory[TEST_ADDRESS_2],
		Memory[TEST_ADDRESS_3],
		Memory[TEST_ADDRESS_4],
		Memory[TEST_ADDRESS_5],
		Memory[TEST_ADDRESS_6],
		Memory[TEST_ADDRESS_7],
		Memory[TEST_ADDRESS_8],
		Memory[TEST_ADDRESS_9],
		Memory[TEST_ADDRESS_10],
		Memory[TEST_ADDRESS_11],
		Memory[TEST_ADDRESS_12]
	);
	sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR*)&server_addr, sizeof(SOCKADDR));
}



void test_and_mark() {
	char buffer[1024];
	bool testing_complete;
	int  len = sizeof(SOCKADDR);
	char chr;
	int  i;
	int  j;
	bool end_of_program;
	long address;
	long load_at;
	int  code;
	int  mark;
	int  passed;

	printf("\n");
	printf("Automatic Testing and Marking\n");
	printf("\n");

	testing_complete = false;

	sprintf(buffer, "Test Student %s", STUDENT_NUMBER);
	sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR*)&server_addr, sizeof(SOCKADDR));

	while (!testing_complete) {
		memset(buffer, '\0', sizeof(buffer));

		if (recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (SOCKADDR*)&client_addr, &len) != SOCKET_ERROR) {
			printf("Incoming Data: %s \n", buffer);

			//if (strcmp(buffer, "Testing complete") == 1)
			if (sscanf(buffer, "Testing complete %d", &mark) == 1) {
				testing_complete = true;
				printf("Current mark = %d\n", mark);

			}
			else if (sscanf(buffer, "Tests passed %d", &passed) == 1) {
				//testing_complete = true;
				printf("Passed = %d\n", passed);

			}
			else if (strcmp(buffer, "Error") == 0) {
				printf("ERROR> Testing abnormally terminated\n");
				testing_complete = true;
			}
			else {
				// Clear Registers and Memory

				Registers[REGISTER_A] = 0;
				Registers[REGISTER_B] = 0;
				Registers[REGISTER_C] = 0;
				Registers[REGISTER_D] = 0;
				Registers[REGISTER_E] = 0;
				Registers[REGISTER_F] = 0;
				IndexRegister = 0;
				Flags = 0;
				ProgramCounter = 0;
				StackPointer = 0;
				for (i = 0; i < MEMORY_SIZE; i++) {
					Memory[i] = 0;
				}

				// Load hex file

				i = 0;
				j = 0;
				load_at = 0;
				end_of_program = false;
				FILE* ofp;
				fopen_s(&ofp, "branch.txt", "a");

				while (!end_of_program) {
					chr = buffer[i];
					switch (chr) {
					case '\0':
						end_of_program = true;

					case ',':
						if (sscanf(InputBuffer, "L=%x", &address) == 1) {
							load_at = address;
						}
						else if (sscanf(InputBuffer, "%x", &code) == 1) {
							if ((load_at >= 0) && (load_at <= MEMORY_SIZE)) {
								Memory[load_at] = (BYTE)code;
								fprintf(ofp, "%02X\n", (BYTE)code);
							}
							load_at++;
						}
						else {
							printf("ERROR> Failed to load instruction: %s \n", InputBuffer);
						}
						j = 0;
						break;

					default:
						InputBuffer[j] = chr;
						j++;
						break;
					}
					i++;
				}
				fclose(ofp);
				// Emulate

				if (load_at > 1) {
					emulate();
					// Send and store results
					sprintf(buffer, "%02X%02X %02X%02X %02X%02X %02X%02X %02X%02X %02X%02X",
						Memory[TEST_ADDRESS_1],
						Memory[TEST_ADDRESS_2],
						Memory[TEST_ADDRESS_3],
						Memory[TEST_ADDRESS_4],
						Memory[TEST_ADDRESS_5],
						Memory[TEST_ADDRESS_6],
						Memory[TEST_ADDRESS_7],
						Memory[TEST_ADDRESS_8],
						Memory[TEST_ADDRESS_9],
						Memory[TEST_ADDRESS_10],
						Memory[TEST_ADDRESS_11],
						Memory[TEST_ADDRESS_12]
					);
					sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR*)&server_addr, sizeof(SOCKADDR));
				}
			}
		}
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	char chr;
	char dummy;

	printf("\n");
	printf("Microprocessor Emulator\n");
	printf("UWE Computer and Network Systems Assignment 1\n");
	printf("\n");

	initialise_filenames();

	if (WSAStartup(MAKEWORD(2, 2), &data) != 0) return(0);

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  // Here we create our socket, which will be a UDP socket (SOCK_DGRAM).
	if (!sock) {
		// Creation failed! 
	}

	memset(&server_addr, 0, sizeof(SOCKADDR_IN));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS_SERVER);
	server_addr.sin_port = htons(PORT_SERVER);

	memset(&client_addr, 0, sizeof(SOCKADDR_IN));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_addr.sin_port = htons(PORT_CLIENT);

	chr = '\0';
	while ((chr != 'e') && (chr != 'E'))
	{
		printf("\n");
		printf("Please select option\n");
		printf("L - Load and run a hex file\n");
		printf("T - Have the server test and mark your emulator\n");
		printf("E - Exit\n");
		if (argc == 2) { building(argc, argv); exit(0); }
		printf("Enter option: ");
		chr = getchar();
		if (chr != 0x0A)
		{
			dummy = getchar();  // read in the <CR>
		}
		printf("\n");

		switch (chr)
		{
		case 'L':
		case 'l':
			load_and_run(argc, argv);
			break;

		case 'T':
		case 't':
			test_and_mark();
			break;

		default:
			break;
		}
	}

	closesocket(sock);
	WSACleanup();


	return 0;
}