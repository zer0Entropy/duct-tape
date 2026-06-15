//
// Created by dgmuller on 6/15/26.
//

#ifndef DUCT_TAPE_INIT_HPP
#define DUCT_TAPE_INIT_HPP

namespace DuctTape {
    struct NeedsToBeInitialized {
        NeedsToBeInitialized() = default;
        virtual ~NeedsToBeInitialized() = 0;
        virtual void Init() = 0;
    };
}

#endif //DUCT_TAPE_INIT_HPP
