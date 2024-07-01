


#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <fstream>
#include <cwctype>
#include <cwchar>

#include "AssemblerCM1800.h"


int32_t main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	UINT oldCodePage = GetConsoleOutputCP();
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	switch (argc)
	{
	case 1:
		/*string str;

		int32_t i = 0;
		while(getline(cin, str)) {
			wcout << str;
		}

		wcout << endl;
		SetConsoleOutputCP(oldCodePage);*/
		wcout << L"Version/Версия: 0.0.1\n"
			<< L"Программа переводит код на ассемблере в машинный для эвм СМ-1800\n"
			<< L"Для более подробной информации запустите с одним из параметров -h, -? или -help\n";
		setOldCP(&oldCodePage);
		return 1;
	case 2:

		if (!string("-h").compare(argv[1]) ||
			!string("-?").compare(argv[1]) ||
			!string("-help").compare(argv[1])) {

			wcout << L"Программа переводит код на ассемблере в машинный для эвм СМ-1800\n\nФормат команды\n"
				<< L"asmToBytes \"Полный путь\\Входной файл\" \"Полный путь\"\n";
			//<< "asmToBytes < \"Путь к входному файлу\"\n"
			//<< "asmToBytes < \"Путь к входному файлу\" > \"Путь к выходному тексту\"\n";

			setOldCP(&oldCodePage);

			return 0;
		}

		break;
	case 3:

		break;
	default:
		setOldCP(&oldCodePage);
		return 1;
	}

	const int32_t BUF_SIZE = 512;
	char* fullPath = new char[BUF_SIZE];

	if (!ExpandEnvironmentStringsA(argv[1], fullPath, BUF_SIZE)) {
		wcout << L"Неправильный формат пути файла: " << to_wstring(argv[1]) << endl;
		setOldCP(&oldCodePage);
		delete[] fullPath;
		return 1;
	}
	
	ifstream infile(fullPath, ios::in);
	if (!infile.is_open()) {
		wcout << L"Не удается открыть файл: " << to_wstring(fullPath) << endl;
		wcout << L"Программа поддерживает только английский язык в пути файла\n";
		setOldCP(&oldCodePage);
		delete[] fullPath;
		return 1;
	}

	string bStr1;

	// Проверка на кодировку UTF-8 с BOM
	const int8_t BOM_BUF_SIZE = 4;
	char* bomBytes = new char[BOM_BUF_SIZE];
	bomBytes[BOM_BUF_SIZE - 1] = '\0';
	infile.read(bomBytes, (int64_t)BOM_BUF_SIZE - 1);
	bStr1 = bomBytes;
	if (bStr1.compare(AssemblerCM1800::BOM) != 0) {
		wcout << L"Неправильная кодировка файла: " << to_wstring(fullPath);
		wcout << L"\nТребуется UTF-8 с BOM\n";
		delete[] fullPath;
		delete[] bomBytes;
		return 1;
	}
	delete[] bomBytes;

	AssemblerCM1800 asmler;
	bStr1 = "";

	while (infile.good()) {
		getline(infile, bStr1);
		bStr1 += '\n';
		asmler.setCode(to_wstring(bStr1), true);
	}

	if (!infile.eof()) {
		infile.close();
		setOldCP(&oldCodePage);
		return 1;
	}
	infile.close();

	wstring bStr2;
	bool errorCode = asmler.assemble(bStr2);
	
	if (errorCode != 0) {
		wcout << bStr2 << endl;
		delete[] fullPath;
		return 0;
	}

	char* sysVar = new char[BUF_SIZE];

	if (!GetEnvironmentVariableA("USERPROFILE", sysVar, BUF_SIZE)) {
		wcout << L"Ошибка считывания переменной USERPROFILE\n";
		setOldCP(&oldCodePage);
		delete[] sysVar;
		return 1;
	}

	ofstream outFile;

	if (argc == 2) {
		strcpy_s(fullPath, BUF_SIZE, (string() + sysVar + "\\Downloads\\mc_CM-1800.txt").c_str());
		outFile.open(fullPath, ios::out);
	}
	else {
		if (!ExpandEnvironmentStringsA(argv[2], fullPath, BUF_SIZE)) {
			wcout << L"Неправильный формат пути файла: " << to_wstring(argv[2]) << endl;
			setOldCP(&oldCodePage);
			delete[] fullPath;
			return 1;
		}
		outFile.open((string() + fullPath + "\\mc_CM-1800.txt").c_str(), ios::out);
	}

	if (!outFile.is_open()) {
		wcout << L"Не удается создать/открыть файл: " << fullPath << endl;
		wcout << L"Программа поддерживает только английский язык в пути файла\n";
		setOldCP(&oldCodePage);
		delete[] fullPath;
		return 1;
	}
	
	outFile << AssemblerCM1800::BOM << to_string(bStr2);
	
	outFile.close();
	delete[] sysVar;
	delete[] fullPath;
	
	setOldCP(&oldCodePage);

	return 0;
}
