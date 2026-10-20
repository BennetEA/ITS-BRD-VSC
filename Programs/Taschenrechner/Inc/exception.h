#ifndef EXCEPTION_U
#define EXCEPTION_U

typedef enum {
   ERR_OK = 0,
   ERR_STACK_FULL,
   ERR_STACK_EMPTY,
   ERR_INSUFFICIENT_ELEMENTS,
   ERR_INVALID_INDEX,
   ERR_DIVISION_BY_ZERO,
   ERR_OVERFLOW,
} Exception;

char *exception_to_string(Exception error);

#endif // !EXCEPTION_U
#define EXCEPTION_U
