// #include <fstream>
// #include <iostream>
// #include <locale>

// int main() {
//     // Thiết lập locale
//     std::locale::global(std::locale("en_US.UTF-8"));

//     // Mở file để đọc
//     std::wifstream file(L"unicode_file.txt");
//     if (!file.is_open()) {
//         std::wcout << L"Không thể mở file." << std::endl;
//         return 1;
//     }

//     // Đọc từ file
//     std::wstring line;
//     while (std::getline(file, line)) {
//         std::wcout << L"Đã đọc: " << line << std::endl;
//     }

//     // Đóng file
//     file.close();

//     return 0;
// // }
// #include <iostream>
// using namespace std;
// int main()
// {
//     const wchar_t* wide_string = L"Chào bạn, đjt mẹ mày!";
//     wcout << wide_string << std::endl;
//     return 0;
// }

// #include <iostream>
// #include <locale>
// #include <codecvt>
// #include <sstream>
// #include <fstream>
// #include <string>
// #include <cstring>
// #include <vector>
// using namespace std;

// int main() {
//     const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>);

//     wstring line;
//     wstring vect[4];
//     wifstream file("test1.txt");
//     file.imbue(utf8_locale);
//     getline(file, line);
//     wstringstream data(line);
//     wstring temp;
//     int i = 0;
//     while(getline(data,temp, L','))
//     {
//         vect[i++] = (temp);
//     }

//     file.close();

//     std::wfstream stream(L"test.txt");
//     stream.imbue(utf8_locale);
//     for (wstring i : vect)
//     stream<<i<<endl;
//     stream.close();
// }
/*
#include <iostream>
#include <locale>
#include <codecvt>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct SinhVien
{
	string _id;
	wstring _name;
	wstring _department;
	int _term;
	string _dob;
	string _avatar;
	wstring _description;
	wstring* _hobby;
	int Hobbies;

};
wstring removeWQuotes(wstring text)
{
	wstring output;
	for (wchar_t ch : text)
	{
		if (ch != L'\"')
			output += ch;
	}
	return output;
}
string removeQuotes(wstring text)
{
	string temp = string(text.begin(), text.end());
	string output;
	for (char ch : temp)
	{
		if (ch != '\"')
			output += ch;
	}
	return output;
}
wstring string_to_wstring(const std::string& str) {
    if (str.empty()) return std::wstring();
    std::size_t charsNeeded = std::mbstowcs(nullptr, str.c_str(), 0) + 1;  // Query size needed
    std::wstring wstrTo(charsNeeded, 0);
    std::mbstowcs(&wstrTo[0], str.c_str(), charsNeeded);
    return wstrTo;
}
int wstoi(const wstring& text) {
	string temp = string(text.begin(), text.end());
	int num = stoi(temp);
	return num;
}
void readFile(const string& filename);

void readFile(const string& filename)
{
    const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>);
	wifstream file(filename);
    file.imbue(utf8_locale);
    if (!file) {
        wcerr << L"[!] Cannot open file\n";
        return;
    }
	wstring line;
    while (getline(file, line))
    {
        SinhVien sv;
        wstringstream builder(line);
        wstring temp;
        int hobbiesCount = 0;

        // Đếm số lượng phần tử
        while (getline(builder, temp, L',')) {
            hobbiesCount++;
        }

        // Reset stream
        builder.clear();
        builder.str(line);

        sv.Hobbies = max(0, hobbiesCount - 7);

        if (getline(builder, temp, L',')) sv._id = removeQuotes(temp);
        if (getline(builder, temp, L',')) sv._name = removeWQuotes(temp);
        if (getline(builder, temp, L',')) sv._department = removeWQuotes(temp);
        if (getline(builder, temp, L',')) sv._term = wstoi(removeWQuotes(temp));
        if (getline(builder, temp, L',')) sv._dob = removeQuotes(temp);
        if (getline(builder, temp, L',')) sv._avatar = removeQuotes(temp);
        if (getline(builder, temp, L',')) sv._description = removeWQuotes(temp);

        if (sv.Hobbies > 0)
        {
            sv._hobby = new wstring[sv.Hobbies];
            int i = 0;
            while (getline(builder, temp, L',') && i < sv.Hobbies)
            {
                sv._hobby[i++] = removeWQuotes(temp);
            }
        }
	}
	file.close();
}
void writeFile(const string& filename, const SinhVien& sv) {

    const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>);
    wofstream file(filename);
    file.imbue(utf8_locale);
    if (!file) {
        std::wcerr << L"[!] Cannot open file\n";
        return;
    }

    // Ghi thông tin cơ bản của sinh viên
    file << L"ID: " << string_to_wstring(sv._id) << std::endl;
    file << L"Name: " << sv._name << std::endl;
    file << L"Department: " << sv._department << std::endl;
    file << L"Term: " << sv._term << std::endl;
    file << L"Date of Birth: " << string_to_wstring(sv._dob) << std::endl;
    file << L"Avatar: " << string_to_wstring(sv._avatar) << std::endl;
    file << L"Description: " << sv._description << std::endl;

    // Ghi thông tin sở thích
    if (sv.Hobbies > 0 && sv._hobby) {
        file << L"Hobbies: ";
        for (int i = 0; i < sv.Hobbies; i++) {
            if (i > 0) {
                file << L", ";  // Để thêm dấu phẩy giữa các sở thích
            }
            file << sv._hobby[i];
        }
        file << std::endl;
    }

    file.close();
}
*/

#include <iostream>
#include <locale>
#include <codecvt>
#include <cstring>
#include <cwchar>
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

/*wchar_t* takeContent(wchar_t buffer[])
{
    wchar_t ch;
    int charCount = 0;
    bool inQuotes = false;

    // Đọc đến khi gặp dấu nháy kép đầu tiên
    for (int i = 0;i<buffer)
    {
        if (ch == L'\"')
        {
            inQuotes = true;
            break;
        }
    }

    // Đếm số ký tự cho đến dấu nháy kép tiếp theo
    long start = ftell(file);  // Lưu vị trí hiện tại của con trỏ file
    while ((ch = fgetwc(file)) != WEOF && inQuotes)
    {
        if (ch == L'\"')
        {
            inQuotes = false;  // Kết thúc chuỗi trong dấu nháy
            break;
        }
        charCount++;
    }

    // Cấp phát bộ nhớ cho data
    wchar_t* data = new wchar_t[charCount + 1];  // +1 cho ký tự kết thúc chuỗi
    // Kiểm tra lỗi cấp phát bộ nhớ
    if (!data)
    {
        cerr << "[!] Alocating memory error\n";
        return NULL;
    }

    // Quay lại vị trí bắt đầu của chuỗi và đọc lại
    fseek(file, start, SEEK_SET);
    for (int i = 0; i < charCount; i++)
    {
        data[i] = fgetwc(file);
    }
    data[charCount] = L'\0';  // Kết thúc chuỗi

    // Bỏ qua dấu nháy kép đóng và dấu phẩy tiếp theo nếu có
    fgetwc(file);  // Bỏ qua dấu nháy kép đóng
    if ((ch = fgetwc(file)) != L',' && ch != WEOF)
    {
        ungetc(ch, file);  // Nếu ký tự tiếp theo không phải dấu phẩy, trả lại vào luồng
    }

    return data;
}*/

void removeWQuotes(wchar_t*& text)
{
    int len = wcslen(text);
    int count = 0;

    // Đầu tiên, đếm số ký tự không phải dấu nháy kép
    for (int i = 0; i < len; ++i) {
        if (text[i] != L'\"') {
            count++;
        }
    }
    wchar_t* temp = new wchar_t[count + 1];  // +1 cho ký tự null
    int index = 0;
    for (int i = 0; i < len; ++i) {
        if (text[i] != L'\"') {
            temp[index++] = text[i];
        }
    }
    temp[index] = L'\0';  // Đảm bảo chuỗi kết thúc đúng cách

    delete[] text; 
    text = temp; 
}

wchar_t* takeContent(wchar_t*& buffer) {
    // Tìm dấu nháy kép đầu tiên để bắt đầu trường dữ liệu
    wchar_t* start = wcschr(buffer, L'\"');
    if (!start) return nullptr; // Nếu không tìm thấy dấu nháy kép, trả về nullptr
    start++; // Bỏ qua dấu nháy kép mở

    // Tìm dấu nháy kép tiếp theo để kết thúc trường dữ liệu
    wchar_t* end = wcschr(start, L'\"');
    if (!end) return nullptr; // Nếu không tìm thấy dấu nháy kép, trả về nullptr

    // Tính độ dài của trường dữ liệu
    int field_len = end - start;

    // Cấp phát bộ nhớ cho dữ liệu và sao chép nội dung từ start đến end
    wchar_t* data = new wchar_t[field_len + 1];
    wcsncpy(data, start, field_len);
    data[field_len] = L'\0'; // Đảm bảo chuỗi kết thúc đúng

    // Cập nhật buffer để bỏ qua phần đã xử lý
    buffer = end + 1;
    if (*buffer == L',') buffer++; // Bỏ qua dấu phẩy nếu có ngay sau dấu nháy kép đóng

    return data;
}


int countFields(const wchar_t* line)
{
    bool inQuotes = false;
    int fieldCount = 0;
    wchar_t ch;
    int i = 0;

    while (line[i] != L'\0') {
        ch = line[i];
        switch (ch) {
        case L'\"':
            inQuotes = !inQuotes;
            break;
        case L',':
            if (!inQuotes) {
                ++fieldCount;
            }
            break;
        default:
            break;
        }
        i++;
    }

    return fieldCount + 1;
}


/*
void readFile(const char filename[], SinhVien& sv)
{
    setlocale(LC_ALL, "vi_VN.utf8");
    FILE* file = fopen(filename, "r, ccs=UTF-8");
    if (!file) {
        std::cout << "[!] Cannot open file\n";
        return;
    }

    wchar_t buffer[1024];
    fgetws(buffer, 1024, file);

    wchar_t* buffer_str = buffer;
    sv._id = takeContent(buffer_str);
    sv._name = takeContent(buffer_str);
    sv._department = takeContent(buffer_str);
    sv._term = wcstol(takeContent(buffer_str), NULL, 10);
    sv._dob = takeContent(buffer_str);
    sv._avatar = takeContent(buffer_str);
    sv._description = takeContent(buffer_str);

    int hobbyCount = countFields(buffer) - 7;
    sv._hobby = new wchar_t* [hobbyCount];
    sv.Hobbies = hobbyCount;
    for (int i = 0; i < hobbyCount; ++i) 
    {
        sv._hobby[i] = takeContent(buffer_str);
    }
    buffer_str = nullptr;
    cout << "Read successfull\n";
    fclose(file);
}
*/

void readFile(const char filename[], SinhVien*& sv, int& numStudents)
{
    setlocale(LC_ALL, "vi_VN.utf8");
    FILE* file = fopen(filename, "r, ccs=UTF-8");
    if (!file) {
        cout << "[!] Cannot open file\n";
        return;
    }

    wchar_t buffer[1024];
    int index = 0;
    while (fgetws(buffer, 1024, file) && index < numStudents)
    {        
        wchar_t* buffer_str = buffer;
        sv[index]._id = takeContent(buffer_str);
        sv[index]._name = takeContent(buffer_str);
        sv[index]._department = takeContent(buffer_str);
        sv[index]._term = wcstol(takeContent(buffer_str), NULL, 10);
        sv[index]._dob = takeContent(buffer_str);
        sv[index]._avatar = takeContent(buffer_str);
        sv[index]._description = takeContent(buffer_str);

        int hobbyCount = countFields(buffer) - 7;
        if (hobbyCount==0)
        {
            sv[index]._hobby = new wchar_t* [hobbyCount];
            sv[index].Hobbies = hobbyCount;
            for (int i = 0; i < hobbyCount; ++i) {
                sv[index]._hobby[i] = L"Không có sở thích";
            }        
        }
        sv[index]._hobby = new wchar_t* [hobbyCount];
        sv[index].Hobbies = hobbyCount;
        for (int i = 0; i < hobbyCount; ++i) {
            sv[index]._hobby[i] = takeContent(buffer_str);
        }
        buffer_str = nullptr;
        index++;
    }
    cout<<"Read successfull\n";
    fclose(file);
}

void writeFile(const char filename[], const SinhVien& sv)
{
    setlocale(LC_ALL, "vi_VN.utf8");
    FILE* file = fopen(filename, "a, ccs=UTF-8");
    if (!file) {
        cout << "[!] Cannot open file\n";
        return;  // Nếu không mở được file, thì thoát khỏi hàm
    }

    // Ghi thông tin cơ bản của sinh viên
    fwprintf(file, L"ID: %ls\n", sv._id);
    fwprintf(file, L"Name: %ls\n", sv._name);
    fwprintf(file, L"Department: %ls\n", sv._department);
    fwprintf(file, L"Term: %d\n", sv._term);
    fwprintf(file, L"Date of Birth: %ls\n", sv._dob);
    fwprintf(file, L"Avatar: %ls\n", sv._avatar);
    fwprintf(file, L"Description: %ls\n", sv._description);

    // Ghi thông tin sở thích
    if (sv.Hobbies > 0 && sv._hobby)
    {
        for (int i = 0; i < sv.Hobbies; i++)
        {
            if (i > 0)
            {
                fwprintf(file, L"\n");  // Thêm xuống dòng giữa các sở thích
            }
            fwprintf(file, L"Hobbies: %ls", sv._hobby[i]);
        }
        fwprintf(file, L"\n");  // Thêm xuống dòng cuối cùng
    }

    fclose(file);  // Đóng file sau khi ghi xong
}
int takeNumber(const char filename[])
{
    FILE* file = fopen(filename,"r");
    int count = 0;
    wchar_t buffer[1024];
    while(fgetws(buffer, 1024, file))
    {
        count++;
    }
    fclose(file);
    return count;
}

wchar_t* readFileIntoBuffer(const char filename[]) {
    setlocale(LC_ALL, "");

    FILE* file = fopen(filename, "r, ccs=UTF-8");
    if (!file) {
        wprintf(L"Failed to open file\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    wchar_t* buffer = new wchar_t[fsize + 1];
    if (buffer) {
        fread(buffer, sizeof(wchar_t), fsize, file);
        buffer[fsize] = L'\0';
    }

    fclose(file);
    return buffer;
}

wchar_t* replaceContent(const wchar_t* source, const wchar_t* search, const wchar_t* replace) {
    int len_search = wcslen(search);
    int len_replace = wcslen(replace);

    // Tính tổng số lần xuất hiện của chuỗi tìm kiếm
    const wchar_t* ins = source;
    wchar_t* tmp;
    int count = 0;
    while ((tmp = wcsstr(ins, search)) != NULL) {
        count++;
        ins = tmp + len_search;
    }

    // Cấp phát bộ nhớ cho kết quả
    wchar_t* result = new wchar_t[wcslen(source) + (len_replace - len_search) * count + 1];
    if (!result) return NULL;  // Trường hợp cấp phát thất bại

    wchar_t* ptr = result;
    ins = source;
    while ((tmp = wcsstr(ins, search)) != NULL) {
        int len = tmp - ins;  // Độ dài của phần trước chuỗi tìm kiếm
        wcsncpy(ptr, ins, len);  // Sao chép phần này vào kết quả
        ptr += len;
        wcsncpy(ptr, replace, len_replace);  // Sao chép chuỗi thay thế vào kết quả
        ptr += len_replace;
        ins = tmp + len_search;  // Tiếp tục sau chuỗi tìm kiếm
    }
    wcscpy(ptr, ins);  // Sao chép phần còn lại của chuỗi nguồn vào kết quả

    return result;
}



wchar_t* hobbiesList(wchar_t** hobby, int hobbies) 
{
    int count = 0;
    // Tính toán kích thước cần thiết cho chuỗi kết quả
    for (int i = 0; i < hobbies; i++) 
    {
        count += wcslen(hobby[i]) + wcslen(L"<li></li>\n");
    }

    // Cấp phát bộ nhớ cho chuỗi kết quả
    wchar_t* result = new wchar_t[count + 1];
    result[0] = L'\0';  // Khởi tạo chuỗi rỗng

    // Ghép nối mỗi sở thích vào chuỗi kết quả
    for (int i = 0; i < hobbies; i++) 
    {
        wcscat(result, L"<li>");
        wcscat(result, hobby[i]);
        wcscat(result, L"</li>\n");
    }

    return result;
}

void replaceDetail(SinhVien sv, wchar_t*& buffer)
{
    buffer = replaceContent(buffer,L"ID", sv._id);
    buffer = replaceContent(buffer,L"NAME", sv._name);
    buffer = replaceContent(buffer,L"Personal_Image", sv._avatar);
    buffer = replaceContent(buffer,L"Faculty", sv._department);
    buffer = replaceContent(buffer,L"Birthday", sv._dob);
    buffer = replaceContent(buffer,L"Description", sv._description);

    if (sv.Hobbies > 0)
    {
        buffer = replaceContent(buffer,L"<li>Hobby</li>", hobbiesList(sv._hobby, sv.Hobbies));     
    }
}

void writeFileFromBuffer(wchar_t* filename, const wchar_t* content) 
{
    setlocale(LC_ALL, "");
    FILE* file = _wfopen(filename, L"w+, ccs=UTF-8");
    if (!file) {
        wprintf(L"Failed to open file\n");
        return;
    }

    fwprintf(file, L"%ls", content);
    fclose(file);
}

wchar_t* generateFilename(const SinhVien& sv)
 {
    const wchar_t* directory = L"D:\\HCMUS\\KTLT-K23\\DoAnGiuaKy\\22120299\\Website\\";
    size_t idLength = wcslen(sv._id);
    size_t directoryLength = wcslen(directory);
    size_t extensionLength = wcslen(L".html");
    size_t totalLength = directoryLength + idLength + extensionLength + 1; // +1 for null terminator

    wchar_t* filename = new wchar_t[totalLength];
    if (!filename) {
        std::wcerr << L"Memory allocation failed.\n";
        return nullptr;
    }

    // Start by copying the directory path
    wcscpy(filename, directory);
    // Append the ID
    wcscat(filename, sv._id);
    // Append the ".html" extension
    wcscat(filename, L".html");

    std::wcout << L"Generated filename: " << filename << std::endl;

    return filename;
}

int main()
{
    int nos = takeNumber("test.txt");
    SinhVien* sv = new SinhVien[nos];
    //SinhVien sv;
    
    readFile("test.txt",sv, nos);
    // wchar_t* filename = generateFilename(sv);
    // replaceDetail(sv,buffer);
    // writeFileFromBuffer(filename,buffer);
    
    for(int i = 0;i<nos;i++)
    {
        wchar_t* buffer = readFileIntoBuffer("template.html");
        wchar_t* filename = generateFilename(sv[i]);
        replaceDetail(sv[i],buffer);
        writeFileFromBuffer(filename,buffer);
        writeFile("output.txt",sv[i]);
    }
}