#ifndef IGRAC_H
#define IGRAC_H

#define MAKS_DUZINA_IMENA 50
#define POCETNI_BALANS 1000

typedef struct {
	char imeIgraca[MAKS_DUZINA_IMENA];
	double balans;
} Igrac;

extern Igrac* currentPlayer;

Igrac* kreirajIgraca(const char* ime);
void unistiIgraca(Igrac* igrac);
void spremiPodatkeIgraca(const Igrac* igrac);
void ucitajPodatkeIgraca(Igrac* igrac);
void provjeriBalans(const Igrac* igrac);
void obnoviBalans(Igrac* igrac);

#endif // IGRAC_H