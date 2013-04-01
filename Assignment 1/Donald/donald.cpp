#include "gecode/int.hh"
#include "gecode/search.hh"

using namespace Gecode;
class Donald : public Space{
protected:
  IntVarArray li;
public:
  Donald(void) : li(*this, 10, 0, 9) {
    IntVar d(li[0]), o(li[1]), n(li[2]), a(li[3]), 
      l(li[4]), g(li[5]), e(li[6]), r(li[7]),
      b(li[8]), t(li[9]);
    
      // no leading zeros
      rel(*this, d, IRT_NQ, 0);
      rel(*this, g, IRT_NQ, 0);
      rel(*this, r, IRT_NQ, 0);
      
      // all letters are distinct
      distinct(*this, li);
      
      // linear equation
      IntArgs c(6+6+6); IntVarArgs x(6+6+6);
      c[0] = 100000; c[1] = 10000; c[2] = 1000; c[3] = 100; c[4] = 10; c[5] = 1;
      x[0] = d;      x[1] = o;     x[2] = n;    x[3] = a;   x[4] = l;  x[5] = d;
      c[6] = 100000; c[7] = 10000; c[8] = 1000; c[9] = 100; c[10] = 10; c[11] = 1;
      x[6] = g;      x[7] = e;     x[8] = r;    x[9] = a;   x[10] = l;  x[11] = d;
      c[12] = -100000; c[13] = -10000; c[14] = -1000; c[15] = -100; c[16] = -10; c[17] = -1;
      x[12] = r;       x[13] = o;      x[14] = b;     x[15] = e;    x[16] = r;   x[17] = t;
      
      linear(*this, c, x, IRT_EQ, 0);
      
      // post branching
      branch(*this, li, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
  }
  
  // search support
  Donald(bool share, Donald& s) : Space(share, s) {
    li.update(*this, share, s.li);
  }
  virtual Space* copy(bool share) {
    return new Donald(share,*this);
  }
  // print solution
  void print(void) const {
    std::cout << li << std::endl;
  }
};

// main function
int main(int argc, char* argv[]) {
  
  // create model and search engine
  Donald* m = new Donald;
  DFS<Donald> e(m);
  delete m;
  
  // search and print all solutions
  while (Donald* s = e.next()) {
    s->print(); delete s;
  }
  return 0;
}