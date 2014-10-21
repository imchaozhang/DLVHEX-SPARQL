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


#include <boost/lexical_cast.hpp>

#include <string>

#include <dlvhex2/PluginInterface.h>
#include <dlvhex2/Error.h>


namespace dlvhex {
    namespace sparql {
        
        class SparqlAtom : public PluginAtom
        {
		public:

            SparqlAtom();
         
            virtual void
            retrieve(const Query& query, Answer& answer) throw (PluginError);

        };
    }
}



#endif	/* SPARQLATOM_H */

