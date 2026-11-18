/* -----------------------------------------------------------------------------
 * Copyright (c) 2020 Advanced Micro Devices, Inc. All Rights Reserved.
 * See 'LICENSE' in the project root for license information.
 * -------------------------------------------------------------------------- */
#pragma once

#if !defined(__HIP_CPU_RT__)
    #error Private HIP-CPU RT implementation headers must not be included directly.
#endif

#include <dlfcn.h>

#include <string_view>

namespace hip
{
    namespace detail
    {
        // BEGIN CLASS MODULE
        class Module final {
            // DATA
            void* so_;

            // FRIENDS - ACCESSORS
            friend
            inline
            void* address_of(
                const Module& x, std::string_view symbol_name) noexcept
            {
                return x.address_of(symbol_name);
            }
            friend
            inline
            decltype(auto) native_handle(const Module& x) noexcept
            {
                return x.native_handle();
            }
            friend
            inline
            bool valid(const Module& x) noexcept
            {
                return x.valid();
            }
        public:
            using native_handle_type = decltype(so_);

            // CREATORS
            Module() = default;
            explicit
            Module(std::string_view shared_object) noexcept;
            Module(const Module&) = default;
            Module(Module&&) = default;
            ~Module();

            // MANIPULATORS
            Module& operator=(const Module&) = default;
            Module& operator=(Module&&) = default;

            // ACCESSORS
            native_handle_type native_handle() const noexcept;
            void* address_of(std::string_view symbol_name) const noexcept;
            bool valid() const noexcept;
        };

        // CREATORS
        inline
        Module::Module(std::string_view so) noexcept
            : so_{dlopen(std::data(so), RTLD_LAZY)}
        {}

        inline
        Module::~Module()
        {
            if (!so_) return;

            dlclose(so_);
        }

        // ACCESSORS
        inline
        void* Module::address_of(std::string_view s) const noexcept
        {
            return reinterpret_cast<void*>(dlsym(so_, std::data(s)));
        }

        inline
        typename Module::native_handle_type
            Module::native_handle() const noexcept
        {
            return so_;
        }

        inline
        bool Module::valid() const noexcept
        {
            return so_;
        }
        // END CLASS MODULE
    } // Namespace hip::detail.
} // Namespace hip.