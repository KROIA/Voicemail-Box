#ifndef SDMMC_H
#define SDMMC_H


#include "diskio.h"

DSTATUS MMC_disk_initialize(void);
DSTATUS MMC_disk_status(void);
DRESULT MMC_disk_read(BYTE* buff, DWORD  sector, UINT count);
DRESULT MMC_disk_write(const BYTE* buff, DWORD  sector, UINT count);
DRESULT MMC_disk_ioctl(BYTE cmd, void* buff);


#endif
