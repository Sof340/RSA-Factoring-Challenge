#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char *argv[])
{
	FILE *file;
	mpz_t number, half, sol, i, remainder, divider;
	char buffer[100];
	
	if (argc != 2)
	{
		printf("Usage: %s filename\n", argv[0]);
		return 1;
	}
	
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return 1;
	}
	
	mpz_init(number);
	mpz_init(half);
	mpz_init(sol);
	mpz_init(i);
	mpz_init(remainder);
	while (fscanf(file, "%99s", buffer) != EOF)
	{
		mpz_set_str(number, buffer, 10);
		mpz_tdiv_q_ui(half, number, 2);
		mpz_set_ui(sol, 0);
		mpz_set_ui(i, 2);

		for (; mpz_cmp_ui(i, mpz_get_ui(half)) <= 0; mpz_add_ui(i, i, 1))
		{
			mpz_mod(remainder, number, i);
			
			if (mpz_cmp_ui(remainder, 0) == 0)
			{
				mpz_set(sol, i);
				break;
			}
		}
		
		mpz_tdiv_q(divider, number, sol);
		gmp_printf("%Zd=%Zd*%Zd\n", number, divider, sol);
	}
	mpz_clear(number);
	mpz_clear(i);
	mpz_clear(sol);
	mpz_clear(divider);
	mpz_clear(half);
	mpz_clear(remainder);
	fclose(file);
	
	return 0;
}

