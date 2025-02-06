#ifndef __CONSOLE_H__
#define __CONSOLE_H__

/*
 * This is the function called by printf to send its output to the screen. You
 * have to implement it in the kernel and in the user program.
 */
#include "inttypes.h"

// Constants
#define NB_LIGNE 25
#define NB_COLONNE 80
#define START_VID_ADDR 0xB8000

#define CURSOR_LOW_CODE 0X0F
#define CURSOR_HIGH_CODE 0x0E

#define CURSOR_CMD_PORT 0x3D4
#define CURSOR_DATA_PORT 0x3D5

// Function declarations
uint16_t* ptr_mem(uint32_t lig, uint32_t col);
void ecrit_car(uint32_t lig, uint32_t col, char c);
void efface_ecran(void);
void place_curseur(uint32_t lig, uint32_t col);
void defilement(void);
void traite_car(char c);
extern void console_putbytes(const char *s, int len);

#endif
