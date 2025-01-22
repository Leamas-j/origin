// Addresses.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

class Address {
    std::string city;
    std::string street;
    int house;
    int flat;
public:
    Address(std::string city, std::string street, int house, int flat) {
        this->city = city;
        this->street = street;
        this->house = house;
        this->flat = flat;
    }
    std::string get_output_address() {
        std::string tmpString = city + ", " + street + ", " + std::to_string(house) + ", " + std::to_string(flat);
        return tmpString;
    }
    std::string get_city(){
        return city;
    }
};

void sort(Address** addresses, int size);

int main()
{    
    SetConsoleOutputCP(1251);     
    Address** adr;
    int addrCount{};
    std::string lCity;
    std::string lStreet;
    int lHouse;
    int lFlat;
    std::ifstream fin{ "in.txt" };
    if (fin.is_open()) {
        if (fin >> addrCount) {
            adr = new Address * [addrCount];
            for (int i = 0; i < addrCount; ++i) {
                fin >> lCity >> lStreet >> lHouse >> lFlat;
                adr[i] = new Address(lCity, lStreet, lHouse, lFlat);
            }
            sort(adr, addrCount);
            std::ofstream fout{ "out.txt" };
            if (fout.is_open()) {
                fout << addrCount << std::endl;
                for (int i =  0; i < addrCount; ++i) {
                    fout << adr[i]->get_output_address() << std::endl;
                }
                fout.close();
                for (int i = 0; i < addrCount; ++i) {
                    delete adr[i];
                }
                delete[] adr;
            }
            else {
                std::cout << "Не получилось открыть файл! \"out.txt\"" << std::endl;
            }
        }
        fin.close();
    }
    else {
        std::cout << "Не получилось открыть файл! \"in.txt\"" << std::endl;
    }    
}

void sort(Address** addresses, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (strcmp(addresses[i]->get_city().c_str(), addresses[j]->get_city().c_str()) > 0) {
                Address* tmpAdr = addresses[i];
                addresses[i] = addresses[j];
                addresses[j] = tmpAdr;
            }
        }
    }
}
