#pragma once

#include "prerequisites.h"

#ifdef __cplusplus
extern "C" {
#endif

int sceNpUtilJsonEscape(char* out, size_t max_out_size, const char* in, size_t in_size);
int sceNpUtilJsonUnescape(char* out, size_t max_out_size, const char* in, size_t in_size, unsigned int flags);

#ifdef __cplusplus
}
#endif
