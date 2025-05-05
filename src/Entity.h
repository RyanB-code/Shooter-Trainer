#pragma once
#include <random>
#include <typeinfo>
#include <any>
#include <unordered_map>
#include <functional>


namespace ShooterTrainer {

    // Entity Registry
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


    // Entity
    class UUID{
    public:
        UUID();
        UUID(uint64_t setId);
        ~UUID();

        operator uint64_t() const;
    private:
        uint64_t id;
    };

    class Entity{
    public:
        Entity();
        Entity(UUID setId);
        virtual ~Entity();

        UUID getUUID() const;

        std::size_t getRegistrySize() const;

        // Registry Interaction
        template<typename T>
        bool addComponent(T v){
            return registry.addComponent(v);
        }
        template<typename T>
        void removeComponent(T v){
            return registry.removeComponent(v);
        }
        template<typename T>
        bool hasComponenet(T v) const {
            return registry.hasComponent(v);
        }
        template<typename T>
        T& getComponent(T v) {
            return registry.getComponent(v);
        }

    private:
        EntityRegistry registry { };
        UUID id;
    }; 
}

namespace std{
    template<>
    struct hash<ShooterTrainer::UUID>{
        std::size_t operator()(const ShooterTrainer::UUID& id) const{
            return std::hash<uint64_t>()((uint64_t) id); 
        }
    };
}
