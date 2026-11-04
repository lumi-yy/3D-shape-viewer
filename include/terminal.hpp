#pragma once

#include <string>
#include "command.hpp"
#include <ncurses.h>

struct Selection {
    Shape shape = Shape::Cube;
    Color color = WHITE;
};

void terminal();

WINDOW* createWindow1(int height, int width, int y, int x);
WINDOW* createWindow2(int height, int width, int y, int x);
void updateSelectionF(int& key, int& selectionIndex, WINDOW* win);
void updateSelectionC(int& key, int& selectionIndex, WINDOW* win);
WINDOW* createCommandWindow(int height, int width, int y, int x);
bool checkTerminalSize();