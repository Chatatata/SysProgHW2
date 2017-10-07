#ifndef TEST_HELPERS_DECL
#define TEST_HELPERS_DECL

#include <stdio.h>

#define X_DESCRIBE(desc) printf("\e[34m\e[1mcontext:\e[0m '%s'\n\e[39m", desc);
#define X_IT(desc) printf("  \e[32m%s\e[39m  %s\n", "\u2713", desc);

#endif

