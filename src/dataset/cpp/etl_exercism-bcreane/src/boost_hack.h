#include <boost/test/tools/detail/print_helper.hpp>

namespace boost {
    namespace test_tools {
        namespace tt_detail {
            template <class F, class S>
            struct print_log_value< ::std::pair<F, S> > {
                void operator()(::std::ostream & os, ::std::pair<F, S> const & p ) {
                    os << "([" << p.first << "], [" << p.second << "])";
                }
            };
        }
    }

    template<class F, class S> inline
    ::std::ostream & operator<<(::std::ostream & os, ::std::pair<F, S> const & p) {
    os << "([" << p.first << "], [" << p.second << "])";
    return os;
    }
}

