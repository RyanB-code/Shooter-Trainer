#include <Registry.h>


using namespace ShooterTrainer;

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



