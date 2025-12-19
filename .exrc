if exists('g:crbc_compile_loaded')
  finish
endif
let g:crbc_compile_loaded = 1

let s:cc       = 'gcc'
let s:cflags   = '-std=c23 -Wall -Wextra -pedantic'
let s:dbgflags = '-g -O0 -fsanitize=address,undefined'
let s:optflags = '-O2'

function! s:Compile(debug)
  if &filetype !=# 'c' && &filetype !=# 'cpp'
    echoerr ">>> not a C/++ file!"
    return
  endif

  let l:src = expand('%')
  "let l:out = expand('%:r')
  let l:out = 'crbc'

  if a:debug
    let l:cmd = printf(
          \ '%s %s %s "%s" -o "%sDbg"',
          \ s:cc, s:cflags, s:dbgflags, l:src, l:out
          \ )
    echo ">>> compiling debug build .."
  else
    let l:cmd = printf(
          \ '%s %s %s "%s" -o "%s"',
          \ s:cc, s:cflags, s:optflags, l:src, l:out
          \ )
    echo ">>> compiling release build .."
  endif

  " write changes before compiling - for good luck
  silent write
  execute '!' . l:cmd
endfunction

command! Compn         call s:Compile(0)
command! Cn            call s:Compile(0)

command! Compd         call s:Compile(1)
command! Cd            call s:Compile(1)

