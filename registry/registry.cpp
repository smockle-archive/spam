#include "registry.hpp"

spam::Registry::Registry() {
    for(int x = 0; x < 32; x++) {
        r[x] = 0;
    }
}
int spam::Registry::store(int reg, int val) {
    int tmp = r[reg];
    r[reg] = val;
    return ((val == r[reg]) ? SUCCESS : FAIL);
}
int spam::Registry::load(int reg){
    return r[reg];
}
