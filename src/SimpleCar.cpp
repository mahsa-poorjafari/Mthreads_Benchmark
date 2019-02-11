#include <iostream>
#include <pthread.h>

using namespace std;

struct thread_data {
   int  thread_id;
   char const *message;
};