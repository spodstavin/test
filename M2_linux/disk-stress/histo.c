#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<pthread.h>
#include	"histo.h"

struct metric_header
{
	pthread_mutex_t	mh_lock;
	unsigned long	*mh_bins;
	unsigned long	mh_bin_count;
	float		mh_min_value;
	float		mh_max_value;
	float		mh_range;
	unsigned long	mh_out_of_bounds_low;
	unsigned long	mh_out_of_bounds_high;
};

typedef struct metric_header METRIC_HEADER;

/*
 *	histo_init
 */

void *
histo_init(	unsigned long	bins,
		float		min_value,
		float		max_value,
		unsigned long	*error )
{
	unsigned long	i;
	METRIC_HEADER	*header;

	if ( bins < 1 )
	{
		*error = HISTO_VALUE;

		return ((void *) NULL);
	}

	if ( min_value > max_value )
	{
		*error = HISTO_VALUE;

		return ((void *) NULL);
	}

	header = (METRIC_HEADER *) malloc(sizeof(METRIC_HEADER));

	if ( header == (METRIC_HEADER *) NULL )
	{
		*error = HISTO_MEMORY;

		return ((void *) NULL);
	}

	header -> mh_bins = malloc(bins * sizeof(unsigned long));

	if ( header -> mh_bins == (unsigned long *) NULL )
	{
		free((void *) header);

		*error = HISTO_MEMORY;

		return ((void *) NULL);
	}

	header -> mh_bin_count = bins;
	header -> mh_min_value = min_value;
	header -> mh_max_value = max_value;
	header -> mh_range = max_value - min_value;

	for ( i = 0; i < bins; i++ )
	{
		header -> mh_bins[i] = 0;
	}

	pthread_mutex_init(&header -> mh_lock, NULL);

	*error = HISTO_OK;

	return ((void *) header);
}

/*
 *	histo_collect
 */

void
histo_collect( void *histo, float value )
{
	unsigned long	index;
	METRIC_HEADER	*header;

	header = (METRIC_HEADER *) histo;

	if ( value < header -> mh_min_value )
	{
		header -> mh_out_of_bounds_low++;

		return;
	}

	if ( value > header -> mh_max_value )
	{
		header -> mh_out_of_bounds_high++;

		return;
	}

	index = ((value - header -> mh_min_value) / header -> mh_range) *
						header -> mh_bin_count;

	pthread_mutex_lock(&header -> mh_lock);
	header -> mh_bins[index] += 1;
	pthread_mutex_unlock(&header -> mh_lock);

	return;
}

/*
 *	histo_collate
 */

int
histo_collate(	void		*out,
		void		*in_1,
		void		*in_2,
		unsigned long	*error )
{
	unsigned long	i;
	METRIC_HEADER	*h_in1;
	METRIC_HEADER	*h_in2;
	METRIC_HEADER	*h_out;

	if ( (h_in1 -> mh_bin_count != h_in2 -> mh_bin_count) ||
	     (h_in1 -> mh_min_value != h_in2 -> mh_min_value) ||
	     (h_in1 -> mh_max_value != h_in2 -> mh_max_value) )
	{
		*error = HISTO_VALUE;

		return (HISTO_ERROR);
	}

	for ( i = 0; i < h_in1 -> mh_bin_count; i++ )
	{
		h_out -> mh_bins[i] = h_in1 -> mh_bins[i] +
							h_in2 -> mh_bins[i];
	}
}

/*
 *	histo_dismiss
 */

void
histo_dismiss( void *histo )
{
	METRIC_HEADER	*header;

	header = (METRIC_HEADER *) histo;

	free((void *) header -> mh_bins);
	free(histo);

	return;
}

void
histo_print(	void	*histo,
		void	*token,
		void	(*before)(void *token),
		void	(*after)(void *token),
		void	(*bin_stats)(	void		*token,
					float		bin_lower,
					float		bin_upper,
					unsigned long	bin_count),
		void	(*out_low)(void *token, unsigned long count),
		void	(*out_high)(void *token, unsigned long count) )
{
	unsigned long	i;
	float		lower;
	METRIC_HEADER	*header;
	float		bin_size;

	header = (METRIC_HEADER *) histo;

	(*before)(token);

	bin_size = header -> mh_range / ((float) header -> mh_bin_count);

	for ( i = 0; i < header -> mh_bin_count; i++ )
	{
		lower = ((float) i) * bin_size;

		(*bin_stats)(token, lower, lower + bin_size,
							header -> mh_bins[i]);
	}

	(*out_low)(token, header -> mh_out_of_bounds_low);
	(*out_high)(token, header -> mh_out_of_bounds_high);

	(*after)(token);

	return;
}
