			.def	getSP, setSP
			.def	saveContext
			.def	restoreContext

			.text

saveContext:
			POPX.A	-52(SP)					; Move o endereço de retorno para o topo da nova pilha
			PUSHM.A #12, R15				; Salva o contexto
			SUBX.A	#4,SP					; Ajusta a pilha para a posição do novo retorno
			RETA

restoreContext:
			POPX.A R3						; Descarta o endereço de retorno
			POPM.A #12, R15					; Restaura o contexto
			RETI							; Retorna da interrupção

getSP:
    		MOVX.A SP, R12					; Copia o ponteiro da pilha para R12 (retorno)
    		ADDX.A #4, R12					; Corrige o valor do CALL
    		RETA							; Retorna

setSP:
    		SUBX.A #4, R12					; PUSH end. de retorno para a nova pilha:
			MOVX.A 0(SP), 0(R12)			; decrementa a nova pilha e move o novo conteúdo
   			MOVX.A R12, SP					; Escreve no ponteiro da pilha a nova posição
			RETA
