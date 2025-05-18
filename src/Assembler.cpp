#include <iostream>

#include "Framework.h"

// For testing things quickly
#include "Entity.h"

using namespace ShooterTrainer::Framework;


int main() {
    Framework application;

    if(!application.setup())
        return 1;
    
    application.run();

    return 0;
}


/*
int main() {
    using namespace ShooterTrainer;

    Entity fuck;

    std::cout << "UUID: " << fuck.getUUID() << "\n";

    bool test1 { true };
    std::string test2 { "test text" };

    fuck.addComponent(test1);
    fuck.addComponent(test2);

    std::cout << "Reg Size: " << fuck.getRegistrySize() << "\n";

    fuck.removeComponent(test1);

    std::cout << "Reg Size Again: " << fuck.getRegistrySize() << "\n";

    auto ref = fuck.getComponent(test2);

    std::cout << "Text 1: " << ref << "\n";

    ref = "new text";

    auto& ref2 = fuck.getComponent(std::string {});

    std::cout << "Text 2: " << ref2 << "\n";


    return 0;
}
*/
