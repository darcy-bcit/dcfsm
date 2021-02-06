# DCFSM
   **Yet another Finite State Machine library written in C** 

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



# Installation

This is a c library tested on POSIX systems

Before installing, make sure you have cmake installed. The minimum required version is 3.17. 

## Create a build folder

Navigate to the src folder where `fsm.h` and `fsm.c` are located.

    $ cd src   
Then create a `build` folder using `mkdir` system call:
                
    $ mkdir build
  
Go into the `build` folder and run cmake

	$ cmake ..
	$ cmake --build .
Install the package:

	$ cmake install	.

## Demo

To run the demo, go to the demo folder, do the same as building the package locally using cmake as mentioned above in **Create a build folder**, do not do the install step.

# Quick Start 

## Adding States

In the `States` enum, add the states you need. 
The states will be numbered starting from 2, which has the same value of 
**`FSM_APP_STATE_START`**
```c
typedef enum
{
    STATE_1= FSM_APP_STATE_START,    // 2
    STATE_2,                         // 3
    STATE_3,                         // 4
} States;
``` 
## Modifying State Transitions

The transition array is an array of `StateTransition` struct, which is defined in fsm.h:

Do not touch any code in `fsm.h` or `fsm.c`
```c
typedef struct
{
    int from_id;
    int to_id;
    state_func perform;
} StateTransition;
```

To construct the transition you want, follow the order of :

`from_id` : the state that is represented as the tail of an arrow in your state diagram;

`to_id` :    the state that is represented as the head of an arrow in your state diagram;

`perform`: a function pointer that corresponds to the action represented by the arrow in your diagram

```c
    StateTransition transitions[] =
    {
            { FSM_INIT,STATE_1, &go_to_one },
            { STATE_1, STATE_2, &go_to_two },
            { STATE_2, STATE_3, &go_to_three},
            { STATE_3, STATE_2, &go_to_two },
            { STATE_3, FSM_EXIT,&exit_code },
    };
```
Configure the fsm_run() function so it reads in the initial state, the state that the next state of the initial state, and the transition array.
```c
    int start_state = FSM_INIT;
    int end_state   = STATE_1;
    code = fsm_run((Environment *)&env, &start_state, &end_state, transitions);
```

Last but not least, write the logic in the transition functions. 
Each function needs to have logic of return a state that will lead to the next state after execution.

## Write Execution Logic
```c
static int go_to_one(Environment *env) {
    printf("GOING TO 1\n");
    return STATE_2;
}
static int go_to_two(Environment *env) {
    printf("GOING TO 2\n");
    return STATE_3;
}
static int go_to_three(Environment *env) {
    printf("GOING TO 3\n");
    // if not end
    return STATE_3;
    // if end
    return FSM_EXIT;
}
```

