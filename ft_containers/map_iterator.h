/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneri <gneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:15:46 by fulloa-s          #+#    #+#             */
/*   Updated: 2022/02/07 12:19:04 by gneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef MAP_ITERATOR_H
#   define MAP_ITERATOR_H

#include "map_algo.hpp"
#include "iterator.hpp"

namespace ft
{
	//--------------------------------------------MAP ITERATOR--------------------------------------------------//
	template<typename tree>
	class map_iterator
	: public ft::iterator<ft::bidirectional_iterator_tag, typename tree::node_pointer>
	{

		public:

			typedef typename tree::node_pointer                     node_pointer;
			typedef typename tree::node_reference                   node_reference;
			typedef typename tree::value_type&                      pair_ref;
			typedef typename tree::value_type*                      pair_ptr;

		protected:
			node_pointer                                                   current;
		

		public:
		 //----------------------------------------CONSTRUCTORS-------------------------------------------------//
		
			map_iterator() : current(NULL){}; // default
			
			map_iterator(const node_pointer __i) {this->current = __i;}; // with node pointer
			
			map_iterator(const map_iterator& __i) {this->current = __i.base();}; // copy
			
			const  node_pointer& base() const { return current; };
			
			map_iterator& operator=(const  map_iterator& u) { current = u.base(); return *this; };
			
		//----------------------------------------OPERATORS OVERLOADING-----------------------------------------//
		
			pair_ref operator*() const 
			{
				return  current->_pair; 
			}
			pair_ptr operator->() const
			{
				return &(operator*());
			}
			map_iterator& operator++()
			{
				current = next_node(current);
				return *this;
			}
			map_iterator operator++(int) 
			{ 
				map_iterator tmp(current);
				current = next_node(current);
				return(tmp);
			};
			map_iterator& operator--()
			{
				current = prev_node(current);
				return *this;
			}
			map_iterator operator--(int) 
			{ 	
				map_iterator tmp(current);
				current = prev_node(current);
				return (tmp); 
			};
			bool operator==(const node_pointer& __rhs)
			{ return base() == __rhs; };
			bool operator!=(const node_pointer& __rhs)
			{ return base() != __rhs; };
		
	};
	//----------------------------------------RELATIONAL OPERATORS----------------------------------------------//
	
	template<typename _IteratorL, typename _IteratorR>
	bool operator==(const map_iterator<_IteratorL>& __lhs, const map_iterator<_IteratorR>& __rhs)
	{ return __lhs.base() == __rhs.base(); };
	template<typename _IteratorL, typename _IteratorR>
	bool operator!=(const map_iterator<_IteratorL>& __lhs, const map_iterator<_IteratorR>& __rhs)
	{ return __lhs.base() != __rhs.base(); };
	
	/******************************** CONST MAP ITERATOR ********************************/
	
	template<typename tree>
	class const_map_iterator
	: public ft::iterator<ft::bidirectional_iterator_tag, typename tree::const_node_pointer>
	{

		public:

			typedef typename tree::const_node_pointer               node_pointer;
			typedef typename tree::const_node_reference             node_reference;
			typedef const typename tree::value_type&                const_pair_ref;
			typedef const typename tree::value_type*                const_pair_ptr;

		protected:
		
			node_pointer                                                   current;

		public:
		//----------------------------------------CONSTRUCTORS-------------------------------------------------//
		
			const_map_iterator() : current(NULL){}; //default
			
			const_map_iterator(const node_pointer __i) {this->current = __i;}; // with node pointer

			const_map_iterator(const const_map_iterator& __i) {this->current = __i.base();}; // copy

			const_map_iterator(const map_iterator<tree> & __i) {this->current = __i.base();}; //copy with map classic map iterator
			
			const  node_pointer& base() const { return current; };
			
			const_map_iterator& operator=(const  const_map_iterator& u) { current = u.base(); return *this; };
			
		//----------------------------------------OPERATORS OVERLOADING----------------------------------------//
		
			const_pair_ref operator*() const 
			{
				return  current->_pair; 
			}
			const_pair_ptr operator->() const
			{
				return &(operator*());
			}
			const_map_iterator& operator++()
			{
				current = next_node(current);
				return *this;
			}
			const_map_iterator operator++(int) 
			{ 
				const_map_iterator tmp(current);
				current = next_node(current);
				return(tmp);
			};
			const_map_iterator& operator--()
			{
				current = prev_node(current);
				return *this;
			}
			const_map_iterator operator--(int) 
			{ 	
				const_map_iterator tmp(current);
				current = prev_node(current);
				return (tmp); 
			};
	};
	
	//----------------------------------------RELATIONAL OPERATORS---------------------------------------------//
	
	template<typename _IteratorL, typename _IteratorR>
	bool operator==(const const_map_iterator<_IteratorL>& __lhs, const const_map_iterator<_IteratorR>& __rhs)
	{ return __lhs.base() == __rhs.base(); };
	
	template<typename _IteratorL, typename _IteratorR>
	bool operator==(const const_map_iterator<_IteratorL>& __lhs, const map_iterator<_IteratorR>& __rhs)
	{ return __lhs.base() == __rhs.base(); };

	template<typename _IteratorL, typename _IteratorR>
	bool operator==(const map_iterator<_IteratorL>& __lhs, const const_map_iterator<_IteratorR>& __rhs)
	{ return __lhs.base() == __rhs.base(); };

	template<typename _IteratorL, typename _IteratorR>
	bool operator!=(const const_map_iterator<_IteratorL>& __lhs, const const_map_iterator<_IteratorR>& __rhs)
	{ return __lhs.base() != __rhs.base(); };

	template<typename _IteratorL, typename _IteratorR>
	bool operator!=(const const_map_iterator<_IteratorL>& __lhs, const map_iterator<_IteratorR>& __rhs)
	{ return __lhs.base() != __rhs.base(); };

	template<typename _IteratorL, typename _IteratorR>
	bool operator!=(const map_iterator<_IteratorL>& __lhs, const const_map_iterator<_IteratorR>& __rhs)
	{ return __lhs.base() != __rhs.base(); };

	/******************************** MAP REVERSE ITERATOR ********************************/
	
	template<typename _iterator>
	class map_reverse_iterator
	: public _iterator
	{
		public:
		
			typedef _iterator					                      	 	 iterator_type;
			typedef typename iterator_type::node_pointer                     node_pointer;
			typedef typename iterator_type::node_reference                   node_reference;
			typedef typename iterator_type::value_type&                      pair_ref;
			typedef typename iterator_type::value_type*                      pair_ptr;
			typedef ptrdiff_t        									 	 difference_type;

		public:
		//----------------------------------------CONSTRUCTORS------------------------------------------------//
		
			map_reverse_iterator() : _iterator(NULL) {}; // default constructor

	 		map_reverse_iterator(const node_pointer& __x) : _iterator(__x) {}; // with node pointer

      		map_reverse_iterator(iterator_type __x) : _iterator(__x) { this->current = prev_node(this->current); }; // with iterator

      		map_reverse_iterator(const map_reverse_iterator& __x)  : _iterator(__x.base()) {}; // copy
			  
      		map_reverse_iterator& operator=(const map_reverse_iterator& __x) {  this->current = (__x.current); return *this; };
	
      		iterator_type base() const
			{
				return _iterator(next_node(this->current));
			};

      		//----------------------------------------OPERATORS OVERLOADING------------------------------------//
      
      		map_reverse_iterator& operator++()
	  		{
				this->current = prev_node(this->current); 
				return *this; 
	  		};
      		map_reverse_iterator operator++(int) 
	  		{ 
				map_reverse_iterator __tmp(this->current);
				this->current = prev_node(this->current);; 
				return __tmp; 
	  		};
      		map_reverse_iterator& operator--() 
	  		{ 
				this->current = next_node(this->current);
				return *this; 
	  		};
      		map_reverse_iterator operator--(int) 
	  		{ 
				map_reverse_iterator __tmp(this->current);
				this->current = next_node(this->current);
				return __tmp; 
	  		};
	};
		
	//----------------------------------------RELATIONAL OPERATORS---------------------------------------------//
	
	template<typename _Iterator, typename _Iterator2>
	bool operator==(const map_reverse_iterator<_Iterator>& __x, const map_reverse_iterator<_Iterator2>& __y) 
	{ return __x.base() == __y.base(); };
	template<typename _Iterator, typename _Iterator2>
	bool operator<(const map_reverse_iterator<_Iterator>& __x, const map_reverse_iterator<_Iterator2>& __y) 
	{ return __y.base() < __x.base(); };
	template<typename _Iterator, typename _Iterator2>
	bool operator!=(const map_reverse_iterator<_Iterator>& __x, const map_reverse_iterator<_Iterator2>& __y) 
	{ return !(__x == __y); };
	template<typename _Iterator, typename _Iterator2>
	bool operator>(const map_reverse_iterator<_Iterator>& __x, const map_reverse_iterator<_Iterator2>& __y) 
	{ return __y < __x; };
	template<typename _Iterator, typename _Iterator2>
	bool operator<=(const map_reverse_iterator<_Iterator>& __x, const map_reverse_iterator<_Iterator2>& __y) 
	{ return !(__y < __x); };
	template<typename _Iterator, typename _Iterator2>
	bool operator>=(const map_reverse_iterator<_Iterator>& __x, const map_reverse_iterator<_Iterator2>& __y) 
	{ return !(__x < __y); };

	/******************************** MAP CONST REVERSE ITERATOR ********************************/
	
	template<typename _iterator>
	class const_map_reverse_iterator
	: public _iterator
	{
		public:

			typedef _iterator					                      	 	iterator_type;
			typedef typename iterator_type::node_pointer               		const_node_pointer;
			typedef typename iterator_type::node_reference             		const_node_reference;
			typedef typename iterator_type::value_type&                      const_pair_ref;
			typedef typename iterator_type::value_type*                      const_pair_ptr;
			typedef ptrdiff_t        									 	 difference_type;

		public:
		//----------------------------------------CONSTRUCTORS-------------------------------------------------//
		
			const_map_reverse_iterator() : _iterator(NULL) {}; // default
			
	 		const_map_reverse_iterator(const const_node_pointer& __x) : _iterator(__x) {}; // with node pointer

      		const_map_reverse_iterator(iterator_type __x) : _iterator(__x) {}; // with iterator 

      		const_map_reverse_iterator(const const_map_reverse_iterator& __x)  : _iterator(__x.base()) {}; // copy
			  
      		const_map_reverse_iterator& operator=(const const_map_reverse_iterator& __x) {  this->current = (__x.current); return *this; };
			
      		iterator_type base() const
			{
				return _iterator(next_node(this->current));
			};

      		//----------------------------------------OPERATORS OVERLOADING------------------------------------//
      
      		const_map_reverse_iterator& operator++()
	  		{
				this->current = prev_node(this->current); 
				return *this; 
	  		};
      		const_map_reverse_iterator operator++(int) 
	  		{ 
				const_map_reverse_iterator __tmp(this->current);
				this->current = prev_node(this->current);; 
				return __tmp; 
	  		};
      		const_map_reverse_iterator& operator--() 
	  		{ 
				this->current = next_node(this->current);
				return *this; 
	  		};
      		const_map_reverse_iterator operator--(int) 
	  		{ 
				const_map_reverse_iterator __tmp(this->current);
				this->current = next_node(this->current);
				return __tmp; 
	  		};
	};
	//----------------------------------------RELATIONAL OPERATORS---------------------------------------------//
	
	template<typename _Iterator, typename _Iterator2>
	bool operator==(const const_map_reverse_iterator<_Iterator>& __x, const const_map_reverse_iterator<_Iterator2>& __y) 
	{ return __x.base() == __y.base(); };
	template<typename _Iterator, typename _Iterator2>
	bool operator<(const const_map_reverse_iterator<_Iterator>& __x, const const_map_reverse_iterator<_Iterator2>& __y) 
	{ return __y.base() < __x.base(); };
	template<typename _Iterator, typename _Iterator2>
	bool operator!=(const const_map_reverse_iterator<_Iterator>& __x, const const_map_reverse_iterator<_Iterator2>& __y) 
	{ return !(__x == __y); };
	template<typename _Iterator, typename _Iterator2>
	bool operator>(const const_map_reverse_iterator<_Iterator>& __x, const const_map_reverse_iterator<_Iterator2>& __y) 
	{ return __y < __x; };
	template<typename _Iterator, typename _Iterator2>
	bool operator<=(const const_map_reverse_iterator<_Iterator>& __x, const const_map_reverse_iterator<_Iterator2>& __y) 
	{ return !(__y < __x); };
	template<typename _Iterator, typename _Iterator2>
	bool operator>=(const const_map_reverse_iterator<_Iterator>& __x, const const_map_reverse_iterator<_Iterator2>& __y) 
	{ return !(__x < __y); };
}

#endif