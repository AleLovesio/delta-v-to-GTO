//
// Created by soldato_fantasma aka Soltasto on 22/07/2018.
//

#ifndef DELTA_V_GTO_ORBIT_H
#define DELTA_V_GTO_ORBIT_H

#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>

#define EARTH_RADIUS_M 6371000
#define EARTH_RADIUS_KM 6371
#define MU 3.986005e14
#define GEO_V 3075
#define GEO_ALT_M 35786000
#define GEO_ALT_KM 35786

using namespace std;
class Orbit { //WARNING! Argument of periapsis should either be 0° or 180°. Altitude of inclination change can either be apogee or perigee.
public:
    Orbit(double const &perigee, double const & apogee, double const & inclination);
    double apogeeChange(double const & new_apogee);
    double apogeeChange(double const & new_apogee, double const & new_inclination);
    double perigeeChange(double const & new_perigee);
    double perigeeChange(double const & new_perigee, double const & new_inclination);
    double inclinationChange(double const & new_inclination, double const &altitude);
    double getApogee() const;
    double getPerigee() const;
    double getInclination() const;
    double getTotalDeltaVChange() const;
    double getSemiMajorAxis() const;
    double getOrbitalSpeed(double const & distance) const;
    void print() const;

private:
    double _apogee; //meters
    double _perigee; //meters
    double _inclination; //degrees
    double _total_delta_v_change; // m/s
    double _getSpeedCross(double const & speed, double const & inclination) const; // m/s
    double _getSpeedAlong(double const & speed, double const & inclination) const; // m/s



};


#endif //DELTA_V_GTO_ORBIT_H
