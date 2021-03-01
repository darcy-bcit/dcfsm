#ifndef DC_FSM_H
#define DC_FSM_H

/*
 * Copyright 2021 D'Arcy Smith + the BCIT CST Datacommunications Option students.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stdbool.h>


/**
 * Generic environment.
 *
 * Used to store variables for a finite state machine to pass to state functions.
 */
struct dc_fsm_environment
{
    const char *name;     /**< Name of the FSM. */
    int from_state_id;    /**< What state is being moved from. */
    int current_state_id; /**< What state is being moved to. */
};


typedef int (*state_func)(struct dc_fsm_environment *env);


/**
 * Represents moving from a state to another state and what function to call
 * when the transition happens.
 */
struct state_transition
{
    int from_id;
    int to_id;
    state_func perform;
};


/**
 * Run the FSM from the from_id state moving into the to_id state.
 *
 * @param env the environment that the FSM uses to store data.
 * @param from_id the state to move from, will store the second to last state
 * @param to_id the state to move to, will store the last state
 * @param transitions the list of state transitions
 * @param verbose print the transitions
 * @return -1 for failure, 0 for success
 */
int dc_fsm_run(struct dc_fsm_environment *env, int *from_id, int *to_id, const struct state_transition transitions[], bool verbose);


/**
 * The standard states that all FSM support.
 */
typedef enum
{
    FSM_IGNORE = -1,
    FSM_INIT,
    FSM_EXIT,
    FSM_APP_STATE_START,
} FSMStates;


#endif // DC_FSM_H
