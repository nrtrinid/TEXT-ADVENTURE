#pragma once

// enum representing normalized keypresses
enum class InputKey {
    Up,
    Down,
    Left,
    Right,
    Enter,
    Unknown
};

// cross-platform function to read a single key input
InputKey getInput();