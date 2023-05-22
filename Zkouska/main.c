
#include "ship.h"


int main() {

	
	tShip* lodInit = init();
	showShip(lodInit);
	transfers(lodInit);
	showShip(lodInit);
	return 0;
}