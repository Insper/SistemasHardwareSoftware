mov $0FFh,%al
add $1,%al 
;CF = 1, AL = 00
----------------------------
;tentar valor abaixo de zero
mov $0,%al
sub $1,%al 
;CF = 1, AL = FF
----------------------------
;tentar valor abaixo de zero
mov $0,%al
cmp $1,%al 
;CF = 1, AL = 00