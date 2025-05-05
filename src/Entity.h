#pragma once
#include "Registry.h"

#include <random>

namespace ShooterTrainer {

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
