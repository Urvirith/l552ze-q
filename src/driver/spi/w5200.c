#include "../../hal/common.h"
#include "w5200.h"

/* WIZNET is MSB,

/* Common Register */
/* Mode */
#define MODER               0x0000

/* Gateway Address Register */
/* Example (GAR0 (0xC0 = 192), GAR1 (0xA8 = 168), GAR2 (0x00 = 0), GAR3 (0x01 = 1) -> 192.168.0.1) */
#define GAR0                0x0001
#define GAR1                0x0002
#define GAR2                0x0003
#define GAR3                0x0004

/* Subnet Mask Address Register */
/* Example (SUBR0 (0xFF = 255), SUBR1 (0xFF = 255), SUBR2 (0xFF = 255), SUBR3 (0x00 = 0) -> 255.255.255) */
#define SUBR0               0x0005
#define SUBR1               0x0006
#define SUBR2               0x0007
#define SUBR3               0x0008

/* Source Hardware Address Register */
/* Example (SHAR0 (0x00), SHAR1 (0x08), SHAR2 (0xDC), SHAR3 (0x01), SHAR4 (0x02), SHAR5 (0x03) -> 00:08:DC:01:02:03) */
#define SHAR0               0x0009
#define SHAR1               0x000A
#define SHAR2               0x000B
#define SHAR3               0x000C
#define SHAR4               0x000D
#define SHAR5               0x000E

/* Source IP Address Register */
/* Example (SIPR0 (0xC0 = 192), SIPR1 (0xA8 = 168), SIPR2 (0x00 = 0), SIPR3 (0x02 = 2) -> 192.168.0.2) */
#define SIPR0               0x000F
#define SIPR1               0x0010
#define SIPR2               0x0011
#define SIPR3               0x0012

/* Interrupt Register */
#define IR                  0x0015

/* Interrupt Mask Register */
#define IMR                 0x0016

/* Retry Time Register */
#define RTR0                0x0017
#define RTR1                0x0018

/* Retry Count Register */
#define RCR                 0x0019

/* Chip Version Register */
#define VERR                0x001F

/* Socket Interrupt Register */
#define IR2                 0x0034

/* Physical Status Register */
#define IR2                 0x0035


/* Socket Registers */
/* Register Offset */
#define SOCK_OFFSET         0x0100

/* Mode */
#define SOCK_MODER          0x4000

/* Command */
#define SOCK_CR             0x4001

/* Interrupt */
#define SOCK_IR             0x4002

/* Status */
#define SOCK_SR             0x4003

/* Source Port */
#define SOCK_SPORTR1        0x4004
#define SOCK_SPORTR2        0x4005

/* Destination Hardware Address Register */
/* Example (SHAR0 (0x00), SHAR1 (0x08), SHAR2 (0xDC), SHAR3 (0x01), SHAR4 (0x02), SHAR5 (0x03) -> 00:08:DC:01:02:03) */
#define SOCK_DHAR0          0x4006
#define SOCK_DHAR1          0x4007
#define SOCK_DHAR2          0x4008
#define SOCK_DHAR3          0x4009
#define SOCK_DHAR4          0x400A
#define SOCK_DHAR5          0x400B

/* Destination IP Address Register */
/* Example (SIPR0 (0xC0 = 192), SIPR1 (0xA8 = 168), SIPR2 (0x00 = 0), SIPR3 (0x02 = 2) -> 192.168.0.2) */
#define SOCK_DIPR0          0x000C
#define SOCK_DIPR1          0x001D
#define SOCK_DIPR2          0x001E
#define SOCK_DIPR3          0x001F

/* Destination Port */
#define SOCK_DPORTR1        0x4010
#define SOCK_DPORTR2        0x4011
