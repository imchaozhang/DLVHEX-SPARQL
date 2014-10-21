/* 
 * File:   virtuosoConn.h
 * Author: chaozhang
 *
 * Created on April 22, 2014, 10:13 PM
 */

#ifndef VIRTUOSOCONN_H
#define	VIRTUOSOCONN_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */


#include <redland.h>
#include <raptor2.h>
#include <rdf_heuristics.h>
#include <rdf_hash_internal.h>

#include <string>




#define DEFAULT_STORAGE_OPTIONS		"dsn='localVirtuoso',user='dba',password='dba'"
#define DEFAULT_CONTEXT			"http://smarthome.asu.edu"
#define DEFAULT_IDENTIFIER		"http://smarthome.asu.edu"

namespace dlvhex
{
    namespace sparql
    {


class virtuosoConn
{
public:
    void init();
    void print_query_result(librdf_query_results*);
    void sparql_select(const std::string& in_select,const std::string& in_graph,const std::string& in_option);
    void free();
    int add_triple(const char *s, const char *p, const char *o);
    int add_triple_typed(const char *s, const char *p, const char *o);
    
    
    virtuosoConn(); //default Constructor
    ~virtuosoConn(); //Destructor
    
    
private:
    librdf_world* world;
    librdf_storage *storage;
    librdf_model* model;
    librdf_node *node;
    librdf_node *subject, *predicate, *object;
    librdf_node* context_node;
    librdf_stream* stream;
    librdf_iterator* iterator;
    librdf_uri *base_uri;
    librdf_query *r_query;
    librdf_query_results *results;
    librdf_hash *options;
    int transactions;
    const char* storage_name;
    const char* storage_options;
    const char* context;
    const char* identifier;
    const char* results_format;
    librdf_statement* statement;
    const char* query_cmd;
  
};

        
    } // sparql
    
} // dlvhex

#endif
