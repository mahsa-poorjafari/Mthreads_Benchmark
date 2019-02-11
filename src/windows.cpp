/*
 * Windows.cpp
 *
 *  Created on: Feb 6, 2019
 *      Author: mahsa
 */
#include "mainheader.h"
#include "windows.h"
#include "convar.h"
int rc;
struct thread_data *my_data;
//lock all door
void *LockAll(void *arg){
	cout << "All doors has been locked" << endl;
	int result = 1;
	pthread_exit(&result);
}

//This is a parent thread = If doors are open, lock the windows,
void *CheckDoors(void *arg){

	bool randbool;
	int d = 0;
	my_data = (struct thread_data *) arg;

	//pthread_mutex_lock(&lock);

    my_data->thread_id = pthread_self();
	cout << "In CheckDoors, child thread" << endl;
	cout << "Thread ID : " << my_data->thread_id << "  Thread closeD Prio: " << param.sched_priority << endl;
	cout << " Message : " << my_data->message << endl;
	//to simulate the real life, just randomly set the value to be different.
	srand(time(NULL));
	float r = (float) rand()/RAND_MAX;
	randbool = (r < 0.5) ? true : false;
	cout << endl << "created Random number: " << r << endl;
	cout << endl << "randbool: " << randbool << endl;
	my_data->signal_val= randbool;
	my_data->signal_name = "Has the door locked?";
	cout << " Signal: " << my_data->signal_name << "= " << my_data->signal_val  << endl;

	//win_data.signal_name = "doors_status";
	//win_data.message = "Doors has been checked";
	done = 1;
	//pthread_cond_signal(&con);
	//pthread_mutex_unlock(&lock);
	//pthread_exit(&my_data->signal_val);
	d = (int) randbool;
	pthread_exit(&d);

}

//This is the parent thread. door windows will be closed, if the doors are open either the car is turn off.
void *CtrWindows(void *data){
	pthread_t ctrdoors;
	bool window_status;
	int *door_status;
	struct thread_data *my_data, win_data, door_data;

    my_data= (struct thread_data *) data;
    cout << "In CtrWindows, Parent Threads" << endl;
    cout << "Thread ID : " << my_data->thread_id<< endl;
    cout << " Message : " << my_data->message << endl;
	cout << " Signal: " << my_data->signal_name << "= " << my_data->signal_val  << endl;
	cout << " Type: " << my_data->type_name << "=> ";

	door_data.type_name = "which door" ;
	door_data.type_val = my_data->type_val;
	rc =  pthread_setschedprio(ctrdoors,15);

	if (my_data->type_val == 5){

		cout << "All the Windows" << endl;
		door_data.message = "Ask to clock all the doors";
		door_data.signal_name = "lock_all_doors";
		rc = pthread_create(&ctrdoors, NULL, LockAll, (void *)&door_data);

	}
	else {
		switch(my_data->type_val){
		case 1 : cout << "Left Windows" << endl;
					break;
		case 2 : cout << "Right Windows" << endl;
					break;
		case 3 : cout << "Front Windows" << endl;
					break;
		case 4 : cout << "Back Windows" << endl;
					break;
		}
	    door_data.message = "Ask to check the doors";
	    door_data.signal_name = "check_doors";
	    rc = pthread_create(&ctrdoors, NULL, CheckDoors, (void *)&door_data);
	};

    if (rc) {
    	cout << "Error:unable to create thread," << rc << endl;
    	exit(-1);
    }
    //thr_join((void *)&door_data);
    pthread_join(ctrdoors, (void **) &door_status);
    cout << "  door_status:  " << *door_status  << endl;
    window_status = ( *door_status) ? true : false;
    /*
    if (pthread_join(ctrdoors, (void **) &door_status) != 0) {
      cout << "Creating ctrdoors Thread failed." << endl;
      exit(3);
    }
    else {
    	cout << "  door_status:  " << *door_status  << endl;
    	window_status = ( *door_status) ? true : false;
    };
    */
    win_data.signal_name= "windows_status";
    win_data.signal_val = window_status;
    win_data.thread_id = pthread_self();
    cout << "Thread ID : " << win_data.thread_id;
    cout << " Signal: " << win_data.signal_name << "= " << win_data.signal_val  << endl;
    cout << '\a';

	done = 1;

    pthread_exit(&window_status);

}

