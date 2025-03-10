#include <iostream>
#include <vector>
#include <algorithm>

#include "windows.h"

#include "DLL/transport.h"
#include "DLL/air.h"
#include "DLL/ground.h"
#include "DLL/camel.h"
#include "DLL/camelfast.h"
#include "DLL/centaur.h"
#include "DLL/roverboots.h"
#include "DLL/broom.h"
#include "DLL/flyingCarpet.h"
#include "DLL/eagle.h"

#include "DLL/myException.h"

namespace  race {
    enum eRaceType {
        Ground = 1,
        Air,
        GroundAir
    };
    enum eTransport {
        RoverBoots = 1,
        Broom,
        Camel,
        Centaur,
        Eagle,
        CamelFast,
        FlyingCarpet
    };
}

bool checkTransport(const int raceNum, const int transpNum, const std::vector<Transport*> trForRace, const std::vector<std::string> allTransp);
bool mySortFunc(Transport* a, Transport* b);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    std::vector<std::string> allTransport{ "Ботинки-вездеходы", "Метла", "Верблюд", "Кентавр", "Орел", "Верблюд-быстроход", "Ковер-самолет" };

     std::vector<Transport*> transportForRace{};
     Transport* tr{};
     int exit{};
     bool firstRace{ true };
     do {
         int raceTypeNum;
         do {
             transportForRace.clear();
             if (firstRace) {
                 std::cout << "Добро пожаловать в гоночный стимулятор!" << std::endl;
             }
             std::cout << "1. Гонка для наземного транспорта" << std::endl;
             std::cout << "2. Гонка для воздушного транспорта" << std::endl;
             std::cout << "3. Гонка для наземного и воздушного транспорта" << std::endl;
             std::cout << "Введите тип гонки: ";
             std::cin >> raceTypeNum;             
             system("cls");
             if ((raceTypeNum != 1) && (raceTypeNum != 2) && (raceTypeNum != 3)) {
                 std::cout << "Неизвестный тип гонки!\n";
             }
         } while ((raceTypeNum != 1) && (raceTypeNum != 2) && (raceTypeNum != 3));

         float distanceLen;
         do {
             std::cout << "Введите длину дистанции (должна быть положительна): ";             
             std::cin >> distanceLen;
             system("cls");
         } while (distanceLen < 0);

         int act{};    
         do {
             if (transportForRace.size() < 2) {
                 std::cout << "Должно быть зарегестрировано хотя бы 2 транспортных средства" << std::endl;
             }
             std::cout << "1. Зарегистрировать транспорт" << std::endl;
             if (transportForRace.size() > 1) {
                 std::cout << "2. Начать гонку" << std::endl;
             }
             std::cout << "Выберите действие: ";
             std::cin >> act;
             system("cls");
             if (act == 1) {
                 int inpTransport;
                 do {
                     switch (raceTypeNum) {
                     case static_cast<int>(race::Ground):
                         std::cout << "Гонка для наземного транспорта. ";
                         break;
                     case static_cast<int>(race::Air):
                         std::cout << "Гонка для воздушного транспорта. ";
                         break;
                     case static_cast<int>(race::GroundAir):
                         std::cout << "Гонка для наземного и воздушного транспорта. ";
                         break;
                     }
                     std::cout << "Расстояние : " << distanceLen << std::endl;

                     if (transportForRace.size()) {
                         std::cout << "Зарегестрированные транспортные средства: ";
                         for (size_t i = 0; i < transportForRace.size(); ++i) {
                             std::cout << transportForRace.at(i)->getName();
                             std::cout << ((i < transportForRace.size() - 1) ? ", " : "\n");
                         }
                     }

                     for (size_t i = 0; i < allTransport.size(); ++i) {
                         std::cout << i + 1 << ". " << allTransport.at(i) << std::endl;
                     }
                     std::cout << "0. Закончить регистрацию" << std::endl;
                     std::cout << "Выберите транспорт или 0 для окончания процесса регистрации: ";
                     std::cin >> inpTransport;
                     system("cls");
                     if (inpTransport) {
                         if (checkTransport(raceTypeNum, inpTransport, transportForRace, allTransport)) {
                             try {
                                 switch (inpTransport) {
                                 case static_cast<int>(race::RoverBoots):
                                     tr = new RoverBoots(distanceLen);
                                     break;
                                 case static_cast<int>(race::Camel):
                                     tr = new Camel(distanceLen);
                                     break;
                                 case static_cast<int>(race::Centaur):
                                     tr = new Centaur(distanceLen);
                                     break;
                                 case static_cast<int>(race::CamelFast):
                                     tr = new CamelFast(distanceLen);
                                     break;
                                 case static_cast<int>(race::Broom):
                                     tr = new Broom(distanceLen);
                                     break;
                                 case static_cast<int>(race::Eagle):
                                     tr = new Eagle(distanceLen);
                                     break;
                                 case static_cast<int>(race::FlyingCarpet):
                                     tr = new FlyingCarpet(distanceLen);
                                     break;
                                 }
                             }
                             catch (MyException myExc) {
                                 std::cout << myExc.what() << std::endl;
                             }
                             transportForRace.push_back(tr);
                             std::cout << tr->getName() << " успешно зарегистрирован!" << std::endl;
                         }
                     }

                 } while (inpTransport);
             }
         } while ((act != 2) || (transportForRace.size() < 2));

         for (auto t : transportForRace) {
             t->calcRaceResult();
         }

         std::sort(transportForRace.begin(), transportForRace.end(), mySortFunc);

         std::cout << "Результат гонки:" << std::endl;

         for (size_t i = 0; i < transportForRace.size(); ++i) {
             std::cout << i+1 << ". " << transportForRace.at(i)->getName() << ". Время: " << transportForRace.at(i)->getResult() << std::endl;
         }
         firstRace = false;
         std::cout << "\n1. Провести ещё одну гонку\n" << "2. Выйти" << std::endl;
         std::cout << "Выберите действие: ";
         std::cin >> exit;
         system("cls");
     } while (exit == 1);
     return 0;
}

bool checkTransport(const int raceNum, const int transpNum, const std::vector<Transport*> trForRace, const std::vector<std::string> allTransp){
    if(raceNum == static_cast<int>(race::Air)) {
        switch (transpNum) {
        case static_cast<int>(race::RoverBoots):
        case static_cast<int>(race::Camel):
        case static_cast<int>(race::Centaur):
        case static_cast<int>(race::CamelFast):
            std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
            return false;
        }
    }
    else if(raceNum == static_cast<int>(race::Ground)) {
        switch (transpNum) {
        case static_cast<int>(race::Broom):
        case static_cast<int>(race::Eagle):
        case static_cast<int>(race::FlyingCarpet):
            std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
            return false;
        }
    }
    for(auto t:trForRace){
        if(t->getName() == allTransp.at(static_cast<size_t>(transpNum)-1)){
            std::cout << allTransp.at(static_cast<size_t>(transpNum) - 1) << " уже зарегистрирован!" << std::endl;
            return false;
        }
    }
    return true;
}

bool mySortFunc(Transport* a, Transport* b){
    return a->getResult() < b->getResult();
}



