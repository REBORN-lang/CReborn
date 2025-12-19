#ifndef CRBC_FREEAST
#define CRBC_FREEAST

// Free memory functions, utilize after having used the AST

#include <stdlib.h>

void FreeExpr(Expr *expr)
{
    if (!expr) return;

    switch (expr->kind) {
    case EXPR_INT:
        free(expr->as);
        break;
    case EXPR_BOOL:
        break;
    case EXPR_CHAR:
        break;
    case EXPR_STRING:
        break;
    case EXPR_IDENT:
        break;
    default:
        break;
    }

    free(expr);
}

static inline void FreeDeclVar(DeclVar *var)
{
    if (!var) return;

    free(var->ident);
    free(var->type);

    free(var);
}

void FreeDecl(Decl *decl)
{
    if (!decl) return;

    switch (decl->kind) {
    case DECL_VAR:
        FreeDeclVar((DeclVar *)decl->as);
        break;

    case DECL_FUNC:
        /* FreeDeclFunc(...) later */
        break;

    case DECL_TYPE_STRUCT:
        /* FreeDeclTypeStruct(...) later */
        break;

    case DECL_TYPE_ENUM:
        /* ... */
        break;

    case DECL_TYPE_UNION:
        /* ... */
        break;
    }

    free(decl);
}

#endif
