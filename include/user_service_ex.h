#pragma once

#include "prerequisites.h"

#include <user_service.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceUserServiceGetForegroundUser(int* user_id);

#ifdef __cplusplus
}
#endif
