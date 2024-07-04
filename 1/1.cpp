
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
class Transport {
public:
    std::string name; // Название транспорта
    int wheelCount; // Количество колес
    int maxSpeed;     // Максимальная скорость
    
    Transport(std::string n, int m, int w) : name(n), maxSpeed(m), wheelCount(w) {}

    virtual void displayUniqueFeatures() = 0; // Виртуальная функция для отображения уникальных характеристик
    virtual ~Transport() {}
};

class  bike : public Transport {
public:

    bike(std::string n, int m, int w) : Transport(n, m, w) {}
    void displayUniqueFeatures() override {}
};

class scooter : public Transport {
public:
    bool hasBell;  // Наличие звонка

    scooter(std::string n, int m, int w, bool b) : Transport(n, m, w), hasBell(b) {}

    void displayUniqueFeatures() override {
        std::cout << "Наличие звонка: " << (hasBell ? "Да" : "Нет") << std::endl;
    }
};

class aftomobile : public Transport {
public:
    aftomobile(std::string n, int m, int w) : Transport(n, m, w) {}
    void displayUniqueFeatures() override {}
};

class bus : public Transport {
public:
    int humans; // количество пассажиров

    bus(std::string n, int m, int w, int h) : Transport(n, m, w), humans(h) {}

    void displayUniqueFeatures() override {
        std::cout << "Максимальное количество пассажиров: " << humans << std::endl;
    }
};

// Абстрактный класс Фабрики Транспорта
class TransportFactory {
public:
    virtual std::unique_ptr<Transport> createTransport(std::string name, int maxSpeed, int wheelCount) = 0;
    virtual ~TransportFactory() {}
};

// Конкретная фабрика для создания Велосипедов
class BikeFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport(std::string name, int maxSpeed, int wheelCount) override {
        return std::make_unique<bike>(name, maxSpeed, wheelCount);
    }
};

// Конкретная фабрика для создания Скутеров
class ScooterFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport(std::string name, int maxSpeed, int wheelCount) override {
        // Здесь предполагается, что у всех скутеров есть звонок
        return std::make_unique<scooter>(name, maxSpeed, wheelCount, true);
    }
};

// Конкретная фабрика для создания Автомобилей
class CarFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport(std::string name, int maxSpeed, int wheelCount) override {
        return std::make_unique<aftomobile>(name, maxSpeed, wheelCount);
    }
};

// Конкретная фабрика для создания Автобусов
class BusFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport(std::string name, int maxSpeed, int wheelCount) override {
        // Здесь предполагается, что у всех автобусов есть пассажиры
        return std::make_unique<bus>(name, maxSpeed, wheelCount, 20); // Примерное количество пассажиров
    }
};



int main()
{
	setlocale(LC_ALL, "Russian");
    BikeFactory bikeFactory;
    ScooterFactory scooterFactory;
    CarFactory carFactory;
    BusFactory busFactory;
    std::vector<std::unique_ptr<Transport>> transportArray;
    transportArray.push_back(bikeFactory.createTransport("Мотоцикл", 140, 2));
    transportArray.push_back(scooterFactory.createTransport("Самокат", 20, 2));
    transportArray.push_back(carFactory.createTransport("Автомобиль", 150, 4));
    transportArray.push_back(busFactory.createTransport("Автобус", 100, 6));
    
    std::string text;
    std::getline(std::cin, text);

    std::vector<int> numbers;
    std::stringstream ss(text);
    int number;
    while (ss >> number) {
        numbers.push_back(number);
    }
    for (int num : numbers) {
        if(num< 4){
            std::cout << "Наименование транспорта: " << transportArray[num]->name << std::endl;
            std::cout << "Кол-во колес: " << transportArray[num]->wheelCount << std::endl;
            std::cout << "Максимальная скорость: " << transportArray[num]->maxSpeed << "км/ч" << std::endl;
            transportArray[num]->displayUniqueFeatures();
        }
        else
            std::cout << "НЕИЗВЕСТНЫЙ ТИП ТРАНСПОРТА " << std::endl;
        std::cout << std::endl;
    }
  
    return 0;
}
