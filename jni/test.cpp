#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include "sim-trace.h"

int my_printf(const char *format, ...)
{
  char buffer[4096];
  size_t buff_size = sizeof(buffer);
  va_list ap;

  va_start(ap, format);
  int n = vsnprintf(buffer, buff_size, format, ap);
  va_end(ap);

  return n > 0 ? write(STDOUT_FILENO, buffer, n) : n;
}

int g = 0;
int target_function(int a, int b, int &result) {
  my_printf("[+] enter target_function\n");
  result = a + b;
  g = result;
  my_printf("[+] stack result  = %d, global result = %d\n", result, g);
  my_printf("[+] leave target_function\n");
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
