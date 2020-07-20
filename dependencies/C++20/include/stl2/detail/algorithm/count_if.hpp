// cmcstl2 - A concept-enabled C++ standard library
//
//  Copyright Casey Carter 2015
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/caseycarter/cmcstl2
//
#ifndef STL2_DETAIL_ALGORITHM_COUNT_IF_HPP
#define STL2_DETAIL_ALGORITHM_COUNT_IF_HPP

#include <stl2/detail/concepts/callable.hpp>
#include <stl2/detail/range/concepts.hpp>

///////////////////////////////////////////////////////////////////////////
// count_if [alg.count]
//
STL2_OPEN_NAMESPACE {
	struct __count_if_fn : private __niebloid {
		template<input_iterator I, sentinel_for<I> S, class Proj = identity,
			indirect_unary_predicate<projected<I, Proj>> Pred>
		constexpr iter_difference_t<I>
		operator()(I first, S last, Pred pred, Proj proj = {}) const {
			auto n = iter_difference_t<I>{0};
			for (; first != last; ++first) {
				if (__stl2::invoke(pred, __stl2::invoke(proj, *first))) {
					++n;
				}
			}
			return n;
		}

		template<input_range R, class Proj = identity,
			indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
		constexpr iter_difference_t<iterator_t<R>>
		operator()(R&& r, Pred pred, Proj proj = {}) const {
			return (*this)(begin(r), end(r), __stl2::ref(pred), __stl2::ref(proj));
		}
	};

	inline constexpr __count_if_fn count_if{};
} STL2_CLOSE_NAMESPACE

#endif