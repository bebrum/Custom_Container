#include <iostream>
#include <string>
#include "List.h"



class IObserver {
public:
    virtual void update(const std::string& message) = 0;
};

class CarBuilder;

struct Car
{
    friend class CarBuilder;

    Car() : number(""), quality("") {}

    std::string getNumber() const {
        return number;
    }

    std::string getQuality() const {
        return quality;
    }

private:
    std::string number;
    std::string quality;
};

class CarBuilder
{
public:
    CarBuilder() : car() {}

    CarBuilder& setNumber(const std::string& num)
    {
        car.number = num;
        return *this;
    }

    CarBuilder& setQuality(const std::string& qual)
    {
        car.quality = qual;
        return *this;
    }

    Car build()
    {
        return car;
    }

private:
    Car car;
};

class AutoPark {
private:
    List<IObserver*> observers;
    List<Car> cars;
public:
    void addObserver(IObserver* observer) {
        observers.insert(observer);
    }

    void addCar(const Car& car) {
        cars.insert(car);
        notifyObservers("new car added: " + car.getNumber());
    }

    void notifyObservers(const std::string& message) {
        for (auto observer : observers) {
            observer.m_node->update(message);
        }
    }
};

class Client : public IObserver {
public:
    void update(const std::string& message) override {
        std::cout << "Client received notification: " << message << std::endl;
    }
};

int main()
{
    AutoPark autoPark;
    Client client;

    autoPark.addObserver(&client);

    Car car = CarBuilder().setNumber("ABC123").setQuality("High").build();
    autoPark.addCar(car);

    return 0;
}