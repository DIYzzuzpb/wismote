/* NO_YET_DOCUMENTED_PTV */

/*
 * Copyright (c) 2011, Plateforme Technologique de Valence.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "contiki.h"
#include "sys/process.h"
#include "sys/autostart.h"
#include "parallax_pir-555-28027.h"
#include "iohandlers.h"
#include "leds.h"
#include "clock.h"
#include <stdint.h>

#include "lib/sensors.h"
#include "contiki.h"
#include <stdio.h>

/*---------------------------------------------------------------------------*/
PROCESS(exemple_presence_process, "exemple_presence process");
AUTOSTART_PROCESSES(&exemple_presence_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(exemple_presence_process, ev, data)
{
  PROCESS_BEGIN();
  /* Set-up GND */
  P6DIR |= BIT0;
  P6OUT &= ~BIT0;
  SENSORS_ACTIVATE(PIR_555_28027_sensor);
  while (1)
  {
    PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event && data == &PIR_555_28027_sensor);
    int presence = ((struct sensors_sensor *)data)->value(0);
    if (presence)
    {
      printf("Someone is here !!!\n");
    }
    else
    {
      printf("Nobody\n");
    }
  }
  PROCESS_END();
}

/*---------------------------------------------------------------------------*/