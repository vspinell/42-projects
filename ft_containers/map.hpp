/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneri <gneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:41:56 by fulloa-s          #+#    #+#             */
/*   Updated: 2022/02/07 12:35:05 by gneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef MAP_H
# define MAP_H

#include <functional>
#include <map>
#include <memory>
#include <iomanip>
#include "map_iterator.h"
#include "utils.hpp"
#include "vector.hpp"

namespace ft
{
    template<class pair> //---> riceve gia la coppia (ft::pair(key, mapped value))
    struct Node
    {
        // typedef	pair        			value_type;
		typedef Node<pair>*				node_pointer;
		typedef const Node<pair>*		const_node_pointer;
        node_pointer        			right;
        node_pointer        			left;
        node_pointer					parent;
		int 							empty_int_max_size;
		
		pair							_pair;

        Node() : right(NULL), left(NULL), parent(NULL), _pair(){}; // default

        Node(const pair& x) : right(NULL), left(NULL), parent(NULL), _pair(x){}; // with a pair

		Node(const Node& x) : right(x.right), left(x.left), parent(x.parent), _pair(x._pair){}; // copy
		
		~Node(){};
    };

	template<class value, class compare = std::less<typename value::first_type>, class alloc = std::allocator<value> > // --> value = pair (key, mapped value)
    class tree
    {
        public:
		
			typedef value                                     	value_type; //--> PAIR
			typedef	compare										value_compare; //--> COMPARE TRA KEY -->FIRST ARG, NO PAIR
        	typedef alloc    	     							allocator_type;
			typedef typename std::allocator<Node<value> >		node_allocator; 
			
        	typedef typename node_allocator::reference			node_reference;
        	typedef typename node_allocator::const_reference	const_node_reference;
        	typedef typename node_allocator::pointer			node_pointer;
			typedef typename node_allocator::const_pointer		const_node_pointer;
			
        	typedef size_t           							size_type;
        	typedef ptrdiff_t        							difference_type;
        	typedef typename value::first_type                  first_type;
        	typedef typename value::second_type                 second_type;
			typedef typename vector<node_pointer>::iterator		vec_iterator;
			typedef typename vector<value_type>::iterator		pairvec_iterator;



        private:
		
        	node_allocator										_alloc;
		    node_pointer										root;
			node_pointer										end;
			value_compare										comp;
			size_type											size;
			vector<node_pointer>								node_vec;

		public:
		//----------------------------------------CONSTRUCTOR, DESTRUCTOR-------------------------------------------------//
		
			tree(const value_compare& _compare = value_compare(),  const node_allocator& _a = node_allocator()) : 
				_alloc(_a),
				root(NULL),
				comp(_compare),
				size(0)	{
					
					end = _alloc.allocate(1);
					_alloc.construct(end, Node<value_type>());
					end->right = end;
					end->left = end;
				};
			
			~tree(){
				
				for(size_t i = 0; i < this->size; i++)
				{
					_alloc.destroy((node_vec[i]));
					_alloc.deallocate(node_vec[i], 1);
				}
				_alloc.deallocate(end, 1);
				
			}
			
			node_pointer	get_root() const { return this->root ;}
			node_pointer	get_begin() const {return this->end->right;};
			node_pointer	get_end() const { return this->end ;}
			size_type		get_size() const { return this->size; }
			value_compare  	key_comp() const  { return this->comp; }


			void	ft_erase_vec()
			{
				vector<value_type>	new_node_vec;
				vec_iterator v_beg = node_vec.begin();
				while(v_beg != node_vec.end())
				{
					new_node_vec.push_back(ft::make_pair((*v_beg)->_pair.first, (*v_beg)->_pair.second));
					v_beg++;
				}
				ft_tree_clear();
				pairvec_iterator nv_beg = new_node_vec.begin();
				while(nv_beg != new_node_vec.end())
				{
					tree_insert((*nv_beg));
					nv_beg++;
				}
			}

			void erase (node_pointer node)
			{
				vec_iterator v_beg = node_vec.begin();
				while(v_beg != node_vec.end())
				{
					if(*v_beg == node)
					{
						_alloc.destroy((*v_beg));
						_alloc.deallocate(*v_beg, 1);
						node_vec.erase(v_beg);
						size--;
						ft_erase_vec();
						return;
					}
					v_beg++;
				}	
			}

			void erase (node_pointer first, node_pointer second )
			{
				vector<node_pointer>	new_node_vec;
				size_t len = 0;
				while(first != second)
				{
					new_node_vec.push_back(first);
					first = next_node(first);
					len++;
				}
				vec_iterator st = new_node_vec.begin();
				// vec_iterator end = new_node_vec.end();
				vec_iterator v_beg = node_vec.begin();
				// vec_iterator v_end = node_vec.end();
				while(len)
				{
					if(*v_beg == *st)
					{
						st++;
						_alloc.destroy((*v_beg));
						_alloc.deallocate(*v_beg, 1);
						node_vec.erase(v_beg);
						size--;
						len--;
					}
					if(v_beg == node_vec.end())
						v_beg = node_vec.begin();
					else
						v_beg++;
					}
			
				ft_erase_vec();
				// vec_iterator v_beg(first);
				// vec_iterator v_end(second);
				// // while(v_beg != v_end)
				// {
				// 	if(*v_beg == node)
				// 	{
				// 		_alloc.destroy((*v_beg));
				// 		_alloc.deallocate(*v_beg, 1);
				// 		node_vec.erase(v_beg);
				// 		size--;
				// 		ft_erase_vec();
				// 		return;
				// 	}
				// 	v_beg++;
				// }	
			}
		
			void ft_tree_clear()
			{
				vec_iterator v_beg = node_vec.begin();
				vec_iterator v_end = node_vec.end();
				for(size_t i = 0; i < this->size; i++)
				{
					_alloc.destroy((node_vec[i]));
					_alloc.deallocate(node_vec[i], 1);
				}
				node_vec.erase(v_beg, v_end);
				this->size = 0;
				root = NULL;
				end->right = end;
				end->left = end;
				end->parent = NULL;
				
			}

			void swap(tree& x)
			{
				std::swap(this->_alloc, x._alloc);
				std::swap(root, x.root);
				std::swap(end, x.end);
				std::swap(comp, x.comp);
				std::swap(size, x.size);
				std::swap(node_vec, x.node_vec);
			}

			pair<node_pointer, bool> tree_insert (const value_type& val)
			{
				node_pointer	tmp;
				if (root == NULL)
				{
					this->root = _alloc.allocate(1);
					node_vec.push_back(root);
					_alloc.construct(root, val);
					this->end->left = root;
					this->end->right = root;
					this->root->parent = end;
					this->root->right = end;
					this->root->left = end;
					tmp = root;
					this->size++;
				}
				else if (this->comp(val.first, end->right->_pair.first) || 
						!(this->comp(val.first, end->left->_pair.first)) || 
						(val.first == end->right->_pair.first))
				{
					// std::cout << "entrato con:" << val.first << std::endl;
					if (val.first == end->right->_pair.first)
						return (ft::make_pair(end->right, false));
					else if (val.first == end->left->_pair.first)
						return (ft::make_pair(end->left, false));
					tmp = _alloc.allocate(1);
					node_vec.push_back(tmp);
					_alloc.construct(tmp, val);
					if (this->comp(val.first, end->right->_pair.first))
					{
						end->right->left = tmp;
						tmp->parent = end->right;
						end->right = tmp;
						tmp->left = end;
					}
					else if (!(this->comp(val.first, end->left->_pair.first)))
					{
						end->left->right = tmp;
						tmp->parent = end->left;
						end->left = tmp;
						tmp->right = end;
					}
					this->size++;
				}
				else
				{
					node_pointer	ptr = this->root;
					while (1)
					{
						if (ptr->left && this->comp(val.first, ptr->_pair.first))
							ptr = ptr->left;
						else if (ptr->right && !this->comp(val.first, ptr->_pair.first))
							ptr = ptr->right;
						if (val.first == ptr->_pair.first)
							return (ft::make_pair(ptr, false));
						if (!ptr->left && this->comp(val.first, ptr->_pair.first))
						{
							tmp = _alloc.allocate(1);
							_alloc.construct(tmp, val);
							tmp->parent = ptr;
							ptr->left  = tmp;
							break ;
						}
						else if (!this->comp(val.first, ptr->_pair.first) && !ptr->right)
						{
							tmp = _alloc.allocate(1);
							_alloc.construct(tmp, val);
							tmp->parent = ptr;
							ptr->right  = tmp;
							break ;
						}
					}
						node_vec.push_back(tmp);
						this->size++;
				}
				return (ft::make_pair(tmp, true));
			}

			node_pointer	find(const first_type& k) const
			{
				if (k == end->right->_pair.first) //--> = piu piccolo
					return node_pointer(end->right);
				else if (k == end->left->_pair.first) // --> = piu grande
					return node_pointer(end->left);
				node_pointer tmp = this->root;
				if (k == tmp->_pair.first) // --> = root
					return tmp;
				if (this->comp(k, tmp->_pair.first)) //--> se minore
				{
					while (tmp != end->right)
					{
						if (k == tmp->_pair.first)
							return tmp;
						tmp = prev_node(tmp);
					}
				}
				else
				{
					while (tmp != end->left)
					{
						if (k == tmp->_pair.first)
							return tmp;
						tmp = next_node(tmp);
					}
				}
				return node_pointer(end);
			}

			size_type count(const first_type& k) const
			{
				node_pointer tmp = find(k);
				if (tmp != end)
					return 1;
				return 0;
			}

			bool empty() const
			{
				return (this->size == 0? 1 : 0);
			}

			size_type tree_max_size() const{

				return this->_alloc.max_size();
			}

			node_pointer	lower_bound(const first_type& k) const
			{
				for (node_pointer tmp = get_begin(); tmp != get_end(); tmp = next_node(tmp))
				{
					if (this->comp(k, tmp->_pair.first) || k == tmp->_pair.first)
						return node_pointer(tmp);
				}
				return node_pointer(get_end());
			}

			node_pointer	upper_bound(const first_type& k) const
			{
				for (node_pointer tmp = get_begin(); tmp != get_end(); tmp = next_node(tmp))
					if (this->comp(k, tmp->_pair.first))
						return node_pointer(tmp);
				return node_pointer(get_end());
			}

			pair<node_pointer, node_pointer>	equal_range(const first_type& k) const
			{
				return pair<node_pointer , node_pointer>(lower_bound(k), upper_bound(k));
			}

    };

    template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
		
        	typedef Key                                      				key_type;
        	typedef T                                        				mapped_type;
        	typedef pair<const key_type, mapped_type>        				value_type;
        	typedef Compare                                  				key_compare;
        	typedef Allocator                                				allocator_type;
        	typedef typename allocator_type::reference       				reference;
        	typedef typename allocator_type::const_reference 				const_reference;
        	typedef typename allocator_type::pointer         				pointer;
        	typedef typename allocator_type::const_pointer   				const_pointer;
        	typedef typename allocator_type::size_type       				size_type;
        	typedef typename allocator_type::difference_type 				difference_type;

     	class value_compare
     	: public std::binary_function<value_type, value_type, bool>
     	{
     		friend class map<Key, T, key_compare, Allocator>;
     	 	protected:
     		key_compare 				comp;

     		value_compare(key_compare __c) : comp(__c) {}

    		public:
     		bool operator()(const value_type& __x, const value_type& __y) const
     		{ return comp(__x.first, __y.first); }
       };
		
		public:
			
			typedef ft::tree<value_type, key_compare, allocator_type>			_tree; //--> definiton of TREE
			
        	typedef typename ft::map_iterator<_tree>							iterator;
			typedef typename ft::const_map_iterator<_tree>						const_iterator;
			typedef typename ft::map_reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::const_map_reverse_iterator<const_iterator>		const_reverse_iterator;

        private:
		
			allocator_type											_alloc;
        	key_compare                                  			compare;
			_tree   												tree;

		public:
		
		//----------------------------------------CONSTRUCTORS , DESTRUCTOR--------------------------------------------------------------------------//
		
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :  _alloc(alloc), compare(comp) {};
			
			template <class InputIterator>
  			map (InputIterator first, InputIterator last,
			  	const key_compare& comp = key_compare(), 
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) : _alloc(alloc), compare(comp) {

					while(first != last)
					{
						insert(*first);
						first++;
					}	
				}
			map (const map& x) : _alloc(x._alloc), compare(x.compare) {

				const_iterator tmp = x.begin();
				while(tmp != x.end())
				{
					insert(*tmp);
					tmp++;
				}
			}
			
			~map(){};
		
		//---------------------------------------OPERATORS OVERLOADING--------------------------------------//

			map& operator= (const map& x){

				this->_alloc = x._alloc;
				this->compare = x.compare;
				tree.ft_tree_clear();
				const_iterator tmp = x.begin();
				while(tmp != x.end())
				{
					insert(*tmp);
					tmp++;
				}
				return *this;
			}
		
		//----------------------------------------ITERATORS-------------------------------------------------//
		
		iterator end() { return iterator(tree.get_end()) ;}
		iterator begin() { return iterator(tree.get_end()->right); }
		const_iterator end() const { return const_iterator(tree.get_end()); }
		const_iterator begin() const { return const_iterator(tree.get_end()->right); }
		size_type size() const { return this->tree.get_size(); }
		
		reverse_iterator rbegin() { return reverse_iterator(tree.get_end()->left); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(tree.get_end()->left); }
		reverse_iterator rend() { return reverse_iterator (tree.get_end()); }
		const_reverse_iterator rend() const { return const_reverse_iterator (tree.get_end()); }
		
		//------------------------------------------METHODS-------------------------------------------------//
		
		size_type erase (const key_type& k)
		{
			iterator it = find(k);
			if (it == end())
				return 0;
			tree.erase(it.base());
			return 1;
		}

		void erase (iterator position)
		{
			tree.erase(position.base());
		}

		void erase (iterator first, iterator last)
		{
			tree.erase(first.base(), last.base());
		}
		
		value_compare value_comp() const
		{
			return value_compare(this->compare);
		}
		
		key_compare key_comp() const
		{
			return key_compare();
		}

		void swap (map& x)
		{
			std::swap(this->_alloc, x._alloc);
			std::swap(this->compare, x.compare);
			tree.swap(x.tree);
		}

		pair<iterator, bool> insert (const value_type& val)
		{
			pair<typename _tree::node_pointer, bool> inserted = tree.tree_insert(val);
			iterator iter(inserted.first);
			return (ft::make_pair(iter, inserted.second));
		}
		
		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			iterator ret(tree.tree_insert(val).first);
			return ret;
		}
		
		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last)
		{
			for (; first != last; first++)
			{
				value_type val = ft::make_pair(first->first, first->second);
				tree.tree_insert(val);
			}
		}

		void clear(){

			tree.ft_tree_clear();
		}

		iterator find(const key_type& k)
		{
			return iterator(tree.find(k));
		}

		const_iterator find(const key_type& k) const
		{
			return const_iterator(tree.find(k));
		}

		size_type count(const key_type& k) const
		{
			return tree.count(k);
		}

		bool empty() const
		{
			return tree.empty();
		}

		iterator lower_bound(const key_type& k)
		{
			return iterator(tree.lower_bound(k));
		}

		const_iterator lower_bound (const key_type& k) const
		{
			return const_iterator(tree.lower_bound(k));
		}

		iterator	upper_bound(const key_type& k)
		{
			return iterator(tree.upper_bound(k));
		}

		const_iterator upper_bound (const key_type& k) const
		{
			return const_iterator(tree.upper_bound(k));
		}

		pair<iterator,iterator>	equal_range (const key_type& k)
		{
			return tree.equal_range(k);
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return tree.equal_range(k);
		}
		
		size_type max_size() const
		{
			return(tree.tree_max_size());
		}

		mapped_type& operator[] (const key_type& k)
		{
			return((insert(ft::make_pair(k,mapped_type())).first)->second);
		}

    };
	//----------------------------------------RELATIONAL OPERATORS-------------------------------------------------//

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator< (const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
    	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator==(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
   		return x.size() == y.size() && !(x<y) && !(y<x);
	}


	template <class Key, class T, class Compare, class Allocator>
	bool
	operator!=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
   		return !(x == y);
	}		

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator> (const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
		return (y < x);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator>=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
		return !(x < y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool
	operator<=(const map<Key, T, Compare, Allocator>& x, const map<Key, T, Compare, Allocator>& y)
	{
		return !(y < x);
	}

}

#endif