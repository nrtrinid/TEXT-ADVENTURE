#ifdef _WIN32
#include <conio.h>
#include "Input.h"

InputKey getInput() {
    int key = _getch();
    if (key == '\r') return InputKey::Enter;
    if (key == 224) {
        int arrow = _getch();
        if (arrow == 72) return InputKey::Up;
        if (arrow == 80) return InputKey::Down;
        if (arrow == 75) return InputKey::Left;
        if (arrow == 77) return InputKey::Right;
    }
    return InputKey::Unknown;
}

#else
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "Input.h"

InputKey getInput() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // Save terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Turn off canonical mode & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings

    int ch = getchar(); // Read one character

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings

    if (ch == '\n') return InputKey::Enter;
    if (ch == 27) { // ESC character starts arrow sequence
        if (getchar() == '[') {
            switch (getchar()) {
            case 'A': return InputKey::Up;
            case 'B': return InputKey::Down;
            case 'C': return InputKey::Left;
            case 'D': return InputKey::Right;
            }
        }
    }
    return InputKey::Unknown;
}
#endif
