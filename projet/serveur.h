#ifndef SERV_H
#define SERV_H

#include "pse.h"

//#define    CMD      "serveur"
#define nb_threads 5
#define   NB_WORKERS   50

void *worker(void *arg);
void sessionClient(int canal);
void remiseAZeroJournal(void);

#endif