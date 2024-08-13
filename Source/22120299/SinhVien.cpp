#include "SinhVien.h"


//void removeWQuotes(wchar_t*& text)
//{
//    size_t len = wcslen(text);
//    int count = 0;
//
//    // Đếm số ký tự không phải dấu nháy kép
//    for (int i = 0; i < len; ++i) {
//        if (text[i] != L'\"') {
//            count++;
//        }
//    }
//    wchar_t* temp = new wchar_t[count + 1];
//    int index = 0;
//    for (int i = 0; i < len; ++i) {
//        if (text[i] != L'\"') {
//            temp[index++] = text[i];
//        }
//    }
//    temp[index] = L'\0';
//
//    delete[] text;
//    text = temp;
//}

wchar_t* takeContent(wchar_t*& buffer) 
{
    // Tìm dấu nháy kép đầu tiên để bắt đầu trường dữ liệu
    wchar_t* start = wcschr(buffer, L'\"');
    if (!start) 
    {
        return nullptr;
    }
    start++; // Bỏ qua dấu nháy kép mở

    // Tìm dấu nháy kép tiếp theo để kết thúc trường dữ liệu
    wchar_t* end = wcschr(start, L'\"');
    if (!end) 
    {
        return nullptr; // Nếu không tìm thấy dấu nháy kép, trả về nullptr
    }

    // Tính độ dài của trường dữ liệu
    int field_len = end - start;

    // Lấy dữ liệu (không bao gồm dấu nháy ")
    wchar_t* data = new wchar_t[field_len + 1];
    wcsncpy(data, start, field_len);
    data[field_len] = L'\0';

    // Cập nhật buffer để bỏ qua trường dữ liệu đã lấy
    buffer = end + 1;

    // Bỏ qua dấu phẩy nếu có ngay sau dấu nháy kép đóng
    if (*buffer == L',') 
    {
        buffer++;
    }

    return data;
}


int countFields(const wchar_t* line)
{
    bool inQuotes = false;
    int fieldCount = 0;
    wchar_t ch;
    int i = 0;

    while (line[i] != L'\0') 
    {
        ch = line[i];
        switch (ch) 
        {
            //Nếu gặp dấu nháy thì thông báo đang ở trong trường dữ liệu, ngược lại thì kết thúc trường dữ liệu
            case L'\"':
                inQuotes = !inQuotes;
                break;
            //Đếm các trường dữ liệu có trong hàng (phân cách bằng dấu ,) nhưng cũng kiểm tra xem có đang ở trong trường dữ liệu nào không
            case L',':
                if (!inQuotes) 
                {
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
    //Khởi tạo locale để làm việc với unicode
    setlocale(LC_ALL, "vi_VN.utf8");
    FILE* file = fopen(filename, "r, ccs=UTF-8");
    if (!file)
    {
        cout << "[!] Error: Cannot open file\n";
        return;
    }

    //Biến buffer để lưu từng hàng dữ liệu trong file
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
        //Nếu sinh viên không có sở thích nào thì cài đặt mặc định
        if (hobbyCount < 1)
        {
            sv[index]._hobby = new wchar_t* [1];
            sv[index].Hobbies = 1;

            // Cấp phát và sao chép chuỗi "Không có sở thích"
            const wchar_t* noHobby = L"Không có sở thích";
            size_t len = wcslen(noHobby) + 1;
            sv[index]._hobby[0] = new wchar_t[len];
            wcscpy(sv[index]._hobby[0], noHobby);
        }
        //Nếu có sở thích thì lưu vào mảng _hobby
        else
        {
            sv[index]._hobby = new wchar_t* [hobbyCount];
            sv[index].Hobbies = hobbyCount;
            for (int i = 0; i < hobbyCount; ++i) {
                sv[index]._hobby[i] = takeContent(buffer_str);
            }
        }
        buffer_str = nullptr;
        index++;
    }
    fclose(file);
}

void writeFile(const char filename[], const SinhVien& sv)
{
    //Khởi tạo locale để làm việc với unicode
    setlocale(LC_ALL, "vi_VN.utf8");
    FILE* file = fopen(filename, "a+, ccs=UTF-8");
    if (!file) {
        cout << "[!] Error: Cannot open file\n";
        return;
    }

    // Ghi thông tin của sinh viên vào file
    fwprintf(file, L"ID: %ls\n", sv._id);
    fwprintf(file, L"Name: %ls\n", sv._name);
    fwprintf(file, L"Department: %ls\n", sv._department);
    fwprintf(file, L"Term: %d\n", sv._term);
    fwprintf(file, L"Date of Birth: %ls\n", sv._dob);
    fwprintf(file, L"Avatar: %ls\n", sv._avatar);
    fwprintf(file, L"Description: %ls\n", sv._description);

    // Trường thông tin sở thích không cố định nên cần xử lí riêng
    if (sv.Hobbies > 0 && sv._hobby)
    {
        for (int i = 0; i < sv.Hobbies; i++)
        {
            if (i > 0)
            {
                fwprintf(file, L"\n");
            }
            fwprintf(file, L"Hobbies: %ls", sv._hobby[i]);
        }
        fwprintf(file, L"\n");
    }

    fclose(file);
}

int takeNumber(const char filename[]) // Tìm kiếm số lượng sinh viên thông qua số dòng trong file
{
    //setlocale(LC_ALL, "vi_VN.utf8");
    FILE* file = fopen(filename, "r, ccs=UTF-8");
    int count = 0;
    wchar_t buffer[1024];
    while (fgetws(buffer, 1024, file))
    {
        count++;
    }
    fclose(file);
    return count;
}

//int takeNumber(const char filename[]) // Tìm kiếm số lượng sinh viên thông qua số dòng trong file
//{
//    //setlocale(LC_ALL, "vi_VN.utf8");
//    FILE* file = fopen(filename, "r");
//    int count = 0;
//    wchar_t buffer[1024];
//    while (fgetws(buffer, 1024, file))
//    {
//        count++;
//    }
//    fclose(file);
//    return count;
//}

wchar_t* readFileIntoBuffer(const char filename[]) 
{
    setlocale(LC_ALL, "vi_VN.utf8");

    FILE* file = fopen(filename, "r, ccs=UTF-8");
    if (!file) {
        wprintf(L"Failed to open file\n");
        return nullptr;
    }

    // Đặt vị trí bắt đầu của file
    //fseek(file, 0, SEEK_SET);

    // Khởi tạo buffer rỗng với kích thước 1 để chứa ký tự kết thúc chuỗi
    wchar_t* buffer = new wchar_t[1];
    buffer[0] = L'\0';

    // Đọc từng dòng trong file
    wchar_t line[256];
    while (fgetws(line, sizeof(line) / sizeof(wchar_t), file))
    {
        // Tính kích thước mới cần thiết
        size_t newLength = wcslen(buffer) + wcslen(line) + 1;

        // Cấp phát buffer mới với kích thước lớn hơn
        wchar_t* newBuffer = new wchar_t[newLength];

        // Sao chép dữ liệu cũ và thêm dòng mới vào
        wcscpy(newBuffer, buffer);
        wcscat(newBuffer, line);

        // Giải phóng buffer cũ và cập nhật con trỏ
        delete[] buffer;
        buffer = newBuffer;
    }

    fclose(file);
    return buffer;
}

wchar_t* replaceContent(wchar_t* buffer, const wchar_t* keyword, const wchar_t* infor)
{
    size_t len_search = wcslen(keyword);
    size_t len_replace = wcslen(infor);

    // Tính tổng số lần xuất hiện của chuỗi tìm kiếm
    wchar_t* ins = buffer;
    wchar_t* tmp = nullptr;
    int count = 0;
    while ((tmp = wcsstr(ins, keyword)) != NULL) {
        count++;
        ins = tmp + len_search;
    }

    // Cấp phát bộ nhớ cho kết quả sau khi thay thế keyword thành thông tin cụ thể - ví dụ: NAME -> Võ Quốc Quang
    wchar_t* result = new wchar_t[wcslen(buffer) + (len_replace - len_search) * count + 1];
    if (!result) 
    {
        return NULL; 
    }

    wchar_t* ptr = result;
    ins = buffer;
    while ((tmp = wcsstr(ins, keyword)) != NULL) 
    {
        int len = tmp - ins;  // Độ dài của phần trước chuỗi tìm kiếm
        wcsncpy(ptr, ins, len);  // Sao chép phần này vào kết quả

        ptr += len;
        wcsncpy(ptr, infor, len_replace);  // Sao chép chuỗi thay thế vào kết quả

        ptr += len_replace;
        ins = tmp + len_search;  // Tiếp tục sau chuỗi tìm kiếm
    }
    wcscpy(ptr, ins);  // Sao chép phần còn lại của chuỗi nguồn vào kết quả

    return result;
}

// Template có sẵn chỉ có dòng Hobby nên cần tạo ra 1 chuỗi bao gồm tất cả sở thích của sinh viên để thay thế
wchar_t* hobbiesList(wchar_t** hobby, int hobbies)
{
    size_t count = 0;
    // Tính toán kích thước cần thiết cho chuỗi kết quả
    for (int i = 0; i < hobbies; i++)
    {
        count += wcslen(hobby[i]) + wcslen(L"<li></li>\n");
    }

    // Cấp phát bộ nhớ cho chuỗi kết quả
    wchar_t* result = new wchar_t[count + 1];
    result[0] = L'\0';  // Khởi tạo chuỗi rỗng

    // Nối mỗi sở thích vào chuỗi kết quả
    for (int i = 0; i < hobbies; i++)
    {
        wcscat(result, L"<li>");
        wcscat(result, hobby[i]);
        wcscat(result, L"</li>\n");
    }

    return result;
}

//Thay thế thông tin cần thiết vào vị trí các keyword trong file html
void replaceDetail(SinhVien sv, wchar_t*& buffer, Options opt)
{
    if(opt._id)
    {
        buffer = replaceContent(buffer, L"ID", sv._id);
    }
    else
    {
        buffer = replaceContent(buffer, L"ID", L"NULL");
    }

    if (opt._name)
    {
        buffer = replaceContent(buffer, L"NAME",sv._name);
    }
    else
    {
        buffer = replaceContent(buffer, L"NAME", L"NULL");

    }

    buffer = replaceContent(buffer, L"Personal_Image", sv._avatar);

    if(opt._department)
    {
        buffer = replaceContent(buffer, L"Faculty", sv._department);
    }
    else 
        buffer = replaceContent(buffer, L"Faculty", L"NULL");

    if(opt._dob)
    {
        buffer = replaceContent(buffer, L"Birthday", sv._dob);
    }
    else
    {
        buffer = replaceContent(buffer, L"Birthday", L"NULL");
    }

    if (opt._description)
    {
        buffer = replaceContent(buffer, L"Description", sv._description);
    }
    else
    {
        buffer = replaceContent(buffer, L"Description", L"NULL");
    }

    if (sv.Hobbies > 0 && opt._hobby)
    {
        buffer = replaceContent(buffer, L"<li>Hobby</li>", hobbiesList(sv._hobby, sv.Hobbies));
    }
    else
    {
        buffer = replaceContent(buffer, L"<li>Hobby</li>", L"NULL");
    }
}

// Viết nội dung đã được chỉnh sửa (thêm vào thông tin sinh viên cụ thể) vào file
void writeFileFromBuffer(const wchar_t* filename, const wchar_t* content)
{
    setlocale(LC_ALL, "vi_VN.utf8");
    FILE* file = _wfopen(filename, L"w+, ccs=UTF-8");
    if (!file) {
        wprintf(L"Failed to open file\n");
        return;
    }

    fwprintf(file, L"%ls", content);
    fclose(file);
}

// Khởi tạo tên file kèm đường dẫn cụ thể với id của sinh viên để phân biệt
wchar_t* generateFilename(const SinhVien& sv)
{
    const wchar_t directory[] = L"Website\\";
    size_t idLength = wcslen(sv._id);
    size_t directoryLength = wcslen(directory);
    size_t extensionLength = wcslen(L".html");
    size_t totalLength = directoryLength + idLength + extensionLength + 1;

    wchar_t* filename = new wchar_t[totalLength];
    if (!filename)
    {
        cout << "[!] Error: Memory allocation failed\n";
        return nullptr;
    }

    // Copy đường dẫn vào tên file
    wcscpy(filename, directory);
    
    // Nối id của sinh viên vào
    wcscat(filename, sv._id);

    // Nối đuôi .hmtl để tạo định dạng cho file là html
    wcscat(filename, L".html");

    return filename;
}

void Option(Options& opt)
{
    char ch;
    cout << "\n\t\tPlease select the data field to be displayed: \n";
    cout<<"\n\t--ID-- (y/n)->:  ";
    cin >> ch;
    if (ch == 'n' || ch == 'N')
        opt._id = false;

    cout<<"\n\t--Name-- (y/n)->:  ";
    cin >> ch;
    if (ch == 'n' || ch == 'N')
        opt._name = false;

    cout<<"\n\t--Department-- (y/n)->:  ";
    cin >> ch;
    if (ch == 'n' || ch == 'N')
        opt._department = false;

    cout<<"\n\t--Term-- (y/n)->:  ";
    cin >> ch;
    if (ch == 'n' || ch == 'N')
        opt._term = false;

    cout<<"\n\t--Birthday-- (y/n)->:  ";
    cin >> ch;
    if (ch == 'n' || ch == 'N')
        opt._dob= false;

    cout<<"\n\t--Description-- (y/n)->:  ";
    cin >> ch;
    if (ch == 'n' || ch == 'N')
        opt._description = false;

    cout<<"\n\t--Hobbies-- (y/n)->:  ";
    cin >> ch;
    if (ch == 'n' || ch == 'N')
        opt._hobby = false;

}