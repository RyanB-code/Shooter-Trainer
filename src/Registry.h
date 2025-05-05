#pragma once

#include <typeinfo>
#include <any>
#include <unordered_map>
#include <functional>


namespace ShooterTrainer {

    using TypeInfoRef = std::reference_wrapper<const std::type_info>;

    struct EntityTypeHasher{
        std::size_t operator()(TypeInfoRef type) const;
    };

    struct EntityTypeEquivalence{
        bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const;
    };

    class EntityRegistry {
    public:
            EntityRegistry();
            ~EntityRegistry();

            template<typename Type>
            bool addComponent(Type object){
                if(registry.contains(typeid(object)))
                    return false;

                return registry.try_emplace(typeid(object), object).second;
            }

            template<typename Type>
            void removeComponent(Type object){
                if(!registry.contains(typeid(object)))
                    return;

                registry.erase(typeid(object));
            }

            template<typename Type>
            bool hasComponent(Type object) const{
                return registry.contains(typeid(object));
            }

            // Throws out_of_range if key not found
            template<typename Type>
            Type& getComponent(Type object) {
                return std::any_cast<Type&>(registry.at(typeid(object)));
            }

            std::size_t getSize() const;

    private:
        std::unordered_map<TypeInfoRef, std::any, EntityTypeHasher, EntityTypeEquivalence> registry { };
    };

}

