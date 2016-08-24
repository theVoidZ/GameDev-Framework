#ifndef TERMINAL_COLORS_H
#define TERMINAL_COLORS_H

/* FOREGROUND */
// Escape character: \e, \033, \x1B in bash

// Forground colors
#define FDEFAULT "\e[39m"       // default color
#define FBLACK "\e[30m"         // black color
#define FRED "\e[31m"           // red color
#define FGREEN "\e[32m"         // green color
#define FYELLOW "\e[33m"        // yellow color
#define FBLUE "\e[34m"          // blue color
#define FMAGENTA "\e[35m"       // magenta color
#define FCYAN "\e[36m"          // cyan color
#define FLIGHT_GRAY "\e[37m"    // light-gray color
#define FDRAK_GRAY "\e[90m"     // dark-gray color
#define FLIGHT_RED "\e[91m"     // light-red color
#define FLIGHT_GREEN "\e[92m"   // light-green color
#define FLIGHT_YELLOW "\e[93m"  // light-yellow color
#define FLIGHT_BLUE "\e[94m"    // light-blue color
#define FLIGHT_MAGENTA "\e[95m" // light-magenta color
#define FLIGHT_CYAN "\e[96m"    // light-Cyan color
#define FWHITE "\e[97m"         // white color
#define FORANGE "\e[38;5;214m"  // orange color

// Background colors
#define BDEFAULT "\e[49m"       // default color
#define BBLACK "\e[40m"         // black color
#define BRED "\e[41m"           // red color
#define BGREEN "\e[42m"         // green color
#define BYELLOW "\e[43m"        // yellow color
#define BBLUE "\e[44m"          // blue color
#define BMAGENTA "\e[45m"       // magenta color
#define BCYAN "\e[46m"          // cyan color
#define BLIGHT_GRAY "\e[47m"    // light-gray color
#define BDRAK_GRAY "\e[100m"     // dark-gray color
#define BLIGHT_RED "\e[101m"     // light-red color
#define BLIGHT_GREEN "\e[102m"   // light-green color
#define BLIGHT_YELLOW "\e[103m"  // light-yellow color
#define BLIGHT_BLUE "\e[104m"    // light-blue color
#define BLIGHT_MAGENTA "\e[105m" // light-magenta color
#define BLIGHT_CYAN "\e[106m"    // light-Cyan color
#define BWHITE "\e[107m"         // white color
#define BORANGE "\e[38;5;214m"  // orange color


// background = foreground + 10
// Attributes
#define RESET "\e[0m"
#define BOLD "\e[1m"
#define DIM "\e[2m"
#define ITALIC "\e[3m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m" // Works only on xterm and tty ( cf. documentation )
#define REVERSE "\e[7m"
#define HIDDEN "\e[8m"

#define RESET_ATTR "\e[21m"
#define RESET_BOLD "\e[21m"
#define RESET_DIM "\e[22m"
#define RESET_ITALIC "\e[24m"
#define RESET_UNDERLINE "\e[25m"
#define RESET_BLINK "\e[26m"
#define RESET_REVERSE "\e[27m"
#define RESET_HIDDEN "\e[28m"

#define RESET_FCOLOR "\e[39m"
#define RESET_BCOLOR "\e[49m"

#endif // TERMINAL_COLORS_H
