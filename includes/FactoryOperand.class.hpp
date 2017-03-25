/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FactoryOperand.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:20:23 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/25 20:18:22 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_OPERAND_CLASS_HPP
# define FACTORY_OPERAND_CLASS_HPP
# include <iostream>
# include <map>
# include "IOperand.class.hpp"

class FactoryOperand
{
	public:
		FactoryOperand(void);
		FactoryOperand(FactoryOperand const & src);
		FactoryOperand const & operator=(FactoryOperand const & rhs);
		IOperand const * createOperand(eOperandType type, std::string const & value) const;
		~FactoryOperand(void);
		
	private:
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;
		
		std::map<eOperandType, IOperand const * (FactoryOperand::*)(std::string const & value) const> create;
};

std::ostream &		operator<<(std::ostream & o, FactoryOperand const & i);

#endif
