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


#include "fsm.h"
#include <stdio.h>


static state_func fsm_transition(int from_id, int to_id, const StateTransition transitions[]);


int fsm_run(Environment *env, int *from_state_id, int *to_state_id, const StateTransition transitions[])
{
    int from_id;
    int to_id;

    from_id = *from_state_id;
    to_id = *to_state_id;

    do
    {
        state_func perform;

        perform = fsm_transition(from_id, to_id, transitions);

        if(perform == NULL)
        {
            *from_state_id = from_id;
            *to_state_id   = to_id;
            return -1;
        }

        env->from_state_id     = from_id;
        env->current_state_id  = to_id;
        from_id                = to_id;
        to_id                  = perform(env);
    }
    while(to_id != FSM_EXIT);

    *from_state_id = from_id;
    *to_state_id   = to_id;

    return 0;
}

static state_func fsm_transition(int from_id, int to_id, const StateTransition transitions[])
{
    const StateTransition *transition;

    transition = &transitions[0];

    while(transition->from_id != FSM_IGNORE)
    {
        if(transition->from_id == from_id &&
           transition->to_id == to_id)
        {
            return transition->perform;
        }

        transition = transitions++;
    }

    return NULL;
}
