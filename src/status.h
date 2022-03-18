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
    NORESOURCE,
    FREEWORKER,
    VICTORY,
    LOSS,
    _UNUSED // add new status above this always ^^^

}           t_status;

typedef struct s_status_info {
    t_status    status;
    char        *text;
    char        *info;
}               t_status_info;

void status_print(t_status e, char *buffer);

#endif
