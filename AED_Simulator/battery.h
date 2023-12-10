#ifndef BATTERY_H
#define BATTERY_H


class Battery{
public:
    explicit Battery();
    void depleteBatteryLevel();
    void chargeBattery();
    int getBatteryLevels() const;
    virtual ~Battery();

private:
    int batteryLevels;
};

#endif // BATTERY_H
