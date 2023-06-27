#pragma
#include <libds/amt/explicit_hierarchy.h>
#include <libds/amt/implicit_sequence.h>
#include "TerritorialWhole.h"

#include "libds/heap_monitor.h"

using TW = TerritorialWhole;
using MWEH_TW = ds::amt::MultiWayExplicitHierarchy<TW*>;
using Block = ds::amt::MultiWayExplicitHierarchyBlock<TW*>;
class TW_Hierarchy
{
public:
    TW_Hierarchy();
    ~TW_Hierarchy();

    MWEH_TW* getMWEH() { return ex_hierarchy; }
    void fillHierarchy(ds::amt::ImplicitSequence<TW*>& IS_R, ds::amt::ImplicitSequence<TW*>& IS_D, ds::amt::ImplicitSequence<TW*>& IS_M);
    Block& getState() { return *ex_hierarchy->accessRoot(); }

private:
    void fillWholeHierarhy(ds::amt::ImplicitSequence<TW*>& IS_R, ds::amt::ImplicitSequence<TW*>& IS_D, ds::amt::ImplicitSequence<TW*>& IS_M,
        ds::amt::ImplicitSequence<Block*>* IS_NewParent, TW_TYPE type, Block& parent);
    bool find_SubString_InString(const std::string& s_note, const std::string& s_code, const int&& sizeOfSubstring, const int&& from_);

private:
    MWEH_TW* ex_hierarchy;
};


