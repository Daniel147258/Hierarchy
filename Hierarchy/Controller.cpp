#include "Controller.h"

bool Controller::predikates(Block* current_Block, ds::amt::MultiWayExplicitHierarchy<TW*>* hierachii, const std::string& str, TW_TYPE type, ds::amt::ImplicitSequence<Block*>& pom_IS, std::function<bool(Block*)> predikat)
{
    Slave<Block*, ds::amt::ImplicitSequence<Block*>::ImplicitSequenceIterator > slave;

    hierachii->processPreOrder(current_Block, [&](const Block* b)
        {
            slave.process_(b->sons_->begin(), b->sons_->end(), pom_IS, [&](Block* item) -> bool
                {
                    return predikat(item);
                });
        });
    outPut(pom_IS);
    return pom_IS.size() > 0 ? true : false;
}

bool Controller::startWith_(Block* current_Block, ds::amt::MultiWayExplicitHierarchy<TW*>* hierachii, const std::string& str, ds::amt::ImplicitSequence<Block*>& pom_IS)
{
    return this->predikates(current_Block, hierachii, str, TW_TYPE::State, pom_IS, [&, this](Block* item) -> bool
        {
            return (item->data_->getOfficialTitle().starts_with(str)) ? true : false;
        });
}

bool Controller::containWith_(Block* current_Block, ds::amt::MultiWayExplicitHierarchy<TW*>* hierachii, const std::string& str, ds::amt::ImplicitSequence<Block*>& pom_IS)
{
    return this->predikates(current_Block, hierachii, str, TW_TYPE::State, pom_IS, [&, this](Block* item) -> bool
        {
            return (item->data_->getOfficialTitle().find(str) != std::string::npos) ? true : false;
        });
}

bool Controller::containTW_TYPE_(Block* current_Block, ds::amt::MultiWayExplicitHierarchy<TW*>* hierachii, TW_TYPE type, ds::amt::ImplicitSequence<Block*>& pom_IS)
{
    return this->predikates(current_Block, hierachii, "", TW_TYPE::State, pom_IS, [&, this](Block* item) -> bool
        {
            return (item->data_->getTWType() == type) ? true : false;
        });
}

void Controller::outPut(ds::amt::ImplicitSequence<Block*>& pom_IS)
{
    int index2 = 0;
    for (const auto item : pom_IS)
    {
        index2++;
        std::cout << item->data_->getOfficialTitle() << "  -> " << index2 << std::endl;
    }
}

