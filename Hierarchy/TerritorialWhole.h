#pragma once
#include <iostream>

#include "TW_TYPE.h"
#include "libds/heap_monitor.h"

class TerritorialWhole
{
public:
    TerritorialWhole(const int& i, const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4, const std::string& s5, const TW_TYPE& t) :
        sortNumber(i), code(s1), officialTitle(s2), mediumTitle(s3), shortTitle(s4), note(s5), tw_type(t) {};
    virtual ~TerritorialWhole() {};
    virtual const int& getSortNumber() const { return sortNumber; }
    virtual const std::string& getCode() const { return code; }
    virtual const std::string& getOfficialTitle() const { return officialTitle; }
    virtual const std::string& getMediumTitle() const { return mediumTitle; }
    virtual const std::string& getShortTitle() const { return shortTitle; }
    virtual const std::string& getNote() const { return note; }
    virtual const TW_TYPE& getTWType() const { return tw_type; }

    virtual void setSortNumber(const int& i) { this->sortNumber = i; }
    virtual void setCode(const std::string& s) { this->code = s; }
    virtual void setOfficialTitle(const std::string& s) { this->officialTitle = s; }
    virtual void setMediumTitle(const std::string& s) { this->mediumTitle = s; }
    virtual void setShortTitle(const std::string& s) { this->shortTitle = s; }
    virtual void setNote(const std::string& s) { this->note = s; }

    virtual std::string& getAt(size_t& index)
    {
        switch (index)
        {
        case 1:
            return code;
        case 2:
            return officialTitle;
        case 3:
            return mediumTitle;
        case 4:
            return shortTitle;
        case 5:
            return note;
        default:
            throw std::exception("getAt:: invalid index!");
        }
    }

private:
    int sortNumber;
    std::string code;
    std::string officialTitle;
    std::string mediumTitle;
    std::string shortTitle;
    std::string note;
    TW_TYPE tw_type;
};

