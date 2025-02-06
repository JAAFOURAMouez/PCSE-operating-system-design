#ifndef __TIME_H__
#define __TIME_H__

#include <stdbool.h>
#include "inttypes.h"

#define IDT_ADDR 0x1000
#define QUARTZ 0x1234DD
#define CLOCKFREQ 200

extern void traitant_IT_32();

// Fonction pour afficher le temps à l'écran
void ecrit_temps(char *ch);

// Gestionnaire d'interruption pour le timer système
void tic_PIT(void);

// Initialise un gestionnaire d'interruption pour une interruption donnée
void init_traitant_IT(int32_t num_IT, void (*traitant)(void));

// Définit la fréquence d'horloge (PIT)
void set_clock_frq(void);

// Masque ou démasque une IRQ
void masque_IRQ(uint32_t num_IRQ, bool masque);

// Retourner le nombre de seconde
int nb_seconde();
#endif
