#ifndef AXIS_H_
#define AXIS_H_

/* Enumeration For Movement Of The Motor */
typedef enum motor_direction {
    Reverse,
    Forward
} Motor_DirDef;

/* Enumeration For States Of The Motor */
typedef enum motor_state {
    BootUp,
    Stopped,
    Operational,
    PreOperational,
    Faulted,
    Homing
} Motor_StateDef;

/* Structure Of Individual Motors */
typedef struct motor_type {
    volatile Motor_DirDef DIRECTION;        // Direction To Move In
    volatile Motor_StateDef STATE;          // State Of The Motor
    volatile uint32_t COUNT;                // Pulse Count From 0 Position  
} Motor_TypeDef;

/* Structure Of Motor Control */
typedef struct motor_control {
    volatile Motor_TypeDef MOTOR1;          // Motor 1 Structure
    volatile Motor_TypeDef MOTOR2;          // Motor 2 Structure
    volatile Motor_TypeDef MOTOR3;          // Motor 3 Structure
    volatile Motor_TypeDef MOTOR4;          // Motor 4 Structure
    volatile Motor_StateDef STATE;
    volatile uint32_t COUNT;                // Target Count
    volatile bool TOGGLE;                   // Toggle Bit To Indicate Heartbeat Of Interrupt
} MotorController_TypeDef;

#endif /* AXIS_H_ */