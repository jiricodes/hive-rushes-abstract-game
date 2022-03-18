#ifndef STATUS_H
# define STATUS_H

#include <stdio.h>

typedef enum e_status {
    OKAY,
    OUTOFBOUNDS,
    OCCUPIED,
    DOMED,
    INVALIDACTION,
    OUTOFRANGE,
    FREEWORKER,
    _UNUSED // add new status above this always ^^^

}           t_status;

typedef struct s_status_info {
    t_status    status;
    char        *text;
    char        *info;
}               t_status_info;

#endif