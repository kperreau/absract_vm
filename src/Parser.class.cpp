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

Parser::Parser(std::string const & str)
: _str(str), _isExit(0), _error(0)
{
	std::string			line;
	std::string			instruction;
	std::smatch			match;
	// std::regex			trim("^[ \t]*([^ \t]+)[ \t]*([^ \t]*)");
	std::regex			trim("^[ \t]*([^ \t]+)[ \t]*(.*)");
	std::istringstream 	ctx(str);

	this->_instruction["push"] = &Parser::_push;
	this->_instruction["add"] = &Parser::_add;
	this->_instruction["sub"] = &Parser::_sub;
	this->_instruction["div"] = &Parser::_div;
	this->_instruction["mod"] = &Parser::_mod;
	this->_instruction["mul"] = &Parser::_mul;
	this->_instruction["pop"] = &Parser::_pop;
	this->_instruction["exit"] = &Parser::_exit;
	this->_instruction["print"] = &Parser::_print;
	this->_instruction["dump"] = &Parser::_dump;
	this->_instruction["assert"] = &Parser::_assert;

	while (std::getline(ctx, line))
	{
		if (this->_isExit)
			break ;
		if (line.find(";") != std::string::npos)
			line.erase(line.find(";"));
		// std::transform(line.begin(), line.end(), line.begin(), ::tolower);
		
		if (std::regex_search(line, match, trim))
		{
			if (this->_instruction.find(match[1].str()) != this->_instruction.end())
				(*this.*(_instruction.at(match[1].str())))(match[2]);
			else
				std::cerr << "Line " << Parser::line << ": Error: Unknown instruction" << std::endl;
		}
		++Parser::line;
	}
	if (!this->_isExit)
	{
		std::cerr << "Line " << Parser::line << ": Error: Missing exit instruction" << std::endl;
		return ;
	}
	return ;
}

Parser::Parser(Parser const & src)
{
	*this = src;
	
	return ;
}

Parser::~Parser(void)
{
	return ;
}

void					Parser::_push(std::string const & value)
{
	IOperand const *	val;

	val = this->_check_value(value);
	if (val != NULL)
		this->_stack.push_front(val);
	return ;
}

void					Parser::_add(std::string const & value)
{
	std::list<IOperand const *>::iterator	it1 = this->_stack.begin();
	std::list<IOperand const *>::iterator	it2 = this->_stack.begin();
	IOperand const *						add;
	std::regex								check("[^ \t]+");
	
	if (regex_match(value, check))
	{
		std::cerr << "Line " << Parser::line << ": add Error" << std::endl;
		return ;
	}
	if (this->_stack.size() < 2)
	{
		std::cerr << "Line " << Parser::line << ": Too few data in stack." << std::endl;
		return ;
	}
	++it2;
	add = **it1 + **it2;
	delete this->_stack.front();
	this->_stack.pop_front();
	delete this->_stack.front();
	this->_stack.pop_front();
	this->_stack.push_front(add);
	return ;
}

void					Parser::_sub(std::string const & value)
{
	std::list<IOperand const *>::iterator	it1 = this->_stack.begin();
	std::list<IOperand const *>::iterator	it2 = this->_stack.begin();
	IOperand const *						sub;
	std::regex								check("[^ \t]+");
	
	if (regex_match(value, check))
	{
		std::cerr << "Line " << Parser::line << ": sub Error" << std::endl;
		return ;
	}
	if (this->_stack.size() < 2)
	{
		std::cerr << "Line " << Parser::line << ": Too few data in stack." << std::endl;
		return ;
	}
	++it2;
	sub = **it1 - **it2;
	delete this->_stack.front();
	this->_stack.pop_front();
	delete this->_stack.front();
	this->_stack.pop_front();
	this->_stack.push_front(sub);
	return ;
}

void					Parser::_mul(std::string const & value)
{
	std::list<IOperand const *>::iterator	it1 = this->_stack.begin();
	std::list<IOperand const *>::iterator	it2 = this->_stack.begin();
	IOperand const *						sub;
	std::regex								check("[^ \t]+");
	
	if (regex_match(value, check))
	{
		std::cerr << "Line " << Parser::line << ": mul Error" << std::endl;
		return ;
	}
	if (this->_stack.size() < 2)
	{
		std::cerr << "Line " << Parser::line << ": Too few data in stack." << std::endl;
		return ;
	}
	++it2;
	sub = **it1 * **it2;
	delete this->_stack.front();
	this->_stack.pop_front();
	delete this->_stack.front();
	this->_stack.pop_front();
	this->_stack.push_front(sub);
	return ;
}

void					Parser::_div(std::string const & value)
{
	std::list<IOperand const *>::iterator	it1 = this->_stack.begin();
	std::list<IOperand const *>::iterator	it2 = this->_stack.begin();
	IOperand const *						sub;
	std::regex								check("[^ \t]+");
	
	if (regex_match(value, check))
	{
		std::cerr << "Line " << Parser::line << ": div Error" << std::endl;
		return ;
	}
	if (this->_stack.size() < 2)
	{
		std::cerr << "Line " << Parser::line << ": Too few data in stack." << std::endl;
		return ;
	}
	++it2;
	sub = **it1 / **it2;
	delete this->_stack.front();
	this->_stack.pop_front();
	delete this->_stack.front();
	this->_stack.pop_front();
	this->_stack.push_front(sub);
	return ;
}

void					Parser::_mod(std::string const & value)
{
	std::list<IOperand const *>::iterator	it1 = this->_stack.begin();
	std::list<IOperand const *>::iterator	it2 = this->_stack.begin();
	IOperand const *						sub;
	std::regex								check("[^ \t]+");
	
	if (regex_match(value, check))
	{
		std::cerr << "Line " << Parser::line << ": mod Error" << std::endl;
		return ;
	}
	if (this->_stack.size() < 2)
	{
		std::cerr << "Line " << Parser::line << ": Too few data in stack." << std::endl;
		return ;
	}
	++it2;
	sub = **it1 % **it2;
	delete this->_stack.front();
	this->_stack.pop_front();
	delete this->_stack.front();
	this->_stack.pop_front();
	this->_stack.push_front(sub);
	return ;
}

void					Parser::_pop(std::string const & value)
{
	std::regex	check("[^ \t]+");
	
	if (regex_match(value, check))
	{
		std::cerr << "Line " << Parser::line << ": pop Error" << std::endl;
		return ;
	}
	if (this->_stack.empty())
	{
		std::cerr << "Line " << Parser::line << ": Stack is empty." << std::endl;
		return ;
	}
	
	delete this->_stack.front();
	this->_stack.pop_front();
	return ;
}

void					Parser::_exit(std::string const & value)
{
	std::regex	check("[^ \t]+");
	
	if (regex_match(value, check))
	{
		std::cerr << "Line " << Parser::line << ": exit Error" << std::endl;
		return ;
	}
	this->_isExit = 1;
	return ;
}

void					Parser::_print(std::string const & value)
{
	std::regex		check("[^ \t]+");
	char			c;
	
	if (regex_match(value, check))
	{
		std::cerr << "Line " << Parser::line << ": print Error" << std::endl;
		return ;
	}
	if (this->_stack.empty())
	{
		std::cerr << "Line " << Parser::line << ": Stack is empty." << std::endl;
		return ;
	}
	if (this->_stack.front()->getType() != Int8)
	{
		std::cerr << "Line " << Parser::line << ": Wrong type." << std::endl;
		return ;
	}
	c = std::stoi(this->_stack.front()->toString());
	std::cout << c << std::endl;
	return ;
}

void					Parser::_dump(std::string const & value)
{
	std::list<IOperand const *>::iterator	it;
	std::regex	check("[^ \t]+");
	
	if (regex_match(value, check))
	{
		std::cerr << "Line " << Parser::line << ": dump Error" << std::endl;
		return ;
	}
	
	if (this->_stack.empty())
	{
		std::cerr << "Line " << Parser::line << ": Stack is empty." << std::endl;
		return ;
	}
	for (it = this->_stack.begin(); it != this->_stack.end(); it++)
		std::cout << (*it)->toString() << std::endl;
	return ;
}

void					Parser::_assert(std::string const & value)
{
	std::regex	check("[^ \t]+");
	IOperand const *	val;

	if (this->_stack.empty())
	{
		std::cerr << "Line " << Parser::line << ": Stack is empty." << std::endl;
		return ;
	}

	val = this->_check_value(value);
	if (this->_stack.front()->getType() != val->getType())
	{
		std::cerr << "Line " << Parser::line << ": Assert: Wrong type." << std::endl;
		return ;
	}
	if (this->_stack.front()->toString() != val->toString())
	{
		std::cerr << "Line " << Parser::line << ": Assert: Wrong value." << std::endl;
		return ;
	}
	return ;
}

IOperand const *		Parser::_check_value(std::string const & value)
{
	std::smatch		match_type;
	std::smatch		match_number;
	eOperandType	opType;
	std::regex		type("^[ \t]*(int8|int16|int32|double|float)\\([^ \t]*\\)[ \t]*([^ \t]*)");
	std::regex		number("\\(((\\+|-)?[0-9]+(\\.(([[:digit:]]+)?))?)\\)");
	
	if (value.size() == 0)
	{
		std::cerr << "Line " << Parser::line << ": too few parameters" << std::endl;
		return (NULL);
	}
	if (!std::regex_search(value, match_type, type))
	{
		std::cerr << "Line " << Parser::line << ": Unknown Type" << std::endl;
		return (NULL);
	}
	else if (match_type[2].str().size() != 0)
	{
		std::cerr << "Line " << Parser::line << ": too much parameters" << std::endl;
		return (NULL);
	}
	if (!std::regex_search(value, match_number, number))
	{
		std::cerr << "Line " << Parser::line << ": Bad value" << std::endl;
		return (NULL);
	}
	
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

int Parser::line = 1;