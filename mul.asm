                section         .text

                global          _start
_start:

                sub             rsp, 128 * 6 * 8
                lea             rdi, [rsp + 128 * 8]
                mov             rcx, 128
                call            read_long
                mov             rdi, rsp
                call            read_long
                lea             r8, [rsp + 128 * 8]
                mov             r9, rcx
                lea             r11, [rsp]
                lea             rsi, [rsp + 4*128*8]
                lea             rdi, [rsp + 2*128*8]
                call            mul_long_long
                mov             rdi, rsi
                call            write_long

                mov             al, 0x0a
                call            write_char

                jmp             exit

; adds two long number
;    rdi -- address of summand #1 (long number)
;    rsi -- address of summand #2 (long number)
;    rcx -- length of long numbers in qwords
; result:
;    sum is written to rsi
add_long_long:
                push            rdi
                push            rsi
                push            rcx

                clc
.loop:
                mov             rax, [rdi]
                lea             rdi, [rdi + 8]
                adc             [rsi], rax
                lea             rsi, [rsi + 8]
                dec             rcx
                jnz             .loop

                pop             rcx
                pop             rsi
                pop             rdi
                ret

; adds 64-bit number to long number
;    rdi -- address of summand #1 (long number)
;    rax -- summand #2 (64-bit unsigned)
;    rcx -- length of long number in qwords
; result:
;    sum is written to rdi
add_long_short:
                push            rdi
                push            rcx
                push            rdx

                xor             rdx,rdx
.loop:
                add             [rdi], rax
                adc             rdx, 0
                mov             rax, rdx
                xor             rdx, rdx
                add             rdi, 8
                dec             rcx
                jnz             .loop

                pop             rdx
                pop             rcx
                pop             rdi
                ret

; multiplies long number by a short
;    r8 -- address of multiplier #1 (long number)
;    r11 -- address of multiplier #2 (long number)
;    r9 -- length of long numbers in qwords
; result:
;    product is written to rsi
mul_long_long:
                push            rsp
                push            r8
                push            r9
                push            r11
                push            rdi
                push            rsi
                push            rcx
                push            rbx

                call            copy_long

                xor             r10, r10
.loop:
                mov             r12, rcx
                mov             rcx, 128
                mov             rbx, [r11]
                lea             r11, [r11 + 8]
                call            mul_long_short
                call            shift_rdi
                call            add_long_long
                call            copy_long
                inc             r10
                mov             rcx, r12
                dec             rcx
                jnz             .loop

                pop             rbx
                pop             rcx
                pop             rsi
                pop             rdi
                pop             r11
                pop             r9
                pop             r8
                pop             rsp
                ret
; copy long number
;   r8 - address of number
;   rdi - address to copy
;   rcx - length of long number in qwords
copy_long:
                push            r8
                push            rdi
                push            rcx
                push            r9
.loop:
                mov             r9, [r8]
                mov             [rdi], r9
                lea             r8, [r8+8]
                lea             rdi, [rdi+8]
                dec             rcx
                jnz             .loop

                pop r9
                pop rcx
                pop rdi
                pop r8
                ret

; shift long number
;   rdi - address of number
;   r10 - offset
;   rcx - length of long number in qwords
shift_rdi:
                push            rdi
                push            r10
                push            rcx
                push            r9

                xor             r9, r9
                lea             rdi, [rdi + 8 * rcx - 8]

.loop:
                mov             r9, [rdi]
                mov             [rdi+8*r10], r9
                sub             rdi, 8
                dec             rcx
                jnz             .loop

                add             rdi, 8
                cmp             r10, 0
                je              .end

.loop1:
                xor             r9, r9
                mov             [rdi], r9
                lea             rdi, [rdi+8]
                dec             r10
                jnz             .loop1

.end:
                pop             r9
                pop             rcx
                pop             r10
                pop             rdi
                ret

; multiplies long number by a short
;    rdi -- address of multiplier #1 (long number)
;    rbx -- multiplier #2 (64-bit unsigned)
;    rcx -- length of long number in qwords
; result:
;    product is written to rdi
mul_long_short:
                push            rax
                push            rdi
                push            rcx
                push            rsi

                xor             rsi, rsi
.loop:
                mov             rax, [rdi]
                mul             rbx
                add             rax, rsi
                adc             rdx, 0
                mov             [rdi], rax
                add             rdi, 8
                mov             rsi, rdx
                dec             rcx
                jnz             .loop

                pop             rsi
                pop             rcx
                pop             rdi
                pop             rax
                ret

; divides long number by a short
;    rdi -- address of dividend (long number)
;    rbx -- divisor (64-bit unsigned)
;    rcx -- length of long number in qwords
; result:
;    quotient is written to rdi
;    rdx -- remainder
div_long_short:
                push            rdi
                push            rax
                push            rcx

                lea             rdi, [rdi + 8 * rcx - 8]
                xor             rdx, rdx

.loop:
                mov             rax, [rdi]
                div             rbx
                mov             [rdi], rax
                sub             rdi, 8
                dec             rcx
                jnz             .loop

                pop             rcx
                pop             rax
                pop             rdi
                ret

; assigns a zero to long number
;    rdi -- argument (long number)
;    rcx -- length of long number in qwords
set_zero:
                push            rax
                push            rdi
                push            rcx

                xor             rax, rax
                rep stosq

                pop             rcx
                pop             rdi
                pop             rax
                ret

; checks if a long number is a zero
;    rdi -- argument (long number)
;    rcx -- length of long number in qwords
; result:
;    ZF=1 if zero
is_zero:
                push            rax
                push            rdi
                push            rcx

                xor             rax, rax
                rep scasq

                pop             rcx
                pop             rdi
                pop             rax
                ret

; read long number from stdin
;    rdi -- location for output (long number)
;    rcx -- length of long number in qwords
read_long:
                push            rcx
                push            rdi

                call            set_zero
.loop:
                call            read_char
                or              rax, rax
                js              exit
                cmp             rax, 0x0a
                je              .done
                cmp             rax, '0'
                jb              .invalid_char
                cmp             rax, '9'
                ja              .invalid_char

                sub             rax, '0'
                mov             rbx, 10
                call            mul_long_short
                call            add_long_short
                jmp             .loop

.done:
                pop             rdi
                pop             rcx
                ret

.invalid_char:
                mov             rsi, invalid_char_msg
                mov             rdx, invalid_char_msg_size
                call            print_string
                call            write_char
                mov             al, 0x0a
                call            write_char

.skip_loop:
                call            read_char
                or              rax, rax
                js              exit
                cmp             rax, 0x0a
                je              exit
                jmp             .skip_loop

; write long number to stdout
;    rdi -- argument (long number)
;    rcx -- length of long number in qwords
write_long:
                push            rax
                push            rcx

                mov             rax, 20
                mul             rcx
                mov             rbp, rsp
                sub             rsp, rax

                mov             rsi, rbp

.loop:
                mov             rbx, 10
                call            div_long_short
                add             rdx, '0'
                dec             rsi
                mov             [rsi], dl
                call            is_zero
                jnz             .loop

                mov             rdx, rbp
                sub             rdx, rsi
                call            print_string

                mov             rsp, rbp
                pop             rcx
                pop             rax
                ret

; read one char from stdin
; result:
;    rax == -1 if error occurs
;    rax \in [0; 255] if OK
read_char:
                push            rcx
                push            rdi

                sub             rsp, 1
                xor             rax, rax
                xor             rdi, rdi
                mov             rsi, rsp
                mov             rdx, 1
                syscall

                cmp             rax, 1
                jne             .error
                xor             rax, rax
                mov             al, [rsp]
                add             rsp, 1

                pop             rdi
                pop             rcx
                ret
.error:
                mov             rax, -1
                add             rsp, 1
                pop             rdi
                pop             rcx
                ret

; write one char to stdout, errors are ignored
;    al -- char
write_char:
                sub             rsp, 1
                mov             [rsp], al

                mov             rax, 1
                mov             rdi, 1
                mov             rsi, rsp
                mov             rdx, 1
                syscall
                add             rsp, 1
                ret

exit:
                mov             rax, 60
                xor             rdi, rdi
                syscall

; print string to stdout
;    rsi -- string
;    rdx -- size
print_string:
                push            rax

                mov             rax, 1
                mov             rdi, 1
                syscall

                pop             rax
                ret


                section         .rodata
invalid_char_msg:
                db              "Invalid character: "
invalid_char_msg_size: equ             $ - invalid_char_msg
