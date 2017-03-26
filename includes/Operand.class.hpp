/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:22:45 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/25 19:23:49 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP
# include <iostream>
# include <cstdlib>
# include "IOperand.class.hpp"
# include "FactoryOperand.class.hpp"

template <typename T>
class Operand : public IOperand
{
	public:
		Operand(void){};
		Operand(eOperandType type, std::string const & value) : _type(type)
		{
			if (type == Int8)
				this->_value = static_cast<char>(std::stoi(value));
			else if (type == Int16)
				this->_value = static_cast<short int>(std::stoi(value));
			else if (type == Int32)
				this->_value = static_cast<int>(std::stoi(value));
			else if (type == Float)
				this->_value = static_cast<float>(std::stof(value));
			else
				this->_value = static_cast<double>(std::stod(value));
			this->_str = std::to_string(this->_value);
			return ;
		}
		
		Operand(Operand const & src){};
		~Operand(void){};

		int getPrecision( void ){}; // Precision of the type of the instance

		eOperandType			getType( void )
		{
			
		}

		IOperand const *		operator+( IOperand const & rhs ){}

		IOperand const *		operator-( IOperand const & rhs ){}

		IOperand const *		operator*( IOperand const & rhs ){}

		IOperand const *		operator/( IOperand const & rhs ){}

		IOperand const *		operator%( IOperand const & rhs ){}

		std::string const &		toString(void) const
		{
			return (this->_str);
		}
		
	private:
		T						_value;
		eOperandType			_type;
		int						_precision;
		const FactoryOperand*	_factory;
		std::string				_str;
};

// std::ostream &		operator<<(std::ostream & o, IOperand const & i)
// {
	// o << i.<< stdn::endl;
	// return ();
// }

#endif
