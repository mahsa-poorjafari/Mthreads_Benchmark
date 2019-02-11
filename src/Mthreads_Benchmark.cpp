/*
 * mt.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: mahsa
 */
#include "mainheader.h"
#include "windows.h"
#include "warning.h"
#include "airconditioner.h"


void *SenThermal();
void *Wipers(void *);
void *CheckSeatBelt();
void *SenSmokeDetector();
void *CheckBattery();
void *FuelControll();
void *SenMoistDetector();
void *HeadLampController();
void *Camera();
void *Speedometer(void *);

bool done;
int newprio = 2;
int policy = 0;
sched_param param;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t con = PTHREAD_COND_INITIALIZER;

void *PrintHello(void *threadarg) {
   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;

   cout << endl << "Thread ID : " << my_data->thread_id;
   cout << " Message : " << my_data->message << endl;
   cout << '\a';

   pthread_exit(NULL);
};


int main () {

	int num_thr;
	struct thread_data td_data, prio_data;
	int rc;
	int ret;
	//int min_prio_for_policy, max_prio_for_policy = 0;
	void * window_status;
	pthread_attr_t tattr;
	pthread_t tid;

	/* initialized with default attributes */
	ret = pthread_attr_init(&tattr);
	/*currently, only the Solaris SCHED_OTHER default value is supported in pthreads. Attempting to set policy as SCHED_FIFO or SCHED_RR will result in the error ENOSUP.  */
	/* Default scheduling policy is SCHED_OTHER */
	pthread_attr_getschedpolicy(&tattr, &policy);

	/* safe to get existing scheduling param */
	ret = pthread_getschedparam(tid, &policy, &param);

	/* set the priority; others are unchanged */
	//param.sched_priority = newprio;
	ret =  pthread_setschedprio(tid,2);
	/* setting the new scheduling param */
	ret = pthread_setschedparam(tid, policy, &param);
	cout << "param.sched_priority: " << param.sched_priority << endl;

	/* with new priority specified */
	prio_data.message = "This is message for the thread with priority 2";

	cout << "main() : Enter the Number of Threads: ";
	cin >> num_thr;
	done = 0;
	pthread_t thr[num_thr];

	cout <<"main() : control the windows" << endl;
	cout << "Which windows?" << endl;

	cout << "1(Left) / 2(Right) / 3(Front) / 4(Back) / 5(All):";
	cin >> td_data.type_val;

	td_data.message = "Ask to control the windows";
	td_data.signal_name = "check_windows";
	td_data.signal_val = false;
	td_data.type_name = "which windows";
	td_data.thread_id = pthread_self();
	rc = pthread_create(&thr[0], NULL, CtrWindows, (void *)&td_data);
	if (rc) {
	   cout << "Error:unable to create thread," << rc << endl;
	   exit(-1);
	}
	ret = pthread_create(&tid, &tattr, PrintHello, (void *)&prio_data);
	pthread_join(thr[0], &window_status);
	cout <<"main() : checking the windows finished " << window_status << endl;
	pthread_exit(NULL);


	//   for( i = 1; i < NUM_THREADS; i++ ) {
	//      cout <<"main() : creating thread, " << i << endl;
	//      td[i].thread_id = i;
	//      td[i].message = "This is message";
	//      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);
	//
	//      if (rc) {
	//         cout << "Error:unable to create thread," << rc << endl;
	//         exit(-1);
	//      }
	//   }

	ret = pthread_create(&thr[1], NULL, Warning, (void *)&td_data);
	if (ret) {
	   cout << "Error:unable to create thread," << ret << endl;
	   exit(-1);
	}

}



//Check the inside and outside temperature. The temperature value will create randomly and send to AirConditioner()
void *SenThermal(){
	return NULL;

}

//After starting the car, the seat belt must be fasten. If not send a alert to Warning()
void *CheckSeatBelt(){
	return NULL;

}

//will send a alert to Warning() if any smoke will detect.
void *SenSmokeDetector(){
	return NULL;

}

//Check the battery right after the car starts, and will send a alert to Warning() if the battery in Low.
void *CheckBattery(){
	return NULL;

}

//Check the fuel tank right after the car starts, and will send a alert to Warning() if the fuel in Low.
void *FuelControll(){
	return NULL;

}

//measures the humidity of outside, and send a signal to Wipers() or AirConditioner() or HeadLampController().
void *SenMoistDetector(){
	return NULL;

}

//It receives moist_signal form the SenMoistDetector() related to the humidity or wet windows and will turn the wipers On or Off
void *Wipers(void *moist_signal){
	return NULL;

}

//It receives moist_signal form the SenMoistDetector() or SenPlluFogDetector() related to the humidity or pollution and will turn the heal lamp On or Off
void *HeadLampController(void *moist_plo_signal){
	return NULL;

}

//Will detect the traffic light
void *Camera(){
	return NULL;

}

//Cameras will send signal from traffic light or obstacles to control the speed
void *Speedometer(void *speed_signal){
	return NULL;

}




