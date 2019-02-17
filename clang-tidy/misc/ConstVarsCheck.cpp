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

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void ConstVarsCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      varDecl(hasType(qualType(unless(isConstQualified())))).bind("x"), this);
}

void ConstVarsCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("x");

  // if variable is already const -> skipped
//  if(MatchedDecl->getType().isConstQualified()) return;

  // Check if variable is reassigned within its scope

  // Check if variable is used as a non-const parameter in a function call


  diag(MatchedDecl->getLocation(), "var %0 is insufficiently awesome")
      << MatchedDecl
      << FixItHint::CreateInsertion(MatchedDecl->getLocation(), "awesome_");
}

} // namespace misc
} // namespace tidy
} // namespace clang
