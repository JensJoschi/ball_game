#ifndef HELPERS_H
#define HELPERS_H

template <typename Enum>
static Enum incrementEnum(Enum value, Enum count) {
    return static_cast<Enum>((static_cast<int>(value) + 1) % static_cast<int>(count));
}
template <typename Enum>
static Enum decrementEnum(Enum value, Enum count) {
    return static_cast<Enum>((static_cast<int>(value) - 1 + static_cast<int>(count)) % static_cast<int>(count));
}

template <typename T>
concept HasCount = requires {
    T::COUNT;
};

enum class Menus{
    mainMenu = 0,
    optionsMenu = 1,
    quit = 2,
    none = 3
};


#endif // HELPERS_H
