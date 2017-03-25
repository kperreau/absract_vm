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
# include <stack>
# include <regex>
# include <sstream>

class Parser
{
	public:
		Parser(void);
		Parser(std::string const & str);
		Parser(Parser const & src);
		//Parser const & operator=(Parser const & rhs);
		~Parser(void);

	private:
		std::string						_str;
		std::stack<IOperand const *>	_stack;
		
};

std::ostream &		operator<<(std::ostream & o, Parser const & i);

#endif
