/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "sdio.h"
#include "malloc.h"

#define	SD_CARD		0
#define EX_FLASH	1

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	u32	res = 0;

	switch (pdrv) {
		case SD_CARD:
			res = SD_Init();
			if(SD_OK==res)
			{
				res = 0;
			}
			else
			{
				res = 1;
			}
			break;
		case EX_FLASH:
			break;
		default:
			res = 1;
	}
	return res==0?0:STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	u32 res = 0;

	switch (pdrv) {
		case SD_CARD:
			res = SD_ReadDisk(buff, sector, count);
			break;
		case EX_FLASH:
			res = 0;
			break;
		default:
			res = 1;
	}
	return res==0?RES_OK:RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	u32	res = 0;
	u8	retry = 0x1F;
	
	switch (pdrv) {
		case SD_CARD:
			while(retry)
			{
				res = SD_WriteDisk((u8*)buff, sector, count);
				if(0==res)
				{
					break;
				}
				retry--;
			}
			break;
		case EX_FLASH:
			res = 0;
		break;
		default:
			res = 1;
	}
	return res==0?RES_OK:RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	
	if(SD_CARD==pdrv)
	{
		switch(cmd)
		{
			case CTRL_SYNC:
				res = RES_OK;
				break;
			case GET_SECTOR_SIZE:
				*((WORD*)buff) = 512;
				res = RES_OK;
				break;
			case GET_BLOCK_SIZE:
				*((WORD*)buff) = 8;
				res = RES_OK;
				break;
			case GET_SECTOR_COUNT:
				res = RES_OK;
				break;
			default:
				res = RES_PARERR;
		}
	}
	else if(EX_FLASH==pdrv)
	{
	}
	else
	{
		res = RES_PARERR;
	}

	return res;
}
#endif

DWORD get_fattime(void)
{
	return 0;
}

void* ff_memalloc(UINT size)
{
	return (void*)mymalloc(SRAMIN, size);
}

void ff_memfree(void* fm)
{
	myfree(SRAMIN, fm);
}








