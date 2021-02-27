#ifndef SXE_LOGGING_STDTYPEDEFS__HPP
#define SXE_LOGGING_STDTYPEDEFS__HPP
/*-
 * Copyright (c) 2020-current, Terry Mathew Poulin <BigBoss1964@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *	1. The origin of this software must not be misrepresented; you must
 *	   not claim that you wrote the original software. If you use this
 *	   software in a product, an acknowledgment in the product
 *	   documentation would be appreciated but is not required.
 *
 *	2. Altered source versions must be plainly marked as such, and must
 *	   not be misrepresented as being the original software.
 *
 *	3. This notice may not be removed or altered from any source
 *	   distribution.
 */

#include <sxe/logging/api.hpp>

namespace sxe { namespace logging {

    /** Mix-in for common type definitions.
     *
     *  - normal types for strings and paths.
     */
    template <class Derived>
    class SXELOG_EXPORT stdtypedefs
    {
      public:

        /** Type used for string parameters.
         */
        using string_type = std::string;

#if SXELOG_CXX17
        /** Type used for filesystem path parameters.
         * 
         * Unlike sxe::common::stdtypedefs this does not support using
         * boost::filesystem as a stand in for std::filesystem.
         */
        using path_type = std::filesystem::path;
#endif

        /** unique_ptr's of this type.
         */
        using unique_ptr = std::unique_ptr<Derived>;

        /** shared_ptr's of this type.
         */
        using shared_ptr = std::shared_ptr<Derived>;

        /** weak_ptr's of this type.
         */
        using weak_ptr = std::weak_ptr<Derived>;

    };


} }

#endif // SXE_LOGGING_STDTYPEDEFS__HPP