#pragma once

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

};

namespace std{
    template<>
    struct hash<ShooterTrainer::UUID>{
        std::size_t operator()(const ShooterTrainer::UUID& id) const{
            return std::hash<uint64_t>()((uint64_t) id); 
        }
    };
}
