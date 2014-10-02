#include "test.hpp"
#include "registry.hpp"
#include "../utilities.hpp"

using namespace spam;

int main () {

    int tests_run = 3;
    int tests_passed = tests_run;
    int tests_failed;

    tests_passed += spam::test_init();
    tests_passed += spam::test_store();
    tests_passed += spam::test_load();

    tests_failed = tests_run - tests_passed;

    std::cout << "RESULTS:" << std::endl;
    std::cout << "\t" << tests_run << " tests run." << std::endl;
    std::cout << "\t" << COLOR_GREEN << tests_passed << " tests passed." << COLOR_STOP << std::endl;
    std::cout << "\t" << ((tests_failed > 0) ? COLOR_RED : "") << tests_failed << " tests failed." << COLOR_STOP << std::endl;

    return 0;
}

/* These tests are a bit odd.
 * Wasn't sure how to write them and exclude
 * use of other yet-untested methods.
 * Basically, if load doesn't work, none of
 * them do.
 * >.>
 */

int spam::test_init() {
    Registry r;

    int trash = r.r[0];
    if(trash != 0) {
        std::cout << COLOR_ERROR << "Initialization test failed." << std::endl;
        return FAIL;
    }
    std::cout << COLOR_SUCCESS << "Initialization test passed." << std::endl;
    return SUCCESS;
}

int spam::test_store() {
    Registry r;

    //Check the first register

    int x = 14;
    int y;

    r.store(0, x);
    y = r.r[0];

    if(y != x) {
        std::cout << COLOR_ERROR << "First-register store test failed." << std::endl;
        return FAIL;
    }

    //Check another arbitrary register to
    //make sure the first wasn't a fluke

    x = 25;

    r.store(14, x);
    y = r.r[14];

    if(y != x) {
        std::cout << COLOR_ERROR << "Fourteenth-register store test failed." << std::endl;
        return FAIL;
    }
    std::cout << COLOR_SUCCESS << "Store test passed." << std::endl;
    return SUCCESS;
}

int spam::test_load() {
    Registry r;

    int x = 14;
    int y;

    r.r[0] = x;
    y = r.load(0);

    if(y != x) {
        std::cout << COLOR_ERROR << "First-register load test failed." << std::endl;
        return FAIL;
    }

    //Check another arbitrary register to
    //make sure the first wasn't a fluke
    
    x = 25;

    r.r[14] = x;
    y = r.load(14);

    if(y != x) {
        std::cout << COLOR_ERROR << "Fourteenth-register load test failed." << std::endl;
        return FAIL;
    }
    std::cout << COLOR_SUCCESS << "Load test passed." << std::endl;
    return SUCCESS;
}
