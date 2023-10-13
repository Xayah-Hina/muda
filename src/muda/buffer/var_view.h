#pragma once
#include <cuda.h>
#include <cinttypes>
#include <muda/viewer/dense.h>

namespace muda
{
template <typename T>
class VarView
{
    T* m_data;

  public:
    VarView(T* data) MUDA_NOEXCEPT : m_data(data) {}
    T*        data() MUDA_NOEXCEPT { return m_data; }
    const T*  data() const MUDA_NOEXCEPT { return m_data; }

    void      copy_from(const T* data);
    void      copy_to(T* data) const;
    void      copy_from(const VarView<T>& data);

    Dense<T>  viewer() MUDA_NOEXCEPT;
    CDense<T> cviewer() const MUDA_NOEXCEPT;
};
}  // namespace muda


#include "details/var_view.inl"