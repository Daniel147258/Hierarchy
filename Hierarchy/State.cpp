#include "State.h"

State::State(const std::string& fileRegion, const std::string& fileDistrict, const std::string& fileMunicipality)
{
    this->hierarchy_ = new TW_Hierarchy();
    IS_Region = new ds::amt::ImplicitSequence<TW*>;
    IS_District = new ds::amt::ImplicitSequence<TW*>;
    IS_Municipality = new ds::amt::ImplicitSequence<TW*>;


    csv.readFileTo_IS(fileRegion, *IS_Region, TW_TYPE::Region);
    csv.readFileTo_IS(fileDistrict, *IS_District, TW_TYPE::District);
    csv.readFileTo_IS(fileMunicipality, *IS_Municipality, TW_TYPE::Municipality);

    this->hierarchy_->fillHierarchy(*IS_Region, *IS_District, *IS_Municipality);
}

State::~State()
{
    if (IS_Region->size() > 0)
    {
        this->DeepClean(*IS_Region);
    }
    if (IS_District->size() > 0)
    {
        this->DeepClean(*IS_District);
    }
    if (IS_Municipality->size() > 0)
    {
        this->DeepClean(*IS_Municipality);
    }
    this->ShallowClean();
}

void State::DeepClean(ds::amt::ImplicitSequence<TW*>& IS)
{
    for (size_t i = 0; i < IS.size(); i++)
    {
        if (IS[i] != nullptr)
        {
            delete IS[i];
            IS[i] = nullptr;
        }
    }
}

void State::ShallowClean()
{
    delete IS_Region;
    delete IS_District;
    delete IS_Municipality;
    delete hierarchy_;
    IS_Region = nullptr;
    IS_District = nullptr;
    IS_Municipality = nullptr;
    hierarchy_ = nullptr;
}
