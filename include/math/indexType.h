#ifndef G3_MATH_INDEX_TYPE
#define G3_MATH_INDEX_TYPE

#include <type_traits>

namespace g3
{
    class Index
    {
    public:
        typedef unsigned int value_type;
        typedef Index        self_type;

        // static values
        static const value_type invalidValue;

        // constructions
        Index() { _index = invalidValue; };
        Index(int i) { if (i < 0) _index = invalidValue; else _index = i; }
        Index(value_type i) { _index = i; }

        // functions
        bool valid() { return _index != invalidValue; }
        void invalidate() { _index = invalidValue; }

        // operator functions
        operator value_type() { return _index; }

        bool operator == (const self_type &i) const { return _index == i._index; }
        bool operator != (const self_type &i) const { return !((*this) == i); }

    private:
        value_type _index;
    };

    const Index::value_type Index::invalidValue = 0xffffffff;

    template<int N, class = typename std::enable_if<(N > 0)>::type>
    class IndexTemplate
    {
    public:
        typedef Index            index_type;
        typedef IndexTemplate<N> self_type;

        // static values
        static const self_type zero;
        static const self_type one;
        static const self_type invalid;
        static const int num = N;

        // constructors
        IndexTemplate() { for (int j = 0; j < N; ++j) _indices[j] = index_type::invalidValue; }
        IndexTemplate(index_type i) { for (int j = 0; j < N; ++j) _indices[j] = i; }
        IndexTemplate(const self_type &i) { for (int j = 0; j < N; ++j) _indices[j] = i._indices[j]; }

        // functions
        bool valid()
        {
            for (int j = 0; j < N; ++j) if (!_indices[j].valid()) return false;
            return true;
        }

        void invalidate()
        { for (int j = 0; j < N; ++j) _indices[j].invalidate(); }

        // TODO : realize funtion array()

        // operator functions
        index_type  operator [] (int i) const
        { return (i >= 0 && i < num) ? _indices[i] : (i < 0) ? _indices[0] : _indices[num - 1]; }
        index_type& operator [] (int i)
        { return (i >= 0 && i < num) ? _indices[i] : (i < 0) ? _indices[0] : _indices[num - 1]; }

        self_type& operator = (const self_type &other)
        { for (int j = 0; j < N; ++j) _indices[j] = other._indices[j]; return *this; }

        bool operator == (const self_type &other) const
        {
            for (int j = 0; j < N; ++j) if (!(_indices[j] == other[j])) return false;
            return true;
        }

        bool operator != (const self_type &other) const
        { return !((*this) == other); }

    protected:
        index_type _indices[N];
    };

    template<int N, class U>
    const IndexTemplate<N> IndexTemplate<N, U>::zero = IndexTemplate<N>(0);

    template<int N, class U>
    const IndexTemplate<N> IndexTemplate<N, U>::one = IndexTemplate<N>(1);

    template<int N, class U>
    const IndexTemplate<N> IndexTemplate<N, U>::invalid = IndexTemplate<N>(Index::invalidValue);

    class Index2 : public IndexTemplate<2>
    {
    public:
        typedef IndexTemplate<2> base_type;

        Index2() : base_type() {}
        Index2(index_type i) : base_type(i) {}
        Index2(index_type i0, index_type i1)
        { _indices[0] = i0; _indices[1] = i1; }
    };

    class Index3 : public IndexTemplate<3>
    {
    public:
        typedef IndexTemplate<3> base_type;

        Index3() : base_type() {}
        Index3(index_type i) : base_type(i) {}
        Index3(index_type i0, index_type i1, index_type i2)
        { _indices[0] = i0; _indices[1] = i1; _indices[2] = i2; }
        Index3(index_type i0, index_type i1, index_type i2, bool cycle)
        {
            _indices[0] = i0;
            if (cycle) { _indices[1] = i2; _indices[2] = i1; }
            else       { _indices[1] = i1; _indices[2] = i2; }
        }
    };

    class Index4 : public IndexTemplate<4>
    {
    public:
        typedef IndexTemplate<4> base_type;

        Index4() : base_type() {}
        Index4(index_type i) : base_type(i) {}
        Index4(index_type i0, index_type i1, index_type i2, index_type i3)
        { _indices[0] = i0; _indices[1] = i1; _indices[2] = i2; _indices[3] = i3; }
    };
}

#endif
