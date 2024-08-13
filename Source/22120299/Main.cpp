#include "SinhVien.h"

int main()
{
    int nos = takeNumber("DATA\\INFOR.csv");
    SinhVien* sv = new SinhVien[nos];
    Options opt{ true, true, true, true, true, true, true };

    readFile("DATA\\INFOR.csv", sv, nos);

    bool option = true;
    cout << "\t\tDo you want to generate student profile web page (y-n)? : ";
    char ch;
    cin >> ch;
    if (ch != 'y')
    {
        option = false;
    }

    if (option)
    {
        Option(opt);
        const wchar_t* test = L"DATA\\test.html";
        cout << "\n\t\t---Press any button for YES and 'n' for NO---\n";
        for (int i = 0; i < nos; i++)
        {
            wcout << "\n\tGenerate profile web page for student id '" << sv[i]._id << "'?";
            char ch;
            cin >> ch;
            if (ch == 'n')
                continue;
            wchar_t* buffer = readFileIntoBuffer("DATA\\htmlTemplate.html");
            writeFileFromBuffer(test, buffer);
            wchar_t* filename = generateFilename(sv[i]);
            replaceDetail(sv[i], buffer, opt);
            writeFileFromBuffer(filename, buffer);
            writeFile("DATA\\output.txt", sv[i]);
        }
        cout << "[#] Genererate Successful\n";
    }
    else
        cout << "[#] Quit Program \n";

}