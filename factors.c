#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char *argv[])
{
	FILE *file;
	mpz_t number, half, sol, i, remainder, divider, inverse;
	char buffer[100];
	int cmp, cmp1, cmp2;

	mpz_init(number);
	mpz_init(half);
	mpz_init(sol);
	mpz_init(i);
	mpz_init(remainder);
	mpz_init(divider);
	mpz_init(inverse);
	if (argc != 2)
	{
		printf("Usage: %s filename\n", argv[0]);
		return (1);
	}
	file = fopen(argv[1],"r");
	if (file == NULL)
	{
		perror("Error opening file");
		return (1);
	}

	while (fscanf(file, "%99s", buffer) != EOF)
	{
		mpz_set_str(number, buffer, 10);
		mpz_tdiv_q_ui(half, number, 2);
		mpz_set_str(i, "2", 10);

		cmp = mpz_cmp(i, half);
		while (cmp <= 0)
		{
			mpz_mod(remainder, number, i);
			cmp1 = mpz_cmp(remainder,0);
			if (cmp1 == 0)
			{
				mpz_set(sol, i);
				break;
			}
			mpz_sub(inverse, half, i);
			mpz_mod(remainder, number, inverse);
                        cmp2 = mpz_cmp(remainder,0);
			if (cmp2 == 0)
                        {
                                mpz_set(sol, inverse);
                                break;
                        }
			mpz_add_ui(i, i, 1);
			cmp = mpz_cmp(i, half);
		}
		mpz_tdiv_q(divider, number, sol);
		gmp_printf("%Zd=%Zd*%Zd\n", number, divider, sol);
	}

	mpz_clear(number);
	mpz_clear(i);
	mpz_clear(sol);
	mpz_clear(divider);
	mpz_clear(inverse);
	mpz_clear(half);
	mpz_clear(remainder);
	fclose(file);

	return (0);
}

