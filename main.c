#include <stdio.h>
#include <stdlib.h>

#define UP 1
#define DOWN -1
#define IDLE 0

int current_floor = 1;
int destination_floor = 0;
int direction = IDLE;
int num_floors = 10;

struct FloorRequest {
    int floor;
    struct FloorRequest *next;
};

struct FloorRequest *floor_requests = NULL;


/*Function that adds request for the elevator to the queue of request
In other words it simulates the user pushin a floor button */

struct FloorRequest* add_floor_request(int floor) {
    if (floor < 1 || floor > num_floors) {
        printf("Invalid floor number\n");
        return NULL;
    }
    
    struct FloorRequest *new_request = (struct FloorRequest*) malloc(sizeof(struct FloorRequest));
    new_request->floor = floor;
    new_request->next = NULL;
    
    if (floor_requests == NULL) {
        floor_requests = new_request;
        destination_floor= floor_requests->floor;
        return floor_requests;
    } 
    else {
        struct FloorRequest *current = floor_requests;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_request;
        return current;
    }

    
}

/*Function that move the elevator to it's next destination using FIFO priority*/

int move_to_next_floor() {
    if (floor_requests == NULL) {
        direction = IDLE;
        return -1;
    }

    if (current_floor == destination_floor) {
        printf("Doors open at floor %d\n", current_floor);
        floor_requests = floor_requests->next;
        destination_floor = 0;
        direction = IDLE;
        return 1;
    }
    else {
        printf("Moving from %d to floor %d\n",current_floor,destination_floor);
        current_floor = destination_floor;
        floor_requests = floor_requests->next;
        
        /*Take the next destination floor if it exists */
        if(floor_requests != NULL){
            destination_floor = floor_requests->floor;
        }
        
        direction = IDLE;
        return 1;
    }
}

void current_direction() {
    
    if (destination_floor > current_floor) {
        direction = UP;
    }
    else if (destination_floor < current_floor){
        direction = DOWN;
    }
    else {
        direction = IDLE;
    }

}



int main() {

    add_floor_request(0);
    add_floor_request(2);
    add_floor_request(7);
    add_floor_request(3);
    add_floor_request(2);
    add_floor_request(7);


    struct FloorRequest *current = floor_requests;
    
    while (current != NULL) {
        move_to_next_floor();
        current = current->next;
    }
    
    /*Code to go through the request queue if needed*/
    
    /*struct FloorRequest *current = floor_requests;
    while (current != NULL) {
        printf("Current floor request : %d\n",current->floor);
        current = current->next;
    }*/
 
    return 0;
}