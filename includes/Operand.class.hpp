/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:22:45 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/11 20:59:12 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP
# include <iostream>
# include <cstdlib>
# include "IOperand.class.hpp"
# include "FactoryOperand.class.hpp"

template <typename T>
class Operand //: public IOperand
{
	public:
		Operand(void){};
		Operand(eOperandType type, std::string const & value){};
		Operand(Operand const & src){};
		~Operand(void){};

		int getPrecision( void ){}; // Precision of the type of the instance

		eOperandType			getType( void ){
			
		}

		IOperand const *		operator+( IOperand const & rhs ){}

		IOperand const *		operator-( IOperand const & rhs ){}

		IOperand const *		operator*( IOperand const & rhs ){}

		IOperand const *		operator/( IOperand const & rhs ){}

		IOperand const *		operator%( IOperand const & rhs ){}

		std::string const &		toString( void ){
		}
		
	private:
		T						_value;
		eOperandType			_type;
		int						_precision;
		const FactoryOperand*	_factory;
		std::string				_str;
};

//std::ostream &		operator<<(std::ostream & o, Operand const & i);

#endif
