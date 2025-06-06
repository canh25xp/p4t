#include "log.h"

#define COLOR_RED "\033[91m"
#define COLOR_YELLOW "\033[93m"
#define COLOR_GREEN "\033[32m"
#define COLOR_NORMAL "\033[0m"

const char *Log::ColorRed = COLOR_RED;
const char *Log::ColorYellow = COLOR_YELLOW;
const char *Log::ColorGreen = COLOR_GREEN;
const char *Log::ColorNormal = COLOR_NORMAL;

void Log::DisableColoredOutput() {
    ColorRed = COLOR_NORMAL;
    ColorYellow = COLOR_NORMAL;
    ColorGreen = COLOR_NORMAL;
    ColorNormal = COLOR_NORMAL;
}
