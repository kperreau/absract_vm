/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactoryOperand.class.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 19:44:25 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/25 20:28:25 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FactoryOperand.class.hpp"
#include "Operand.class.hpp"

FactoryOperand::FactoryOperand(void)
{
	this->create[Int8] = &FactoryOperand::createInt8;
	this->create[Int16] = &FactoryOperand::createInt16;
	this->create[Int32] = &FactoryOperand::createInt32;
	this->create[Float] = &FactoryOperand::createFloat;
	this->create[Double] = &FactoryOperand::createDouble;
	return ;
}

FactoryOperand::FactoryOperand(FactoryOperand const & src)
{
	this->create[Int8] = &FactoryOperand::createInt8;
	this->create[Int16] = &FactoryOperand::createInt16;
	this->create[Int32] = &FactoryOperand::createInt32;
	this->create[Float] = &FactoryOperand::createFloat;
	this->create[Double] = &FactoryOperand::createDouble;
	return ;
}

FactoryOperand const & FactoryOperand::operator=(FactoryOperand const & rhs)
{
	return (*this);
}

IOperand const * FactoryOperand::createOperand(eOperandType type, std::string const & value) const
{
	return((*this->create[type])(value));
}

FactoryOperand::~FactoryOperand(void)
{
	return ;
}

IOperand const * FactoryOperand::createInt8(std::string const & value) const
{
	return (new Operand<char>(Int8, value));
}

IOperand const * FactoryOperand::createInt16(std::string const & value) const
{
	return (new Operand<short int>(Int16, value));
}

IOperand const * FactoryOperand::createInt32(std::string const & value) const
{
	return (new Operand<int>(Int32, value));
}

IOperand const * FactoryOperand::createFloat(std::string const & value) const
{
	return (new Operand<float>(Float, value));
}

IOperand const * FactoryOperand::createDouble(std::string const & value) const
{
	return (new Operand<double>(Double, value));
}
