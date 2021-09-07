#ifndef W5200_H_
#define W5200_H_

/* 
    WIZNet W5200 Chipset
    http://wiznethome.cafe24.com/wp-content/uploads/wiznethome/Chip/W5200/Documents/W5200_DS_V140E.pdf
    http://wiznethome.cafe24.com/wp-content/uploads/wiznethome/Network%20Module/WIZ820io/Document/WIZ820io_User_Manual_V1.0.pdf
*/

typedef struct {
    volatile uint32_t CR1;              // Control Register 1
    volatile uint32_t CR2;              // Control Register 2
    volatile uint32_t SR;               // Baud Rate Register Register
    volatile uint32_t DR;               // Guard Time / Prescaler Register
    volatile uint32_t CRCPR;            // Receiver Timeout Register
    volatile uint32_t RXCRCPR;          // Request Register
    volatile uint32_t TXCRCPR;          // Interrupt And Status Register
} W5200_TypeDef;

#endif /* W5200_H_ */
