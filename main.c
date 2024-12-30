#include "txt.h"

int main(void) {

	Txt txt = {0};

	/* initialisation */
	{
		int ret = initialiseTxt(&txt);
		switch (ret) {
		case 0:
			break;
		case -1: // newWindow failed.
		case -2: // newShader failed.
		case -3: // newTexture failed.
		default:
			logRet(ret, "initialiseTxt");
			return -1;
		}
	}

	runTxt(&txt);

	shutdownTxt(&txt);

	return 0;
}
