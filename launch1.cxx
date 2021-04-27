#include <cuda_runtime_api.h>

int main() {
  // Here are the archs.
  printf("%s = %d\n", @enum_names(nvvm_arch_t), @enum_values(nvvm_arch_t))...;
}