/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneri <gneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:50:32 by francesco         #+#    #+#             */
/*   Updated: 2022/02/07 13:01:51 by gneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef ITERATOR_H
# define ITERATOR_H

#include <cstddef>

namespace ft
{
    /**
   *  These are empty types, used to distinguish different iterators.  The
   *  distinction is not made by what they contain, but simply by what they
   *  are.  Different underlying algorithms can then be used based on the
   *  different operations supported by different iterator types.
    */
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

 
     /**
    *  Common %iterator class.
    *
    *  This class does nothing but define nested typedefs.  %Iterator classes
    *  can inherit from this class to save some work.  The typedefs are then
    *  used in specializations and overloading.
    */

    template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t, 
            typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {
      /// One of the iterator_tags.
      typedef _Category     iterator_category;
      /// The type "pointed to" by the iterator.
      typedef _Tp           value_type;
      /// Distance between iterators is represented as this type.
      typedef _Distance     difference_type;
      /// This type represents a pointer-to-value_type.
      typedef _Pointer      pointer;
      /// This type represents a reference-to-value_type.
      typedef _Reference    reference;
    };

    /**
   *  This class does nothing but define nested typedefs.  The general
   *  version simply @a forwards the nested typedefs from the Iterator
   *  argument.  Specialized versions for pointers and pointers-to-const
   *  provide tighter, more correct semantics.
   */
    
    template<typename _Iterator>
    struct iterator_traits
    {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type        value_type;
      typedef typename _Iterator::difference_type   difference_type;
      typedef typename _Iterator::pointer           pointer;
      typedef typename _Iterator::reference         reference;
    };

    /// Partial specialization for pointer types.
    template<typename _Tp>
    struct iterator_traits<_Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef _Tp*                        pointer;
      typedef _Tp&                        reference;
    };

    /// Partial specialization for const pointer types.
    template<typename _Tp>
    struct iterator_traits<const _Tp*>
    {
      typedef random_access_iterator_tag iterator_category;
      typedef _Tp                         value_type;
      typedef ptrdiff_t                   difference_type;
      typedef const _Tp*                  pointer;
      typedef const _Tp&                  reference;
    };
	
  /************************************       NORMAL ITERATOR       ************************************/

   /**
   *  Iteratore di base, deriva dalla classe iteratore.
   */
  

  template<typename _Iterator>
  class normal_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
		                  typename iterator_traits<_Iterator>::value_type,
		                  typename iterator_traits<_Iterator>::difference_type,
		                  typename iterator_traits<_Iterator>::pointer,
                      typename iterator_traits<_Iterator>::reference>
    {
      
      protected:

    	_Iterator                                         current;
  
        typedef ft::iterator_traits<_Iterator>		        __traits_type;
  
      public:
        typedef _Iterator					                iterator_type;
        typedef typename __traits_type::pointer   	      	pointer;
        typedef typename __traits_type::difference_type 	difference_type;
        typedef typename __traits_type::reference 	      	reference;

         //----------------------------------------CONSTRUCTORS-------------------------------------------------//
		
        normal_iterator() : current(NULL){}; // DEFAULT CONSTRUCTOR
		
        normal_iterator(const _Iterator& __i) : current(__i){}; // CONSTRUCTOR WITH ITERATOR 
		
        const _Iterator& base() const { return current; };
		
        _Iterator& operator=(const _Iterator& u) { current = u.base(); return *this; };
		
        template <class T> normal_iterator(const normal_iterator<T>& u) : current(u.base()) {}
		    template <class T> normal_iterator& operator=(const normal_iterator<T>& u) { current = u.base(); return *this; }

         //----------------------------------------OPERATORS OVERLOADING-------------------------------------------------//

        reference			operator*() const { return *current; };
        pointer				operator->() const  { return current; };
        reference			operator[](difference_type __n) const { return current[__n]; }; 
        normal_iterator&	operator++() { ++current; return *this; };
        normal_iterator		operator++(int) { return normal_iterator(current++); };
        normal_iterator&	operator--() { --current; return *this; };
        normal_iterator		operator--(int) { return normal_iterator(current--); };
        normal_iterator&	operator+=(difference_type __n) { current += __n; return *this; };
        normal_iterator		operator+(difference_type __n) const { return normal_iterator(current + __n); };
        normal_iterator&	operator-=(difference_type __n) { current -= __n; return *this; };
        normal_iterator		operator-(difference_type __n) const { return normal_iterator(current - __n); };

      };

	//----------------------------------------RELATIONAL OPERATORS-------------------------------------------------//
      // Forward iterator requirements
        
      template<typename _IteratorL, typename _IteratorR>
      bool operator==(const normal_iterator<_IteratorL>& __lhs, const normal_iterator<_IteratorR>& __rhs)
      { return __lhs.base() == __rhs.base(); };
      template<typename _IteratorL, typename _IteratorR>
      bool operator!=(const normal_iterator<_IteratorL>& __lhs, const normal_iterator<_IteratorR>& __rhs)
      { return __lhs.base() != __rhs.base(); };
    
      // Random access iterator requirements
      
      template<typename _IteratorL, typename _IteratorR>
      bool operator<(const normal_iterator<_IteratorL>& __lhs, const normal_iterator<_IteratorR>& __rhs)
      { return __lhs.base() < __rhs.base(); };
    
      template<typename _IteratorL, typename _IteratorR>
      bool operator>(const normal_iterator<_IteratorL>& __lhs, const normal_iterator<_IteratorR>& __rhs)
      { return __lhs.base() > __rhs.base(); };
    
      template<typename _IteratorL, typename _IteratorR>
      bool operator<=(const normal_iterator<_IteratorL>& __lhs, const normal_iterator<_IteratorR>& __rhs)
      { return __lhs.base() <= __rhs.base(); };
    
      template<typename _IteratorL, typename _IteratorR>
      bool operator>=(const normal_iterator<_IteratorL>& __lhs, const normal_iterator<_IteratorR>& __rhs)
      { return __lhs.base() >= __rhs.base(); };
      
      template<typename _Iterator, typename _Iterator2>
      typename normal_iterator<_Iterator>::difference_type 
      operator-(const normal_iterator<_Iterator>& __lhs, const normal_iterator<_Iterator2>& __rhs)
      { return __lhs.base() - __rhs.base(); };
      
      template<typename _Iterator>
      normal_iterator<_Iterator>
      operator+(typename normal_iterator<_Iterator>::difference_type __n, const normal_iterator<_Iterator>& __i)
      { return normal_iterator<_Iterator>(__i.base() + __n); };


  /************************************       REVERSE ITERATOR       ***********************************/

  /*
  * Bidirectional and random access iterators have corresponding reverse
  * %iterator adaptors that iterate through the data structure in the
  * opposite direction.  They have the same signatures as the corresponding
  * iterators. A copy of the original iterator (the base iterator) is kept internally 
  * and used to reflect the operations performed on the reverse_iterator:
  * whenever the reverse_iterator is incremented, its base iterator is decreased,
  * and vice versa. A copy of the base iterator with the current state can be 
  * obtained at any time by calling member base.
  */
  
  template<typename _Iterator>
  class reverse_iterator
    : public iterator<typename iterator_traits<_Iterator>::iterator_category,
	                    typename iterator_traits<_Iterator>::value_type,
	                    typename iterator_traits<_Iterator>::difference_type,
	                    typename iterator_traits<_Iterator>::pointer,
                      	typename iterator_traits<_Iterator>::reference>
  {
    protected:
      _Iterator current;

      typedef iterator_traits<_Iterator>		          __traits_type;

    public:
      typedef _Iterator					                iterator_type;
      typedef typename __traits_type::pointer		    pointer;
      typedef typename __traits_type::difference_type	difference_type;
      typedef typename __traits_type::reference		    reference;

       //----------------------------------------CONSTRUCTORS-------------------------------------------------//
       
       reverse_iterator() : current(NULL) {}; // default constructor
      
      /* initalization constructor
      * Constructs a reverse iterator from some original iterator __x. 
      * The behavior of the constructed object replicates the original, 
      * except that it iterates through its pointed elements in the reverse order.
      */
      explicit reverse_iterator(iterator_type __x) : current(__x) {}; // constructor from an iterator
      
      reverse_iterator(const reverse_iterator& __x)  : current(__x.base()) {}; // copy constructor

      /* copy / type-cast constructor
      * Constructs a reverse iterator from some other reverse iterator.
      * The constructed object keeps the same sense of iteration as rev_it.
      */
      
      template<typename _Iter>
      reverse_iterator(const reverse_iterator<_Iter>& __x) : current(__x.base()) {};
      
      iterator_type base() const { return current; };

      template<typename _Iter>
      reverse_iterator& operator=(const reverse_iterator<_Iter>& __x) { current = __x.base(); return *this; };
	  
      //----------------------------------------OPERATORS OVERLOADING-------------------------------------------------//
      
		reference			operator*() const { _Iterator tmp = current; return *--tmp; };
    	pointer				operator->() const  { _Iterator tmp = current; --tmp; return tmp.operator->(); };
    	reverse_iterator&	operator++() { --current; return *this; };
    	reverse_iterator	operator++(int) { reverse_iterator __tmp = *this; --current; return __tmp; };
    	reverse_iterator&	operator--() { ++current; return *this; };
    	reverse_iterator	operator--(int) { reverse_iterator __tmp = *this; ++current; return __tmp; };
    	reverse_iterator	operator+(difference_type __n) const { return reverse_iterator(current - __n); };
    	reverse_iterator&	operator+=(difference_type __n) { current -= __n; return *this; };
    	reverse_iterator	operator-(difference_type __n) const { return reverse_iterator(current + __n); };
    	reverse_iterator&	operator-=(difference_type __n) { current += __n; return *this; };
    	reference			operator[](difference_type __n) const { return *(*this + __n); };

  };

  	//----------------------------------------RELATIONAL OPERATORS-------------------------------------------------//
	   
	template<typename _Iterator, typename _Iterator2>
	bool	operator==(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator2>& __y) 
	{ return __x.base() == __y.base(); };
	
	template<typename _Iterator, typename _Iterator2>
	bool	operator<(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator2>& __y) 
	{ return __y.base() < __x.base(); };
	  
	template<typename _Iterator, typename _Iterator2>
	bool	operator!=(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator2>& __y) 
	{ return !(__x == __y); };
	 
	template<typename _Iterator, typename _Iterator2>
	bool	operator>(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator2>& __y) 
	{ return __y < __x; };
	  
	template<typename _Iterator, typename _Iterator2>
	bool	operator<=(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator2>& __y) 
	{ return !(__y < __x); };

	template<typename _Iterator, typename _Iterator2>
	bool	operator>=(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator2>& __y) 
	{ return !(__x < __y); };
	  
	template<typename _Iterator, typename _Iterator2>
	typename reverse_iterator<_Iterator>::difference_type	operator-(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator2>& __y)
	{ return __y.base() - __x.base(); };
	  
	template<typename _Iterator>
	reverse_iterator<_Iterator>		operator+(typename reverse_iterator<_Iterator>::difference_type __n, const reverse_iterator<_Iterator>& __x)
	{ return reverse_iterator<_Iterator>(__x.base() - __n); };

}

#endif