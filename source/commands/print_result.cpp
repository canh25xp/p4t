#include "print_result.h"

#include "p4/clientapi.h"

void PrintResult::OutputStat(StrDict *varList) {
    m_Data.push_back(PrintData{});
}

void PrintResult::OutputText(const char *data, int length) {
    std::vector<char> &fileContent = m_Data.back().contents;
    fileContent.insert(fileContent.end(), data, data + length);
}

void PrintResult::OutputBinary(const char *data, int length) {
    OutputText(data, length);
}
