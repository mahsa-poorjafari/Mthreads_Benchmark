/*
 * mainheader.h
 *
 *  Created on: Feb 6, 2019
 *      Author: mahsa
 */

#ifndef MAINHEADER_H_
#define MAINHEADER_H_

#include <iostream>
//#include <sys/resource.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
using namespace std;
extern sched_param param;
extern int policy;
extern bool done;
struct thread_data {
   int thread_id;
   char const *message;
   char const *signal_name;
   bool signal_val;
   char const * type_name;
   int type_val;
};

#endif /* MAINHEADER_H_ */
