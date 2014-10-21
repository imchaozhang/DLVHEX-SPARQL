/**
 * @file UpdateAtom.cpp
 * @author Chao ZHANG
 * @date 04/22/2014 21:09:10
 *
 * @brief Defintion of the Update Atom.
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "UpdateAtom.h"
#include "virtuosoConn.h"
#include <string>
#include <dlvhex2/Registry.h>
#include <dlvhex2/Term.h>


namespace dlvhex {
    namespace sparql {
        UpdateAtom::UpdateAtom() : PluginAtom("update", 1)
        {
            
            
            addInputConstant();
            addInputConstant();
            addInputConstant();
            
            
            setOutputArity(0);
        }
        
        
        void
        UpdateAtom::retrieve(const Query& query, Answer& answer) throw (PluginError)
        {
            Registry &registry = *getRegistry();
            
            std::string update_subject;
            
            std::string update_predicate;
            
            std::string update_object;
            
            
            const Term& s_subject = registry.terms.getByID(query.input[0]);
            
            const Term& s_predicate = registry.terms.getByID(query.input[1]);
            
            const Term& s_object = registry.terms.getByID(query.input[2]);
            
            
            if (!s_subject.isQuotedString())
            {
                throw PluginError("Wrong input argument type for argument 1");
            }
            
            update_subject = s_subject.getUnquotedString();
            
            
            if (!s_predicate.isQuotedString())
            {
                throw PluginError("Wrong input argument type for argument 2");
            }
            
            update_predicate = s_predicate.getUnquotedString();
            
            
            if (!s_object.isQuotedString())
            {
                throw PluginError("Wrong input argument type for argument 3");
            }
            
            
            update_object = s_object.getUnquotedString();
            
            
            virtuosoConn newVirtuoso;
            
            newVirtuoso.add_triple(update_subject.c_str(),update_predicate.c_str(),update_object.c_str());
            
            
            
            Tuple tu;
            answer.get().push_back(tu);
            
				
                }
	}
    
}

