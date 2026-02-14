#ifndef CRBC_ABSTR_H
#define CRBC_ABSTR_H

#include <stdio.h> // FILE, fprintf()
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===== EXPRESSIONS =====
enum ExprKind {
    EXPR_INT, EXPR_BOOL,
    EXPR_CHAR, EXPR_STRING,
    EXPR_IDENT
};

// fwd.
typedef struct Expr Expr;  
typedef struct ExprInt ExprInt;
typedef struct ExprChar ExprChar;
typedef struct ExprBool ExprBool;
typedef struct ExprString ExprString;
typedef struct ExprIdent ExprIdent;
typedef struct ExprBinary ExprBinary;

struct Expr {
    enum ExprKind kind;
    union {
        ExprInt    *intLiteral;
        ExprBool   *boolLiteral;
        ExprChar   *charLiteral;
        ExprString *stringLiteral;
        ExprIdent  *ident;
    } as;
};

struct ExprInt {
    int value;
};
//
struct ExprChar {
    char value;
};
//
struct ExprBool {
    bool value;
};
//
struct ExprString {
    char *value;
};
//
struct ExprIdent {
    char *name;
};
//
struct ExprBinary {
    Expr *left;
    Expr *right;
    char op;
};

// ===== STATEMENTS =====

typedef struct Stmt Stmt;
typedef struct Block Block;

struct Stmt {
    int _dummy;
};

struct Block {
    int _dummy;
};

// ===== DECLARATIONS =====
enum DeclKind {
    DECL_VAR,
    DECL_FUNC,
    DECL_TYPE_STRUCT,
    DECL_TYPE_ENUM,
    DECL_TYPE_UNION
};

// fwd.
typedef struct Decl Decl;
typedef struct DeclVar DeclVar;
typedef struct DeclFunc DeclFunc;
typedef struct DeclTypeStruct DeclTypeStruct;
typedef struct EnumMember EnumMember;
typedef struct DeclTypeEnum DeclTypeEnum;
typedef struct DeclTypeUnion DeclTypeUnion;

struct Decl {
    enum DeclKind kind;
    union {
        DeclVar        *var;
        DeclFunc       *func;
        DeclTypeStruct *typeStruct;
        DeclTypeEnum   *typeEnum;
        DeclTypeUnion  *typeUnion;
    } as;
};

// variable declaration
struct DeclVar {
    char *ident;
    char *type;      // TODO: replace with Type*
    Expr *init;      // NULL => declaration only
};

struct DeclFunc {
    char *ident;
    char *return_type;  // NULL => inferred
    char *params;       // TODO: param list
    Block *body;        // NULL => forward declaration
};

struct DeclTypeStruct {
    char *ident;
    char *members;   // TODO: member list
};

struct EnumMember {
    char *name;
    char *value;     // NULL => implicit
};

struct DeclTypeEnum {
    char *ident;
    EnumMember *members;
};

// union type declaration
struct DeclTypeUnion {
    char *ident;
    char *members;   // TODO: member list
};

// ===== FUNCTIONS =====
static inline Decl *DeclareVariable(const char *ident, const char *type, Expr *init) {
    Decl *decl   = malloc(sizeof *decl);
    DeclVar *var = malloc(sizeof *var);

    var->ident   = strdup(ident);
    var->type    = type ? strdup(type) : NULL;
    var->init    = init;

    decl->kind   = DECL_VAR;
    decl->as.var = var;

    return decl;
}

static inline Expr *ExprIntLiteral(int value) {
    Expr *expr   = malloc(sizeof *expr);
    ExprInt *lit = malloc(sizeof *lit);

    lit->value   = value;

    expr->kind          = EXPR_INT;
    expr->as.intLiteral = lit;

    return expr;
}

#endif

