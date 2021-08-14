#ifndef PHASE_H_
#define PHASE_H_

/* Enumeration For Phase Control */
typedef enum {
    Idle,
    Running,
    Complete,
    Stopping,
    Stopped,
    Aborting,
    Aborted,
    Holding,
    Held,
    Restarting
} Phase_StateDef;

#endif /* PHASE_H_ */