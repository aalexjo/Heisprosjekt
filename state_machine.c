#include"state_machine.h"


void ev_button_pressed(elev_button_type_t buttonType, int floor) {
	qm_update_queue(floor, buttonType);
	elev_set_button_lamp(buttonType, floor, 1);
}


void ev_timeout() {
	elev_set_door_open_lamp(0);
	sm_stop = 0;
}


void ev_floor_signal(int floor) {
	printf("test \n"); //Remove before FAT
	sm_last_floor = floor;
	qm_update_floor(floor);
  
	if(floor != -1) {
	  elev_set_floor_indicator(floor);
		if(floor == qm_get_next_floor()){
			sm_arrived_at_target_floor(floor);
		}
	}
}


void ev_stop_button_pressed() {
	elev_set_motor_direction(0);
	elev_set_stop_lamp(1);
  
	if (elev_get_floor_sensor_signal() != -1) {//åpner døren hvis i etasje
		elev_set_door_open_lamp(1);
	}
	qm_delete_queue();
}


void ev_stop_button_released() {
	elev_set_stop_lamp(1);
	if (elev_get_floor_sensor_signal() != -1) {
		dt_start_timer();
	}
}


void sm_arrived_at_target_floor(int floor) {
	elev_set_motor_direction(0);
	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
//Mellom disse KAN det ha skjedd utilsiktede endringer
	sm_next_direction = qm_get_next_direction();

	if (sm_next_direction == 1) {    //slukker lys i knapper
		elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
	}
  else if (sm_next_direction == -1) {
		elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
	}

	elev_set_button_lamp(qm_get_next_direction(), floor, 0);
	//
  elev_set_door_open_lamp(1);
	dt_start_timer();
	sm_stop = 1;
	qm_update_floor(floor);
}


void sm_go_to_floor(){
	if((qm_get_next_floor()==-1 ) || sm_stop ){
		elev_set_motor_direction(0);
	}
	else if (sm_last_floor > qm_get_next_floor()){
		elev_set_motor_direction(-1);
    
	}else if (sm_last_floor < qm_get_next_floor()){
		elev_set_motor_direction(1);
	}
}
