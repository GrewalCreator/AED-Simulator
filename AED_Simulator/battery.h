#ifndef BATTERY_H
#define BATTERY_H


class Battery{
public:
    Battery();
    void depleteBatteryLevel();
    void chargeBattery();
    virtual ~Battery();

private:
    int batteryLevels;
};

#endif // BATTERY_H
