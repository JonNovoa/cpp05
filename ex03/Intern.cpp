/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 20:10:51 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/24 20:23:57 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

AForm *createShrubbery(const std::string &target)
{
	return (new ShrubberyCreationForm(target));
}

AForm *createRobotomy(const std::string &target)
{
	return (new RobotomyRequestForm(target));
}

AForm *createPardon(const std::string &target)
{
	return (new PresidentialPardonForm(target));
}

Intern::Intern()
{
}

Intern::Intern(const Intern &other)
{
	(void)other;
}

Intern &Intern::operator=(const Intern &other)
{
	(void)other;
	return (*this);
}

Intern::~Intern()
{
}

/*CREA EL FORMULARIO*/
AForm *Intern::makeForm(const std::string &formName,
	const std::string &target)
{
    /*NOMBRE DE LOS FORMULARIOS*/
      std::string names[3] =
    {
        "shrubbery creation",
        "robotomy request",
        "presidental pardon"
    };

    /*Funciones para crear cada formulario*/
    AForm *(*create[3])(const std::string &) =
    {
        createShrubbery,
        createRobotomy,
        createPardon,
    };

    /*Buscamos el nombre del formulario*/
    for(int i = 0; i < 3; i++)
    {
        if(formName == names[i])
        {
            /*CREA EL FORMULARIO*/ 
			std::cout << "Intern creates " << formName << std::endl;
			return (create[i](target));
        }
    }

    /*SI NO EXISTE EL FORMULARIO*/ 
	std::cout << "Intern cannot create " << formName
		<< " because it does not exist" << std::endl;
    
    return (NULL);
}
