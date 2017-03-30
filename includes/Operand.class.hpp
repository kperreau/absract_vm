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
# include <sstream>
# include <iomanip>
# include <cstdlib>
# include "IOperand.class.hpp"
# include "FactoryOperand.class.hpp"
# include "Parser.class.hpp"

template <typename T>
class Operand : public IOperand
{
	public:
		Operand(void){};
		Operand(eOperandType type, std::string const & value, int precision, FactoryOperand const * factory)
		: _type(type), _str(value), _precision(precision), _factory(factory)
		{
			std::stringstream	ss;
			std::regex			regex("0*$");
			// if (type == Int8)
				// this->_value = static_cast<char>(std::stoi(value));
			// else if (type == Int16)
				// this->_value = static_cast<short int>(std::stoi(value));
			// else if (type == Int32)
				// this->_value = static_cast<int>(std::stoi(value));
			// else if (type == Float)
				// this->_value = static_cast<float>(std::stof(value));
			// else
				// this->_value = static_cast<double>(std::stod(value));
			if (type < Float)
			{
				this->_value = static_cast<T>(std::stoi(value));
			}
			else
			{
				this->_value = static_cast<T>(std::stod(value));
			}
			ss << std::fixed << std::setprecision(this->_precision) << +this->_value;
			this->_str = regex_replace(ss.str(), regex, "");
			// this->_str = ss.str();
			return ;
		}

		Operand(Operand const & src)
		{
			this->_type = src.getType();
			this->_str = src.toString();
			return ;
		}

		~Operand(void)
		{
		}

		int getPrecision(void) const
		{
			return (this->_precision);
		}

		eOperandType			getType(void) const
		{
			return (this->_type);
		}

		// IOperand const &		operator=( IOperand const & rhs)
		// {
			// this->_type = rhs.getType();
			// this->_str = rhs.toString();
			// return (*this);
		// }

		IOperand const *		operator+(IOperand const & rhs) const
		{
			eOperandType		type;
			std::stringstream	ss;

			type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			if (type < Float)
				ss << std::stoi(this->toString()) + std::stoi(rhs.toString());
			else
				ss << std::stod(this->toString()) + std::stod(rhs.toString());
			return (this->_factory->createOperand(type, ss.str()));
			// else if (type == Int16)
				// this->_value = static_cast<short int>(std::stoi(value));
			// else if (type == Int32)
				// this->_value = static_cast<int>(std::stoi(value));
			// else if (type == Float)
				// this->_value = static_cast<float>(std::stof(value));
			// else
				// this->_value = static_cast<double>(std::stod(value));
			// return (new Operand<>(type, value));
		}

		IOperand const *		operator-(IOperand const & rhs) const
		{
			eOperandType		type;
			std::stringstream	ss;

			type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			if (type < Float)
				ss << std::stoi(this->toString()) - std::stoi(rhs.toString());
			else
				ss << std::stod(this->toString()) - std::stod(rhs.toString());
			return (this->_factory->createOperand(type, ss.str()));
		}

		IOperand const *		operator*(IOperand const & rhs) const
		{
			eOperandType		type;
			std::stringstream	ss;

			type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			if (type < Float)
				ss << std::stoi(this->toString()) * std::stoi(rhs.toString());
			else
				ss << std::stod(this->toString()) * std::stod(rhs.toString());
			return (this->_factory->createOperand(type, ss.str()));
		}

		IOperand const *		operator/(IOperand const & rhs) const
		{
			eOperandType		type;
			std::stringstream	ss;

			if (std::stold(rhs.toString()) == 0)
			{
				std::cerr << "Line " << Parser::line << ": Divizion by zero." << std::endl;
				return (NULL);
			}
			type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			if (type < Float)
				ss << std::stoi(this->toString()) / std::stoi(rhs.toString());
			else
				ss << std::stod(this->toString()) / std::stod(rhs.toString());
			return (this->_factory->createOperand(type, ss.str()));
		}

		IOperand const *		operator%(IOperand const & rhs) const
		{
			eOperandType		type;
			std::stringstream	ss;

			if (std::stold(rhs.toString()) == 0)
			{
				std::cerr << "Line " << Parser::line << ": Divizion by zero." << std::endl;
				return (NULL);
			}
			type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			if (type < Float)
				ss << std::stoi(this->toString()) * std::stoi(rhs.toString());
			else
				ss << std::stod(this->toString()) * std::stod(rhs.toString());
			return (this->_factory->createOperand(type, ss.str()));
		}

		std::string const &		toString(void) const
		{
			return (this->_str);
		}
		
	private:
		T						_value;
		eOperandType			_type;
		int						_precision;
		FactoryOperand const *	_factory;
		std::string				_str;
};

// std::ostream &		operator<<(std::ostream & o, IOperand const & i)
// {
	// o << std::to_string(i._value);
	// return (o);
// }

#endif
