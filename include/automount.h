#pragma once

#include "prerequisites.h"

#define SCE_SYSMODULE_AUTO_MOUNT 0xCD

#ifdef __cplusplus
extern "C" {
#endif

struct _SceAutoMounterClientUsbDeviceInfo {
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
	char deviceFilePath[64];
	uint64_t encryptDeviceNgCapability;
	uint32_t encryptDeviceFormat;
	uint32_t encryptDeviceStatus;
	char encryptDeviceFilePath[64];
	uint64_t encryptDeviceId;
	uint32_t fsFormatType;
	uint32_t fsMountStatus;
};
typedef struct _SceAutoMounterClientUsbDeviceInfo SceAutoMounterClientUsbDeviceInfo;

int sceAutoMounterClientInit(uint64_t*);
int sceAutoMounterClientGetUsbDeviceList(char (*)[64], int*);
int sceAutoMounterClientGetUsbDeviceInfo(const char*, SceAutoMounterClientUsbDeviceInfo*);
//int sceAutoMounterClientRegisterCallback(uint32_t, SceAutoMounterClientCallbackFunc, void*);
//int sceAutoMounterClientUnregisterCallback(uint32_t, SceAutoMounterClientCallbackFunc);

#ifdef __cplusplus
}
#endif
