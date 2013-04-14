#include "gecode/int.hh"
#include "gecode/driver.hh"

using namespace Gecode;
class A22 : public Script {
protected:
  IntVar x;
  IntVar y;
  IntVar z;
  
public:
  A22(const Options& opt) : x(*this, 1, 9), y(*this, 1, 9), z(*this, 1, 20) {
    IntArgs coefficient(3);
    coefficient[0] = 3;
    coefficient[1] = 4;
    coefficient[2] = -1;
    
    // IntVarArgs array(3);
 //    array[0] = x;
 //    array[1] = y;
 //    array[2] = z;
  
    rel(*this, 3*x + 4*y == z);
    // linear(*this, coefficient, array, IRT_LE, 0);
  
    branch(*this, array, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
  }
  
  A22(bool share, A22& s) : Script(share, s){
    x.update(*this, share, s.x);
    y.update(*this, share, s.y);
    z.update(*this, share, s.z);
  }
  
  virtual Space* copy(bool share) {
    return new A22(share,*this);
  }
  
  void print(std::ostream& os) const {
    os << "x=" << x << std::endl;
    os << "y=" << y << std::endl;
    os << "z=" << z << std::endl;
  }
};

int main(int argc, char* argv[]) {
  Options opt("A22");
  opt.parse(argc,argv);
  Script::run<A22,DFS,Options>(opt);
  return 0;
}