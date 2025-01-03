#pragma once

#include "txt.h"

typedef void (*Func)(Txt *txt, void *opt);

void funcQuit(Txt *txt, void *opt);
void funcNormal(Txt *txt, void *opt);
void funcEdit(Txt *txt, void *opt);
void funcPrint(Txt *txt, void *opt);
