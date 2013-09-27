/*********************                                                        */
/*! \file symmetry_breaking.h
 ** \verbatim
 ** Original author: ajreynol
 ** Major contributors: none
 ** Minor contributors (to current version): none
 ** This file is part of the CVC4 prototype.
 ** Copyright (c) 2009-2012  New York University and The University of Iowa
 ** See the file COPYING in the top-level source directory for licensing
 ** information.\endverbatim
 **
 ** \brief Pre-process step for first-order reasoning
 **/

#include "cvc4_private.h"

#ifndef __CVC4__QUANT_SYMMETRY_BREAKING_H
#define __CVC4__QUANT_SYMMETRY_BREAKING_H

#include "theory/theory.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "expr/node.h"
#include "expr/type_node.h"

#include "util/sort_inference.h"
#include "context/context.h"
#include "context/context_mm.h"
#include "context/cdchunk_list.h"

namespace CVC4 {
namespace theory {

namespace uf {
  class StrongSolverTheoryUF;
}

class SubsortSymmetryBreaker {
  typedef context::CDHashMap<Node, bool, NodeHashFunction> NodeBoolMap;
  typedef context::CDHashMap<Node, int, NodeHashFunction> NodeIntMap;
  typedef context::CDHashMap<Node, Node, NodeHashFunction> NodeNodeMap;
  //typedef context::CDChunkList<int> IntList;
  typedef context::CDList<Node> NodeList;
  typedef context::CDHashMap<Node, NodeList*, NodeHashFunction> NodeListMap;
private:
  /** quantifiers engine */
  QuantifiersEngine* d_qe;
  eq::EqualityEngine * getEqualityEngine();
  bool areDisequal( Node n1, Node n2 );
  bool areEqual( Node n1, Node n2 );
  Node getRepresentative( Node n );
  uf::StrongSolverTheoryUF * getStrongSolver();
  std::vector< Node > d_unit_lemmas;
  Node d_true;
  context::CDO< bool > d_conflict;
public:
  SubsortSymmetryBreaker( QuantifiersEngine* qe, context::Context* c );
  ~SubsortSymmetryBreaker(){}

private:
  class TypeInfo {
  private:
    SubsortSymmetryBreaker * d_ssb;
    //bool isActive( Node n, unsigned & deq );
  public:
    TypeInfo( SubsortSymmetryBreaker * ssb, context::Context* c );
    //list of all nodes from this (sub)type
    std::vector< Node > d_nodes;
    //the current domain constants for this (sub)type
    NodeList d_dom_constants;
    //# nodes in d_nodes that have been domain constants, size of this distinct # of domain constants seen
    unsigned d_dc_nodes;
    //the node we are currently watching to become a domain constant
    context::CDO< int > d_first_active;
    //node to id
    std::map< Node, unsigned > d_node_to_id;
    Node getBaseConstant() { return d_nodes.empty() ? Node::null() : d_nodes[0]; }
    bool hasDomainConstant( Node n );
    unsigned getNumDomainConstants();
    Node getDomainConstant( int i );
    Node getFirstActive();
  };
  std::map< TypeNode, std::vector< int > > d_sub_sorts;
  std::map< int, TypeNode > d_sid_to_type;
  std::map< int, TypeInfo * > d_type_info;

  //maximum domain constants sort
  context::CDO< int > d_max_dom_const_sort;
  context::CDO< bool > d_has_dom_const_sort;

  TypeInfo * getTypeInfo( TypeNode tn, int sid );

  void processFirstActive( TypeNode tn, int sid, int curr_card );
private:
  //void printDebugNodeInfo( const char * c, Node n );
  void printDebugTypeInfo( const char * c, TypeNode tn, int sid );
  /** new node */
  void newEqClass( Node n );
  /** merge */
  void merge( Node a, Node b );
  /** assert disequal */
  void assertDisequal( Node a, Node b );
  /** fact list */
  context::CDO< unsigned > d_fact_index;
  NodeList d_fact_list;
  std::vector< Node > d_pending_lemmas;
  std::vector< Node > d_lemmas;
public:
  /** queue fact */
  void queueFact( Node n );
  /** check */
  bool check( Theory::Effort level );
};

}
}

#endif
