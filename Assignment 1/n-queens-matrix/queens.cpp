#include <gecode/int.hh>
#include <gecode/driver.hh>

using namespace Gecode;

class Queens : public Script {
protected:
  IntVarArray chessboard;
  int n;

public:  
  Queens(const SizeOptions& opt) : chessboard(*this, opt.size() * opt.size(),0,1) {
    n = opt.size();
    Matrix<IntVarArray> mat(chessboard, n, n);
    int i, j, m;
    IntVarArray d1(*this, n);
    IntVarArray d2(*this, n);
    
    // n queens together
    count(*this, chessboard, 1, IRT_EQ, n);
    
    // only one queen in a row
    for(i=0; i<n; i++) {
      count(*this, mat.row(i), 1, IRT_LQ, 1);
    }
    
    // only one queen in a column
    for(i=0; i<n; i++) {
      count(*this, mat.col(i), 1, IRT_LQ, 1);
    }
    
    // only one queen in a diagonal
    for(i=0; i<n; i++) {
      for(j=0; j<n-i; j++) {
        d1[j] = mat(j+i, j);
      }
      for(m=j; m<n; m++) {
        d1[m] = IntVar(*this, 0, 0);
      }
      count(*this, d1, 1, IRT_LQ, 1);
      
      for(j=0; j<=i; j++) {
        d2[j] = mat(i-j, j);
      }
      for(m=j; m<n; m++) {
        d2[m] = IntVar(*this, 0, 0);
      }
      count(*this, d2, 1, IRT_LQ, 1);
    }
    
    for(i=0; i<n; i++) {
      for(j=i; j<n; j++) {
        d1[j] = mat(n-1+i-j, j);
      }
      for(m=j; m<n; m++) {
        d1[m] = IntVar(*this, 0, 0);
      }
      count(*this, d1, 1, IRT_LQ, 1);
      
      for(j=n-1-i; j<n; j++) {
        d2[j] = mat(i+j-(n-1), j);
      }
      for(m=j; m<n; m++) {
        d2[m] = IntVar(*this, 0, 0);
      }
      count(*this, d2, 1, IRT_LQ, 1);
    }
       
    branch(*this, chessboard, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
  }
  
  Queens(bool share, Queens& s) : Script(share,s) {
    chessboard.update(*this, share, s.chessboard);
    (*this).n = s.n;
  }
  virtual Space* copy(bool share) {
    return new Queens(share,*this);
  }
  virtual void print(std::ostream& os) const {
    Matrix<IntVarArray> mat(chessboard, n, n);
    os << mat << std::endl;
  }
};

int main(int argc, char* argv[]) {
  SizeOptions opt("Queens");
  opt.size(10);
  opt.parse(argc,argv);
  Script::run<Queens,DFS,SizeOptions>(opt);
  return 0;
}