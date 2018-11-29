.include "buff.h"

;============================================-=
; File:
       .file "buff.s"
; Behaviour:
;      Library of Buffalo Monitor Routines.
; Assumptions:
;      Routines only modify registers and the stack.
; Board:
;      CME11-E9-EVBU (with the PW link HACK)
; Author:
;      Peter Walsh & Aidan Ferguson Oct 31 2018
;============================================-=

;----------------------------------------------
;            Text Section (code and data)
;----------------------------------------------
.sect .text

;======================
; Buff routine stubs
;======================

set INCHAR, 0xffcd
set OUTA, 0xffb8
set OUTSTRGO, 0xffca
set OUTCRLF, 0xffc4
set OUT1BSP, 0xffbe


; INCHAR returns value in a
; C expects return value in b 

getc:   psha

        jsr INCHAR

        psha
        pulb
        pula
        rts

; C provides input parameter in b
; OUTA expects input parameter in a

putc:   psha
        pshb
        pula

        jsr OUTA


        pula
        rts

wcrlf:  jsr OUTCRLF
        rts

; C provides input parameter in d
; OUTSTRGO  expects input parameter in x

wstr:   pshx     ; save x 
        xgdx
        pshx     ; save d

        tpa      ; save ccr
        psha

        jsr OUTSTRGO

        pula
        tap      ; restore ccr

        pulx     ; restore d
        xgdx
        pulx     ; restore x
xwstr:  rts

mdump:  pshx     ; save x 
        xgdx
        pshx     ; save d

        tpa      ; save ccr
        

        jsr OUT1BSP

        
        tap      ; restore ccr

        pulx     ; restore d
        xgdx
        pulx     ; restore x
xmdump: rts

run:    pshx     ; save x 
        xgdx
        pshx     ; save d

        tpa      ; save ccr
        

        jsr 0,x 

        
        tap      ; restore ccr

        pulx     ; restore d
        xgdx
        pulx     ; restore x
xrun:   rts
.end
