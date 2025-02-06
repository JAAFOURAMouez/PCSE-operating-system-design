#include "processus.h"
#include "cpu.h"
#include "inttypes.h"
#include "stdio.h"
#include "tinyalloc.h"
#include "string.h"
#include "time.h"

struct processus* tab_processus[8];
struct processus* proc_en_execution;
struct processus* tete;
struct processus* queue;
struct processus* endormi; 
struct processus* zombie;
int8_t nb_processus_cree=0;
/*--------------------------------------------------------------tp3-Partie1-test1------------------------------------------------------------------------------ */
/*void idle(void)
{
    printf("[idle] je tente de passer la main a proc1...\n");
    ctx_sw((int*)tab_processus[0]->registre, (int*)tab_processus[1]->registre);
}
void proc1(void)
{
    printf("[proc1] idle m a donne la main\n");
    printf("[proc1] j arrete le systeme\n");
    hlt();
}
*/
/*--------------------------------------------------------------tp3-Partie1-test2------------------------------------------------------------------------------ */
/*
void idle(void)
{
    for (int i = 0; i < 3; i++) {
        printf("[idle] je tente de passer la main a proc1...\n");
        ctx_sw((int*)tab_processus[0]->registre, (int*)tab_processus[1]->registre);
        printf("[idle] proc1 m’a redonne la main\n");
    }
    printf("[idle] je bloque le systeme\n");
    hlt();
}

void proc1(void)
{
    for (;;) {
        printf("[proc1] idle m’a donne la main\n");
        printf("[proc1] je tente de lui la redonner...\n");
        ctx_sw((int*)tab_processus[1]->registre, (int*)tab_processus[0]->registre);
    }
}
*/
/*--------------------------------------------------------------tp3-Partie2----------------------------------------------------------------------------------- */
char *mon_nom(){
    return proc_en_execution->nom;
}
int mon_pid(){
    return proc_en_execution->pid;
}
/*void ordonnance(){
    if(mon_pid()==0){
        proc_en_execution=tab_processus[1];
        ctx_sw((int*)tab_processus[0]->registre, (int*)tab_processus[1]->registre);
    }
    else{
        proc_en_execution=tab_processus[0];
        ctx_sw((int*)tab_processus[1]->registre, (int*)tab_processus[0]->registre);

    }
}

void idle(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc1(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
*/
/*--------------------------------------------------------------tp3-Partie3-1--------------------------------------------------------------------------------- */
/*
void ordonnance(){
    if(mon_pid()==0){
        tab_processus[0]->etat=ACTIVABLE;
        tab_processus[1]->etat=ELU;
        proc_en_execution=tab_processus[1];
        ctx_sw((int*)tab_processus[0]->registre, (int*)tab_processus[1]->registre);
    }else if(mon_pid()==1){
        tab_processus[1]->etat=ACTIVABLE;
        tab_processus[2]->etat=ELU;
        proc_en_execution=tab_processus[2];
        ctx_sw((int*)tab_processus[1]->registre, (int*)tab_processus[2]->registre);
    }else if(mon_pid()==2){
        tab_processus[2]->etat=ACTIVABLE;
        tab_processus[3]->etat=ELU;
        proc_en_execution=tab_processus[3];
        ctx_sw((int*)tab_processus[2]->registre, (int*)tab_processus[3]->registre);
    }else if(mon_pid()==3){
        tab_processus[3]->etat=ACTIVABLE;
        tab_processus[4]->etat=ELU;
        proc_en_execution=tab_processus[4];
        ctx_sw((int*)tab_processus[3]->registre, (int*)tab_processus[4]->registre);
    }else if(mon_pid()==4){
        tab_processus[4]->etat=ACTIVABLE;
        tab_processus[5]->etat=ELU;
        proc_en_execution=tab_processus[5];
        ctx_sw((int*)tab_processus[4]->registre, (int*)tab_processus[5]->registre);
    }else if(mon_pid()==5){
        tab_processus[5]->etat=ACTIVABLE;
        tab_processus[6]->etat=ELU;
        proc_en_execution=tab_processus[6];
        ctx_sw((int*)tab_processus[5]->registre, (int*)tab_processus[6]->registre);
    }else if(mon_pid()==6){
        tab_processus[6]->etat=ACTIVABLE;
        tab_processus[7]->etat=ELU;
        proc_en_execution=tab_processus[7];
        ctx_sw((int*)tab_processus[6]->registre, (int*)tab_processus[7]->registre);
    }else if(mon_pid()==7){
        tab_processus[7]->etat=ACTIVABLE;
        tab_processus[0]->etat=ELU;
        proc_en_execution=tab_processus[0];
        //ctx_sw((int*)tab_processus[7]->registre, (int*)tab_processus[0]->registre);
        hlt();
    }
}

void idle(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc1(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc2(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc3(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc4(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}void proc5(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc6(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc7(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
int32_t cree_processus(void (*code)(void),char* nom){
    if(nb_processus_cree==0){
        tab_processus[nb_processus_cree]->pid=nb_processus_cree;
        strcpy(tab_processus[nb_processus_cree]->nom,nom);
        tab_processus[nb_processus_cree]->etat=ELU;
        nb_processus_cree++;
        return tab_processus[nb_processus_cree-1]->pid;
    }else if(nb_processus_cree<8){
        tab_processus[nb_processus_cree]->pid=nb_processus_cree;
        strcpy(tab_processus[nb_processus_cree]->nom,nom);
        tab_processus[nb_processus_cree]->etat=ACTIVABLE;
        tab_processus[nb_processus_cree]->registre[1]=(int)(&tab_processus[nb_processus_cree]->pile[511]);
        tab_processus[nb_processus_cree]->pile[511]=(int)code;
        nb_processus_cree++;
        return tab_processus[nb_processus_cree-1]->pid;
    }else return -1;
}*/

/*--------------------------------------------------------------tp3-Partie3-2--------------------------------------------------------------------------------- */
/*
void ordonnance(){
    if(mon_pid()==0){
        tab_processus[0]->etat=ACTIVABLE;
        tab_processus[1]->etat=ELU;
        proc_en_execution=tab_processus[1];
        ctx_sw((int*)tab_processus[0]->registre, (int*)tab_processus[1]->registre);
    }else if(mon_pid()==1){
        tab_processus[1]->etat=ACTIVABLE;
        tab_processus[2]->etat=ELU;
        proc_en_execution=tab_processus[2];
        ctx_sw((int*)tab_processus[1]->registre, (int*)tab_processus[2]->registre);
    }else if(mon_pid()==2){
        tab_processus[2]->etat=ACTIVABLE;
        tab_processus[3]->etat=ELU;
        proc_en_execution=tab_processus[3];
        ctx_sw((int*)tab_processus[2]->registre, (int*)tab_processus[3]->registre);
    }else if(mon_pid()==3){
        tab_processus[3]->etat=ACTIVABLE;
        tab_processus[4]->etat=ELU;
        proc_en_execution=tab_processus[4];
        ctx_sw((int*)tab_processus[3]->registre, (int*)tab_processus[4]->registre);
    }else if(mon_pid()==4){
        tab_processus[4]->etat=ACTIVABLE;
        tab_processus[5]->etat=ELU;
        proc_en_execution=tab_processus[5];
        ctx_sw((int*)tab_processus[4]->registre, (int*)tab_processus[5]->registre);
    }else if(mon_pid()==5){
        tab_processus[5]->etat=ACTIVABLE;
        tab_processus[6]->etat=ELU;
        proc_en_execution=tab_processus[6];
        ctx_sw((int*)tab_processus[5]->registre, (int*)tab_processus[6]->registre);
    }else if(mon_pid()==6){
        tab_processus[6]->etat=ACTIVABLE;
        tab_processus[7]->etat=ELU;
        proc_en_execution=tab_processus[7];
        ctx_sw((int*)tab_processus[6]->registre, (int*)tab_processus[7]->registre);
    }else if(mon_pid()==7){
        tab_processus[7]->etat=ACTIVABLE;
        tab_processus[0]->etat=ELU;
        proc_en_execution=tab_processus[0];
        //ctx_sw((int*)tab_processus[7]->registre, (int*)tab_processus[0]->registre);
        hlt();
    }
}

void idle(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc1(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc2(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc3(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc4(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc5(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc6(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc7(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}

void insertion_queue(struct processus *nouveau){
    nouveau->etat=ACTIVABLE;
    if (tete==NULL){
        tete=nouveau;
        queue=nouveau;
    }else{
        queue->suiv=nouveau;
        nouveau->suiv=NULL;
        queue=nouveau;
    }
}

int32_t cree_processus(void (*code)(void),char* nom){
    if(nb_processus_cree==0){
        struct processus * proc=malloc(sizeof(struct processus));
        proc->pid=nb_processus_cree;
        strcpy(proc->nom,nom);
        proc->etat=ELU;
        tab_processus[nb_processus_cree]=proc;
        nb_processus_cree++;
        proc_en_execution=proc;
        return proc_en_execution->pid;
    }else if(nb_processus_cree<8){
        struct processus *proc=malloc(sizeof(struct processus));
        proc->pid=nb_processus_cree;
        strcpy(proc->nom,nom);
        proc->etat=ACTIVABLE;
        proc->registre[1]=(int)&proc->pile[511];
        proc->pile[511]=(int)code;
        tab_processus[nb_processus_cree]=proc;
        nb_processus_cree++;
        insertion_queue(proc);
        return proc->pid;
    }else return -1;
}*/

/*--------------------------------------------------------------tp3-Partie3-3--------------------------------------------------------------------------------- */
/*
void ordonnance(){
    if(mon_pid()==0){
        tab_processus[0]->etat=ACTIVABLE;
        tab_processus[1]->etat=ELU;
        proc_en_execution=tab_processus[1];
        ctx_sw((int*)tab_processus[0]->registre, (int*)tab_processus[1]->registre);
    }else if(mon_pid()==1){
        tab_processus[1]->etat=ACTIVABLE;
        tab_processus[2]->etat=ELU;
        proc_en_execution=tab_processus[2];
        ctx_sw((int*)tab_processus[1]->registre, (int*)tab_processus[2]->registre);
    }else if(mon_pid()==2){
        tab_processus[2]->etat=ACTIVABLE;
        tab_processus[3]->etat=ELU;
        proc_en_execution=tab_processus[3];
        ctx_sw((int*)tab_processus[2]->registre, (int*)tab_processus[3]->registre);
    }else if(mon_pid()==3){
        tab_processus[3]->etat=ACTIVABLE;
        tab_processus[4]->etat=ELU;
        proc_en_execution=tab_processus[4];
        ctx_sw((int*)tab_processus[3]->registre, (int*)tab_processus[4]->registre);
    }else if(mon_pid()==4){
        tab_processus[4]->etat=ACTIVABLE;
        tab_processus[5]->etat=ELU;
        proc_en_execution=tab_processus[5];
        ctx_sw((int*)tab_processus[4]->registre, (int*)tab_processus[5]->registre);
    }else if(mon_pid()==5){
        tab_processus[5]->etat=ACTIVABLE;
        tab_processus[6]->etat=ELU;
        proc_en_execution=tab_processus[6];
        ctx_sw((int*)tab_processus[5]->registre, (int*)tab_processus[6]->registre);
    }else if(mon_pid()==6){
        tab_processus[6]->etat=ACTIVABLE;
        tab_processus[7]->etat=ELU;
        proc_en_execution=tab_processus[7];
        ctx_sw((int*)tab_processus[6]->registre, (int*)tab_processus[7]->registre);
    }else if(mon_pid()==7){
        tab_processus[7]->etat=ACTIVABLE;
        tab_processus[0]->etat=ELU;
        proc_en_execution=tab_processus[0];
        //ctx_sw((int*)tab_processus[7]->registre, (int*)tab_processus[0]->registre);
        hlt();
    }
}

void idle(void){
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}
void proc1(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}
void proc2(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}
void proc3(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}
void proc4(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}
void proc5(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}
void proc6(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}
void proc7(void) {
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}

void insertion_queue(struct processus *nouveau){
    nouveau->etat=ACTIVABLE;
    if (tete==NULL){
        tete=nouveau;
        queue=nouveau;
    }else{
        queue->suiv=nouveau;
        nouveau->suiv=NULL;
        queue=nouveau;
    }
}

int32_t cree_processus(void (*code)(void),char* nom){
    if(nb_processus_cree==0){
        struct processus * proc=malloc(sizeof(struct processus));
        proc->pid=nb_processus_cree;
        strcpy(proc->nom,nom);
        proc->etat=ELU;
        tab_processus[nb_processus_cree]=proc;
        nb_processus_cree++;
        proc_en_execution=proc;
        return proc_en_execution->pid;
    }else if(nb_processus_cree<8){
        struct processus *proc=malloc(sizeof(struct processus));
        proc->pid=nb_processus_cree;
        strcpy(proc->nom,nom);
        proc->etat=ACTIVABLE;
        proc->registre[1]=(int)&proc->pile[511];
        proc->pile[511]=(int)code;
        tab_processus[nb_processus_cree]=proc;
        nb_processus_cree++;
        insertion_queue(proc);
        return proc->pid;
    }else return -1;
}
*/

/*--------------------------------------------------------------tp3-Partie3-4--------------------------------------------------------------------------------- */



void insertion_endormi(struct processus *nouveau){
    nouveau->etat=ENDORMI;
    if(endormi==NULL||endormi->heure>nouveau->heure){
        nouveau->suiv=endormi;
        endormi=nouveau;
    }else{
        struct processus* courant=endormi;
        while (courant->suiv!=NULL&&courant->suiv->heure<=nouveau->heure){
            courant=courant->suiv;
        }
        nouveau->suiv=courant->suiv;
        courant->suiv=nouveau;
    }
}

struct processus* extract_tete(){
    struct processus *nouveau_tete=tete->suiv;
    struct processus *tete_actuel=tete;
    tete_actuel->etat=ELU;
    tete=nouveau_tete;
    return tete_actuel;
}

void insertion_queue(struct processus *nouveau){
    nouveau->etat=ACTIVABLE;
    if (tete==NULL){
        tete=nouveau;
        queue=nouveau;
    }else{
        queue->suiv=nouveau;
        nouveau->suiv=NULL;
        queue=nouveau;
    }
}

void ordonnance(){
    int temps=nb_seconde();
    while (endormi!=NULL && endormi->heure==temps)
    {
        struct processus* current=endormi;
        endormi=endormi->suiv;
        insertion_queue(current);
    }
    struct processus* ancien=proc_en_execution;
    if (proc_en_execution->heure==0 && proc_en_execution->etat!=ZOMBIE)
    {
        insertion_queue(proc_en_execution);
    }
    proc_en_execution=extract_tete();
    ctx_sw(ancien->registre,proc_en_execution->registre);
}

void dors(uint32_t nbs_secs){
    proc_en_execution->heure=nbs_secs+nb_seconde();
    insertion_endormi(proc_en_execution);
    ordonnance();
}

void  fin_processus(void){
    proc_en_execution->etat=ZOMBIE;
    struct processus * courrant=zombie;
    if(!zombie){
        zombie=proc_en_execution;
        zombie->suiv=NULL;
    }else{
        while (courrant->suiv!=NULL)
        {
            courrant=courrant->suiv;
        }
        courrant->suiv=proc_en_execution;
        courrant->suiv->suiv=NULL;
    }
    ordonnance();
}
int32_t cree_processus(void (*code)(void),char* nom){
    if(nb_processus_cree==0){
        struct processus * proc=malloc(sizeof(struct processus));
        proc->pid=nb_processus_cree;
        strcpy(proc->nom,nom);
        proc->etat=ELU;
        tab_processus[nb_processus_cree]=proc;
        nb_processus_cree++;
        proc_en_execution=proc;
        return proc_en_execution->pid;
    }else if(nb_processus_cree<8){
        struct processus *proc=malloc(sizeof(struct processus));
        proc->pid=nb_processus_cree;
        strcpy(proc->nom,nom);
        proc->etat=ACTIVABLE;
        proc->registre[1]=(int)&proc->pile[511];
        proc->pile[511]=(int)code;
        tab_processus[nb_processus_cree]=proc;
        nb_processus_cree++;
        insertion_queue(proc);
        return proc->pid;
    }else return -1;
}

void idle(void){
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        sti();
        hlt();
        cli();
    }
}
void proc1(void) {
    for (;;) {
        printf("[temps = %u] processus %s pid = %i\n", nb_seconde(),
        mon_nom(), mon_pid());
        dors(2);
    }
    fin_processus();

}
void proc2(void) {
    for (;;) {
        printf("[temps = %u] processus %s pid = %i\n", nb_seconde(),
        mon_nom(), mon_pid());
        dors(3);
    }
    fin_processus();

}
void proc3(void) {
    for (;;) {
        printf("[temps = %u] processus %s pid = %i\n", nb_seconde(),
        mon_nom(), mon_pid());
        dors(5);
    }
    fin_processus();

}
void proc4(void) {
    for (;;) {
        printf("[temps = %u] processus %s pid = %i\n", nb_seconde(),
        mon_nom(), mon_pid());
        dors(6);
    }
    fin_processus();
}
void proc5(void) {
    for (;;) {
        printf("[temps = %u] processus %s pid = %i\n", nb_seconde(),
        mon_nom(), mon_pid());
        dors(7);
    }
    fin_processus();
}
void proc6(void) {
    for (;;) {
        printf("[temps = %u] processus %s pid = %i\n", nb_seconde(),
        mon_nom(), mon_pid());
        dors(8);
    }
    fin_processus();
}
void proc7(void) {
    for (;;) {
        printf("[temps = %u] processus %s pid = %i\n", nb_seconde(),
        mon_nom(), mon_pid());
        dors(9);
    }
    fin_processus();
}
