#include <sys/mman.h>
#include <unistd.h>

#include "sim-trace.h"
#include "vixl/src/aarch64/macro-assembler-aarch64.h"

using namespace vixl;
using namespace vixl::aarch64;

extern "C" {
void __clear_cache(void *beg, void *end);
}

#define __ masm->

static void interp_function(void *func, CpuState *state) {
  Decoder decoder;
  Simulator simulator(&decoder);
  simulator.SetTraceParameters(LOG_ALL);
  const Instruction *pc = static_cast<const Instruction *>(func);
  for (int code = 0; code < 31; code++) {
    simulator.WriteXRegister(code, state->ReadXRegister(code));
  }
  simulator.WriteSp(state->WriteSP());

  simulator.RunFrom(pc);

  for (int code = 0; code < 31; code++) {
    state->WriteXRegister(code, simulator.ReadXRegister(code));
  }
}

// caller -> target function
//  ==>
// caller -> simulator bridge -> interp_function -> simulator -> simulate target function

size_t create_simulator_bridge(void *func, uint32_t *code_buffer, size_t buff_size, void *stack) {
  MacroAssembler *masm = new MacroAssembler((uint8_t *) code_buffer, buff_size);

  {
    __ mov(ip0, sp);
    __ Mov(ip1, (uint64_t) stack);

    // switch to simulator stack
    __ mov(sp, ip1);

    MemOperand tos(sp, -2L * kXRegSizeInBytes, PreIndex);

    // save GPRs
    // x31 = ip0 = original sp
    __ stp(x30, ip0, tos);

    for (int i = 28; i >= 0; i -= 2) {
      // STP Xn, Xm, [SP, #-16]!
      __ stp(Register::GetXRegFromCode(i), Register::GetXRegFromCode(i + 1), tos);
    }

    __ Mov(x0, (uint64_t) func);
    __ mov(x1, sp);
    __ Mov(ip0, (uint64_t) interp_function);
    // x0 = target function
    // x1 = cpu state
    __ blr(ip0);

    // restore GPRs
    for (int i = 0; i <= 28; i += 2) {
      __ ldp(Register::GetXRegFromCode(i),
             Register::GetXRegFromCode(i + 1),
             MemOperand(sp, 2L * kXRegSizeInBytes, PostIndex));
    }
    __ ldp(x30, ip0, MemOperand(sp, 2L * kXRegSizeInBytes, PostIndex));
    // restore sp
    __ mov(sp, ip0);
    __ ret();
  }

  masm->FinalizeCode();
  size_t code_size = masm->GetSizeOfCodeGenerated();
  void *code_end = masm->GetCursorAddress<void *>();
  delete masm;

  __clear_cache((void *) code_buffer, code_end);

  return code_size;
}
