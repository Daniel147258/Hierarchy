#include "CSV__.h"

void CSV__::createTWInstance(TW_TYPE type, TW*& tw)
{
    switch (type)
    {
    case TW_TYPE::Region:
        tw = new TW(0, "", "", "", "", "", TW_TYPE::Region);
        break;

    case TW_TYPE::District:
        tw = new TW(0, "", "", "", "", "", TW_TYPE::District);
        break;

    case TW_TYPE::Municipality:
        tw = new TW(0, "", "", "", "", "", TW_TYPE::Municipality);
        break;

    default:
        throw std::logic_error("tw has not instance!");
    }
}

void CSV__::setTWProperties(int column_count, TW* tw, std::string& word)
{
    switch (column_count)
    {
    case 1:
        tw->setSortNumber(std::stoi(word));
        break;

    case 2:
        tw->setCode(word);
        break;

    case 3:
        tw->setOfficialTitle(word);
        break;

    case 4:
        tw->setMediumTitle(word);
        break;

    case 5:
        tw->setShortTitle(word);
        break;

    case 6:
        tw->setNote(word);
        break;
    default:
        throw std::logic_error("void readFileToVector(const std::string& file, std::vector<TW*>& struture_vector): The size is defined, but in this method was counted more.");
        break;
    }
}

void CSV__::readFileTo_IS(const std::string& file, ds::amt::ImplicitSequence<TW*>& IS_, TW_TYPE type)
{
    std::fstream file_input;
    std::string line, word;
    file_input.open(file);

    int column_count = 0;
    int row_count = 0;

    while (std::getline(file_input, line))
    {
        row_count++;

        std::stringstream s(line);

        if (row_count >= 2)
        {
            TW* tw = nullptr;
            createTWInstance(type, tw);

            while (std::getline(s, word, ';'))
            {
                column_count++;
                setTWProperties(column_count, tw, word);
            }
            IS_.insertLast().data_ = tw;
            column_count = 0;
        }
    }
}

