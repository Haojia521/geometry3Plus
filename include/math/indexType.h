#ifndef G3_MATH_INDEX_TYPE
#define G3_MATH_INDEX_TYPE

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
        inline bool valid() { return _index != invalidValue; }
        inline void invalidate() { _index = invalidValue; }

        // operator functions
        inline operator value_type() { return _index; }

        inline bool operator == (const self_type &i) const { return _index == i._index; }
        inline bool operator != (const self_type &i) const { return !((*this) == i); }

    private:
        value_type _index;
    };

    const Index::value_type Index::invalidValue = 0xffffffff;

    template<int n>
    class IndexTemplate
    {
    public:
        typedef Index            value_type;
        typedef IndexTemplate<n> self_type;

        // static values
        static const self_type zero;
        static const self_type one;
        static const self_type invalid;
        static const int num = n;

        // constructors
        IndexTemplate() { for (int j = 0; j < n; ++j) _indices[j] = value_type::invalidValue; }
        IndexTemplate(value_type i) { for (int j = 0; j < n; ++j) _indices[j] = i; }
        IndexTemplate(const self_type &i) { for (int j = 0; j < n; ++j) _indices[j] = i._indices[j]; }

        // functions
        inline bool valid()
        {
            for (int j = 0; j < n; ++j) if (!_indices[j].valid()) return false;
            return true;
        }

        inline void invalidate()
        { for (int j = 0; j < n; ++j) _indices[j].invalidate(); }

        // TODO : realize funtion array()

        // operator functions
        inline value_type  operator [] (int i) const
        { return (i >= 0 && i < num) ? _indices[i] : (i < 0) ? _indices[0] : _indices[num - 1]; }
        inline value_type& operator [] (int i)
        { return (i >= 0 && i < num) ? _indices[i] : (i < 0) ? _indices[0] : _indices[num - 1]; }

        inline self_type& operator = (const self_type &other)
        { for (int j = 0; j < n; ++j) _indices[j] = other._indices[j]; return *this; }

        inline bool operator == (const self_type &other) const
        {
            for (int j = 0; j < n; ++j) if (!(_indices[j] == other[j])) return false;
            return true;
        }

        inline bool operator != (const self_type &other) const
        { return !((*this) == other); }

    protected:
        value_type _indices[n];
    };

    template<int n>
    const IndexTemplate<n> IndexTemplate<n>::zero = IndexTemplate<n>(0);

    template<int n>
    const IndexTemplate<n> IndexTemplate<n>::one = IndexTemplate<n>(1);

    template<int n>
    const IndexTemplate<n> IndexTemplate<n>::invalid = IndexTemplate<n>(Index::invalidValue);

    class Index2 : public IndexTemplate<2>
    {
    public:
        typedef IndexTemplate<2> base_type;

        Index2() : base_type() {}
        Index2(value_type i) : base_type(i) {}
        Index2(value_type i0, value_type i1)
        { _indices[0] = i0; _indices[1] = i1; }
    };

    class Index3 : public IndexTemplate<3>
    {
    public:
        typedef IndexTemplate<3> base_type;

        Index3() : base_type() {}
        Index3(value_type i) : base_type(i) {}
        Index3(value_type i0, value_type i1, value_type i2)
        { _indices[0] = i0; _indices[1] = i1; _indices[2] = i2; }
        Index3(value_type i0, value_type i1, value_type i2, bool cycle)
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
        Index4(value_type i) : base_type(i) {}
        Index4(value_type i0, value_type i1, value_type i2, value_type i3)
        { _indices[0] = i0; _indices[1] = i1; _indices[2] = i2; _indices[3] = i3; }
    };
}

#endif
