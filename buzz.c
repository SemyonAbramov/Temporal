#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>


typedef enum deviders
{
	DIV_3 = 1,
	DIV_5 = 2,
	DIV_3_AND_5 = 3
} deviders_t;



int sum_of_chars(char* line)
{
	int sum = 0;
	int i = 0;
	int len = strlen(line);

	while (i < len)
	{
		sum += (line[i] - '0');
		i++;
	}

	return sum;
} 


int sum_of_numerals(int number, int length)
{
	int sum = number;
	char* line = malloc(sizeof(char) * length);
	int len = 0;

	memset(line, 0, sizeof(char) * length);
	
	while (!(sum >= 0 && sum <= 9))
	{
		len = sprintf(line, "%d", sum);
		sum = sum_of_chars(line);
	}
	free(line);
		
	return sum;
}

inline char get_last_char(int num,char* line)
{
	sprintf(line, "%d", num);
	return line[strlen(line) - 1];
}  
		
void parse_number(int number, int len, char** str)
{
	char last_char;
	int sum = 0;
	uint8_t is_div3 = 0, is_div5 = 0;
	char* line = malloc(sizeof(char) * len);
	
	sum = sum_of_numerals(number, len);
	printf("sum: %d \n", sum);
	last_char = get_last_char(number, line);
	
	if (sum == 3 || sum == 6 || 
		sum == 9 || sum == 0)
		is_div3 = 1;

	if (last_char == '0' || last_char == '5')
		is_div5 = 1;
		
	switch ((is_div5 << 1) | is_div3)
	{
		case DIV_3:
			strcat(*str, "BIZZ");
			break;
		case DIV_5:
			strcat(*str, "BUZZ");
			break;
		case DIV_3_AND_5:
			strcat(*str, "BIZZBUZZ");
			break;
		default: 
			sprintf(line, "%d", number);
			strcat(*str, line);
			break;
	}				
	
	free(line);
	
	return;
} 

char* parse_string(char* end)
{
	
	char* begin = end;
	char* out_buf = malloc((strlen(end) * 8) * sizeof(char));
	int len_before = 0, len_after = 0, number = 0, parse_result = 0, i = 0;
	
	while (end[0] != '\0')
	{
	/*	if (!(end[0] >= '0' && end[0] <= '9'))
		{ 
			if ((end[0] == '-' || end[0] == '+') && end[1] != '\0' 
				&& end[1] >= '0' && end[1] <= '9') 
			{
				end++;
			}
			else
			{
				out_buf[strlen(out_buf)] = end[0];
				end++;
			}
		}
		else
		{
			len_before = strlen(end);
			number = strtol(end, &end, 10);
			len_after = strlen(end);
			parse_number(number, len_before - len_after, &out_buf);
			i++;
		}
	*/
		if ((end[0] >= '0' && end[0] <= '9') || ((end[0] == '-' || end[0] == '+') 
			&& end[1] != '\0' && (end[1] >= '0' && end[1] <= '9'))) 
		{		
			len_before = strlen(end);
			number = strtol(end, &end, 10);
			len_after = strlen(end);
			parse_number(number, len_before - len_after, &out_buf);
			i++;
		}
		else
		{				
			out_buf[strlen(out_buf)] = end[0];
			end++;
		}	
	}
	return out_buf;
}

int main(int argc, char* argv[])
{
	FILE* fp;
	char* out_buf; 
	if (argc != 2)
	{
		char* end;
		fp = fopen("input", "r+");
		
		if (fp == NULL)
			printf("NULL\n");

		size_t len = 0;
		getline(&end, &len, fp);
		printf("end: %s \n", end);
		out_buf = parse_string(end);
		fprintf(fp, "%s", out_buf);		
		free(end);		
		fclose(fp);
	}
	else
	{
		char* end = argv[1];
		out_buf = parse_string(end);
		printf("str: %s \n", out_buf);
	}
	
	free(out_buf);
	
	return 0;
}		
	
/*	
int main(int argc, char* argv[])
{
	
	char* end;
	FILE* fp;
	
	if (argc != 2)
	{
		end = NULL;
		fp = fopen("input", "r+");
		
		if (fp == NULL)
			printf("NULL\n");

		size_t len = 0;
		getline(&end, &len, fp);
		printf("end: %s \n", end);
	} 
	else
	{		
		end = argv[1];
	}
	

	
	end = argv[1];

	char* out_buf = malloc((strlen(end) * 8) * sizeof(char));
	memset(out_buf, 0, (strlen(end) * 8) * sizeof(char));

	int len_before = 0, len_after = 0, number = 0, parse_result = 0, i = 0;

	while (end[0] != '\0')
	{
		if (!(end[0] >= '0' && end[0] <= '9'))
		{ 
			if ((end[0] == '-' || end[0] == '+') && end[1] != '\0') 
			{
				end++;
			}
			else
			{
				out_buf[strlen(out_buf)] = end[0];
				end++;
			}
		}
		else
		{
			len_before = strlen(end);
			number = strtol(end, &end, 10);
			len_after = strlen(end);
			parse_str(number, len_before - len_after, &out_buf);
			i++;
		}
	}	

	if (argc != 2)
	{
		fprintf(fp, "%s", out_buf);
	}

	printf("str: %s \n", out_buf);
	free(out_buf);
	
	return 0;
}
*/
