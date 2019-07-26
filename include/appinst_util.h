#pragma once

#include "prerequisites.h"

#ifdef __cplusplus
extern "C" {
#endif

enum SceAppInstUtilDelete {
	SCE_APP_INST_UTIL_DELETE_PATCH = (1u << 0),
	SCE_APP_INST_UTIL_DELETE_ADDCONT_EXTRA_DATA = (1u << 1),
	SCE_APP_INST_UTIL_DELETE_TEMP_DATA = (1u << 2),
	SCE_APP_INST_UTIL_DELETE_DOWNLOAD_DATA = (1u << 3),
	SCE_APP_INST_UTIL_DELETE_USERS_SAVE_DATA = (1u << 4),
	SCE_APP_INST_UTIL_DELETE_ALL_USERS_SAVE_DATA = (1u << 5),
};

int sceAppInstUtilInitialize(void);
int sceAppInstUtilTerminate(void);

int sceAppInstUtilGetTitleIdFromPkg(const char* pkgPath, char* titleId, int* isApp);
int sceAppInstUtilGetPrimaryAppSlot(const char* titleId, int* slot);

int sceAppInstUtilAppPrepareOverwritePkg(const char* pkgPath);

int sceAppInstUtilAppInstallPkg(const char* pkgPath, void* reserved);

int sceAppInstUtilAppUnInstall(const char* titleId);
int sceAppInstUtilAppUnInstallByUser(const char* titleId, int userId);
int sceAppInstUtilAppUnInstallPat(const char* titleId);
int sceAppInstUtilAppUnInstallTypes(const char* titleId, unsigned int deleteTypes);
int sceAppInstUtilAppUnInstallAddcont(const char* titleId, const char* addcontName);
int sceAppInstUtilAppUnInstallTheme(const char* contentId);

bool sceAppInstUtilAppIsInInstalling(const char* contentId);
int sceAppInstUtilAppIsInUpdating(const char* titleId, int* updating);
bool sceAppInstUtilAppIsInUpdating2(const char* titleId);
int sceAppInstUtilAppExists(const char* titleId, int* exists);
int sceAppInstUtilAppIsInstalledAddcontExist(const char* titleId, bool* exists);
int sceAppInstUtilAppGetSize(const char* titleId, unsigned long* size);

int sceAppInstUtilAppRecoverApp(const char* titleId);

int sceAppInstUtilGetInstallProgress(const char* contentId, unsigned int* progress);
int sceAppInstUtilGetInstallProgressInfo(const char* contentId, unsigned int* state, unsigned int* progress, unsigned long* progressSize, unsigned long* totalSize, unsigned int* restSec);
int sceAppInstUtilGetInstallProgressInfo2(const char* contentId, unsigned int* state, unsigned int* subState, unsigned int* progress, unsigned long* progressSize, unsigned long* totalSize, unsigned int* restSec, char* appVersion);

#ifdef __cplusplus
}
#endif
