#ifndef G3_MATH_INDEX_UTIL
#define G3_MATH_INDEX_UTIL

#include <math/indexType.h>

namespace g3
{
    namespace IndexUtil
    {
        // TODO: review the codes of origin project geometry3Sharp and think over
        //       wether the functions are necessary or not.
        //       (may add new types triangle, edge, vertex_dege, triangle_edge
        //       for class DMesh3.)

        //// test if [a0,a1] and [b0,b1] are the same pair, ignoring order
        //inline bool same_pair_unordered(const Index &a0, const Index &a1,
        //                              const Index &b0, const Index &b1)
        //{ return (a0 == b0 && a1 == b1) || (a0 == b1 && a1 == b0); }

        //// find the vtx that is the same in both ev0 and ev1
        //inline Index find_shared_edge_v(const Index2 &ev0, const Index2 &ev1)
        //{
        //    for (int i0 = 0; i0 < Index2::num; ++i0)
        //        for (int i1 = 0; i1 < Index2::num; ++i1)
        //            if (ev0[i0] == ev1[i1]) return ev0[i0];
        //    return Index::invalidValue;  // return invalid index
        //}

        //// find the other vtx that in the same edge
        //inline Index find_edge_other_v(const Index2 &ev, const Index &v)
        //{
        //    if (ev[0] == v) return ev[1];
        //    else if (ev[1] == v) return ev[0];
        //    else return Index::invalidValue;
        //}

        //// return index of v in tri_verts, or InvalidID if not found
        //inline Index find_tri_index(const Index &v, const Index3 &tri_verts)
        //{
        //    for (int i = 0; i < Index3::num; ++i)
        //        if (tri_verts[i] == v) return Index(i);
        //    return Index::invalidValue;
        //}

        //// return index of e in tri_verts, or InvalidID if not found
    }
}

#endif
