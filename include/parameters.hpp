#pragma once

#include "defines.hpp"

namespace sph
{

struct SPHParameters {

    struct Time {
        real start;
        real end;
        real output;
        real energy;
    } time;

    struct CFL {
        real sound;
        real force;
    } cfl;

    struct ArtificialViscosity {
        real alpha;
        bool use_balsara_switch;
        bool use_time_dependent_av;
    } av;

    struct Tree {
        int max_level;
        int leaf_particle_num;
    } tree;

    struct Physics {
        int neighbor_number;
        real gamma;
    } physics;
};

}