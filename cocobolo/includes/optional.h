/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optional.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:09:11 by aamirkha          #+#    #+#             */
/*   Updated: 2024/06/25 13:23:27 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONAL_H
# define OPTIONAL_H

# include "cocobolo.h"
# include <stdbool.h>

typedef struct s_optional	t_optional;
typedef bool				(*t_optional_predicate)(const t_optional *obj);
typedef long				t_value;

struct						s_optional
{
	t_value					value;
	bool					has_value;
};

t_optional					make_optional(void);
void						set_optional(t_optional *optional, t_value val);
bool						has_value(const t_optional *optional);
t_value						value(const t_optional *optional);
t_value						value_or(const t_optional *optional, t_value val);
bool						any_of(t_optional_predicate unary_predicate,
								...) __attribute__((sentinel));

#endif // OPTIONAL_H
