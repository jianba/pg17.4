/*-------------------------------------------------------------------------
 *
 * pg_auth_members.h
 *	  definition of the "authorization identifier members" system catalog
 *	  (pg_auth_members).
 *
 *
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/catalog/pg_auth_members.h
 *
 * NOTES
 *	  The Catalog.pm module reads this file and derives schema
 *	  information.
 *
 *-------------------------------------------------------------------------
 */
#ifndef PG_AUTH_MEMBERS_H
#define PG_AUTH_MEMBERS_H

#include "catalog/genbki.h"
#include "catalog/pg_auth_members_d.h"

/* ----------------
 *		pg_auth_members definition.  cpp turns this into
 *		typedef struct FormData_pg_auth_members
 * ----------------
 */
CATALOG(pg_auth_members,1261,AuthMemRelationId) BKI_SHARED_RELATION BKI_ROWTYPE_OID(2843,AuthMemRelation_Rowtype_Id) BKI_SCHEMA_MACRO
{
	Oid			oid;			/* oid */
	Oid			roleid BKI_LOOKUP(pg_authid);	/* ID of a role */
	Oid			member BKI_LOOKUP(pg_authid);	/* ID of a member of that role */
	Oid			grantor BKI_LOOKUP(pg_authid);	/* who granted the membership */
	bool		admin_option;	/* granted with admin option? */
	bool		inherit_option; /* exercise privileges without SET ROLE? */
	bool		set_option;		/* use SET ROLE to the target role? */
	Oid			dbid BKI_LOOKUP_OPT(pg_database);	/* ID of a database this
													 * mapping is effective in */
} FormData_pg_auth_members;

/* ----------------
 *		Form_pg_auth_members corresponds to a pointer to a tuple with
 *		the format of pg_auth_members relation.
 * ----------------
 */
typedef FormData_pg_auth_members *Form_pg_auth_members;

DECLARE_UNIQUE_INDEX_PKEY(pg_auth_members_oid_index, 6303, AuthMemOidIndexId, pg_auth_members, btree(oid oid_ops));
DECLARE_UNIQUE_INDEX(pg_auth_members_role_member_db_index, 2694, AuthMemRoleMemDbIndexId, pg_auth_members, btree(roleid oid_ops, member oid_ops, grantor oid_ops, dbid oid_ops));
DECLARE_UNIQUE_INDEX(pg_auth_members_member_db_role_index, 2695, AuthMemMemRoleDbIndexId, pg_auth_members, btree(member oid_ops, dbid oid_ops, roleid oid_ops, grantor oid_ops));
DECLARE_INDEX(pg_auth_members_grantor_index, 6302, AuthMemGrantorIndexId, pg_auth_members, btree(grantor oid_ops));

MAKE_SYSCACHE(AUTHMEMROLEMEMDB, pg_auth_members_role_member_db_index, 8);
MAKE_SYSCACHE(AUTHMEMMEMDBROLE, pg_auth_members_member_db_role_index, 8);

#endif							/* PG_AUTH_MEMBERS_H */
