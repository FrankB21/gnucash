/*
 * FIEL:
 * builder.h
 *
 * FUNCTION:
 * Generic SQL backend query builder
 * Compiles typed tag-value pairs into sql queries
 *
 * HISTORY:
 * Linas Vepstas January 2001
 */

#ifndef __SQL_BUILDER_H__
#define __SQL_BUILDER_H__

#include "date.h"
#include "guid.h"

typedef enum {
   SQL_UPDATE=1,
   SQL_INSERT,
   SQL_SELECT
} sqlBuild_QType;

typedef struct _builder sqlBuilder;

extern sqlBuilder * sqlBuilder_new(void);
extern void sqlBuilder_destroy (sqlBuilder *);

/* Start building a new SQL query on table 'tablename' 
 * Previous query is erased.
 */
extern void sqlBuild_Table (sqlBuilder *b,
                           const char *tablename,
                           sqlBuild_QType qtype);


/* Set tag-value pairs.  Each of these adds the indicated
 * tag and value to an UPDATE or INSERT statement.  For SELECT
 * statements, val may be NULL (and is ignored in any case).
 */
extern void sqlBuild_Set_Str (sqlBuilder *b,
                              const char *tag,
                              const char *val);

extern void sqlBuild_Set_Char (sqlBuilder *b,
                              const char *tag,
                              char val);

extern void sqlBuild_Set_GUID (sqlBuilder *b,
                               const char *tag,
                               const GUID *val);

extern void sqlBuild_Set_Date (sqlBuilder *b,
                               const char *tag,
                               Timespec val);


/* build the update 'where' clause */
/* typically, the primary tag is used in the where clauses */
/* this where clause is used for both SELECT and UPDATE statements */
extern void sqlBuild_Where_Str (sqlBuilder *b,
                                const char *tag,
                                const char *val);
extern void sqlBuild_Where_GUID (sqlBuilder *b,
                                const char *tag,
                                const GUID *val);


/* Get the completed query string back.  This query string is
 * probably general enough to work with almost any SQL db, 
 * I beleive. */
extern const char *sqlBuild_Query (sqlBuilder *b);


#endif /* __SQL_BUILDER_H__ */

