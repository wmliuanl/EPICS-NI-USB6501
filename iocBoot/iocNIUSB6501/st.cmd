#!../../bin/linux-aarch64/NIUSB6501

#- SPDX-FileCopyrightText: 2005 Argonne National Laboratory
#-
#- SPDX-License-Identifier: EPICS

#- You may have to change NIUSB6501 to something else
#- everywhere it appears in this file

< envPaths

## Register all support components
dbLoadDatabase "../../dbd/NIUSB6501.dbd"
NIUSB6501_registerRecordDeviceDriver(pdbbase) 

## Load record instances
dbLoadRecords("../../db/NIUSB6501.db","IOCName=RPi")
dbLoadRecords("../../db/NIUSB6501_RB.db","IOCName=RPi")

iocInit()

## Start any sequence programs
#seq sncNIUSB6501,"user=${USER}"
