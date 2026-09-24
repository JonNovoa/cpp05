/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:24:45 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/24 20:59:55 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>

int main()
{
	
	Intern someRandomIntern;

	AForm *form;

	//El intern crea un robotomy request
	form = someRandomIntern.makeForm("robotomy request", "Bender");
	
	//Comprobamos que se ha creado
	if(form)
	{
		//Bureaucrat GRADO 1
		Bureaucrat boss("Boss", 1);

		//Firma de formulario
		boss.signForm(*form);

		//Ejecuta el formulario
		boss.executeForm(*form);

		delete form;
	}

	return 0;
}
