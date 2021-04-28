#include <cstdio>
#include <cuda_runtime_api.h>

template<int x, int... y>
constexpr int upper_bound = x < y ...?? int... : sizeof...y;

// tuning params
using nt  [[attribute   ]] = int;
using vt  [[attribute(1)]] = int;
using occ [[attribute(0)]] = int;

// flags
using strided    [[attribute]] = void;
using persistent [[attribute]] = void;

enum my_tuning_t {
  kepler  [[ .nt=128, .vt=5               ]] = 35,
  maxwell [[ .nt=256, .vt=7,  .persistent ]] = 52,
  pascal  [[ .nt=64,  .vt=11, .strided    ]] = 61,
  turing  [[ .nt=256, .vt=15, .occ=3      ]] = 75,
  ampere  [[ .nt=256, .vt=19, .strided    ]] = 86,
};

template<typename tuning_t>
__global__ void kernel() {
  // Find the best tunings for this target's PTX version.

  // Loop over all architectures specified at the compiler command line.
  @meta for enum(nvvm_arch_t arch : nvvm_arch_t) {

    // Enter the architecture being lowered to PTX.
    if target(arch == __nvvm_arch) {
      
      // Search for the best tuning for this architecture.
      constexpr int index = upper_bound<arch, @enum_values(tuning_t)...>;

      // There must be a viable tuning.
      static_assert(index, @string("No viable tuning for ", @enum_name(arch)));

      // Pluck out the best one.
      constexpr tuning_t tuning = @enum_value(tuning_t, index - 1);

      // Report what we've chosen.
      @meta printf("Selecting tuning \"%s\" for arch %s\n", @enum_name(tuning),
        @enum_name(arch));

      // Set the __launch_bounds__.
      __nvvm_maxntidx(@enum_attribute(tuning, nt));
      __nvvm_minctasm(@enum_attribute(tuning, occ));

      // Call the user function.
      printf("\"%s\"=%d, arch=%d, nt=%d, vt=%d, occ=%d\n", 
        @enum_name(tuning), 
        (int)tuning,
        (int)arch,
        @enum_attribute(tuning, nt), 
        @enum_attribute(tuning, vt),
        @enum_attribute(tuning, occ)
      );
    }
  }
}

int main() {
  kernel<my_tuning_t><<<1, 1>>>();
  cudaDeviceSynchronize();
}