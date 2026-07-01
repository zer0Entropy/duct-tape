//
// Created by dgmuller on 6/15/26.
//

#ifndef DUCT_TAPE_SHUTDOWN_HPP
#define DUCT_TAPE_SHUTDOWN_HPP

namespace DuctTape {
    struct NeedsToBeShutdown {
        bool shutdown;

        NeedsToBeShutdown(): shutdown{false} {}

        virtual ~NeedsToBeShutdown() = default;

        virtual void Shutdown() = 0;

        bool IsShutdown() const {
            return shutdown;
        }
    };
}

#endif //DUCT_TAPE_SHUTDOWN_HPP
