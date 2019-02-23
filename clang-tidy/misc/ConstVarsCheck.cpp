//===--- ConstVarsCheck.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ConstVarsCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "../utils/DeclRefExprUtils.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void ConstVarsCheck::registerMatchers(MatchFinder *Finder) {
  const std::string varName = "x";
  const auto refersToVar =
      ignoringParenImpCasts(declRefExpr(to(varDecl(equalsBoundNode(varName)))));
  Finder->addMatcher(
      functionDecl(hasDescendant(
          varDecl(hasType(qualType(unless(isConstQualified())))).bind(varName)),
          unless(hasDescendant(
              binaryOperator(hasOperatorName("="), hasLHS(refersToVar))))),
      this);
}

void ConstVarsCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Var = Result.Nodes.getNodeAs<VarDecl>("x");

// Hot to get all references for a variabel:
//  auto AllDeclRefExprs = utils::decl_ref_expr::allDeclRefExprs(
//        *Var, *FuncDecl, *Result.Context);
//  auto it = AllDeclRefExprs.begin();
//  while (it != AllDeclRefExprs.end()) {
////    diag(declPtr->getBeginLoc(), "var ref at %0")
////        << declPtr->getDecl();
//    ++it;
//  }
//

  SourceRange range(Var->getSourceRange());
  diag(range.getBegin(), "Var should be const")
      << Var
      << FixItHint::CreateInsertion(Var->getBeginLoc(), "const ");
}

} // namespace misc
} // namespace tidy
} // namespace clang
