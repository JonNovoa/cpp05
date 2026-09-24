/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:21:30 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/24 18:40:31 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm(
	const std::string &target)
	: AForm("PresidentialPardonForm", 25, 5), _target(target)
{
}

PresidentialPardonForm::PresidentialPardonForm(
	const PresidentialPardonForm &other)
	: AForm(other), _target(other._target)
{
}

PresidentialPardonForm &PresidentialPardonForm::operator=(
	const PresidentialPardonForm &other)
{
	if (this != &other)
		_target = other._target;
	return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
    if(!getSigned())
        throw std::exception();
    if(executor.getGrade() > getGradeToExecute())
        throw std::exception();
    std::cout << _target
		<< " has been pardoned by Zaphod Beeblebrox."
		<< std::endl;
}
