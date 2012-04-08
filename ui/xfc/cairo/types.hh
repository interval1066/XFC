/**
   @file xfc/cairo/types.hh
   @brief Cairo types definitions.
   
   Differant types used in this cairo wrapper.
*/

#ifndef __XFC_CAIRO_TYPES__
#define __XFC_CAIRO_TYPES__ 1

#include <cairo.h>
#include <exception>

namespace Xfc {
    namespace Cairo {

        enum Status {
            STATUS_SUCCESS =               CAIRO_STATUS_SUCCESS,
            STATUS_NO_MEMORY =             CAIRO_STATUS_NO_MEMORY,
            STATUS_INVALID_RESTORE =       CAIRO_STATUS_INVALID_RESTORE,
            STATUS_INVALID_POP_GROUP =     CAIRO_STATUS_INVALID_POP_GROUP,
            STATUS_NO_CURRENT_POINT =      CAIRO_STATUS_NO_CURRENT_POINT,
            STATUS_INVALID_MATRIX =        CAIRO_STATUS_INVALID_MATRIX,
            STATUS_INVALID_STATUS =        CAIRO_STATUS_INVALID_STATUS,
            STATUS_NULL_POINTER =          CAIRO_STATUS_NULL_POINTER,
            STATUS_INVALID_STRING =        CAIRO_STATUS_INVALID_STRING,
            STATUS_INVALID_PATH_DATA =     CAIRO_STATUS_INVALID_PATH_DATA,
            STATUS_READ_ERROR =            CAIRO_STATUS_READ_ERROR,
            STATUS_WRITE_ERROR =           CAIRO_STATUS_WRITE_ERROR,
            STATUS_SURFACE_FINISHED =      CAIRO_STATUS_SURFACE_FINISHED,
            STATUS_SURFACE_TYPE_MISMATCH = CAIRO_STATUS_SURFACE_TYPE_MISMATCH,
            STATUS_PATTERN_TYPE_MISMATCH = CAIRO_STATUS_PATTERN_TYPE_MISMATCH,
            STATUS_INVALID_CONTENT =       CAIRO_STATUS_INVALID_CONTENT,
            STATUS_INVALID_FORMAT =        CAIRO_STATUS_INVALID_FORMAT,
            STATUS_INVALID_VISUAL =        CAIRO_STATUS_INVALID_VISUAL,
            STATUS_FILE_NOT_FOUND =        CAIRO_STATUS_FILE_NOT_FOUND,
            STATUS_INVALID_DASH =          CAIRO_STATUS_INVALID_DASH,
            STATUS_INVALID_DSC_COMMENT =   CAIRO_STATUS_INVALID_DSC_COMMENT
        };

        class Exception : public std::exception {
            Status m_status;
        public:
            Exception( Status status ) : m_status( status ) {}

            const char *what() const throw() {
                return cairo_status_to_string( (cairo_status_t)m_status );
            }
        };
    }
}

#endif
