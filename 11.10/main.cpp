#include <iostream>
#include <string>
using namespace std;

class Base {
public:
    static int people_on_base;
    static int vehicles_on_base;
    static double petrol_on_base;
    static double goods_on_base;
};

class Vehicle {
    double petrol_amount;
    double tank_volume;
public:
    Vehicle(double petrol_amount, double tank_volume) : petrol_amount(petrol_amount), tank_volume(tank_volume) {}
    double getTankVolume() {
        return tank_volume;
    }
    double getPetrolAmount() {
        return petrol_amount;
    }
    virtual void arrive() {
        cout << "Vehicle arrived at the base." << endl;
    }
    virtual bool leave() {
        return true;
    }
};

class Bus : public Vehicle {
    int people;
    int max_people;
public:
    Bus(int people, int max_people, double petrol, double max_petrol) : Vehicle(petrol, max_petrol), people(people), max_people(max_people) {}
    int getPeopleCount() {
        return people;
    }
    int getMaxPeople() {
        return max_people;
    }
    void arrive() {
        cout << "Bus arrived at the base with " << people << " passengers." << endl;
        Base::people_on_base += people;
        Vehicle::arrive();
    }
    bool leave() {
        if (Base::people_on_base > 0) {
            if (Base::people_on_base > max_people) {
                people = max_people;
                Base::people_on_base -= max_people;
            }
            else {
                people = (max_people - Base::people_on_base);
            }

            Vehicle::leave();
        }

        return false;
    }
};

class Truck : public Vehicle {
    double load;
    double max_load;
public:
    Truck(double load, double max_load, double petrol, double max_petrol) : Vehicle(petrol, max_petrol), load(load), max_load(max_load) {}
    double getCurrentLoad() {
        return load;
    }
    double getMaxLoad() {
        return max_load;
    }
    void arrive() {
        cout << "Truck arrived at the base with a load of " << load << " tons." << endl;
        Base::goods_on_base += load;
        Vehicle::arrive();
    }
    bool leave() {
        if (Base::goods_on_base > 0) {
            if (Base::goods_on_base > max_load) {
                load = max_load;
                Base::goods_on_base -= max_load;
            }
            else {
                load = (max_load - Base::goods_on_base);
            }

            Vehicle::leave();
        }

        return false;
    }
};

int Base::people_on_base = 10;
int Base::vehicles_on_base = 0;
double Base::petrol_on_base = 25000.0;
double Base::goods_on_base = 1500.0;

int main() {
    Bus bus(20, 50, 20.0, 100.0);
    Truck truck(10, 30.0, 30.0, 150.0);

    bus.arrive();
    truck.arrive();

    if (bus.leave()) {
        cout << "Bus successfully left the base." << endl;
    }
    else {
        cout << "Bus couldn't leave the base." << endl;
    }

    if (truck.leave()) {
        cout << "Truck successfully left the base." << endl;
    }
    else {
        cout << "Truck couldn't leave the base." << endl;
    }

    return 0;
}