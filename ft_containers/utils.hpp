/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneri <gneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:04:28 by fulloa-s          #+#    #+#             */
/*   Updated: 2022/02/07 12:13:00 by gneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef UTILS_H
# define UTILS_H

#include <string>

namespace ft
{
    /********************************  INTEGRAL CONSTANT  ********************************/
    
    template <class _Tp, _Tp __v>
    struct integral_constant
    {
        static const _Tp      value = __v;
        typedef _Tp               value_type;
        typedef integral_constant type;
        operator value_type() const throw() {return value;}
    };

    typedef integral_constant<bool, true>  true_type;
    typedef integral_constant<bool, false>  false_type;

    /********************************  ENABLE IF  ********************************/

    template <bool, class _Tp = void>
    struct enable_if {};
    template <class _Tp>
    struct enable_if<true, _Tp> {typedef _Tp type;};

    /********************************  IS INTEGRAL  ********************************/
    
    template <class _Tp> struct is_integral                     : public false_type {};
    template <>          struct is_integral<bool>               : public true_type {};
    template <>          struct is_integral<char>               : public true_type {};
    template <>          struct is_integral<signed char>        : public true_type {};
    template <>          struct is_integral<unsigned char>      : public true_type {};
    template <>          struct is_integral<wchar_t>            : public true_type {};
    // template <>          struct is_integral<char16_t>           : public true_type {}; LINUX
    // template <>          struct is_integral<char32_t>           : public true_type {}; LINUX
    template <>          struct is_integral<short>              : public true_type {};
    template <>          struct is_integral<unsigned short>     : public true_type {};
    template <>          struct is_integral<int>                : public true_type {};
    template <>          struct is_integral<unsigned int>       : public true_type {};
    template <>          struct is_integral<long>               : public true_type {};
    template <>          struct is_integral<unsigned long>      : public true_type {};
    template <>          struct is_integral<long long>          : public true_type {};
    template <>          struct is_integral<unsigned long long> : public true_type {};
    template <>          struct is_integral<__int128_t>         : public true_type {};
    template <>          struct is_integral<__uint128_t>        : public true_type {};

    /********************************  EQUAL  ********************************/
    
    template<typename _InputIterator1, typename _InputIterator2>
    bool
    equal(_InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2)
    {
        for (; __first1 != __last1; ++__first1, ++__first2)
            if (!(*__first1 == *__first2))
                return false;
        return true;
    }

    /********************************  LEXICOGRAPHICAL COMPARE  ********************************/

    /**
    * @brief Performs "dictionary" comparison on ranges.
    * 
    * "Returns true if the sequence of elements defined by the range
    *  [first1,last1) is lexicographically less than the sequence of elements
    *  defined by the range [first2,last2).  Returns false otherwise."
    */

    template<typename _InputIterator1, typename _InputIterator2>
    bool
    lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                _InputIterator2 __first2, _InputIterator2 __last2)
    {
        for (; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
        {
            if (*__first1 < *__first2)
                return true;
            if (*__first2 < *__first1)
                return false;
        }
        return (__first1 == __last1 && __first2 != __last2);
    }

    /********************************  PAIR  ********************************/

    template <class _T1, class _T2>
    struct pair
    {
        typedef _T1 first_type;
        typedef _T2 second_type;
    
        first_type      first;
        second_type     second;
    
        pair() : first(), second() {}
    
        pair(_T1 const& __t1, _T2 const& __t2) : first(__t1), second(__t2) {}
    
        template <class _U1, class _U2>
        pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}
    
        pair& operator=(pair const& __p) {
            first = __p.first;
            second = __p.second;
            return *this;
        }
    };

    template <class _T1, class _T2>
    bool operator==(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return __x.first == __y.first && __x.second == __y.second;
    }
    
    template <class _T1, class _T2>
    bool operator!=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return !(__x == __y);
    }
    
    template <class _T1, class _T2>
    bool operator< (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return __x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second);
    }
    
    template <class _T1, class _T2>
    bool operator> (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return __y < __x;
    }
    
    template <class _T1, class _T2>
    bool operator>=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return !(__x < __y);
    }
    
    template <class _T1, class _T2>
    bool operator<=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
    {
        return !(__y < __x);
    }
    
    /********************************  MAKE PAIR  ********************************/

    template <class _T1, class _T2>
    pair<_T1,_T2> make_pair(_T1 __x, _T2 __y)
    {
        return pair<_T1, _T2>(__x, __y);
    }
}

#endif