/**
* @file include/bin2llvmir/optimizations/constants/constants.h
* @brief Composite type reconstruction analysis.
* @copyright (c) 2017 Avast Software, licensed under the MIT license
*/

#ifndef BIN2LLVMIR_OPTIMIZATIONS_CONSTANTS_CONSTANTS_H
#define BIN2LLVMIR_OPTIMIZATIONS_CONSTANTS_CONSTANTS_H

#include <set>
#include <unordered_set>
#include <vector>

#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/Pass.h>

#include "tl-cpputils/address.h"
#include "bin2llvmir/analyses/reaching_definitions.h"
#include "bin2llvmir/providers/config.h"
#include "bin2llvmir/providers/debugformat.h"
#include "bin2llvmir/providers/fileimage.h"

namespace bin2llvmir {

class ConstantsAnalysis : public llvm::ModulePass
{
	public:
		static char ID;
		ConstantsAnalysis();
		virtual bool runOnModule(llvm::Module& M) override;
		virtual void getAnalysisUsage(llvm::AnalysisUsage& AU) const override;

	private:
		void checkForGlobalInInstruction(
				ReachingDefinitionsAnalysis& RDA,
				llvm::Instruction* inst,
				llvm::Value* val,
				bool storeValue = false);
		void tagFunctionsWithUsedCryptoGlobals();
		void setPic32GpValue(ReachingDefinitionsAnalysis& RDA);

	private:
		llvm::Module * m_module = nullptr;
		Config* config = nullptr;
		FileImage* objf = nullptr;
		DebugFormat* dbgf = nullptr;
};

} // namespace bin2llvmir

#endif
