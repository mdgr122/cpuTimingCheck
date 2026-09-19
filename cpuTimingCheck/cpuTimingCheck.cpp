// cpuTimingCheck.cpp : Defines the entry point for the application.
//

#include <Windows.h>
#include <intrin.h>
#include <cstdio>
#include <print>

int main()
{
  std::print("PID: {}\n", GetCurrentProcessId());
  std::print("Press Enter to start...\n");
  getchar();
  
  for (int i = 0; i < 20; i++) 
  {
    int regs[4] = {0};
    __cpuid(regs, 1);
    bool hv = (regs[2] >> 31) & 1;

    // --- rdtsc timing pair around a cpuid 000
    unsigned __int64 t1 = __rdtsc();
    int dummy[4];
    __cpuid(dummy, 0); // serializing op, causes VM-exit in a VM
    unsigned __int64 t2 = __rdtsc();

    std::print("[{:2}] cpuid.1: ECX=0x{:08X} | HV Bit={} | RDTSC Delta: {:2} cycles\n", i, regs[2], hv ? 1 : 0, (unsigned long long)(t2 - t1));
    Sleep(500);
  }

  std::print("done\n");
  return 0;
}