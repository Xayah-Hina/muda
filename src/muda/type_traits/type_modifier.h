#pragma once
#include <type_traits>

namespace muda
{
/*************************************************************************
* 
*                               Raw Type
* 
*************************************************************************/
template <typename T>
using raw_type_t = std::remove_all_extents_t<std::remove_reference_t<T>>;

/*************************************************************************
* 
*                               View Type
* 
*************************************************************************/
template <typename T>
struct read_only_viewer
{
    using type = T;
};

template <typename T>
struct read_write_viewer
{
    using type = T;
};

template <typename T>
using read_only_viewer_t = typename read_only_viewer<T>::type;

template <typename T>
constexpr bool is_read_only_viewer_v = std::is_same_v<T, read_only_viewer_t<T>>;

template <typename T>
using read_write_viewer_t = typename read_write_viewer<T>::type;

template <typename T>
constexpr bool is_read_write_viewer_v = std::is_same_v<T, read_write_viewer_t<T>>;

template <typename T>
constexpr bool is_uniform_viewer_v =
    is_read_only_viewer_v<T> && is_read_write_viewer_v<T>;
}  // namespace muda