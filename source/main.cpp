//
// Created by soldato_fantasma aka Soltasto on 22/07/2018.
//

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Orbit.h"

#define BEST_PROFILE_PRECISION 10000 // The higher the better, but requires more time

using namespace std;

int main() {
    int stay;
    do {
        stay=0;
        double perigee, apogee, inclination;
        cout << "Enter Perigee in km, Apogee in km, Inclination in degrees." << endl;
        cin >> perigee >> apogee >> inclination;
        perigee=perigee*1000; //Convert to m
        apogee=apogee*1000;//Convert to m
        Orbit orbit(perigee, apogee,inclination); //Initial orbit creation
        orbit.print(); //Prints current orbit data
        cout << endl;

        if(apogee < GEO_ALT_M) {
            cout << "Sub-sync transfer." << endl << endl;

            double inclination_test = inclination;
            double best_profile = inclination_test, best_delta_v = HUGE_VAL;
            while( inclination_test > 0 ) //Searching the best profile
            {
                Orbit test_orbit(perigee, apogee,inclination);
                test_orbit.apogeeChange(GEO_ALT_M, inclination_test);
                test_orbit.perigeeChange(GEO_ALT_M,0);

                if(test_orbit.getTotalDeltaVChange()<best_delta_v) {
                    best_delta_v = test_orbit.getTotalDeltaVChange();
                    best_profile = inclination_test;
                }
                inclination_test = inclination_test - (inclination/BEST_PROFILE_PRECISION);
            }
            //Increase Apogee altitude to GEO altitude
            orbit.apogeeChange(GEO_ALT_M, best_profile);
            cout << "First maneuver: " << endl;
            cout << setprecision(4) << fixed << "Apogee changed to " << GEO_ALT_KM << "km" << endl;
            cout << setprecision(4) << fixed << "Inclination changed to " << best_profile << " degrees" << endl;
            orbit.print();
            cout << endl;
            //Increase Perigee altitude to GEO altitude and bring inclination to 0
            orbit.perigeeChange(GEO_ALT_M,0);
            cout << "Second maneuver: " << endl;
            cout << setprecision(4) << fixed << "Perigee changed to " << GEO_ALT_KM << "km" << endl;
            cout << setprecision(4) << fixed << "Inclination changed to " << 0 << " degrees" << endl;
            orbit.print();
            cout << endl;
        } else if(apogee == GEO_ALT_M) {
            cout << "Sync transfer." << endl << endl;
            //Increase Aerigee altitude to GEO altitude and bring inclination to 0
            orbit.perigeeChange(GEO_ALT_M,0);
            cout << "First maneuver: " << endl;
            cout << setprecision(4) << fixed << "Perigee changed to " << GEO_ALT_KM << "km" << endl;
            cout << setprecision(4) << fixed << "Inclination changed to " << 0 << " degrees" << endl;
            orbit.print();
            cout << endl;
        } else { //Apogee > GEO_ALT_M
            cout << "Super-sync transfer." << endl << endl;

            double inclination_test = inclination;
            double best_profile = inclination_test, best_delta_v = HUGE_VAL;
            while( inclination_test > 0 ) // Searching the best profile
            {
                Orbit test_orbit(perigee, apogee,inclination);
                test_orbit.perigeeChange(GEO_ALT_M, inclination_test);
                test_orbit.apogeeChange(GEO_ALT_M,0);

                if(test_orbit.getTotalDeltaVChange()<best_delta_v) {
                    best_delta_v = test_orbit.getTotalDeltaVChange();
                    best_profile = inclination_test;
                }
                inclination_test = inclination_test - (inclination/BEST_PROFILE_PRECISION);
            }

            //Now executing the best profile

            orbit.perigeeChange(GEO_ALT_M,best_profile); //Raising the perigee to GEO altitude and clearing most of the inclination
            cout << "First maneuver: " << endl;
            cout << setprecision(4) << fixed << "Perigee changed to " << GEO_ALT_KM << "km" <<endl;
            cout << setprecision(4) << fixed << "Inclination changed to " << best_profile << " degrees" <<endl;
            orbit.print();
            cout << endl;
            orbit.apogeeChange(GEO_ALT_M,0); //Bringing the apogee back to GEO and completing the inclination zeroing
            cout << "Second maneuver: " << endl;
            cout << setprecision(4) << fixed << "Apogee changed to " << GEO_ALT_KM << "km" <<endl;
            cout << setprecision(4) << fixed << "Inclination changed to " << 0 << " degrees" <<endl;
            orbit.print();
            cout << endl;
        }

        cout << setprecision(4) << fixed << "Total delta v to GEO: " << orbit.getTotalDeltaVChange() << " m/s" << endl << endl;

        cout << "Enter 1 to restart or any other key to close." << endl;
        cin >> stay;
        cout << endl << endl << endl;
    }while(stay==1);
    return 0;
}
