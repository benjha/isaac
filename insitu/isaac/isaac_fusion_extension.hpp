/* This file is part of ISAAC.
 *
 * ISAAC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * ISAAC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Lesser Public
 * License along with ISAAC.  If not, see <www.gnu.org/licenses/>. */

#pragma once

#include <boost/fusion/container/list.hpp>
#include <boost/fusion/include/list.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>
#include <boost/fusion/include/list_fwd.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/mpl/size.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

namespace isaac
{

template<int N>
struct isaac_for_each_unrolled_2_params
{
	template<typename I0, typename F, typename P1, typename P2>
	static void call(I0 const& i0, F const& f, P1& p1, P2& p2)
	{
		f(*i0,p1,p2);
		isaac_for_each_unrolled_2_params<N-1>::call(boost::fusion::next(i0), f, p1, p2);
	}
};

template<>
struct isaac_for_each_unrolled_2_params<0>
{
	template<typename It, typename F, typename P1, typename P2>
	static void call(It const&, F const&, P1& p1, P2& p2)
	{
	}
};

template <typename Sequence, typename F,typename P1,typename P2>
inline void isaac_for_each_2_params(Sequence& seq, F const& f, P1& p1, P2& p2)
{
	typedef typename boost::fusion::result_of::begin<Sequence>::type begin;
	typedef typename boost::fusion::result_of::end<Sequence>::type end;
	isaac_for_each_unrolled_2_params
	<
		boost::fusion::result_of::distance<begin, end>::type::value
	>::call(boost::fusion::begin(seq), f, p1, p2);
}

template <typename Sequence, typename F,typename P1>
inline void isaac_for_each_1_params(Sequence& seq, F const& f, P1& p1)
{
	int i = 0;
	isaac_for_each_2_params<Sequence,F,P1,int>(seq,f,p1,i);
}


} //namespace isaac;
