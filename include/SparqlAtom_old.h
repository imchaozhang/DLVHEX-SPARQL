/* 
 * File:   SparqlAtom.h
 * Author: chaozhang
 *
 * Created on April 21, 2014, 9:53 PM
 */

#ifndef SPARQLATOM_H
#define	SPARQLATOM_H


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <redland.h>
#include <raptor2.h>
#include <rdf_heuristics.h>
#include <rdf_hash_internal.h>
#include <rdf_init.h>

#include <boost/lexical_cast.hpp>

#include <string>

#include <dlvhex2/PluginInterface.h>
#include <dlvhex2/Error.h>

#define DEFAULT_STORAGE_OPTIONS		"dsn='localVirtuoso',user='dba',password='dba'"
#define DEFAULT_CONTEXT			"http://smarthome.asu.edu"
#define DEFAULT_IDENTIFIER		"http://smarthome.asu.edu"

namespace dlvhex {
    namespace sparql {
        
        class SparqlAtom : public PluginAtom
        {
		public:

            SparqlAtom();
            
            
            void
            map_query_result(librdf_world* world, librdf_model* model, librdf_query_results *results, Answer& answer_para, Registry &registry_para);
            
            virtual void
            retrieve(const Query& query, Answer& answer) throw (PluginError);

        };
    }
}



#endif	/* SPARQLATOM_H */

