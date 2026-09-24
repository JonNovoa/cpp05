/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 12:57:31 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/24 18:56:17 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("RobotomyRequestForm", 72, 45), _target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(
	const RobotomyRequestForm &other)
	: AForm(other), _target(other._target)
{
}

RobotomyRequestForm &RobotomyRequestForm::operator=(
	const RobotomyRequestForm &other)
{
	if (this != &other)
		_target = other._target;
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
    if(!getSigned())
        throw std::exception();

    if(executor.getGrade() > getGradeToExecute())
        throw std::exception();
    
    std::cout << "* drilling noises *" << std::endl;
    
    if(std::rand() % 2 == 0)
        std::cout << _target << "has been robotomized successfully"
            << std::endl;
    else
        std::cout << " The robotmy failed on " << _target << std::endl;
}