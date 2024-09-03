#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "igrac.h"
#include "rulet.h"
#include "util.h"

int main() {
    srand((unsigned int)time(NULL));

    currentPlayer = kreirajIgraca("Defaultni_Igrac");
    ucitajPodatkeIgraca(currentPlayer);
    MenuOpcija opcija = OPCIJA_IZLAZ;

    while (1) {
        ispisiIzbornik();
        if (scanf("%d", &opcija) != 1) {
            ocistiUnosniBuffer();
            continue;
        }

        switch (opcija) {
        case OPCIJA_IGRAJ: {
            double iznosOklade;
            while (1) {
                printf("\nUnesite iznos oklade: ");
                if (scanf("%lf", &iznosOklade) == 1) {
                    if (iznosOklade > 0 && iznosOklade <= currentPlayer->balans) {
                        break;
                    }
                    else {
                        printf("Neispravan iznos oklade. Pokušajte ponovo.\n");
                    }
                }
                else {
                    ocistiUnosniBuffer();
                    printf("Neispravan unos. Pokušajte ponovo.\n");
                }
            }

            int vrstaOklade;
            printf("\nOdaberite vrstu oklade (0 za broj, 1 za boju, 2 za parnost): ");
            if (scanf("%d", &vrstaOklade) == 1) {
                if (vrstaOklade == BROJ) {
                    int broj;
                    printf("\nUnesite broj (0-36): ");
                    do {
                        scanf("%d", &broj);
                    } while (broj < 0 || broj > 36);

                    poloziOkladu(currentPlayer, iznosOklade, BROJ, broj, ZELENA, PAR);
                }
                else if (vrstaOklade == BOJA) {
                    int boja;
                    printf("\nOdaberite boju (0 za crvenu, 1 za crnu): ");
                    do {
                        scanf("%d", &boja);
                    } while (boja > 1 || boja < 0);

                    poloziOkladu(currentPlayer, iznosOklade, BOJA, -1, boja, PAR);
                }
                else if (vrstaOklade == PARNOST) {
                    int parnost;
                    printf("\nOdaberite parnost (0 za parne, 1 za neparne): ");
                    if (scanf("%d", &parnost) == 1 && (parnost == PAR || parnost == NEPAR)) {
                        poloziOkladu(currentPlayer, iznosOklade, PARNOST, -1, ZELENA, parnost);
                    }
                    else {
                        printf("\nNeispravna parnost.\n");
                        ocistiUnosniBuffer();
                    }
                }
                else {
                    printf("\nNeispravna vrsta oklade.\n");
                    ocistiUnosniBuffer();
                }
            }
            else {
                ocistiUnosniBuffer();
            }
            break;
        }
        case OPCIJA_SPREMI_PODATKE:
            spremiPodatkeIgraca(currentPlayer);
            printf("\nPodaci igraca su spremljeni.\n");
            break;
        case OPCIJA_PROVJERI_BALANS:
            provjeriBalans(currentPlayer);
            break;
        case OPCIJA_PRIKAZI_PRAVILA:
            prikaziPravila();
            break;
        case OPCIJA_OBNOVI_BALANS:
            obnoviBalans(currentPlayer);
            break;
        case OPCIJA_IZLAZ:
            printf("\nDovidenja!\n");
            spremiPodatkeIgraca(currentPlayer);
            unistiIgraca(currentPlayer);
            return 0;
        case OPCIJA_PRETRAZI_OKLADE:
            pretraziOkladu(currentPlayer);
            break;
        case OPCIJA_DODAJ_OKLADE:
        {
            double iznos;
            double dobitak;
            printf("\nUnesite iznos oklade: ");
            if (scanf("%lf", &iznos) == 1 && iznos > 0) {
                printf("Unesite dobitak: ");
                if (scanf("%lf", &dobitak) == 1) {
                    dodajOkladu(iznos, dobitak);
                    printf("Oklada dodana.\n");
                }
                else {
                    printf("Neispravan unos za dobitak.\n");
                    ocistiUnosniBuffer();
                }
            }
            else {
                printf("Neispravan unos za iznos oklade.\n");
                ocistiUnosniBuffer();
            }
        }
        break;
        case OPCIJA_OBRISI_OKLADE:
        {
            int index;
            printf("\nUnesite indeks oklade za brisanje: ");
            if (scanf("%d", &index) == 1) {
                obrisiOkladu(index - 1);
                printf("Oklada obrisana.\n");
            }
            else {
                printf("Neispravan unos za indeks.\n");
                ocistiUnosniBuffer();
            }
        }
        break;
        case OPCIJA_PRIKAZI_OKLADE:
            prikaziOklade();
            break;
        default:
            printf("\nNeispravna opcija. Pokusajte ponovo.\n");
        }
    }
}