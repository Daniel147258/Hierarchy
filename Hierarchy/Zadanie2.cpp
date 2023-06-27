#include <Windows.h>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>

#include "TerritorialWhole.h"
#include "CSV__.h"
#include "TW_TYPE.h"
#include "State.h"
#include "Slave.h"
#include "Controller.h"
#include "libds/heap_monitor.h"
#include "MW_Hierarchy_Iterator.h"
#include "Application.h"

#include"libds/adt/table.h"


int main()
{
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    setlocale(LC_ALL, "slovak");
    initHeapMonitor();

    std::string regionFile("C:\\Users\\matej\\OneDrive\\Desktop\\kraje.csv");
    std::string districtFile("C:\\Users\\matej\\OneDrive\\Desktop\\okresy.csv");
    std::string municipalityFile("C:\\Users\\matej\\OneDrive\\Desktop\\obce.csv");
    std::string& r_f = regionFile;
    std::string& d_f = districtFile;
    std::string& m_f = municipalityFile;

    Application* app = new Application(r_f, d_f, m_f);

    delete app;
}