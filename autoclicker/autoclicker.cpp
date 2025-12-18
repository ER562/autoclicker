#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <chrono>

using std::endl;
using std::cout;

int main()
{
    MOUSEINPUT mause_left_press{ 0, 0, 0, MOUSEEVENTF_LEFTDOWN, 0 ,GetMessageExtraInfo() };
    MOUSEINPUT mause_left_release{ 0, 0, 0, MOUSEEVENTF_LEFTUP, 0, GetMessageExtraInfo() };

    unsigned int interval = 1000;
    bool state = false;

    INPUT input[2];

    input[0].type = INPUT_MOUSE;
    input[0].mi = mause_left_press;
    input[1].type = INPUT_MOUSE;
    input[1].mi = mause_left_release;

    //time
    auto now = std::chrono::steady_clock::now();
    auto last = std::chrono::steady_clock::now();

    //hotkeys
    RegisterHotKey(NULL, 1, MOD_CONTROL, 0x4D);
    RegisterHotKey(NULL, 2, MOD_CONTROL, 0x4C);
    RegisterHotKey(NULL, 3, MOD_CONTROL | MOD_NOREPEAT, VK_RETURN);

    MSG message;

    cout << "Settings:" << endl << "Click interval: " << interval << endl << "State:" << state << endl;
    cout << "\nCTRL +\nM --> +10 to interval\nL --> -10 to interval\nENTER --> turns of or on\n";

    while (1) {

        //clicking
        now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count() >= interval) {
            last = std::chrono::steady_clock::now();
            if (state) {
                UINT uSent = SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
            }
        }

        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            if (message.wParam == 1) {
                if (interval + 10 < 5000) {
                    interval += 10;
                }
            }
            else if (message.wParam == 2) {
                if (interval - 10 > 0) {
                    interval -= 10;
                }
            }
            else if (message.wParam == 3) {
                state = !state;
            }
            system("cls");
            cout << "Settings:" << endl << "Click interval: " << interval << endl << "State:" << state << endl;
            cout << "\nCTRL +\nM --> +10 to interval\nL --> -10 to interval\nENTER --> turns of or on\n";
        }
    }
}