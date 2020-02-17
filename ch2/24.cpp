//
// Created by asus on 2020/2/8.
//

#include <windows.h>
#include <iostream>

int main() {
    using namespace std;

    char *source = new char[100], *destination = new char[100];

    cout << "please enter the source file:" << endl;
    cin >> source;
    cout << "please enter the destination file:" << endl;
    cin >> destination;
    CopyFile(source, destination, false);
    if (GetLastError() == ERROR_FILE_NOT_FOUND) {
        cout << ERROR_FILE_NOT_FOUND;
    }
    return 0;
}
