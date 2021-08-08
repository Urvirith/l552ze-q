#include "common.h"
#include "ucpd.h"

/*
    UCPD programming sequences
    The normal sequence of use of the UCPD unit is:
    1. Configure UCPD.
    2. Enable UCPD.
    3. Concurrently:
    – On demand from protocol layer, send Tx message
    – Intercept (poll or wait for interrupt) relevant Rx messages and recover detail to
    hand off to protocol layer
    Repeat the last point infinitely.
    Initialization phase
    Use the following sequence for a clean startup:
    1. Prepare all initial clock divider values, by writing the UCPD_CFG register.
    2. Enable the unit, by setting the UCPDEN bit.
*/


/*
    Hard Reset transmission
    As soon as it is known that a Hard Reset needs to be transmitted, setting the TXHRST bit of
    the UCPD_CR register forces the internal state machine to generate the correct sequence.
    The value of UCPD_TX_ORDSET does not require update in this precise case (the correct
    code for Hard Reset is sent by UCPD).
    The USB Power Delivery specification requires that in the case of an ongoing message
    transmission, the Hard Reset takes precedence. In this case, for example, UCPD truncates
    the payload of the current message, appending EOP to the end. No notification is available
    via the registers (for example through the TXMSGSEND flag). This is justified by the fact
    that the Hard Reset takes precedence over any previous activity (for which it is therefore no
    longer important to know if it is completed).
*/

/*
    USB PD transmit
    On reception of a message from the protocol layer (that is, to be sent), prepare Tx message
    contents by writing the UCPD_TX_ORDSET and UCPD_TX_PAYSZ registers.
    The message transmission is triggered by setting the TXSEND bit, with an appropriate
    value of the TXMODE bitfield.
    When the data byte is transmitted, the TXIS flag is raised to request a new data write to the
    UCPD_TXDR register.
    This re-iterates until the entire payload of data is transmitted.
    Upon sending the CRC packet, the TXMSGSENT flag is set to indicate the completion of
    the message transmission.
*/

/* 
    Notification of start of the receive message sequence is triggered by an interrupt on
    UCPD_SR (bit RXORDDET).
    The information is recovered by reading:
    • UCPD_RX_SOP (on interrupt RXORDDET)
    • UCPD_RXDR (on interrupt RXNE, repeats for each byte)
    • UCPD_RXPAYSZ (on interrupt RXMSGEND)
    The data previously read from UCPD_RXDR above must be discarded at this point if the
    RXERR flag is set.
    If the CRC is valid, the received data is transferred to the protocol layer.
    For debug purposes, it may be desirable to track statistics of the number of incorrect
    K-codes received (this is done only when 3/4 K-codes were valid as defined in the
    specification). This is facilitated through:
    • RXSOP3OF4 bit indicating the presence of at least one invalid K-code
    • RXSOPKINVALID bitfield identifying the order of invalid K-code in the ordered set
*/