#include "application.h"
#include "jerryscript-port.h"

#include <cstdarg>

// Necessary for building
void jerry_port_fatal(jerry_fatal_code_t code) {
    Log.error("JerryScript fatal error, code: %u", code);
    
    LEDStatus led(RGB_COLOR_RED, LED_PATTERN_BLINK);
    led.setActive(true);
    delay(5000);
    
    exit(code);
}

void jerry_port_log(jerry_log_level_t level, const char *format, ...) {
    char *buf = new char[512];
    
    va_list args;
    va_start(args, format);
    
    vsnprintf(buf, 511, format, args);
    switch(level) {
        case JERRY_LOG_LEVEL_TRACE:
            Log.trace("%s", buf);
            break;
        case JERRY_LOG_LEVEL_DEBUG:
            Log.info("%s", buf);
            break;
        case JERRY_LOG_LEVEL_WARNING:
            Log.warn("%s", buf);
            break;
        case JERRY_LOG_LEVEL_ERROR:
            Log.error("%s", buf);
            break;
        default:
            Log.error("%s", buf);
    }
    
    va_end(args);
    
    delete[] buf;
}

