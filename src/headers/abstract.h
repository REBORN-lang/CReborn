#ifndef CRBC_ABSTR
#define CRBC_ABSTR

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===== EXPRESSIONS =====
enum ExprKind {
    EXPR_INT, EXPR_BOOL,
    EXPR_CHAR, EXPR_STRING,
    EXPR_IDENT
};

typedef struct Expr {
    enum ExprKind kind;
    void *as;
} Expr;

typedef struct ExprInt {
    int value;
} ExprInt;
//
typedef struct ExprChar {
    char value;
} ExprChar;
//
typedef struct ExprBool {
    bool value;
} ExprBool;
//
typedef struct ExprString {
    char *value;
} ExprString;
//
typedef struct ExprIdent {
    char *name;
} ExprIdent;

// ===== STATEMENTS =====
typedef struct Stmt {
    int _dummy;
} Stmt;

typedef struct Block {
    int _dummy;
} Block;

// ===== DECLARATIONS =====
enum DeclKind {
    DECL_VAR,
    DECL_FUNC,
    DECL_TYPE_STRUCT,
    DECL_TYPE_ENUM,
    DECL_TYPE_UNION
};

typedef struct Decl {
    enum DeclKind kind;
    void *as;
} Decl;

// variable declaration
typedef struct DeclVar {
    char *ident;
    char *type;      // TODO: replace with Type*
    Expr *init;      // NULL => declaration only
} DeclVar;

// function declaration
typedef struct DeclFunc {
    char *ident;
    char *return_type;  // NULL => inferred
    char *params;       // TODO: param list
    Block *body;        // NULL => forward declaration
} DeclFunc;

// struct type declaration
typedef struct DeclTypeStruct {
    char *ident;
    char *members;   // TODO: member list
} DeclTypeStruct;

// enum type declaration
typedef struct EnumMember {
    char *name;
    char *value;     // NULL => implicit
} EnumMember;

typedef struct DeclTypeEnum {
    char *ident;
    EnumMember *members;
} DeclTypeEnum;

// union type declaration
typedef struct DeclTypeUnion {
    char *ident;
    char *members;   // TODO: member list
} DeclTypeUnion;

// ===== FUNCTIONS =====
static inline Decl *DeclareVariable(const char *ident, const char *type, Expr *init) {
    Decl *decl   = malloc(sizeof *decl);
    DeclVar *var = malloc(sizeof *var);

    var->ident   = strdup(ident);
    var->type    = type ? strdup(type) : NULL;
    var->init    = init;

    decl->kind   = DECL_VAR;
    decl->as     = var;

    return decl;
}

static inline Expr *ExprIntLiteral(int value) {
    Expr *expr   = malloc(sizeof *expr);
    ExprInt *lit = malloc(sizeof *lit);

    lit->value   = value;

    expr->kind   = EXPR_INT;
    expr->as     = lit;

    return expr;
}

#endif

