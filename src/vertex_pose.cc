#include "vertex_pose.h"

#include "sophus/so3.hpp"
namespace backend {

void VertexPose::Plus(const VecX &delta)
{
  VecX &parameters = Parameters();
  parameters.head<3>() += delta.head<3>();
  Qd q(parameters[6], parameters[3], parameters[4], parameters[5]);
  q = q * Sophus::SO3d::exp(Vec3(delta[3], delta[4], delta[5]))
              .unit_quaternion();  // right multiplication with so3
  q.normalized();
  parameters[3] = q.x();
  parameters[4] = q.y();
  parameters[5] = q.z();
  parameters[6] = q.w();
}
}  // namespace backend
