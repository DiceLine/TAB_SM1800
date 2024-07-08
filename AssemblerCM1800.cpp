


#pragma once

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <windows.h>
#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <cwchar>
#include <cwctype>

#include "AssemblerCM1800.h"


void setOldCP(UINT* oldCp) {
	SetConsoleCP(*oldCp);
	SetConsoleOutputCP(*oldCp);
}

template<typename ... Args>
wstring string_format(const wstring& format, Args ... args)
{
	int32_t size_s = swprintf(nullptr, 0, format.c_str(), args ...) + 1;
	if (size_s <= 0) { throw runtime_error("Error during formatting."); }
	auto size = static_cast<size_t>(size_s);
	unique_ptr<wchar_t[]> buf(new wchar_t[size]);
	swprintf(buf.get(), size, format.c_str(), args ...);
	return wstring(buf.get(), buf.get() + size - 1);
}

wstring to_wstring(const string& str) {
	static size_t length;
	static wchar_t dest[MAXWORD];
	if (mbstowcs_s(&length, dest, MAXWORD, str.c_str(), str.length()) != 0)
		return L"";
	return wstring(dest).substr(0, length);
}

string to_string(const wstring& str)
{
	static size_t length;
	static char dest[2 * MAXWORD];
	if (wcstombs_s(&length, dest, 2 * MAXWORD, str.c_str(), str.length()) != 0)
		return "";
	return string(dest).substr(0, length);
}

wstring to_wcopy(const wstring& str)
{
	return wstring(str.c_str());
}

string to_copy(const string& str)
{
	return string(str.c_str());
}

wstring str_toupper(wstring str) {
	transform(str.begin(), str.end(), str.begin(), [](wchar_t ch) { return towupper(ch); });
	return str;
}

bool hasWcsDifProp(wstring& wchStr) {
	bool isUpper = false, isLower = false;
	for (int64_t i = 0; i < wchStr.length(); ++i) {
		if (iswupper(wchStr[i])) isUpper = true;
		else if(iswlower(wchStr[i])) isLower = true;
	}
	return isUpper && isLower;
}

AssemblerCM1800::AssemblerCM1800() {

	// Набор инструкций процессора
	// Если вы хотите добавить новую инструкцию,
	// то если эта инструкция использует запятую, то обязательно включайте ее в строку.
	// В других случаях команда записывается строго, как должна быть введена.
	asmTable = new const wchar_t* [INSTR_QUANTITY] {
			L"NOP",
			L"LXI B,",
			L"STAX B",
			L"INX B",
			L"INR B",
			L"DCR B",
			L"MVI B,",
			L"RLC",
			L"",
			L"DAD B",
			L"LDAX B",
			L"DCX B",
			L"INR C",
			L"DCR C",
			L"MVI C,",
			L"RRC",
			L"",
			L"LXI D,",
			L"STAX D",
			L"INX D",
			L"INR D",
			L"DCR D",
			L"MVI D,",
			L"RAL",
			L"",
			L"DAD D",
			L"LDAX D",
			L"DCX D",
			L"INR E",
			L"DCR E",
			L"MVI E,",
			L"RAR",
			L"",
			L"LXI H,",
			L"SHLD",
			L"INX H",
			L"INR H",
			L"DCR H",
			L"MVI H,",
			L"DAA",
			L"",
			L"DAD H",
			L"LHLD",
			L"DCX H",
			L"INR L",
			L"DCR L",
			L"MVI L,",
			L"CMA",
			L"",
			L"LXI SP,",
			L"STA",
			L"INX SP",
			L"INR M",
			L"DCR M",
			L"MVI M,",
			L"STC",
			L"",
			L"DAD SP",
			L"LHLD",
			L"DCX SP",
			L"INR A",
			L"DCR A",
			L"MVI A,",
			L"CMC",
			L"MOV B,B",
			L"MOV B,C",
			L"MOV B,D",
			L"MOV B,E",
			L"MOV B,H",
			L"MOV B,L",
			L"MOV B,M",
			L"MOV B,A",
			L"MOV C,B",
			L"MOV C,C",
			L"MOV C,D",
			L"MOV C,E",
			L"MOV C,H",
			L"MOV C,L",
			L"MOV C,M",
			L"MOV C,A",
			L"MOV D,B",
			L"MOV D,C",
			L"MOV D,D",
			L"MOV D,E",
			L"MOV D,H",
			L"MOV D,L",
			L"MOV D,M",
			L"MOV D,A",
			L"MOV E,B",
			L"MOV E,C",
			L"MOV E,D",
			L"MOV E,E",
			L"MOV E,H",
			L"MOV E,L",
			L"MOV E,M",
			L"MOV E,A",
			L"MOV H,B",
			L"MOV H,C",
			L"MOV H,D",
			L"MOV H,E",
			L"MOV H,H",
			L"MOV H,L",
			L"MOV H,M",
			L"MOV H,A",
			L"MOV L,B",
			L"MOV L,C",
			L"MOV L,D",
			L"MOV L,E",
			L"MOV L,H",
			L"MOV L,L",
			L"MOV L,M",
			L"MOV L,A",
			L"MOV M,B",
			L"MOV M,C",
			L"MOV M,D",
			L"MOV M,E",
			L"MOV M,H",
			L"MOV M,L",
			L"HLT",
			L"MOV M,A",
			L"MOV A,B",
			L"MOV A,C",
			L"MOV A,D",
			L"MOV A,E",
			L"MOV A,H",
			L"MOV A,L",
			L"MOV A,M",
			L"MOV A,A",
			L"ADD B",
			L"ADD C",
			L"ADD D",
			L"ADD E",
			L"ADD H",
			L"ADD L",
			L"ADD M",
			L"ADD A",
			L"ADC B",
			L"ADC C",
			L"ADC D",
			L"ADC E",
			L"ADC H",
			L"ADC L",
			L"ADC M",
			L"ADC A",
			L"SUB B",
			L"SUB C",
			L"SUB D",
			L"SUB E",
			L"SUB H",
			L"SUB L",
			L"SUB M",
			L"SUB A",
			L"SBB B",
			L"SBB C",
			L"SBB D",
			L"SBB E",
			L"SBB H",
			L"SBB L",
			L"SBB M",
			L"SBB A",
			L"ANA B",
			L"ANA C",
			L"ANA D",
			L"ANA E",
			L"ANA H",
			L"ANA L",
			L"ANA M",
			L"ANA A",
			L"XRA B",
			L"XRA C",
			L"XRA D",
			L"XRA E",
			L"XRA H",
			L"XRA L",
			L"XRA M",
			L"XRA A",
			L"ORA B",
			L"ORA C",
			L"ORA D",
			L"ORA E",
			L"ORA H",
			L"ORA L",
			L"ORA M",
			L"ORA A",
			L"CMP B",
			L"CMP C",
			L"CMP D",
			L"CMP E",
			L"CMP H",
			L"CMP L",
			L"CMP M",
			L"CMP A",
			L"RNZ",
			L"POP B",
			L"JNZ",
			L"JMP",
			L"CNZ",
			L"PUSH B",
			L"ADI",
			L"RST 0",
			L"RZ",
			L"RET",
			L"JZ",
			L"",
			L"CZ",
			L"CALL",
			L"ACI",
			L"RST 1",
			L"RNC",
			L"POP D",
			L"JNC",
			L"OUT",
			L"CNC",
			L"PUSH D",
			L"SUI",
			L"RST 2",
			L"RC",
			L"",
			L"JC",
			L"IN",
			L"CC",
			L"",
			L"SBI",
			L"RST 3",
			L"RPO",
			L"POP H",
			L"JPO",
			L"XTHL",
			L"CPO",
			L"PUSH H",
			L"ANI",
			L"RST 4",
			L"RPE",
			L"PCHL",
			L"JPE",
			L"XCHG",
			L"CPE",
			L"",
			L"XRI",
			L"RST 5",
			L"RP",
			L"POP PSW",
			L"JP",
			L"DI",
			L"CP",
			L"PUSH PSW",
			L"ORI",
			L"RST 6",
			L"RM",
			L"SPHL",
			L"JM",
			L"EI",
			L"CM",
			L"",
			L"CPI",
			L"RST 7"
	};

	// Динамические массивы для мнемоник и операндов
	mnemonics = vector<SetA>(INSTR_QUANTITY);
	operators = vector<wstring>(OPERATORS_QNTY);

	operators[0] = L"A";
	operators[1] = L"B";
	operators[2] = L"C";
	operators[3] = L"D";
	operators[4] = L"E";
	operators[5] = L"H";
	operators[6] = L"L";
	operators[7] = L"M";
	operators[8] = L"SP";
	operators[9] = L"PSW";

	wstring str;
	
	for (int64_t i = 0, j; i < INSTR_QUANTITY; ++i) {
		str = asmTable[i];
		for (j = 0; j <= str.length(); ++j) {
			if (asmTable[i][j] == L' ' || asmTable[i][j] == L'\0') {
				mnemonics[i].command = str.substr(0, j);
				mnemonics[i].index = i;
				break;
			}
		}
	}
	
	sort(mnemonics.begin(), mnemonics.end(), [](SetA a, SetA b) -> bool { return a.command.length() < b.command.length(); });

	machineCodes = new wchar_t* [INSTR_QUANTITY];

	for (uint32_t i = 0; i < INSTR_QUANTITY; ++i) {
		machineCodes[i] = new wchar_t[3];
		str = string_format(L"%02X", i);
		wcscpy_s(machineCodes[i], 3, str.c_str());
	}
}

AssemblerCM1800::AssemblerCM1800(const wstring& text) {
	AssemblerCM1800();
	asmCode = text;
}

AssemblerCM1800::~AssemblerCM1800() {
	delete[] asmTable;
	delete[] machineCodes;

	asmTable = nullptr;
	machineCodes = nullptr;
}

void AssemblerCM1800::clear() {
	asmCode.clear();
}

void AssemblerCM1800::setCode(const wstring& text, bool addMode) {
	if (!addMode) {
		asmCode = text;
		return;
	}
	asmCode += text;
}

void AssemblerCM1800::setError(wstring formatMessage, bool& hadErrorCode) {
	wstring warningStr;
	if (!hadErrWarning) {
		warningStr =
		L"\tПредупреждение:\nЕсли программа указывает на ошибку ввода, но вам кажется, что ассемблерный текст корректный, убедитесь, что все символы латинские.\n";
		hadErrWarning = true;
	}
	hadErrorCode = true;
	errorStr += warningStr + formatMessage + L'\n';
}

int64_t AssemblerCM1800::getStringsQuantity() {
	return strCounter;
}

bool AssemblerCM1800::hasNumFormat(wstring& str) {
	int64_t len = str.length();
	if (len == 0) return true;
	wstring outStr;
	for (int64_t k = 0; k < len; ++k) {
		if (iswxdigit(str[k])) outStr += str[k];
		else if (str[k] != L' ') {
			if (k > 0 && iswxdigit(str[k - 1]) && (str[k] == L'H' || str[k] == L'h')) {
				continue;
			}
			return false;
		}
	}
	str = outStr;
	return true;
}

bool AssemblerCM1800::hasOperandFormat(wstring& str) {
	int64_t curLen = str.length();
	if (curLen == 0) return true;
	int64_t opLen;
	for (int64_t k = 0; k < OPERATORS_QNTY; ++k) {
		opLen = operators[k].length();
		if (curLen < opLen) break;
		if (str.compare(operators[k]) == 0) return true;
	}
	return false;
}

bool AssemblerCM1800::hasMnemonic(wstring& str) {
	int64_t curLen = str.length();
	if (curLen == 0) return true;
	int64_t mnemonicLen;
	for (int64_t k = 0; k < INSTR_QUANTITY; ++k) {
		mnemonicLen = mnemonics[k].command.length();
		if (curLen < mnemonicLen) break;
		if (str.compare(mnemonics[k].command) == 0) return true;
	}
	return false;
}

int64_t AssemblerCM1800::hasLabel(wstring& str, int64_t size)
{
	if (str.length() == 0) return 0;
	for (int64_t k = 0; k < size; ++k) {
		if (str.compare(labels[k].text) == 0) return k;
	}
	return EMT;
}

void AssemblerCM1800::checkNumFormatWithSetErr(wstring& str, bool& hadErrorCode) {
	if (!hasNumFormat(str)) {
		wstring message;
		message =
		string_format(L"Ошибка ввода: Неверный формат числа: Код(стр. %lld): %ls", 
			strCounter, str.c_str());

		setError(message, hadErrorCode);
		return;
	}
}

void AssemblerCM1800::checkOperandFormatWithSetErr(wstring& str, bool& hadErrorCode) {
	if (!hasOperandFormat(str)) {
		wstring message;
		message =
			string_format(L"Ошибка ввода: Неверный оператор: Код(стр. %lld): %ls",
				strCounter, str.c_str());

		setError(message, hadErrorCode);
	}
}

void AssemblerCM1800::checkMnemonicWithSetErr(wstring& str, bool& hadErrorCode) {
	if (!hasMnemonic(str)) {
		wstring message;
		message =
			string_format(L"Ошибка ввода: Неизвестная инструкция: Код(стр. %lld): %ls",
				strCounter, str.c_str());

		setError(message, hadErrorCode);
	}
}

int AssemblerCM1800::hadCorrectFormat(wstring& str, int64_t size) {
	if (hasOperandFormat(str)) return OP;
	if (hasMnemonic(str)) return MNE;
	if (hasNumFormat(str)) return NUM;
	if (hasLabel(str, size) != EMT) return LAB;
	return ERR;
}

int AssemblerCM1800::assemble(wstring& mCode) {

	int64_t length = asmCode.length();
	if (length < INSTR_MIN_LGTH) return EMT;
	
	errorStr.clear();
	result.clear();

	const int RLT_SIZE = INSTR_QUANTITY / 2;
	int rltIter = 0, rltSizeCoef = 1;
	result = vector<SetB>(RLT_SIZE * rltSizeCoef);

	wstring clearedAsmCode, bufS1, bufS2, bufMsg;
	bool hadErrorCode = false;
	hadErrWarning = false;
	
	bool hasComment = false, hadOBody = false;
	// Отсеиваем из ассемблерного кода комментарии и приводим все разделители к одному типу.
	for (int64_t i = 0; i < length; ++i) {
		switch (asmCode[i])
		{
		case L'\n':
			hasComment = false;
			clearedAsmCode += asmCode[i];
			++strCounter;
			break;
		case L'\t':
			if(!hasComment) clearedAsmCode += L' ';
			break;
		case L';':
			hasComment = true;
			break;
		case L'{':
			if (!hasComment) {
				hadOBody = true;
				clearedAsmCode += asmCode[i];
			}
			break;
		case L'}':
			if (!hasComment) {
				clearedAsmCode += asmCode[i];
				if (!hadOBody) {
					bufMsg =
						string_format(L"Ошибка ввода: отсутствует открывающая скобка: Код(стр. %lld): %lc",
							strCounter, L'}');

					setError(bufMsg, hadErrorCode);
				}
				hadOBody = false;
			}
			break;
		default:
			if (!hasComment) clearedAsmCode += asmCode[i];
			break;
		}
	}
	length = clearedAsmCode.length();
	
	wstring command;
	
	bool firstToken = false, secondToken = false;
	bool hadNewLine = false, hadBeginAddr = false;
	bool isAddrAtBegin = true, didnotFind;
	
	int64_t i = 0, len = 0, k, bInt;
	hadOBody = false;
	strCounter = 1;

	const int LABELS_SIZE = 16;
	int labelsIter = 0, labelsIter2 = 0, labelsSizeCoef = 1;
	labels = vector<Label>(LABELS_SIZE * labelsSizeCoef);

	// Анализ текста на метки. Определение корректности. Сохранение меток.
	while (i + len <= length) {
		switch (clearedAsmCode[i + len])
		{
			case L':': {
				if (len == 0) {
					bufMsg =
						string_format(L"Ошибка ввода: Пустая метка или текст метки не оканчивается \':\' символом: Код(стр. %lld): %ls",
							strCounter, clearedAsmCode.substr(i, len + 1).c_str());
					setError(bufMsg, hadErrorCode);
					++i;
					break;
				}
				bufS1 = clearedAsmCode.substr(i, len);

				if (hasOperandFormat(bufS1)) {
					bufMsg =
						string_format(L"Ошибка ввода: Текст метки не должен совпадать с оператором: Код(стр. %lld): %ls",
							strCounter, clearedAsmCode.substr(i, len + 1).c_str());
					setError(bufMsg, hadErrorCode);
					i += len + 1;
					len = 0;
					break;
				}

				if (hasMnemonic(bufS1)) {
					bufMsg =
						string_format(L"Ошибка ввода: Текст метки не должен совпадать с мнемоникой: Код(стр. %lld): %ls",
							strCounter, clearedAsmCode.substr(i, len + 1).c_str());
					setError(bufMsg, hadErrorCode);
					i += len + 1;
					len = 0;
					break;
				}

				if (hasNumFormat(bufS1)) {
					bufMsg =
						string_format(L"Ошибка ввода: Текст метки не должен представлять число: Код(стр. %lld): %ls",
							strCounter, clearedAsmCode.substr(i, len + 1).c_str());
					setError(bufMsg, hadErrorCode);
					i += len + 1;
					len = 0;
					break;
				}
				
				if (!hadErrorCode) {
					if (labelsIter == LABELS_SIZE * labelsSizeCoef) {
						labels.resize(LABELS_SIZE * ++labelsSizeCoef);
					}
					labels[labelsIter++].text = bufS1;
				}

				i += len + 1;
				len = 0;
				break;
			}
			case L'\n':
				++strCounter;
			case L' ':
			case L'{':
			case L'}': {
				i += len + 1;
				len = 0;
				break;
			}
			default: {
				++len;
				break;
			}
		}
	}

	// Анализ потенциальных инструкций на совпадение c мнемониками
	// Построение полного формата инструкции
	// Определение ошибок
	// Анализ начального адреса
	i = 0; len = 0;
	strCounter = 1;
	int64_t labelAddressesQnt = 0;
	bool hadLabelAddr = false;

	while (i + len <= length) {
		switch (clearedAsmCode[i + len])
		{
			case L'{':
			case L'}': {
				if (len != 0) {
					bufMsg =
						string_format(L"Ошибка ввода: Операторы блока должны быть отделены от остального текста: Код(стр. %lld): %ls",
							strCounter, clearedAsmCode.substr(i, len + 1).c_str());
					setError(bufMsg, hadErrorCode);
					i += len + 1;
					len = 0;
					break;
				}
				++i;
				break;
			}
			case L':': {
				
				bufS1 = clearedAsmCode.substr(i, len);
				if (firstToken) {
					bufMsg =
						string_format(L"Ошибка последовательности: Метка должна быть перед инструкцией: Код(стр. %lld): %ls",
							strCounter, clearedAsmCode.substr(i, len + 1).c_str());
					setError(bufMsg, hadErrorCode);
					i += len + 1;
					len = 0;
					break;
				}

				if(!hadErrorCode) labels[labelsIter2++].value = rltIter;
				
				i += len + 1;
				len = 0;
				break;
			}
			case L'&': {
				if (len != 0) {
					bufMsg =
					string_format(L"Ошибка ввода: Установка начального адреса должна быть на отдельной строке: Код(стр. %lld): %ls", 
						strCounter, clearedAsmCode.substr(i, len + 1).c_str());
					setError(bufMsg, hadErrorCode);

					i += len + 1;
					len = 0;
					break;
				}
				hadNewLine = false;

				if (hadBeginAddr) {
					bufMsg =
					string_format(L"Ошибка адресации: Установка начального адреса возможна только один раз: Код(стр. %lld): %lc",
					strCounter, clearedAsmCode[i]);

					setError(bufMsg, hadErrorCode);
					++i;
					break;
				}
				hadBeginAddr = true;

				if (!isAddrAtBegin) {
					bufMsg =
					string_format(L"Ошибка последовательности: Установка начального адреса возможна только в начале программы: Код(стр. %lld): %lc",
					strCounter, clearedAsmCode[i]);
					
					setError(bufMsg, hadErrorCode);
				}
				isAddrAtBegin = false;

				if (i + 1 + 2 * (int64_t)MAX_ADDR_LENGTH <= length) {
					len = clearedAsmCode.substr(i + 1, 2 * MAX_ADDR_LENGTH).length();
					for (k = 1; k < 2 * (int64_t)MAX_ADDR_LENGTH; ++k) {
						bufS1 = clearedAsmCode.substr(i + 1, 2 * (int64_t)MAX_ADDR_LENGTH - k);
						if (hasNumFormat(bufS1)) {
							len = bufS1.length();
							break;
						}
					}
				}
				
				if (!hadErrorCode) startAddress = wcstoll(bufS1.c_str(), nullptr, 16);

				i += len + 1;
				len = 0;

				break;
			}
			case L'\n': {

				if (firstToken) {
					bufS1 = clearedAsmCode.substr(i, len);
					switch (hadCorrectFormat(bufS1, labelsIter))
					{
						case OP:
							if (!hadErrorCode && len != 0)
								command += bufS1;
							break;
						case NUM:
							if (!hadErrorCode && len != 0)
								result[rltIter].address += bufS1;
							break;
						case LAB:
							if (!hadErrorCode && len != 0) {
								result[rltIter].address = bufS1;
								hadLabelAddr = true;
							}
							break;
						default:
							bufMsg =
								string_format(L"Ошибка ввода: текст не является операндом или числом: Код(стр. %lld): %ls",
									strCounter, bufS1.c_str());
							setError(bufMsg, hadErrorCode);
							break;
					}
					
					if (!hadErrorCode) {
						if (hadLabelAddr) {
							++labelAddressesQnt;
							hadLabelAddr = false;
						}

						didnotFind = true;
						k = 0;
						do {
							if (command.compare(asmTable[k]) == 0) {
								result[rltIter].index = k;
								result[rltIter++].command = command;
								didnotFind = false;
								break;
							}
							if (k == (int64_t)INSTR_QUANTITY - 1 && didnotFind) {
								command = command.substr(0, command.length() - 1);
								k = -1;
							}
							++k;
						} while (didnotFind);
					}

					command.clear();
					firstToken = false;
					secondToken = false;
					hadNewLine = true;
					++strCounter;
					i += len + 1;
					len = 0;
					break;
				}

				++strCounter;
				hadNewLine = true;
			}
			case L' ': {
				
				if (len == 0) {
					++i;
					break;
				}

				isAddrAtBegin = false;
				if (!firstToken) {

					if (hadNewLine) --strCounter;
					bufS1 = clearedAsmCode.substr(i, len);
					if (hasWcsDifProp(bufS1)) {
						bufMsg =
						string_format(L"Ошибка ввода: Неизвестная инструкция: Код(стр. %lld): %ls", 
						strCounter, bufS1.c_str());

						setError(bufMsg, hadErrorCode);

						i += len + 1;
						len = 0;

						break;
					}
					
					bufS2 = str_toupper(bufS1);
					
					if (hasMnemonic(bufS1)) command += bufS1 + L' ';
					else if(hasMnemonic(bufS2)) command += bufS2 + L' ';
					else {
						bufMsg =
							string_format(L"Ошибка ввода: Неизвестная инструкция: Код(стр. %lld): %ls",
								strCounter, bufS1.c_str());

						setError(bufMsg, hadErrorCode);
					}

					if (!hadErrorCode) {
						if (rltIter == RLT_SIZE * rltSizeCoef) {
							result.resize(RLT_SIZE * ++rltSizeCoef);
						}
						if (hadNewLine) {
							for (k = 0; k < INSTR_QUANTITY; ++k) {
								if (bufS2.compare(asmTable[k]) == 0) {
									result[rltIter].command = bufS2;
									result[rltIter++].index = k;
									break;
								}
							}
						}
					}

					firstToken = true;

					if (hadNewLine) {
						command.clear();
						firstToken = false;
						secondToken = false;
						++strCounter;
					}
				}
				else {
					bufS1 = clearedAsmCode.substr(i, len);
					switch (hadCorrectFormat(bufS1, labelsIter))
					{
						case OP:
							if (!hadErrorCode) command += bufS1;
							break;
						case NUM:
							if (!hadErrorCode) result[rltIter].address += bufS1;
							break;
						case LAB:
							if (!hadErrorCode) {
								result[rltIter].address = bufS1;
								hadLabelAddr = true;
							}
							break;
						default:
							bufMsg =
								string_format(L"Ошибка ввода: текст не является операндом или числом: Код(стр. %lld): %ls",
									strCounter, bufS1.c_str());
							setError(bufMsg, hadErrorCode);
							break;
					}
					secondToken = true;
				}

				hadNewLine = false;
				i += len + 1;
				len = 0;
				break;
			}
			case L',': {
				hadNewLine = false;
				if (firstToken) {
					if (len == 0) {
						bufMsg =
						string_format(L"Ошибка ввода: Перед запятой запрещены разделители: Код(стр. %lld): %lc", 
							strCounter, L',');

						setError(bufMsg, hadErrorCode);
						++i;
						break;
					}
					bufS1 = clearedAsmCode.substr(i, len);
					checkOperandFormatWithSetErr(bufS1, hadErrorCode);
					if (!hadErrorCode) {
						command += bufS1 + L',';
					}
					secondToken = true;
				}
				i += len + 1;
				len = 0;
				break;
			}
			default: {
				hadNewLine = false;
				++len;
				break;
			}
		}
	}
	
	if (hadErrorCode) {
		mCode = errorStr;
		return 1;
	}

	int64_t bInt2;
	vector<int64_t> labelCounters(labelsIter);

	for (i = 0; i < rltIter; ++i) {

		for (k = 0; k < labelsIter; ++k) {

			if (result[i].address.length() != 0) {

				if (k == 0) {
					bInt = hasLabel(result[i].address, labelsIter);

					if (bInt != EMT) {
						bInt2 = 2;
					}
					else if (k == 0) {
						bInt2 = result[i].address.length() / 2;
					}
				}
				
				if (i < labels[k].value) {
					labelCounters[k] += bInt2;
				}
			}
		}
	}

	const int BYTES_IN_LINE = 16;
	wstring machineText;
	int64_t addressBytesQuantity;

	for (i = 0, k = 0; i < rltIter; ++i) {

		machineText = machineText + L' ' + machineCodes[result[i].index];

		bInt = hasLabel(result[i].address, labelsIter);
		len = result[i].address.length();

		if (len != 0 && bInt != EMT) {
			addressBytesQuantity = startAddress + labelCounters[bInt];
			result[i].address = string_format(L"%04llX", labels[bInt].value + addressBytesQuantity);
		}
		
		len = result[i].address.length();
		++k;

		if (k == BYTES_IN_LINE) {
			machineText += L'\n';
			k = 0;
		}

		if (len == 2) {
			machineText += L' ' + result[i].address;
			++k;
		}
		else if (len == 4) {
			machineText += L' ' + result[i].address.substr(2, 2);
			++k;

			if (k == BYTES_IN_LINE) {
				machineText += L'\n';
				k = 0;
			}

			machineText += L' ' + result[i].address.substr(0, 2);
			++k;
		}

		if (k == BYTES_IN_LINE) {
			machineText += L'\n';
			k = 0;
		}
	}

	mCode = machineText;
	return 0;
}
