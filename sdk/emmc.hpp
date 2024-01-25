#pragma once
#include "xparameters.h"
#include "xsdps.h"

#include <stdio.h>

typedef unsigned char bool_t;

typedef enum xilSDResult
{
	XILSD_SUCCESS = 0,
	XILSD_NO_CARD,
	XILSD_WRITE_PROTECTION,
	XILSD_ERR_WRITING,
	XILSD_ERR_READING
} xilSDResult_t;

#define SD_DEVICE_ID    XPAR_XSDPS_0_DEVICE_ID
#define SD_BASEADDR     XPAR_PS7_SD_1_BASEADDR
#define SD_CLK_FREQ_HZ  XPAR_PS7_SD_1_SDIO_CLK_FREQ_HZ

#define CARD_INSERTED(a) ((a & XSDPS_PSR_CARD_INSRT_MASK) >> 16) ? TRUE : FALSE
#define WRITE_PROTECTED(a) ((a & XSDPS_PSR_WPS_PL_MASK) >> 18) ? TRUE :FALSE

static XSdPs gXilSdPsInst;

bool_t isCardInTheSocket(void);
bool_t isCardWriteProtected(void);
bool_t xilSdInit(void);
u32 xilSdWrite(uint8_t* buff, uint32_t blkId, uint32_t numBlks);
u32 xilSdRead(uint8_t* buff, uint32_t blkId, uint32_t numBlks);
