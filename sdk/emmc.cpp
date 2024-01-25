#include "emmc.hpp"



bool_t isCardInTheSocket(void)
{
	bool_t   ret;
	uint32_t statusReg;

	statusReg = XSdPs_GetPresentStatusReg(SD_BASEADDR);

	ret = CARD_INSERTED(statusReg);

	return ret;
}

bool_t isCardWriteProtected(void)
{
	bool_t   ret;
	uint32_t statusReg;

	statusReg = XSdPs_GetPresentStatusReg(SD_BASEADDR);

	ret = WRITE_PROTECTED(statusReg);

	return ret;
}

bool_t xilSdInit(void)
{
	bool_t ret = TRUE;

	uint32_t status;
	XSdPs *sdInstPtr = &gXilSdPsInst;
	XSdPs_Config *ConfigPtr;

	//Check if it is possible to write in card (card must be inserted)

	//Write enable can also be checked if it is routed on HW
	if(isCardInTheSocket() != TRUE)
	{
		xil_printf("SD device is not inserted", NULL);
		return FALSE;
	}

	/*
	 * If card can be written, controller is initialized
	 */
	ConfigPtr = XSdPs_LookupConfig(SD_DEVICE_ID);
	if (ConfigPtr == NULL)
	{
		xil_printf("SD device does not exist", NULL);
		ret = FALSE;
	}

	status = XSdPs_CfgInitialize(sdInstPtr, ConfigPtr, ConfigPtr->BaseAddress);
	if (status != XST_SUCCESS)
	{
		xil_printf("SD controller could not be initialized", NULL);
		ret = FALSE;
	}

	status = XSdPs_CardInitialize(sdInstPtr);
	if(status != XST_SUCCESS)
	{
		xil_printf("SD card could not be initialized", NULL);
		ret = FALSE;
	}

	return ret;

}

u32 xilSdWrite(uint8_t* buff, uint32_t blkId, uint32_t numBlks)
{
	XSdPs *sdInstPtr = &gXilSdPsInst;
	uint32_t statusReg;
	xilSDResult_t ret;

	statusReg = XSdPs_WritePolled(sdInstPtr,blkId, numBlks, buff);

	return statusReg;
}

u32 xilSdRead(uint8_t* buff, uint32_t blkId, uint32_t numBlks)
{
	XSdPs *sdInstPtr = &gXilSdPsInst;
	uint32_t statusReg;
	xilSDResult_t ret;

	statusReg = XSdPs_ReadPolled(sdInstPtr,blkId, numBlks, buff);


	return statusReg;
}
