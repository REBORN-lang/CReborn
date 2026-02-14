#ifndef CRBC
#define CRBC
/*================================================================================================*
 * CReborn - The first "official" C implementation of the Reborn programming language
 *           based on the Reborn Standard (reborn-lang.github.io/documents/standard)
 *
 * The name CReborn (C/Reborn, CREBORN or whatever) has been chosen because
 * this implementation works by using C as its IR, or in much simpler terms,
 * this compiler works by compiling Reborn code to C, and then using the GNU C
 * Compiler (GNU Compiler Collection, gcc) to compile the output C program to
 * an executable. This decision was made to both simplify the development and also
 * to be able to focus more on the frontend of the compiler instead of focusing on
 * optimization and platform-specific instructions.
 *================================================================================================*
 *#* STYLE GUIDELINES FOR CODE CONTRIBUTORS (AND MAINTAINERS):
 *    - Use camelCase for variables.
 *    - Use PascalCase for functions.
 *    - 4 spaces indentation (not tabs but spaces.)
 *    - Don't exceed 100 characters on a single line unless you *really* must, it's mostly
 *      for readability since we think that it is better for code to extend vertically, rather
 *      than horizontally. (Also given some developers might use 3:2 or other less-wide formats.)
 *================================================================================================*
 *#* NOTES FOR VIM USERS
 *    - For Vim users that don't know how to set a limit to the coloumn size, you just:
 *                                  :set textwidth=100
 *                                  :set formatoptions+=t
 *      You can also obviously also set this in your .vimrc.
 *    
 *    - For Vim users that want to (a)llow the local .exrc for commodity, you can just do:
 *                                      :set exrc nosecure
 *      and reopen any file in the repo, then you will be asked to (a)llow, meaning to trust this
 *      repo's .exrc, after (a)llowing it you will already have the 4 spaces indentation, the 100
 *      characters limit (textwidth limit) and the format options set automatically. This only
 *      applies when editing files from this repo, but if you want them in your global .vimrc or
 *      neovim config you can also copy them, again, from the local .exrc file.
 *
 * - Note: If you use vim/nvim and you loaded (allowed) the .exrc from this repo you can also use
 *         these commands that will automatically compile for either release / normal mode testing
 *         or for debugging mode.
 *   
 *   :Cn / :Compn - Compiles with 'Normal compile'
 *   :Cd / :Compd - Compiles with 'Debug compile'
 *
 *#* COMPILE COMMANDS
 *   Normal compile = 'cc rbc.c -o crbc -O2 -Wall -Wextra -pedantic'
 *   Debug compile = 'cc rbc.c -o crbc -g -O0 -Wall -Wextra -pedantic -fsanitize=address,undefined'
 */

// Include directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// git@github.com:jstmaxlol/kat
#include "heads/kat.h"

// CReborn headers (CReborn APIs)
#include "heads/codegen.h"
#include "heads/abstract.h"
#include "heads/freeast.h"

// ASTs in abstract.h
//

// Functions (fwd. declars. and externs)
//
// headers/abstract.h
// headers/freeast.h
// headers/codegen.h
//
// local / helpers
static inline int Eval(int x);
static inline void EmitExpr(Expr *expr, FILE *out);
static inline void EmitDeclVar(DeclVar *v, FILE *out);

// main
int main(int argc, char **argv) {
    printf(":> Checking for arguments...\n");

    if (argc >= 2) {
        // mostly debug info
        for (int i = 1; i < argc; i++) {
            printf("argv[%d] = %s\n", i, argv[i]);
        }
    } else {
        printf(":> No arguments were found. (%d)\n\n", argc-1);
    }

    // TODO: remove this, added for clarity
    printf("\n");

    const char *identBuff = "number";
    const char *typeBuff  = "int";

    int valueBuff = 2;

    if (argc == 3) {
        if (strlen(argv[1]) >= 1)
            identBuff = argv[1];
        //if (strlen(argv[2]) >= 1)
        //    typeBuff = argv[2];
        if (strlen(argv[2]) >= 1)
            valueBuff = atoi(argv[2]);
    }

    Expr *e = ExprIntLiteral(valueBuff);
    Decl *decl = DeclareVariable(identBuff, typeBuff, e);

    if (decl->kind == DECL_VAR) {
        DeclVar *v = decl->as.var;
        printf("v->ident=%s, v->type=%s\nlet %s: %s = %d;", v->ident, v->type, v->ident, v->type, valueBuff);
    }

    FreeExpr(e);
    FreeDecl(decl);

    return 0;
}

// Functions (definitions)
//
static inline int Eval(int x) {
    // TODO:
    // (work on this after AST is finished)
    return x;
}

void EmitExpr(Expr *expr, FILE *out) {
    if (!expr) return;

    switch (expr->kind) {

    case EXPR_INT: {
        ExprInt *lit = expr->as.intLiteral;
        fprintf(out, "%d", lit->value);
        break;
    }

    case EXPR_BOOL: {
        ExprBool *b = expr->as.boolLiteral;
        fprintf(out, "%s", b->value ? "1" : "0");
        break;
    }

    case EXPR_CHAR: {
        ExprChar *c = expr->as.charLiteral;
        fprintf(out, "'%c'", c->value);
        break;
    }

    case EXPR_STRING: {
        ExprString *s = expr->as.stringLiteral;
        fprintf(out, "\"%s\"", s->value);
        break;
    }

    case EXPR_IDENT: {
        ExprIdent *id = expr->as.ident;
        fprintf(out, "%s", id->name);
        break;
    }

    default:
        break;
    }
}

void EmitDeclVar(DeclVar *v, FILE *out) {
    fprintf(out, "%s %s", v->type, v->ident);

    if (v->init != NULL) {
        fprintf(out, " = ");
        EmitExpr(v->init, out);
    }

    fprintf(out, ";\n");
}

#endif
