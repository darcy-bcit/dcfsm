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


#include <dc_fsm/fsm.h>
#include <stdio.h>
#include <stdlib.h>


struct echo_environment
{
    struct dc_fsm_environment common;
    int c;
};


static int read_input(struct echo_environment *env);
static int write_output(struct echo_environment *env);
_Noreturn static int read_error(struct echo_environment *env);
_Noreturn static int write_error(struct echo_environment *env);


typedef enum
{
    READ = FSM_APP_STATE_START,    // 2
    WRITE,                         // 3
    ERROR,                         // 4
} States;


int main(int argc, char *argv[])
{
    struct echo_environment env;
    struct state_transition transitions[] =
    {
            { FSM_INIT,   READ,       (state_func)&read_input   },
            { READ,       ERROR,      (state_func)&read_error   },
            { READ,       WRITE,      (state_func)&write_output },
            { READ,       FSM_EXIT,   (state_func)NULL          },
            { WRITE,      ERROR,      (state_func)&write_error  },
            { WRITE,      READ,       (state_func)&read_input   },
            { FSM_IGNORE, FSM_IGNORE, (state_func)NULL          },
    };
    int code;
    int start_state;
    int end_state;

    env.common.name = "echo";
    start_state = FSM_INIT;
    end_state   = READ;
    code = dc_fsm_run((struct dc_fsm_environment *)&env, &start_state, &end_state, transitions, false);

    if(code != 0)
    {
        fprintf(stderr, "Cannot move from %d to %d\n", start_state, end_state);

        return EXIT_FAILURE;
    }

//    fprintf(stderr, "Exiting state %d\n", start_state);

    (void)argc;
    (void)argv;

    return EXIT_SUCCESS;
}

static int read_input(struct echo_environment *env)
{
    env->c = getchar();

    if(env->c == EOF)
    {
        if(ferror(stdin))
        {
            return ERROR;
        }

        return FSM_EXIT;
    }

    return WRITE;
}

static int write_output(struct echo_environment *env)
{
    int ret_val;

    ret_val = putchar(env->c);

    if(ret_val == EOF)
    {
        return ERROR;
    }

    return READ;
}

_Noreturn static int read_error(struct echo_environment *env)
{
    perror("getc");

    (void)env;

    exit(EXIT_FAILURE);
}

_Noreturn static int write_error(struct echo_environment *env)
{
    perror("putc");

    (void)env;

    exit(EXIT_FAILURE);
}
