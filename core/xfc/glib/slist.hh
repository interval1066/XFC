#ifndef XFC_SLIST_HH
#define XFC_SLIST_HH

#include <list>

#ifndef __G_SLIST_H__
#include <glib/gslist.h>
#endif

namespace Xfc {
namespace G {

    /**
        Template version of glib GSList, holding only a subset of functions
        that can be contained inside a glist. The template has all of the short
        commings of the underlaying GSList, and adds only type safty and
        some simple conversions.
        
        Also note that the list holds a pointer to the elements inside the
        list and that these pointers are unmaintained and unreferenced.

        The template are ment as a thin wrapper to be able to handle listed
        handed over by the underlaying GTK layer as cheap as possible.

        This class in NOT thread safe.
    */
    template<class T> class SList {
        GSList *_list;
    public:
        class iterator {
            GSList *_cur;
        public:
            iterator( SList<T> &base ) : _cur( base._list ) {}

            void operator++() {
                _cur = g_slist_next( _cur );
            }

            operator T * () { return _cur->data; }
        };
        
        SList() {
            _list = g_slist_alloc();
        }

        // Please note that this is not typesafe, so you need to know what you are doing
        SList( GSList *orig ) {
            _list = orig;
        }
        
        ~SList() { g_slist_free( _list ); }

        iterator begin() const {
            return iterator( _list );
        }

        iterator end() const {
            return iterator( g_slist_last( _list ));
        }

        // The same as push_back in STL
        void append( T *data ) {
            _list = g_slist_append( _list, data );
        }
        
        void prepend( T *data ) {
            _list = g_list_prepend( _list, data );
        }
        
        void insert( T* data, size_t position) {
            _list = g_slist_insert( _list, data, position );
        }
        
        void remove( const T *data ) {
            _list = g_slist_remove( _list, data );
        }
        
        void remove_all( const T *data) {
            _list = g_slist_remove_all( _list, data );
        }

        size_t length() const {
            return g_slist_length( _list );
        }
        
        SList<T> copy() const {
            return SList<T>( g_slist_copy( _list ));
        }
        
        SList<T> reverse() const {
            return SList<T>( g_slist_reverse( _list ));
        }
        
        void concat( SList<T> &list ) {
            _list = g_slist_concat( _list, list._list );
        }
            
        T* nth_data(size_t n) {
            return g_slist_nth_data( _list, n );
        }

        size_t index( const T *data ) const {
            return g_slist_index( _list, data );
        }

        /**
            Convert to the nearest STL container, but only on demand.
            This is a full copy, and perform as that !
        */
        operator std::list<T *> &() const {
            std::list< T* > l;
            
            for( iterator i = begin(); i != end(); ++i )
                l.push_back( *i );
                
            return l;
        }

        friend class iterator;
    };
}
}

#endif
