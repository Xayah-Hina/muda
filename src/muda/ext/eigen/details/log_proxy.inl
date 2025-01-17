#define MUDA_LOG_MATRIX()                                                      \
    {                                                                          \
        for(int i = 0; i < M; ++i)                                             \
        {                                                                      \
            for(int j = 0; j < N; ++j)                                         \
            {                                                                  \
                o << val(i, j);                                                \
                if(j != N - 1)                                                 \
                    o << " ";                                                  \
            }                                                                  \
            if(i != M - 1)                                                     \
                o << "\n";                                                     \
        }                                                                      \
        return o;                                                              \
    }

namespace muda
{
template <typename T, int M, int N>
MUDA_DEVICE LogProxy& operator<<(LogProxy& o, const Eigen::Matrix<T, M, N>& val)
    MUDA_LOG_MATRIX();

template <typename T, int M, int N, int MapOptions, typename StrideType>
MUDA_DEVICE LogProxy& operator<<(LogProxy& o,
                                 const Eigen::Map<Eigen::Matrix<T, M, N>, MapOptions, StrideType>& val)
    MUDA_LOG_MATRIX();

template <typename T, int M, int N, int MapOptions, typename StrideType>
MUDA_DEVICE LogProxy& operator<<(
    LogProxy& o, const Eigen::Map<const Eigen::Matrix<T, M, N>, MapOptions, StrideType>& val)
    MUDA_LOG_MATRIX();
}  // namespace muda

#undef MUDA_LOG_MATRIX
