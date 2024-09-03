#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "igrac.h"
#include "util.h"

Igrac* currentPlayer = NULL;

Igrac* kreirajIgraca(const char* ime) {
	Igrac* igrac = (Igrac*)malloc(sizeof(Igrac));
	if (!igrac) {
		obradiGresku("\nNeuspjelo alociranje memorije za igraca.");
		exit(EXIT_FAILURE);
	}
	strncpy(igrac->imeIgraca, ime, MAKS_DUZINA_IMENA - 1);
	igrac->imeIgraca[MAKS_DUZINA_IMENA - 1] = '\0';
	igrac->balans = POCETNI_BALANS;
	return igrac;
}

void unistiIgraca(Igrac* igrac) {
	if (igrac) {
		free(igrac);
		igrac = NULL;
	}
}

void spremiPodatkeIgraca(const Igrac* igrac) {
	const char* tempFile = "temp_podaci_igraca.bin";
	FILE* datoteka = fopen(tempFile, "wb");
	if (!datoteka) {
		obradiGresku("Neuspjelo otvaranje privremene datoteke za pisanje.");
		return;
	}
	if (fwrite(igrac, sizeof(Igrac), 1, datoteka) != 1) {
		fclose(datoteka);
		remove(tempFile);
		obradiGresku("Neuspjelo pisanje podataka igraca u privremenu datoteku.");
		return;
	}
	fclose(datoteka);

	remove("podaci_igraca.bin");
	rename(tempFile, "podaci_igraca.bin");
}

void ucitajPodatkeIgraca(Igrac* igrac) {
	FILE* datoteka = fopen("podaci_igraca.bin", "rb");
	if (!datoteka) {
		return;
	}

	fseek(datoteka, 0, SEEK_END);
	long velicinaDatoteke = ftell(datoteka);
	fseek(datoteka, 0, SEEK_SET);

	if (velicinaDatoteke == 0) {
		printf("Datoteka je prazna. Inicijalizacija igraca s pocetnim balansom.\n");
		igrac->balans = POCETNI_BALANS;
	}
	else {
		if (fread(igrac, sizeof(Igrac), 1, datoteka) != 1) {
			obradiGresku("Neuspjelo citanje podataka igraca iz datoteke.");
		}
	}

	fclose(datoteka);
}

void provjeriBalans(const Igrac* igrac) {
	printf("Trenutni balans: %.2f\n", igrac->balans);
}

void obnoviBalans(Igrac* igrac) {
	double iznos;
	printf("\nUnesite iznos za obnovu balansa: ");
	if (scanf("%lf", &iznos) == 1 && iznos > 0) {
		igrac->balans += iznos;
		printf("Balans je uspjesno obnovljen. Novi balans: %.2f\n", igrac->balans);
	}
	else {
		printf("Neispravan iznos.\n");
		ocistiUnosniBuffer();
	}
}