
; * New * SE driver for DM-SYSTEM2  source list (need m80/l80)
; Copyright by GIGAMIX / Programed by Mattya
; Address = (2400h〜27FFh:1KB)

;変更点
;SEPLAYは HLにデータ先頭アドレスが入って呼ばれる
;差し替え可能なドライバにするためヘッダ情報を付加
; Address = (2800h〜2BFFh:1KB)

;        .z80
;        aseg
;        ORG     2800h

bgmpau		equ	04049h
psgchn		equ	0405dh
;seadd		equ	0431ah
;seadd		equ	0bffeh

bgflag		equ	04300h + 15
;---------------------------
;		 0....5....10...15...20...25...30...35...
	DEFM	'* New * SE driver for DM-SYSTEM2 /Mattya'
	DEFB	1AH,01H
	DEFS	6
;--------------------------

xSEon::
        jp      seplay
xSEint::
	jp	seint



; seplay **********************************************************************
;[in]	a		演奏するSE番号(0のとき強制終了)
;	seadd(431ah)	データ先頭アドレス
;[out]	なし
;[reg]	あらかた
seplay:
;        inc     hl
;        inc     hl
;        ld      a,(hl)

	or	a
	jp	z,se.end
	dec	a
	ld	c,a

	.comment	&
	push	bc


;ワークエリアのゼロクリア
	ld	hl,work
	ld	(hl),0
	ld	de,work+1
	ld	bc,work.end-work-1
	ldir

	pop	bc
			&


;全チャンネル共通データの格納
;       ld      hl,seadd
;       ld      e,(hl)
;       inc     hl
;       ld      d,(hl)
        EX      DE,HL

	ld	a,(de)
	ld	(work),a		;データ数格納

	inc	de
	ld	h,0
	ld	l,c
	add	hl,de
	ex	de,hl
	ld	h,0
	ld	l,c
	add	hl,hl
	add	hl,de			;hl …… ディレクトリ

	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	push	de
	inc	hl
	push	hl
	ld	a,(hl)
	rlca
	and	00000001b
	ld	(work+1),a		;BGM停止on/off(1:off)
;	call	nz,bgmpau
	pop	hl
	ld	a,(hl)
	and	00000011b
	ld	(work+2),a		;使用チャンネル数(1〜3)
	dec	hl
	dec	hl
	pop	de
	add	hl,de			;hl …… 最初のチャンネルのSEヘッダ


;PSG チャンネルのマスク
	ld	b,a
	push	bc
	push	hl
	ld	a,00011111b
msk.loop:
	rlca
	djnz	msk.loop
	ld	(psgchn.w),a
	ld	l,a
;	call	psgchn
	pop	hl
	pop	bc


;各チャンネルごとのデータの格納
	ld	ix,work.c
scan.loop:
	push	hl
	ld	d,0
	ld	e,(hl)
	add	hl,de
	ld	(ix),l
	ld	(ix+1),h		;最初のSEデータのアドレス

	pop	hl
	inc	hl
	ld	a,(hl)
	ld	(ix+10),a		;最初のウェイト

	inc	hl
	ld	a,(hl)
	rrca
	rrca
	rrca
	rrca
	and	00001111b
	ld	(ix+2),a		;ディチューン

	ld	a,(hl)
	and	00001111b
	ld	(ix+3),a		;優先順位

	ld	a,0ffh
	ld	(ix+13),a		;→使用中

	ld	de,16
	add	ix,de
	inc	hl
	djnz	scan.loop

        di
        ld      a,(bgflag)
        set     1,a
        ld      (bgflag),a
        ei


;終了
se.end:
;	ld	bc,work.end-work
;	ld	de,9000h
;	ld	hl,work
;	ldir

	ret




; seint ***********************************************************************
;[in]	なし
;[out]	なし
;[reg]	あらかた
seint:
	ld	hl,cnl.a
	exx
	ld	ix,work.a
	call	one.cnl

	ld	hl,cnl.b
	exx
	ld	ix,work.b
	call	one.cnl

	ld	hl,cnl.c
	exx
	ld	ix,work.c
	call	one.cnl

	ret




;１チャンネル分の処理 ---------------------------
jmp.tbl1:
	dw	bit00,bit01,bit10,bit11
jmp.tbl2:
	dw	bit1100,bit1101,bit1110,bit1111

one.cnl0:
	inc	de
one.cnl00:
	ld	(ix),e
	ld	(ix+1),d
one.cnl:
	ld	a,(ix+13)
	or	a
	ret	z			;SEで使っていないチャンネル

	ld	a,(ix+10)
	or	a
	jr	z,one.cnl01
	dec	(ix+10)
	jp	to.end			;ウェイト中

one.cnl01:
	ld	e,(ix)
	ld	d,(ix+1)
	ld	a,(de)
	ld	hl,jmp.tbl1
one.cnl1:
	rlca
	rlca
	and	00000011b
	add	a,a
	ld	b,0
	ld	c,a
	add	hl,bc
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ex	de,hl
	ld	e,(ix)
	ld	d,(ix+1)
	ld	a,(de)
	inc	de
	jp	(hl)			;a   = ひとつめのデータ
					;de  = ふたつめのデータのアドレス
					;ix  = ワークの先頭アドレス




;00?? -----------------------
;1st:	0 0 w w w w w w		w:次の発声までの待ち時間(0〜63)
;2nd:	l l l l l l l l		l:ループ回数(0〜254)
;				l=FFhの場合、そのSEの終了
;3rd:	a a a a a a a a		a:ループ先の相対アドレス(-255〜0)
bit00:
	ld	(ix+10),a

	ld	a,(ix+11)
	or	a
	jr	nz,@loop		;ループ中

	ld	a,(de)
	cp	0ffh
	jr	z,hekira		;SE終了

	inc	a
	ld	(ix+11),a
	inc	de
	ld	a,(de)
	ld	(ix+12),a
	dec	de
@loop:
	inc	de
	inc	de
	dec	(ix+11)
	jr	z,one.cnl00		;ループ終了

	ld	h,0
	ld	l,(ix+12)
	ex	de,hl
	and	a
	sbc	hl,de
	ex	de,hl
	jp	one.cnl00


hekira:
	xor	a
	ld	(ix+13),a

	exx
	inc	hl
	inc	hl
	inc	hl
	ld	a,(hl)
	or	(psgchn.w)
	ld	(psgchn.w),a
	ld	l,a
;	call	psgchn
	jp	to.end



;01?? -----------------------
;	0 1 w w w w w w		1回の割り込み処理の終了
;				w:次の発声までの待ち時間(0〜63)
bit01:
	res	6,a
	ld	(ix+10),a
	ld	(ix),e
	ld	(ix+1),d


to.end:
;ポルタメントの処理
	ld	l,(ix+6)
	ld	h,(ix+5)
	ld	a,(ix+7)
	or	a
	jr	z,detune
	ld	a,(ix+9)
	or	a
	jr	nz,bit010		;今回は増減させない

	ld	a,(ix+8)
	ld	(ix+9),a

	ld	d,0
	ld	e,(ix+7)
	bit	3,e
	call	nz,minus
	add	hl,de
	res	4,h
	ld	(ix+6),l
	ld	(ix+5),h

bit010:
	dec	(ix+9)


;ディチューンの処理
detune:
	ld	d,0
	ld	e,(ix+2)
	bit	3,e
	call	nz,minus
	add	hl,de
	res	4,h
	push	hl

;PSGレジスタに書き込む
	exx
	ld	c,(hl)

	ld	a,(ix+14)
	or	a
	jr	z,write0
	ld	a,c
	or	00111000b
	ld	c,a
write0:

	ld	a,(ix+15)
	or	a
	jr	z,write1
	ld	a,c
	or	00000111b
	ld	c,a
write1:

	inc	hl
	ld	a,(hl)
	pop	de
	di
	call	wrtpsg
	inc	a
	ld	e,d
	call	wrtpsg			;トーン

	inc	hl
	ld	a,(hl)
	ld	e,(ix+4)
	call	wrtpsg			;音量

	ld	a,7
	call	rdpsg
	inc	hl
	or	(hl)
	and	c
	ld	e,a
	ld	a,7
	call	wrtpsg			;ノイズ／トーンのon/off
	ei


;	ld	bc,work.end-work
;	ld	de,9000h
;	ld	hl,work
;	ldir
	ret


cnl.a:	db	11110110b,0, 8,00001001b
cnl.b:	db	11101101b,2, 9,00010010b
cnl.c:	db	11011011b,4,10,00100100b



;10?? -----------------------
;	1 0 n t v v v v		n:ノイズ t:トーンのon/off (1:off)
;				v:音量指定(0〜15)
bit10:
	ld	c,a
	and	00001111b
	ld	(ix+4),a		;音量
	ld	a,c
	and	00100000b
	ld	(ix+14),a		;ノイズ
	ld	a,c
	and	00010000b
	ld	(ix+15),a		;トーン
	jp	one.cnl00



;11?? -----------------------
bit11:
	ld	hl,jmp.tbl2
	rlca
	rlca
	jp	one.cnl1



;1100 -----------------------
;1st:	1 1 0 0 |high4|		トーンの直接指定 (0〜4095)
;2nd:	|     low8    |
bit1100:
	and	00001111b
	ld	(ix+5),a
	ld	a,(de)
	ld	(ix+6),a
	jp	one.cnl0



;1101 -----------------------
;	1 1 0 1 n n n n		n:ノイズの直接指定(0〜15:実際は×2して発声)
bit1101:
	and	00001111b
	ld	(half.noise),a
	jp	one.cnl00



;1110 -----------------------
;1st:	1 1 1 0 p p p p		p:ポルタメント(-8〜+7)	p=0でポルタメントoff
;2nd:	t t t t t t t t		t:増減時間(0〜255)
bit1110:
	and	00001111b
	ld	(ix+7),a
	ld	a,(de)
	ld	(ix+8),a
	jp	one.cnl0



;1111 -----------------------
;	1 1 1 1 v v v v		v:音量の相対指定(-8〜+7)
bit1111:
	and	00001111b
	bit	3,a
	jr	z,bit11110
	or	11110000b
bit11110:
	ld	c,(ix+4)
	add	a,c
	ld	(ix+4),a
	jp	one.cnl00




; sub *************************************************************************
;PSGレジスタに値を書き込む
;[in]	a	レジスタ番号
;	e	書き込む値
;[out]	なし
;[reg]	af'
wrtpsg:
	out	(0a0h),a
	ex	af,af'
	ld	a,e
	out	(0a1h),a
	ex	af,af'
	ret


;PSGレジスタから値を読む
;[in]	a	レジスタ番号
;[out]	a	読み込んだ値
;[reg]	af
rdpsg:
	out	(0a0h),a
	in	a,(0a2h)
	ret


;4bit + 16bit のための補正
;[in]	de	補正する値(4bit)
;[out]	de	補正された値(16bit)
;[reg]	af,de
minus:
	ld	d,0ffh
	ld	a,e
	or	11110000b
	ld	e,a
	ret



; work ************************************************************************
work:
	db	0			;データ数
	db	0			;BGM停止on/off(1:off)
	db	0			;使用チャンネル数(1〜3)
half.noise:
	db	0			;ノイズ(0〜15:実際は×2して発声)
psgchn.w:
	db	0			;PSGCHN へ渡す値

work.c:
	dw	0			;読み出しているSEデータのアドレス    +0
	db	0			;ディチューン(-8〜+7)
	db	0			;優先順位(0(高)〜15(低))             +3
	db	0			;音量(0〜15)
	db	0			;トーン(上位４ビット)                +5
	db	0			;トーン(下位８ビット)
	db	0			;ポルタメント(-8〜+7)                +7
	db	0			;増減時間(0〜255)
	db	0			;現在の増減時間(0〜255)              +9
	db	0			;次の発声までの待ち時間(0〜63)
	db	0			;ループ回数(0〜254)                 +11
	db	0			;ループ先の相対アドレス(-255〜0)
	db	0			;SEで使用中かどうか(0ffh:使用中)    +13
	db	0			;ノイズのon/off(1:off)
	db	0			;トーンのon/off(1:off)              +15

work.b:
	ds	16,0
work.a:
	ds	16,0
work.end:


;	end
