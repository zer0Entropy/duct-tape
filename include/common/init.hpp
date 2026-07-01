//
// Created by dgmuller on 6/15/26.
//

#ifndef DUCT_TAPE_INIT_HPP
#define DUCT_TAPE_INIT_HPP

namespace DuctTape {
    struct NeedsToBeInitialized {
        bool initialized;

        NeedsToBeInitialized(): initialized{false} {}

        virtual ~NeedsToBeInitialized() = default;

        virtual void Init() = 0;

        bool IsInitialized() const {
            return initialized;
        }
    };
}

#endif //DUCT_TAPE_INIT_HPP
