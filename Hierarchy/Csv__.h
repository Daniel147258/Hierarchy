#pragma once


#include <functional>
#include <fstream>
#include <sstream>

#include "TerritorialWhole.h"

#include <libds/amt/implicit_sequence.h> 
#include "libds/heap_monitor.h"

using TW = TerritorialWhole;
class CSV__
{
public:
    CSV__() {};
    ~CSV__() {};

    void readFileTo_IS(const std::string& file, ds::amt::ImplicitSequence<TW*>& IS_, TW_TYPE type);

private:
    void createTWInstance(TW_TYPE type, TW*& tw);
    void setTWProperties(int column_count, TW* tw, std::string& word);
};
