#include "command.hpp"

#include <iostream>
#include <string>
#include <unordered_map>

namespace {

const std::unordered_map<std::string, Shape> SHAPES = {
    {"cube", Shape::Cube},
    {"sphere", Shape::Sphere},
    {"cylinder", Shape::Cylinder},
    {"cone", Shape::Cone},
    {"pyramid", Shape::Pyramid}
};

const std::unordered_map<std::string, Color> COLORS = {
    {"lightgray", LIGHTGRAY}, {"gray", GRAY},       {"darkgray", DARKGRAY},
    {"yellow", YELLOW},       {"gold", GOLD},       {"orange", ORANGE},
    {"pink", PINK},           {"red", RED},         {"maroon", MAROON},
    {"green", GREEN},         {"lime", LIME},       {"darkgreen", DARKGREEN},
    {"skyblue", SKYBLUE},     {"blue", BLUE},       {"darkblue", DARKBLUE},
    {"purple", PURPLE},       {"violet", VIOLET},   {"darkpurple", DARKPURPLE},
    {"beige", BEIGE},         {"brown", BROWN},     {"darkbrown", DARKBROWN},
    {"white", WHITE},         {"black", BLACK},     {"blank", BLANK},
    {"magenta", MAGENTA},     {"raywhite", RAYWHITE}
};

Shape parseShape(const std::string& name) {
    if (name.empty()) return Shape::Cube;

    auto it = SHAPES.find(name);
    if (it != SHAPES.end()) return it->second;

    return Shape::Cube;
}

Color parseColor(const std::string& name) {
    if (name.empty()) return WHITE;

    auto it = COLORS.find(name);
    if (it != COLORS.end()) return it->second;

    return WHITE;
}

}

SceneConfig getUI_fc(const std::string& command) {
    SceneConfig config;

    if (command == "exit") {
        config.shape = Shape::Exit;
        return config;
    }

    std::string fig;
    std::string colorName;

    int i = 0;

    while (i < command.length() && command[i] != ' ') {
        fig += command[i++];
    }

    if (i < command.length()) {
        i++;

        while (i < command.length() && command[i] != ' ') {
            colorName += command[i++];
        }
    }

    config.shape = parseShape(fig);
    config.color = parseColor(colorName);

    return config;
}

SceneConfig getUI_fc() {
    std::string command;

    std::cout << "--->";
    std::getline(std::cin, command);

    return getUI_fc(command);
}