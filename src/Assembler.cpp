#include <iostream>

#include "Framework.h"

using namespace ShooterTrainer::Framework;

int main() {
    Framework application;

    if(!application.setup())
        return 1;
    
    application.run();

    return 0;
}
