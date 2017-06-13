#ifndef JERRYPHOTON_CPP_STATIC_GUARD
#error "This file is only meant to be included by jerryphoton.cpp"
#endif

#include "application.h"
#include "jerryscript.h"
#include "jerryscript-ext/arg.h"

namespace jerryphoton {

static jerry_value_t
photon_delay(const jerry_value_t func,
             const jerry_value_t thiz,
             const jerry_value_t *args,
             const jerry_length_t argscount) {
    double ms = 0;

    jerryx_arg_t validators[] = {
        jerryx_arg_number(&ms, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED)
    };
    const size_t validatorscnt = sizeof(validators) / sizeof(*validators);

    jerry_value_t valid = 
        jerryx_arg_transform_args(args, argscount, validators, validatorscnt);
    if(!jerry_value_is_undefined(valid)) {
        Log.trace("Bad arguments in 'photon.pin' function.");
        return valid;
    }
    jerry_release_value(valid);

    if(ms < 0) {
        static const char msg[] = 
            "photon.delay: milliseconds can't be negative";
        Log.error(msg);
        return jerry_create_error(JERRY_ERROR_RANGE, 
            reinterpret_cast<const jerry_char_t*>(msg));
    }

    delay(ms);

    return jerry_create_undefined();
}

} //namespace jerryphoton
