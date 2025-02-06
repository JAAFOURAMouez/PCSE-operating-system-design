#include "console.h"
#include "stddef.h"
#include "cpu.h"
#include "string.h"

// Cursor position variables
static uint16_t lig = 0;
static uint16_t col = 0;

// Text properties
static uint8_t clignote = 0;
static uint8_t backgroundCouleur = 0;
static uint8_t textCouleur = 15;

// Get memory address of a screen location
uint16_t* ptr_mem(uint32_t lig, uint32_t col) {
    if (lig >= NB_LIGNE || col >= NB_COLONNE) {
        return NULL; // Error
    } else {
        uint16_t* addr = (uint16_t*)(START_VID_ADDR + 2 * (lig * NB_COLONNE + col));
        return addr;
    }
}

// Write a character at a specific position
void ecrit_car(uint32_t lig, uint32_t col, char c) {
    uint16_t* addr = ptr_mem(lig, col);
    *addr = c | (clignote << 15) | (backgroundCouleur << 12) | (textCouleur << 8);
}

// Clear the screen
void efface_ecran(void) {
    for (uint16_t l = 0; l < NB_LIGNE; ++l) {
        for (uint16_t kase = 0; kase < NB_COLONNE; ++kase) {
            ecrit_car(l, kase, ' '); // Space (ASCII 32)
        }
    }
}

// Place cursor at a given position
void place_curseur(uint32_t lig, uint32_t col) {
    uint16_t pos = col + lig * NB_COLONNE;
    uint8_t low_pos = (uint8_t)(pos & 0xff);
    uint8_t high_pos = (uint8_t)(pos >> 8);

    outb(CURSOR_LOW_CODE, CURSOR_CMD_PORT);
    outb(low_pos, CURSOR_DATA_PORT);

    outb(CURSOR_HIGH_CODE, CURSOR_CMD_PORT);
    outb(high_pos, CURSOR_DATA_PORT);
}

// Scroll the screen
void defilement(void) {
    memmove((void*)ptr_mem(0, 0), (void*)ptr_mem(1, 0), 24 * NB_COLONNE * 2);
    for (uint32_t kase = 0; kase < NB_COLONNE; ++kase) {
        ecrit_car(24, kase, ' ');
    }
}

// Handle special characters
void traite_car(char c) {
    if (c < 32 || c == 127) {
        switch (c) {
            case 8: // Backspace
                if (col > 0) col--;
                break;
            case 9: // Tab
                if (col <= 72) col += 4;
                break;
            case 10: // Newline
                if (lig < 24) {
                    col = 0;
                    ++lig;
                } else {
                    defilement();
                    col = 0;
                    lig = 24;
                }
                break;
            case 12: // Form feed
                efface_ecran();
                col = 0;
                lig = 0;
                break;
            case 13: // Carriage return
                col = 0;
                break;
            default:
                break;
        }
    } else if (c >= 32 && c <= 126) {
        ecrit_car(lig, col, c);
        ++col;
        if (col >= NB_COLONNE) {
            col = 0;
            ++lig;
            if (lig >= NB_LIGNE) {
                defilement();
                lig = 24;
            }
        }
    } else {
        traite_car(c % 128);
    }
    place_curseur(lig, col);
}

// Print a string to the console
void console_putbytes(const char *s, int len) {
    for (uint16_t i = 0; i < len; ++i) {
        traite_car(s[i]);
    }
}
