/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "../diskio.h"		/* FatFs lower layer API */
#include <emul/emulator.h>
#include <stdio.h>
//#include "usbdisk.h"	/* Example: USB drive control */
//#include "atadrive.h"	/* Example: ATA drive control */
//#include "sdcard.h"		/* Example: MMC/SDC contorl */

/* Definitions of physical drive number for each drive */
#define FLASH	0
#define ATA		1	/* Example: Map ATA drive to drive number 0 */
#define MMC		2	/* Example: Map MMC/SD card to drive number 1 */
#define USB		3	/* Example: Map USB drive to drive number 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	#ifdef DEBUG_DISKIO
	printf("disk_status\n");
	#endif //DEBUG_DISKIO

	if(pdrv != FLASH) return STA_NOINIT;
	else return 0;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	#ifdef DEBUG_DISKIO
	printf("disk_initialize\n");
	#endif //DEBUG_DISKIO

	if(pdrv != FLASH) return STA_NOINIT;
	else return 0;
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
	#ifdef DEBUG_DISKIO
	printf("disk_read\n");	
    printf("pdrv: %d\nsector: %d\ncount: %d\n", pdrv, sector, count);
	#endif //DEBUG_DISKIO

	if(pdrv != FLASH) return RES_ERROR;

	if( storage_read(buff, sector, count) != count ) return RES_ERROR;
	else return RES_OK;
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
	#ifdef DEBUG_DISKIO
	printf("disk_write\n");
	printf("pdrv: %d\nsector: %d\ncount: %d\n", pdrv, sector, count);
	#endif //DEBUG_DISKIO

	if(pdrv != FLASH) return RES_ERROR;

	if( storage_write(buff, sector, count) != count ) return RES_ERROR;
	else return RES_OK;
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
	#ifdef DEBUG_DISKIO
	printf("disk_ioctl %i\n", cmd);
	#endif //DEBUG_DISKIO

	switch (cmd) {
		case CTRL_SYNC:
			break;

		case GET_SECTOR_SIZE:
			*(WORD*)buff = get_storage_sector_size();
			// printf("QUESTION: sector_size\n");
			break;

		case GET_SECTOR_COUNT:
			*(DWORD*)buff = get_storage_sector_count();
			// printf("QUESTION: sector_count\n");
			break;

		case GET_BLOCK_SIZE:
			*(DWORD*)buff = get_storage_block_size();
			// printf("QUESTION: block_size\n");
 			break;
	}

	return RES_OK;
}
#endif

DWORD get_fattime (void){
	#ifdef DEBUG_DISKIO
	printf("get_fattime\n");
	#endif //DEBUG_DISKIO

	return 0;
}
