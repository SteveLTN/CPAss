#include <gecode/int.hh>
#include <gecode/gist.hh>

using namespace Gecode;

class Sudoku : public Space {
protected:
  IntVarArray units;
  IntVarArray block[3][3];
  IntVarArray rows[9];
  IntVarArray columns[9];
public:
  Sudoku(int given_units[9][9]) : units(*this, 81) {
    // copy the given units into our variable unit
    int i,j,s,t,k;
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
    for(i=0; i<9; i++) {
      columns[i] = IntVarArray(*this, 9);
      for(j=0; j<9; j++) {
        columns[i][j] = units[i*9 + j];
      }
      distinct(*this, columns[i], ICL_DOM);
    }

    // distinct in rows
    for(j=0; j<9; j++) {
      rows[j] = IntVarArray(*this, 9);
      for(i=0; i<9; i++) {
        rows[j][i] = units[i*9 + j];
      }
      distinct(*this, rows[j]);
    }

    // distinct in blocks
    for(s=0; s<3; s++) {
      for(t=0; t<3; t++) {
        block[s][t] = IntVarArray(*this, 9);
        for(i=s*3, k=0; i<s*3+3; i++){
          for(j=t*3; j<t*3+3; j++, k++){
            block[s][t][k] = units[i*9 + j];
          }
        }
        distinct(*this, block[s][t]);
      }
    }

    // branching
    branch(*this, units, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
  }
  
  Sudoku(bool share, Sudoku& s) : Space(share, s){
    units.update(*this, share, s.units);
  }
  virtual Space* copy(bool share) {
    return new Sudoku(share,*this);
  }
  void print(std::ostream& os) const {
    int i,j;
    for(i=0; i<9; i++) {
      for(j=0; j<9; j++) {
        os << units[i*9 + j] << " ";
        if (j%3 == 2)
          os << " ";
      }
      os << std::endl;
      if (i%3 == 2)
        os << std::endl;
    }
  }
};

int main(int argc, char* argv[]) {
  int given[9][9] = {
  	{0,0,0, 0,0,3, 0,6,0},
  	{0,0,0, 0,0,0, 0,1,0},
  	{0,9,7, 5,0,0, 0,8,0},

  	{0,0,0, 0,9,0, 2,0,0},
  	{0,0,8, 0,7,0, 4,0,0},
  	{0,0,3, 0,6,0, 0,0,0},

  	{0,1,0, 0,0,2, 8,9,0},
  	{0,4,0, 0,0,0, 0,0,0},
  	{0,5,0, 1,0,0, 0,0,0}
      };
  Sudoku* m = new Sudoku(given);
  Gist::Print<Sudoku> p("Print solution");
  Gist::Options o;
  o.inspect.click(&p);
  Gist::dfs(m,o);
  delete m;
  return 0;
}