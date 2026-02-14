#ifndef CRBC_FREEAST_H
#define CRBC_FREEAST_H

// Free memory functions, utilize after having used the AST

#include <stdlib.h>

void FreeExpr(Expr *expr)
{
    if (!expr) return;

    switch (expr->kind) {
        case EXPR_INT:
            free(expr->as.intLiteral);
            break;
        case EXPR_BOOL:
            free(expr->as.boolLiteral);
            break;
        case EXPR_CHAR:
            free(expr->as.charLiteral);
            break;
        case EXPR_STRING:
            free(expr->as.stringLiteral);
            break;
        case EXPR_IDENT:
            free(expr->as.ident);
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
        FreeDeclVar(decl->as.var);
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
