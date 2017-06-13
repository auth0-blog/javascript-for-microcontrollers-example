#ifndef JERRYPHOTON_UTILS_H
#define JERRYPHOTON_UTILS_H

#include "jerryscript.h"

namespace jerryphoton {

void log_jerry_error(jerry_value_t error);

jerry_value_t create_string(const char *str);

}

#endif //JERRYPHOTON_UTILS_H

