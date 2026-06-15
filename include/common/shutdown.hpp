//
// Created by dgmuller on 6/15/26.
//

#ifndef DUCT_TAPE_SHUTDOWN_HPP
#define DUCT_TAPE_SHUTDOWN_HPP

namespace DuctTape {
    struct NeedsToBeShutdown {
        NeedsToBeShutdown() = default;
        virtual ~NeedsToBeShutdown() = 0;
        virtual void Shutdown() = 0;
    };
}

#endif //DUCT_TAPE_SHUTDOWN_HPP
