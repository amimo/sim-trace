#ifndef _SIM_TRACE_H_
#define _SIM_TRACE_H_

#include <stddef.h>

struct CpuState {
  union Register {
    int64_t x;
    int32_t w;
  };

  Register gprs[32]; // [x0, ..., x29, x30, SP]

  inline int64_t WriteSP() const {
    return gprs[31].x;
  }

  inline void WriteSP(int64_t value) {
    gprs[31].x = value;
  }

  inline int64_t ReadLR() { return gprs[30].x; }

  inline int32_t ReadWRegister(unsigned code) const {
    return gprs[code].w;
  }

  inline void WriteWRegister(unsigned code, int32_t value) {
    gprs[code].x = 0;
    gprs[code].w = value;
  }

  inline int64_t ReadXRegister(unsigned code) const {
    return gprs[code].x;
  }

  inline void WriteXRegister(unsigned code, int64_t value) {
    gprs[code].x = value;
  }
};

size_t create_simulator_bridge(void *func, uint32_t *code_buffer, size_t buff_size, void *stack);

#endif //_SIM_TRACE_H_
