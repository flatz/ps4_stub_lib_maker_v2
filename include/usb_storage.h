#pragma once

#include "prerequisites.h"

#define SCE_SYSMODULE_USB_STORAGE 0xD5

#ifdef __cplusplus
extern "C" {
#endif

struct _SceUsbStorageDeviceInfo {
	uint64_t totalSpace;
	uint64_t availableSpace;
	uint16_t vendorId;
	uint16_t productId;
	uint16_t bcdDevice;
	char manufacturer[256];
	uint64_t manufacturerLength;
	char product[256];
	uint64_t productLength;
	char serialNumber[256];
	uint64_t serialNumberLength;
	uint64_t additionalFeatures;
	uint64_t capacity;
};
typedef struct _SceUsbStorageDeviceInfo SceUsbStorageDeviceInfo;

//int sceUsbStorageIsExist(uint32_t, const char*);
//int sceUsbStorageRegisterCallback(uint32_t, ...);
//int sceUsbStorageUnregisterCallback(uint32_t, ...);

int sceUsbStorageGetDeviceInfo(uint32_t, SceUsbStorageDeviceInfo*);
int sceUsbStorageGetDeviceList(uint32_t*, int32_t*);
int sceUsbStorageInit(ScePthreadAttr*);
int sceUsbStorageRequestMap(uint32_t, const char*, int32_t, uint64_t, char*, uint64_t*, const void*, size_t);
int sceUsbStorageRequestMapWSB(uint32_t, const char*, int32_t, uint64_t, char*, uint64_t*, const void*, size_t);
int sceUsbStorageRequestUnmap(uint32_t, const char*, const void*, size_t);
int sceUsbStorageTerm();

#ifdef __cplusplus
}
#endif
