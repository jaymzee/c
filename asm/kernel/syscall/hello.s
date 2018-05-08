	.global	_start
	.data
msg:
	.ascii	"hello world!\n"
	msglen = . - msg
	.text
_start:
	mov	$1,%rax		# use the write syscall
	mov	$1,%rdi		# write to stdout
	mov	$msg,%rsi	# use string "Hello World"
	mov	$msglen,%rdx	# write 12 characters
	syscall			# make syscall

	mov	$60,%rax	# use the _exit syscall
	mov	$0,%rdi		# error code 0
	syscall			# make syscall
