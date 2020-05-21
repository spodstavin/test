#if !defined(__HISTO_H__)

#define	HISTO_OK	0
#define	HISTO_ERROR	1

#define	HISTO_MEMORY	1
#define	HISTO_VALUE	2

void *
histo_init(	unsigned long	bins,
		float		min_value,
		float		max_value,
		unsigned long	*error );

void
histo_collect( void *metrics, float value );

int
histo_collate(	void		*out,
		void		*in_1,
		void		*in_2,
		unsigned long	*error );

void
histo_dismiss( void *histo );

void
histo_print(	void	*histo,
		void	*token,
		void	(*before)( void *token ),
		void	(*after)( void *token ),
		void	(*bin_stats)(	void		*token,
					float		bin_lower,
					float		bin_upper,
					unsigned long	bin_count),
		void	(*out_low)( void *token, unsigned long count ),
		void	(*out_high)( void *token, unsigned long count ) );

#endif
