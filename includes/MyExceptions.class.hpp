/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyExceptions.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 18:22:36 by kperreau          #+#    #+#             */
/*   Updated: 2017/03/25 20:34:56 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYEXCEPTION_HPP
# define MYEXCEPTION_HPP

# include <stdexcept>

class MyException : public std::invalid_argument, public std::overflow_error
{
	public:
		MyException(const MyException & e) : invalid_argument(e), overflow_error(e) {};
		const MyException& operator=(const MyException & e);
		virtual const char* what() const throw ()
		{
			return (this->_msg.c_str());
		};

		virtual ~MyException() throw (){}

	private:
		std::string		_msg;
};

#endif