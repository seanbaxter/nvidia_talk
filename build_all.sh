set -x
circle --cuda-path=/usr/local/cuda -sm_35 -sm_52 -sm_61 -sm_75 launch1.cxx -lcudart && ./launch1
circle --cuda-path=/usr/local/cuda -sm_35 -sm_52 -sm_61 -sm_75 launch2.cxx -lcudart && ./launch2
circle --cuda-path=/usr/local/cuda -sm_35 -sm_52 -sm_61 -sm_75 launch3.cxx -lcudart && ./launch3