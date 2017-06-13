#include "utils.h"

#include "application.h"

#include <vector>

namespace jerryphoton {

jerry_value_t create_string(const char *str) {
    return jerry_create_string(reinterpret_cast<const jerry_char_t*>(str));
}

void log_jerry_error(jerry_value_t error) {
    jerry_value_t prop = create_string("message");
    jerry_value_t msg = jerry_get_property(error, prop);
    
    const size_t size = jerry_get_string_size(msg);    
    std::vector<char> buf(size + 1);
    buf[size] = '\0';
    
    jerry_string_to_char_buffer(msg, 
        reinterpret_cast<jerry_char_t*>(buf.data()), size);
    Log.error("Error evaluating the script, code %s", buf.data());

    jerry_release_value(msg);
    jerry_release_value(prop);
}

}
