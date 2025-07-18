/*!
    \file    gd32c11x_dbg.h
    \brief   definitions for the DBG
    
    \version 2023-12-31, V1.2.0, firmware for GD32C11x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef GD32C11X_DBG_H
#define GD32C11X_DBG_H

#include "gd32c11x.h"

/* DBG definitions */
#define DBG                      DBG_BASE

/* registers definitions */
#define DBG_ID                   REG32(DBG + 0x00U)         /*!< DBG_ID code register */
#define DBG_CTL                  REG32(DBG + 0x04U)         /*!< DBG control register */

/* bits definitions */
/* DBG_ID */
#define DBG_ID_ID_CODE           BITS(0,31)                 /*!< DBG ID code values */

/* DBG_CTL */
#define DBG_CTL_SLP_HOLD         BIT(0)                     /*!< keep debugger connection during sleep mode */
#define DBG_CTL_DSLP_HOLD        BIT(1)                     /*!< keep debugger connection during deepsleep mode */
#define DBG_CTL_STB_HOLD         BIT(2)                     /*!< keep debugger connection during standby mode */
#define DBG_CTL_TRACE_IOEN       BIT(5)                     /*!< enable trace pin assignment */
#define DBG_CTL_FWDGT_HOLD       BIT(8)                     /*!< debug FWDGT kept when core is halted */
#define DBG_CTL_WWDGT_HOLD       BIT(9)                     /*!< debug WWDGT kept when core is halted */
#define DBG_CTL_TIMER0_HOLD      BIT(10)                    /*!< hold TIMER0 counter when core is halted */
#define DBG_CTL_TIMER1_HOLD      BIT(11)                    /*!< hold TIMER1 counter when core is halted */
#define DBG_CTL_TIMER2_HOLD      BIT(12)                    /*!< hold TIMER2 counter when core is halted */
#define DBG_CTL_TIMER3_HOLD      BIT(13)                    /*!< hold TIMER3 counter when core is halted */
#define DBG_CTL_CAN0_HOLD        BIT(14)                    /*!< debug CAN0 kept when core is halted */
#define DBG_CTL_I2C0_HOLD        BIT(15)                    /*!< hold I2C0 smbus when core is halted */
#define DBG_CTL_I2C1_HOLD        BIT(16)                    /*!< hold I2C1 smbus when core is halted */
#define DBG_CTL_TIMER4_HOLD      BIT(17)                    /*!< hold TIMER4 counter when core is halted */
#define DBG_CTL_TIMER5_HOLD      BIT(18)                    /*!< hold TIMER5 counter when core is halted */
#define DBG_CTL_TIMER6_HOLD      BIT(19)                    /*!< hold TIMER6 counter when core is halted */
#define DBG_CTL_TIMER7_HOLD      BIT(20)                    /*!< hold TIMER7 counter when core is halted */
#define DBG_CTL_CAN1_HOLD        BIT(21)                    /*!< debug CAN1 kept when core is halted */
#define DBG_CTL_TIMER11_HOLD     BIT(25)                    /*!< hold TIMER11 counter when core is halted */
#define DBG_CTL_TIMER12_HOLD     BIT(26)                    /*!< hold TIMER12 counter when core is halted */
#define DBG_CTL_TIMER13_HOLD     BIT(27)                    /*!< hold TIMER13 counter when core is halted */
#define DBG_CTL_TIMER8_HOLD      BIT(28)                    /*!< hold TIMER8 counter when core is halted */
#define DBG_CTL_TIMER9_HOLD      BIT(29)                    /*!< hold TIMER9 counter when core is halted */
#define DBG_CTL_TIMER10_HOLD     BIT(30)                    /*!< hold TIMER10 counter when core is halted */

/* constants definitions */
#define DBG_LOW_POWER_SLEEP      DBG_CTL_SLP_HOLD           /*!< keep debugger connection during sleep mode */
#define DBG_LOW_POWER_DEEPSLEEP  DBG_CTL_DSLP_HOLD          /*!< keep debugger connection during deepsleep mode */
#define DBG_LOW_POWER_STANDBY    DBG_CTL_STB_HOLD           /*!< keep debugger connection during standby mode */

/* debug hold when core is halted */
typedef enum
{
    DBG_FWDGT_HOLD             = BIT(8),                    /*!< debug FWDGT kept when core is halted */
    DBG_WWDGT_HOLD             = BIT(9),                    /*!< debug WWDGT kept when core is halted */
    DBG_TIMER0_HOLD            = BIT(10),                   /*!< hold TIMER0 counter when core is halted */
    DBG_TIMER1_HOLD            = BIT(11),                   /*!< hold TIMER1 counter when core is halted */
    DBG_TIMER2_HOLD            = BIT(12),                   /*!< hold TIMER2 counter when core is halted */
    DBG_TIMER3_HOLD            = BIT(13),                   /*!< hold TIMER3 counter when core is halted */
    DBG_CAN0_HOLD              = BIT(14),                   /*!< debug CAN0 kept when core is halted */
    DBG_I2C0_HOLD              = BIT(15),                   /*!< hold I2C0 smbus when core is halted */
    DBG_I2C1_HOLD              = BIT(16),                   /*!< hold I2C1 smbus when core is halted */
    DBG_TIMER4_HOLD            = BIT(17),                   /*!< hold TIMER4 counter when core is halted */
    DBG_TIMER5_HOLD            = BIT(18),                   /*!< hold TIMER5 counter when core is halted */
    DBG_TIMER6_HOLD            = BIT(19),                   /*!< hold TIMER6 counter when core is halted */
    DBG_TIMER7_HOLD            = BIT(20),                   /*!< hold TIMER7 counter when core is halted */
    DBG_CAN1_HOLD              = BIT(21),                   /*!< debug CAN1 kept when core is halted */
    DBG_TIMER11_HOLD           = BIT(25),                   /*!< hold TIMER11 counter when core is halted */
    DBG_TIMER12_HOLD           = BIT(26),                   /*!< hold TIMER12 counter when core is halted */
    DBG_TIMER13_HOLD           = BIT(27),                   /*!< hold TIMER13 counter when core is halted */
    DBG_TIMER8_HOLD            = BIT(28),                   /*!< hold TIMER8 counter when core is halted */
    DBG_TIMER9_HOLD            = BIT(29),                   /*!< hold TIMER9 counter when core is halted */
    DBG_TIMER10_HOLD           = BIT(30),                   /*!< hold TIMER10 counter when core is halted */
}dbg_periph_enum;

/* function declarations */
/* read DBG_ID code register */
uint32_t dbg_id_get(void);

/* enable low power behavior when the MCU is in debug mode */
void dbg_low_power_enable(uint32_t dbg_low_power);
/* disable low power behavior when the MCU is in debug mode */
void dbg_low_power_disable(uint32_t dbg_low_power);

/* enable peripheral behavior when the MCU is in debug mode */
void dbg_periph_enable(dbg_periph_enum dbg_periph);
/* disable peripheral behavior when the MCU is in debug mode */
void dbg_periph_disable(dbg_periph_enum dbg_periph);

/* enable trace pin assignment */
void dbg_trace_pin_enable(void);
/* disable trace pin assignment */
void dbg_trace_pin_disable(void);

#endif /* GD32C11X_DBG_H */
