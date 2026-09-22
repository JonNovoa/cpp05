/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 20:13:37 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/22 20:23:46 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form:form()
	: _name("Default"), _signed(false),
	 _gradeToSign(150), _gradeToExecute(150)
{
}

Form:Form(const std::string &name, int _gradeToSign, int _gradeToExecute
	: _name(name), _signed(false),
	 _gradeToSign(_gradeToSign), _gradeToExecute(gradeToExecute))
{
	if(gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if(gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &other)
	: _name(other._name), _signed(other._signed),
	 _gradeToSign(other._gradeToSign),
	 _gradeToExecute(other._gradeToExecute)
{
}

Form &Form::operator=(const Form &other)
{
	if(this != &other)
		_signed = other._signed;
	return (*this);
}

Form:~Form()
{
}

const std::string &Form::getName() const
{
	return (_name);
}

bool Form::getSigned() const
{
	return (_signed);
}

int Form::getGradeToSign() const
{
	return (_gradeToSign);
}

int Form::getGradeToExecute() const
{
	return (_gradeToExecute);
}

void Form::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_signed = true;
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Form grade is too high!");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Form grade is too low!");
}

std::ostream &operator<<(std::ostream &out, const Form &form)
{
	out << form.getName()
		<< ", signed: " << (form.getSigned() ? "yes" : "no")
		<< ", grade required to sign: " << form.getGradeToSign()
		<< ", grade required to execute: " << form.getGradeToExecute();
	return (out);
}