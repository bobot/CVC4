/*********************                                                        */
/*! \file theory_arith_type_rules.h
 ** \verbatim
 ** Original author: dejan
 ** Major contributors: taking, cconway, mdeters
 ** Minor contributors (to current version): none
 ** This file is part of the CVC4 prototype.
 ** Copyright (c) 2009-2012  New York University and The University of Iowa
 ** See the file COPYING in the top-level source directory for licensing
 ** information.\endverbatim
 **
 ** \brief [[ Add brief comments here ]]
 **
 ** [[ Add file-specific comments here ]]
 **/

#include "cvc4_private.h"

#ifndef __CVC4__THEORY__ARITH__THEORY_ARITH_TYPE_RULES_H
#define __CVC4__THEORY__ARITH__THEORY_ARITH_TYPE_RULES_H

#include "util/subrange_bound.h"

namespace CVC4 {
namespace theory {
namespace arith {


class ArithConstantTypeRule {
public:
  inline static TypeNode computeType(NodeManager* nodeManager, TNode n, bool check)
      throw (TypeCheckingExceptionPrivate, AssertionException) {
    Assert(n.getKind() == kind::CONST_RATIONAL);
    if(n.getConst<Rational>().isIntegral()){
      return nodeManager->integerType();
    }else{
      return nodeManager->realType();
    }
  }
};/* class ArithConstantTypeRule */

class ArithOperatorTypeRule {
public:
  inline static TypeNode computeType(NodeManager* nodeManager, TNode n, bool check)
      throw (TypeCheckingExceptionPrivate, AssertionException) {
    TypeNode integerType = nodeManager->integerType();
    TypeNode realType = nodeManager->realType();
    TNode::iterator child_it = n.begin();
    TNode::iterator child_it_end = n.end();
    bool isInteger = true;
    for(; child_it != child_it_end; ++child_it) {
      TypeNode childType = (*child_it).getType(check);
      if (!childType.isInteger()) {
        isInteger = false;
        if( !check ) { // if we're not checking, nothing left to do
          break;
        }
      }
      if( check ) {
        if(!childType.isReal()) {
          throw TypeCheckingExceptionPrivate(n, "expecting an arithmetic subterm");
        }
      }
    }
    Kind k = n.getKind();
    bool isDivision = k == kind::DIVISION || k == kind::DIVISION_TOTAL;
    return (isInteger && !isDivision ? integerType : realType);
  }
};/* class ArithOperatorTypeRule */

class ArithPredicateTypeRule {
public:
  inline static TypeNode computeType(NodeManager* nodeManager, TNode n, bool check)
      throw (TypeCheckingExceptionPrivate, AssertionException) {
    if( check ) {
      TypeNode lhsType = n[0].getType(check);
      if (!lhsType.isReal()) {
        Message() << lhsType << " : " << n[0] << std::endl;
        throw TypeCheckingExceptionPrivate(n, "expecting an arithmetic term on the left-hand-side");
      }
      TypeNode rhsType = n[1].getType(check);
      if (!rhsType.isReal()) {
        throw TypeCheckingExceptionPrivate(n, "expecting an arithmetic term on the right-hand-side");
      }
    }
    return nodeManager->booleanType();
  }
};/* class ArithPredicateTypeRule */

class SubrangeProperties {
public:
  inline static Cardinality computeCardinality(TypeNode type) {
    Assert(type.getKind() == kind::SUBRANGE_TYPE);

    const SubrangeBounds& bounds = type.getConst<SubrangeBounds>();
    if(!bounds.lower.hasBound() || !bounds.upper.hasBound()) {
      return Cardinality::INTEGERS;
    }
    return Cardinality(bounds.upper.getBound() - bounds.lower.getBound());
  }

  inline static Node mkGroundTerm(TypeNode type) {
    Assert(type.getKind() == kind::SUBRANGE_TYPE);

    const SubrangeBounds& bounds = type.getConst<SubrangeBounds>();
    if(bounds.lower.hasBound()) {
      return NodeManager::currentNM()->mkConst(Rational(bounds.lower.getBound()));
    }
    if(bounds.upper.hasBound()) {
      return NodeManager::currentNM()->mkConst(Rational(bounds.upper.getBound()));
    }
    return NodeManager::currentNM()->mkConst(Rational(0));
  }
};/* class SubrangeProperties */

}/* CVC4::theory::arith namespace */
}/* CVC4::theory namespace */
}/* CVC4 namespace */

#endif /* __CVC4__THEORY__ARITH__THEORY_ARITH_TYPE_RULES_H */
