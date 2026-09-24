/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 20:13:37 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/24 18:53:11 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm()
	: _name("Default"), _signed(false),
	 _gradeToSign(150), _gradeToExecute(150)
{
}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute)
	: _name(name), _signed(false),
	 _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	if(gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if(gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &other)
	: _name(other._name), _signed(other._signed),
	 _gradeToSign(other._gradeToSign),
	 _gradeToExecute(other._gradeToExecute)
{
}

AForm &AForm::operator=(const AForm &other)
{
	if(this != &other)
		_signed = other._signed;
	return (*this);
}

AForm::~AForm()
{
}

const std::string &AForm::getName() const
{
	return (_name);
}

bool AForm::getSigned() const
{
	return (_signed);
}

int AForm::getGradeToSign() const
{
	return (_gradeToSign);
}

int AForm::getGradeToExecute() const
{
	return (_gradeToExecute);
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_signed = true;
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return ("Form grade is too high!");
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return ("Form grade is too low!");
}

std::ostream &operator<<(std::ostream &out, const AForm &form)
{
	out << form.getName()
		<< ", signed: " << (form.getSigned() ? "yes" : "no")
		<< ", grade required to sign: " << form.getGradeToSign()
		<< ", grade required to execute: " << form.getGradeToExecute();
	return (out);
}