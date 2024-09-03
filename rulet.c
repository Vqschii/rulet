#define _CRT_SECURE_NO_WARNINGS

#include "rulet.h"
#include <stdio.h>
#include <stdlib.h>

static int brojOklada = 0;
static Oklada oklade[100];

inline int validnaOklada(double iznos, double balans) {
    return iznos > 0 && iznos <= balans;
}

int usporediOklade(const void* a, const void* b) {
    Oklada* okladaA = (Oklada*)a;
    Oklada* okladaB = (Oklada*)b;
    return (okladaB->dobitak - okladaA->dobitak);
}

void poloziOkladu(Igrac* igrac, double iznos, VrstaOklade vrstaOklade, int broj, Boja boja, Parnost parnost) {
    while (!validnaOklada(iznos, igrac->balans)) {
        printf("\nNedovoljan balans ili neispravan iznos oklade. Pokušajte ponovo.\n");
        printf("\nUnesite iznos oklade: ");
        scanf("%lf", &iznos);
    }

    Rulet rezultat = zavrtiRulet();
    int pobijedio = 0;
    double dobitak = 0;

    if (vrstaOklade == BROJ && broj == rezultat.broj) {
        pobijedio = 1;
        dobitak = iznos * 35;
    }
    else if (vrstaOklade == BOJA && boja == rezultat.boja) {
        pobijedio = 1;
        dobitak = iznos * 2;
    }
    else if (vrstaOklade == PARNOST && ((parnost == PAR && rezultat.broj % 2 == 0) || (parnost == NEPAR && rezultat.broj % 2 != 0))) {
        pobijedio = 1;
        dobitak = iznos * 2;
    }

    if (pobijedio) {
        printf("\nCestitamo! Pobijedili ste!\n");
        igrac->balans += dobitak - iznos;
    }
    else {
        printf("\nIzgubili ste.\n");
        igrac->balans -= iznos;
    }
    printf("\nTrenutni balans: %.2f\n", igrac->balans);

    oklade[brojOklada].iznos = iznos;
    oklade[brojOklada].dobitak = pobijedio ? dobitak : -iznos;
    brojOklada++;
}

Rulet zavrtiRulet() {
    Rulet rezultat;
    rezultat.broj = rand() % 37;
    if (rezultat.broj == 0) {
        rezultat.boja = ZELENA;
    }
    else if (rezultat.broj % 2 == 0) {
        rezultat.boja = CRNA;
    }
    else {
        rezultat.boja = CRVENA;
    }
    printf("\n\nRezultat: Broj %d, Boja %s\n", rezultat.broj,
        rezultat.boja == CRVENA ? "Crvena" :
        rezultat.boja == CRNA ? "Crna" : "Zelena");
    return rezultat;
}

void prikaziPravila() {
    printf("\nPravila igre Rulet:\n");
    printf("1. Mozete se kladiti na broj (0-36), boju (crvena/crna) ili parnost (par/nepar).\n");
    printf("2. Ako se kladite na broj i pogodite, dobit cete 35 puta veci iznos oklade.\n");
    printf("3. Ako se kladite na boju ili parnost i pogodite, dobit cete dvostruki iznos oklade.\n");
    printf("4. Zelena boja (broj 0) ne spada u crvenu ni crnu boju.\n");
}

Oklada* pretraziOkladu() {
    qsort(oklade, brojOklada, sizeof(Oklada), usporediOklade);

    int trazeniBroj;
    printf("\nUnesite redni broj oklade za pretragu: ");
    if (scanf("%d", &trazeniBroj) != 1 || trazeniBroj < 1 || trazeniBroj > brojOklada) {
        printf("Neispravan unos rednog broja oklade.\n");
        ocistiUnosniBuffer();
        return;
    }

    Oklada* rezultat = bsearch(&oklade[trazeniBroj - 1], oklade, brojOklada, sizeof(Oklada), usporediOklade);
    if (rezultat != NULL) {
        printf("\nNadjena oklada %d: Iznos = %.2f, Dobitak = %.2f\n", trazeniBroj, rezultat->iznos, rezultat->dobitak);
    }
    else {
        printf("\nOklada %d nije pronadjena.\n", trazeniBroj);
    }
}

void dodajOkladu(double iznos, double dobitak) {
    if (brojOklada < 100) {
        oklade[brojOklada].iznos = iznos;
        oklade[brojOklada].dobitak = dobitak;
        brojOklada++;
    }
    else {
        printf("Kapacitet za oklade je pun.\n");
    }
}

void obrisiOkladu(int index) {
    if (index < 0 || index >= brojOklada) {
        printf("Neispravan indeks oklade.\n");
        return;
    }
    for (int i = index; i < brojOklada - 1; i++) {
        oklade[i] = oklade[i + 1];
    }
    brojOklada--;
}

void prikaziOklade() {
    qsort(oklade, brojOklada, sizeof(Oklada), usporediOklade);
    printf("\nSve oklade:\n");
    for (int i = 0; i < brojOklada; i++) {
        printf("Oklada %d: Iznos = %.2f, Dobitak = %.2f\n", i + 1, oklade[i].iznos, oklade[i].dobitak);
    }
}