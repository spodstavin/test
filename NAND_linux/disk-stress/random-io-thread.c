#include	<stdio.h>
#include	<stdlib.h>
#include	<errno.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	"disk-stress.h"

/*
 *	Externals
 */

extern unsigned long	Verbose;
extern char		*Prog_name;
extern G_SLEEPY_BARRIER	Sleepy_barrier;

/*
 *	random_io_test
 */

static unsigned long
random_io_test( int fd, DISK_THREAD_PARAMETER *dtp )
{
	unsigned long	erc;
	unsigned long	io_blocks;
	unsigned long	operations;
	int		perform_read;
	unsigned long	slots_in_test;
	unsigned long	starting_block;

	/*
	 *	Compute some useful constants.
	 */

	io_blocks = DTP_BLOCK_SIZE(dtp) / DISK_BLOCK_SIZE;
	operations = DTP_REQUESTS_PER_THREAD(dtp);
	slots_in_test = DTP_TEST_AREA_SIZE(dtp) / io_blocks;

	/*
	 *	Perform the test for the requested number of operations.
	 */

	while ( operations-- )
	{
		/*
		 *	Determine the type of I/O operation to perform.
		 */

		perform_read = choose_io_type(dtp);

		/*
		 *	Randomly choose a slot to perform the operation on.
		 */

		erc = (unsigned long) (uniform_random() * slots_in_test);

		starting_block = DTP_STARTING_BLOCK(dtp) + (erc * io_blocks);

		/*
		 *	Appropriate verbosity.
		 */

		if ( Verbose > 2 )
		{
			(void) printf("%s: (%s;%ld) I/O [%s,%ld,%ld]\n",
					Prog_name, DTP_RAW_DEVICE_NAME(dtp),
					DTP_NUMBER(dtp),
					(perform_read) ? "R" : "W",
		      			starting_block, io_blocks);
		}

		/*
		 *	Perform the selected operation.
		 */

		if ( perform_read )
		{
			erc = read_blocks(fd, dtp, starting_block, io_blocks);
		}
		else
		{
			if ( DTP_WRITE_VERIFICATION(dtp) )
			{
				erc = write_with_verification(fd, dtp,
						starting_block, io_blocks);
			}
			else
			{
				erc = write_blocks(fd, dtp, starting_block,
								io_blocks);
			}
		}

		/*
		 *	Handle any errors.
		 */

		if ( erc != 0 )
		{
			char buffer[256];

			(void) sprintf(buffer,
					"%s: (%s;%ld) %s [%s,%ld,%ld] error",
					Prog_name, DTP_RAW_DEVICE_NAME(dtp),
					DTP_NUMBER(dtp),
					(erc == EDOM) ? "verification" : "I/O",
					(perform_read) ? "R" : "W",
		      			starting_block, io_blocks);

			errno = erc;

			perror(buffer);

			break;
		}
	}

	/*
	 *	Exit with status.
	 */

	return (erc);
}

/*
 *	random_io_thread
 */

void
random_io_thread( void *arg )
{
	int			fd;
	int			mode;
	DISK_THREAD_PARAMETER	*dtp;

	/*
	 *	Covert the argument into a disk_info pointer.
	 */

	dtp = (DISK_THREAD_PARAMETER *) arg;

	/*
	 *	Compute the open mode.
	 */

	if ( DTP_READ_FRACTION(dtp) == 0.0 )
	{
		if ( DTP_WRITE_VERIFICATION(dtp) )
		{
			mode = O_RDWR;
		}
		else
		{
			mode = O_WRONLY;
		}
	}
	else
	{
		if ( DTP_READ_FRACTION(dtp) == 1.0 )
		{
			mode = O_RDONLY;
		}
		else
		{
			mode = O_RDWR;
		}
	}

	/*
	 *	Attempt to open the disk.
	 */

	fd = open(DTP_RAW_DEVICE_NAME(dtp), mode);

	if ( fd == -1 )
	{
		char	buffer[256];

		(void) sprintf(buffer, "%s: (%s;%ld) - open failure",
					Prog_name, DTP_RAW_DEVICE_NAME(dtp),
					DTP_NUMBER(dtp));

		perror(buffer);

		DTP_STATUS(dtp) = errno;

		pthread_exit((void *) &DTP_STATUS(dtp));
	}

	/*
	 *	Sleep on the barrier until all of the other threads are ready.
	 */

	g_sleepy_barrier(&Sleepy_barrier);

	/*
	 *	Run the test.
	 */

	DTP_STATUS(dtp) = random_io_test(fd, dtp);

	/*
	 *	Close the disk.
	 */

	(void) close(fd);

	/*
	 *	Done!
	 */

	pthread_exit((void *) &DTP_STATUS(dtp));
}
