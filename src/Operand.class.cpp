/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:22:14 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/11 20:51:52 by kperreau         ###   ########.fr       */
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

/*Operand const * Operand::createOperand( eOperandType type, std::string const & value )
{
	
	return (NULL);
}

Operand const * Operand::createInt8( std::string const & value )
{
	
	return (NULL);
}

Operand const * Operand::createInt16( std::string const & value )
{
	
	return (NULL);
}

Operand const * Operand::createInt32( std::string const & value )
{
	
	return (NULL);
}

Operand const * Operand::createFloat( std::string const & value )
{
	
	return (NULL);
}

Operand const * Operand::createDouble( std::string const & value )
{
	
	return (NULL);
}*/

std::ostream &		operator<<(std::ostream & o, Operand const & i)
{
	
	return (o);
}
