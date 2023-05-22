#include "ship.h"

tShip* init() {
	tShip* lod = (tShip*)malloc(sizeof(tShip));
	FILE* file = fopen("init.csv", "r");
	if (file == NULL) {
		printf("chyba pri otevirani souboru init.csv v metode init()");
		return NULL;
	}

	char line[256];
	char znak;

	for (size_t i = 0; i < N; i++) {
		lod->countStack[i] = 0;  // inicializace poèítadla zásobníku na 0
	}

	for (size_t i = 0; i < N; i++) {
		if (fgets(line, sizeof(line), file) != NULL) {
			char* token = strtok(line, ";");
			while (token != NULL) {
				sscanf(token, "%c", &znak);
				lod->stack[i][lod->countStack[i]] = znak;  // pøidání znaku do zásobníku
				lod->countStack[i]++;  // zvýšení poèítadla zásobníku
				token = strtok(NULL, ";");
			}
		}
	}


	fclose(file);

	return lod;
}

//vypise a vrati aktualni stav lodi
void showShip(tShip* ship) {
	for (size_t i = 0; i < N; i++)
	{
		printf("\nstack %d:\n", i);
		for (size_t j = 0; j < ship->countStack[i]; j++)
		{
			printf("%c\t", ship->stack[i][j]);
		}
		printf("\n");
	}
}

// presune zasoby na lodi podle souboru transfer.csv
void transfers(tShip* ship) {
    FILE* fileTrans = fopen("transfer.csv", "r");
    if (fileTrans == NULL) {
        printf("Chyba pri otevirani souboru transfers.csv v metode transfers");
        return;
    }
    char line[256];
    if (fgets(line, 256, fileTrans) == NULL)
    {
        printf("chyba pri cteni hlavy souboru transfer.csv");
        return;
    }
    int count = 0;
    int from = 0;
    int to = 0;

    while (fgets(line, 256, fileTrans) != NULL)
    {
        sscanf(line, "%d;%d;%d", &count, &from, &to);
        from = from - 1;
        to = to - 1;

        // ovìøení, zda je možné provést pøesun
        if (count > ship->countStack[from]) {
            printf("Nejsou dostatecne zasoby na presun.\n");
            continue;
        }

        // pøesun zásob
        for (int i = 0; i < count; i++) {
            int fromIndex = ship->countStack[from] - 1; // index posledního prvku v zásobníku "from"
            int toIndex = ship->countStack[to]; // index, kde se má uložit prvek v zásobníku "to"
            ship->stack[to][toIndex] = ship->stack[from][fromIndex];  // pøesun prvkù
            ship->stack[from][fromIndex] = '\0';  // vymazání pøesunutého prvku
            ship->countStack[from]--;  // snížení poèítadla v zásobníku "from"
            ship->countStack[to]++;  // zvýšení poèítadla v zásobníku "to"
        }
    }
    fclose(fileTrans);
}
