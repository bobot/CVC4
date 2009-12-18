/*********************                                           -*- C++ -*-  */
/** smt_parser_black.h
 ** Original author: cconway
 ** Major contributors: none
 ** Minor contributors (to current version): none
 ** This file is part of the CVC4 prototype.
 ** Copyright (c) 2009 The Analysis of Computer Systems Group (ACSys)
 ** Courant Institute of Mathematical Sciences
 ** New York University
 ** See the file COPYING in the top-level source directory for licensing
 ** information.
 **
 ** Black box testing of CVC4::parser::SmtParser.
 **/

#include <cxxtest/TestSuite.h>
//#include <string>
#include <sstream>

#include "expr/expr.h"
#include "expr/expr_manager.h"
#include "parser/parser.h"

using namespace CVC4;
using namespace CVC4::parser;
using namespace std;

const string goodInputs[] = {
    "", // empty string is OK
    "(benchmark foo :assume true)",
    "(benchmark bar :formula true)",
    "(benchmark qux :formula false)",
    "(benchmark baz :extrapreds ( (a) (b) ) )",
    "(benchmark zab :extrapreds ( (a) (b) ) :formula (implies (and (implies a b) a) b))",
    ";; nothing but a comment",
    "; a comment\n)(benchmark foo ; hello\n  :formula true; goodbye\n)"
  };

/* The following expressions are good in a context where a, b, and c have been declared as BOOLEAN. */
const string goodBooleanExprs[] = {
    "(and a b)",
    "(or (and a b) c)",
    "(implies (and (implies a b) a) b))",
    "(and (iff a b) (not a))",
    "(iff (xor a b) (and (or a b) (not (and a b))))"
};

const string badInputs[] = {
    "(benchmark foo)", // empty benchmark is not OK
    "(benchmark bar :assume)", // no args
    "(benchmark bar :formula)",
  };

/* The following expressions are bad even in a context where a, b, and c have been declared as BOOLEAN. */
const string badBooleanExprs[] = {
    "",
    "(and a)", // wrong arity
    "(and a b", // no closing paren
    "(a and b)", // infix
    "(OR (AND a b) c)", // wrong case
    "(a IMPLIES b)", // infix AND wrong case
    "(not a b)", // wrong arity
    "not a" // needs parens
};

class SmtParserBlack : public CxxTest::TestSuite {
private:
  ExprManager *d_exprManager;
  Parser::InputLanguage d_lang;
public:
  void setUp() {
    d_exprManager = new ExprManager();
    d_lang = Parser::LANG_SMTLIB;
  }

  void testGoodInputs() {
    //    cout << "In testGoodInputs()\n";
    for(int i = 0; i < sizeof(goodInputs); ++i) {
      istringstream stream(goodInputs[i]);
      Parser* smtParser = Parser::getNewParser(d_exprManager, d_lang, stream);
      TS_ASSERT( !smtParser->done() );
      while(!smtParser->done()) {
        TS_ASSERT( smtParser->parseNextCommand() != NULL );
      }
      delete smtParser;
    }
  }

  void testBadInputs() {
    //    cout << "In testGoodInputs()\n";
    for(int i = 0; i < sizeof(badInputs); ++i) {
      istringstream stream(badInputs[i]);
      Parser* smtParser = Parser::getNewParser(d_exprManager, d_lang, stream);
      TS_ASSERT_THROWS( smtParser->parseNextCommand(), ParserException );
      delete smtParser;
    }
  }

  void testGoodBooleanExprs() {
    //    cout << "In testGoodInputs()\n";
    for(int i = 0; i < sizeof(goodBooleanExprs); ++i) {
      istringstream stream(goodBooleanExprs[i]);
      Parser* smtParser = Parser::getNewParser(d_exprManager, d_lang, stream);
      TS_ASSERT( !smtParser->done() );
      while(!smtParser->done()) {
        TS_ASSERT( !smtParser->parseNextExpression().isNull() );
      }
      delete smtParser;
    }
  }

  void testBadBooleanExprs() {
    //    cout << "In testGoodInputs()\n";
    for(int i = 0; i < sizeof(badBooleanExprs); ++i) {
      istringstream stream(badBooleanExprs[i]);
      SmtParser smtParser(d_exprManager, stream);
      TS_ASSERT_THROWS( smtParser.parseNextExpression(), ParserException );
    }
  }

};
