#include <mex.h>
#include <igl/C_STR.h>
#include <igl/matlab/mexErrMsgTxt.h>
#undef assert
#define assert(isOK) ((isOK) ? (void)0 : (void)mexErrMsgTxt(C_STR(__FILE__<<":"<<__LINE__<<": failed assertion `"<<#isOK<<"'")))
#include <igl/matlab/MexStream.h>
#include <igl/matlab/parse_rhs.h>
#include <Eigen/Core>
#include "ccd_convex_hull.h"

void mexFunction(int nlhs, mxArray *plhs[],
    int nrhs, const mxArray *prhs[])
{
  igl::matlab::MexStream mout;
  std::streambuf *outbuf = std::cout.rdbuf(&mout);

  using namespace igl::matlab;
  using namespace Eigen;

  mexErrMsgTxt(nrhs == 4, "Expected 4 inputs: V1,F1,V2,F2");
  mexErrMsgTxt(nlhs <= 1, "Expected at most 1 output");

  MatrixXd V1, V2;
  MatrixXi F1, F2;
  parse_rhs_double(prhs,   V1);
  parse_rhs_index (prhs+1, F1);
  parse_rhs_double(prhs+2, V2);
  parse_rhs_index (prhs+3, F2);
  mexErrMsgTxt(V1.cols()==3, "V1 must be #V1 by 3");
  mexErrMsgTxt(V2.cols()==3, "V2 must be #V2 by 3");

  CcdConvexHull h1{&V1}, h2{&V2};
  ccd_t ccd = make_ccd(false);

  int result = ccdGJKIntersect(&h1, &h2, &ccd);

  if(nlhs > 0)
  {
    plhs[0] = mxCreateLogicalScalar(result != 0);
  }

  std::cout.rdbuf(outbuf);
}
