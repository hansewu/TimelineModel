

#ifndef __MLT_EXT_FILTER_H__
#define __MLT_EXT_FILTER_H__

#include "MltConfig.h"

#include <framework/mlt.h>
#include "MltProperties.h"

namespace Mlt
{
	class Properties;
	class Producer;
	class Service;

	class MLTPP_DECLSPEC ExtFilter 
	{
		private:
			Filter m_Filter;
		public:
			ExtFilter( Filter &filter );
			ExtFilter( ExtFilter &filter );
			virtual ~ExtFilter( );
			//virtual mlt_filter get_filter( );
			//mlt_service get_service( );
			int connect( Service &service, int index = 0 );
			void set_in_and_out( int in, int out );
			int get_in( );
			int get_out( );
			int get_length( );
			int get_length2( Frame &frame );
			int get_track( );
			int get_position( Frame &frame );
			double get_progress( Frame &frame );
			void process( Frame &frame );


			void set_filter(const char *filter_name); // kShotcutFilterProperty = "moviemator:filter"  f.set(kShotcutFilterProperty, "fadeInMovit");
			const char *get_filter(); //filter->get(kShotcutFilterProperty)

			int get_loader(); //?? filter->get_int("_loader")
			const char *get_service_name(); //filter->get("mlt_service")

			void set_results(void *data, int data_size); //??  m_filter->set("results", NULL, 0);
	};
}

#endif // __MLT_EXT_FILTER_H__
