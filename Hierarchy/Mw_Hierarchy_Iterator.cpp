#include "MW_Hierarchy_Iterator.h"

MW_Hierarchy_Iterator::MW_Hierarchy_Iterator(Block& root_Block)
{
    pointerBlock_ = nullptr;
    pointerBlock_ = &root_Block;
    level_ = 0;
}

void MW_Hierarchy_Iterator::goUP()
{
    if (level_ > MIN_LEVEL_ && level_ <= MAX_LEVEL_)
    {
        pointerBlock_ = reinterpret_cast<Block*>(pointerBlock_->parent_);
        --level_;
    }
    else
    {
        std::cout << "Nachadzate sa na MINIMALNOM levli nemozete ist vyssie. LEVEL: Slovakia" << std::endl;
    }
}

void MW_Hierarchy_Iterator::goDOWN(int&& index)
{
    if (level_ >= MIN_LEVEL_ && level_ < MAX_LEVEL_)
    {
        pointerBlock_ = pointerBlock_->sons_->access(index)->data_;
        ++level_;
    }
    else
    {
        std::cout << "Nachadzate sa na MAXIMALNOM levli nemozete ist nizsie. LEVEL: Obec" << std::endl;
    }
}
