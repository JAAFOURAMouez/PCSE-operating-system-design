#include <cpu.h>
#include <inttypes.h>
#include <stdio.h>
#include <time.h>
#include <console.h>
#include<processus.h>
#include "tinyalloc.h"
// Déclaration de la fonction traitant_IT_32 pour l'interruption
extern void traitant_IT_32(void);

void kernel_start(void)
{
    /*----------------------------------------------------tp1---------------------------------------------*/
    efface_ecran();
    place_curseur(0,0);
    printf("hello, C est Mouez\n");
    

    
    /*----------------------------------------------------tp2---------------------------------------------*/
    /*
    //Initialiser l'interruption pour le timer (PIT)
    init_traitant_IT(32, traitant_IT_32);
    //Régler la fréquence de l'horloge (PIT)
    set_clock_frq();
    //Démasquer l'IRQ du timer
    masque_IRQ(0, 0);
    //Activer les interruptions
    sti();
    // Boucle infinie pour maintenir le noyau actif
    */
    /*----------------------------------------------------tp3-Partie 1-----------------------------------*/
    /*cli();
    struct processus idle_struct ={.pid=0,.nom="idle",.etat=ACTIVABLE,.registre[1]=(int)(&idle_struct.pile[511])};;
    struct processus proc1_struct={.pid=1,.nom="proc1",.etat=ACTIVABLE,.registre[1]=(int)(&proc1_struct.pile[511])};
    proc1_struct.pile[511]=(int) proc1;
    tab_processus[0]=&idle_struct;
    tab_processus[1]=&proc1_struct;
    proc_en_execution=tab_processus[0];
    idle();
    while (1) {
        hlt(); // Attend la prochaine interruption
    }*/

    /*----------------------------------------------------tp3-Partie 2-----------------------------------*/
    /*
    for (int i = 0; i < 8; i++)
    {
        tab_processus[i]=malloc(sizeof(struct processus));
    }
    cree_processus(idle,"idle");
    cree_processus(proc1,"proc1");
    cree_processus(proc2,"proc2");
    cree_processus(proc3,"proc3");
    cree_processus(proc4,"proc4");
    cree_processus(proc5,"proc5");
    cree_processus(proc6,"proc6");
    cree_processus(proc7,"proc7");
    proc_en_execution=tab_processus[0];

    idle();
    while (1) {
        hlt(); // Attend la prochaine interruption
    }*/
    /*----------------------------------------------------tp3-Partie 3-----------------------------------*/
    //Initialiser l'interruption pour le timer (PIT)
    init_traitant_IT(32, traitant_IT_32);
    //Régler la fréquence de l'horloge (PIT)
    set_clock_frq();
    //Démasquer l'IRQ du timer
    masque_IRQ(0, 0);
    cree_processus(idle,"idle");
    cree_processus(proc1,"proc1");
    cree_processus(proc2,"proc2");
    cree_processus(proc3,"proc3");
    cree_processus(proc4,"proc4");
    cree_processus(proc5,"proc5");
    cree_processus(proc6,"proc6");
    cree_processus(proc7,"proc7");
    idle();
    while (1) {
        hlt(); // Attend la prochaine interruption
    }
    /*----------------------------------------------------tp3-Partie 4-----------------------------------*/

}
