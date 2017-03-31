/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:35:56 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/25 19:32:19 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP
# include "IOperand.class.hpp"
# include "FactoryOperand.class.hpp"
# include <iostream>
# include <string>
# include <list>
# include <stack>
# include <regex>
# include <sstream>

class Parser
{
	public:
		static int		line;

		Parser(std::string const & str);
		Parser(Parser const & src);
		//Parser const & operator=(Parser const & rhs);
		
		~Parser(void);

	private:
		void				_push(std::string const & value);
		void				_add(std::string const & value);
		void				_mul(std::string const & value);
		void				_div(std::string const & value);
		void				_mod(std::string const & value);
		void				_sub(std::string const & value);
		void				_pop(std::string const & value);
		void				_exit(std::string const & value);
		void				_dump(std::string const & value);
		void				_print(std::string const & value);
		void				_assert(std::string const & value);
		IOperand const *	_check_value(std::string const & value);
		
		std::string						_str;
		std::list<IOperand const *>		_stack;
		FactoryOperand					_factory;
		int								_error;
		int								_isExit;
		
		std::map<std::string, void (Parser::*)(std::string const & value)> _instruction;
		std::map<std::string, enum eOperandType> _type;
};

std::ostream &		operator<<(std::ostream & o, Parser const & i);

#endif
