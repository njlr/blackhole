#pragma once

#include <ctime>

namespace blackhole {

namespace sink {

namespace rotation {

struct timer_t {
    std::time_t current() const {
        return std::time(nullptr);
    }
};

} // namespace rotation

} // namespace sink

} // namespace blackhole
