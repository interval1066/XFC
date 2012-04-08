/**
   @file xfc/cairo/context.hh
   @brief A Cairo Context C++ wrapper interface.
   
   Provides Context, an object that stores global information used 
   to control the drawing on a cairo surface.
*/

#ifndef __XFC_CAIRO_CONTEXT__
#define __XFC_CAIRO_CONTEXT__ 1

#include <xfc/cairo/types.hh>
#include <xfc/cairo/pattern.hh>
#include <xfc/pango/layout.hh>

#include <string>

namespace Xfc {
    namespace Cairo {

        enum Content {
            CONTENT_COLOR = CAIRO_CONTENT_COLOR,
            CONTENT_ALPHA = CAIRO_CONTENT_ALPHA,
            CONTENT_COLOR_ALPHA = CAIRO_CONTENT_COLOR_ALPHA
        };
    }
}

#include <xfc/cairo/surface.hh>

namespace Xfc {
    namespace Cairo {

        enum FillRule {
            FILL_RULE_WINDING  = CAIRO_FILL_RULE_WINDING,
            FILL_RULE_EVEN_ODD = CAIRO_FILL_RULE_EVEN_ODD
        };

        enum LineCap {
            LINE_CAP_BUTT   = CAIRO_LINE_CAP_BUTT,
            LINE_CAP_ROUND  = CAIRO_LINE_CAP_ROUND,
            LINE_CAP_SQUARE = CAIRO_LINE_CAP_SQUARE
        };
        
        enum LineJoin {
            LINE_JOIN_MITER = CAIRO_LINE_JOIN_MITER,
            LINE_JOIN_ROUND = CAIRO_LINE_JOIN_ROUND,
            LINE_JOIN_BEVEL = CAIRO_LINE_JOIN_BEVEL
        };

        enum Operator {
            OPERATOR_CLEAR     = CAIRO_OPERATOR_CLEAR,

            OPERATOR_SOURCE    = CAIRO_OPERATOR_SOURCE,
            OPERATOR_OVER      = CAIRO_OPERATOR_OVER,
            OPERATOR_IN        = CAIRO_OPERATOR_IN,
            OPERATOR_OUT       = CAIRO_OPERATOR_OUT,
            OPERATOR_ATOP      = CAIRO_OPERATOR_ATOP,

            OPERATOR_DEST      = CAIRO_OPERATOR_DEST,
            OPERATOR_DEST_OVER = CAIRO_OPERATOR_DEST_OVER,
            OPERATOR_DEST_IN   = CAIRO_OPERATOR_DEST_IN,
            OPERATOR_DEST_OUT  = CAIRO_OPERATOR_DEST_OUT,
            OPERATOR_DEST_ATOP = CAIRO_OPERATOR_DEST_ATOP,

            OPERATOR_XOR       = CAIRO_OPERATOR_XOR,
            OPERATOR_ADD       = CAIRO_OPERATOR_ADD,
            OPERATOR_SATURATE  = CAIRO_OPERATOR_SATURATE
        };

        /// Has its own ref counter internaly and are not using G::Object !
        class Context {
            cairo_t *m_cr;
        public:
            /// Construct a new Context from an existing cairo_t.
            /// @param ctx A pointer to a cairo_t.
            ///
            /// The <EM>context</EM> can be a newly created cairo_t or an existing
            /// CairoContext.
            explicit Context( cairo_t *ctx );

            Context( Surface &surface );

            Context( const Context & );

            ~Context();

            /**
               Checks whether an error has previously occurred for this context.

               @return the current status of this context
               @see Status
             */
            Status status();

            /**
               Makes a copy of the current state of context and saves it on an internal 
               stack of saved states for context. When restore() is called, context will 
               be restored to the saved state. Multiple calls to cairo_save() and 
               restore() can be nested; each call to restore() restores 
               the state from the matching paired save().

               It isn't necessary to clear all saved states before a Context is freed. 
             */
            void save();

            /**
               Restores context to the state saved by a preceding call to save() and 
               removes that state from the stack of saved states.
            */
            void restore();

            /**
               Gets the target surface for the cairo context as passed when this object 
               is constructed.

               This function will always return a valid pointer, but the result can be a 
               "nil" surface if cr is already in an error state, 
               (ie. status() != STATUS_SUCCESS). A nil surface is indicated by 
               surface_status() != STATUS_SUCCESS.

               @returns: the target surface.
            */
            Surface get_target();

            /**
               This group functionality can be convenient for performing intermediate 
               compositing. One common use of a group is to render objects as opaque 
               within the group, (so that they occlude each other), and then blend the 
               result with translucence onto the destination.

               Groups can be nested arbitrarily deep by making balanced calls to 
               push_group()/pop_group(). Each call pushes/pops the new 
               target group onto/from a stack.

               The push_group() function calls save() so that any changes 
               to the graphics state will not be visible outside the group, (the pop_group 
               functions call restore()).

               By default the intermediate group will have a content type of 
               CONTENT_COLOR_ALPHA. Other content types can be chosen for the group 
               by using push_group_with_content() instead. 
            */
            void push_group();

            /**
               Temporarily redirects drawing to an intermediate surface known as a 
               group. The redirection lasts until the group is completed by a call 
               to pop_group() or pop_group_to_source(). These calls provide 
               the result of any drawing to the group as a pattern, (either as an 
               explicit object, or set as the source pattern).

               The group will have a content type of content. The ability to control 
               this content type is the only distinction between this function and 
               push_group() which you should see for a more detailed description 
               of group rendering.

               @param content : A Content indicating the type of group that will be created 
             */
            void push_group_with_content( Content content );

            /**
               Terminates the redirection begun by a call to push_group() or 
               push_group_with_content() and returns a new pattern containing 
               the results of all drawing operations performed to the group.

               The pop_group() function calls restore(), (balancing a call to 
               save() by the push_group function), so that any changes to 
               the graphics state will not be visible outside the group.

               @return a newly created (surface) pattern containing the results 
               of all drawing operations performed to the group. The caller owns 
               the returned object and should call pattern_destroy() when finished 
               with it.
            */
            Pattern pop_group();

            /**
               Terminates the redirection begun by a call to push_group() or 
               push_group_with_content() and installs the resulting pattern 
               as the source pattern in the given cairo context.
             */
            void pop_group_to_source();

            /**
               Gets the target surface for the current group as started by the 
               most recent call to push_group() or group_with_content().

               This function will return NULL if called "outside" of any group 
               rendering blocks, (that is, after the last balancing call to pop_group() 
               or pop_group_to_source()).

               @returns the target group surface.
             */
            Surface get_group_target();

            /**
               Sets the source pattern within cr to an opaque color. This opaque color
               will then be used for any subsequent drawing operation until a new source
               pattern is set.

               The color components are floating point numbers in the range 0 to 1. If
               the values passed in are outside that range, they will be clamped.

               @param red red component of color
               @param green green component of color
               @param blue blue component of color
            */
            void set_source_rgb( double red, double green, double blue);

            /**
                Sets the source pattern within cr to a translucent color. This color will
                then be used for any subsequent drawing operation until a new source
                pattern is set.

                The color and alpha components are floating point numbers in the
                range 0 to 1. If the values passed in are outside that range, they will be clamped.

                @param red red component of color
                @param green green component of color
                @param blue blue component of color
                @param alpha alpha component of color
             */
            void set_source_rgba( double red, double green, double blue, double alpha);

            /**
                Sets the source pattern within cr to source. This pattern will then be used
                for any subsequent drawing operation until a new source pattern is set.

                Note: The pattern's transformation matrix will be locked to the user space
                in effect at the time of set_source(). This means that further
                modifications of the current transformation matrix will not affect the
                source pattern. 

                @param source a cairo_pattern_t to be used as the source for subsequent drawing operations.
                
                @see Pattern::set_matrix().
             */
            void set_source( Pattern &pattern );

            /**
                This is a convenience function for creating a pattern from surface and setting
                it as the source in cr with set_source().

                The x and y parameters give the user-space coordinate at which the surface origin
                should appear. (The surface origin is its upper-left corner before any transformation
                has been applied.) The x and y patterns are negated and then set as translation
                values in the pattern matrix.

                Other than the initial translation pattern matrix, as described above, all other
                pattern attributes, (such as its extend mode), are set to the default values. The
                resulting pattern can be queried with get_source() so that these attributes can
                be modified if desired, (eg. to create a repeating pattern with Pattern::set_extend()).

                @param surface a surface to be used to set the source pattern
                @param x User-space X coordinate for surface origin
                @param y User-space Y coordinate for surface origin
             */
            void set_source_surface( Surface &surface, double x, double y);

            /**
                Gets the current source pattern.

                @return the current source pattern.
            */
            Pattern get_source();

            /**
                Set the antialiasing mode of the rasterizer used for drawing shapes.
                This value is a hint, and a particular backend may or may not support
                a particular value. At the current time, no backend supports
                ANTIALIAS_SUBPIXEL when drawing shapes.

                Note that this option does not affect text rendering, instead
                see FontOptions::set_antialias().

                @param antialias the new antialiasing mode 
             */
            void set_antialias( Antialias antialias);

            /**
                Gets the current shape antialiasing mode, as set by set_shape_antialias().

                @return the current shape antialiasing mode.
            */
            Antialias get_antialias();

            /**
                Sets the dash pattern to be used by cairo_stroke(). A dash pattern is
                specified by dashes, an array of positive values. Each value provides
                the length of alternate "on" and "off" portions of the stroke. The offset
                specifies an offset into the pattern at which the stroke begins.

                Each "on" segment will have caps applied as if the segment were a separate
                sub-path. In particular, it is valid to use an "on" length of 0.0 with
                LINE_CAP_ROUND or LINE_CAP_SQUARE in order to distributed dots or squares along a path.

                Note: The length values are in user-space units as evaluated at the time of stroking.
                This is not necessarily the same as the user space at the time of set_dash().

                If num_dashes is 0 dashing is disabled.

                If num_dashes is 1 a symmetric pattern is assumed with alternating on and off portions
                of the size specified by the single value in dashes.

                If any value in dashes is negative, or if all values are 0, then cr will be put into
                an error state with a status of #STATUS_INVALID_DASH.

                @param dashes an array specifying alternate lengths of on and off stroke portions
                @param num_dashes the length of the dashes array
                @param offset an offset into the dash pattern at which the stroke should start
             */
            void set_dash( const double *dashes, int num_dashes, double offset);

            /**
                Set the current fill rule within the cairo context. The fill rule is used to
                determine which regions are inside or outside a complex (potentially
                self-intersecting) path. The current fill rule affects both fill() and clip().
                See fillrule for details on the semantics of each available fill rule.

                @param fill_rule a fill rule, specified as a FillRule
            */
            void set_fill_rule( FillRule fill_rule );

            /**
                Gets the current fill rule, as set by set_fill_rule().

                @return the current fill rule.
            */         
            FillRule get_fill_rule();

            /**
                Sets the current line cap style within the cairo context. See LineCap
                for details about how the available line cap styles are drawn.

                As with the other stroke parameters, the current line cap style is examined
                by stroke(), stroke_extents(), and stroke_to_path(), but does not have
                any effect during path construction.
                
                @param line_cap a line cap style
            */         
            void set_line_cap( LineCap line_cap);

            /**
                Gets the current line cap style, as set by set_line_cap().

                @return the current line cap style.
            */            
            LineCap get_line_cap();

            /**
                Sets the current line join style within the cairo context. See LineJoin for
                details about how the available line join styles are drawn.

                As with the other stroke parameters, the current line join style is examined
                by stroke(), stroke_extents(), and stroke_to_path(), but does not have any
                effect during path construction.

                @param line_join a line joint style
            */         
            void set_line_join( LineJoin line_join);
            
            /**
                Gets the current line join style, as set by set_line_join().
                @return the current line join style. 
            */         
            LineJoin get_line_join();


            
            void set_line_width( double width );
            double get_line_width();
            void set_miter_limit( double limit );
            double get_miter_limit();
            void set_operator( Operator op);
            Operator get_operator();
            void set_tolerance( double tolerance );
            double get_tolerance();
            void clip();
            void clip_preserve();
            void reset_clip();
            void fill();
            void fill_preserve();
            void fill_extents( double *x1, double *y1, double *x2, double *y2);
            bool in_fill( double x, double y);
            void mask( Pattern &pattern);
            void mask_surface ( Surface &surface, double surface_x, double surface_y);
            void paint();
            void paint_with_alpha(double alpha);
            void stroke();
            void stroke_preserve();
            void stroke_extents( double *x1, double *y1, double *x2, double *y2);
            bool in_stroke( double x, double y);
            void copy_page();
            void show_page();

            operator cairo_t* () const {return m_cr;}

            // Path interface
            void get_current_point( double *x, double *y );
            void new_path();
            void new_sub_path();
            void close_path();
            void arc( double xc, double yc, double radius, double angle1, double angle2);
            void arc_negative( double xc, double yc, double radius, double angle1, double angle2);
            void curve_to( double x1, double y1, double x2, double y2, double x3, double y3);
            void line_to( double x, double y );
            void move_to( double x, double y);
            void rectangle( double x, double y, double width, double height);
            void text_path( const std::string &utf8 );
            void rel_curve_to( double dx1, double dy1, double dx2, double dy2, double dx3, double dy3);
            void rel_line_to( double dx, double dy);
            void rel_move_to( double dx, double dy);

            // Translation
            void translate( double tx, double ty );
            void scale( double sx, double sy );
            void rotate( double angle );

            // pango integration
            void show_layout( Pango::Layout &layout );
        };
    }
}

#endif
