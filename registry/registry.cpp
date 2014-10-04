#include "registry.hpp"

spam::Registry::Registry() {
    for(int x = 0; x < 32; x++) {
        r[x] = 0;
    }
}
int spam::Registry::store(int reg, int val) {
    int tmp = r[reg];
    r[reg] = val;
    std::cout << "Received " << val << ", register " << reg << " is set to " << r[reg] << std::endl;
    return ((val == r[reg]) ? SUCCESS : FAIL);
}
int spam::Registry::load(int reg){
    return r[reg];
}
