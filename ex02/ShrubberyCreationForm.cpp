/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 11:43:40 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/24 18:54:41 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(
    const ShrubberyCreationForm &other)
    : AForm(other), _target(other._target)
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(
    const ShrubberyCreationForm &other)
{
    if(this != &other)
        _target = other._target;
    return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
    if(!getSigned())
        throw std::exception();
    
    if(executor.getGrade() > getGradeToExecute())
        throw std::exception();

    /*CREA EL NOMBRE DEL ARCHIVO*/
    std::string filename = _target + "_shrubbery";
    
    /*CREA/ABRE EL ARCHIVO*/
    std::ofstream file(filename.c_str());

    file << "       /\\\n";
	file << "      /  \\\n";
	file << "     /    \\\n";
	file << "    /____\\\n";
	file << "      ||\n";
	file << "      ||\n";
	file << "\n";
	file << "       /\\\n";
	file << "      /  \\\n";
	file << "     /____\\\n";
	file << "       ||\n";
	file << "       ||\n";

    file.close();
}

