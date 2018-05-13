//
// Created by mayfa on 8.5.18.
//

#ifndef HTTP_COMMUNICATOR_RT_ASSERT_H
#define HTTP_COMMUNICATOR_RT_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#define rt_assert(condition, message) {\
    if (!(condition)) {\
        printf(message);\
        exit(1);\
    }\
};

#endif //HTTP_COMMUNICATOR_RT_ASSERT_H
