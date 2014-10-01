#ifndef REGISTRY_H
#define REGISTRY_H

#include "../utilities.hpp"

namespace spam {

class Registry {
    public:
        int r[32];
        Registry();
        int store(int reg, int val);
        int load (int reg);
};

}

#endif
