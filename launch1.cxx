#include <cstdio>

__global__ void kernel() {
  // Generate a compile-time for loop over the enums inside the kernel.
  @meta for enum(nvvm_arch_t arch : nvvm_arch_t) {

    // Enter an if-target when the current target matches arch.
    if target(arch == __nvvm_arch) {

      // Do something with the compile-time arch.
      @meta printf("arch %s\n", @enum_name(arch));
    }
  }
}

int main() { 
  // Or just simply print out the archs.
  printf("%s=%d\n", @enum_names(nvvm_arch_t), @enum_values(nvvm_arch_t))...;
}