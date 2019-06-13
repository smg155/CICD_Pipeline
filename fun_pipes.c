#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int fds[2];
	pipe(fds);

	pid_t pid = fork();
	if (pid == -1) {
		printf("error with fork\n");
		exit(1);
	} else if (pid > 0) {
		close(fds[1]);
		char buffer[16];
		read(fds[0], buffer, 13);

		printf("From parent: %s\n", buffer);
	} else {
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		execlp("echo", "echo", "hello world!", NULL);
	}

	waitpid(pid, NULL, 0);
}
