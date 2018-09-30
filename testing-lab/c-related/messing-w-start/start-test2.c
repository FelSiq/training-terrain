extern long write(int fd, const void *buf, long count);
void exit(int status);

void _start() {
	write(1, "Hello world!\n", 13);
	exit(0);
}
