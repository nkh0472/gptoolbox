#pragma once
#include <ccd/ccd.h>
#include <Eigen/Core>
#include <limits>

struct CcdConvexHull
{
  const Eigen::MatrixXd *V;
};

static void ccd_convex_hull_support(
  const void *_obj, const ccd_vec3_t *dir, ccd_vec3_t *out)
{
  const CcdConvexHull *hull = static_cast<const CcdConvexHull *>(_obj);
  const Eigen::MatrixXd &V = *hull->V;
  double best = -std::numeric_limits<double>::infinity();
  int best_i = 0;
  for(int i = 0; i < (int)V.rows(); i++)
  {
    double d = dir->v[0]*V(i,0) + dir->v[1]*V(i,1) + dir->v[2]*V(i,2);
    if(d > best){ best = d; best_i = i; }
  }
  out->v[0] = V(best_i, 0);
  out->v[1] = V(best_i, 1);
  out->v[2] = V(best_i, 2);
}

static void ccd_convex_hull_center(
  const void *_obj, ccd_vec3_t *out)
{
  const CcdConvexHull *hull = static_cast<const CcdConvexHull *>(_obj);
  const Eigen::MatrixXd &V = *hull->V;
  out->v[0] = V.col(0).mean();
  out->v[1] = V.col(1).mean();
  out->v[2] = V.col(2).mean();
}

// Fill in a ccd_t struct for two convex hulls (GJK or MPR).
// center callbacks are only needed for MPR — pass with_center=true for those.
static ccd_t make_ccd(bool with_center = false)
{
  ccd_t ccd;
  CCD_INIT(&ccd);
  ccd.support1 = ccd_convex_hull_support;
  ccd.support2 = ccd_convex_hull_support;
  if(with_center)
  {
    ccd.center1 = ccd_convex_hull_center;
    ccd.center2 = ccd_convex_hull_center;
  }
  ccd.max_iterations = 500;
  ccd.epa_tolerance  = 1e-6;
  ccd.mpr_tolerance  = 1e-6;
  return ccd;
}
