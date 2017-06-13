#include "application.h"

#include "jerryphoton/jerryphoton.h"

#include <vector>
#include <cstdint>

using namespace jerryphoton;

// This enables automatic connections to WiFi networks
SYSTEM_MODE(AUTOMATIC);

// Instantiates the default logger, uses the serial port over USB for logging.
static SerialLogHandler loghandler(LOG_LEVEL_ALL);

static String ipaddress;
static uint32_t freemem = 0;

static TCPServer upload(65500);
static void check_upload();

// Called once when the microcontroller boots
void setup() {
    // Enable serial USB.
    USBSerial1.begin();
    
    // Give some time for other system modules to initialize 
    // before starting the loop
    delay(2000);

    Particle.variable("ipAddress", ipaddress);
    Particle.variable("freeMemory", freemem);
    Particle.publish("spark/device/ip");
    
    js::instance().eval(
        "count = 0;"
        "photon.pin.mode(7, 'OUTPUT');"
        "setInterval(function() {"
        "   photon.pin(7, !photon.pin(7));"
        "   photon.log.trace('Hello from JavaScript! ' + count.toString());"
        "   ++count;"
        "}, 1000);"
    );

    upload.begin();

    Log.trace("Setup ended");    
}

void loop() {
    ipaddress = WiFi.localIP().toString();
    freemem = System.freeMemory();

    check_upload();

    js::instance().loop();
}

static void check_upload() {
    using namespace std;
    
    TCPClient client(upload.available());
    if(!client.connected()) {
        return;
    }

    // Remove old JS instance (frees RAM)
    if(js::instantiated()) {
        delete &js::instance();
    }

    vector<uint8_t> buffer;

    while(client.connected()) {
        const size_t required = client.available();
        if(required > 0) {
            const size_t start = buffer.size();
            buffer.resize(start + required);

            Log.trace("Required %i bytes", required);

            const int read = client.read(&buffer[start], required);

            Log.trace("Read %i bytes", read);
        }

        // Keep wifi alive
        Particle.process();
    }

    if(!buffer.empty()) {
        // Read completed, time to load the script
        js::instance().eval(reinterpret_cast<const char*>(buffer.data()),
                            buffer.size());
    } else {
        Log.error("Attempted to load empty script, doing nothing");
    }
}
