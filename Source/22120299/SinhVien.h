#ifndef _SINHVIEN_H
#define _SINHVIEN_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale>
#include <codecvt>
#include <cwchar>
#include <stdio.h>
using namespace std;

struct SinhVien
{
    wchar_t* _id;
    wchar_t* _name;
    wchar_t* _department;
    int _term;
    wchar_t* _dob;
    wchar_t* _avatar;
    wchar_t* _description;
    wchar_t** _hobby;  // Mảng các chuỗi
    int Hobbies;
};

struct Options
{
    bool _id;
    bool _name;
    bool _department;
    bool _term;
    bool _dob;
    bool _description;
    bool _hobby; 
};

wchar_t* takeContent(wchar_t*& buffer);

int countFields(const wchar_t* line);

void readFile(const char filename[], SinhVien*& sv, int& numStudents);

void writeFile(const char filename[], const SinhVien& sv);

int takeNumber(const char filename[]);

wchar_t* readFileIntoBuffer(const char filename[]);

wchar_t* replaceContent(const wchar_t* source, const wchar_t* search, const wchar_t* replace);

wchar_t* hobbiesList(wchar_t** hobby, int hobbies);

void replaceDetail(SinhVien sv, wchar_t*& buffer, Options opt);

void writeFileFromBuffer(const wchar_t* filename, const wchar_t* content);

wchar_t* generateFilename(const SinhVien& sv);

void Option(Options& opt);

#endif // !_SINHVIEN_H
