#pragma once
#include <string>
#include <chrono>

#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>

#include <cuda_profiler_api.h>
#include <nvtx3/nvToolsExt.h>
#include <nvtx3/nvToolsExtCuda.h>

#include "check/checkCudaErrors.h"

namespace muda
{
template <typename F>
MUDA_HOST double ProfileHost(F&& f)
{
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count() / 1000.0;
}

class Profile
{
    bool need_pop;

  public:
    Profile() MUDA_NOEXCEPT
        : need_pop(false)
    {
        checkCudaErrors(cudaProfilerStart());
    }
    Profile(const std::string& name) MUDA_NOEXCEPT
        : need_pop(true)
    {
        nvtxEventAttributes_t eventAttrib = {0};
        eventAttrib.version               = NVTX_VERSION;
        eventAttrib.size                  = NVTX_EVENT_ATTRIB_STRUCT_SIZE;
        eventAttrib.colorType             = NVTX_COLOR_ARGB;
        eventAttrib.color                 = 255;
        eventAttrib.messageType           = NVTX_MESSAGE_TYPE_ASCII;
        eventAttrib.message.ascii         = name.c_str();
        nvtxRangePushEx(&eventAttrib);

        checkCudaErrors(cudaProfilerStart());
    }
    ~Profile()
    {
        checkCudaErrors(cudaProfilerStop());
        if(need_pop)
            nvtxRangePop();
    }
};

class RangeName
{
  public:
    RangeName(const std::string& name) MUDA_NOEXCEPT
    {
        nvtxEventAttributes_t eventAttrib = {0};
        eventAttrib.version               = NVTX_VERSION;
        eventAttrib.size                  = NVTX_EVENT_ATTRIB_STRUCT_SIZE;
        eventAttrib.colorType             = NVTX_COLOR_ARGB;
        eventAttrib.color                 = 255;
        eventAttrib.messageType           = NVTX_MESSAGE_TYPE_ASCII;
        eventAttrib.message.ascii         = name.c_str();
        nvtxRangePushEx(&eventAttrib);
    }

    ~RangeName() { nvtxRangePop(); }
};
}  // namespace muda