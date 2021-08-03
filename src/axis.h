#ifndef AXIS_H_
#define AXIS_H_

/* Structure Of Individual Motors */
typedef struct {
    volatile Motor_DirDef DIRECTION;        // Direction To Move In
    volatile Motor_StateDef STATE;          // State Of The Motor
    volatile uint32_t COUNT;                // Count From 0 Position  
    volatile uint32_t PLL_CFGR;             // PLL Configuration Register
} Motor_TypeDef;

/* Enumeration For Movement Of The Motor */
typedef enum {
    Reverse,
    Forward
} Motor_DirDef;

/* Enumeration For States Of The Motor */
typedef enum {
    BootUp,
    Stopped,
    Operational,
    PreOperational,
    Faulted,
    Homing
} Motor_StateDef;

#endif /* AXIS_H_ */