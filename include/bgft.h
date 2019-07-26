#pragma once

#include "prerequisites.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_BGFT_ERROR_SAME_APPLICATION_ALREADY_INSTALLED (0x80990088)

typedef int SceBgftTaskId;

enum _SceBgftTaskSubType {
	SCE_BGFT_TASK_SUB_TYPE_UNKNOWN = 0,
	SCE_BGFT_TASK_SUB_TYPE_PHOTO = 1,
	SCE_BGFT_TASK_SUB_TYPE_MUSIC = 2,
	SCE_BGFT_TASK_SUB_TYPE_VIDEO = 3,
	SCE_BGFT_TASK_SUB_TYPE_MARLIN_VIDEO = 4,
	SCE_BGFT_TASK_SUB_TYPE_UPDATA_ORBIS = 5,
	SCE_BGFT_TASK_SUB_TYPE_GAME = 6,
	SCE_BGFT_TASK_SUB_TYPE_GAME_AC = 7,
	SCE_BGFT_TASK_SUB_TYPE_GAME_PATCH = 8,
	SCE_BGFT_TASK_SUB_TYPE_GAME_LICENSE = 9,
	SCE_BGFT_TASK_SUB_TYPE_SAVE_DATA = 10,
	SCE_BGFT_TASK_SUB_TYPE_CRASH_REPORT = 11,
	SCE_BGFT_TASK_SUB_TYPE_PACKAGE = 12,
	SCE_BGFT_TASK_SUB_TYPE_MAX = 13,
};
typedef enum _SceBgftTaskSubType SceBgftTaskSubType;

enum _SceBgftTaskOpt {
	SCE_BGFT_TASK_OPT_NONE = 0x0,
	SCE_BGFT_TASK_OPT_DELETE_AFTER_UPLOAD = 0x1,
	SCE_BGFT_TASK_OPT_INVISIBLE = 0x2,
	SCE_BGFT_TASK_OPT_ENABLE_PLAYGO = 0x4,
	SCE_BGFT_TASK_OPT_FORCE_UPDATE = 0x8,
	SCE_BGFT_TASK_OPT_REMOTE = 0x10,
	SCE_BGFT_TASK_OPT_COPY_CRASH_REPORT_FILES = 0x20,
	SCE_BGFT_TASK_OPT_DISABLE_INSERT_POPUP = 0x40,
	SCE_BGFT_TASK_OPT_INTERNAL = 0x80, /* ignores release date */
	SCE_BGFT_TASK_OPT_DISABLE_CDN_QUERY_PARAM = 0x10000,
};
typedef enum _SceBgftTaskOpt SceBgftTaskOpt;

struct _SceBgftDownloadRegisterErrorInfo {
	/* TODO */
	uint8_t buf[0x100];
};
typedef struct _SceBgftDownloadRegisterErrorInfo SceBgftDownloadRegisterErrorInfo;

struct _SceBgftDownloadParam {
	int userId;
	int entitlementType;
	const char* id; /* max size = 0x30 */
	const char* contentUrl; /* max size = 0x800 */
	const char* contentExUrl;
	const char* contentName; /* max size = 0x259 */
	const char* iconPath; /* max size = 0x800 */
	const char* skuId;
	SceBgftTaskOpt option;
	const char* playgoScenarioId;
	const char* releaseDate;
	const char* packageType;
	const char* packageSubType;
	unsigned long packageSize;
};
typedef struct _SceBgftDownloadParam SceBgftDownloadParam;

struct _SceBgftDownloadParamEx {
	SceBgftDownloadParam params;
	unsigned int slot;
};
typedef struct _SceBgftDownloadParamEx SceBgftDownloadParamEx;

struct _SceBgftDownloadTaskInfo {
	char* contentTitle;
	char* iconPath;
	unsigned long notificationUtcTick;
};
typedef struct _SceBgftDownloadTaskInfo SceBgftDownloadTaskInfo;

struct _SceBgftTaskProgress {
	unsigned int bits;
	int errorResult;
	unsigned long length;
	unsigned long transferred;
	unsigned long lengthTotal;
	unsigned long transferredTotal;
	unsigned int numIndex;
	unsigned int numTotal;
	unsigned int restSec;
	unsigned int restSecTotal;
	int preparingPercent;
	int localCopyPercent;
};
typedef struct _SceBgftTaskProgress SceBgftTaskProgress;

struct _SceBgftInitParams {
	void* heap;
	size_t heapSize;
};
typedef struct _SceBgftInitParams SceBgftInitParams;

#define SCE_BGFT_INVALID_TASK_ID (-1)

int sceBgftServiceInit(SceBgftInitParams* params);
int sceBgftServiceTerm(void);

int sceBgftServiceDownloadFindTaskByContentId(const char* contentId, SceBgftTaskSubType subType, SceBgftTaskId* taskId);
int sceBgftServiceDownloadFindActivePatchTask(const char* unk, SceBgftTaskId* taskId);
int sceBgftServiceDownloadFindActivePupTask(SceBgftTaskId* taskId);

int sceBgftServiceDownloadStartTask(SceBgftTaskId taskId);
int sceBgftServiceDownloadStartTaskAll(void);
int sceBgftServiceDownloadPauseTask(SceBgftTaskId taskId);
int sceBgftServiceDownloadPauseTaskAll(void);
int sceBgftServiceDownloadResumeTask(SceBgftTaskId taskId);
int sceBgftServiceDownloadResumeTaskAll(void);
int sceBgftServiceDownloadStopTask(SceBgftTaskId taskId);
int sceBgftServiceDownloadStopTaskAll(void);

int sceBgftServiceDownloadGetProgress(SceBgftTaskId taskId, SceBgftTaskProgress* progress);

int sceBgftInitialize(SceBgftInitParams* params);
int sceBgftFinalize(void);

int sceBgftDownloadRegisterTask(SceBgftDownloadParam* params, SceBgftTaskId* taskId);
int sceBgftDownloadRegisterTaskByStorageEx(SceBgftDownloadParamEx* params, SceBgftTaskId* taskId);
int sceBgftDownloadRegisterTaskStoreWithErrorInfo(SceBgftDownloadParam* params, SceBgftTaskId* taskId, SceBgftDownloadRegisterErrorInfo* errorInfo);
int sceBgftDownloadUnregisterTask(SceBgftTaskId taskId);
int sceBgftDownloadReregisterTaskPatch(SceBgftTaskId oldTaskId, SceBgftTaskId* newTaskId);

int sceBgftDownloadStartTask(SceBgftTaskId taskId);
int sceBgftDownloadStopTask(SceBgftTaskId taskId);
int sceBgftDownloadPauseTask(SceBgftTaskId taskId);
int sceBgftDownloadResumeTask(SceBgftTaskId taskId);

int sceBgftDownloadGetTaskInfo(SceBgftTaskId taskId, SceBgftDownloadTaskInfo* taskInfo);

int sceBgftDownloadGetProgress(SceBgftTaskId taskId, SceBgftTaskProgress* progress);
int sceBgftDownloadGetPatchProgress(const char* contentId, SceBgftTaskProgress* progress);
int sceBgftDownloadGetPlayGoProgress(const char* contentId, SceBgftTaskProgress* progress);
int sceBgftDownloadGetGameAndGameAcProgress(const char* contentId, SceBgftTaskProgress* progress);

int sceBgftDownloadFindActiveGameAndGameAcTask(const char* contentId, SceBgftTaskId* taskId);
int sceBgftDownloadFindActiveTask(const char* contentId, SceBgftTaskSubType subType, SceBgftTaskId* taskId);

int sceBgftDebugDownloadRegisterPkg(SceBgftDownloadParam* params, SceBgftTaskId* taskId);

#ifdef __cplusplus
}
#endif
