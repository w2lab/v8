
#ifndef INCLUDE_V8_EXT_H_
#define INCLUDE_V8_EXT_H_

#include <stddef.h>
#include <stdint.h>

#include "v8config.h"         // NOLINT(build/include_directory)

namespace v8 {
namespace ext {

bool V8_EXPORT GenerateRandomWasm(Isolate* i, std::vector<uint8_t> const& input, std::vector<uint8_t>& output);

} // namespace ext
} // namespace v8
#endif  // INCLUDE_V8_EXT_H_
