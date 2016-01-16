/* Revision: 2.7.3 */

/******************************************************************************
* Copyright 1998-2015 NetBurner, Inc.  ALL RIGHTS RESERVED
*
*    Permission is hereby granted to purchasers of NetBurner Hardware to use or
*    modify this computer program for any use as long as the resultant program
*    is only executed on NetBurner provided hardware.
*
*    No other rights to use this program or its derivatives in part or in
*    whole are granted.
*
*    It may be possible to license this or other NetBurner software for use on
*    non-NetBurner Hardware. Contact sales@Netburner.com for more information.
*
*    NetBurner makes no representation or warranties with respect to the
*    performance of this computer program, and specifically disclaims any
*    responsibility for any damages, special or consequential, connected with
*    the use of this program.
*
* NetBurner
* 5405 Morehouse Dr.
* San Diego, CA 92121
* www.netburner.com
******************************************************************************/

#include <effs_fat/ramdrv_f.h>

#ifdef __cplusplus
extern "C" {
#endif

const uint32_t RAMDRV0_SIZE = 0x8000;
const uint32_t RAMDRV1_SIZE = 0x0;

char ramdrv0[RAMDRV0_SIZE];
char ramdrv1[RAMDRV1_SIZE];

F_DRIVER t_drivers[RAMDRV_CNT];

t_RamDrv RamDrv[RAMDRV_CNT] = {
  { ramdrv0, (RAMDRV0_SIZE/F_SECTOR_SIZE), 0, &t_drivers[0] },
  { ramdrv1, (RAMDRV1_SIZE/F_SECTOR_SIZE), 0, &t_drivers[1] },
};

#ifdef __cplusplus
}
#endif
