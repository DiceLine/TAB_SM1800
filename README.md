# **About it**

TAB - Translate Assembler to Bytes. It's assembly language translator into machine code for the SM1800 computer. This is an implementation of the standard SM-1800 assembler specification with a slight extension.

# **How to use**

The program runs in the console. The first parameter is the full path of the file with the assembly code. The second (optional) parameter is the full path to where the machine code is saved. If the second parameter is not specified, the default path is "C:\Users\UserName\Downloads". Exit file has a constant name "mc_CM-1800" and a .txt format.

Examples:
```
TAB_SM1800 "%USERPROFILE%\Desktop\AsmCode.txt"
TAB_SM1800 "%USERPROFILE%\Desktop\AsmCode.txt" "%USERPROFILE%\Desktop"
```

### In assembler code

#### Standart specification

* Labels system. Using ':' to set labels and being able to reference them
* Standard commands that are listed in Section 3. COMMAND OPERATION CODES
* Strict literal format: no delimiters
* Comments using ';' symbol.
* The 'h' or 'H' character at the end of a hexadecimal literal. (optionally)

#### Specification extension

You can set:
* Your program's starting address in memory by adding "&HEX_NUM". Used to address labels.
* The brackets. It's just for visuality and designed for ease of programming.
* Any indents and separate numeric literals.

Example:
```
;	An example of a translatable assembly language program similar to the isNotZero() function with a strong simplification
{
	&50 00		; starting address
	MVI A, 01h	; some
	DCR A		; code
	JZ EXIT		; jump to the address if the result of the last operation is equal to zero
	MVI A, 01H	; we report that the result is not equal to zero.
EXIT:	RET
}
```

# **Для чего / Wherefore**
Для русскоязычного читателя есть статьи (Original links):

[wiki](https://ru.wikipedia.org/wiki/%D0%A1%D0%9C_%D0%AD%D0%92%D0%9C)

<http://ineum.ru/sm-1800>

**ECM - Electronic Computing Machine.**

**SM ECM**  (a “system of small” ECM) is a series (family) of control computers created in the late 1970s  – early 1980s with the participation of various countries that were members of the CMEA.

## **History**:

More than 30 institutes and enterprises took part in the development: from Bulgaria , Hungary , the GDR , Cuba , Poland , Romania and Czechoslovakia .

In 1974  , by decision of the Intergovernmental Commission for Cooperation of Socialist Countries in the Field of Computer Engineering (IPC CT), the Institute of Electronic Control Machines (INEUM) was appointed the lead organization. Chief Designer - B. N. Naumov , since 1984  - N. L. Prokhorov .

In 1981, a number of managers and developers were awarded the USSR State Prize with the wording “for the development and organization of serial production of the SM 3 and SM 4 complexes of technical and software tools of the international small computer system”

## **Intel line**:

It was developed under the supervision of N. L. Prokhorov with the participation of specialists from the Kiev NPO Electronmash . It had a modular structure with the unification of modules via the I41 bus (OST 25.969-83) - a modified Multibus .

**SM-1800  — 8-bit on the КР580ВМ80А processor (analogous to Intel 8080 ). Bus — I41. Produced since 1981 at the Minpribor factories in Kiev and Tbilisi**:

Main technical characteristics:

* command system architecture КР58ОИК80А
* clock frequency 2 MHz word width 8 bits
* instruction execution time from 2 to 8.5 µs, maximum memory size (combination of RAM and permanent memory - arbitrary) 64 KB, maximum number of addressable input ports 256 outputs 256,
number of interrupt levels 8
* system interface I40, I41 (Multibus)

SM 1800 consists of a base computer (BECM), a set of external device modules located in a cabinet, rack and operator’s desk.

The BECM has four modifications:

* **SM-1801**  — Basic computer, consists of a mounting block, a central processor module and a system control module (SCM, console). It is the basis of a microcomputer in a frame design for embedding in installations
* **SM-1802**  — Basic computer, consists of an autonomous compact unit (ACU), a central processor module (CPM) and a system control module (SCM, console). It is the basis for embedded microcomputers.
* **SM-1803**  — Basic computer, similar in composition and purpose to SM-1802, but has a stack design. Overall dimensions in height are 6U.
* **SM-1804** — Designed for use in industrial environments with demanding operating conditions.

# **Assembler / Ассемблер**

*The above text is taken from the manual of **"St. Petersburg State Technical University (TU) Peskov I.A., Makaruk R.V. Development of programs in machine codes and assembly language: workshop for full-time students. – SPb.: St. Petersburg State Technical University (TU), 2019. – 76 p."**. The text is subject to the same copyright protection as the given manual.*

The SM-1800 microcomputer is an eight-bit built-in aggregative machine made on microcircuits of the К580, К589, К565 and other series. The central processor of the КР580ИК80А computer is a complete functional analogue of the single-chip microprocessor Intel 8080.

All external devices are connected via appropriate adapters to the SM-1800 system bus, made according to the I41 standard. The processor addresses devices according to this standard using the “isolated lines” method, which means the use of special input/output (IN/OUT) commands.

## COMMANDS of the SM-1800 microcomputer

### 1. SYMBOLS USED IN DESCRIBING ASSEMBLER COMMANDS.

When describing the commands of the SM-1800 microcomputer, the following register designations are used:

R – designation of one of the single-byte registers of the macroprocessor from the following set: A, B, C, D, E, H, L; 

F – flag register (one-byte), five of the eight bits of which are used to record the following characteristics of the operation result:

|  Bit in register F      |  Bit designation |                   Feature content                    | Bit state «1»          |    Bit State «0»       |
|:-----------------------:|:----------------:|:----------------------------------------------------:|:----------------------:|:----------------------:|
|            0            |        CY        |             carry over from the 7th bit              | there is a carry over  | there is no carry over |
|            2            |        P         |   estimate of the number of units in the result code |          even          |           odd          |
|            4            |        AC        |              carryover from 3rd digit                |      yes carryover     |      no carryover      |
|            6            |        Z         |                     null result                      |      result is zero    |     result not zero    |
|            7            |        S         |                     result sign                      |    negative (minus)    |     positive (plus)    |

SP – stack pointer (two-byte register);

PC – program counter (two-byte register);

M is a symbol used to designate a RAM cell, and the address of this cell is indicated indirectly - it is contained in a pair of registers H, L.

In the description of commands of cyclic shift of the accumulator contents (RAL, RAR, RLC, RRC) the designation AM - bit M of the register A (accumulator) is used, and A0 and A7 are respectively the low and high (sign) bits of the accumulator.

When reading the description of commands, the following notations should be taken into account when writing:

B2 - the second byte of the command ( in ADI, ACI, ANI, CPI, CPI, MVI, ORI, SBI, SUI, XRI commands - this is the direct data, in IN and OUT commands - the port address),

B3 - the third byte of the command, usually does not appear independently

( ) - byte content (command, register, memory). Should read:
* (H) - the contents of the H register,
* (B) - the contents of the register B,
* (B2)- the content of the second byte of the command,
* (M) - the contents of the RAM cell, the address of which is placed in the pair of registers H, L, i.e. the address is (H, L).

### 2. BRIEF DESCRIPTION OF COMMANDS
| Designation | Description |
|:----------|:---|
|ADD R| Adds the contents of the R register to the contents of the accumulator|
|ADD M| Adds the contents of a memory location to the contents of the accumulator|
|ADI (B2)| Addition of direct data (B2) to the accumulator content|
|ADC R| Adding the contents of the R register and the accumulator|
|ADC M| Adding the contents of the memory location and the accumulator|
|ACI (B2)| Adding the direct data (B2) to the contents of the accumulator|
|ANA R| Logical multiplication ("AND") of the contents of register R and accumulator|
|ANA M| Logical multiplication ("AND") of the contents of the memory location and the accumulator|
|ANI B2| Logical multiplication ("AND") of the contents of the direct data (B2) and the accumulator|
|CALL (B2)(B3)| Unconditional call, i.e., a jump to the instruction whose address is contained in the second and third bytes of the instruction|
|CC (B2)(B3)| Call by condition: if there is a carry CY=1 - (by carry)|
|CNC (B2)(B3)| Condition call: if there is no transfer CY=0 - (no transfer)|
|CZ (B2)(B3)| Call by condition: result is zero Z=1 - (zero)|
|CNZ (B2)(B3)|Condition call: the result is not zero Z=0 - (no zero)|
|CM (B2)(B3)| Call by condition: the result is negative S=1 - (minus)|
|CP (B2)(B3)| Call by condition: the result is positive S=0 (plus)|
|CPE (B2)(B3)| Call by condition: the sum of the units in the result code is even P=1 - (parity)|
|CPO (B2)(B3)| Condition call: the sum of the units in the result code is odd P=0 - (odd)|
|CMA| Inverting the contents of the accumulator|
|CMC| Inverting the content of the CY carry flag |
|CMP R| Comparing the contents of the R register and the accumulator|
|CMP M| Comparing the contents of a memory location and the accumulator|
|CPI (B2)| Comparison of direct data (B2) and accumulator|
|DAA| Convert the accumulator contents to BDD (Binary Decimal Code)|
|DAD B| Add (B,C) to (H,L)|
|DAD D| Adding (D,E) to (H,L)|
|DAD H| Adding (H,L) to (H,L)|
|DAD SP| Add stack pointer (SP) to (H,L)|
|DCR R| Negative increment of R|
|DCR M| Negative increment of memory location content|
|DCX B| Negative increment (B,C)|
|DCX D|Negative increment (D,E)|
|DCX H| Negative increment (H,L)|
|DCX SP| Negative increment of stack pointer contents (SP)|
|DI| System Interrupt Inhibit|
|EI| Enable system interrupt|
|HLT| Stop|
|IN (B2)| Input data into the accumulator from the port whose address is determined by the content of the second byte of the command (B2)|
|INR R| Positive increment (R)|
|INR M| Positive increment of the contents of the memory location|
|INX B| Positive increment (B,C)|
|INX D| Positive increment (D,E)|
|INX H|Positive increment (H,L)|
|INX SP |Positive increment of stack pointer contents (SP)|
|JMP (B2)(B3)| Unconditional jump to the instruction whose address is contained in the second and third bytes of the instruction|
|JC (B2)(B3)| Transition by condition: CY=1 - (by carry)|
|JNC (B2)(B3)| Condition transition: CY=0 - (no carry)|
|JZ (B2)(B3)| Transition by condition: Z=1 - (zero)|
|JNZ (B2)(B3)| Condition Transition: Z=0 - (no zero)|
|JM (B2)(B3)| Condition Transition: S=1 - (minus)|
|JP (B2)(B3)|Condition transition: S=0 (plus)|
|JPE (B2)(B3)|Jump by condition: P=1 - (parity)|
|JPO (B2)(B3)| Condition transition: P=0 - (odd parity)|
|LDA (B2)(B3)| Load the accumulator with the contents of the memory location whose address is contained in the second and third bytes of the command|
|LDAX B| Load the accumulator with the contents of the memory location whose address is contained in registers B,C|
|LDAX D| Load the accumulator with the contents of the memory location whose address is contained in registers D,E|
|LHLD (B2)(B3)| Load registers H,L with the contents of the memory location whose address is contained in the second and third bytes of the command|
|LXI B, (B2)(B3)| Load direct data B2,B3 into registers B,C|
|LXI D, (B2)(B3)| Load direct data B2,B3 into registers D,E|
|LXI H, (B2)(B3)| Load direct data B2,B3 into registers H,L|
|LXI SP, (B2)(B3)| Load direct data B2,B3 into stack pointer SP|
|MOV R1,R2| Send the contents of the register R2 to the register R1|
|MOV R,M | Send the contents of a memory location to the R register|
|MOV M,R | Send the contents of register R to memory cell |
|MVI R, (B2)| Send direct data B2 to register R|
|MVI M, (B2)| Send direct B2 data to memory location |
|ORA R |Logical addition ("OR") of the contents of the register R and the accumulator|
|ORA M |Logical addition (OR) of the contents of the memory location and the accumulator|
|ORI (B2)| Logical OR addition of the contents of the immediate data (B2) and the accumulator|
|OUT (B2)| Outputs data from the accumulator to the port whose address is contained in the second byte of the B2 instruction|
|PCHL| Send (H,L) to the PC program counter |
|POP B| Retrieve the contents of registers B,C from the stack|
|POP D| Fetch the contents of registers D,E from the stack|
|POP H |Fetch the contents of registers H,L from the stack|
|POP PSW| Retrieve the contents of accumulator A and register F from the stack|
|PUSH B |Send the contents of registers B,C to the stack|
|PUSH D |Send the contents of registers D,E to the stack|
|PUSH H |Send the contents of registers H,L to the stack|
|PUSH PSW| Send the contents of accumulator A and register F to the stack|
|RAL |Cyclic shift of the accumulator contents to the left one bit CY to A0,A7 to CY|
|RAR |Cyclic shift of the accumulator content to the right by one digit CY in A7,A0 in CY|
|RLC| Cyclic shift of the accumulator content to the left by one digit A7 in A0,A7 in CY|
|RRC| Cyclic shift of the accumulator content to the right by one digit A0 in A7,A0 in CY|
|RET| Return unconditional to the instruction with the last address on the stack|
|RC |Return by condition: CY=1 - (by carry)|
|RNC| Return by condition: CY=0 - (no carryover)|
|RZ |Return by condition: Z=1 - (by zero)|
|RNZ| Return by condition: Z=0 - (no zero)|
|RM |Return by condition: S=1 - (minus)|
|RP |Return by condition: S=0 (on the plus side)|
|RPE| Return by condition: P=1 - (parity)|
|RPO| Return by condition: P=0 - (odd parity)|
|RST |Start by results of interrupt processing|
|SBB R| Subtract the contents of the R register from the accumulator with the offset|
|SBB M| Subtract from the accumulator the contents of a memory location with a memory location|
|SBI (B2)| Subtracting from the accumulator the direct data of B2 with a scope|
|SUB R | Subtract the contents of the R register from the accumulator|
|SUB M |Subtract the contents of a memory location from the accumulator|
|SUI (B2)| Subtracting direct data B2 from the accumulator|
|SHLD (B2)(B3)| Writing (H,L) to memory with the address contained in the second and third bytes of the instruction|
|SPHL| Sending (H,L) to the SP stack pointer|
|STA (B2)(B3)| Writing the contents of the accumulator to the memory location whose address is contained in the second and third bytes of the instruction|
|STAX B| Write the contents of the accumulator in a memory location whose address is contained in registers B,C|
|STAX D| Write the contents of the accumulator in a memory location whose address is contained in registers D,E|
|STC| Set the carry flag to the state "1"|
|XRA R| Modulo addition ("Excluding OR") of the contents of the register R and the accumulator|
|XRA M| Modulo addition ("Excluding OR") of the contents of the memory location and the accumulator|
|XRI (B2)| Modulo OR addition of the direct data of B2 and the accumulator|
|XCHG| Exchange of contents between registers D,E and H,L|
|XTHL| Exchanging content between the upper stack cells and the H,L registers|

### 3. COMMAND OPERATION CODES
```
00 NOP          40 MOV B,B      80 ADD B      C0 RNZ  
01 LXI B,XXXX   41 MOV B,C      81 ADD C      C1 POP B  
02 STAX B       42 MOV B,D      82 ADD D      C2 JNZ XXXX  
03 INX B        43 MOV B,E      83 ADD E      C3 JMP XXXX  
04 INR B        44 MOV B,H      84 ADD H      C4 CNZ XXXX  
05 DCR B        45 MOV B,L      85 ADD L      C5 PUSH B  
06 MVI B,XX     46 MOV B,M      86 ADD M      C6 ADI XX  
07 RLC          47 MOV B,A      87 ADD A      C7 RST 0  
08 - - - -      48 MOV C,B      88 ADC B      C8 RZ  
09 DAD B        49 MOV C,C      89 ADC C      C9 RET  
0A LDAX B       4A MOV C,D      8A ADC D      CA JZ XXXX  
0B DCX B        4B MOV C,E      8B ADC E      CB - - - -  
0C INR C        4C MOV C,H      8C ADC H      CC CZ XXXX  
0D DCR C        4D MOV C,L      8D ADC L      CD CALL XXXX  
0E MVI C,XX     4E MOV C,M      8E ADC M      CE ACI XX  
0F RRC          4F MOV C,A      8F ADC A      CF RST 1  
10 - - - -      50 MOV D,B      90 SUB B      D0 RNC  
11 LXI D,XXXX   51 MOV D,C      91 SUB C      D1 POP D  
12 STAX D       52 MOV D,D      92 SUB D      D2 JNC XXXX  
13 INX D        53 MOV D,E      93 SUB E      D3 OUT XXXX  
14 INR D        54 MOV D,H      94 SUB H      D4 CNC XXXX  
15 DCR D        55 MOV D,L      95 SUB L      D5 PUSH D  
16 MVI D,XX     56 MOV D,M      96 SUB M      D6 SUI XX  
17 RAL          57 MOV D,A      97 SUB A      D7 RST 2  
18 - - - -      58 MOV E,B      98 SBB B      D8 RC  
19 DAD D        59 MOV E,C      99 SBB C      D9 - - - -  
1A LDAX D       5A MOV E,D      9A SBB D      DA JC XXXX  
1B DCX D        5B MOV E,E      9B SBB E      DB IN XX  
1C INR E        5C MOV E,H      9C SBB H      DC CC XXXX
1D DCR E        5D MOV E,L      9D SBB L      DD - - - -  
1E MVI E,XX     5E MOV E,M      9E SBB M      DE SBI XX  
1F RAR          5F MOV E,A      9F SBB A      DF RST 3  
20 - - - -      60 MOV H,B      A0 ANA B      E0 RPO  
21 LXI H,XXXX   61 MOV H,C      A1 ANA C      E1 POP H  
22 SHLD XXXX    62 MOV H,D      A2 ANA D      E2 JPO XXXX  
23 INX H        63 MOV H,E      A3 ANA E      E3 XTHL  
24 INR H        64 MOV H,H      A4 ANA H      E4 CPO XXXX  
25 DCR H        65 MOV H,L      A5 ANA L      E5 PUSH H  
26 MVI H,XX     66 MOV H,M      A6 ANA M      E6 ANI XX  
27 DAA          67 MOV H,A      A7 ANA A      E7 RST 4  
28 - - - -      68 MOV L,B      A8 XRA B      E8 RPE  
29 DAD H        69 MOV L,C      A9 XRA C      E9 PCHL  
2A LHLD XXXX    6A MOV L,D      AA XRA D      EA JPE XXXX  
2B DCX H        6B MOV L,E      AB XRA E      EB XCHG  
2C INR L        6C MOV L,H      AC XRA H      EC CPE XXXX  
2D DCR L        6D MOV L,L      AD XRA L      ED - - - -  
2E MVI L,XX     6E MOV L,M      AE XRA M      EE XRI XX  
2F CMA          6F MOV L,A      AF XRA A      EF RST 5  
30 - - - -      70 MOV M,B      B0 ORA B      F0 RP  
31 LXI SP,XXXX  71 MOV M,C      B1 ORA C      F1 POP PSW  
32 STA XXXX     72 MOV M,D      B2 ORA D      F2 JP XXXX  
33 INX SP       73 MOV M,E      B3 ORA E      F3 DI  
34 INR M        74 MOV M,H      B4 ORA H      F4 CP XXXX  
35 DCR M        75 MOV M,L      B5 ORA L      F5 PUSH PSW  
36 MVI M,XX     76 HLT          B6 ORA M      F6 ORI XX  
37 STC          77 MOV M,A      B7 ORA A      F7 RST 6  
38 - - - -      78 MOV A,B      B8 CMP B      F8 RM  
39 DAD SP       79 MOV A,C      B9 CMP C      F9 SPHL  
3A LHLD XXXX    7A MOV A,D      BA CMP D      FA JM XXXX  
3B DCX SP       7B MOV A,E      BB CMP E      FB EI  
3C INR A        7C MOV A,H      BC CMP H      FC CM XXXX  
3D DCR A        7D MOV A,L      BD CMP L      FD - - - -  
3E MVI A,XX     7E MOV A,M      BE CMP M      FE CPI XX  
3F CMC          7F MOV A,A      BF CMP A      FF RST 7  
```
