#pragma once

#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "llvm/ADT/STLExtras.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"

#include "codegen.h"
#include "error.h"
#include "jit.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"

struct DebugInfo {
  llvm::DICompileUnit* TheCU;
  llvm::DIType* DblTy;
  std::vector<llvm::DIScope*> LexicalBlocks;

  void emitLocation(ExprAST* AST);
  llvm::DIType* getDoubleTy();
};

extern DebugInfo KSDbgInfo;

extern std::unique_ptr<llvm::LLVMContext> TheContext;
extern std::unique_ptr<llvm::Module> TheModule;
extern std::unique_ptr<llvm::IRBuilder<>> Builder;
extern llvm::ExitOnError ExitOnErr;

extern std::map<std::string, llvm::AllocaInst*> NamedValues;
extern std::unique_ptr<llvm::orc::ArxJIT> TheJIT;
extern std::map<std::string, std::unique_ptr<PrototypeAST>> FunctionProtos;

extern std::unique_ptr<llvm::DIBuilder> DBuilder;

auto show_llvm() -> void;
auto open_shell() -> void;
auto compile() -> void;
auto compile_to_file() -> void;
