@echo off
for %%a in ("*.cpp") do clang-format "%%a" -i --style="{ BasedOnStyle: LLVM, UseTab: Always, IndentWidth: 4, TabWidth: 4, BreakBeforeBraces: Attach, AllowShortIfStatementsOnASingleLine: true, IndentCaseLabels: true, ColumnLimit: 0 }"
pause