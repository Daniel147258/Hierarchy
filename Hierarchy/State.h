#pragma once

#include "CSV__.h"
#include "Controller.h"
#include "TW_Hierarchy.h"

#include "libds/heap_monitor.h"

class State
{
public:
    State(const std::string& fileRegion, const std::string& fileDistrict, const std::string& fileMunicipality);
    ~State();

    TW_Hierarchy* getHierarchy() { return hierarchy_; };

private:
    void DeepClean(ds::amt::ImplicitSequence<TW*>& IS);
    void ShallowClean();

protected:
    ds::amt::ImplicitSequence<TW*>* IS_Region;
    ds::amt::ImplicitSequence<TW*>* IS_District;
    ds::amt::ImplicitSequence<TW*>* IS_Municipality;

private:
    CSV__ csv;
    TW_Hierarchy* hierarchy_;
};

