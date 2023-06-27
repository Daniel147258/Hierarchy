#pragma once

#include "CSV__.h"
#include "Controller.h"
#include "libds/heap_monitor.h"
#include "MW_Hierarchy_Iterator.h"

constexpr int SIZE_OF_SUBSTRING = 6;

constexpr int CODE_GO_UP = 1;
constexpr int CODE_STARTWITH_FIND = 2;
constexpr int CODE_CONTAIN_FIND = 3;
constexpr int CODE_CHOOSE = 4;

using HierarchyIterator = MW_Hierarchy_Iterator;

class Application
{
public:
    Application(const std::string& fileRegion, const std::string& fileDistrict, const std::string& fileMunicipality);
    ~Application();

private:
    void startAplication(std::string& currentPoin_string, HierarchyIterator* h_iterator, Controller& controller, State* state);
    void evaluate_mainOPTION(HierarchyIterator& h_iterator, Controller& controller, int& zvolenaUzemnaJednotka, bool& continue_);
    void evaluateInputOperations(int& zvolenaOperacia, std::string& zadanyNazov, HierarchyIterator& h_iterator, Controller& controller,
        int& zvolenaUzemnaJednotka, bool& continue_);
    void evaluteInput(const int& zvolenaOperacia, std::string& zadanyNazov, HierarchyIterator& h_iterator, Controller& controller,
        int& zvolenaUzemnaJednotka, bool& continue_);

    void printTW(HierarchyIterator& h_iterator, const std::string& Officialtitle);

    void setCurrentBlock(const int& zvolenaUzemnaJednotka, HierarchyIterator& h_iterator, ds::amt::ImplicitSequence<Block*>& IS_findedBlock);
    void setInputPredikate(HierarchyIterator& h_iterator, ds::amt::ImplicitSequence<Block*>& IS_index,
        bool& continue_, int& zvolenaOperacia, std::string& zadanyNazov, Controller& controller, int& zvolenaUzemnaJednotka);
    bool try_stopApplication(bool& continue_, std::string& inputStr, int& zvolenaOperacia, std::string& zadanyNazov, HierarchyIterator& h_iterator,
        Controller& controller, int& zvolenaUzemnaJednotka);

private:
    State* state_;
    Controller controller_;
    HierarchyIterator* h_iterator_;
};

