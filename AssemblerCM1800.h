


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

using namespace std;


void setOldCP(UINT* oldCp);

template<typename ... Args>
wstring string_format(const wstring& format, Args ... args);

wstring to_wstring(const string& str);
string to_string(const wstring& str);

wstring to_wcopy(const wstring& str);
string to_copy(const string& str);

wstring str_toupper(wstring str);

bool hasWcsDifProp(wstring& wchStr);


class AssemblerCM1800
{
private:
	static const int32_t INSTR_QUANTITY		= 256;
	static const int32_t INSTR_MIN_LGTH		= 2;
	static const int32_t INSTR_MAX_LGTH		= 4;
	static const int32_t OPERATORS_QNTY		= 10;
	static const int32_t MAX_ADDR_LENGTH	= 4;

	struct SetA {
		int64_t index;
		wstring command;
	};

	struct SetB {
		int64_t index;
		wstring command;
		wstring address;
	};

	struct Label {
		int64_t value;
		wstring text;
	};

	// Содержимое двух массивов должно совпадать по индексам. Требуется строгое соотвествие.
	const wchar_t** asmTable;
	wchar_t** machineCodes;

	wstring asmCode;
	vector<SetA> mnemonics;
	vector<SetB> result;
	vector<wstring> operators;
	vector<Label> labels;
	wstring errorStr;
	int64_t strCounter = 1, startAddress = 0;
	bool hadErrWarning;


	bool hasNumFormat(wstring& str);
	bool hasOperandFormat(wstring& str);
	bool hasMnemonic(wstring& str);
	int64_t hasLabel(wstring& str, int64_t size);
	void checkNumFormatWithSetErr(wstring& str, bool& hadErrorCode);
	void checkOperandFormatWithSetErr(wstring& str, bool& hadErrorCode);
	void checkMnemonicWithSetErr(wstring& str, bool& hadErrorCode);
	int hadCorrectFormat(wstring& str, int64_t size);
	void setError(wstring formatMessage, bool& hadErrorCode);

public:
	static constexpr const char* BOM = "\xEF\xBB\xBF";

	enum retCodes {
		EMT = -1,
		ERR,
		NUM,
		LAB,
		OP,
		MNE
	};

	
	AssemblerCM1800();
	AssemblerCM1800(const wstring& text);
	~AssemblerCM1800();

	void clear();
	void setCode(const wstring& text, bool addMode);
	int64_t getStringsQuantity();
	int assemble(wstring& mCode);
};
