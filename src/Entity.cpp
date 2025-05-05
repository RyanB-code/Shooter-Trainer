#include "Entity.h"


namespace ShooterTrainer{

std::size_t EntityTypeHasher::operator()(TypeInfoRef type) const{
    return type.get().hash_code();
}

bool EntityTypeEquivalence::operator()(TypeInfoRef lhs, TypeInfoRef rhs) const{
    return lhs.get() == rhs.get();
}

EntityRegistry::EntityRegistry(){

}
EntityRegistry::~EntityRegistry(){

}
std::size_t EntityRegistry::getSize() const {
    return registry.size();
}

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

} // End namespace ShooterTrainer
