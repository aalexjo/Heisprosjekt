//This is a test for the module Queue Manager

#ifndef Queue_Manager_test_h
#define Queue_Manager_test_h
#include "Linked_list.h"

static int qm_last_floor;
static elev_motor_direction_t qm_next_direction;
<<<<<<< HEAD
static linked_list* qm_order_list;
=======
linked_list* qm_order_list; 

>>>>>>> origin/master

void qm_update_floor(int floor);
void qm_update_queue(int floor, elev_button_type_t button);
int qm_get_next_floor(void);
int qm_get_next_direction(void);
void qm_init_queue(void);



#endif /* Queue_Manager_test_h */
