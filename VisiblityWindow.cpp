#include <iostream>
#include <windows.h>
#include <conio.h>

#define HIDE_KEY 0x48
#define SHOW_KEY 0x53
#define EXIT_KEY 0x58

void clrscr() {
    DWORD Unused = 0;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD zerozeroc = {0, 0};
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    DWORD Length = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacterW(GetStdHandle(STD_OUTPUT_HANDLE), ' ', Length, zerozeroc, &Unused);
    FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), csbi.wAttributes, Length, zerozeroc, &Unused);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), zerozeroc);
}

void writeat(LPCSTR chars, COORD pos, WORD color = 0) {
    DWORD unused;
    WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), chars, strlen(chars), pos, &unused);
    FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color, strlen(chars), pos, &unused);
}

void changecolor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {

    SetConsoleTitle("Simple Window Visibility Controller - Made by MaayanM.C (AKA Ne-guy)");

    while (TRUE) {

        std::cout << "Enter the program's title: ";

        std::string title;
        std::getline(std::cin, title);

        HWND window = FindWindowA(NULL, title.c_str());

        if (window == NULL) {
            clrscr();
            std::cout << "ERROR: Window was not found.";
            Sleep(2000);
            clrscr();
            continue;
        }

        std::cout << "\n(H)ide / (S)how / E(X)it>";

        while (TRUE) {
            
            int val = getch();
            char chara = val;

            if (GetAsyncKeyState(HIDE_KEY) & 0x8000) {
                writeat("Window Hidden.    ", {4 * 2, 4}, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                ShowWindow(window, SW_HIDE);
            }
            else if (GetAsyncKeyState(SHOW_KEY) & 0x8000) {
                writeat("Window Shown.    ", {4 * 2, 4}, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                ShowWindow(window, SW_SHOW);
            }
            else if (GetAsyncKeyState(EXIT_KEY) & 0x8000) {
                clrscr();
                break;
            }
            

        }
    }

}