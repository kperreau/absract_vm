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
	std::stringstream	ss;

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
	this->_instruction["reset"] = &Parser::_reset;
	this->_instruction["rev"] = &Parser::_rev;
	this->_instruction["sort"] = &Parser::_sort;
	this->_instruction["unique"] = &Parser::_unique;

	this->_type["int8"] = Int8;
	this->_type["int16"] = Int16;
	this->_type["int32"] = Int32;
	this->_type["float"] = Float;
	this->_type["double"] = Double;

	while (std::getline(ctx, line))
	{
		if (this->_isExit)
			break ;
		if (line.find(";") != std::string::npos)
			line.erase(line.find(";"));
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);
		
		if (std::regex_search(line, match, trim))
		{
			try {
				if (this->_instruction.find(match[1].str()) != this->_instruction.end())
				{
					try {
						(*this.*(_instruction.at(match[1].str())))(match[2]);
					}
					catch (const MyException::invalid_argument & e){
						std::cerr << ANSI_COLOR_YELLOW << "Line " << Parser::line << ": Error: " << match[1].str() << " " << e.what() << COLOR_RESET << std::endl;
					}
				}
				else
				{
					ss << "Unknown instruction";
					throw MyException::invalid_argument(ss.str());
				}
			}
			catch (const MyException::invalid_argument & e){
				std::cerr << ANSI_COLOR_YELLOW << "Line " << Parser::line << ": Error: " << e.what() << COLOR_RESET << std::endl;
			}
		}
		++Parser::line;
	}
	try {
		if (!this->_isExit)
		{
			ss << "Missing exit instruction";
			throw MyException::invalid_argument(ss.str());
			return ;
		}
	}
	catch (const MyException::invalid_argument & e){
		std::cerr << ANSI_COLOR_YELLOW << "Line " << Parser::line << ": Error: " << e.what() << COLOR_RESET << std::endl;
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

	try {
		val = this->_check_value(value);
	}
	catch (const MyException::invalid_argument & e){
		std::cerr << ANSI_COLOR_YELLOW << "Line " << Parser::line << ": Error: PUSH " << e.what() << COLOR_RESET << std::endl;
	}
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
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.size() < 2)
	{
		err << "Too few data in stack.";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	++it2;
	add = **it2 + **it1;
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
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw std::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.size() < 2)
	{
		err << "Too few data in stack.";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	++it2;
	sub = **it2 - **it1;
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
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.size() < 2)
	{
		err << "Too few data in stack.";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	++it2;
	sub = **it2 * **it1;
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
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.size() < 2)
	{
		err << "Too few data in stack.";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	++it2;
	try {
		sub = **it2 / **it1;
	}
	catch (const MyException::invalid_argument & e){
		std::cerr << ANSI_COLOR_YELLOW << "Line " << Parser::line << ": Error: Div " << e.what() << COLOR_RESET << std::endl;
	}
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
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.size() < 2)
	{
		err << "Too few data in stack.";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	++it2;
	try {
		sub = **it2 % **it1;
	}
	catch (const MyException::invalid_argument & e){
		std::cerr << ANSI_COLOR_YELLOW << "Line " << Parser::line << ": Error: Mod " << e.what() << COLOR_RESET << std::endl;
	}
	delete this->_stack.front();
	this->_stack.pop_front();
	delete this->_stack.front();
	this->_stack.pop_front();
	this->_stack.push_front(sub);
	return ;
}

void					Parser::_pop(std::string const & value)
{
	std::regex			check("[^ \t]+");
	int					error;
	std::stringstream	err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.empty())
	{
		err << "Stack is empty";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	delete this->_stack.front();
	this->_stack.pop_front();
	return ;
}

void					Parser::_exit(std::string const & value)
{
	std::regex			check("[^ \t]+");
	std::stringstream	err;

	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		return ;
	}
	this->_isExit = 1;
	return ;
}

void					Parser::_print(std::string const & value)
{
	std::regex			check("[^ \t]+");
	char				c;
	int					error;
	std::stringstream	err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.empty())
	{
		err << "Stack is empty";
		throw MyException::invalid_argument(err.str());
	}
	if (this->_stack.front()->getType() != Int8)
	{
		err << "Wrong type";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	c = std::stoi(this->_stack.front()->toString());
	std::cout << ANSI_COLOR_GREEN << c << COLOR_RESET;
	return ;
}

void					Parser::_dump(std::string const & value)
{
	std::list<IOperand const *>::iterator	it;
	std::regex								check("[^ \t]+");
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (this->_stack.empty())
	{
		err << "Stack is empty";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	std::cout << ANSI_COLOR_CYAN;
	for (it = this->_stack.begin(); it != this->_stack.end(); it++)
		std::cout << (*it)->toString() << std::endl;
	std::cout << COLOR_RESET;
	return ;
}

void					Parser::_assert(std::string const & value)
{
	std::regex			check("[^ \t]+");
	IOperand const *	val;
	std::stringstream	err;

	try {
		val = this->_check_value(value);
	}
	catch (const MyException::invalid_argument & e){
		std::cerr << ANSI_COLOR_YELLOW << "Line " << Parser::line << ": Error: assert " << e.what() << COLOR_RESET << std::endl;
		return ;
	}
	
	if (this->_stack.empty())
	{
		err << "Stack is empty";
		throw MyException::invalid_argument(err.str());
		return ;
	}
	if (this->_stack.front()->getType() != val->getType())
	{
		err << "Wrong type";
		throw MyException::invalid_argument(err.str());
	}
	if (this->_stack.front()->toString() != val->toString())
	{
		err << "Wrong value";
		throw MyException::invalid_argument(err.str());
	}
	return ;
}

void					Parser::_reset(std::string const & value)
{
	std::list<IOperand const *>::iterator	it;
	std::regex								check("[^ \t]+");
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.empty())
	{
		err << "Stack is empty";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	for (it = this->_stack.begin(); it != this->_stack.end(); it++)
		delete *it;
	this->_stack.clear();
	return ;
}

bool					Parser::egal(IOperand const * first, IOperand const * second)
{
	return (*first == *second);
}

bool					Parser::compare(IOperand const * first, IOperand const * second)
{
	return (*first < *second);
}

void					Parser::_sort(std::string const & value)
{
	std::list<IOperand const *>::iterator	it;
	std::regex								check("[^ \t]+");
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.size() < 2)
	{
		err << "Too few data in stack.";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	this->_stack.sort(Parser::compare);
	return ;
}

void					Parser::_unique(std::string const & value)
{
	std::list<IOperand const *>::iterator	it;
	std::regex								check("[^ \t]+");
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.size() < 2)
	{
		err << "Too few data in stack.";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	this->_stack.unique(Parser::egal);
	return ;
}
void					Parser::_rev(std::string const & value)
{
	std::list<IOperand const *>::iterator	it;
	std::regex								check("[^ \t]+");
	int										error;
	std::stringstream						err;

	error = 0;
	if (regex_match(value, check))
	{
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	if (this->_stack.size() < 2)
	{
		err << "Too few data in stack.";
		throw MyException::invalid_argument(err.str());
		error = 1;
	}
	
	if (error)
		return ;
	
	this->_stack.reverse();
	return ;
}

IOperand const *		Parser::_check_value(std::string const & value)
{
	std::smatch			match_type;
	std::smatch			match_number;
	eOperandType		opType;
	std::regex			type("^[ \t]*(int8|int16|int32|double|float)\\([^ \t]*\\)[ \t]*([^ \t]*)");
	std::regex			number("\\(((\\+|-)?[0-9]+(\\.(([[:digit:]]+)?))?)\\)");
	int					error;
	std::stringstream	err;
	
	error = 0;
	if (value.size() == 0)
	{
		err << "too few parameters";
		throw MyException::invalid_argument(err.str());
		return (NULL);
	}
	if (!std::regex_search(value, match_type, type))
	{
		error = 1;
		err << "Unknown Type or bad format";
		throw MyException::invalid_argument(err.str());
	}
	
	if (match_type.size() > 2
		&& match_type[2].str().size() != 0)
	{
		error = 1;
		err << "Too much parameters";
		throw MyException::invalid_argument(err.str());
	}
	if (!std::regex_search(value, match_number, number))
	{
		error = 1;
		err << "Bad value";
		throw MyException::invalid_argument(err.str());
	}
	if (match_type.size() > 1
		&& this->_type.find(match_type[1].str()) != this->_type.end())
		opType = this->_type[match_type[1].str()];
	else
	{
		error = 1;
		err << "Bad Type";
		throw MyException::invalid_argument(err.str());
	}
	return (error ? NULL : this->_factory.createOperand(opType, match_number[1].str()));
}

int Parser::line = 1;