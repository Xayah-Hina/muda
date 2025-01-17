namespace muda::eigen
{
template <typename T, FieldEntryLayout Layout, int M, int N>
MUDA_GENERIC auto MatrixEntryViewer<T, Layout, M, N>::operator()(int i)
    -> Eigen::Map<Eigen::Matrix<T, M, N>, 0, Eigen::Stride<Eigen::Dynamic, Eigen::Dynamic>>
{
    auto info = Base::operator()(i);
    return Eigen::Map<Eigen::Matrix<T, M, N>, 0, Eigen::Stride<Eigen::Dynamic, Eigen::Dynamic>>{
        info.begin, Eigen::Stride<Eigen::Dynamic, Eigen::Dynamic>{info.outer_stride, info.inner_stride}};
}

template <typename T, FieldEntryLayout Layout, int M, int N>
MUDA_GENERIC auto CMatrixEntryViewer<T, Layout, M, N>::operator()(int i) const
    -> Eigen::Map<const Eigen::Matrix<T, M, N>, 0, Eigen::Stride<Eigen::Dynamic, Eigen::Dynamic>>
{
    auto info = Base::operator()(i);
    return Eigen::Map<const Eigen::Matrix<T, M, N>, 0, Eigen::Stride<Eigen::Dynamic, Eigen::Dynamic>>{
        info.begin, Eigen::Stride<Eigen::Dynamic, Eigen::Dynamic>{info.outer_stride, info.inner_stride}};
}

template <typename T, FieldEntryLayout Layout>
MUDA_HOST auto make_viewer(FieldEntry<T, Layout, 1, 1>& e)->FieldEntryViewer<T, Layout, 1, 1>
{
    return e.viewer();
}

template <typename T, FieldEntryLayout Layout>
MUDA_HOST auto make_cviewer(FieldEntry<T, Layout, 1, 1>& e)->CFieldEntryViewer<T, Layout, 1, 1>
{
    return e.cviewer();
}

template <typename T, FieldEntryLayout Layout, int M, int N>
MUDA_HOST auto make_viewer(FieldEntry<T, Layout, M, N>& e)->MatrixEntryViewer<T, Layout, M, N>
{
    return MatrixEntryViewer<T, Layout, M, N>{e.viewer()};
}

template <typename T, FieldEntryLayout Layout, int M, int N>
MUDA_HOST auto make_cviewer(const FieldEntry<T, Layout, M, N>& e)
    -> CMatrixEntryViewer<T, Layout, M, N>
{
    return CMatrixEntryViewer<T, Layout, M, N>{e.cviewer()};
}
}  // namespace muda::eigen
