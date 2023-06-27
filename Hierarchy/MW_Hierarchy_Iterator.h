#pragma once

#include "TerritorialWhole.h"
#include <libds/amt/implicit_sequence.h>
#include <libds/amt/explicit_hierarchy.h>

constexpr int MIN_LEVEL_ = 0;
constexpr int MAX_LEVEL_ = 3;

using TW = TerritorialWhole;
using MWEH_TW = ds::amt::MultiWayExplicitHierarchy<TW*>;
using Block = ds::amt::MultiWayExplicitHierarchyBlock<TW*>;
class MW_Hierarchy_Iterator
{
public:
    MW_Hierarchy_Iterator(Block& root_Block);
    ~MW_Hierarchy_Iterator() {};

    void goUP();
    void goDOWN(int&& index);
    void setPointer(Block* node, size_t l)
    {
        this->level_ = l;
        pointerBlock_ = node;
    }

    Block& getReferenceBlock() { return *pointerBlock_; }
    Block* getPointerBlock_() { return pointerBlock_; }
    size_t getLevel() { return level_; }

private:
    Block* pointerBlock_;
    size_t level_;
};


