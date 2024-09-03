#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void ispisiIzbornik() {
	printf("\n\n\n\n");
	printf("                 *******  ******   *      *  *      ****** ******* *******  ******\n");
	printf("                 *     * *      *  *      *  *      *         *       *     *     \n");
	printf("                 ******* *      *  *      *  *      *         *       *     *     \n");
	printf("                 *   *   *      *  *      *  *      ****      *       *     **** \n");
	printf("                 *    *  *      *  *      *  *      *         *       *     *     \n");
	printf("                 *     *  ******    ******   ****** ******    *       *     ******\n");
	printf("\n\n\n\n");
	printf("                                         1. Polozi okladu\n");
	printf("                                         2. Spremi podatke igraca\n");
	printf("                                         3. Provjeri balans\n");
	printf("                                         4. Prikaz pravila igre\n");
	printf("                                         5. Obnovi balans\n");
	printf("                                         6. Pretrazi rezultate\n");
	printf("                                         7. Dodaj okladu\n");
	printf("                                         8. Obrisi okladu\n");
	printf("                                         9. Prikazi sve oklade\n");
	printf("                                         10. Izlaz\n");
	printf("\n                                       Odaberite opciju: ");
}

void ocistiUnosniBuffer() {
	int znak;
	while ((znak = getchar()) != '\n' && znak != EOF);
}

void obradiGresku(const char* poruka) {
	perror(poruka);
	exit(EXIT_FAILURE);
}

int kopirajDatoteku(const char* izvor, const char* odrediste) {
	FILE* izvorDat = fopen(izvor, "rb");
	if (!izvorDat) {
		return 0;
	}

	FILE* odredisteDat = fopen(odrediste, "wb");
	if (!odredisteDat) {
		fclose(izvorDat);
		return 0;
	}

	char buffer[1024];
	size_t bytesRead;

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), izvorDat)) > 0) {
		fwrite(buffer, 1, bytesRead, odredisteDat);
	}

	fclose(izvorDat);
	fclose(odredisteDat);

	return 1;
}