#include	<stdio.h>
#include	<stdlib.h>
#include	<pthread.h>
#include	<math.h>
#include	"disk-stress.h"

/*
 *	defines
 */

#define	FIFO_SIZE	1024

#define	MBIG		4000000
#define	MSEED		1618033
#define	MZ		0
#define	FAC		(1.0 / MBIG)

/*
 *	locals
 */

static long		Idum = (long) -1;

static pthread_mutex_t	Fifo_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t	Fifo_conditional = PTHREAD_COND_INITIALIZER;
static pthread_t	Fifo_thread;

static unsigned long	Fifo_in;
static unsigned long	Fifo_out;
static unsigned long	Fifo_size;
static double		Fifo[FIFO_SIZE];

/*
 *	internal_uniform_random
 *
 *	set idum to any negative value to (re)initialize the sequence.
 *
 *	assumes long to be at least 32 bits
 */

static double
internal_uniform_random( long *idum_p )
{
	int	i;
	int	k;
	int	ii;
	long	mj;
	long	mk;

	static int	inext;
	static int	inextp;
	static double	ma[56];		/* 56 is a magic number */

	static int	first = TRUE;

	if ( (*idum_p < 0) || first )
	{
		first = FALSE;
		mj = MSEED - (*idum_p < 0 ? -*idum_p : *idum_p);
		mj %= MBIG;
		ma[55] = mj;
		mk = 1.0;

		for ( i = 1; i <= 54; i++ )
		{
			ii = (21 * i) % 55;
			ma[ii] = mk;
			mk = mj - mk;

			if (mk < MZ)
			{
				mk += MBIG;
			}

			mj = ma[ii];
		}

		for ( k = 1; k <= 4; k++ )
		{
			for ( i = 1; i <= 55; i++ )
			{
				ma[i] -= ma[1 + (i + 30) % 55];

				if ( ma[i] < MZ )
				{
					ma[i] += MBIG;
				}
			}
		}

		inext = 0;
		inextp = 31;
		*idum_p = 1;
	}

	if ( ++inext == 56 )
	{
		inext = 1;
	}

	if ( ++inextp == 56 )
	{
		inextp = 1;
	}

	mj = ma[inext] - ma[inextp];

	if ( mj < MZ )
	{
		mj += MBIG;
	}

	ma[inext] = mj;

	return (mj * FAC);
}

/*
 *	Producer thread
 */

static void
producer( void *arg )
{
	double		value;
	unsigned long	per_invocation_count;

	/*
	 *	Acquire the FIFO lock.
	 */

	pthread_mutex_lock(&Fifo_lock);

	/*
	 *	Loop forever.
	 */

	while ( TRUE )
	{
		/*
		 *	Fill the FIFO. There is an invocation limiter to
		 *	prevent the possibility of running forever on MP
		 *	systems.
		 */

		per_invocation_count = FIFO_SIZE;

		while ( (Fifo_size < FIFO_SIZE) && (per_invocation_count > 0) )
		{
			pthread_mutex_unlock(&Fifo_lock);

			value = internal_uniform_random(&Idum);

			pthread_mutex_lock(&Fifo_lock);

			Fifo[Fifo_in++] = value;

			Fifo_size++;

			if ( Fifo_in >= FIFO_SIZE )
			{
				Fifo_in = 0;
			}

			per_invocation_count--;
		}

		/*
		 *	If the FIFO was initially empty issue a
		 *	broadcast to get things going again.
		 */

		pthread_cond_broadcast(&Fifo_conditional);

		/*
		 *	Wait on the conditional for something to do.
		 *
		 *	The FIFO lock is atomically freed before the
		 *	wait and reacquired before this thread gets
		 *	to proceed into the generator loop below.
		 */

		pthread_cond_wait(&Fifo_conditional, &Fifo_lock);
	}

	/*
	 *	Done!
	 */

	return;
}

/*
 *	init_uniform_random
 */

int
init_uniform_random( long seed )
{
	int	erc;

	/*
	 *	Handle the seed.
	 */

	Idum = (seed < 0) ? seed : -seed;

	/*
	 *	Prime the generator.
	 */

	(void) internal_uniform_random(&Idum);

	/*
	 *	Initialize the FIFO controls.
	 */

	Fifo_in = 0;
	Fifo_out = 0;
	Fifo_size = 0;

	/*
	 *	Attempt to invoke the producer thread.
	 */

	erc = pthread_create(&Fifo_thread, (pthread_attr_t *) NULL,
						(void *) producer, &erc);

	/*
	 *	Return the status.
	 */

	return (erc);
}

/*
 *	uniform_random
 */

double
uniform_random( void )
{
	double	value;

	/*
	 *	Acquire the FIFO lock.
	 */

	pthread_mutex_lock(&Fifo_lock);

	/*
	 *	An empty FIFO must be filled. Wake up the producer thread
	 *	and wait for it to signal that it is done. Loop around this
	 *	process to deal with the worst case situation on MP machines.
	 */

	while ( Fifo_size == 0 )
	{
		pthread_cond_broadcast(&Fifo_conditional);
		pthread_cond_wait(&Fifo_conditional, &Fifo_lock);
	}

	/*
	 *	Obtain a value to return.
	 */

	value = Fifo[Fifo_out++];

	Fifo_size--;

	if ( Fifo_out >= FIFO_SIZE )
	{
		Fifo_out = 0;
	}

	/*
	 *	If the FIFO is now less than half empty, wake up the
	 *	producer thread.
	 */

	if ( Fifo_size < (FIFO_SIZE/2) )
	{
		pthread_cond_broadcast(&Fifo_conditional);
	}

	/*
	 *	Release the FIFO lock.
	 */

	pthread_mutex_unlock(&Fifo_lock);

	/*
	 *	Return the random number.
	 */

	return (value);
}

/*
 *	uniform_random_between
 */

double
uniform_random_between( double lower, double upper )
{
	double	range = upper - lower;

	return (lower + range * uniform_random());
}

