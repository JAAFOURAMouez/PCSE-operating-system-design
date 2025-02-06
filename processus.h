#ifndef PROCESSUS_H
#define PROCESSUS_H
#define STACK_SIZE 512
#define MAX_NAME_LEN 32
#include "inttypes.h"
extern struct processus* tab_processus[8];
extern struct processus* proc_en_execution;
typedef enum {
    ELU,
    ACTIVABLE,
    ENDORMI,
    ZOMBIE
} etat_processus;

typedef struct processus {
    int pid;
    char nom[MAX_NAME_LEN];
    etat_processus etat;
    int registre[5];
    int pile[STACK_SIZE];
    struct processus * suiv;
    uint32_t heure;
} processus;
int32_t cree_processus(void (*code)(void), char *nom);
void ctx_sw(int * adress_ancien_proc, int * adress_nouveau_proc);
void idle(void);
void proc1(void);
void proc2(void);
void proc3(void);
void proc4(void);
void proc5(void);
void proc6(void);
void proc7(void);
void ordonnance(void);

extern processus idle_proc;  // Déclaration des processus
extern processus proc1_proc;

#endif
