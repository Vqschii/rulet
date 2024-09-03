#ifndef RULET_H
#define RULET_H

#include "igrac.h"

typedef enum {
    OPCIJA_IGRAJ = 1,
    OPCIJA_SPREMI_PODATKE,
    OPCIJA_PROVJERI_BALANS,
    OPCIJA_PRIKAZI_PRAVILA,
    OPCIJA_OBNOVI_BALANS,
    OPCIJA_PRETRAZI_OKLADE,
    OPCIJA_DODAJ_OKLADE,
    OPCIJA_OBRISI_OKLADE,
    OPCIJA_PRIKAZI_OKLADE,
    OPCIJA_IZLAZ
} MenuOpcija;
typedef enum {
    CRVENA,
    CRNA,
    ZELENA
} Boja;

typedef enum {
    BROJ,
    BOJA,
    PARNOST
} VrstaOklade;

typedef enum {
    PAR,
    NEPAR
} Parnost;

typedef struct {
    int broj;
    Boja boja;
} Rulet;

typedef struct {
    double iznos;
    double dobitak;
} Oklada;

void poloziOkladu(Igrac* igrac, double iznos, VrstaOklade vrstaOklade, int broj, Boja boja, Parnost parnost);
Rulet zavrtiRulet();
void prikaziPravila();
Oklada* pretraziOkladu(int brojOklade);
void dodajOkladu(double iznos, double dobitak);
void obrisiOkladu(int index);
void prikaziOklade();

#endif // RULET_H