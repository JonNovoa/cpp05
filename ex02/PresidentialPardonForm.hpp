/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovoa-a <jnovoa-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:04:11 by jnovoa-a          #+#    #+#             */
/*   Updated: 2026/09/24 13:05:20 by jnovoa-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		std::string _target;

	public:
		PresidentialPardonForm(const std::string &target);

		PresidentialPardonForm(const PresidentialPardonForm &other);

		PresidentialPardonForm &operator=(const PresidentialPardonForm &other);

		~PresidentialPardonForm();

		void execute(Bureaucrat const &executor) const;
};

#endif