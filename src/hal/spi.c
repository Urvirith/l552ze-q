#include "common.h"
#include "spi.h"

/* SPI Setup */
/*
    1.Write proper GPIO registers: Configure GPIO for MOSI, MISO and SCK pins.
    2.  Write to the SPI_CR1 register:
        a)  Configure the serial clock baud rate using the BR[2:0] bits (Note: 4).
        b)  Configure the CPOL and CPHA bits combination to define one of the 
            four relationships between the data transfer and the serial clock 
            (CPHA must be cleared in NSSP mode). 
            (Note: 2 - except the case when CRC is enabled at TI mode).
        c)  Select simplex or half-duplex mode by configuring RXONLY or BIDIMODE and BIDIOE 
            (RXONLY and BIDIMODE can't be set at the same time).
        d)  Configure the LSBFIRST bit to define the frame format (Note: 2).
        e)  Configure the CRCL and CRCEN bits if CRC is needed 
            (while SCK clock signal is at idle state).
        f)  Configure SSM and SSI (Notes: 2 & 3).
        g)  Configure the MSTR bit (in multimaster NSS configuration, avoid conflict state on 
            NSS if master is configured to prevent MODF error).
    3.  Write to SPI_CR2 register:
        a)  Configure the DS[3:0] bits to select the data length for the transfer.
        b)  Configure SSOE (Notes: 1 & 2 & 3).
        c)  Set the FRF bit if the TI protocol is required (keep NSSP bit cleared in TI mode).
        d)  Set the NSSP bit if the NSS pulse mode between two data units is required 
            (keep CHPA and TI bits cleared in NSSP mode).
        e)  Configure the FRXTH bit. The RXFIFO threshold must be aligned to the 
            read access size for the SPIx_DR register.
        f)  Initialize LDMA_TX and LDMA_RX bits if DMA is used in packed mode.
    4.      Write to SPI_CRCPR register: Configure the CRC polynomial if needed.
*/
void spi_open(SPI_TypeDef *ptr, SPI_BaudRate br, SPI_ClockSetup cs, SPI_BitFirst bit, SPI_DataSize ds) {
    clr_ptr_vol_bit_u32(ptr->CR1, SPE_BIT);
    set_ptr_vol_u32(ptr->CR1, BR_OFFSET, BR_MASK, br);

    switch (cs) {
        case SPI_RisingEdgeClockLow:
            clr_ptr_vol_bit_u32(ptr->CR1, CPHA_BIT);
            clr_ptr_vol_bit_u32(ptr->CR1, CPOL_BIT);
            break;
        case SPI_FallingEdgeClockLow:
            set_ptr_vol_bit_u32(ptr->CR1, CPHA_BIT);
            clr_ptr_vol_bit_u32(ptr->CR1, CPOL_BIT);
            break;
        case SPI_RisingEdgeClockHigh:
            clr_ptr_vol_bit_u32(ptr->CR1, CPHA_BIT);
            set_ptr_vol_bit_u32(ptr->CR1, CPOL_BIT);
            break;
        case SPI_FallingEdgeClockHigh:
            set_ptr_vol_bit_u32(ptr->CR1, CPHA_BIT);
            set_ptr_vol_bit_u32(ptr->CR1, CPOL_BIT);
            break;
    }

    switch (bit) {
        case SPI_Msb:
            clr_ptr_vol_bit_u32(ptr->CR1, LSB_FIRST_BIT);
            break;
        case SPI_Lsb:
            set_ptr_vol_bit_u32(ptr->CR1, LSB_FIRST_BIT);
            break;
    }
    
    set_ptr_vol_bit_u32(ptr->CR1, CRCL_BIT);                /* Set CRC To 8-Bit */
    set_ptr_vol_bit_u32(ptr->CR1, CRCEN_BIT);               /* Set CRC Enabled  */
    set_ptr_vol_bit_u32(ptr->CR1, MSTR_BIT);                /* Set Master Mode  */
    set_ptr_vol_u32(ptr->CR2, DS_OFFSET, DS_MASK, ds);      /* Set Datasize     */
}

void spi_enable(SPI_TypeDef *ptr) {
    set_ptr_vol_bit_u32(ptr->CR1, SPE_BIT);
}

/*
    The correct disable procedure is (except when receive only mode is used):
    1. Wait until FTLVL[1:0] = 00 (no more data to transmit).
    2. Wait until BSY=0 (the last data frame is processed).
    3. Disable the SPI (SPE=0).
    4. Read data until FRLVL[1:0] = 00 (read all the received data).
    The correct disable procedure for certain receive only modes is:
    Note:
    1. Interrupt the receive flow by disabling SPI (SPE=0) in the specific time window while
    the last data frame is ongoing.
    2. Wait until BSY=0 (the last data frame is processed).
    3. Read data until FRLVL[1:0] = 00 (read all the received data).
*/
void spi_disable(SPI_TypeDef *ptr) {
    clr_ptr_vol_bit_u32(ptr->CR1, SPE_BIT);
}

bool spi_get_read(SPI_TypeDef *ptr){
    return get_ptr_vol_bit_u32(&ptr->SR, RXNE_BIT);
}

void spi_read(SPI_TypeDef *ptr, uint8_t* buf, int len) {
    int i = 0; // Index based on len
    
    while(i < len) {
        if (spi_get_read(ptr)) {
            buf[i] = get_ptr_vol_raw_u8((volatile uint8_t *)&ptr->DR);
            i++;
        }
    }
    
}