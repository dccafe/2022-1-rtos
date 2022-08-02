#include <msp430f5529.h>
#include <stdint.h>
#include <scheduler.h>

task_t     tasks[10];
uint8_t    nRegTasks;
uint16_t * schedulerSP = (uint16_t *)(0x2700);

void startRTOS()
{
    // Muda a pilha para a pilha da próxima tarefa
    setSP(tasks[0].pStack);

    // Restaura o contexto da próxima tarefa
    restoreContext();
}

void registerTask(void *newTask)
{
    static uint16_t * stackStart  = (uint16_t *) 0x2800;
    const  uint16_t   stackOffset = 0x80;

    tasks[nRegTasks].pTask  = newTask;
    tasks[nRegTasks].pStack = stackStart;

    stackStart += stackOffset;

    *(--tasks[nRegTasks].pStack) =     (uint16_t) newTask; // PUSH newTask
    *(--tasks[nRegTasks].pStack) = ((( (uint32_t) newTask ) >> 4) & 0xF000) | GIE;

    uint8_t i = 12;
    while(i--)
    {
        // Um registro de 20 bits ocupa 32 bits na pilha
        *(--tasks[nRegTasks].pStack) = 0xCAFE;
        *(--tasks[nRegTasks].pStack) = 0xFACA;
    }

    nRegTasks++;
}

uint16_t   runningTaskNumber;

#pragma vector=WDT_VECTOR
__attribute__((naked))
__interrupt void WDTISR()
{
    // Despachante
    // Salva o contexto da tarefa em execução
    saveContext();

    // Salva o ponteiro da pilha da tarefa em execução
    tasks[runningTaskNumber].pStack = getSP();

    // Restaura o ponteiro da pilha do escalonador
    //setSP(schedulerSP);

    // Scheduler
    runningTaskNumber = (runningTaskNumber + 1) % nRegTasks;

    // Salva o ponteiro da pilha do escalonador
    //schedulerSP = getSP();

    // Muda a pilha para a pilha da próxima tarefa
    setSP(tasks[runningTaskNumber].pStack);

    // Restaura o contexto da próxima tarefa
    restoreContext();

}
