/* 
 * File:   UpdateAtom.h
 * Author: chaozhang
 *
 * Created on April 21, 2014, 9:53 PM
 */

#ifndef UPDATEATOM_H
#define	UPDATEATOM_H


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "virtuosoConn.h"

#include <string>

#include <dlvhex2/PluginInterface.h>
#include <dlvhex2/Error.h>

namespace dlvhex {
    namespace sparql {
        
        class UpdateAtom : public PluginAtom
        {
		public:

            UpdateAtom();
                     
            virtual void
            retrieve(const Query& query, Answer& answer) throw (PluginError);

        };
    }
}



#endif	/* UPDATEATOM_H */

