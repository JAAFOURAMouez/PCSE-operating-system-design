#include <cpu.h>
#include <stdbool.h>
#include "console.h"
#include "time.h"
#include "segment.h"
#include "debug.h"
#include "processus.h"

int system_time = 0;
int ticks = 0;

void ecrit_temps(char* time) {
    char* cour = time;
    while (*cour != '\0') {
        cour++;
    }
    int col = 79;
    while (cour != time) {
        cour--;
        ecrit_car(0, col, *cour);
        col--;
    }
}

void tic_PIT(void) {
    // Envoie un signal pour signifier que l'interruption est traitée
    outb(0x20, 0x20);

    ticks++;
    if (ticks == 50) {  // 50 ticks par seconde
        system_time++;
        ticks = 0;
    }

    // Formatage du temps en hh:mm:ss
    char timestring[9];
    sprintf(timestring, "%02d:%02d:%02d", system_time / 3600, (system_time / 60) % 60, system_time % 60);

    // Afficher le temps à l'écran
    ecrit_temps(timestring);
    ordonnance();
}

void init_traitant_IT(int32_t num_IT, void (*traitant)(void)) {
    uint32_t* adress = (uint32_t *)((uint32_t*)0x1000 + 2 * num_IT);
    uint32_t premiere_partie = (uint32_t)KERNEL_CS | (uint32_t)traitant;
    uint32_t deuxieme_partie = (uint32_t)(((uint32_t)traitant) & 0xFFFF0000) | 0x8E00;
    *adress = premiere_partie;
    *(adress + 1) = deuxieme_partie;
}

void set_clock_frq() {
    outb(0x34, 0x43);  // Commande pour le PIT
    outb((QUARTZ / CLOCKFREQ) & 0xFF, 0x40);  // LSB
    outb((QUARTZ / CLOCKFREQ) >> 8, 0x40);    // MSB
}

void masque_IRQ(uint32_t num_IRQ, bool masque) {
    uint8_t mask = inb(0x21);

    if (masque) {
        mask |= (1 << num_IRQ);  // Masquer l'IRQ
    } else {
        mask &= ~(1 << num_IRQ);  // Démasquer l'IRQ
    }

    outb(mask, 0x21);  // Écrire le masque mis à jour
}

int nb_seconde(){
    return system_time;
}