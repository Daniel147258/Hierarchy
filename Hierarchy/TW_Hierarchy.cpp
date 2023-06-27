#include "TW_Hierarchy.h"

TW_Hierarchy::TW_Hierarchy()
{
    ex_hierarchy = new MWEH_TW();
    ex_hierarchy->emplaceRoot().data_ = new TW(0, "", "Slovakia", "", "", "", TW_TYPE::State);
};

TW_Hierarchy::~TW_Hierarchy()
{
    delete ex_hierarchy->accessRoot()->data_;
    delete ex_hierarchy;    // pretoze Multiway ma clear, pouzije post order a vymaze BlokType
};

void TW_Hierarchy::fillHierarchy(ds::amt::ImplicitSequence<TW*>& IS_R, ds::amt::ImplicitSequence<TW*>& IS_D, ds::amt::ImplicitSequence<TW*>& IS_M)
{
    auto& root = *ex_hierarchy->accessRoot();
    fillWholeHierarhy(IS_R, IS_D, IS_M, root.sons_, TW_TYPE::Region, root);
}

void TW_Hierarchy::fillWholeHierarhy(ds::amt::ImplicitSequence<TW*>& IS_R, ds::amt::ImplicitSequence<TW*>& IS_D, ds::amt::ImplicitSequence<TW*>& IS_M,
    ds::amt::ImplicitSequence<Block*>* IS_NewParent, TW_TYPE type, Block& parent)
{
    for (size_t i = 0; i < IS_R.size(); i++)
    {
        if (TW_TYPE::Region == type
            || TW_TYPE::District == type && this->find_SubString_InString(parent.data_->getNote(), IS_D[i]->getCode(), 2, 3)
            || TW_TYPE::Municipality == type && this->find_SubString_InString(parent.data_->getCode(), IS_M[i]->getCode(), 6, 0))
        {
            Block* block_newSon = new Block();
            block_newSon->parent_ = &parent;
            block_newSon->data_ = IS_R.access(i)->data_;
            IS_NewParent->insertLast().data_ = block_newSon;
            switch (type)
            {
            case TW_TYPE::Region:
                fillWholeHierarhy(IS_D, IS_D, IS_M, block_newSon->sons_, TW_TYPE::District, *block_newSon);
                break;
            case TW_TYPE::District:
                fillWholeHierarhy(IS_M, IS_M, IS_M, block_newSon->sons_, TW_TYPE::Municipality, *block_newSon);
                break;
            default:
                break;
            }
        }
    }
}

bool TW_Hierarchy::find_SubString_InString(const std::string& s_note, const std::string& s_code, const int&& sizeOfSubstring, const int&& from_)
{
    if (sizeOfSubstring + from_ <= s_code.size())
    {
        char* buffer = new char[sizeOfSubstring + 1];
        buffer[std::size_t(s_code.copy(buffer, sizeOfSubstring, from_))] = '\0';
        bool pom1 = s_note.find(std::string(buffer)) != std::string::npos ? true : false;
        delete buffer;
        return pom1;
    }
    else
    {
        throw std::logic_error("TW_Hierarchy::find_SubString_InString: sizeOfSubstring + from_ > s_code.size()    !!!");
    }
}