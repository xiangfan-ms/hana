/*!
@file
Forward declares `boost::hana::replicate`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPLICATE_HPP
#define BOOST_HANA_FWD_REPLICATE_HPP

#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Create a monadic structure by combining a lifted value with itself
    //! `n` times.
    //! @relates MonadPlus
    //!
    //! Given a value `x`, a non-negative number `n` and the tag of a monadic
    //! structure `M`, `replicate` creates a new monadic structure which is
    //! the result of combining `x` with itself `n` times inside the monadic
    //! structure. In other words, `replicate` simply `lift`s `x` into the
    //! monadic structure, and then combines that with itself `n` times:
    //! @code
    //!     replicate<M>(x, n) == cycle(lift<M>(x), n)
    //! @endcode
    //!
    //! If `n` is zero, then the identity of the `concat` operation is returned.
    //! In the case of sequences, this corresponds to creating a new sequence
    //! holding `n` copies of `x`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Constant `C` and MonadPlus `M`, the signature is
    //! @f$ \mathtt{replicate}_M : T \times C \to M(T) @f$.
    //!
    //! @tparam M
    //! The tag of the returned monadic structure. It must be a
    //! model of the MonadPlus concept.
    //!
    //! @param x
    //! The value to lift into a monadic structure and then combine with
    //! itself.
    //!
    //! @param n
    //! A non-negative `Constant` of an unsigned integral type representing
    //! the number of times to combine `lift<M>(x)` with itself. If `n == 0`,
    //! then `replicate` returns `empty<M>()`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/replicate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto replicate = [](auto&& x, auto&& n) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct replicate_impl : replicate_impl<M, when<true>> { };

    template <typename M>
    struct replicate_t;

    template <typename M>
    constexpr replicate_t<M> replicate{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_REPLICATE_HPP