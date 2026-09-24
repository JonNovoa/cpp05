/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:24:45 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/24 13:40:38 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main()
{
	//Tiene suficiente grado para ejecutar los 3 formularios
	Bureaucrat boss("Boss", 1);

	//No tiene suficiente grado
	Bureaucrat intern("Intern", 150);
	
	//Creamos los 3 formularios
	ShrubberyCreationForm shrubbery("home");
	RobotomyRequestForm robotomy("Bender");
	PresidentialPardonForm pardon("Arthurn Dent");

	std::cout << "===== EJECUTAR SIN FIRMAR =====" << std::endl;

	// INTENTAMOS EJECUTAR SIN FIRMAR
	boss.executeForm(shrubbery);

	std::cout << std::endl;
	std::cout << "===== FIRMAR FORMULARIOS =====" << std::endl;

	// BOSS FIRMA LOS TRES FORMULARIOS
	boss.signForm(shrubbery);
	boss.signForm(robotomy);
	boss.signForm(pardon);

	std::cout << std::endl;
	std::cout << "===== EJECUTAR FORMULARIOS =====" << std::endl;

	// BOSS EJECUTA LOS TRES FORMULARIOS
	boss.executeForm(shrubbery);
	boss.executeForm(robotomy);
	boss.executeForm(pardon);

	std::cout << std::endl;
	std::cout << "===== GRADO INSUFICIENTE =====" << std::endl;

	// INTERN INTENTA EJECUTAR UN FORMULARIO
	intern.executeForm(shrubbery);

	return (0);
}