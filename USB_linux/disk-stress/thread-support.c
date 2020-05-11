#include	<stdio.h>
#include	<stdlib.h>
#include	<pthread.h>
#include	<errno.h>
#include	<sys/time.h>
#include	"disk-stress.h"
#include	"histo.h"

/*
 *	Externals
 */

extern char 	*Prog_name;

/*
 *	choose_io_type
 */

int
choose_io_type( DISK_THREAD_PARAMETER *dtp )
{
	int	do_read;

	/*
	 *	What type of operation is called for?
	 */

	if ( DTP_READ_FRACTION(dtp) == 0.0 )
	{
		do_read = FALSE;		/* write */
	}
	else
	{
		if ( DTP_READ_FRACTION(dtp) == 1.0 )
		{
			do_read = TRUE;		/* read */
		}
		else
		{
			if ( uniform_random() <= DTP_READ_FRACTION(dtp) )
			{
				do_read = TRUE;	/* read */
			}
			else
			{
				do_read = FALSE;/* write */
			}
		}
	}

	/*
	 *	Return status.
	 */

	return (do_read);
}

/*
 *	write_blocks
 */

int
write_blocks(	int			fd,
		DISK_THREAD_PARAMETER	*dtp,
		unsigned long		starting_block,
		unsigned long		blocks )
{
	int	erc;
	ssize_t	size;
	ssize_t	bytes;
	loff_t	l_offset;

	/*
	 *	Perform the seek.
	 */

	l_offset = ((loff_t) starting_block) * ((loff_t) DISK_BLOCK_SIZE);

	if ( lseek64(fd, l_offset, SEEK_SET) == -1 )
	{
		return (errno);
	}

	/*
	 *	Issue the write and time it as appropriate.
	 */

	bytes = DISK_BLOCK_SIZE * blocks;

	if ( DTP_WRITE_METRICS(dtp) == (void *) NULL )
	{
		size = write(fd, DTP_WRITE_BUFFER(dtp), bytes);
		erc = errno;
	}
	else
	{
		struct timezone	tz;
		struct timeval	after;
		struct timeval	before;
		struct timeval	result;
		float		duration;

		(void) gettimeofday(&before, &tz);
		size = write(fd, DTP_WRITE_BUFFER(dtp), bytes);
		erc = errno;
		(void) gettimeofday(&after, &tz);

		timersub(&after, &before, &result);

		duration = ((float) result.tv_sec) +
					(((float) result.tv_usec) / 1.0E6);

		histo_collect(DTP_WRITE_METRICS(dtp), duration);
	}

	if ( size == -1 )
	{
		return (erc);
	}

	/*
	 *	Return the results.
	 */

	return ((size == bytes) ? 0 : EIO);
}

/*
 *	read_blocks
 */

int
read_blocks(	int			fd,
		DISK_THREAD_PARAMETER	*dtp,
		unsigned long		starting_block,
		unsigned long		blocks )
{
	int	erc;
	ssize_t	size;
	ssize_t	bytes;
	loff_t	l_offset;

	/*
	 *	Perform the seek.
	 */

	l_offset = ((loff_t) starting_block) * ((loff_t) DISK_BLOCK_SIZE); 

	if ( lseek64(fd, l_offset, SEEK_SET) == -1 )
	{
		return (errno);
	}

	/*
	 *	Issue the read and time it as appropriate.
	 */

	bytes = DISK_BLOCK_SIZE * blocks;

	if ( DTP_READ_METRICS(dtp) == (void *) NULL )
	{
		size = read(fd, DTP_READ_BUFFER(dtp), bytes);
		erc = errno;
	}
	else
	{
		struct timezone	tz;
		struct timeval	after;
		struct timeval	before;
		struct timeval	result;
		float		duration;

		(void) gettimeofday(&before, &tz);
		size = read(fd, DTP_READ_BUFFER(dtp), bytes);
		erc = errno;
		(void) gettimeofday(&after, &tz);

		timersub(&after, &before, &result);

		duration = ((float) result.tv_sec) +
					(((float) result.tv_usec) / 1.0E6);

		histo_collect(DTP_READ_METRICS(dtp), duration);
	}

	if ( size == -1 )
	{
		return (erc);
	}

	/*
	 *	Return the results.
	 */

	return ((size == bytes) ? 0 : EIO);
}

/*
 *	lock_block
 */

int
lock_block( DISK_INFO *di, unsigned long block, int sleep_control )
{
	BLOCK_LOCK	*p;
	int		erc;
	unsigned long	index;

	/*
	 *	Compute the hash index.
	 */

	index = block & 0xFF;

	/*
	 *	Acquire the mechanism lock.
	 */

	pthread_mutex_lock(&di -> di_lock);

	/*
	 *	The process loop.
	 */

	while ( TRUE )
	{
		/*
		 *	Search the hash list for a match.
		 */

		for ( p = di -> di_hash[index].blhh_list;
				p != (BLOCK_LOCK *) NULL; p = p -> bl_next )
		{
			if ( p -> bl_block_number == block )
			{
				break;
			}
		}

		/*
		 *	Found a match? Deal with it!
		 */

		if ( p == (BLOCK_LOCK *) NULL )
		{
			/*
			 *	No match. Enter a BLOCK_LOCK into the
			 *	appropriate hash table entry list.
			 */

			if ( di -> di_bl_free_list == (BLOCK_LOCK *) NULL )
			{
				(void) fprintf(stderr, "%s: list empty\n",
								Prog_name);

				exit(1);
			}

			p = di -> di_bl_free_list;
			di -> di_bl_free_list = p -> bl_next;

			p -> bl_block_number = block;

			p -> bl_next = di -> di_hash[index].blhh_list;
			di -> di_hash[index].blhh_list = p;

			pthread_mutex_unlock(&di -> di_lock);

			erc = 0;

			break;
		}
		else
		{
			/*
			 *	Match - block is already locked.
			 */

			if ( sleep_control == LOCK_MAY_SLEEP )
			{
				pthread_cond_wait(
					&di -> di_hash[index].blhh_conditional,
					&di -> di_lock);
			}
			else
			{
				erc = -1;

				break;
			}
		}
	}

	/*
	 *	Release the lock.
	 */

	pthread_mutex_unlock(&di -> di_lock);

	/*
	 *	Return status.
	 */

	return (erc);
}

/*
 *	unlock_block
 */

void
unlock_block( DISK_INFO *di, unsigned long block )
{
	BLOCK_LOCK	*p;
	unsigned long	index;
	BLOCK_LOCK	*prev;

	/*
	 *	Compute the hash index.
	 */

	index = block & 0xFF;

	/*
	 *	Acquire the mechanism lock.
	 */

	pthread_mutex_lock(&di -> di_lock);

	/*
	 *	Search the hash list for a match.
	 */

	prev = (BLOCK_LOCK *) NULL;

	for ( p = di -> di_hash[index].blhh_list; p != (BLOCK_LOCK *) NULL;
							p = p -> bl_next )
	{
		if ( p -> bl_block_number == block )
		{
			break;
		}

		prev = p;
	}

	/*
	 *	Better find a match!
	 */

	if ( p == (BLOCK_LOCK *) NULL )
	{
		(void) fprintf(stderr, "%s: unlock failure\n", Prog_name);

		exit(1);
	}
	else
	{
		/*
		 *	Remove BLOCK_LOCK from hash list (unlock).
		 */

		if ( prev == (BLOCK_LOCK *) NULL )
		{
			di -> di_hash[index].blhh_list = p -> bl_next;
		}
		else
		{
			prev -> bl_next = p -> bl_next;
		}

		p -> bl_next =  di -> di_bl_free_list;
		di -> di_bl_free_list = p;
	}

	/*
	 *	Wake up any thread waiting for a lock within this hash head.
	 */

	pthread_cond_broadcast(&di -> di_hash[index].blhh_conditional);

	/*
	 *	Release the lock.
	 */

	pthread_mutex_unlock(&di -> di_lock);

	/*
	 *	Done!
	 */

	return;
}

/*
 *	compare_buffers
 */

static int
compare_buffers( void *b1, void *b2, unsigned long io_blocks )
{
	unsigned long	*u1;
	unsigned long	*u2;
	unsigned long	count;

	u1 = (unsigned long *) b1;
	u2 = (unsigned long *) b2;
	count = (io_blocks * DISK_BLOCK_SIZE) / sizeof(unsigned long);

	while ( count-- )
	{
		if ( *u1++ != *u2++ )
		{
			return (EDOM);
		}
	}

	return (0);
}

/*
 *	generate_pattern
 */

static void
generate_pattern(	void		*buffer,
			unsigned long	starting_block,
			unsigned long	number,
			unsigned long	io_blocks )
{
	unsigned long	*u;
	unsigned long	count;

	u = (unsigned long *) buffer;
	count = (io_blocks * DISK_BLOCK_SIZE) / sizeof(unsigned long);

	starting_block += number;	/* permute by thread number */

	while ( count-- )
	{
		*u++ = starting_block++;
	}

	return;
}

/*
 *	write_with_verification
 */

int
write_with_verification(	int			fd,
				DISK_THREAD_PARAMETER	*dtp,
				unsigned long		starting_block,
				unsigned long		io_blocks )
{
	int	erc;

	/*
	 *	Generate a pattern in the write buffer that is based on
	 *	the block number to be written and the ID of thread
	 *	performing this operation.
	 */

	generate_pattern(DTP_WRITE_BUFFER(dtp), starting_block,
						DTP_NUMBER(dtp), io_blocks);

	/*
	 *	Lock the block to prevent changes.
	 */

	(void) lock_block(DTP_DISK_INFO(dtp), starting_block, LOCK_MAY_SLEEP);

	/*
	 *	Write the pattern.
	 */

	erc = write_blocks(fd, dtp, starting_block, io_blocks);

	/*
	 *	Deal with the results.
	 */

	if ( erc == 0 )
	{
		/*
		 *	Write succeeded! Read the results back.
		 */

		erc = read_blocks(fd, dtp, starting_block, io_blocks);

		/*
		 *	Unlock the block.
		 */

		unlock_block(DTP_DISK_INFO(dtp), starting_block);

		/*
		 *	If there was no read error, verify the data written.
		 */

		if ( erc == 0 )
		{
			erc = compare_buffers(DTP_WRITE_BUFFER(dtp),
					DTP_READ_BUFFER(dtp), io_blocks);
		}
	}
	else
	{
		/*
		 *	Write error. Unlock the block.
		 */

		unlock_block(DTP_DISK_INFO(dtp), starting_block);
	}

	/*
	 *	Return status.
	 */

	return (erc);
}

/*
 *	g_init_sleepy_barrier
 */

void
g_init_sleepy_barrier( G_SLEEPY_BARRIER *barrier, unsigned long n_threads )
{
	pthread_mutex_init(&barrier -> gsb_check_in_lock, NULL);
	pthread_cond_init(&barrier -> gsb_conditional, NULL);
	barrier -> gsb_check_in_count = 0;
	barrier -> gsb_emptying = FALSE;
	barrier -> gsb_full_count = n_threads;

	return;
}

/*
 *	g_sleepy_barrier
 *
 *	This barrier routine is self re-initializing, so it needs to be
 *	initialized only once at the beginning.
 *
 *	This type of barrier puts each arriving thread to sleep until the
 *	last thread arrives and waits up all of the sleeping threads.
 */

void
g_sleepy_barrier( G_SLEEPY_BARRIER *barrier )
{
	/*
	 *	Don't allow a thread to enter until all of the threads
	 *	from the previous barrier have left.
	 */

	while ( barrier -> gsb_emptying );

	/*
	 *	Not in emptying state so allow threads to check in.
	 *
	 *	Acquire the barrier lock.
	 */

	pthread_mutex_lock(&barrier -> gsb_check_in_lock);

	/*
	 *	Increment the barrier check in count.
	 */

	barrier -> gsb_check_in_count++;

	/*
	 *	React based on the updated check in count.
	 */

	if ( barrier -> gsb_check_in_count ==
				barrier -> gsb_full_count ) /* last thread */
	{
		/*
		 *	Last thread has checked in. Mark the barrier as
		 *	emptying (preventing any thread from entering
		 *	until the barrier is empty). Broadcast the wakeup
		 *	to all sleeping threads so that they may leave.
		 */

		barrier -> gsb_emptying = TRUE;

		pthread_cond_broadcast(&barrier -> gsb_conditional);
	}
	else					 /* all other processors */
	{
		/*
		 *	Any thread except the last has checked in.
		 *
		 *	Sleep on the conditional until the last thread
		 *	checks in.
		 */

		pthread_cond_wait(&barrier -> gsb_conditional,
						&barrier -> gsb_check_in_lock);
	}

	/*
	 *	Handle the emptying state. Threads get here when they
	 *	are leaving after all of them have checked in.
	 *
	 *	Decrement the check in count.
	 */

	barrier -> gsb_check_in_count--;

	/*
	 *	If the check in count is now 0, the barrier is empty and
	 *	it is permissible for threads to enter the barrier once
	 *	again.
	 */

	if ( barrier -> gsb_check_in_count == 0 )
	{
		barrier -> gsb_emptying = FALSE;
	}

	/*
	 *	Release the barrier lock.
	 */

	pthread_mutex_unlock(&barrier -> gsb_check_in_lock);

	/*
	 *	Done!
	 */

	return;
}
