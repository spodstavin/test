#if !defined(__DISK_STRESS_H__)

#define __DISK_STRESS_H__

#include	<time.h>
#include	<pthread.h>

/*
 *	Useful defines.
 */

#define	TRUE			1
#define FALSE			0
#define	YYDEBUG			1	/* yacc/bison debugging enabled */
#define	DISK_BLOCK_SIZE		512	/* minimum physical block size */
#define	PREFERED_ALIGNMENT	512

/*
 *	Sleepy barrier structure
 */

struct g_sleepy_barrier
{
	pthread_mutex_t		gsb_check_in_lock;
	pthread_cond_t		gsb_conditional;
	unsigned long		gsb_check_in_count;
	unsigned long		gsb_full_count;
	volatile int		gsb_emptying;
};

typedef struct g_sleepy_barrier G_SLEEPY_BARRIER;

/*
 *	Barrier prototypes
 */

void g_init_sleepy_barrier( G_SLEEPY_BARRIER *barrier,
						unsigned long n_threads );

void g_sleepy_barrier( G_SLEEPY_BARRIER *barrier );

/*
 *	Disk thread parameter (one per thread)
 */

struct disk_thread_parameter
{
	struct disk_info	*dtp_disk_info;		/* disk information */

	pthread_t		dtp_id;			/* thread ID */
	unsigned long		dtp_number;		/* thread number */
	unsigned long		dtp_status;		/* exit status */
	void			*dtp_write_buffer;	/* buffer memory */
	void			*dtp_read_buffer;	/* buffer memory */
};

typedef struct disk_thread_parameter DISK_THREAD_PARAMETER;

#define	DTP_BLOCK_DEVICE_NAME(x) \
				((x) -> dtp_disk_info -> di_block_device_name)

#define	DTP_RAW_DEVICE_NAME(x) \
				((x) -> dtp_disk_info -> di_raw_device_name)

#define	DTP_ACCESS_PATTERN(x) \
				((x) -> dtp_disk_info -> di_access_pattern)

#define	DTP_READ_FRACTION(x) \
				((x) -> dtp_disk_info -> di_read_fraction)

#define	DTP_REQUESTS_PER_THREAD(x) \
				((x) -> dtp_disk_info -> di_requests_per_thread)

#define	DTP_THREADS_PER_DISK(x) \
				((x) -> dtp_disk_info -> di_threads_per_disk)

#define	DTP_BLOCK_SIZE(x) \
				((x) -> dtp_disk_info -> di_block_size)

#define	DTP_STARTING_BLOCK(x) \
				((x) -> dtp_disk_info -> di_starting_block)

#define	DTP_TEST_AREA_SIZE(x) \
				((x) -> dtp_disk_info -> di_test_area_size)

#define DTP_WRITE_VERIFICATION(x) \
				((x) -> dtp_disk_info -> di_write_verification)

#define	DTP_DISK_INFO(x) \
				((x) -> dtp_disk_info)

#define	DTP_ID(x) \
				((x) -> dtp_id)

#define	DTP_WRITE_BUFFER(x) \
				((x) -> dtp_write_buffer)

#define	DTP_READ_BUFFER(x) \
				((x) -> dtp_read_buffer)

#define	DTP_NUMBER(x) \
				((x) -> dtp_number)

#define	DTP_STATUS(x) \
				((x) -> dtp_status)

#define	DTP_READ_METRICS(x) \
				((x) -> dtp_disk_info -> di_read_metrics)

#define	DTP_WRITE_METRICS(x) \
				((x) -> dtp_disk_info -> di_write_metrics)

/*
 *	block_lock structure - if present block is locked. No need for
 *	length parameter since all threads are performing the same length,
 *	non-overlaping I/Os.
 */

struct block_lock
{
	struct block_lock	*bl_next;
	unsigned long		bl_block_number;
};

typedef struct block_lock BLOCK_LOCK;

/*
 *	block locking hash head
 */

struct block_lock_hash_head
{
	BLOCK_LOCK	*blhh_list;
	pthread_cond_t	blhh_conditional;
};

typedef struct block_lock_hash_head BLOCK_LOCK_HASH_HEAD;

#define	HASH_TABLE_SIZE	256

/*
 *	Disk structure (one per test "disk")
 */

struct disk_info
{
	struct disk_info	*di_next;

	char			*di_block_device_name;	/* disk device name */
	char			*di_raw_device_name;	/* disk device name */
	unsigned long		di_access_pattern;	/* random or seq. */
	unsigned long		di_write_verification;	/* verify writes? */
	float			di_read_fraction;	/* read fraction */
	unsigned long		di_requests_per_thread;	/* I/Os */
	unsigned long		di_block_size;		/* block size */
	unsigned long		di_starting_block;	/* starting block */
	unsigned long		di_test_area_size;	/* area size */
	unsigned long		di_threads_per_disk;	/* threads per disk */

	float			di_histogram_upper_bound;
	unsigned long		di_histogram_bins;
	void			*di_read_metrics;	/* metric collection */
	void			*di_write_metrics;	/* metric collection */

	DISK_THREAD_PARAMETER	*di_parameters;

	pthread_mutex_t		di_lock;
	BLOCK_LOCK		*di_bl_free_list;
	BLOCK_LOCK_HASH_HEAD	di_hash[HASH_TABLE_SIZE];
};

typedef struct disk_info DISK_INFO;

/*
 *	Pattern defines
 */

#define	DISK_PATTERN_RANDOM	0
#define	DISK_PATTERN_SEQUENTIAL	1

/*
 *	Prototypes
 */

void	*allocate_memory( unsigned long amount );

void	random_io_thread( void *arg );
void	sequential_io_thread( void *arg );

int	init_uniform_random ( long seed );
double	uniform_random( void );
double	uniform_random_between( double lower, double upper );

int	choose_io_type( DISK_THREAD_PARAMETER *dtp );

int	write_blocks(	int			fd,
			DISK_THREAD_PARAMETER	*dtp,
			unsigned long		starting_block,
			unsigned long		blocks );

int	read_blocks(	int			fd,
			DISK_THREAD_PARAMETER	*dtp,
			unsigned long		starting_block,
			unsigned long		blocks );

int	write_with_verification(int			fd,
				DISK_THREAD_PARAMETER	*dtp,
				unsigned long		starting_block,
				unsigned long		io_blocks );

#define	LOCK_NO_SLEEP	0
#define	LOCK_MAY_SLEEP	1

int	lock_block( DISK_INFO *di, unsigned long block, int sleep_control );
void	unlock_block( DISK_INFO *di, unsigned long block );


void	random_io_thread( void *arg );
void	sequential_io_thread( void *arg );

#endif
