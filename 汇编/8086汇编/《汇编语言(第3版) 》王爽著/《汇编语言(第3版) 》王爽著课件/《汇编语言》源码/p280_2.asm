;编程：在屏幕中间依次显示“a”~“z”，并可以让人看清。在显示的过程中，按下'Esc'键后，改变显示的颜色。

;对更改中断向量时间间隔内可能发生的中断状况作了进一步安全保障 cli ,sti的使用

;完整功能代码：

assume cs:code

stack segment
	db 128 dup (0)
stack ends

data segment
	dw 0,0
data ends

code segment
start:	mov ax,stack
	mov ss,ax
	mov sp,128
	mov ax,data
	mov ds,ax
	mov ax,0
	mov es,ax



	push es:[9*4]
	pop ds:[0]
	push es:[9*4+2]
	pop ds:[2]		;将原来的int 9中断例程的入口地址保存在ds:0、ds:2单元中

	cli			;置屏蔽中断标志位IF=0

	mov word ptr es:[9*4],offset int9
	mov es:[9*4+2],cs	;在中断向量表中设置新的int 9中断例程的入口地址

	sti			;撤消屏蔽，置屏蔽中断标志位IF=1

	mov ax,0b800h
	mov es,ax
	mov ah,'a'
    s:	mov  es:[160*12+40*2],ah
	call delay
	inc ah
	cmp ah,'z'
	jna s
	mov ax,0
	mov es,ax

	cli			;置屏蔽中断标志位IF=0

	push ds:[0]
	pop es:[9*4]
	push ds;[2]
	pop es;[9*4+2]   	;将中断向量表中int 9中断例程的入口恢复为原来的地址

	sti			;撤消屏蔽，置屏蔽中断标志位IF=1

	mov ax,4c00h
	int 21h

delay:	push ax
	push dx
	mov dx,2000h
	mov ax,0
  s1: 	sub ax,1
	sbb dx,0
	cmp ax,0
	jne s1
	cmp dx,0
	jne s1
	pop dx
	pop ax
	ret

;------以下为新的int 9中断例程--------------------

int9:	push ax
	push bx
	push es

	in al,60h

	pushf
	;pushf
	;pop bx
	;and bh,11111100b
	;push bx
	;popf			;去掉了中断处理程序中没有意义的指令语句
	call dword ptr ds:[0] 	;对int指令进行模拟，调用原来的int 9中断例程

	cmp al,1
	jne int9ret

	mov ax,0b800h
	mov es,ax
	inc byte ptr es:[160*12+40*2+1]  ;属性增加1，改变颜色

int9ret:pop es
	pop bx
	pop ax
	iret

code ends
end start

      push ds:[0]
	cli;置屏蔽中断标志位
      pop es:[9*4]
      push ds;[2]
      pop es;[9*4+2]   ;将中断向量表中的int 9 中断向量恢复
	sti;取消屏蔽

      mov ax,4c00h
      int 21h
delay:push ax
      push dx
      mov dx,2000h ;loop 10000000h times
      mov ax,0
  s1: sub ax,1
      sbb dx,0
      cmp ax,0
      jne s1
      cmp dx,0
      jne s1
      pop dx
      pop ax
      ret

   ;---以下是我们的 int 9 中断处理程序---------------------

 int9:push ax
      push bx
      push es

      in al,60h

      pushf
      ;;;;;
      call dword ptr ds:[0] ;调用系统提供的中断处理程序
      cmp al,1
      jne int9ret

      mov ax,0b800h
      mov es,ax
      inc byte ptr es:[160*12+40*2+1]  ;颜色属性 +1 

int9ret:pop es
      pop bx
      pop ax
      iret

code ends
end start
