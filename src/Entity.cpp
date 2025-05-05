#include "Entity.h"


namespace ShooterTrainer{

static std::random_device RANDOM_DEVICE;
static std::mt19937_64 RANDOM_ENGINE(RANDOM_DEVICE());
static std::uniform_int_distribution<uint64_t> UNIFORM_DISTRIBUTION;

UUID::UUID() : id { UNIFORM_DISTRIBUTION(RANDOM_ENGINE) }{

}
UUID::UUID(uint64_t setID) : id { setID } {

}
UUID::~UUID(){

}
UUID::operator uint64_t() const {
    return id;
}
    
Entity::Entity() : id { UUID { } } {

}
Entity::Entity(UUID setID) : id { setID }{

}
Entity::~Entity(){

}
UUID Entity::getUUID() const {
    return id;
}
std::size_t Entity::getRegistrySize() const {
    return registry.getSize();
}

}
