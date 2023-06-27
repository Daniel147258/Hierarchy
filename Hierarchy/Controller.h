#pragma once

#include "State.h"
#include "Slave.h"
#include <libds/amt/explicit_hierarchy.h>
#include "libds/heap_monitor.h"


using Block = ds::amt::MultiWayExplicitHierarchyBlock<TW*>;
class Controller
{
public:
    Controller() {};
    ~Controller() {};

    bool predikates(Block* current_Block, ds::amt::MultiWayExplicitHierarchy<TW*>* hierachii, const std::string& str, TW_TYPE type, ds::amt::ImplicitSequence<Block*>& pom_IS,
        std::function<bool(Block*)> predikat);
    bool startWith_(Block* current_Block, ds::amt::MultiWayExplicitHierarchy<TW*>* hierachii, const std::string& str, ds::amt::ImplicitSequence<Block*>& pom_IS);
    bool containWith_(Block* current_Block, ds::amt::MultiWayExplicitHierarchy<TW*>* hierachii, const std::string& str, ds::amt::ImplicitSequence<Block*>& pom_IS);
    bool containTW_TYPE_(Block* current_Block, ds::amt::MultiWayExplicitHierarchy<TW*>* hierachii, TW_TYPE type, ds::amt::ImplicitSequence<Block*>& pom_IS);

private:
    void outPut(ds::amt::ImplicitSequence<Block*>& pom_IS);
};
