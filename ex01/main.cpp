/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 20:23:58 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/22 20:24:16 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	std::cout << "===== FORM =====" << std::endl;

	try
	{
		Form form("Contract", 50, 30);

		std::cout << form << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "===== SUCCESSFUL SIGN =====" << std::endl;

	try
	{
		Bureaucrat bob("Bob", 40);
		Form form("Contract", 50, 30);

		std::cout << bob << std::endl;
		std::cout << form << std::endl;

		bob.signForm(form);

		std::cout << form << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "===== FAILED SIGN =====" << std::endl;

	try
	{
		Bureaucrat john("John", 60);
		Form form("Contract", 50, 30);

		std::cout << john << std::endl;
		std::cout << form << std::endl;

		john.signForm(form);

		std::cout << form << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "===== INVALID FORM =====" << std::endl;

	try
	{
		Form form("Invalid", 0, 30);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return (0);
}