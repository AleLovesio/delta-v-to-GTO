//
// Created by soldato_fantasma aka Soltasto on 22/07/2018.
//

#ifndef DELTA_V_GTO_ORBIT_H
#define DELTA_V_GTO_ORBIT_H

#define GEO_ALT_M 35786000
#define GEO_ALT_KM 35786

class Orbit { //WARNING! Argument of periapsis should either be 0° or 180°. Altitude of inclination change can either be apogee or perigee.
public:
    Orbit(double const & perigee, double const & apogee, double const & inclination);

    double perigeeChange(double const & new_perigee);
    double perigeeChange(double const & new_perigee, double const & new_inclination);
    double apogeeChange(double const & new_apogee);
    double apogeeChange(double const & new_apogee, double const & new_inclination);
    double inclinationChange(double const & new_inclination, double const & altitude);

    double getPerigee() const;
    double getApogee() const;
    double getInclination() const;
    double getTotalDeltaVChange() const;
    double getSemiMajorAxis() const;
    double getOrbitalSpeed(double const & altitude) const;

    void print() const;

private:
    double _perigee; //meters
    double _apogee; //meters
    double _inclination; //degrees
    double _total_delta_v_change; // m/s

    static double _getSpeedCross(double const & speed, double const & inclination); // m/s
    static double _getSpeedAlong(double const & speed, double const & inclination); // m/s
};

#endif //DELTA_V_GTO_ORBIT_H
