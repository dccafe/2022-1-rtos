#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <msp430f5529.h>
#include <stdint.h>

typedef struct{
    uint16_t *pTask;
    uint16_t *pStack;
} task_t;


void * getSP();
void setSP(void * stackPointer);
void restoreContext();
void saveContext();

void registerTask(void *newTask);
void startRTOS();

#endif // __SCHEDULER_H__
