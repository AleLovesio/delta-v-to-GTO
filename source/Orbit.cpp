//
// Created by soldato_fantasma aka Soltasto on 22/07/2018.
//


#include "Orbit.h"

//Constructor, sets the orbit parameters to begin with
Orbit::Orbit(double const & perigee, double const & apogee, double const & inclination) {
    _perigee                =   perigee;
    _apogee                 =   apogee;
    _inclination            =   inclination;
    _total_delta_v_change   =   0;
}

//Returns the Apogee
double Orbit::getApogee() const {
    return _apogee;
}

//Returns the Perigee
double Orbit::getPerigee() const {
    return _perigee;
}

//Returns the Inclination
double Orbit::getInclination() const {
    return _inclination;
}
//Returns the SMA
double Orbit::getSemiMajorAxis() const {
    return ((_perigee+_apogee)/2) + EARTH_RADIUS_M;
}
//Returns the current orbit speed at a certain altitude
double Orbit::getOrbitalSpeed(double const & distance) const {
    return sqrt(MU * (  (2/(distance + EARTH_RADIUS_M))  -  (1/getSemiMajorAxis())  )  );
}
//returns the total delta v change since orbit declaration
double Orbit::getTotalDeltaVChange() const {
    return _total_delta_v_change;
}
//Prints the Orbit data
void Orbit::print() const {
    cout << setprecision(4) << fixed << "Current Orbit: "
         << _perigee/1000 << " km x "
         << _apogee/1000 << " km x "
         << _inclination << " degrees; " << endl
         << "Apogee Speed:" << getOrbitalSpeed(_apogee)
         << " m/s; Perigee Speed: " << getOrbitalSpeed(_perigee)
         << " m/s; delta v to this orbit: " << getTotalDeltaVChange() << endl << endl;
}
//Performs an Apogee + Inclination change
double Orbit::apogeeChange(double const & new_apogee, const double & new_inclination) {
    //Calculating the speeds before the burn
    double v_before         =   getOrbitalSpeed(_perigee);
    double v_before_cross   =   _getSpeedCross(v_before,_inclination);
    double v_before_along   =   _getSpeedAlong(v_before,_inclination);

    //Changing the orbit parameters after the burn
    _apogee         =   new_apogee;
    _inclination    =   new_inclination;

    //Calculating the speeds after the burn
    double v_next           =   getOrbitalSpeed(_perigee);
    double v_next_cross     =   _getSpeedCross(v_next,_inclination);
    double v_next_along     =   _getSpeedAlong(v_next,_inclination);

    //Calculating the speed change
    double delta_v_change   =   sqrt(pow(v_next_cross - v_before_cross,2) + pow(v_next_along - v_before_along,2)) ;

    //Saving the aggregate speed change
    _total_delta_v_change   +=  delta_v_change;
    return delta_v_change;
}
//Performs an Apogee change
double Orbit::apogeeChange(double const & new_apogee) {
    //Calculating the speed before the burn
    double delta_v_before   =   getOrbitalSpeed(_perigee);

    //Changing the orbit parameters after the burn
    _apogee     =   new_apogee;

    //Calculating the speed after the burn
    double delta_v_next     =   getOrbitalSpeed(_perigee);

    //Calculating the speed change
    double delta_v_change   =   fabs(delta_v_next-delta_v_before);

    //Saving the aggregate speed change
    _total_delta_v_change   +=  delta_v_change;
    return delta_v_change;
}
//Performs a Perigee + Inclination change
double Orbit::perigeeChange(double const & new_perigee, const double & new_inclination) {
    //Calculating the speeds before the burn
    double v_before         =   getOrbitalSpeed(_apogee);
    double v_before_cross   =   _getSpeedCross(v_before,_inclination);
    double v_before_along   =   _getSpeedAlong(v_before,_inclination);

    //Changing the orbit parameters after the burn
    _perigee        =   new_perigee;
    _inclination    =   new_inclination;

    //Calculating the speeds after the burn
    double v_next           =   getOrbitalSpeed(_apogee);
    double v_next_cross     =   _getSpeedCross(v_next,_inclination);
    double v_next_along     =   _getSpeedAlong(v_next,_inclination);

    //Calculating the speed change
    double delta_v_change   =   sqrt(pow(v_next_cross - v_before_cross,2) + pow(v_next_along - v_before_along,2)) ;

    //Saving the aggregate speed change
    _total_delta_v_change   +=  delta_v_change;
    return delta_v_change;
}
//Performs a Perigee change
double Orbit::perigeeChange(double const & new_perigee) {
    //Calculating the speed before the burn
    double delta_v_before   =   getOrbitalSpeed(_apogee);

    //Changing the orbit parameters after the burn
    _perigee    =   new_perigee;

    //Calculating the speed after the burn
    double delta_v_next     =   getOrbitalSpeed(_apogee);

    //Calculating the speed change
    double delta_v_change   =   fabs(delta_v_next-delta_v_before);

    //Saving the aggregate speed change
    _total_delta_v_change   +=  delta_v_change;
    return delta_v_change;
}
//performs an Inclination change
double Orbit::inclinationChange(double const & new_inclination, double const & altitude) {
    double delta_v_change, speed_along_before, speed_cross_before, speed_along_next, speed_cross_next;

    if(_inclination!=new_inclination) { //checking if the inclinations has really changed
        if (altitude == _perigee) { //checking if the inclination change burn is at perigee

            //Calculating the speeds before the burn
            speed_along_before  =   _getSpeedAlong(getOrbitalSpeed(_perigee), _inclination);
            speed_cross_before  =   _getSpeedCross(getOrbitalSpeed(_perigee), _inclination);

            //Changing the orbit parameters after the burn
            _inclination        =   new_inclination;

            //Calculating the speeds after the burn
            speed_along_next    =   _getSpeedAlong(getOrbitalSpeed(_perigee), _inclination);
            speed_cross_next    =   _getSpeedCross(getOrbitalSpeed(_perigee), _inclination);

            //Calculating the speed change
            delta_v_change      =   sqrt(
                    pow((speed_along_next - speed_along_before), 2) + pow((speed_cross_next - speed_cross_before), 2));

        } else if (altitude == _apogee) { //checking if the inclination change burn is at apogee

            //Calculating the speeds before the burn
            speed_along_before  =   _getSpeedAlong(getOrbitalSpeed(_apogee), _inclination);
            speed_cross_before  =   _getSpeedCross(getOrbitalSpeed(_apogee), _inclination);

            //Changing the orbit parameters after the burn
            _inclination        =   new_inclination;

            //Calculating the speeds after the burn
            speed_along_next    =   _getSpeedAlong(getOrbitalSpeed(_apogee), _inclination);
            speed_cross_next    =   _getSpeedCross(getOrbitalSpeed(_apogee), _inclination);

            //Calculating the speed change
            delta_v_change      =   sqrt(
                    pow((speed_along_next - speed_along_before), 2) + pow((speed_cross_next - speed_cross_before), 2));

        } else {
            //Program must end if the inclination change is not happening at perigee or at apogee
            cout << "ERROR! Wrong usage of inclination change." << endl;
            exit(EXIT_FAILURE);
        }
    }

    //Saving the aggregate speed change
    _total_delta_v_change   +=  delta_v_change;
    return delta_v_change;
}
//Returns the speed along the reference frame
double Orbit::_getSpeedAlong(double const & speed, double const & inclination) const {
    return speed * cos((inclination/180)*M_PI);
}
//Returns the speed across the reference frame
double Orbit::_getSpeedCross(double const & speed, double const & inclination) const {
    return speed * sin((inclination/180)*M_PI);
}
