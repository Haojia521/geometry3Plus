#include <math/vector3i.h>

namespace g3
{
    const Vector3i Vector3i::zero = Vector3i();
    const Vector3i Vector3i::one = Vector3i(1, 1, 1);
    const Vector3i Vector3i::axisX = Vector3i(1, 0, 0);
    const Vector3i Vector3i::axisY = Vector3i(0, 1, 0);
    const Vector3i Vector3i::axisZ = Vector3i(0, 0, 1);
}
