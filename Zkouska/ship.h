#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3

typedef struct{
	char stack[N][20];
	int countStack[N];
}tShip;

// naète vychozi stav zasob na lodi dle souboru init.csv
tShip* init();

void showShip(tShip* ship);

void transfers(tShip* ship);
