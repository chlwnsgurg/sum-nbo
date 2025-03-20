#include "nbo.h"

uint32_t nboToHbo(uint32_t nbo) {
    return ((nbo & 0x000000FF) << 24) |
           ((nbo & 0x0000FF00) << 8)  |
           ((nbo & 0x00FF0000) >> 8)  |
           ((nbo & 0xFF000000) >> 24);
}
