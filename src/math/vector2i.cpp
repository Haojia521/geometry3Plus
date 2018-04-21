#include <math/vector2i.h>

#include <limits>

namespace g3
{
    const Vector2i Vector2i::zero  = Vector2i();
    const Vector2i Vector2i::one   = Vector2i(1, 1);
    const Vector2i Vector2i::axisX = Vector2i(1, 0);
    const Vector2i Vector2i::axisY = Vector2i(0, 1);
}