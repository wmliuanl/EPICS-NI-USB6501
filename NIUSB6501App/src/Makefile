# SPDX-FileCopyrightText: 2003 Argonne National Laboratory
#
# SPDX-License-Identifier: EPICS

TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================


PROD_SYS_LIBS += usb
#=============================
# Build the IOC application

PROD_IOC = NIUSB6501
# NIUSB6501.dbd will be created and installed
DBD += NIUSB6501.dbd

# NIUSB6501.dbd will be made up from these files:
NIUSB6501_DBD += base.dbd
NIUSB6501_DBD += devniusb6501.dbd
# Include dbd files from all support applications:
#NIUSB6501_DBD += xxx.dbd

# Add all the support libraries needed by this IOC
#NIUSB6501_LIBS += xxx

# NIUSB6501_registerRecordDeviceDriver.cpp derives from NIUSB6501.dbd
NIUSB6501_SRCS += NIUSB6501_registerRecordDeviceDriver.cpp
NIUSB6501_SRCS += devniusb6501.c
NIUSB6501_SRCS += niusb6501.cpp

# Build the main IOC entry point on workstation OSs.
NIUSB6501_SRCS_DEFAULT += NIUSB6501Main.cpp
NIUSB6501_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#NIUSB6501_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
NIUSB6501_LIBS += $(EPICS_BASE_IOC_LIBS)


# Link QSRV (pvAccess Server) if available
ifdef EPICS_QSRV_MAJOR_VERSION
    NIUSB6501_LIBS += qsrv
    NIUSB6501_LIBS += $(EPICS_BASE_PVA_CORE_LIBS)
    NIUSB6501_DBD += PVAServerRegister.dbd
    NIUSB6501_DBD += qsrv.dbd
endif

# Finally link IOC to the EPICS Base libraries
AWARPiDIOCtrl_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

