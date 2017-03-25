/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:22:14 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/25 20:34:33 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.class.hpp"
#include "FactoryOperand.class.hpp"

Operand::Operand(void)
{
	std::cout << "Default constructor called." << std::endl;
	
	return ;
}

Operand::Operand(eOperandType type, std::string const & value)
{
	std::cout << "Parameter constructor called." << std::endl;
	
	return ;
}

Operand::Operand(Operand const & src)
{
	std::cout << "Copy constructor called." << std::endl;
	*this = src;
	
	return ;
}

Operand::~Operand(void)
{
	std::cout << "Destructor called." << std::endl;
	
	return ;
}

std::ostream &		operator<<(std::ostream & o, Operand const & i)
{
	
	return (o);
}
