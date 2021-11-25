//
// Created by YANG Zehai on 2021/3/25.
//

#ifndef PUR_RT_PUR_HEAP_DATA_WRAPPER_H
#define PUR_RT_PUR_HEAP_DATA_WRAPPER_H

#include <cstddef>
#include <cstdint>

namespace pur {

namespace rt {

template <class DataType>
struct PurHeapDataWrapper {
  uint32_t mSize;
  uint16_t mSurviveTimesThisGeneration;
  bool mValid;
  bool mMarked;
  size_t mNewAddr;
  DataType mData; // std::vector, std::unordered_map ...
}; // PurHeapDataWrapper

}; // namespace pur::rt

}; // namespace pur

#endif // PUR_RT_PUR_HEAP_DATA_WRAPPER_H
