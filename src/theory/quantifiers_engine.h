/*********************                                                        */
/*! \file quantifiers_engine.h
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
 ** \brief Theory instantiator, Instantiation Engine classes
 **/

#include "cvc4_private.h"

#ifndef __CVC4__QUANTIFIERS_ENGINE_H
#define __CVC4__QUANTIFIERS_ENGINE_H

#include "theory/theory.h"
#include "util/hash.h"
#include "theory/trigger.h"

#include "util/stats.h"

#include <ext/hash_set>
#include <iostream>
#include <map>

namespace CVC4 {

class TheoryEngine;
class SmtEngine;

// attribute for "contains instantiation constants from"
struct InstConstantAttributeId {};
typedef expr::Attribute<InstConstantAttributeId, Node> InstConstantAttribute;

struct InstLevelAttributeId {};
typedef expr::Attribute<InstLevelAttributeId, uint64_t> InstLevelAttribute;

struct InstVarNumAttributeId {};
typedef expr::Attribute<InstVarNumAttributeId, uint64_t> InstVarNumAttribute;

struct BoundVarAttributeId {};
typedef expr::Attribute<BoundVarAttributeId, bool> BoundVarAttribute;


namespace theory {

class InstStrategyList;
class QuantifiersEngine;

class InstStrategy
{
public:
  enum Status {
    STATUS_UNFINISHED,
    STATUS_UNKNOWN,
    STATUS_SAT,
  };/* enum Effort */
protected:
  /** reference to the instantiation engine */
  QuantifiersEngine* d_quantEngine;
protected:
  /** giving priorities */
  std::vector< InstStrategy* > d_priority_over;
  /** do not instantiate list */
  std::vector< Node > d_no_instantiate;
  std::vector< Node > d_no_instantiate_temp;
  /** reset instantiation */
  virtual void processResetInstantiationRound( Theory::Effort effort ) = 0;
  /** process method */
  virtual int process( Node f, Theory::Effort effort, int e, int limitInst = 0 ) = 0;
public:
  InstStrategy( QuantifiersEngine* ie ) : d_quantEngine( ie ){}
  virtual ~InstStrategy(){}

  /** reset instantiation */
  void resetInstantiationRound( Theory::Effort effort );
  /** do instantiation round method */
  int doInstantiation( Node f, Theory::Effort effort, int e, int limitInst = 0 );
  /** update status */
  static void updateStatus( int& currStatus, int addStatus ){
    if( addStatus==STATUS_UNFINISHED ){
      currStatus = STATUS_UNFINISHED;
    }else if( addStatus==STATUS_UNKNOWN ){
      if( currStatus==STATUS_SAT ){
        currStatus = STATUS_UNKNOWN;
      }
    }
  }
  /** identify */
  virtual std::string identify() const { return std::string("Unknown"); }
public:
  /** set priority */
  void setPriorityOver( InstStrategy* is ) { d_priority_over.push_back( is ); }
  /** set no instantiate */
  void setNoInstantiate( Node n ) { d_no_instantiate.push_back( n ); }
  /** should instantiate */
  bool shouldInstantiate( Node n ) { 
    return std::find( d_no_instantiate_temp.begin(), d_no_instantiate_temp.end(), n )==d_no_instantiate_temp.end(); 
  }
};

class Instantiator{
  friend class QuantifiersEngine;
protected:
  /** reference to the instantiation engine */
  QuantifiersEngine* d_quantEngine;
  /** reference to the theory that it looks at */
  Theory* d_th;
  /** instantiation strategies */
  std::vector< InstStrategy* > d_instStrategies;
  /** instantiation strategies active */
  std::map< InstStrategy*, bool > d_instStrategyActive;
  /** has constraints from quantifier */
  std::map< Node, bool > d_hasConstraints;
  /** is instantiation strategy active */
  bool isActiveStrategy( InstStrategy* is ) { 
    return d_instStrategyActive.find( is )!=d_instStrategyActive.end() && d_instStrategyActive[is];
  }
  /** add inst strategy */
  void addInstStrategy( InstStrategy* is ){
    d_instStrategies.push_back( is );
    d_instStrategyActive[is] = true;
  }
  /** reset instantiation round */
  virtual void processResetInstantiationRound( Theory::Effort effort ) = 0;
  /** process quantifier */
  virtual int process( Node f, Theory::Effort effort, int e, int limitInst = 0 ) = 0;
public:
  /** set has constraints from quantifier f */
  void setHasConstraintsFrom( Node f );
  /** has constraints from */
  bool hasConstraintsFrom( Node f );
  /** is full owner of quantifier f? */
  bool isOwnerOf( Node f );
public:
  Instantiator(context::Context* c, QuantifiersEngine* qe, Theory* th);
  ~Instantiator();

  /** get corresponding theory for this instantiator */
  Theory* getTheory() { return d_th; }
  /** Pre-register a term.  Done one time for a Node, ever. */
  virtual void preRegisterTerm( Node t ) { }
  /** assertNode function, assertion was asserted to theory */
  virtual void assertNode( Node assertion ){}
  /** reset instantiation round */
  void resetInstantiationRound( Theory::Effort effort );
  /** do instantiation method*/
  int doInstantiation( Node f, Theory::Effort effort, int e, int limitInst = 0 );
  /** identify */
  virtual std::string identify() const { return std::string("Unknown"); }
  /** print debug information */
  virtual void debugPrint( const char* c ) {}
  /** get status */
  //int getStatus() { return d_status; }
};/* class Instantiator */

class QuantifiersModule
{
public:
  QuantifiersModule(){}
  ~QuantifiersModule(){}
  /* Call during check registerQuantifier has already been called */
  virtual void check( Theory::Effort e ) = 0;
  /* Called for new quantifiers */
  virtual void registerQuantifier( Node n ) = 0;
  virtual void assertNode( Node n ) = 0;
  virtual Node explain(TNode n) = 0;
};

class TermDb
{
public:
  TermDb(){}
  ~TermDb(){}
  /** map from APPLY_UF operators to ground terms for that operator */
  std::map< Node, std::vector< Node > > d_op_map;
  /** map from type nodes to terms of that type */
  std::map< TypeNode, std::vector< Node > > d_type_map;
  /** add a term to the database */
  virtual void add( Node n, std::vector< Node >& added, bool withinQuant = false ) = 0;
};


namespace quantifiers{
  class InstantiationEngine;
}

class QuantifiersEngine
{
  friend class quantifiers::InstantiationEngine;
  friend class InstMatch;
private:
  typedef context::CDHashMap< Node, bool, NodeHashFunction > BoolMap;
  /** reference to theory engine object */
  TheoryEngine* d_te;
  /** vector of modules for quantifiers */
  std::vector< QuantifiersModule* > d_modules;
  /** equality query class */
  EqualityQuery* d_eq_query;

  /** list of all quantifiers */
  std::vector< Node > d_quants;
  /** map from universal quantifiers to the list of variables */
  std::map< Node, std::vector< Node > > d_vars;
  /** map from universal quantifiers to the list of skolem constants */
  std::map< Node, std::vector< Node > > d_skolem_constants;
  /** map from universal quantifiers to their skolemized body */
  std::map< Node, Node > d_skolem_body;
  /** map from universal quantifiers to their bound body */
  std::map< Node, Node > d_bound_body;
  /** instantiation constants to universal quantifiers */
  std::map< Node, Node > d_inst_constants_map;
  /** map from universal quantifiers to the list of instantiation constants */
  std::map< Node, std::vector< Node > > d_inst_constants;
  /** map from universal quantifiers to their counterexample body */
  std::map< Node, Node > d_counterexample_body;
  /** map from universal quantifiers to their counterexample literals */
  std::map< Node, Node > d_ce_lit;
  /** map from quantifiers to whether they are active */
  BoolMap d_active;
  /** lemmas produced */
  std::map< Node, bool > d_lemmas_produced;
  /** lemmas waiting */
  std::vector< Node > d_lemmas_waiting;
  /** inst matches produced for each quantifier */
  std::map< Node, InstMatchTrie > d_inst_match_trie;
  /** phase requirements for each quantifier for each instantiation literal */
  std::map< Node, std::map< Node, bool > > d_phase_reqs;
  std::map< Node, std::map< Node, Node > > d_phase_reqs_equality;
  std::map< Node, std::map< Node, Node > > d_phase_reqs_disequality;
  /** free variable for instantiation constant type */
  std::map< TypeNode, Node > d_free_vars;
  /** bound variable for variable types */
  std::map< TypeNode, Node > d_bound_vars;
  /** owner of quantifiers */
  std::map< Node, Theory* > d_owner;
  /** term database */
  TermDb* d_term_db;
private:
  /** for computing relavance */
  /** map from quantifiers to symbols they contain */
  std::map< Node, std::vector< Node > > d_syms;
  /** map from symbols to quantifiers */
  std::map< Node, std::vector< Node > > d_syms_quants;
  /** relevance for quantifiers and symbols */
  std::map< Node, int > d_relevance;
  /** compute symbols */
  void computeSymbols( Node n, std::vector< Node >& syms );
private:
  /** helper functions compute phase requirements */
  static void computePhaseReqs2( Node n, bool polarity, std::map< Node, int >& phaseReqs );
  /** set instantiation level attr */
  void setInstantiationLevelAttr( Node n, uint64_t level );
  /** set instantiation constant attr */
  void setInstantiationConstantAttr( Node n, Node f );
  /** make instantiation constants for */
  void makeInstantiationConstantsFor( Node f );
public:
  QuantifiersEngine(context::Context* c, TheoryEngine* te);
  ~QuantifiersEngine();
  /** get instantiator for id */
  Instantiator* getInstantiator( int id );
  /** get theory engine */
  TheoryEngine* getTheoryEngine() { return d_te; }
  /** get equality query object */
  EqualityQuery* getEqualityQuery() { return d_eq_query; }
  /** set equality query object */
  void setEqualityQuery( EqualityQuery* eq ) { d_eq_query = eq; }
public:
  /** add module */
  void addModule( QuantifiersModule* qm ) { d_modules.push_back( qm ); }
  /** check at level */
  void check( Theory::Effort e );
  /** register quantifier */
  void registerQuantifier( Node f );
  /** register quantifier */
  void registerPattern( std::vector<Node> & pattern);
  /** assert (universal) quantifier */
  void assertNode( Node f );
public:
  /** add lemma lem */
  bool addLemma( Node lem );
  /** instantiate f with arguments terms */
  bool addInstantiation( Node f, std::vector< Node >& terms );
  /** do instantiation specified by m */
  bool addInstantiation( Node f, InstMatch& m, bool addSplits = false );
  /** split on node n */
  bool addSplit( Node n, bool reqPhase = false, bool reqPhasePol = true );
  /** add split equality */
  bool addSplitEquality( Node n1, Node n2, bool reqPhase = false, bool reqPhasePol = true );
  /** has added lemma */
  bool hasAddedLemma() { return !d_lemmas_waiting.empty(); }
  /** flush lemmas */
  void flushLemmas( OutputChannel* out );
  /** get number of waiting lemmas */
  int getNumLemmasWaiting() { return (int)d_lemmas_waiting.size(); }
public:
  /** get number of quantifiers */
  int getNumQuantifiers() { return (int)d_quants.size(); }
  /** get quantifier */
  Node getQuantifier( int i ) { return d_quants[i]; }
  /** get instantiation constants */
  void getInstantiationConstantsFor( Node f, std::vector< Node >& ics ) { 
    ics.insert( ics.begin(), d_inst_constants[f].begin(), d_inst_constants[f].end() ); 
  }
  /** get the i^th instantiation constant of f */
  Node getInstantiationConstant( Node f, int i ) { return d_inst_constants[f][i]; }
  /** get number of instantiation constants for f */
  int getNumInstantiationConstants( Node f ) { return (int)d_inst_constants[f].size(); }
  std::vector<Node> createInstVariable( std::vector<Node> & vars );
public:
  /** get the ce body f[e/x] */
  Node getCounterexampleBody( Node f ) { return d_counterexample_body[ f ]; }
  /** get or create the ce body f[e/x] */
  Node getOrCreateCounterexampleBody( Node f );
  /** get the corresponding counterexample literal for quantified formula node n */
  Node getCounterexampleLiteralFor( Node f ) { return d_ce_lit.find( f )==d_ce_lit.end() ? Node::null() : d_ce_lit[ f ]; }
  /** get the skolemized body f[e/x] */
  Node getSkolemizedBody( Node f );
  /** get the bound body */
  Node getBoundBody( Node f );
  /** set active */
  void setActive( Node n, bool val ) { d_active[n] = val; }
  /** get active */
  bool getActive( Node n ) { return d_active.find( n )!=d_active.end() && d_active[n]; }
  /** is phase required */
  bool isPhaseReq( Node f, Node lit ) { return d_phase_reqs[f].find( lit )!=d_phase_reqs[f].end(); }
  /** get phase requirement */
  bool getPhaseReq( Node f, Node lit ) { return d_phase_reqs[f].find( lit )==d_phase_reqs[f].end() ? false : d_phase_reqs[f][ lit ]; }
  /** get term req terms */
  void getPhaseReqTerms( Node f, std::vector< Node >& nodes );
  /** helper functions compute phase requirements */
  static void computePhaseReqs( Node n, bool polarity, std::map< Node, bool >& phaseReqs );
  /** compute phase requirements */
  void generatePhaseReqs( Node f );
public:
  /** returns node n with bound vars of f replaced by instantiation constants of f
      node n : is the futur pattern
      node f : is the quantifier containing which bind the variable
      return a pattern where the variable are replaced by variable for
      instantiation.
   */
  Node getSubstitutedNode( Node n, Node f );
  /** same as before but node f is just linked to the new pattern by the
      applied attribute
      vars the bind variable
      nvars the same variable but with an attribute
  */
  Node convertNodeToPattern( Node n, Node f,
                             const std::vector<Node> & vars,
                             const std::vector<Node> & nvars);
  /** get free variable for instantiation constant */
  Node getFreeVariableForInstConstant( Node n );
  /** get bound variable for variable */
  Node getBoundVariableForVariable( Node n );
public:
  /** has owner */
  bool hasOwner( Node f ) { return d_owner.find( f )!=d_owner.end(); }
  /** get owner */
  Theory* getOwner( Node f ) { return d_owner[f]; }
  /** set owner */
  void setOwner( Node f, Theory* t ) { d_owner[f] = t; }
public:
  /** set term database */
  void setTermDatabase( TermDb* tdb ) { d_term_db = tdb; }
  /** get term database */
  TermDb* getTermDatabase() { return d_term_db; }
  /** add term to database */
  void addTermToDatabase( Node n, bool withinQuant = false );
private:
  /** set relevance */
  void setRelevance( Node s, int r );
public:
  /** get relevance */
  int getRelevance( Node s ) { return d_relevance.find( s )==d_relevance.end() ? -1 : d_relevance[s]; }
  /** get number of quantifiers for symbol s */
  int getNumQuantifiersForSymbol( Node s ) { return (int)d_syms_quants[s].size(); }
public:
  /** statistics class */
  class Statistics {
  public:
    IntStat d_num_quant;
    IntStat d_instantiation_rounds;
    IntStat d_instantiation_rounds_lc;
    IntStat d_instantiations;
    IntStat d_max_instantiation_level;
    IntStat d_splits;
    IntStat d_total_inst_var;
    IntStat d_total_inst_var_unspec;
    IntStat d_inst_unspec;
    IntStat d_inst_duplicate;
    IntStat d_lit_phase_req;
    IntStat d_lit_phase_nreq;
    IntStat d_triggers;
    IntStat d_multi_triggers;
    IntStat d_multi_trigger_instantiations;
    Statistics();
    ~Statistics();
  };
  Statistics d_statistics;
};/* class QuantifiersEngine */

}/* CVC4::theory namespace */
}/* CVC4 namespace */

#endif /* __CVC4__INSTANTIATION_ENGINE_H */