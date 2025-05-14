/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
 * \addtogroup ECATSlave ECATSlave
 * @{
 */

/**
\file ECATSlave.h
\brief ECATSlave function prototypes and defines

\version 1.0.0.11
 */

 
 #ifndef _ECATSLAVE_H_
#define _ECATSLAVE_H_


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"

#include "ecatappl.h"

/*-----------------------------------------------------------------------------------------
------
------    Defines and Types
------
-----------------------------------------------------------------------------------------*/

#endif //_ECATSLAVE_H_

//include custom application object dictionary 
#include "ECATSlaveObjects.h"


#if defined(_ECATSLAVE_) && (_ECATSLAVE_ == 1)
    #define PROTO
#else
    #define PROTO extern
#endif

#pragma pack(1)	  // 使结构体的 1 字节对齐
/* TPDO结构体 */
typedef struct
{
	UINT8 button_1_2;
	UINT8 padding;
} _tpdo1A00_t;	

/* RPDO结构体 */
typedef struct
{
	UINT8 LED_1_2;
	UINT8 padding;
} _rpdo1600_t;	
#pragma pack()	// 取消自定义字节对齐

PROTO void APPL_Application(void);
#if EXPLICIT_DEVICE_ID
PROTO UINT16 APPL_GetDeviceID(void);
#endif

PROTO void   APPL_AckErrorInd(UINT16 stateTrans);
PROTO UINT16 APPL_StartMailboxHandler(void);
PROTO UINT16 APPL_StopMailboxHandler(void);
PROTO UINT16 APPL_StartInputHandler(UINT16 *pIntMask);
PROTO UINT16 APPL_StopInputHandler(void);
PROTO UINT16 APPL_StartOutputHandler(void);
PROTO UINT16 APPL_StopOutputHandler(void);

PROTO UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize);
PROTO void APPL_InputMapping(UINT16* pData);
PROTO void APPL_OutputMapping(UINT16* pData);

#undef PROTO
/** @}*/

