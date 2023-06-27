#include "Application.h"


Application::Application(const std::string& fileRegion, const std::string& fileDistrict, const std::string& fileMunicipality)
{
    state_ = new State(fileRegion, fileDistrict, fileMunicipality);
    Block& root_Block = state_->getHierarchy()->getState();
    std::string currentPoin_string = root_Block.data_->getOfficialTitle();
    h_iterator_ = new HierarchyIterator(root_Block);

    this->startAplication(currentPoin_string, h_iterator_, controller_, state_);
}

Application::~Application()
{
    delete state_;
    delete h_iterator_;
}

void Application::startAplication(std::string& currentPoin_string, HierarchyIterator* h_iterator, Controller& controller, State* state)
{
    std::cout << "***********************************************************************************************************************" << std::endl;
    std::cout << "                                                       Vitajte                                                         " << std::endl;
    std::cout << "***********************************************************************************************************************" << std::endl;
    std::cout << "Vas zvoleny stat je: " << currentPoin_string << std::endl;
    std::cout << "Prosim stlacte prislusne cislo, v ktorom chcete pokracovat:" << std::endl;

    int zvolenaUzemnaJednotka = 0;

    bool continue_ = true;
    while (continue_)
    {
        evaluate_mainOPTION(*h_iterator, controller, zvolenaUzemnaJednotka, continue_);
    }
}

void Application::evaluate_mainOPTION(HierarchyIterator& h_iterator, Controller& controller, int& zvolenaUzemnaJednotka, bool& continue_)
{
    std::cout << "Prosim stlacte cislo pre operaciu:   Chod spat o level nizsie -> stlac(" << CODE_GO_UP << ") " << std::endl;
    std::cout << "Prosim stlacte cislo pre operaciu:   HLADAJ Uzemnu jednotku o level vyssie, ZACIATOCNIMI pismenami -> stlac(" << CODE_STARTWITH_FIND << ") " << std::endl;
    std::cout << "Prosim stlacte cislo pre operaciu:   HLADAJ Uzemnu jednotku o level vyssie, OBSAHUJUCE pismena -> stlac(" << CODE_CONTAIN_FIND << ") " << std::endl;
    std::cout << "Prosim stlacte cislo pre operaciu:   Chcem sa opytat, ci dana UJ obsahuje ine UJ -> stlac(" << CODE_CHOOSE << ") " << std::endl;
    std::string zvolenaOperaciaString = "";
    std::string zadanyNazov = "";
    std::getline(std::cin >> std::ws, zvolenaOperaciaString);
    int zvolenaOperacia = std::atoi(zvolenaOperaciaString.c_str());  // because input can be string, than application is still running
    if (!try_stopApplication(continue_, zvolenaOperaciaString, zvolenaOperacia, zadanyNazov, h_iterator, controller, zvolenaUzemnaJednotka))
    {
        evaluateInputOperations(zvolenaOperacia, zadanyNazov, h_iterator, controller, zvolenaUzemnaJednotka, continue_);
    }
}

void Application::evaluteInput(const int& zvolenaOperacia, std::string& zadanyNazov, HierarchyIterator& h_iterator, Controller& controller, int& zvolenaUzemnaJednotka, bool& continue_)
{
    if (zvolenaOperacia == CODE_STARTWITH_FIND || zvolenaOperacia == CODE_CONTAIN_FIND)
    {
        std::cout << "Zadaj hladany nazov: ";
        std::getline(std::cin >> std::ws, zadanyNazov);
    }
}

TW_TYPE getValueTWType(int index)
{
    switch (index)
    {
    case 0:
        return TW_TYPE::State;
    case 1:
        return TW_TYPE::Region;
    case 2:
        return TW_TYPE::District;
    case 3:
        return TW_TYPE::Municipality;
    default:
        return TW_TYPE::State;
    }
}


void Application::evaluateInputOperations(int& zvolenaOperacia, std::string& zadanyNazov, HierarchyIterator& h_iterator, Controller& controller, int& zvolenaUzemnaJednotka, bool& continue_)
{
    ds::amt::ImplicitSequence<Block*> IS_findedBlock;
    ds::amt::ImplicitSequence<Block*>& IS_currentBlock = *h_iterator.getReferenceBlock().sons_;
    auto& pointerBlock = h_iterator.getReferenceBlock();
    auto& tw_type_iterator = pointerBlock.data_->getTWType();

    switch (zvolenaOperacia)
    {
    case CODE_GO_UP:
        if (tw_type_iterator != TW_TYPE::State)
        {
            h_iterator.goUP();
            std::cout << ": " << h_iterator.getReferenceBlock().data_->getOfficialTitle() << std::endl;
        }
        else
        {
            std::cout << "Hlbka je uz minimalna, nemozete ist vyssie prosim zopakujte svoju volbu." << std::endl;
            evaluate_mainOPTION(h_iterator, controller, zvolenaUzemnaJednotka, continue_);
        }
        break;
    case CODE_STARTWITH_FIND:

        if (tw_type_iterator != TW_TYPE::Municipality)
        {
            evaluteInput(zvolenaOperacia, zadanyNazov, h_iterator, controller, zvolenaUzemnaJednotka, continue_);
            if (!try_stopApplication(continue_, zadanyNazov, zvolenaOperacia, zadanyNazov, h_iterator, controller, zvolenaUzemnaJednotka))
            {
                if (controller.startWith_(h_iterator_->getPointerBlock_(), state_->getHierarchy()->getMWEH(), zadanyNazov, IS_findedBlock))
                {
                    setInputPredikate(h_iterator, IS_findedBlock, continue_, zvolenaOperacia, zadanyNazov, controller, zvolenaUzemnaJednotka);
                }
                else
                {
                    std::cout << "Zadana uzemna jednotka sa nenasla!" << std::endl;
                    evaluate_mainOPTION(h_iterator, controller, zvolenaUzemnaJednotka, continue_);
                }
            }
        }
        else
        {
            std::cout << "Hlbka je uz hranicna, nemozete ist nizsie prosim zopakujte svoju volbu." << std::endl;
            evaluate_mainOPTION(h_iterator, controller, zvolenaUzemnaJednotka, continue_);
        }
        break;
    case CODE_CONTAIN_FIND:
        if (tw_type_iterator != TW_TYPE::Municipality)
        {
            evaluteInput(zvolenaOperacia, zadanyNazov, h_iterator, controller, zvolenaUzemnaJednotka, continue_);
            if (!try_stopApplication(continue_, zadanyNazov, zvolenaOperacia, zadanyNazov, h_iterator, controller, zvolenaUzemnaJednotka))
            {
                if (controller.containWith_(h_iterator_->getPointerBlock_(), state_->getHierarchy()->getMWEH(), zadanyNazov, IS_findedBlock))
                {
                    setInputPredikate(h_iterator, IS_findedBlock, continue_, zvolenaOperacia, zadanyNazov, controller, zvolenaUzemnaJednotka);
                }
                else
                {
                    std::cout << "Zadana uzemna jednotka sa nenasla!" << std::endl;
                    evaluate_mainOPTION(h_iterator, controller, zvolenaUzemnaJednotka, continue_);
                }
            }
        }
        else
        {
            std::cout << "Hlbka je uz hranicna, nemozete ist nizsie prosim zopakujte svoju volbu." << std::endl;
            evaluate_mainOPTION(h_iterator, controller, zvolenaUzemnaJednotka, continue_);
        }
        break;
    case CODE_CHOOSE:
        if (tw_type_iterator != TW_TYPE::Municipality)
        {
            evaluteInput(zvolenaOperacia, zadanyNazov, h_iterator, controller, zvolenaUzemnaJednotka, continue_);
            if (!try_stopApplication(continue_, zadanyNazov, zvolenaOperacia, zadanyNazov, h_iterator, controller, zvolenaUzemnaJednotka))
            {
                int zadanyIndex = 0;
                std::string zadanyIndexString = "";
                std::cout << "Prosim vyberte si hladany typ: STAT == 1" << std::endl;
                std::cout << "Prosim vyberte si hladany typ: REGION == 2" << std::endl;
                std::cout << "Prosim vyberte si hladany typ: OKRES == 3" << std::endl;
                std::cout << "Prosim vyberte si hladany typ: OBEC == 4" << std::endl;
                std::cout << "Zadaj cislo pre typ: " << std::endl;
                std::getline(std::cin >> std::ws, zadanyIndexString);
                zadanyIndex = std::atoi(zadanyIndexString.c_str());
                if (controller.containTW_TYPE_(h_iterator_->getPointerBlock_(), state_->getHierarchy()->getMWEH(), getValueTWType(zadanyIndex - 1), IS_findedBlock))
                {
                    std::cout << "Zadana uzemna jednotka sa nasla!" << std::endl;
                    setInputPredikate(h_iterator, IS_findedBlock, continue_, zvolenaOperacia, zadanyNazov, controller, zvolenaUzemnaJednotka);
                }
                else
                {
                    std::cout << "Zadana uzemna jednotka sa nenasla!" << std::endl;
                    evaluate_mainOPTION(h_iterator, controller, zvolenaUzemnaJednotka, continue_);
                }
            }
        }
        else
        {
            std::cout << "Hlbka je uz maximalna, nemozete ist nizsie prosim zopakujte svoju volbu." << std::endl;
            evaluate_mainOPTION(h_iterator, controller, zvolenaUzemnaJednotka, continue_);
        }
        break;
    default:
        evaluate_mainOPTION(h_iterator, controller, zvolenaUzemnaJednotka, continue_);
        break;

    }
}

void Application::printTW(HierarchyIterator& h_iterator, const std::string& Officialtitle)
{
    switch (h_iterator.getReferenceBlock().data_->getTWType())
    {
    case TW_TYPE::State:
        std::cout << "Stat" << std::endl;
        break;
    case TW_TYPE::Region:
        std::cout << "Kraj: " << Officialtitle << std::endl;
        break;
    case TW_TYPE::District:
        std::cout << "Okres: " << Officialtitle << std::endl;
        break;
    case TW_TYPE::Municipality:
        std::cout << "Obec: " << Officialtitle << std::endl;
        break;
    }
}

int getValueTWType(TW_TYPE type)
{
    switch (type)
    {
    case TW_TYPE::State:
        return 0;
    case TW_TYPE::Region:
        return 1;
    case TW_TYPE::District:
        return 2;
    case TW_TYPE::Municipality:
        return 3;
    default:
        return -1;
    }
}

void Application::setCurrentBlock(const int& zvolenaUzemnaJednotka, HierarchyIterator& h_iterator, ds::amt::ImplicitSequence<Block*>& IS_findedBlock)
{
    if (h_iterator.getReferenceBlock().data_->getTWType() != TW_TYPE::State
        && zvolenaUzemnaJednotka == 0)
    {
        h_iterator.goUP();
        std::cout << state_->getHierarchy()->getMWEH()->size() << std::endl;
    }
    else if (zvolenaUzemnaJednotka >= 1
        && zvolenaUzemnaJednotka <= IS_findedBlock.size())
    {
        auto newCurrentBlock = IS_findedBlock.access(zvolenaUzemnaJednotka - 1)->data_;
        h_iterator.setPointer(newCurrentBlock, getValueTWType(newCurrentBlock->data_->getTWType()));
        printTW(h_iterator, h_iterator.getReferenceBlock().data_->getOfficialTitle());
    }
}

void Application::setInputPredikate(HierarchyIterator& h_iterator, ds::amt::ImplicitSequence<Block*>& IS_findedBlock,
    bool& continue_, int& zvolenaOperacia, std::string& zadanyNazov, Controller& controller, int& zvolenaUzemnaJednotka)
{
    int zadanyIndex = 0;
    std::string zadanyIndexString = "";
    auto IS_size_ = IS_findedBlock.size();
    if (IS_size_ >= 1)
    {
        std::cout << "Zadaj cislo pre ukazovatel uzemnej jednotky: " << std::endl;
        std::getline(std::cin >> std::ws, zadanyIndexString);
        zadanyIndex = std::atoi(zadanyIndexString.c_str());
        if (!try_stopApplication(continue_, zadanyIndexString, zvolenaOperacia, zadanyNazov, h_iterator, controller, zvolenaUzemnaJednotka))
        {
            if (zadanyIndex > IS_size_ || zadanyIndex <= 0)
            {
                std::cout << "Zadane cislo nie spravne prosim zopakujte moznost znova." << std::endl;
                setInputPredikate(h_iterator, IS_findedBlock, continue_, zvolenaOperacia, zadanyNazov, controller, zvolenaUzemnaJednotka);
            }
            else
            {
                setCurrentBlock(zadanyIndex, h_iterator, IS_findedBlock);
            }
        }
    }
}

bool Application::try_stopApplication(bool& continue_, std::string& inputStr, int& zvolenaOperacia, std::string& zadanyNazov, HierarchyIterator& h_iterator, Controller& controller, int& zvolenaUzemnaJednotka)
{
    std::string currentStr = inputStr;
    for (size_t i = 0; i < inputStr.size(); i++)
    {
        inputStr[i] = std::tolower(inputStr[i]);
    }
    if (inputStr.find("exit") != std::string::npos)
    {
        std::cout << "EXIT of Appilication.";
        std::cin.ignore();
        continue_ = false;
        return true;
    }
    else
    {
        inputStr = currentStr;
        return false;
    }
}
