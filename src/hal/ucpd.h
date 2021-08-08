#ifndef UCPD_H_
#define UCPD_H_

// UCPD DRIVER
// ARM UCPD MODULE
// UCPD Description - is on pg 1981

/* USB Type-C / USB Power Delivery interface (UCPD) */

/* Register Pointer Structure */
typedef struct {
    volatile uint32_t CFG1;             // Configuration Register 1
    volatile uint32_t CFG2;             // Configuration Register 2
    volatile uint32_t CFG3;             // Configuration Register 3
    volatile uint32_t CR;               // Control Register
    volatile uint32_t IMR;              // Interrupt Mask Register
    volatile uint32_t SR;               // Status Register
    volatile uint32_t ICR;              // Interrupt Clear Register
    volatile uint32_t TX_ORDSET;        // TX Ordered Set Type Register
    volatile uint32_t TX_PAYSZ;         // TX Payload Size Register
    volatile uint32_t TXDR;             // TX Data Register
    volatile uint32_t RX_ORDSET;        // RX Ordered Set Type Register
    volatile uint32_t RX_PAYSZ;         // RX Payload Size Register
    volatile uint32_t RX_RXDR;          // RX Data Register
    volatile uint32_t RX_ORDEXT1;       // RX Ordered Set Extension Register 1
    volatile uint32_t RX_ORDEXT2;       // RX Ordered Set Extension Register 2
} UCPD_TypeDef;

/* Register Masks */
/* CFGR1 */
#define HBITCLKDIV_MASK     MASK_6_BIT  /* The bitfield determines the division ratio (the bitfield value plus one) of a ucpd_clk divider producing half-bit clock (hbit_clk) Min - 0x00 = 1 (Bypass), Max - 3F = 64*/
#define IFRGAP_MASK         MASK_5_BIT  /* The bitfield determines the division ratio (the bitfield value minus one) of a ucpd_clk divider producing inter-frame gap timer clock (tInterFrameGap) Min - 0x00 = 1 (Not Supported), Max - 1F = 32 */
#define TRANSWIN_MASK       MASK_5_BIT  /* The bitfield determines the division ratio (the bitfield value minus one) of a hbit_clk divider producing tTransitionWindow interval Min - 0x00 = 1 (Not Supported), Max - 1F = 32 */ 
#define PDCLK_MASK          MASK_3_BIT  /* The bitfield determines the division ratio of a kernel clock pre-scaler producing UCPD peripheral clock (ucpd_clk) Min - 0x00 = 1 (Bypass), Max - 0x4 = 16 */
#define RXORDSET_MASK       MASK_9_BIT  /* The bitfield determines the types of ordered sets that the receiver must detect. When set/cleared, each bit enables/disables a specific function 0bxxxxxxxx1: SOP detect enabled, 0bxxxxxxx1x: SOP' detect enabled, 0bxxxxxx1xx: SOP'' detect enabled, 0bxxxxx1xxx: Hard Reset detect enabled, 0bxxxx1xxxx: Cable Detect reset enabled, 0bxxx1xxxxx: SOP'_Debug enabled, 0bxx1xxxxxx: SOP''_Debug enabled, 0bx1xxxxxxx: SOP extension#1 enabled, 0b1xxxxxxxx: SOP extension#2 enabled */
/* CR */
#define TX_MODE_MASK        MASK_2_BIT  /* Writing the bitfield triggers the action as follows, depending on the value: 0x0: Transmission of Tx packet previously defined in other registers, 0x1: Cable Reset sequence, 0x2: BIST test sequence (BIST Carrier Mode 2) */
#define CN_EN_MASK          MASK_2_BIT  /* This bitfield enables CC1 and CC2 line analog PHYs (pull-ups and pull-downs) according toANAMODE and ANASUBMODE[1:0] setting, 0x0: Disable both PHYs, 0x1: Enable CC1 PHY, 0x2: Enable CC2 PHY, 0x3: Enable CC1 and CC2 PHY */
/* BRR */
#define BAUD_RATE_MASK      MASK_16_BIT
/* RTOR */
#define RTO_TIMEO_MASK      MASK_24_BIT

/* Register Bits */
/* CFGR1 */
#define UCPDEN_BIT          BIT_31
/* CR2 */
#define RTOEN_BIT           BIT_23
/* ICR */
#define FECF_BIT            BIT_1
#define ORECR_BIT           BIT_3
#define IDLECF_BIT          BIT_4
#define RTOCF_BIT           BIT_11
/* ISR */
#define FE_BIT              BIT_1
#define ORE_BIT             BIT_3
#define IDLE_BIT            BIT_4
#define RXNE_BIT            BIT_5
#define TC_BIT              BIT_6
#define TXE_BIT             BIT_7


/* Register Offsets */
/* CFGR1 */
#define HBITCLKDIV_OFFSET   0
#define IFRGAP_OFFSET       6
#define TRANSWIN_OFFSET     11
#define PDCLK_OFFSET        17
#define RXORDSET_OFFSET     20
/* CR */
#define TX_MODE_OFFSET      0
#define CN_EN_OFFSET        10
/* BRR */
#define BAUD_RATE_OFFSET    0
/* RTOR */
#define RTO_TIMEO_OFFSET    0


#endif /* USBC_H_ */