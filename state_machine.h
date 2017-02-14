#pragma once
#include"elev.h"

static int sm_last_floor;
static int sm_target_floor;
static int sm_direction;

void ev_button_pressed(elev_button_type_t buttonType, int floor);
void ev_timeout();
void ev_floor_signal(int floor);
void ev_stop_button_pressed();
void ev_stop_button_released();
void sm_arrived_at_floor(floor);