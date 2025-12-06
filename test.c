#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	run_test(char *filename)
{
	int		fd;
	char	*line;
	int		counter;

	printf("=== Testing %s ===\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return ;
	}
	counter = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line %d: %s", counter++, line);
		free(line);
	}
	close(fd);
	printf("=== End of %s ===\n\n", filename);
}

int	main(void)
{
	printf("----- get_next_line Test Suite -----\n\n");
	printf("BUFFER_SIZE: %d\n\n", BUFFER_SIZE);
	run_test("test.txt");
	run_test("multiple_nl.txt");
	run_test("single_line_no_nl.txt");
	run_test("empty.txt");
	run_test("1char.txt");
	run_test("long_line.txt");
	run_test("get_next_line.c");
	printf("----- End of Test Suite -----\n");
	// Invlaid file descriptor test
	printf("=== Testing invalid file descriptor ===\n");
	char *line = get_next_line(-1);
	if (line == NULL)
		printf("line: NULL (as expected for invalid fd)\n");
	else
	{
		printf("line: %s (unexpected for invalid fd)\n", line);
		free(line);
	}
	line = get_next_line(100);
	if (line == NULL)
		printf("line: NULL (as expected for invalid fd)\n");
	else
	{
		printf("line: %s (unexpected for invalid fd)\n", line);
		free(line);
	}
	// Closed file descriptor test
	int fd = open("empty.txt", O_RDONLY);
	close(fd);
	line = get_next_line(fd);
	if (line == NULL)
		printf("line: NULL (as expected for closed fd)\n");
	else
	{
		printf("line: %s (unexpected for closed fd)\n", line);
		free(line);
	}
	// Write only file descriptor test
	fd = open("write_only.txt", O_WRONLY);
	line = get_next_line(fd);
	if (line == NULL)
		printf("line: NULL (as expected for write-only fd)\n");
	else
	{
		printf("line: %s (unexpected for write-only fd)\n", line);
		free(line);
	}
	close(fd);
	// End of invalid file descriptor test
	return (0);
}