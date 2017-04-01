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
# include <climits>
# include <cfloat>
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
			std::stringstream	ss_err;

			if (this->CheckOverflow())
			{
				ss_err << "Overflow or underflow";
				throw MyException::overflow_error(ss_err.str());
				return ;
			}
			std::stringstream	ss;
			std::regex			regex("0*$");
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
			if (this->_str == "")
				this->_str = "0";
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
				ss << "Divizion by zero";
				throw MyException::invalid_argument(ss.str());
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
				ss << "Divizion by zero";
				throw MyException::invalid_argument(ss.str());
				return (NULL);
			}
			type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			if (type < Float)
				ss << std::stoi(this->toString()) * std::stoi(rhs.toString());
			else
				ss << std::stod(this->toString()) * std::stod(rhs.toString());
			return (this->_factory->createOperand(type, ss.str()));
		}

		bool					operator<(IOperand const & rhs) const
		{
			eOperandType		type;

			type = (this->getType() > rhs.getType()) ? this->getType() : rhs.getType();
			if (type < Float)
				return (std::stoi(this->toString()) < std::stoi(rhs.toString()));
			else
				return (std::stod(this->toString()) < std::stod(rhs.toString()));
			return (false);
		}

		bool					operator==(IOperand const & rhs) const
		{
			eOperandType		type;

			if (this->getType() != rhs.getType())
				return (false);
			if (this->getType() < Float)
				return (std::stoi(this->toString()) == std::stoi(rhs.toString()));
			else
				return (std::stod(this->toString()) == std::stod(rhs.toString()));
			return (false);
		}

		std::string const &		toString(void) const
		{
			return (this->_str);
		}
		
		bool					CheckOverflow(void) const
		{
			try {
				switch (this->_type)
				{
					case Int8:
						if (std::stoi(this->_str) > SCHAR_MAX
							|| std::stoi(this->_str) < SCHAR_MIN)
							return (1);
						break ;
					case Int16:
						if (std::stoi(this->_str) > SHRT_MAX
							|| std::stoi(this->_str) < SHRT_MIN)
							return (1);
						break ;
					case Int32:
						if (std::stol(this->_str) > INT_MAX
							|| std::stol(this->_str) < INT_MIN)
							return (1);
						break ;
					case Float:
						if (std::stod(this->_str) > FLT_MAX
							|| std::stod(this->_str) < FLT_MIN)
							return (1);
						break ;
					case Double:
						if (std::stold(this->_str) > DBL_MAX
							|| std::stold(this->_str) < DBL_MIN)
							return (1);
						break ;
				}
			}
			catch (...)
			{
				return (1);
			}
			return (0);
		}
		
	private:
		T						_value;
		eOperandType			_type;
		int						_precision;
		FactoryOperand const *	_factory;
		std::string				_str;
};

#endif
