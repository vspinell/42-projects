/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneri <gneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:48:58 by fulloa-s          #+#    #+#             */
/*   Updated: 2022/02/07 12:11:46 by gneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef STACK_H
# define STACK_H

#include "vector.hpp"

namespace ft
{
    template<typename _Tp, typename Container = ft::vector<_Tp> >
    class stack
    {
        public:
            typedef typename Container::value_type                value_type;
            typedef typename Container::reference                 reference;
            typedef typename Container::const_reference           const_reference;
            typedef typename Container::size_type                 size_type;
            typedef          Container                            container_type;
		
        protected:
		
        	Container	cont;

         public:
        // XXX removed old def ctor, added def arg to this one to match 14882
        /**
         *  @brief  Default constructor creates no elements.
         */
        explicit	stack(const Container& __c = Container()) : cont(__c) {}
        /**
         *  Returns true if the %stack is empty.
         */
        bool	empty() const { return cont.empty(); }
    
        /**  Returns the number of elements in the %stack.  */
        size_type	size() const { return cont.size(); }
    
        /**
         *  Returns a read/write reference to the data at the first
         *  element of the %stack.
         */
        reference	top() { return cont.back();}
    
        /**
         *  Returns a read-only (constant) reference to the data at the first
         *  element of the %stack.
         */
        const_reference	top() const { return cont.back(); }
    
        /**
         *  @brief  Add data to the top of the %stack.
         *  @param  x  Data to be added.
         *
         *  This is a typical %stack operation.  The function creates an
         *  element at the top of the %stack and assigns the given data
         *  to it.  The time complexity of the operation depends on the
         *  underlying sequence.
         */
        void	push(const value_type& __x) { cont.push_back(__x); }
        /**
         *  @brief  Removes first element.
         *
         *  This is a typical %stack operation.  It shrinks the %stack
         *  by one.  The time complexity of the operation depends on the
         *  underlying sequence.
         *
         *  Note that no data is returned, and if the first element's
         *  data is needed, it should be retrieved before pop() is
         *  called.
         */
        void	pop() { cont.pop_back(); }
        template<typename _Type, typename _Container>
        friend bool operator==(const stack<_Type, _Container>& __x, const stack<_Type, _Container>& __y);

         template<typename _Type, typename _Container>
        friend bool operator<(const stack<_Type, _Container>& __x, const stack<_Type, _Container>& __y);
	
    };
	
    /**
     *  @brief  Stack equality comparison.
     *  @param  x  A %stack.
     *  @param  y  A %stack of the same type as @a x.
     *  @return  True iff the size and elements of the stacks are equal.
         *
         *  This is an equivalence relation.  Complexity and semantics
         *  depend on the underlying sequence type, but the expected rules
         *  are: this relation is linear in the size of the sequences, and
         *  stacks are considered equivalent if their sequences compare
         *  equal.
        */
        template<typename _Type, typename _Container>
        bool operator==(const stack<_Type, _Container>& __x, const stack<_Type, _Container>& __y) { return __x.cont == __y.cont; }
     
        /**
         *  @brief  Stack ordering relation.
         *  @param  x  A %stack.
         *  @param  y  A %stack of the same type as @a x.
         *  @return  True iff @a x is lexicographically less than @a y.
         *
         *  This is an total ordering relation.  Complexity and semantics
         *  depend on the underlying sequence type, but the expected rules
         *  are: this relation is linear in the size of the sequences, the
         *  elements must be comparable with @c <, and
         *  std::lexicographical_compare() is usually used to make the
         *  determination.
        */
        template<typename _Type, typename _Container>
        bool operator<(const stack<_Type, _Container>& __x, const stack<_Type, _Container>& __y) { return __x.cont < __y.cont; }
     
        /// Based on operator==
        template<typename _Type, typename _Container>
        bool operator!=(const stack<_Type, _Container>& __x, const stack<_Type, _Container>& __y) { return !(__x == __y); }
     
        /// Based on operator<
        template<typename _Type, typename _Container>
        bool operator>(const stack<_Type, _Container>& __x, const stack<_Type, _Container>& __y) { return __y < __x; }
     
        /// Based on operator<
        template<typename _Type, typename _Container>
        bool operator<=(const stack<_Type, _Container>& __x, const stack<_Type, _Container>& __y) { return !(__y < __x); }
     
        /// Based on operator<
        template<typename _Type, typename _Container>
        bool operator>=(const stack<_Type, _Container>& __x, const stack<_Type, _Container>& __y) { return !(__x < __y); }
}

#endif
