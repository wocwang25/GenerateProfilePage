#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <codecvt> // Thêm thư viện này để sử dụng codecvt_utf8
#include <locale>  // Được yêu cầu cho locale

using namespace std;
wstring htmlContent;

void replaceContent(const wstring& keyword, const wstring replaceWord)
{
    size_t startPos;
    while ((startPos = htmlContent.find(keyword)) != wstring::npos) 
    {
        htmlContent.replace(startPos, keyword.length(), replaceWord);
    }
}

void readHtml(const string& filename)
{
    wifstream htmlFile("template.html");

    // Cài đặt locale cho đọc UTF-8
    htmlFile.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));
    // Đọc nội dung file
    if (!htmlFile)
     {

        wcerr << "[!] Cannot open file\n" << endl;
        return;
    }

    wstringstream buffer;
    buffer << htmlFile.rdbuf();
    htmlContent = buffer.str();

    // Thay thế các chỉ mục cố định
        replaceContent(L"NAME",L"Võ Quốc Quang");
        replaceContent(L"ID",L"22120299");
        replaceContent(L"Hobby",L"Thích yêu em");
        replaceContent(L"Faculty",L"Công nghệ thông tin");
        replaceContent(L"Birthday",L"07/05/2004");
        replaceContent(L"Description",L"Tôi đẹp trai");


    htmlFile.close();
    // Ghi nội dung đã thay thế vào một file mới
    wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    wstring id = L"22120299";
    wstring scr = L".html";
    string fileout = converter.to_bytes(id+scr);
    wofstream outFile(fileout);
    // Cài đặt locale cho ghi UTF-8
    outFile.imbue(locale(locale::classic(), new codecvt_utf8<wchar_t>));

    if (outFile) 
    {
        outFile << htmlContent;
    } else 
    {
        wcerr << "Không thể ghi vào file." << endl;
        return;
    }
    outFile.close();
}
int main() {
    readHtml("template.html");

    return 0;
}
