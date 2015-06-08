#include <Grid.h>

using namespace std;
using namespace Grid;
using namespace Grid::QCD;

int main (int argc, char ** argv)
{
  Grid_init(&argc,&argv);

  std::cout << "Testing Remez"<<std::endl;

  double     lo=0.01;
  double     hi=1.0;
  int precision=64;
  int    degree=10;
  AlgRemez remez(0.001,1.0,precision);

  ////////////////////////////////////////
  // sqrt and inverse sqrt
  ////////////////////////////////////////

  std::cout << "Generating degree "<<degree<<" for x^(1/2)"<<std::endl;
  remez.generateApprox(degree,1,2);
  MultiShiftFunction Sqrt(remez,1.0,false);
  MultiShiftFunction InvSqrt(remez,1.0,true);


  std::cout << "Generating degree "<<degree<<" for x^(1/4)"<<std::endl;
  remez.generateApprox(degree,1,4);
  MultiShiftFunction SqrtSqrt(remez,1.0,false);
  MultiShiftFunction InvSqrtSqrt(remez,1.0,true);

  
  ofstream gnuplot(std::string("Sqrt.gnu"),std::ios::out|std::ios::trunc);
  Sqrt.gnuplot(gnuplot);

  ofstream gnuplot_inv(std::string("InvSqrt.gnu"),std::ios::out|std::ios::trunc);
  InvSqrt.gnuplot(gnuplot);

  double x=0.6789;
  double sx=sqrt(x);
  double ssx=sqrt(sx);
  double isx=1.0/sx;
  double issx=1.0/ssx;

  double asx  =Sqrt.approx(x);
  double assx =SqrtSqrt.approx(x);
  double aisx =InvSqrt.approx(x);
  double aissx=InvSqrtSqrt.approx(x);

  std::cout << "x^(1/2) : "<<sx<<" "<<asx<<std::endl;
  std::cout << "x^(1/4) : "<<ssx<<" "<<assx<<std::endl;
  std::cout << "x^(-1/2): "<<isx<<" "<<aisx<<std::endl;
  std::cout << "x^(-1/4): "<<issx<<" "<<aissx<<std::endl;
  assert(fabs(sx-asx)<1.0e-6);
  assert(fabs(ssx-assx)<1.0e-6);
  assert(fabs(isx-aisx)<1.0e-6);
  assert(fabs(issx-aissx)<1.0e-6);

  Grid_finalize();
}
