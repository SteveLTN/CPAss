#include <gecode/int.hh>
#include <gecode/gist.hh>

using namespace Gecode;

class Sudoku : public Space {
protected:
  IntVarArray units;
public:
  Sudoku(int[9][9] given_units) : units(*this, 81) {
    // copy the given units into our variable unit
    int i,j;
    for(i=0; i<9; i++) {
      for(j=0; j<9; j++) {
        // if the number is given, we just use a variable whose lower bound and upper bound are the same
        if(given_units[i][j] != 0)
          units[i*9 + j] = IntVar(*this, given_units[i][j], given_units[i][j]);
        else
          units[i*9 + j] = IntVar(*this, 1, 9);
      }
    }
    
    // distinct in columns
    
    // distinct in rows
    
    // distinct in blocks
    
  }
}