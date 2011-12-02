/*********************                                                        */
/*! \file instantiator_arith_instantiator.h
 ** \verbatim
 ** Original author: ajreynol
 ** Major contributors: none
 ** Minor contributors (to current version): none
 ** This file is part of the CVC4 prototype.
 ** Copyright (c) 2009, 2010, 2011  The Analysis of Computer Systems Group (ACSys)
 ** Courant Institute of Mathematical Sciences
 ** New York University
 ** See the file COPYING in the top-level source directory for licensing
 ** information.\endverbatim
 **
 ** \brief instantiator_arith_instantiator
 **/


#include "cvc4_private.h"

#ifndef __CVC4__INSTANTIATOR_ARITH_H
#define __CVC4__INSTANTIATOR_ARITH_H

#include "theory/instantiation_engine.h"
#include "theory/arith/arithvar_node_map.h"

#include "util/stats.h"

namespace CVC4 {
namespace theory {
namespace arith {

class InstantiatorTheoryArith : public Instantiator{
  friend class InstantiationEngine;
private:
  /** delta */
  std::map< TypeNode, Node > d_deltas;
  /** for each quantifier, simplex rows */
  std::map< Node, std::vector< ArithVar > > d_instRows;
  /** tableaux */
  std::map< ArithVar, Node > d_tableaux_term;
  std::map< ArithVar, std::map< Node, Node > > d_tableaux_ce_term;
  std::map< ArithVar, std::map< Node, Node > > d_tableaux;
  /** ce tableaux */
  std::map< ArithVar, std::map< Node, Node > > d_ceTableaux;
  /** get value */
  Node getTableauxValue( Node n, bool minus_delta = false );
  Node getTableauxValue( ArithVar v, bool minus_delta = false );
  /** do instantiation */
  bool doInstantiation( Node term, ArithVar x, InstMatch* m, Node var );
  bool doInstantiation2( Node term, ArithVar x, InstMatch* m, Node var, bool minus_delta = false );
public:
  InstantiatorTheoryArith(context::Context* c, InstantiationEngine* ie, Theory* th);
  ~InstantiatorTheoryArith() {}

  /** check function, assertion is asserted to theory */
  void check( Node assertion );
  /**  reset instantiation */
  void resetInstantiationRound();
  /** identify */
  std::string identify() const { return std::string("InstantiatorTheoryArith"); }
  /** print debug */
  void debugPrint( const char* c );
private:
  /** add term to row */
  void addTermToRow( ArithVar x, Node n, Node& f, NodeBuilder<>& t );
  /** process at effort */
  void process( Node f, int effort );
  /** get delta for node */
  Node getDelta( Node n );

  class Statistics {
  public:
    IntStat d_instantiations;
    IntStat d_instantiations_minus;
    IntStat d_instantiations_match_pure;
    IntStat d_instantiations_match_var;
    IntStat d_instantiations_match_no_var;
    Statistics();
    ~Statistics();
  };
  Statistics d_statistics;
};/* class InstantiatiorTheoryArith  */

}
}
}

#endif