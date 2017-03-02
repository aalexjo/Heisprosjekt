#include "elev.h"
#include <stdio.h>
#include <stdbool.h>
#include "state_machine.h"
#include "Door_Timer.h"

void elevator_init();


int main() {
    // Initialize hardware
	elevator_init();
  
	bool timeout = true;

  while (true) {
		//sjekker om heisen ankommer en etasje
		if (elev_get_floor_sensor_signal() != -1) {
			ev_floor_signal(elev_get_floor_sensor_signal());
		}

		//sjekker etter knappetrykk
		for (int i = 0; i < N_FLOORS-1; i++) {//itererer gjennom alle etasjer
			for (int j = 0; j <= 2; j++) {//iterer gjennom alle typer knapper
				if((j == 0 && i == N_FLOORS - 1)||(j == 1 && i == 0)) {
					continue;
					}
				if (elev_get_button_signal(j, i)) {					
					ev_button_pressed(j, i);
				}
			}
		}

		//sjekker timeout

		if (dt_is_timeout() && !timeout) {
			ev_timeout();
			printf("timeout \n");
			timeout = true;
		}else {
			timeout = dt_is_timeout();
		}


		sm_go_to_floor();


    }
  
		qm_delete_queue();
		free(qm_order_list); //tenkt gjennom, er dette nok?
		qm_order_list = NULL;
  
    return 0;
}


void elevator_init() {
	if (!elev_init()) {
		printf("Unable to initialize elevator hardware!\n");
	}
	while (elev_get_floor_sensor_signal() == -1)
	{
		elev_set_motor_direction(1);
	}
	elev_set_motor_direction(0);
	qm_init_queue();

	sm_stop =0;
}
