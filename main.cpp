/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:20:34 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/25 19:09:00 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.class.hpp"
#include "FactoryOperand.class.hpp"
#include "Parser.class.hpp"
#include <fstream>
#include <regex>

int		main(int argc, char **argv)
{
	std::string		input;
	std::string		line;

	if (argc == 2)
	{
		std::ifstream	file(argv[1]);
		if (!file.is_open())
		{
			std::cerr << "Can't open file." << std::endl;
			return (-1);
		}
       	while (std::getline(file, line))
			input.append(line + "\n");
		file.close();
		Parser	parsed(input);
		
	}
	else if (argc == 1 && fileno(stdin) != -1)
	{
		std::regex	end("^[ \t]*;;[ \t]*$");
		
		while (std::getline(std::cin, line))
		{
			if (regex_match(line, end))
				break ;
			input.append(line + "\n");
		}
		Parser	parsed(input);
	}
	else
	{
		std::cout << "Bad arguments." << std::endl;
	}
	return (0);
}
