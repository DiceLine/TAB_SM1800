# **About it / Об этом**

TATB - Translate Assembler To Bytes. It's assembly language translator into machine code for the SM1800 computer.

# **How to use / Как использовать**

The program runs in the console. The first parameter is the full path of the file with the assembly code. The second (optional) parameter is the full path to where the machine code is saved. If the second parameter is not specified, the default path is "C:\Users\UserName\Downloads". Exit file has a constant name "mc_CM-1800" and a .txt format.

Examples:
```
TATB_SM1800 "%USERPROFILE%\Desktop\AsmCode.txt"
TATB_SM1800 "%USERPROFILE%\Desktop\AsmCode.txt" "%USERPROFILE%\Desktop"
```

### In assembler code

You can set:
<li>Your program's starting address in memory by adding "&HEX_NUM". Used to address labels.
<li>Labels using ':' and you can refer to them.
<li>The brackets. It's just for visuality and designed for ease of programming.
<li>Any indents and separate numeric literals.
<li>Comments using ';' symbol.

Example:
```
;	An example of a translatable assembly program
{
	&50 00		; starting address
	intruction1	; some
	intruction2	; code
	JMP INST4	; jump to address
	intruction3
INST4:	intruction4
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

<li>command system architecture КР58ОИК80А
<li>clock frequency 2 MHz word width 8 bits
<li>instruction execution time from 2 to 8.5 µs, maximum memory size (combination of RAM and permanent memory - arbitrary) 64 KB, maximum number of addressable input ports 256 outputs 256,
number of interrupt levels 8
<li>system interface I40, I41 (Multibus)

SM 1800 consists of a base computer (BECM), a set of external device modules located in a cabinet, rack and operator’s desk.

The BECM has four modifications:

**<li>SM-1801**  — Basic computer, consists of a mounting block, a central processor module and a system control module (SCM, console). It is the basis of a microcomputer in a frame design for embedding in installations
**<li>SM-1802**  — Basic computer, consists of an autonomous compact unit (ACU), a central processor module (CPM) and a system control module (SCM, console). It is the basis for embedded microcomputers.
**<li>SM-1803**  — Basic computer, similar in composition and purpose to SM-1802, but has a stack design. Overall dimensions in height are 6U.
**<li>SM-1804** — Designed for use in industrial environments with demanding operating conditions.

# **Assembler / Ассемблер**

*The above text is taken from the manual of **"St. Petersburg State Technical University (TU) Peskov I.A., Makaruk R.V. Development of programs in machine codes and assembly language: workshop for full-time students. – SPb.: St. Petersburg State Technical University (TU), 2019. – 76 p."**. The text is subject to the same copyright protection as the given manual.*

The SM-1800 microcomputer is an eight-bit built-in aggregative machine made on microcircuits of the К580, К589, К565 and other series. The central processor of the КР580ИК80А computer is a complete functional analogue of the single-chip microprocessor Intel 8080.

All external devices are connected via appropriate adapters to the SM-1800 system bus, made according to the I41 standard. The processor addresses devices according to this standard using the “isolated lines” method, which means the use of special input/output (IN/OUT) commands.

## COMMANDS of the SM-1800 microcomputer

### 1. SYMBOLS USED IN DESCRIBING ASSEMBLER COMMANDS.

When describing the commands of the SM-1800 microcomputer, the following register designations are used:

R – designation of one of the single-byte registers of the macroprocessor from the following set: A, B, C, D, E, H, L; 

F – flag register (one-byte), five of the eight bits of which are used to record the following characteristics of the operation result:
```
|-------------------------|------------------|------------------------------------------------------|-------------------------------------------------|
|  Bit in register F      |  Bit designation |                   Feature content                    |                   Bit state                     |
|                         |                  |                                                      |           «1»          |          «0»           |
|-------------------------|------------------|------------------------------------------------------|------------------------|------------------------|
|            0            |        CY        |             carry over from the 7th bit              | there is a carry over  | there is no carry over |
|            2            |        P         |   estimate of the number of units in the result code |          even          |           odd          |
|            4            |        AC        |              carryover from 3rd digit                |      yes carryover     |      no carryover      |
|            6            |        Z         |                     null result                      |      result is zero    |     result not zero    |
|            7            |        S         |                     result sign                      |    negative (minus)    |     positive (plus)    |
|-------------------------|------------------|------------------------------------------------------|------------------------|------------------------|
```
SP – stack pointer (two-byte register);

PC – program counter (two-byte register);

M is a symbol used to designate a RAM cell, and the address of this cell is indicated indirectly - it is contained in a pair of registers H, L.

### 2. BRIEF DESCRIPTION OF COMMANDS

```
Обозначение 	Описание
ADD R	Сложение содержимого регистра R с содержимым аккумулятора
ADD M 	Сложение содержимого ячейки памяти с содержимым аккумулятора
ADI (B2)	Сложение непосредственных данных (В2) с содержимым аккумулятора
ADC R	Сложение содержимого регистра R и аккумулятора
ADC M 	Сложение содержимого ячейки памяти и аккумулятора
ACI (B2)	Сложение непосредственных данных (В2) с содержимым аккумулятора
ANA R	Логическое умножение («И») содержимого регистра R и аккумулятора
ANA M	Логическое умножение («И») содержимого ячейки памяти и аккумулятора
ANI B2	Логическое умножение («И») содержимого непосредственных данных (В2) и аккумулятора
CALL (B2)(B3)	Вызов безусловный, т.е. переход к команде, адрес которой содержится во втором и третьем байтах команды
CC (B2)(B3)	Вызов по условию: при наличии переноса CY=1 – (по переносу)
CNC (B2)(B3)	Вызов по условию: при отсутствии переноса CY=0 – (нет переноса)
CZ (B2)(B3)	Вызов по условию: результат равен нулю Z=1 – (по нулю)
CNZ (B2)(B3)	Вызов по условию: результат не равен нулю Z=0 – (нет нуля)
CM (B2)(B3)	Вызов по условию: результат отрицателен S=1 – (по минусу)
CP (B2)(B3)	Вызов по условию: результат положителен S=0 (по плюсу)
CPE (B2)(B3)	Вызов по условию: сумма единиц в коде результата четная P=1 – (по четности)
CPO (B2)(B3)	Вызов по условию: сумма единиц в коде результата нечетная P=0 – (по нечетности)
CMA	Инвертирование содержимого аккумулятора
CMC	Инвертирование содержимого флага переноса CY 
CMP R	Сравнение содержимого регистра R и аккумулятора
CMP M 	Сравнение содержимого ячейки памяти и аккумулятора
CPI (B2)	Сравнение непосредственных данных (В2) и аккумулятора
DAA	Преобразование содержимого аккумулятора в BDD (двоично-десятичном коде)
DAD B	Сложение (В,С) с (H,L)
DAD D	Сложение (D,E) с (H,L)
DAD H	Сложение (H,L) с (H,L)
DAD SP	Сложение  указателя стека (SP) с (H,L)
DCR R	Отрицательное приращение R
DCR M	Отрицательное приращение содержимого ячейки памяти
DCX B	Отрицательное приращение (В,С)
DCX D	Отрицательное приращение (D,E)
DCX H	Отрицательное приращение (H,L)
DCX SP	Отрицательное приращение содержимого указателя стека (SP)
DI	Запрещение системного прерывания
EI	Разрешение системного прерывания
HLT	Останов
IN (B2)	Ввод данных в аккумулятор из порта, адрес которого определяется содержимым второго байта команды (В2)
INR R	Положительное приращение (R)
INR M	Положительное приращение содержимого ячейки памяти
INX B	Положительное приращение (B,C)
INX D	Положительное приращение (D,E)
INX H	Положительное приращение (H,L)
INX SP	Положительное приращение содержимого указателя стека (SP)
JMP (B2)(B3)	Переход безусловный к команде, адрес которой содержится во втором и третьем байтах команды
JC (B2)(B3)	Переход по условию: CY=1 – (по переносу)
JNC (B2)(B3)	Переход по условию: CY=0 – (нет переноса)
JZ (B2)(B3)	Переход по условию: Z=1 – (по нулю)
JNZ (B2)(B3)	Переход по условию: Z=0 – (нет нуля)
JM (B2)(B3)	Переход по условию: S=1 – (по минусу)
JP (B2)(B3)	Переход по условию: S=0 (по плюсу)
JPE (B2)(B3)	Переход по условию: P=1 – (по четности)
JPO (B2)(B3)	Переход по условию: P=0 – (по нечетности)
LDA (B2)(B3)	Загрузка аккумулятора содержимым ячейки памяти, адрес которой содержится во втором и третьем байтах команды
LDAX B	Загрузка аккумулятора содержимым ячейки памяти, адрес которой содержится в регистрах B,C
LDAX D	Загрузка аккумулятора содержимым ячейки памяти, адрес которой содержится в регистрах D,E
LHLD
 (B2)(B3)	Загрузка регистров H,L содержимым ячейки памяти, адрес которой содержится во втором и третьем байтах команды
LXI B, (B2)(B3)	Загрузка непосредственных данных В2,В3 в регистры B,C
LXI D, (B2)(B3)	Загрузка непосредственных данных В2,В3 в регистры D,E
LXI H, (B2)(B3)	Загрузка непосредственных данных В2,В3 в регистры H,L
LXI SP, (B2)(B3)	Загрузка непосредственных данных В2,В3 в указатель стека SP
MOV R1,R2	Пересылка содержимого регистра R2 в регистр R1
MOV R,M 	Пересылка содержимого ячейки памяти в регистр R
MOV M,R	Пересылка содержимого регистра R в ячейку памяти 
MVI R, (B2)	Пересылка непосредственных данных В2 в регистр R
MVI M, (B2)	Пересылка непосредственных данных В2 в ячейку памяти 
ORA R	Логическое сложение («ИЛИ») содержимого регистра R и аккумулятора
ORA M	Логическое сложение («ИЛИ») содержимого ячейки памяти и аккумулятора
ORI (B2)	Логическое сложение («ИЛИ») содержимого непосредственных данных (В2) и аккумулятора
OUT (B2)	Вывод данных из аккумулятора в порт, адрес которого содержится во втором байте команды В2
PCHL	Засылка (H,L) в программный счетчик PC 
POP B	Извлечение содержимого регистров B,C из стека
POP D	Извлечение содержимого регистров D,E из стека
POP H	Извлечение содержимого регистров H,L из стека
POP PSW	Извлечение содержимого аккумулятора А и регистра F из стека
PUSH B	Засылка содержимого регистров B,C в стек
PUSH D	Засылка содержимого регистров D,E в стек
PUSH H 	Засылка содержимого регистров H,L в стек
PUSH PSW	Засылка содержимого аккумулятора А и регистра F в стек
RAL	Циклический сдвиг содержимого аккумулятора влево на один разряд CY в А0,А7 в CY
RAR
	Циклический сдвиг содержимого аккумулятора вправо на один разряд CY в А7,А0 в CY
RLC	Циклический сдвиг содержимого аккумулятора влево на один разряд А7 в А0,А7 в CY
RRC	Циклический сдвиг содержимого аккумулятора вправо на один разряд А0 в А0,А7 в CY
RET	Возврат безусловный к команде с адресом, помещенным последним в стек
RC	Возврат по условию: CY=1 – (по переносу)
RNC	Возврат по условию: CY=0 – (нет переноса)
RZ	Возврат по условию: Z=1 – (по нулю)
RNZ	Возврат по условию: Z=0 – (нет нуля)
RM	Возврат по условию: S=1 – (по минусу)
RP	Возврат по условию: S=0 (по плюсу)
RPE	Возврат по условию: P=1 – (по четности)
RPO	Возврат по условию: P=0 – (по нечетности)
RST	Пуск по результатам обработки прерывания
SBB R	Вычитание из аккумулятора содержимого регистра R с заемом
SBB M	Вычитание из аккумулятора содержимого ячейки памяти с заемом
SBI (B2)	Вычитание из аккумулятора непосредственных данных В2 с заемом
SUB R	Вычитание из аккумулятора содержимого регистра R
SUB M	Вычитание из аккумулятора содержимого ячейки памяти
SUI (B2)	Вычитание из аккумулятора непосредственных данных В2
SHLD (B2)(B3)	Запись (H,L) в память с адресом, который содержится во втором и третьем байтах команды
SPHL	Засылка (H,L) в указатель стека SP
STA (B2)(B3)	Запись содержимого аккумулятора  в ячейку памяти, адрес которой содержится во втором и третьем байтах команды
STAX B	Запись содержимого аккумулятора  в ячейку памяти, адрес которой содержится в регистрах В,С
STAX D	Запись содержимого аккумулятора  в ячейку памяти, адрес которой содержится в регистрах D,E
STC	Установка флага переноса в состояние «1»
XRA R	Сложение по модулю («Исключающее ИЛИ») содержимого регистра R и аккумулятора
XRA M	Сложение по модулю («Исключающее ИЛИ») содержимого ячейки памяти и аккумулятор а
XRI (B2)	Сложение по модулю («Исключающее ИЛИ») непосредственных данных В2 и аккумулятора
XCHG	Обмен содержимым между регистрами D,E и H,L
XTHL	Обмен содержимым между верхними ячейками стека и регистрами H,L
```
### 3. COMMAND OPERATION CODES 
```
00 NOP          40 MOV B,B      80 ADD B      C0 RNZ  
01 LXI B,XXXX   41 MOV B,C      81 ADD C      C1 POP B  
02 STAX B       42 MOV B,D      82 ADD D      C2 JNZ XXXX  
03 INX B        43 MOV B,E	    83 ADD E	    C3 JMP XXXX  
04 INR B        44 MOV B,H 	    84 ADD H	    C4 CNZ XXXX  
05 DCR B        45 MOV B,L	    85 ADD L	    C5 PUSH B  
06 MVI B,XX     46 MOV B,M	    86 ADD M    	C6 ADI XX  
07 RLC          47 MOV B,A	    87 ADD A	    C7 RST 0  
08 - - - -      48 MOV C,B	    88 ADC B	    C8 RZ  
09  DAD B       49 MOV C,C	    89 ADC C    	C9 RET  
0A  LDAX B      4A MOV C,D	    8A ADC D	    CA JZ XXXX  
0B  DCX B       4B MOV C,E	    8B ADC E	    CB - - - -  
0C  INR C       4C MOV C,H 	    8C ADC H	    CC CZ XXXX  
0D  DCR C       4D MOV C,L	    8D ADC L	    CD CALL XXXX  
0E  MVI C,XX    4E MOV C,M	    8E ADC M    	CE ACI XX  
0F  RRC         4F MOV C,A	    8F ADC A	    CF RST 1  
10 - - - -      50 MOV D,B	    90 SUB B	    D0 RNC  
11 LXI D,XXXX   51 MOV D,C	    91 SUB C	    D1 POP D  
12 STAX D       52 MOV D,D	    92 SUB D	    D2 JNC XXXX  
13 INX D        53 MOV D,E	    93 SUB E	    D3 OUT XXXX  
14 INR D        54 MOV D,H      94 SUB H	    D4 CNC XXXX  
15 DCR D        55 MOV D,L	    95 SUB L      D5 PUSH D  
16 MVI D,XX     56 MOV D,M	    96 SUB M      D6 SUI XX  
17 RAL          57 MOV D,A	    97 SUB A      D7 RST 2  
18 - - - -      58 MOV E,B	    98 SBB B	    D8 RC  
19  DAD D       59 MOV E,C	    99 SBB C	    D9 - - - -  
1A  LDAX D      5A MOV E,D	    9A SBB D	    DA JC XXXX  
1B  DCX D       5B MOV E,E	    9B SBB E	    DB IN XX  
1C  INR E       5C MOV E,H 	    9C SBB H	    DC CC XXXX
1D  DCR E       5D MOV E,L	    9D SBB L	    DD - - - -  
1E  MVI E,XX    5E MOV E,M	    9E SBB M	    DE SBI XX  
1F  RAR         5F MOV E,A	    9F SBB A	    DF RST 3  
20 - - - -      60 MOV H,B	    A0 ANA B	    E0 RPO  
21 LXI H,XXXX   61 MOV H,C	    A1 ANA C	    E1 POP H  
22 SHLD XXXX    62 MOV H,D	    A2 ANA D	    E2 JPO XXXX  
23 INX H        63 MOV H,E	    A3 ANA E	    E3 XTHL  
24 INR H        64 MOV H,H 	    A4 ANA H	    E4 CPO XXXX  
25 DCR H        65 MOV H,L	    A5 ANA L	    E5 PUSH H  
26 MVI H,XX     66 MOV H,M	    A6 ANA M	    E6 ANI XX  
27 DAA          67 MOV H,A	    A7 ANA A	    E7 RST 4  
28 - - - -      68 MOV L,B	    A8 XRA B	    E8 RPE  
29 DAD H        69 MOV L,C	    A9 XRA C	    E9 PCHL  
2A LHLD XXXX    6A MOV L,D	    AA XRA D	    EA JPE XXXX  
2B DCX H        6B MOV L,E	    AB XRA E	    EB XCHG  
2C INR L        6C MOV L,H 	    AC XRA H	    EC CPE XXXX  
2D DCR L        6D MOV L,L	    AD XRA L	    ED - - - -  
2E MVI L,XX     6E MOV L,M	    AE XRA M	    EE XRI XX  
2F CMA          6F MOV L,A	    AF XRA A	    EF RST 5  
30 - - - -      70 MOV M,B	    B0 ORA B	    F0 RP  
31 LXI SP,XXXX  71 MOV M,C	    B1 ORA C	    F1 POP PSW  
32 STA XXXX     72 MOV M,D	    B2 ORA D	    F2 JP XXXX  
33 INX SP       73 MOV M,E	    B3 ORA E	    F3 DI  
34 INR M        74 MOV M,H      B4 ORA H	    F4 CP XXXX  
35 DCR M        75 MOV M,L	    B5 ORA L	    F5 PUSH PSW  
36 MVI M,XX     76 HLT          B6 ORA M	    F6 ORI XX  
37 STC          77 MOV M,A	    B7 ORA A	    F7 RST 6  
38 - - - -      78 MOV A,B	    B8 CMP B	    F8 RM  
39 DAD SP       79 MOV A,C	    B9 CMP C	    F9 SPHL  
3A LHLD XXXX    7A MOV A,D	    BA CMP D	    FA JM XXXX  
3B DCX SP       7B MOV A,E	    BB CMP E	    FB EI  
3C INR A        7C MOV A,H 	    BC CMP H	    FC CM XXXX  
3D DCR A        7D MOV A,L	    BD CMP L	    FD - - - -  
3E MVI A,XX     7E MOV A,M	    BE CMP M	    FE CPI XX  
3F CMC          7F MOV A,A	    BF CMP A	    FF RST 7  
```
