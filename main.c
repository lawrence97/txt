#include "txt.h"

int main(void) {

	Txt txt;

	if (initialiseTxt(&txt) < 0) {
		return -1;
	}

	runTxt(&txt);
	shutdownTxt(&txt);

	return 0;
}
