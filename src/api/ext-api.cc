#undef USING_V8_SHARED // Suddenly breaks because of recent development of cppgc
// #define STOP_USING_V8_SHARED
#include "src/api/api.h"
#include "src/api/api-inl.h"
#include "src/api/ext-api.h"
#include "include/v8-ext.h"
#include "src/wasm/wasm-js.h"
#include "src/execution/isolate.h"
#include "src/wasm/wasm-engine.h"
#include "src/wasm/wasm-result.h"
#include "src/wasm/wasm-objects.h"
#include "src/wasm/wasm-objects-inl.h"
#include "src/objects/objects.h"
#include "src/handles/handles.h"
#include "src/handles/handles-inl.h"
#include "src/wasm/wasm-module-builder.h"
#include "test/fuzzer/fuzzer-support.h"
#include "test/fuzzer/wasm-fuzzer-common.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>
namespace i = v8::internal;

bool v8::ext::GenerateRandomWasm(v8::Isolate* i, std::vector<uint8_t> const& input, std::vector<uint8_t>& output) {
  i::Isolate* isolate = reinterpret_cast<i::Isolate*>(i);

  // Wrap the vector
  v8::base::Vector<const uint8_t> data { input.data(), input.size() };
  
  i::AccountingAllocator allocator;
  i::Zone zone(&allocator, ZONE_NAME);

  i::wasm::ZoneBuffer buffer(&zone);

  std::unique_ptr<i::wasm::WasmValue[]> interpreter_args;
  std::unique_ptr<i::Handle<i::Object>[]> compiler_args;
  // The first byte builds the bitmask to control which function will be
  // compiled with Turbofan and which one with Liftoff.

  i::wasm::fuzzer::WasmCompileFuzzer compilerFuzzer;

  //uint8_t tier_mask = data.empty() ? 0 : data[0];
  //if (!data.empty()) data += 1;
  if (!compilerFuzzer.GenerateModule(isolate, &zone, data, &buffer, false)) {
    return false;
  }

  // Fast marshall to output
  auto generatedSize = buffer.size();
  output.resize(generatedSize);
  std::memcpy(output.data(), buffer.data(), generatedSize);

  return true;
}