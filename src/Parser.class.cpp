/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 16:45:41 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/25 19:13:24 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.class.hpp"

Parser::Parser(std::string const & str) : _str(str)
{
	std::string			line;
	std::string			instruction;
	std::smatch			match;
	// std::regex			push("(\\+|-)?[[:digit:]]+");
	// std::regex			push("^[ \t]*+push[ \t](int|double|float)$");
	std::regex			trim("^[ \t]*([^ \t]+)[ \t]*([^ \t]*)");
	std::istringstream 	ctx(str);

	this->_instruction["push"] = &Parser::_push;
	this->_instruction["add"] = &Parser::_add;
	this->_instruction["pop"] = &Parser::_pop;
	this->_instruction["exit"] = &Parser::_exit;
	this->_instruction["print"] = &Parser::_print;
	this->_instruction["dump"] = &Parser::_dump;
	
	while (std::getline(ctx, line))
	{
		if (line.find(";") != std::string::npos)
			line.erase(line.find(";"));
		// std::transform(line.begin(), line.end(), line.begin(), ::tolower);
		
		if (!std::regex_search(line, match, trim))
			continue ;
		if (this->_instruction.find(match[1].str()) != this->_instruction.end())
			(*this.*(_instruction.at(match[1].str())))(match[2]);
	}	
	return ;
}

Parser::Parser(Parser const & src)
{
	// std::cout << "Copy constructor called." << std::endl;
	*this = src;
	
	return ;
}

Parser::~Parser(void)
{
	// std::cout << "Destructor called." << std::endl;
	
	return ;
}

void					Parser::_push(std::string const & value)
{
	IOperand const *	val;

	// std::cout << "push" << std::endl;
	val = this->_check_value(value);
	if (val != NULL)
		this->_stack.push_font(val);
	return ;
}

void					Parser::_add(std::string const & value)
{
	// std::cout << "add" << std::endl;
	return ;
}

void					Parser::_pop(std::string const & value)
{
	// std::cout << "pop" << std::endl;
	return ;
}

void					Parser::_exit(std::string const & value)
{
	// std::cout << "exit" << std::endl;
	return ;
}

void					Parser::_print(std::string const & value)
{
	// std::cout << "print" << std::endl;
	return ;
}

void					Parser::_dump(std::string const & value)
{
	std::list<IOperand const *>::iterator	it;

	// std::cout << "dump" << std::endl;
	for (it = this->_stack.begin(); it != this->_stack.end(); it++)
		std::cout << (*it)->toString() << std::endl;
	return ;
}

IOperand const *		Parser::_check_value(std::string const & value)
{
	std::smatch		match_type;
	std::smatch		match_number;
	eOperandType	opType;
	std::regex		type("^[ \t]*(int8|int16|int32|double|float)\\(([^ \t]*)\\)$");
	std::regex		number("\\(((\\+|-)?[0-9]+(\\.(([[:digit:]]+)?))?)\\)");
	
	if (!std::regex_search(value, match_type, type))
		return (NULL);
	if (!std::regex_search(value, match_number, number))
		return (NULL);
	
	if (match_type[1].str() == "int8")
		opType = Int8;
	else if (match_type[1].str() == "int16")
		opType = Int16;
	else if (match_type[1].str() == "int32")
		opType = Int32;
	else if (match_type[1].str() == "float")
		opType = Float;
	else
		opType = Double;
	
	// std::cout << match_type[1].str() << std::endl;
	// std::cout << match_number[1].str() << std::endl;
	
	return (this->_factory.createOperand(opType, match_number[1].str()));
}