/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:39:22 by yukoc             #+#    #+#             */
/*   Updated: 2025/04/29 13:39:36 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*test(void *arg)
{
	int i;

	(void)arg;
	i = 3;
	while (i > -1)
	{
		if (i > 0)
			printf("BOMBA PATLIYOR %d...\n", i);
		else
			printf("BOMBA PATLADI!\n");
		i--;
		if (i > -1)
			sleep(1);
	}
	return (NULL);
}

int main(void)
{
	pthread_t thread;

	printf("Hello, World!\n");
	printf("Creating thread \"test\"...\n");
	if (pthread_create(&thread, NULL, test, NULL) != 0)
	{
		perror("Failed to create thread");
		return (1);
	}
	printf("Thread \"test\" created successfully.\n");
	pthread_join(thread, NULL);
	printf("Thread \"test\" has finished.\n");
	printf("Exiting main thread.\n");
	return (0);
}
