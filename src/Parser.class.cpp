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

Parser::Parser(void)
{
	std::cout << "Default constructor called." << std::endl;
	
	return ;
}

Parser::Parser(std::string const & str) : _str(str)
{
	std::string			line;
	std::regex			comments("[ \t]*;");
	std::istringstream 	ctx(str);

	std::cout << "Parameter constructor called." << std::endl;
	while (std::getline(ctx, line))
	{
		if (line.find(";") != std::string::npos)
			line.erase(line.find(";"));
		if (regex_match(line, comments))
			std::cout << "Commentaire" << std::endl;
	}	
	return ;
}

Parser::Parser(Parser const & src)
{
	std::cout << "Copy constructor called." << std::endl;
	*this = src;
	
	return ;
}

Parser::~Parser(void)
{
	std::cout << "Destructor called." << std::endl;
	
	return ;
}
