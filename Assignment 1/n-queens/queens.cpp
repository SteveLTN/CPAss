/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2001
 *
 *  Last modified:
 *     $Date: 2012-12-21 01:48:30 +0100 (Fri, 21 Dec 2012) $ by $Author: tack $
 *     $Revision: 13214 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <gecode/driver.hh>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>

using namespace Gecode;

/**
 * \brief %Example: n-%Queens puzzle
 *
 * Place n queens on an n times n chessboard such that they do not
 * attack each other.
 *
 * \ingroup Example
 *
 */
class Queens : public Script {
public:
  /// Position of queens on boards
  IntVarArray q;
  /// Propagation to use for model
  enum {
    PROP_BINARY,  ///< Use only binary disequality constraints
    PROP_MIXED,   ///< Use single distinct and binary disequality constraints
    PROP_DISTINCT ///< Use three distinct constraints
  };
  enum {
    BRANCH_MIN,
    BRANCH_MID,
    BRANCH_MAX_MAX,
    BRANCH_KNIGHT_MOVE
  };
  /// The actual problem
  Queens(const SizeOptions& opt)
    : q(*this,opt.size(),0,opt.size()-1) {
    const int n = q.size();
    switch (opt.propagation()) {
    case PROP_BINARY:
      for (int i = 0; i<n; i++)
        for (int j = i+1; j<n; j++) {
          rel(*this, q[i] != q[j]);
          rel(*this, q[i]+i != q[j]+j);
          rel(*this, q[i]-i != q[j]-j);
        }
      break;
    case PROP_MIXED:
      for (int i = 0; i<n; i++)
        for (int j = i+1; j<n; j++) {
          rel(*this, q[i]+i != q[j]+j);
          rel(*this, q[i]-i != q[j]-j);
        }
      distinct(*this, q, opt.icl());
      break;
    case PROP_DISTINCT:
      distinct(*this, IntArgs::create(n,0,1), q, opt.icl());
      distinct(*this, IntArgs::create(n,0,-1), q, opt.icl());
      distinct(*this, q, opt.icl());
      break;
    }
    switch(opt.branching()) {
    case BRANCH_MIN:
        branch(*this, q, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
        break;
    case BRANCH_MID:
      branch(*this, q, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
      break;
    case BRANCH_MAX_MAX:
      branch(*this, q, INT_VAR_SIZE_MAX(), INT_VAL_MIN());
      break;
    case BRANCH_KNIGHT_MOVE:
      branch(*this, q, INT_VAR_MIN_MIN(), INT_VAL_MED());
      break;
    }
  }

  /// Constructor for cloning \a s
  Queens(bool share, Queens& s) : Script(share,s) {
    q.update(*this, share, s.q);
  }

  /// Perform copying during cloning
  virtual Space*
  copy(bool share) {
    return new Queens(share,*this);
  }

  /// Print solution
  virtual void
  print(std::ostream& os) const {
    os << "queens\t";
    for (int i = 0; i < q.size(); i++) {
      os << q[i] << ", ";
      if ((i+1) % 10 == 0)
        os << std::endl << "\t";
    }
    os << std::endl;
  }
};


/** \brief Main-function
 *  \relates Queens
 */
int main(int argc, char* argv[]) {
  SizeOptions opt("Queens");
  opt.iterations(500);
  opt.size(10);
  opt.propagation(Queens::PROP_DISTINCT);
  opt.propagation(Queens::PROP_BINARY, "binary",
                      "only binary disequality constraints");
  opt.propagation(Queens::PROP_MIXED, "mixed",
                      "single distinct and binary disequality constraints");
  opt.propagation(Queens::PROP_DISTINCT, "distinct",
                      "three distinct constraints");

  opt.branching(Queens::BRANCH_MID, "middle",
    "branch from the middle value");
  opt.branching(Queens::BRANCH_MIN, "min", "branch from the minimum value");
  opt.branching(Queens::BRANCH_MAX_MAX, "reverse", "branch from the minimum value");
  opt.branching(Queens::BRANCH_KNIGHT_MOVE, "knightmove", "branch by knightmove");
  opt.parse(argc,argv);
  Script::run<Queens,DFS,SizeOptions>(opt);
  return 0;
}

// STATISTICS: example-any

