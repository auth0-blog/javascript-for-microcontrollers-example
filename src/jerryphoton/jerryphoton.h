#ifndef JERRYPHOTON_H
#define JERRYPHOTON_H

#include <cstddef>

namespace jerryphoton {

class js final {
public:
    static js& instance();
    ~js();

    static bool instantiated();

    // Disable copies
    js(const js&) = delete;
    js& operator=(const js&) = delete;

    // Disable move
    js(js&&) = delete;
    js& operator=(js&&) = delete;

    void eval(const char* script, size_t size = 0);
    
    void loop();

    struct impl;
private:
    js();

    impl *pimpl_;
}; // class js

} // nameslace jerryphoton

#endif //JERRYPHOTON_H
