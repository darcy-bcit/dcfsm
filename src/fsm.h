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


typedef struct
{
    int from_state_id;
    int current_state_id;
} Environment;


typedef int (*state_func)(Environment *env);


typedef struct
{
    int from_id;
    int to_id;
    state_func perform;
} StateTransition;


int fsm_run(Environment *env, int *from_id, int *to_id, const StateTransition transitions[]);

typedef enum
{
    FSM_IGNORE = -1,
    FSM_INIT,
    FSM_EXIT,
    FSM_APP_STATE_START,
} FSMStates;


#endif // DC_FSM_H
