/*
#include <iostream>
#include <cassert>
using namespace std;
*/

//=================== COMMENT OUT UP ====================

class Vehicle {
public:
    Vehicle(string ID){
        m_ID = ID;
    }
    string id() const{  // get ID
        return m_ID;
    }
    virtual ~Vehicle() {};  
    virtual string description() const = 0; // description of the Vehicle
    virtual bool canHover() const{  // if the Vehicle can hover
        return true;
    }
private:
    string m_ID;    // each vehicle has a ID
};

class Drone : public Vehicle {
public:
    Drone(string ID):Vehicle(ID){}
    virtual string description() const{
        return "a drone";
    }
    ~Drone(){
        cout << "Destroying " << id() << ", a drone" << endl;
    }
};

class Balloon : public Vehicle{
public:
    Balloon(string name, double dia):Vehicle(name){
        m_dia = dia;
    }
    virtual string description() const{
        if(m_dia >= 8) return "a large balloon";    // diameter equal or more than 8 are large balloon
        else return "a small balloon";
    }
    ~Balloon(){
        cout << "Destroying the balloon " << id() << endl;
    }
private:
    double m_dia;   // each balloon has a diameter
};

class Satellite : public Vehicle{
public:
    Satellite(string ID):Vehicle(ID){}
    virtual string description() const{
        return "a satellite";
    }
    virtual bool canHover() const{  // A satellite can't hover
        return false;
    }
    ~Satellite(){
        cout << "Destroying the satellite " << id() << endl;
    }
};

//=================== COMMENT OUT DOWN ====================
/*
void display(const Vehicle* v)
{
    cout << v->id() << " is " << v->description();
    if (v->canHover())
        cout << ", so it can hover";
    cout << endl;
}

int main()
{
    Vehicle* fleet[4];
    fleet[0] = new Drone("CB4UP");
    // Balloons have an id and a diameter in meters  Balloons with a
    // diameter under 8 meters are small balloons; those with a diameter
    // 8 meters or more are large balloons
    fleet[1] = new Balloon("99LB", 6.3);
    fleet[2] = new Balloon("CN20230201", 30.2);
    fleet[3] = new Satellite("EB8675309");

    for (int k = 0; k < 4; k++)
        display(fleet[k]);

    // Clean up the vehicles before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete fleet[k];
}
*/