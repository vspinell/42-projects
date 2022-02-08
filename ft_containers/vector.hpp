/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneri <gneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 08:49:08 by fulloa-s          #+#    #+#             */
/*   Updated: 2022/02/07 12:07:16 by gneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef VECTOR_H
# define VECTOR_H

#include <iostream>
#include <string>
#include <exception>
#include <limits.h>
#include "iterator.hpp"
#include <algorithm>

#include "utils.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:

		    typedef T                                      			    value_type;
		    typedef Allocator                               		    allocator_type;
		    typedef typename allocator_type::reference&				    reference;
		    typedef typename allocator_type::const_reference&           const_reference;
		    typedef typename allocator_type::size_type                  size_type;
		    typedef typename allocator_type::difference_type            difference_type;
   		    typedef typename allocator_type::pointer                    pointer;
		    typedef typename allocator_type::const_pointer              const_pointer;
    
		    typedef ft::normal_iterator<pointer>                        iterator;
		    typedef ft::normal_iterator<const_pointer>                  const_iterator;
		    typedef ft::reverse_iterator<const_iterator>	            const_reverse_iterator;
		    typedef ft::reverse_iterator<iterator>		                reverse_iterator;
		
		private:

		    allocator_type                                              _alloc;
		    size_type                                                   _size;
		    size_type                                                   _capacity;
		    pointer                                                     _begin;
		
		/******************************** COSTRUCTORS ********************************/
		public:
	
		    explicit vector (const allocator_type& alloc = allocator_type()) : 
		    				_alloc(alloc), 
		    				_size(0), 
		    				_capacity(0), 
		    				_begin(NULL)
		    				{}
		    explicit vector (size_type n, const value_type& val = value_type(), 
		    				const allocator_type& alloc = allocator_type()) : 
		    				_alloc(alloc), 
		    				_size(n), 
		    				_capacity(0), 
		    				_begin(NULL)
		    {
		    	if (n > 0) // CONTROLLO
		    	{
		    		_capacity = _size * 2;
		    		_begin = _alloc.allocate(_capacity);
		    		for(size_type i = 0; i < _size; i++)
		    			_alloc.construct(&_begin[i], val);
		    	}
		    }
    
		    template <class InputIterator>
		    vector (InputIterator first, InputIterator last, 
		    		const allocator_type& alloc = allocator_type(), 
		    		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) : 
		    		_alloc(alloc), 
		    		_size(0), 
		    		_capacity(0), 
		    		_begin(NULL) 
		    {
		    	InputIterator tmp = first;
		    	while(tmp++ != last)
		    		_size++;
    
		    	_capacity = _size * 2;
		    	_begin = _alloc.allocate(_capacity);
		    	for(size_type i = 0; i < _size; i++)
		    		_alloc.construct(&_begin[i], *first++);
		    }
    
		    vector (const vector& x) : 
		    		_alloc(x._alloc), 
		    		_size(x._size), 
		    		_capacity(x._capacity), 
		    		_begin(NULL) 
		    {
		    	_begin = _alloc.allocate(_capacity);
		    	for(size_type i = 0; i < _size; i++)
		    		_alloc.construct(&_begin[i], x._begin[i]);
    
		    }

		/***********************************DESTRUCTOR*************************************/

		~vector(){

			if(_begin != NULL)
			{
				for(size_t i = 0; i < _size; i++)
					_alloc.destroy(&_begin[i]); 

				_alloc.deallocate(_begin, _capacity);
			}
		}
		
		/***********************************ITERATOR****************************************/

		iterator begin() { return iterator(this->_begin);}
		const_iterator begin() const { return const_iterator(this->_begin);}
		iterator end() { return iterator(this->_begin + this->_size); }
		const_iterator end() const { return const_iterator(this->_begin + this->_size); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
 
        /********************************OPERATOR OVERLOADING********************************/
        
        vector& operator= (const vector& x){

            if(this != &x)
            {
                if(_begin != NULL)
                {
                    for(size_t i = 0; i < _size; i++)
                        _alloc.destroy(&_begin[i]); 
                    _alloc.deallocate(_begin, _capacity);
                }
                this->_size = x._size;
                this->_capacity = x._capacity;
                _begin = _alloc.allocate(_capacity);
                for(size_type i = 0; i < _size; i++)
                    _alloc.construct(&_begin[i], x._begin[i]);
            }
            return(*this);
        }

        /********************************  ELEMENT ACCESS  ********************************/

        /**
         *  Returns a reference to the element at position n in the vector.
         *  The function "vector::at" automatically checks whether n is within the bounds of valid elements in the vector,
         *  throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size). 
         *  This is in contrast with member operator[], that does not check against bounds.
         *  
         */
        reference operator[]( size_type pos )
        { 
            return (this->_begin[pos]);
        }

        reference at(size_type n)
        {
            if(n > this->_size || this->_begin == NULL)
                throw std::out_of_range("std::out_of_range");
            return (this->_begin[n]);
        }

        const_reference at(size_type n) const
        {
            if(n > this->_size || this->_begin == NULL)
                throw std::out_of_range("std::out_of_range");
            return (this->_begin[n]);
        }
        //Returns a reference to the first element in the vector.
        //Calling these functions on an empty container causes undefined behavior.
        reference front()
        {
            return *begin();
        }
        
        const_reference front() const
        {
            return *begin();
        }
        //Returns a reference to the last element in the vector.
        reference back()
        {
            return *(end() - 1); 
        }
        const_reference back() const
        {
            return *(end() - 1);
        }

        /********************************  CAPACITY ********************************/

        void    reserve(size_type n)
        {
            if (n > this->_capacity)
            {
                pointer tmp = this->_alloc.allocate(n);
                for (size_type i = 0; i < this->_size; i++)
                {
                    _alloc.construct(&tmp[i], _begin[i]);
                    _alloc.destroy(&_begin[i]);
                }
                _alloc.deallocate(_begin, _capacity);
                this->_capacity = n;
                _begin = tmp;
            }
        }
        
        void    resize(size_type n, value_type val = value_type())
        {
            size_type tmp = n;
            while (tmp < this->_size)
                _alloc.destroy(&_begin[tmp++]);
            while (n > this->_size)
                push_back(val);
            this->_size = n;
        }
        
        size_type   size() const { return this->_size ;}
        size_type   max_size() const { return this->_alloc.max_size();}
        size_type   capacity() const {return this->_capacity ;}
        bool        empty() const { return this->begin() == this->end() ;}
        
        //------------------------------MODIFIERS-------------------------------------//
        
        void    assign(size_type n, const value_type& val)
        {
            clear();
            insert(this->begin(), n, val);
        }
        
        template <class InputIterator>
        void    assign(InputIterator first, InputIterator last) //da testare
        {
            clear();
            insert (begin(), first, last);
        }
        
        template <class InputIterator>
        void    insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
        {
            for (; first != last; first++)
                   position = insert(position, *first) + 1; //questo  insert ritorna la posizione all'elemento cambiato quindi aggiungiamo una posizione in modo da cambiare la position e aggiungere davanti al prossimo elemento(successivo a quello nuovo appena aggiunto)
        }
        
        iterator    insert(iterator position, const value_type& val)
        {
            int i = 0;
            while(begin() != position--)
                i++;
                
            if (this->_size + 1 > this->_capacity)
                reserve(this->_capacity < 2 ? 2 : this->_capacity * 2);
            for (iterator tmp = end(); tmp != begin() + i; tmp--)
                *tmp = *(tmp - 1);
            _begin[i] = val;
            this->_size++;
            return begin() + i;
        }
        
        void    insert(iterator position, size_type n, const value_type& val)
        {
            int i = 0;
            while(begin() != position--)
                i++;
            while (this->_size + n > this->_capacity)
                reserve(this->_capacity < 2 ? 2 : this->_capacity * 2);
            for (iterator tmp = end() - 1 + n; tmp != begin() + i + n - 1; tmp--)
                *tmp = *(tmp - n);
            for (iterator tmp = begin() + i; tmp < begin() + i + n; tmp++)
                *tmp = val;
            this->_size += n;
        }
    
        void    clear()
        {
            if (!empty())
            {
                for (iterator i = this->begin(); i < this->end(); i++)
                    this->_alloc.destroy(&(*i));
                this->_size = 0;
            }
        }
        
        iterator    erase(iterator position)
        {
            _alloc.destroy(&(*position));
            for (iterator tmp = position; tmp < end(); tmp++)
                *tmp = *(tmp + 1);
            this->_size--;
            return  position;
        }
        
        iterator    erase(iterator first, iterator last)
        {
            for (iterator tmp = first; tmp != last; tmp++)
                erase(first);
            return first;
        }

        void    push_back(const value_type& val)
        {
            if (this->_size + 1 > this->_capacity)
                reserve(this->_capacity < 2 ? 2 : this->_capacity * 2);
            this->_alloc.construct(this->_begin + this->_size++, val);
        }
        
        void    pop_back()
        {
            _alloc.destroy(&_begin[--this->_size]);
        }
        
        void    swap(vector& x)
        {
			std::swap(this->_alloc, x._alloc);
			std::swap(this->_begin, x._begin);
			std::swap(this->_size, x._size);
			std::swap(this->_capacity, x._capacity);
		}

	};

	// Vectors are considered equivalent if their sizes are equal, and if corresponding elements compare equal.

    //----------------------------------------RELATIONAL OPERATORS-------------------------------------------------//
    
	template<typename _Tp, typename _Alloc>
	bool    operator==(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{ return (__x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin())); }

	template<typename _Tp, typename _Alloc>
	bool    operator<(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{ return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end()); }

	template<typename _Tp, typename _Alloc>
	bool    operator!=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{ return !(__x == __y); }
 
	/// Based on operator<
	template<typename _Tp, typename _Alloc>
	bool    operator>(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{ return __y < __x; }
 
	/// Based on operator<
	template<typename _Tp, typename _Alloc>
	bool    operator<=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{ return !(__y < __x); }
 
	/// Based on operator<
	template<typename _Tp, typename _Alloc>
	bool    operator>=(const vector<_Tp, _Alloc>& __x, const vector<_Tp, _Alloc>& __y)
	{ return !(__x < __y); }
	
	template<typename _Tp, typename _Alloc>
	void    swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y)
	{ __x.swap(__y); }
}

#endif