/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 12:55:45 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/24 12:56:09 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		std::string _target;

	public:
		RobotomyRequestForm(const std::string &target);

		RobotomyRequestForm(const RobotomyRequestForm &other);

		RobotomyRequestForm &operator=(const RobotomyRequestForm &other);

		~RobotomyRequestForm();

		void execute(Bureaucrat const &executor) const;
};

#endif