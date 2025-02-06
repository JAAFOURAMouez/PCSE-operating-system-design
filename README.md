# **Conception d'un Noyau de Système d'Exploitation**  

Ce projet consiste en la conception et l'implémentation d'un noyau de système d'exploitation simplifié, développé dans le cadre du cours "Projet de conception de systèmes d'exploitation - fondements". Le noyau gère les processus, les interruptions, l'ordonnancement, et l'affichage en mode texte CGA.

## 🚀 **Fonctionnalités**  
✅ Gestion des interruptions (horloge, clavier, etc.)  
✅ Ordonnancement des processus avec l'algorithme Round-Robin  
✅ Gestion de l'écran en mode texte CGA (80x25)  
✅ Création et terminaison de processus  
✅ Endormissement des processus avec un mécanisme de type `sleep`  
✅ Gestion dynamique de la mémoire pour les processus  

## 🛠️ **Technologies utilisées**  
- **Langage** : C et assembleur (x86)  
- **Mode d'affichage** : Mode texte CGA (Color Graphics Adapter)  
- **Gestion des interruptions** : Utilisation de l'IDT (Interrupt Descriptor Table)  
- **Ordonnancement** : Algorithme Round-Robin avec gestion des processus actifs et endormis  
- **Gestion de la mémoire** : Allocation dynamique avec `malloc` via `tinyalloc`  
## 🔧 **Installation et exécution**
### Prérequis
- **Compilateur** : GCC pour le C et NASM pour l'assembleur.

- **Émulateur** : QEMU pour exécuter le noyau.

- **Système** : Environnement Linux recommandé.

### Compilation et exécution
Clonez le dépôt :

```bash
git clone 
```
Compilez le noyau :

bash
Copy
make
Exécutez le noyau dans QEMU :

bash
Copy
make run
📝 Fonctionnalités détaillées
Gestion des interruptions
Horloge : Utilisation du PIT (Programmable Interval Timer) pour générer des interruptions périodiques.

Clavier : Gestion des entrées clavier via les interruptions IRQ1.

IDT : Initialisation de la table des vecteurs d'interruption pour gérer les interruptions matérielles.

Ordonnancement des processus
Round-Robin : Chaque processus reçoit un temps d'exécution fixe avant de passer la main au suivant.

Changement de contexte : Sauvegarde et restauration des registres du processeur lors du passage d'un processus à un autre.

Processus endormis : Gestion des processus en attente avec un mécanisme de type sleep.

Gestion de l'écran
Mode texte CGA : Affichage de caractères en 80 colonnes et 25 lignes.

Curseur : Gestion du curseur clignotant pour indiquer la position d'écriture.

Couleurs : Support des 16 couleurs de texte et 8 couleurs de fond.

Gestion des processus
Création : Création dynamique de processus avec allocation de mémoire.

Terminaison : Terminaison explicite ou automatique des processus.

Recyclage : Réutilisation des structures de processus terminés (zombies).

📌 Améliorations possibles
Priorités : Implémentation d'un système de priorités pour les processus.

Synchronisation : Ajout de primitives de synchronisation (sémaphores, mutex).

Système de fichiers : Intégration d'un système de fichiers minimaliste.

Multicœur : Support des processeurs multicœurs pour un véritable parallélisme.

📚 Documentation
Pour plus de détails sur l'implémentation, consultez les fichiers PDF fournis :

projet_pit.pdf : Gestion du temps et des interruptions.

projet_ecran.pdf : Gestion de l'écran en mode CGA.

projet_processus.pdf : Gestion des processus et ordonnancement.

