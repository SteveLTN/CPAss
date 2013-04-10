#include "gecode/int.hh"
#include "gecode/driver.hh"
#include "gecode/minimodel.hh"

using namespace Gecode;

class Queens : public Script {
protected:
  IntVarArray chessboard;

public:  
  Queens(const SizeOptions& opt) : chessboard(*this, opt.size() * opt.size(),0,1) {
    const int n = opt.size();
    Matrix<IntVarArray> mat(chessboard, n, n);
    int i, j, m;
    int diasum;
    // only one queen in a column
    for(i=0; i<n; i++) {
      rel(*this, sum(mat.row(i)) == 1);
    }
    
    // only one queen in a row
    for(i=0; i<n; i++) {
      rel(*this, sum(mat.col(i)) == 1);
    }
    
    // only one queen in a diagonal
    for(m=1; m<n; m++) {
      diasum = 0;
      i = m;
      j = 0;
      while(--i >= 0 && ++j < n) {
        diasum += mat(i,j).val();
      }
      rel(*this, expr(*this, diasum) == 1);
    }
    for(m=0; m<n; m++) {
      diasum = 0;
      i = m;
      j = 0;
      while(++i < n && ++j < n) {
        diasum += mat(i,j).val();        
      }
      rel(*this, expr(*this, diasum) == 1);
    }
    for(m=1; m<n; m++) {
      diasum = 0;
      i = 0;
      j = m;
      while(++i < n && ++j < n) {
        diasum += mat(i,j).val();
      }
      rel(*this, expr(*this, diasum) == 1);
    }
    for(m=1; m<n; m++) {
      diasum = 0;
      i = m;
      j = n-1;
      while(++i < n && --j >= 0) {
        diasum += mat(i,j).val();
      }
      rel(*this, expr(*this, diasum) == 1);
    }
    // end of diagonals
    
    branch(*this, chessboard, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
  }
  
  Queens(bool share, Queens& s) : Script(share,s) {
    chessboard.update(*this, share, s.chessboard);
  }
  virtual Space* copy(bool share) {
    return new Queens(share,*this);
  }
  virtual void print(std::ostream& os) const {
    int n = opt.size();
    int i, j;
    for(i=0; i<n; i++) {
      for(j=0; j<n; j++) {
        os << mat(i,j) << "\t";
      }
      os << std::endl;
    }
  }
};

int main(int argc, char* argv[]) {
  SizeOptions opt("Queens");
  opt.size(10);
IntVars  opt.parse(argc,argv);
  Script::run<Queens,DFS,SizeOptions>(opt);
  return 0;
}