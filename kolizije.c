#include "kolizije.h"

void provera_sudara(void) {
    int i;
    for (i = 0;i < MAX_PREPREKA; i++) {
        if (prepreke[i].tip == RUPA) {
            float u;
            for (u = 0; u <= 2*PI+EPSILON; u += PI/20) {
                float x_rupe = 0.5 * cos(u) + prepreke[i].info.rupa.x;
                float z_rupe = -0.5 * sin(u) + prepreke[i].info.rupa.z;
                float x_kolca = tr_x;
                float z_kolca = 4;
                if (x_rupe >= x_kolca-0.375 && x_rupe <= x_kolca+0.375 && z_rupe >= z_kolca-0.7 && z_rupe <= z_kolca+0.5) {
                    if (sudar_u_toku)
                        return;
                    else
                        helti -= 5;
                    sudar_u_toku = 1;
                    return;
                }
            }
        } else if (prepreke[i].tip == RAMPA) {
            if (prepreke[i].info.rampa.velicina == 0.5) {
                float z_rampe = prepreke[i].info.rampa.z;
                float x_rampe1 = prepreke[i].info.rampa.x - 0.5;
                float x_rampe2 = prepreke[i].info.rampa.x + 0.5;
                float x_kolca = tr_x;
                if ((x_rampe1 >= x_kolca-0.375 && x_rampe1 <= x_kolca+0.375 && z_rampe >= 3.2) || (x_rampe2 >= x_kolca-0.375 && x_rampe2 <= x_kolca+0.375 && z_rampe >= 3.2)) {
                    if (sudar_u_toku)
                        return;
                    else
                        helti -= 10;
                    sudar_u_toku = 1;
                    return;
                }
            } else {
                float z_rampe = prepreke[i].info.rampa.z;
                float x_rampe1 = prepreke[i].info.rampa.x - 1;
                float x_rampe2 = prepreke[i].info.rampa.x + 1;
                float x_rampe3 = prepreke[i].info.rampa.x - 0.4;
                float x_rampe4 = prepreke[i].info.rampa.x + 0.4;
                float x_kolca = tr_x;
                if ((x_rampe1 >= x_kolca-0.375 && x_rampe1 <= x_kolca+0.375 && z_rampe >= 3.2) || (x_rampe2 >= x_kolca-0.375 && x_rampe2 <= x_kolca+0.375 && z_rampe >= 3.2)
                 || (x_rampe3 >= x_kolca-0.375 && x_rampe3 <= x_kolca+0.375 && z_rampe >= 3.2) || (x_rampe4 >= x_kolca-0.375 && x_rampe4 <= x_kolca+0.375 && z_rampe >= 3.2)) {
                    if (sudar_u_toku)
                        return;
                    else
                        helti -= 10;
                    sudar_u_toku = 1;
                    return;
                 }
            }
        }
    }
    sudar_u_toku = 0;
}