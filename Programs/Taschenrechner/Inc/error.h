#ifndef ERROR_H
#define ERROR_H

typedef enum {
   ERR_OK = 0,
   ERR_STACK_FULL,
   ERR_STACK_EMPTY,
   ERR_INVALID_INDEX,
   ERR_DIVISION_BY_ZERO,
} Error;

const char *error_to_string(Error error);
#endif // !ERROR_H
