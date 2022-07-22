#ifndef FTG_GENERATION_UTMODIFY_H
#define FTG_GENERATION_UTMODIFY_H

#include "ftg/generation/Fuzzer.h"
#include "ftg/sourceanalysis/SourceAnalysisReport.h"
#include "clang/Tooling/Core/Replacement.h"

namespace ftg {

class UTModify {
public:
  const static std::string HeaderName;
  const static std::string UTEntryFuncName;
  UTModify(const Fuzzer &F, const SourceAnalysisReport &SourceReport);
  const std::map<std::string, std::string> &getNewFiles() const;
  const std::map<std::string, clang::tooling::Replacements> &
  getReplacements() const;

private:
  struct GlobalVarSetter {
    std::string FuncName;
    std::string FuncBody;
  };
  const static std::string CPPMacroEnd;
  const static std::string CPPMacroStart;
  const static std::string FilePathPrefix;
  std::map<std::string, std::string> FileNewMap;
  std::map<std::string, clang::tooling::Replacements> FileReplaceMap;
  std::map<std::pair<std::string, unsigned>, clang::tooling::Replacement>
      Replaces;

  bool addReplace(const clang::tooling::Replacement &Replace);
  void clear();
  std::string generateAssignStatement(const FuzzInput &Input) const;
  void generateBottom(
      const std::map<std::string, std::vector<std::string>> &FuzzVarFlagDecls,
      const std::map<std::string, std::vector<GlobalVarSetter>> &Setters,
      const Unittest &UT, const SourceAnalysisReport &SourceReport);
  std::string generateDeclTypeName(const Type &T) const;
  void generateFuzzVarDeclarations(
      std::map<std::string, std::string> &FuzzVarDecls,
      std::map<std::string, std::vector<std::string>> &FuzzVarFlagDecls,
      const FuzzInput &Input) const;
  void generateFuzzVarGlobalSetters(
      std::map<std::string, std::vector<GlobalVarSetter>> &Setters,
      const FuzzInput &Input) const;
  void generateFuzzVarReplacements(const FuzzInput &Input);
  bool generateHeader(const std::string &BasePath);
  std::string
  generateHeaderInclusion(const std::string Path, const std::string &UTPath,
                          const SourceAnalysisReport &SourceReport) const;
  std::string generateIdentifier(const Definition &Def) const;
  void generateMainDeletion(const SourceAnalysisReport &SourceReport);
  void generateTop(
      const std::map<std::string, std::string> &FuzzVarDecls,
      const std::map<std::string, std::vector<std::string>> &FuzzVarFlagDecls,
      const std::map<std::string, std::vector<GlobalVarSetter>> &Setters,
      const std::string &UTPath, const SourceAnalysisReport &SourceReport);
};

} // namespace ftg

#endif // FTG_GENERATION_UTMODIFY_H
