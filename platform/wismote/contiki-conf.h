/**
 * \defgroup wismote Wismote platform
 *
 * This is the module implementing Contiki on the Wismote platform.
 *
 * @{
 */

/**
 * \file
 *         Contiki configuration.
 * \author
 *         Anthony Gelibert <anthony.gelibert@lcis.grenoble-inp.fr>
 * \date
 *         March 21, 2011
 */

/*
 * Copyright (c) 2011, LCIS/CTSYS.
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
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS "AS IS" AND
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

#ifndef __CONTIKI_CONF_H__
#define __CONTIKI_CONF_H__

/* ----- Compiler macros ----- */
/* For the CC_CONF_* macros, see : /core/sys/cc.h */
#define CC_CONF_REGISTER_ARGS 1
#define CC_CONF_INLINE  __inline__
#define CCIF
#define CLIF

/* ----- Clock module ----- */
#define CLOCK_CONF_SECOND 128UL
/* XXX_PTV Change to long */
typedef unsigned short clock_time_t;

/* ----- UIP module ----- */
/* ---- General ---- */
typedef unsigned short uip_stats_t;
/** Globally enable logging. */
#define PLATFORM_LOGGING           1
#if PLATFORM_LOGGING
/** Enable UIP logging. */
#define UIP_CONF_LOGGING           1
/** Enable configuration logging. */
#define LOG_CONF_ENABLED           1
/** Enable UIP statistics. */
#define UIP_CONF_STATISTICS        1
#else
/** Disable UIP logging. */
#define UIP_CONF_LOGGING           0
/** Disable configuration logging. */
#define LOG_CONF_ENABLED           0
/** Disable UIP statistics. */
#define UIP_CONF_STATISTICS        0
#endif
/** Disable PING ADDR. CONF. */
#define UIP_CONF_PINGADDRCONF      0
/** Disable IP packet reassembly. */
#define UIP_CONF_REASSEMBLY        0
/** Size of the uIP buffer. */
#define UIP_CONF_BUFFER_SIZE    1514
/* ---- UDP ---- */
/** Enable UDP compilation. */
#define UIP_CONF_UDP               1
/** Disable UDP checksum. */
#define UIP_CONF_UDP_CHECKSUMS     0
#if UIP_CONF_UDP
/** Number of simultaneous connection. */
#define UIP_CONF_UDP_CONNS         5
/** Enable broadcast. */
#define UIP_CONF_BROADCAST         1
#else
#define UIP_CONF_UDP_CONNS         0
/** Disable UDP broadcast. */
#define UIP_CONF_BROADCAST         0
#endif

/* ---- TCP ---- */
/** Enable TCP compilation. */
#define UIP_CONF_TCP               1
#if UIP_CONF_TCP
/** Enable open connection. */
#define UIP_CONF_ACTIVE_OPEN       1
/** Number of open connection. */
#define UIP_CONF_MAX_CONNECTIONS   5
/** Number of open ports. */
#define UIP_CONF_MAX_LISTENPORTS   5
#else
/** Disable open connex. */
#define UIP_CONF_ACTIVE_OPEN       0
/** No open connex. */
#define UIP_CONF_MAX_CONNECTIONS   0
/** No port available. */
#define UIP_CONF_MAX_LISTENPORTS   0
#endif

/* ----- SPI module ----- */
/** SPI: Macro to wait for TX ready. */
#define SPI_WAITFORTxREADY() while (!(IFG2 & UCB0TXIFG))
/** SPI: Macro to wait for TX done. */
#define SPI_WAITFOREOTx() while (UCB0STAT & UCBUSY)
/** SPI: TX Buffer. */
#define SPI_TXBUF UCB0TXBUF
/** SPI: RX Buffer. */
#define SPI_RXBUF UCB0RXBUF

/* ----- CLOCK module ----- */
/** CLOCK: this platform uses XT1 clock. */
#define XT1_CONF_CLOCK 1
/** CLOCK: disable debug. */
#define SMCLOCK_CONF_DEBUG 0

/* ----- IOHANDLERS module ----- */
/** IOHANDLERS: disable debug. */
#define IOHANDLERS_CONF_DEBUG 0


/* If MAIN_UART == 1, the main UART is UART1.
 * If MAIN_UART == 0, the main UART is UART0.
 * Else, it's an error
 */
#define MAIN_UART 0

/* Just a dumb check. */
#ifndef MAIN_UART
#define MAIN_UART 0
#endif

/* And another... */
#if MAIN_UART!=0 && MAIN_UART!=1
#error "MAIN_UART == 1 or MAIN_UART == 0"
#endif

/* ----- UART module ----- */
/** UART0: uses interrupt for TX. */
#define UART0_CONF_TX_WITH_INTERRUPT 1
/** UART0: size of the TX buffer. */
#define UART0_CONF_TX_BUFSIZE      128
/** UART1: SLIP doesn't use the MAIN_UART */
#define SLIP_USE_UART1 (MAIN_UART)
/** UART1: uses interrupt for TX. */
#define UART1_CONF_TX_WITH_INTERRUPT 1
/** UART1: size of the TX buffer. */
#define UART1_CONF_TX_BUFSIZE      128
/** UART1: "stdio.h" uses the MAIN_UART */
#define STDIO_USE_UART1 (MAIN_UART)

/* ----- Serial Line module ----- */
/** Serial Line module uses the MAIN_UART */
#define SL_USE_UART1 (MAIN_UART)
/** Buffer for the serial line reception buffer. */
#define SERIAL_LINE_CONF_BUFSIZE 64


/* ----- Diagnostic ----- */
/** Diagnostic use a JSON output. */
#define DIAGNOSTIC_CONF_OUTPUT JSON_OUTPUT

#ifndef CONTIKI_NO_NET
/* ----- Netstatck ----- */
/* Network configuration */
#define NETSTACK_CONF_MAC     csma_driver
#define NETSTACK_CONF_RDC     contikimac_driver
#define NETSTACK_CONF_RADIO   cc2520_driver
#define NETSTACK_CONF_FRAMER  framer_802154

#if WITH_UIP6
/* Network setup for IPv6 */
#define NETSTACK_CONF_NETWORK sicslowpan_driver
#define CXMAC_CONF_ANNOUNCEMENTS         0
#define XMAC_CONF_ANNOUNCEMENTS          0
#define QUEUEBUF_CONF_NUM                8
#else /* WITH_UIP6 */
/* Network setup for non-IPv6 (rime). */
#define NETSTACK_CONF_NETWORK rime_driver
#define COLLECT_CONF_ANNOUNCEMENTS       1
#define CXMAC_CONF_ANNOUNCEMENTS         0
#define XMAC_CONF_ANNOUNCEMENTS          0
#define CONTIKIMAC_CONF_ANNOUNCEMENTS    0
#define CONTIKIMAC_CONF_COMPOWER         1
#define XMAC_CONF_COMPOWER               1
#define CXMAC_CONF_COMPOWER              1
#define COLLECT_NEIGHBOR_CONF_MAX_COLLECT_NEIGHBORS     32
#define QUEUEBUF_CONF_NUM                16
#endif /* WITH_UIP6 */
#endif /* CONTIKI_NO_NET */

/* ----- Includes ----- */
#include "types.h"
#include <msp430f5437.h>

#endif /* __CONTIKI_CONF_H__ */

/** @} */

