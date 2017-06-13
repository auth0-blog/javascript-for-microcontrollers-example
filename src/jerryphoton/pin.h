#ifndef JERRYPHOTON_CPP_STATIC_GUARD
#error "This file is only meant to be included by jerryphoton.cpp"
#endif

#include "application.h"
#include "jerryscript.h"
#include "jerryscript-ext/arg.h"

namespace jerryphoton {

static jerry_value_t
photon_pin(const jerry_value_t func,
           const jerry_value_t thiz,
           const jerry_value_t *args,
           const jerry_length_t argscount) {
    double pin = 0;
    bool value = false;

    jerryx_arg_t validators[] = {
        jerryx_arg_number(&pin, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
        jerryx_arg_boolean(&value, JERRYX_ARG_COERCE, JERRYX_ARG_OPTIONAL)
    };
    const size_t validatorscnt = sizeof(validators) / sizeof(*validators);

    jerry_value_t valid = 
        jerryx_arg_transform_args(args, argscount, validators, validatorscnt);
    if(!jerry_value_is_undefined(valid)) {
        Log.trace("Bad arguments in 'photon.pin' function.");
        return valid;
    }
    jerry_release_value(valid);

    if(argscount == 1) {
        value = digitalRead(pin);
        return jerry_create_boolean(value);
    } else {
        digitalWrite(pin, value);
        return jerry_create_undefined();
    }
}

static jerry_value_t
photon_pin_mode(const jerry_value_t func,
                const jerry_value_t thiz,
                const jerry_value_t *args,
                const jerry_length_t argscount) {
    double pin = 0;
    char mode[10] = { 0 };

    jerryx_arg_t validators[] = {
        jerryx_arg_number(&pin, JERRYX_ARG_COERCE, JERRYX_ARG_REQUIRED),
        jerryx_arg_string(mode, sizeof(mode) - 1, 
            JERRYX_ARG_NO_COERCE, JERRYX_ARG_OPTIONAL)
    };
    const size_t validatorscnt = sizeof(validators) / sizeof(*validators);

    jerry_value_t valid = 
        jerryx_arg_transform_args(args, argscount, validators, validatorscnt);
    if(!jerry_value_is_undefined(valid)) {
        Log.trace("Bad arguments in 'photon.pin.mode' function.");
        return valid;
    }
    jerry_release_value(valid);

    if(argscount == 1) {
        jerry_value_t result;
        switch(getPinMode(pin)) {
            case OUTPUT:
                result = jerry_get_property(thiz, jerry_create_string(
                    reinterpret_cast<const jerry_char_t*>("OUTPUT")));
                break;
            case INPUT:
                result = jerry_get_property(thiz, jerry_create_string(
                    reinterpret_cast<const jerry_char_t*>("INPUT")));
                break;
            case INPUT_PULLUP:
                result = jerry_get_property(thiz, jerry_create_string(
                    reinterpret_cast<const jerry_char_t*>("INPUT_PULLUP")));
                break;
            case INPUT_PULLDOWN:
                result = jerry_get_property(thiz, jerry_create_string(
                    reinterpret_cast<const jerry_char_t*>("INPUT_PULLDOWN")));
                break;
            default:
                result = jerry_create_error(JERRY_ERROR_COMMON, 
                    reinterpret_cast<const jerry_char_t*>(
                        "photon.pin.mode: unknown pin mode (bad pin number?)"));
        }
        return result;
    } else {
        if(strcmp(mode, "OUTPUT") == 0) {
            pinMode(pin, OUTPUT);
        } else if(strcmp(mode, "INPUT") == 0) {
            pinMode(pin, INPUT);
        } else if(strcmp(mode, "INPUT") == 0) {
            pinMode(pin, INPUT_PULLUP);
        } else if(strcmp(mode, "INPUT") == 0) {
            pinMode(pin, INPUT_PULLDOWN);
        } else {
            return jerry_create_error(JERRY_ERROR_COMMON, 
                reinterpret_cast<const jerry_char_t*>(
                    "photon.pin.mode: unknown pin mode"));
        }
        return jerry_create_undefined();
    }
}

} //namespace jerryphoton
