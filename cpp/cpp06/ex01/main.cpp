/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <vspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:41:21 by vspinell          #+#    #+#             */
/*   Updated: 2021/12/13 12:11:15 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

typedef struct	s_Data
{
	int a;
}				Data;

uintptr_t serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}

int main ()
{
	Data data;
	Data *data_ptr;
	uintptr_t row;

	std::cout << "Initial address of Data*: " << &data << std::endl;
	row = serialize(&data);
	std::cout << "Serialized pointer: " << row << std::endl;
	data_ptr = deserialize(row);
	std::cout << "Deserialized pointer: " << data_ptr << std::endl;
}
