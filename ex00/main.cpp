/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 13:20:15 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/08/25 13:57:13 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
	std::cout << "===== VALID BUREAUCRAT =====" << std::endl;

	try
	{
		Bureaucrat bob("Bob", 42);

		std::cout << bob << std::endl;
		std::cout << "Name: " << bob.getName() << std::endl;
		std::cout << "Grade: " << bob.getGrade() << std::endl;

		std::cout << std::endl;
		std::cout << "Incrementing grade..." << std::endl;
		bob.incrementGrade();
		std::cout << bob << std::endl;

		std::cout << "Decrementing grade..." << std::endl;
		bob.decrementGrade();
		std::cout << bob << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "===== GRADE TOO HIGH =====" << std::endl;

	try
	{
		Bureaucrat high("High", 0);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "===== GRADE TOO LOW =====" << std::endl;

	try
	{
		Bureaucrat low("Low", 151);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "===== INCREMENT FROM GRADE 1 =====" << std::endl;

	try
	{
		Bureaucrat high("High", 1);

		std::cout << high << std::endl;
		high.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "===== DECREMENT FROM GRADE 150 =====" << std::endl;

	try
	{
		Bureaucrat low("Low", 150);

		std::cout << low << std::endl;
		low.decrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "===== COPY CONSTRUCTOR =====" << std::endl;

	try
	{
		Bureaucrat original("Original", 50);
		Bureaucrat copy(original);

		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy:     " << copy << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "===== ASSIGNMENT OPERATOR =====" << std::endl;

	try
	{
		Bureaucrat first("First", 20);
		Bureaucrat second("Second", 100);

		std::cout << "Before assignment:" << std::endl;
		std::cout << "First:  " << first << std::endl;
		std::cout << "Second: " << second << std::endl;

		second = first;

		std::cout << "After assignment:" << std::endl;
		std::cout << "First:  " << first << std::endl;
		std::cout << "Second: " << second << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return (0);
}