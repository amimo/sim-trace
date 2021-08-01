#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include "sim-trace.h"

int g = 0;
int target_function(int a, int b, int &result) {
  result = a + b;
  g = result;
  return result;
}

int main(int argc, char *argv[]) {
  size_t buffer_size = getpagesize();
  size_t stack_size = 1 * 1024 * 1024;

  uint32_t *code_buffer = (uint32_t *) mmap(nullptr,
                                            buffer_size,
                                            PROT_READ | PROT_WRITE | PROT_EXEC,
                                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  assert(code_buffer != MAP_FAILED);
  char *stack = (char *) mmap(nullptr, stack_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  assert(stack != MAP_FAILED);

  void *sp = stack + stack_size - 256;
  size_t bridge_size = 0;

  create_simulator_bridge((void *) target_function, code_buffer, buffer_size, sp);

  int (*f)(int, int, int &) = reinterpret_cast<int (*)(int, int, int &)>(code_buffer);
  int result;
  int n = f(3, 5, result);

  assert(n == 8);
  assert(result == 8);
  assert(g == 8);

  printf("stack result  = %d, register result = %d, global result = %d\n", result, n, g);

  return 0;
}
