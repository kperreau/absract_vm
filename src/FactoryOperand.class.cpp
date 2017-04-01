/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactoryOperand.class.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 19:44:25 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/25 21:11:40 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FactoryOperand.class.hpp"
#include "Operand.class.hpp"

FactoryOperand::FactoryOperand(void)
{
	this->_create[Int8] = &FactoryOperand::createInt8;
	this->_create[Int16] = &FactoryOperand::createInt16;
	this->_create[Int32] = &FactoryOperand::createInt32;
	this->_create[Float] = &FactoryOperand::createFloat;
	this->_create[Double] = &FactoryOperand::createDouble;
	return ;
}

FactoryOperand::FactoryOperand(FactoryOperand const & src)
{
	*this = src;
	return ;
}

FactoryOperand const & FactoryOperand::operator=(FactoryOperand const & rhs)
{
	return (*this);
}

IOperand const * FactoryOperand::createOperand(eOperandType type, std::string const & value) const
{
	IOperand const *	op = NULL;
	
	try {
		op = (*this.*(_create.at(type)))(value);
	}
	catch (const MyException::overflow_error & e){
		std::cerr << ANSI_COLOR_YELLOW << "Line " << Parser::line << ": Error: " << e.what() << std::endl;
	}
	return (op);
}

FactoryOperand::~FactoryOperand(void)
{
	return ;
}

IOperand const * FactoryOperand::createInt8(std::string const & value) const
{
	return (new Operand<char>(Int8, value, 0, this));
}

IOperand const * FactoryOperand::createInt16(std::string const & value) const
{
	return (new Operand<short int>(Int16, value, 0, this));
}

IOperand const * FactoryOperand::createInt32(std::string const & value) const
{
	return (new Operand<int>(Int32, value, 0, this));
}

IOperand const * FactoryOperand::createFloat(std::string const & value) const
{
	return (new Operand<float>(Float, value, 2, this));
}

IOperand const * FactoryOperand::createDouble(std::string const & value) const
{
	return (new Operand<double>(Double, value, 4, this));
}
