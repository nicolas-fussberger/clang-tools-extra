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
  // FIXME: Add callback implementation.
  const auto *Var = Result.Nodes.getNodeAs<VarDecl>("x");
//  const auto *FuncDecl = Result.Nodes.getNodeAs<FunctionDecl>("func");


//  auto AllDeclRefExprs = utils::decl_ref_expr::allDeclRefExprs(
//        *Var, *FuncDecl, *Result.Context);
//  auto it = AllDeclRefExprs.begin();
//  while (it != AllDeclRefExprs.end()) {
////    diag(declPtr->getBeginLoc(), "var ref at %0")
////        << declPtr->getDecl();
//    ++it;
//  }
//

  // Check if variable is reassigned within its scope

  // Check if variable is used as a non-const parameter in a function call

//  diag(FuncDecl->getLocation(), "func %0 contains non-const vars")
//      << FuncDecl;
  SourceRange range(Var->getSourceRange());
  diag(range.getBegin(), "Var should be const")
      << Var
      << FixItHint::CreateInsertion(Var->getBeginLoc(), "const");
}

} // namespace misc
} // namespace tidy
} // namespace clang
