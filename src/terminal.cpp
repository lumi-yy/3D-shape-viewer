#include "terminal.hpp"
#include "command.hpp"
#include "renderer.hpp"
#include <ncurses.h>

const Shape shapes[] = {
    Shape::Cube,
    Shape::Pyramid,
    Shape::Sphere,
    Shape::Cylinder,
    Shape::Cone
};

const Color colors[] = {
    LIGHTGRAY, GRAY, DARKGRAY,
    YELLOW, GOLD, ORANGE,
    PINK, RED, MAROON,
    GREEN, LIME, DARKGREEN,
    SKYBLUE, BLUE, DARKBLUE,
    PURPLE, VIOLET, DARKPURPLE,
    BEIGE, BROWN, DARKBROWN,
    WHITE, BLACK, BLANK,
    MAGENTA, RAYWHITE
};

void terminal() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    bool running = true;

    while (running) {
        if (!checkTerminalSize()){
            int ch = getch();

            if (ch == KEY_RESIZE)
                continue;

            if (ch == 'q' || ch == 'Q')
                running = false;

            continue;
        }

        erase();
        clear();
        refresh();

        Selection selection{};

        WINDOW* commandWin = createCommandWindow(7, 95, 1, 5);
        WINDOW* win1 = createWindow1(25, 30, 9, 5);
        WINDOW* win2 = createWindow2(25, 65, 9, 35);

        if (!commandWin || !win1 || !win2) {
            if (commandWin) delwin(commandWin);
            if (win1) delwin(win1);
            if (win2) delwin(win2);
            break;
        }

        char command[256] = {};
        int key = 0;
        int selectionIndex = 0;

        updateSelectionF(key, selectionIndex, win1);
        updateSelectionC(key, selectionIndex, win2);

        echo();
        curs_set(1);
        mvwgetnstr(commandWin, 3, 4, command, sizeof(command) - 1);
        noecho();
        curs_set(0);

        SceneConfig config{};

        if (command[0] != '\0') {
            config = getUI_fc(command);

            if (config.shape == Shape::Exit) {
                delwin(commandWin);
                delwin(win1);
                delwin(win2);
                break;
            }
        } 
        else {
            while (true) {
                key = wgetch(win1);

                if (key == '\n' || key == KEY_ENTER) {
                    selection.shape = shapes[selectionIndex];
                    selectionIndex = 0;
                    break;
                }

                updateSelectionF(key, selectionIndex, win1);
            }

            while (true) {
                key = wgetch(win2);

                if (key == '\n' || key == KEY_ENTER) {
                    selection.color = colors[selectionIndex];
                    break;
                }

                updateSelectionC(key, selectionIndex, win2);
            }

            config.shape = selection.shape;
            config.color = selection.color;
        }

        delwin(commandWin);
        delwin(win1);
        delwin(win2);

        render(config);

        touchwin(stdscr);
        refresh();
    }

    endwin();
}

WINDOW* createWindow1(int height, int width, int y, int x) {
    WINDOW* win = newwin(height, width, y, x);

    if (win == nullptr) return nullptr;

    box(win, 0, 0);
    mvwprintw(win, 2, 2, "%s", "Choose a figure:");
    mvwprintw(win, 5, 4, "%s", "1. Cube");
    mvwprintw(win, 7, 4, "%s", "2. Pyramid");
    mvwprintw(win, 9, 4, "%s", "3. Sphere");
    mvwprintw(win, 11, 4, "%s", "4. Cylinder");
    mvwprintw(win, 13, 4, "%s", "5. Cone");

    wrefresh(win);
    return win;
}

WINDOW* createWindow2(int height, int width, int y, int x) {
    WINDOW* win = newwin(height, width, y, x);

    if (win == nullptr) return nullptr;

    box(win, 0, 0);
    mvwprintw(win, 2, 2, "%s", "Choose a color:");
    wrefresh(win);

    return win;
}

WINDOW* createCommandWindow(int height, int width, int y, int x) {
    WINDOW* win = newwin(height, width, y, x);

    if (win == nullptr) return nullptr;

    box(win, 0, 0);
    mvwprintw(win, 1, 2, "%s", "Command:");
    mvwprintw(win, 3, 2, "%s", "> ");

    wrefresh(win);
    return win;
}

void updateSelectionF(int& key, int& selectionIndex, WINDOW* win) {
    switch (key) {
        case 'w':
        case 'W':
            if (selectionIndex > 0)
                selectionIndex--;
            break;

        case 's':
        case 'S':
            if (selectionIndex < 4)
                selectionIndex++;
            break;
    }

    int positions[] = {5, 7, 9, 11, 13};
    const char* figures[] = {
        "1. Cube",
        "2. Pyramid",
        "3. Sphere",
        "4. Cylinder",
        "5. Cone"
    };

    for (int i = 0; i < 5; i++) {
        if (i == selectionIndex) wattron(win, A_REVERSE);

        mvwprintw(win, positions[i], 4, "%-15s", figures[i]);

        if (i == selectionIndex) wattroff(win, A_REVERSE);
    }

    wrefresh(win);
}

void updateSelectionC(int& key, int& selectionIndex, WINDOW* win) {
    int columns = 3;
    int count = sizeof(colors) / sizeof(colors[0]);

    const char* names[] = {
        "Light Gray", "Gray", "Dark Gray",
        "Yellow", "Gold", "Orange",
        "Pink", "Red", "Maroon",
        "Green", "Lime", "Dark Green",
        "Sky Blue", "Blue", "Dark Blue",
        "Purple", "Violet", "Dark Purple",
        "Beige", "Brown", "Dark Brown",
        "White", "Black", "Blank",
        "Magenta", "Ray White"
    };

    switch (key) {
        case 'w':
        case 'W':
            if (selectionIndex >= columns)
                selectionIndex -= columns;
            break;

        case 's':
        case 'S':
            if (selectionIndex + columns < count)
                selectionIndex += columns;
            break;

        case 'a':
        case 'A':
            if (selectionIndex > 0)
                selectionIndex--;
            break;

        case 'd':
        case 'D':
            if (selectionIndex + 1 < count)
                selectionIndex++;
            break;
    }

    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 2, 2, "%s", "Choose a color:");

    for (int i = 0; i < count; i++) {
        int row = i / columns;
        int col = i % columns;

        int y = 5 + row * 2;
        int x = 3 + col * 19;

        if (i == selectionIndex)
            wattron(win, A_REVERSE);

        mvwprintw(win, y, x, "%-16s", names[i]);

        if (i == selectionIndex)
            wattroff(win, A_REVERSE);
    }

    wrefresh(win);
}

bool checkTerminalSize(){
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int MIN_ROWS = 34;
    int MIN_COLS = 100;

    if (rows < MIN_ROWS || cols < MIN_COLS){
        erase();

        mvprintw(0, 0, "Terminal is too small!");
        mvprintw(1, 0, "Required: %dx%d", MIN_COLS, MIN_ROWS);
        mvprintw(2, 0, "Current:  %dx%d", cols, rows);
        mvprintw(4, 0, "Please resize the terminal.");

        refresh();
        return false;
    }

    return true;
}