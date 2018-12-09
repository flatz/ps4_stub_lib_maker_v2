#include <kernel_ex.h>

#include <stdlib.h>
#include <string.h>

int sceKernelGetModuleInfo(SceKernelModule handle, SceKernelModuleInfo* info) {
	int ret;

	if (!info) {
		ret = SCE_KERNEL_ERROR_EFAULT;
		goto err;
	}

	memset(info, 0, sizeof(*info));
	{
		info->size = sizeof(*info);
	}

	ret = syscall(SYS_dynlib_get_info, handle, info); /* TODO: make proper error code */

err:
	return ret;
}

int sceKernelGetModuleInfoByName(const char* name, SceKernelModuleInfo* info) {
	SceKernelModuleInfo tmpInfo;
	SceKernelModule handles[SCE_KERNEL_MAX_MODULES];
	size_t numModules;
	size_t i;
	int ret;

	if (!name) {
		ret = SCE_KERNEL_ERROR_EFAULT;
		goto err;
	}
	if (!info) {
		ret = SCE_KERNEL_ERROR_EFAULT;
		goto err;
	}

	memset(handles, 0, sizeof(handles));

	ret = sceKernelGetModuleList(handles, ARRAY_SIZE(handles), &numModules);
	if (ret) {
		goto err;
	}

	for (i = 0; i < numModules; ++i) {
		ret = sceKernelGetModuleInfo(handles[i], &tmpInfo);
		if (ret) {
			goto err;
		}

		if (strcmp(tmpInfo.name, name) == 0) {
			memcpy(info, &tmpInfo, sizeof(tmpInfo));
			ret = 0;
			goto err;
		}
	}

	ret = SCE_KERNEL_ERROR_ENOENT;

err:
	return ret;
}

int sceKernelGetModuleInfoEx(SceKernelModule handle, SceKernelModuleInfoEx* info) {
	int ret;

	if (!info) {
		ret = SCE_KERNEL_ERROR_EFAULT;
		goto err;
	}

	memset(info, 0, sizeof(*info));
	{
		info->size = sizeof(*info);
	}

	ret = syscall(SYS_dynlib_get_info_ex, handle, info); /* TODO: make proper error code */

err:
	return ret;
}

int sceKernelGetModuleInfoExByName(const char* name, SceKernelModuleInfoEx* info) {
	SceKernelModuleInfoEx tmpInfo;
	SceKernelModule handles[SCE_KERNEL_MAX_MODULES];
	size_t numModules;
	size_t i;
	int ret;

	if (!name) {
		ret = SCE_KERNEL_ERROR_EFAULT;
		goto err;
	}
	if (!info) {
		ret = SCE_KERNEL_ERROR_EFAULT;
		goto err;
	}

	memset(handles, 0, sizeof(handles));

	ret = sceKernelGetModuleList(handles, ARRAY_SIZE(handles), &numModules);
	if (ret) {
		goto err;
	}

	for (i = 0; i < numModules; ++i) {
		ret = sceKernelGetModuleInfoEx(handles[i], &tmpInfo);
		if (ret) {
			goto err;
		}

		if (strcmp(tmpInfo.name, name) == 0) {
			memcpy(info, &tmpInfo, sizeof(tmpInfo));
			ret = 0;
			goto err;
		}
	}

	ret = SCE_KERNEL_ERROR_ENOENT;

err:
	return ret;
}
